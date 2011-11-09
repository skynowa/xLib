/**
 * \file  CxSleeper.cpp
 * \brief like ::Sleep()
 */


#include <xLib/Sync/CxSleeper.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxSleeper::CxSleeper() :
    _m_objEvent(FALSE, FALSE)
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxSleeper::~CxSleeper() {

}
//---------------------------------------------------------------------------
BOOL
CxSleeper::bSleep(
    const ULONG culTimeout  ///< in milliseconds
)
{
    /*DEBUG*/// n/a

    CxEvent::EObjectState osRes = _m_objEvent.osWait(culTimeout);
    /*DEBUG*/xASSERT_RET(CxEvent::osSignaled == osRes || CxEvent::osTimeout == osRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxSleeper::bWakeUp() {
    /*DEBUG*/// n/a

    BOOL bRes = _m_objEvent.bSet();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxSleeper::bIsSleeping() {
    /*DEBUG*/// n/a

    return _m_objEvent.bIsSignaled();
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
