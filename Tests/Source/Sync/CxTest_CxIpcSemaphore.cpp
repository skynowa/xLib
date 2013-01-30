/**
 * \file   CxTest_CxIpcSemaphore.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxIpcSemaphore.h>

#include <xLib/Common/CxString.h>
#include <xLib/Sync/CxCurrentThread.h>


//---------------------------------------------------------------------------
CxTest_CxIpcSemaphore::CxTest_CxIpcSemaphore() {

}
//---------------------------------------------------------------------------
CxTest_CxIpcSemaphore::~CxTest_CxIpcSemaphore() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxIpcSemaphore::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    struct _SFunctor
    {
    #if   xOS_ENV_WIN
        static uint_t xSTDCALL
    #elif xOS_ENV_UNIX
        static void * xSTDCALL
    #endif
	    uiJob(void *pArguments) {
	        CxTracer() << xT("Start");

            CxIpcSemaphore *psemSem = static_cast<CxIpcSemaphore *>(pArguments);
            xTEST_PTR(psemSem);

	        for (int i = 0; i < 50; i ++) {
	            psemSem->vWait(xTIMEOUT_INFINITE);

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
    pthread_t ulId = 0UL;

    int iRv = ::pthread_create(&ulId, NULL, &_SFunctor::uiJob, &semSemaphore);
    xTEST_EQ(0, iRv);
#endif

    //-------------------------------------
    // vPost
    for (size_t i = 0; i < 50; ++ i) {
        CxCurrentThread::vSleep(1);

        for (int x = 0; x < 2; x ++) {
            semSemaphore.vPost();
        }
    }

    //m_bRv = CxCurrentThread::bSleep(3000);
}
//---------------------------------------------------------------------------
