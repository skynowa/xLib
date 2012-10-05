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
#if   xOS_ENV_WIN
    CxWaitableTimer WT;

    //-------------------------------------
    //создаем
    WT.vCreate(false, xT(""), NULL);

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

    return true;
}
//---------------------------------------------------------------------------
