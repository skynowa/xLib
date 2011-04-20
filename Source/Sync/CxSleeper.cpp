/****************************************************************************
* Class name:  CxSleeper
* Description: like ::Sleep()
* File name:   CxSleeper.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.07.2009 12:54:38
*
*****************************************************************************/


#include <xLib/Sync/CxSleeper.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxSleeper (конструктор)
CxSleeper::CxSleeper() :
    _m_objEvent()
{
    BOOL bRes = FALSE;

    bRes = _m_objEvent.bCreate(NULL, FALSE, FALSE, NULL);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
//DONE: ~CxSleeper (деструктор)
CxSleeper::~CxSleeper() {

}
//---------------------------------------------------------------------------
//DONE: bSleep (засыпание)
BOOL
CxSleeper::bSleep(ULONG ulTimeout) const {
    /*DEBUG*/// n/a

    ULONG ulRes = 0;

    ulRes = ::WaitForSingleObject(_m_objEvent.hGetHandle(), ulTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_FAILED != ulRes || WAIT_OBJECT_0 == ulRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWakeUp (сброс засыпания)
BOOL
CxSleeper::bWakeUp() const {
    /*DEBUG*/// n/a

    BOOL bRes = FALSE;

    bRes = _m_objEvent.bSet();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bIsSleeping (спим ли)
BOOL
CxSleeper::bIsSleeping() const {
    /*DEBUG*/// n/a

    return _m_objEvent.bIsSignaled();
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
