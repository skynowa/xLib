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
void
CxTest_CxWaitableTimer::unit(
    const ulonglong_t &cullCaseLoops
)
{
#if   xOS_ENV_WIN
    CxWaitableTimer WT;

    //-------------------------------------
    //создаем
    WT.create(false, xT(""), NULL);

    //-------------------------------------
    //Устанавливаем
    WT.vSet(/*-30000000LL*/0, 2000, NULL, NULL, 0);

    while (true) {
        //-------------------------------------
        //ждем
        WT.vWait(INFINITE);
    }
#elif xOS_ENV_UNIX

#endif
}
//---------------------------------------------------------------------------
