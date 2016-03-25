/**
 * \file   Test_WaitableTimer.cpp
 * \brief
 */


#include "Test_WaitableTimer.h"

//-------------------------------------------------------------------------------------------------
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
    WT.create(false, xT(""), xPTR_NULL);

    //-------------------------------------
    //Устанавливаем
    WT.set(/*-30000000LL*/0, 2000, xPTR_NULL, xPTR_NULL, 0);

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
