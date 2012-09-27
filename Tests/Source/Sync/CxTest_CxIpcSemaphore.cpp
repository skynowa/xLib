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
bool
CxTest_CxIpcSemaphore::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    struct _SFunctor
    {
    #if xOS_ENV_WIN
        static uint_t xSTDCALL
    #elif xOS_ENV_UNIX
        static void * xSTDCALL
    #endif
	    uiJob(void *pArguments) {
	        CxTracer() << xT("Start");

            CxIpcSemaphore *psemSem = static_cast<CxIpcSemaphore *>(pArguments);
            xTEST_PTR(psemSem);

	        for (int i = 0; i < 50; i ++) {
	            bool bRv = psemSem->bWait(xTIMEOUT_INFINITE);
	            xTEST_EQ(true, bRv);

	            CxTracer() << xTRACE_VAR(i);
	        }

	        CxTracer() << xT("Stop");

	        return 0U;
	    }
    };


    //-------------------------------------
    // bCreate
    CxIpcSemaphore semSemaphore;

    m_bRv = semSemaphore.bCreate(4, xT("sema_name"));
    xTEST_EQ(true, m_bRv);

#if xOS_ENV_WIN
    uintptr_t puiRv = ::_beginthreadex(NULL, 0U, &_SFunctor::uiJob, &semSemaphore, 0U, NULL);
    xTEST_PTR(puiRv);
#elif xOS_ENV_UNIX
    pthread_t ulId = 0UL;

    int iRv = ::pthread_create(&ulId, NULL, &_SFunctor::uiJob, &semSemaphore);
    xTEST_EQ(0, iRv);
#endif

    //-------------------------------------
    // bRelease
    for (size_t i = 0; i < 50; ++ i) {
        m_bRv = CxCurrentThread::bSleep(1);
        xTEST_EQ(true, m_bRv);

        for (int x = 0; x < 2; x ++) {
            m_bRv = semSemaphore.bPost();
            xTEST_EQ(true, m_bRv);
        }
    }

    //m_bRv = CxCurrentThread::bSleep(3000);

    return true;
}
//---------------------------------------------------------------------------
