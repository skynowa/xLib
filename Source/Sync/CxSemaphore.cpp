/****************************************************************************
* Class name:  CxSemaphore
* Description: работа с семафорами
* File name:   CxSemaphore.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     19.05.2009 18:46:41
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Sync/CxSemaphore.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxSemaphore ()
CxSemaphore::CxSemaphore() :
	_m_hSemaphore    (),
	_m_lpsaAttributes(NULL),
	_m_pcszName      (NULL)
{
}
//---------------------------------------------------------------------------
//TODO: + ~CxSemaphore ()
CxSemaphore::~CxSemaphore() {
	/*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: + hGetHandle ()
HANDLE 
CxSemaphore::hGetHandle() const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hSemaphore.bIsValid(), NULL);

	return _m_hSemaphore.m_hHandle;
}
//---------------------------------------------------------------------------
//TODO: + bCreate (Creates or opens a named or unnamed semaphore object)
BOOL 
CxSemaphore::bCreate(LPSECURITY_ATTRIBUTES lpsaAttributes, LONG liInitialCount, LONG liMaxCount, LPCTSTR pcszName) {
	/*DEBUG*/xASSERT_RET(FALSE == _m_hSemaphore.bIsValid(),					  FALSE);
	/*DEBUG*///lpsaAttributes - n/a
	/*DEBUG*/xASSERT_RET(0 <= liInitialCount && liInitialCount <= liMaxCount, FALSE);
	/*DEBUG*/xASSERT_RET(MAX_PATH > ::lstrlen(pcszName),					  FALSE);

	HANDLE hRes = NULL;

	hRes = ::CreateSemaphore(lpsaAttributes, liInitialCount, liMaxCount, pcszName);
	/*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

	_m_hSemaphore.m_hHandle = hRes;
	_m_lpsaAttributes       = lpsaAttributes;
	_m_pcszName             = pcszName;

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bOpen ()
BOOL 
CxSemaphore::bOpen(ULONG ulAccess, BOOL bInheritHandle, LPCTSTR pcszName) {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hSemaphore.bIsValid(), FALSE);
	/*DEBUG*///ulAccess - not need
	/*DEBUG*///pcszName - not need
	
	HANDLE hRes = NULL;

	hRes = ::OpenSemaphore(ulAccess, bInheritHandle, pcszName);
	/*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

	_m_hSemaphore.m_hHandle = hRes;
	
	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bRelease ()
BOOL 
CxSemaphore::bRelease(LONG liReleaseCount, LONG *pliOldCount) const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hSemaphore.bIsValid(), FALSE);
	/*DEBUG*///liReleaseCount - not need
	/*DEBUG*///pliOldCount    - not need

	BOOL bRes = FALSE;
	
	bRes = ::ReleaseSemaphore(_m_hSemaphore.m_hHandle, liReleaseCount, pliOldCount);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bWait ()
BOOL 
CxSemaphore::bWait(ULONG ulTimeout) const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hSemaphore.bIsValid(), FALSE);
	/*DEBUG*///ulTimeout - not need

	ULONG ulRes = WAIT_FAILED;

	ulRes = ::WaitForSingleObject(_m_hSemaphore.m_hHandle, ulTimeout); 
	/*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == ulRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + liGetValue ()
LONG 
CxSemaphore::liGetValue() const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hSemaphore.bIsValid(), - 1);

	LONG liRes = - 1; 
	BOOL bRes  = FALSE;

	bRes = bRelease(0, &liRes);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, - 1);

	return liRes; 
}
//---------------------------------------------------------------------------
//TODO: + bReset ()
BOOL 
CxSemaphore::bReset(LONG liInitialCount, LONG liMaxCount) {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hSemaphore.bIsValid(),                   FALSE);
	/*DEBUG*/xASSERT_RET(0 <= liInitialCount && liInitialCount <= liMaxCount, FALSE);

	BOOL bRes = FALSE;

	/*
	void Reset(int init = 0)	{ 
		sem_destroy(&S); 
		
		sem_init(&S, 0, init); 
	}
	*/


	bRes = _m_hSemaphore.bClose();
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	bRes = bCreate(_m_lpsaAttributes, liInitialCount, liMaxCount, _m_pcszName);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------