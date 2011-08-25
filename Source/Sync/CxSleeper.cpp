/**
 * \file  CxSleeper.cpp
 * \brief like ::Sleep()
 */


#include <xLib/Sync/CxSleeper.h>


#if defined(xOS_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxSleeper
CxSleeper::CxSleeper() :
    _m_objEvent()
{
    BOOL bRes = FALSE;

    bRes = _m_objEvent.bCreate(NULL, FALSE, FALSE, xT(""));
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
//DONE: ~CxSleeper
CxSleeper::~CxSleeper() {

}
//---------------------------------------------------------------------------
//DONE: bSleep (sleep)
BOOL
CxSleeper::bSleep(
    const ULONG culTimeout
) const
{
    /*DEBUG*/// n/a

    ULONG ulRes = 0;

    ulRes = ::WaitForSingleObject(_m_objEvent.hGetHandle(), culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_FAILED != ulRes || WAIT_OBJECT_0 == ulRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWakeUp (wakeup)
BOOL
CxSleeper::bWakeUp() const {
    /*DEBUG*/// n/a

    BOOL bRes = FALSE;

    bRes = _m_objEvent.bSet();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bIsSleeping (check for sleeping)
BOOL
CxSleeper::bIsSleeping() const {
    /*DEBUG*/// n/a

    return _m_objEvent.bIsSignaled();
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
#elif defined(xOS_LINUX)

#endif
