/**
 * \file   CxTest_CxWaitableTimer.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxWaitableTimer.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxWaitableTimer::unit(
    culonglong_t &a_caseLoops
)
{
    xUNUSED(a_caseLoops);

#if   xENV_WIN
    CxWaitableTimer WT;

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
