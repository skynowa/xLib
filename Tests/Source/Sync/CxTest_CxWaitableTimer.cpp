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
BOOL
CxTest_CxWaitableTimer::bUnit(
    const ULONGLONG cullBlockLoops
)
{
#if defined(xOS_ENV_WIN)
    BOOL bRes = FALSE;

    CxWaitableTimer WT;

    //-------------------------------------
    //создаем
    bRes = WT.bCreate(FALSE, xT(""), NULL);
    if (FALSE == bRes) {
        printf("CreateWaitableTimer failed (%li)\n", GetLastError());
        return 1;
    }
    printf("CreateWaitableTimer success (%li)\n", GetLastError());

    //-------------------------------------
    //Устанавливаем
    WT.bSet(/*-30000000LL*/0, 2000, NULL, NULL, 0);
    if (FALSE == bRes) {
        printf("SetWaitableTimer failed (%li)\n", GetLastError());
        return 2;
    }
    printf("SetWaitableTimer success (%li)\n", GetLastError());


    while (true) {
        //-------------------------------------
        //ждем
        bRes = WT.bWait(INFINITE);
        printf("ulWait success (%li)\n", GetLastError());

        if (FALSE == bRes) {
            printf("ulWait failed (%li)\n", GetLastError());
        } else {
            printf("Timer was signaled.\n");
        }

    }
#elif defined(xOS_ENV_UNIX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
