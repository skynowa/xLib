/**
 * \file   Test_IpcSemaphore.cpp
 * \brief
 */


#include <Test/Sync/Test_IpcSemaphore.h>

#include <xLib/Core/String.h>
#include <xLib/Sync/Thread.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_IpcSemaphore)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_IpcSemaphore::unit()
{
    xTEST_CASE("IpcSemaphore")
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
                // Tracer() << xT("Start");

                IpcSemaphore *psemSem = static_cast<IpcSemaphore *>(pArguments);
                xTEST_PTR(psemSem);

                for (int_t i = 0; i < 50; i ++) {
                    psemSem->wait(xTIMEOUT_INFINITE);

                    // Tracer() << xTRACE_VAR(i);
                }

                // Tracer() << xT("Stop");

                return 0;
            }
        };

        // create
        IpcSemaphore semSemaphore;
        semSemaphore.create(4, xT("sema_name"));

    #if   xENV_WIN
        uintptr_t puiRv = ::_beginthreadex(xPTR_NULL, 0U, &_Functor::worker, &semSemaphore, 0U, xPTR_NULL);
        #if xARCH_BITS_32
            xTEST_DIFF(uintptr_t(0), puiRv);
        #else
            xTEST_PTR(puiRv);
        #endif
    #elif xENV_UNIX
        pthread_t id = 0UL;
        int_t iRv = ::pthread_create(&id, xPTR_NULL, &_Functor::worker, &semSemaphore);
        xTEST_EQ(iRv, 0);
    #endif

        // post
        for (size_t i = 0; i < 50; ++ i) {
            Thread::currentSleep(1);
            for (int_t x = 0; x < 2; x ++) {
                semSemaphore.post();
            }
        }

        // m_bRv = Thread::currentSleep(3000);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
