/**
 * \file   CxTest_CxIpcSemaphore.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxIpcSemaphore.h>

#include <xLib/Core/CxString.h>
#include <xLib/Sync/CxThread.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxIpcSemaphore::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxIpcSemaphore::CxIpcSemaphore", a_caseLoops)
    {
        struct _Functor
        {
        #if   xENV_WIN
            static uint_t   xSTDCALL
        #elif xENV_UNIX
            static void_t * xSTDCALL
        #endif
            worker(void_t *pArguments)
            {
                // CxTracer() << xT("Start");

                CxIpcSemaphore *psemSem = static_cast<CxIpcSemaphore *>(pArguments);
                xTEST_PTR(psemSem);

                for (int_t i = 0; i < 50; i ++) {
                    psemSem->wait(xTIMEOUT_INFINITE);

                    // CxTracer() << xTRACE_VAR(i);
                }

                // CxTracer() << xT("Stop");

                return 0;
            }
        };

        // create
        CxIpcSemaphore semSemaphore;
        semSemaphore.create(4, xT("sema_name"));

    #if   xENV_WIN
        uintptr_t puiRv = ::_beginthreadex(NULL, 0U, &_Functor::worker, &semSemaphore, 0U, NULL);
        #if xARCH_BITS_32
            xTEST_DIFF(uintptr_t(0), puiRv);
        #else
            xTEST_PTR(puiRv);
        #endif
    #elif xENV_UNIX
        pthread_t id = 0UL;
        int_t iRv = ::pthread_create(&id, NULL, &_Functor::worker, &semSemaphore);
        xTEST_EQ(iRv, 0);
    #endif

        // post
        for (size_t i = 0; i < 50; ++ i) {
            CxThread::currentSleep(1);
            for (int_t x = 0; x < 2; x ++) {
                semSemaphore.post();
            }
        }

        // m_bRv = CxThread::currentSleep(3000);
    }
}
//-------------------------------------------------------------------------------------------------
