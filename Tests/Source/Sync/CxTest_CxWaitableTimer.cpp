/**
 * \file   CxTest_CxWaitableTimer.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxWaitableTimer.h>


//---------------------------------------------------------------------------
CxTest_CxWaitableTimer::CxTest_CxWaitableTimer() {

}
//---------------------------------------------------------------------------
CxTest_CxWaitableTimer::~CxTest_CxWaitableTimer() {

}
//---------------------------------------------------------------------------
/* virtual */
bool
CxTest_CxWaitableTimer::bUnit(
    const ulonglong_t cullCaseLoops
)
{
#if xOS_ENV_WIN
    bool bRv = false;

    CxWaitableTimer WT;

    //-------------------------------------
    //создаем
    bRv = WT.bCreate(false, xT(""), NULL);
    if (false == bRv) {
        printf("CreateWaitableTimer failed (%lu)\n", GetLastError());
        return 1;
    }
    printf("CreateWaitableTimer success (%lu)\n", GetLastError());

    //-------------------------------------
    //Устанавливаем
    WT.bSet(/*-30000000LL*/0, 2000, NULL, NULL, 0);
    if (false == bRv) {
        printf("SetWaitableTimer failed (%lu)\n", GetLastError());
        //--return 2;
    }
    printf("SetWaitableTimer success (%lu)\n", GetLastError());


    while (true) {
        //-------------------------------------
        //ждем
        bRv = WT.bWait(INFINITE);
        printf("ulWait success (%lu)\n", GetLastError());

        if (false == bRv) {
            printf("ulWait failed (%lu)\n", GetLastError());
        } else {
            printf("Timer was signaled.\n");
        }

    }
#elif xOS_ENV_UNIX

#endif

    return true;
}
//---------------------------------------------------------------------------
