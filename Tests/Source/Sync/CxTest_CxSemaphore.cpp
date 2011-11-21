/**
 * \file   CxTest_CxSemaphore.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxSemaphore.h>


#if xOS_ENV_WIN
//---------------------------------------------------------------------------
bool m_bRes = false;
CxSemaphore m_Semaphore;
//---------------------------------------------------------------------------
unsigned __stdcall
vTest( void* pArguments ) {
    bool bRes = false;

    /*LOG*/std::cout << "Start" << std::endl;

    for (int i = 1; i < 100; i ++) {
        bRes = m_Semaphore.bWait(INFINITE);
        xTEST_DIFF(false, bRes);

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
bool
CxTest_CxSemaphore::bUnit(
    const ulonglong_t cullBlockLoops
)
{
    m_bRes = m_Semaphore.bCreate(NULL, 4, 2048, xT(""));
    xTEST_DIFF(false, m_bRes);

    if (NULL == _beginthreadex(0, 0, &vTest, 0, 0, NULL)) {
        std::cout << "Error begin thread " << std::endl;
    }

    //-------------------------------------
    //bRelease
    for (size_t i = 0; i < 100; ++ i) {
        ::Sleep(2000);

        for (int x = 0; x < 2; x ++) {
            m_bRes = m_Semaphore.bRelease(1, NULL);
            xTEST_DIFF(false, m_bRes);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
#elif xOS_ENV_UNIX

#endif
