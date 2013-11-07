/**
 * \file  CxSleeper.cpp
 * \brief sleeper
 */


#include <xLib/Sync/CxSleeper.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE_HO
CxSleeper::CxSleeper() :
    _event(false, false)
{
    _event.create();
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxSleeper::sleep(
    culong_t &a_culTimeout  ///< in milliseconds
)
{
    // n/a

    CxEvent::ExObjectState osRv = _event.wait(a_culTimeout);
    xTEST_EQ(true, CxEvent::osSignaled == osRv || CxEvent::osTimeout == osRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxSleeper::wakeUp() {
    // n/a

    _event.set();
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO bool_t
CxSleeper::isSleeping() {
    // n/a

    return _event.isSignaled();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
