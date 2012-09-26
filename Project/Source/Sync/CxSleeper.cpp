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

}
//---------------------------------------------------------------------------
/*virtual*/
CxSleeper::~CxSleeper() {

}
//---------------------------------------------------------------------------
bool
CxSleeper::bSleep(
    const ulong_t &a_culTimeout  ///< in milliseconds
)
{
    /*DEBUG*/// n/a

    CxEvent::ExObjectState osRes = _m_objEvent.osWait(a_culTimeout);
    /*DEBUG*/xASSERT_RET(CxEvent::osSignaled == osRes || CxEvent::osTimeout == osRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxSleeper::bWakeUp() {
    /*DEBUG*/// n/a

    bool bRv = _m_objEvent.bSet();
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxSleeper::bIsSleeping() {
    /*DEBUG*/// n/a

    return _m_objEvent.bIsSignaled();
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
