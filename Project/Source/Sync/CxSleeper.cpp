/**
 * \file  CxSleeper.cpp
 * \brief sleeper
 */


#include <xLib/Sync/CxSleeper.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxSleeper::CxSleeper() :
    _m_objEvent(false, false)
{
    _m_objEvent.vCreate();
}
//---------------------------------------------------------------------------
/* virtual */
CxSleeper::~CxSleeper() {

}
//---------------------------------------------------------------------------
void
CxSleeper::vSleep(
    const ulong_t &a_culTimeout  ///< in milliseconds
)
{
    // n/a

    CxEvent::ExObjectState osRes = _m_objEvent.osWait(a_culTimeout);
    xTEST_EQ(true, CxEvent::osSignaled == osRes || CxEvent::osTimeout == osRes);
}
//---------------------------------------------------------------------------
void
CxSleeper::vWakeUp() {
    // n/a

    _m_objEvent.vSet();
}
//---------------------------------------------------------------------------
bool
CxSleeper::bIsSleeping() {
    // n/a

    return _m_objEvent.bIsSignaled();
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
