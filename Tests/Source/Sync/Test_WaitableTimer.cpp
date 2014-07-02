/**
 * \file   Test_WaitableTimer.cpp
 * \brief
 */


#include <Test/Sync/Test_WaitableTimer.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_WaitableTimer::unit(
    culonglong_t &a_caseLoops
)
{
    xUNUSED(a_caseLoops);

#if   xENV_WIN
    WaitableTimer WT;

    //-------------------------------------
    //создаем
    WT.create(false, xT(""), NULL);

    //-------------------------------------
    //Устанавливаем
    WT.set(/*-30000000LL*/0, 2000, NULL, NULL, 0);

    while (true) {
        //-------------------------------------
        //ждем
        WT.wait(INFINITE);
    }
#elif xENV_UNIX

#endif
}
//-------------------------------------------------------------------------------------------------
