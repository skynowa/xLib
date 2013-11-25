/**
 * \file   CxTest_CxIpcSemaphore.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxIpcSemaphore.h>

#include <xLib/Core/CxString.h>
#include <xLib/Sync/CxThread.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxIpcSemaphore::unit(
    culonglong_t &a_caseLoops
)
{
    struct _SFunctor
    {
    #if   xOS_ENV_WIN
        static uint_t   xSTDCALL
    #elif xOS_ENV_UNIX
        static void_t * xSTDCALL
    #endif
	    uiJob(void_t *pArguments)
	    {
	        CxTracer() << xT("Start");

            CxIpcSemaphore *psemSem = static_cast<CxIpcSemaphore *>(pArguments);
            xTEST_PTR(psemSem);

	        for (int_t i = 0; i < 50; i ++) {
	            psemSem->wait(xTIMEOUT_INFINITE);

	            CxTracer() << xTRACE_VAR(i);
	        }

	        CxTracer() << xT("Stop");

	        return 0U;
	    }
    };


    //-------------------------------------
    // bCreate
    CxIpcSemaphore semSemaphore;

    semSemaphore.create(4, xT("sema_name"));

#if   xOS_ENV_WIN
    uintptr_t puiRv = ::_beginthreadex(NULL, 0U, &_SFunctor::uiJob, &semSemaphore, 0U, NULL);
    #if xARCH_X86
        xTEST_DIFF(uintptr_t(0), puiRv);
    #else
        xTEST_PTR(puiRv);
    #endif
#elif xOS_ENV_UNIX
    pthread_t id = 0UL;

    int_t iRv = ::pthread_create(&id, NULL, &_SFunctor::uiJob, &semSemaphore);
    xTEST_EQ(0, iRv);
#endif

    //-------------------------------------
    // vPost
    for (size_t i = 0; i < 50; ++ i) {
        CxThread::currentSleep(1);

        for (int_t x = 0; x < 2; x ++) {
            semSemaphore.post();
        }
    }

    //m_bRv = CxThread::currentSleep(3000);
}
//------------------------------------------------------------------------------
