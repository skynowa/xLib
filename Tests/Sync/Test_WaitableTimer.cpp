/**
 * \file   Test_WaitableTimer.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_WaitableTimer)
xTEST_UNIT(Test_WaitableTimer)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_WaitableTimer::unit()
{
#if   xENV_WIN
    WaitableTimer WT;

    //-------------------------------------
    //создаем
    WT.create(false, xT(""), nullptr);

    //-------------------------------------
    //Устанавливаем
    WT.set(/*-30000000LL*/0, 2000, nullptr, nullptr, 0);

    while (true) {
        //-------------------------------------
        //ждем
        WT.wait(INFINITE);
    }
#elif xENV_UNIX

#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
