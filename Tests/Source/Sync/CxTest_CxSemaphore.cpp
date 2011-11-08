/****************************************************************************
* Class name:  CxTest_CxSemaphore
* Description: test CxSemaphore
* File name:   CxTest_CxSemaphore.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Sync/CxTest_CxSemaphore.h>


#if defined(xOS_ENV_WIN)
//---------------------------------------------------------------------------
BOOL m_bRes = FALSE;
CxSemaphore m_Semaphore;
//---------------------------------------------------------------------------
unsigned __stdcall
vTest( void* pArguments ) {
    BOOL bRes = FALSE;

    /*LOG*/std::cout << "Start" << std::endl;

    for (int i = 1; i < 100; i ++) {
        bRes = m_Semaphore.bWait(INFINITE);
        xTEST_DIFF(FALSE, bRes);

        /*LOG*/std::cout << i << std::endl;
    }

    /*LOG*/std::cout << "Stop" << std::endl;

    return 0;
}
//---------------------------------------------------------------------------
CxTest_CxSemaphore::CxTest_CxSemaphore() {

}
//---------------------------------------------------------------------------
CxTest_CxSemaphore::~CxTest_CxSemaphore() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxSemaphore::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    m_bRes = m_Semaphore.bCreate(NULL, 4, 2048, xT(""));
    xTEST_DIFF(FALSE, m_bRes);

    if (NULL == _beginthreadex(0, 0, &vTest, 0, 0, NULL)) {
        std::cout << "Error begin thread " << std::endl;
    }

    //-------------------------------------
    //bRelease
    for (size_t i = 0; i < 100; ++ i) {
        ::Sleep(2000);

        for (int x = 0; x < 2; x ++) {
            m_bRes = m_Semaphore.bRelease(1, NULL);
            xTEST_DIFF(FALSE, m_bRes);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#elif defined(xOS_ENV_UNIX)

#endif
