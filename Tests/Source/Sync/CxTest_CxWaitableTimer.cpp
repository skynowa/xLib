/****************************************************************************
* Class name:  CxTest_CxWaitableTimer
* Description: test CxWaitableTimer
* File name:   CxTest_CxWaitableTimer.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Sync/CxTest_CxWaitableTimer.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxWaitableTimer
CxTest_CxWaitableTimer::CxTest_CxWaitableTimer() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxWaitableTimer
CxTest_CxWaitableTimer::~CxTest_CxWaitableTimer() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxWaitableTimer::bUnit(
    const ULONGLONG cullBlockLoops
)
{
#if defined(xOS_WIN)
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
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
