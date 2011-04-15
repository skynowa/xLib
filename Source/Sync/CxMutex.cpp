/****************************************************************************
* Class name:  CxMutex
* Description: работа с мьютексами
* File name:   CxMutex.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     19.05.2009 18:48:44
* Version:     1.0.0.0 Debug
*
*****************************************************************************/



#include <xLib/Sync/CxMutex.h>


/****************************************************************************
*    public                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxMutex ()
CxMutex::CxMutex() :
	_m_hMutex()
{
}
//---------------------------------------------------------------------------
//TODO: + ~CxMutex ()
CxMutex::~CxMutex() {
	/*DEBUG*/xASSERT(FALSE != _m_hMutex.bIsValid());
}
//---------------------------------------------------------------------------
//TODO: + hGetHandle ()
HANDLE 
CxMutex::hGetHandle() const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hMutex.bIsValid(), NULL);

	return _m_hMutex.m_hHandle;
}
//---------------------------------------------------------------------------
//TODO: + bCreate ()
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
//TODO: + bOpen ()
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
//TODO: + bRelease ()
BOOL 
CxMutex::bRelease() const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hMutex.bIsValid(), FALSE);

	BOOL bRes = FALSE;

	bRes = ::ReleaseMutex(_m_hMutex.m_hHandle);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bWait ()
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