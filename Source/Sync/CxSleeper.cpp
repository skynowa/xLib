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
    const ulong_t culTimeout  ///< in milliseconds
)
{
    /*DEBUG*/// n/a

    CxEvent::EObjectState osRes = _m_objEvent.osWait(culTimeout);
    /*DEBUG*/xASSERT_RET(CxEvent::osSignaled == osRes || CxEvent::osTimeout == osRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxSleeper::bWakeUp() {
    /*DEBUG*/// n/a

    bool bRes = _m_objEvent.bSet();
    /*DEBUG*/xASSERT_RET(false != bRes, false);

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
