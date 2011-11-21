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
/*virtual*/
bool
CxTest_CxWaitableTimer::bUnit(
    const ulonglong_t cullBlockLoops
)
{
#if xOS_ENV_WIN
    bool bRes = false;

    CxWaitableTimer WT;

    //-------------------------------------
    //создаем
    bRes = WT.bCreate(false, xT(""), NULL);
    if (false == bRes) {
        printf("CreateWaitableTimer failed (%lu)\n", GetLastError());
        return 1;
    }
    printf("CreateWaitableTimer success (%lu)\n", GetLastError());

    //-------------------------------------
    //Устанавливаем
    WT.bSet(/*-30000000LL*/0, 2000, NULL, NULL, 0);
    if (false == bRes) {
        printf("SetWaitableTimer failed (%lu)\n", GetLastError());
        //--return 2;
    }
    printf("SetWaitableTimer success (%lu)\n", GetLastError());


    while (true) {
        //-------------------------------------
        //ждем
        bRes = WT.bWait(INFINITE);
        printf("ulWait success (%lu)\n", GetLastError());

        if (false == bRes) {
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
