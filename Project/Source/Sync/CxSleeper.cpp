/**
 * \file  CxSleeper.cpp
 * \brief sleeper
 */


#include <xLib/Sync/CxSleeper.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxSleeper::CxSleeper() :
    _m_objEvent(false, false)
{
    _m_objEvent.create();
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxSleeper::sleep(
    culong_t &a_culTimeout  ///< in milliseconds
)
{
    // n/a

    CxEvent::ExObjectState osRes = _m_objEvent.wait(a_culTimeout);
    xTEST_EQ(true, CxEvent::osSignaled == osRes || CxEvent::osTimeout == osRes);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxSleeper::wakeUp() {
    // n/a

    _m_objEvent.set();
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxSleeper::isSleeping() {
    // n/a

    return _m_objEvent.isSignaled();
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
