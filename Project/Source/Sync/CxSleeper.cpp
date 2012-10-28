/**
 * \file  CxSleeper.cpp
 * \brief like ::Sleep()
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
    /*DEBUG*/// n/a

    CxEvent::ExObjectState osRes = _m_objEvent.osWait(a_culTimeout);
    /*DEBUG*/xTEST_EQ(true, CxEvent::osSignaled == osRes || CxEvent::osTimeout == osRes);
}
//---------------------------------------------------------------------------
void
CxSleeper::vWakeUp() {
    /*DEBUG*/// n/a

    _m_objEvent.vSet();
}
//---------------------------------------------------------------------------
bool
CxSleeper::bIsSleeping() {
    /*DEBUG*/// n/a

    return _m_objEvent.bIsSignaled();
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
