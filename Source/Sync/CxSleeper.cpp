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
    _m_objEvent()	// _m_objEvent.bCreate(/*NULL, FALSE, FALSE, xT("")*/);
{

}
//---------------------------------------------------------------------------
CxSleeper::~CxSleeper() {

}
//---------------------------------------------------------------------------
BOOL
CxSleeper::bSleep(
    const ULONG culTimeout
)
{
    /*DEBUG*/// n/a

#if defined(xOS_WIN)
    ULONG ulRes = ::WaitForSingleObject(_m_objEvent.hGet(), culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_FAILED != ulRes || WAIT_OBJECT_0 == ulRes, FALSE);
#elif defined(xOS_LINUX)
	BOOL bRes = _m_objEvent.bWait(culTimeout);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#endif

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
CxSleeper::bIsSleeping() const {
    /*DEBUG*/// n/a

    return _m_objEvent.bIsSignaled();
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
