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
CxSleeper::CxSleeper() :
    _m_objEvent(false, false)
{
    _m_objEvent.create();
}
//------------------------------------------------------------------------------
/* virtual */
CxSleeper::~CxSleeper() {

}
//------------------------------------------------------------------------------
void
CxSleeper::sleep(
    const ulong_t &a_culTimeout  ///< in milliseconds
)
{
    // n/a

    CxEvent::ExObjectState osRes = _m_objEvent.wait(a_culTimeout);
    xTEST_EQ(true, CxEvent::osSignaled == osRes || CxEvent::osTimeout == osRes);
}
//------------------------------------------------------------------------------
void
CxSleeper::wakeUp() {
    // n/a

    _m_objEvent.set();
}
//------------------------------------------------------------------------------
bool
CxSleeper::isSleeping() {
    // n/a

    return _m_objEvent.isSignaled();
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
