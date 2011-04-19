/****************************************************************************
* Class name:  CxMutex
* Description: mutex
* File name:   CxMutex.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     19.05.2009 18:48:44
*
*****************************************************************************/



#include <xLib/Sync/CxMutex.h>


/****************************************************************************
*    public                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxMutex ()
CxMutex::CxMutex() :
	_m_hMutex()
{
}
//---------------------------------------------------------------------------
//DONE: ~CxMutex ()
CxMutex::~CxMutex() {
	/*DEBUG*/xASSERT(FALSE != _m_hMutex.bIsValid());
}
//---------------------------------------------------------------------------
//DONE: hGetHandle ()
HANDLE 
CxMutex::hGetHandle() const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hMutex.bIsValid(), NULL);

	return _m_hMutex.m_hHandle;
}
//---------------------------------------------------------------------------
//DONE: bCreate ()
BOOL 
CxMutex::bCreate(LPSECURITY_ATTRIBUTES lpsaAttributes, BOOL bInitialOwner, LPCTSTR pcszName) {
	/*DEBUG*/xASSERT_RET(FALSE == _m_hMutex.bIsValid(), FALSE);
	/*DEBUG*///lpsaAttributes - n/a
	/*DEBUG*///bInitialOwner  - n/a
	/*DEBUG*///pcszName       - n/a

	HANDLE hRes = NULL;

	hRes = ::CreateMutex(lpsaAttributes, bInitialOwner, pcszName);
	/*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

	_m_hMutex.m_hHandle = hRes;

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bOpen ()
BOOL 
CxMutex::bOpen(ULONG dwAccess, BOOL bInheritHandle, LPCTSTR pcszName) {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hMutex.bIsValid(), FALSE);
	/*DEBUG*///dwAccess       - n/a
	/*DEBUG*///bInheritHandle - n/a
	/*DEBUG*///pcszName       - n/a

	HANDLE hRes = NULL;

	hRes = ::OpenMutex(dwAccess, bInheritHandle, pcszName);
	/*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

	_m_hMutex.m_hHandle = hRes;

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bRelease ()
BOOL 
CxMutex::bRelease() const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hMutex.bIsValid(), FALSE);

	BOOL bRes = FALSE;

	bRes = ::ReleaseMutex(_m_hMutex.m_hHandle);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWait ()
BOOL 
CxMutex::bWait(ULONG ulTimeout) const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hMutex.bIsValid(), FALSE);
	/*DEBUG*///ulTimeout - n/a

	ULONG ulRes = WAIT_FAILED;

	ulRes = ::WaitForSingleObject(_m_hMutex.m_hHandle, ulTimeout); 
	/*DEBUG*/xASSERT_RET(WAIT_OBJECT_0  == ulRes, FALSE);
	/*DEBUG*/xASSERT_RET(WAIT_ABANDONED != ulRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------