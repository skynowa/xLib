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
//DONE: CxTest_CxWaitableTimer (constructor)
CxTest_CxWaitableTimer::CxTest_CxWaitableTimer() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxWaitableTimer (destructor)
CxTest_CxWaitableTimer::~CxTest_CxWaitableTimer() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxWaitableTimer::bUnit() {
#if defined(xOS_WIN)
    BOOL bRes = FALSE;

    CxWaitableTimer WT;

    //-------------------------------------
    //создаем
    bRes = WT.bCreate(FALSE, NULL, xT(""));
    if (FALSE == bRes) {
        printf("CreateWaitableTimer failed (%d)\n", GetLastError());
        return 1;
    }
    printf("CreateWaitableTimer success (%d)\n", GetLastError());

    //-------------------------------------
    //Устанавливаем
    WT.bSet(/*-30000000LL*/0, 2000, NULL, NULL, 0);
    if (FALSE == bRes) {
        printf("SetWaitableTimer failed (%d)\n", GetLastError());
        return 2;
    }
    printf("SetWaitableTimer success (%d)\n", GetLastError());


    while (true) {
        //-------------------------------------
        //ждем
        BOOL bRes = WT.bWait(INFINITE);
        printf("ulWait success (%d)\n", GetLastError());

        if (FALSE == bRes) {
            printf("ulWait failed (%d)\n", GetLastError());
        } else {
            printf("Timer was signaled.\n");
        }

    }
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
