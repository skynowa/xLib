/****************************************************************************
* Class name:  CxMutexScopeLock
* Description: мъютекс в блоке
* File name:   CxAutoMutex.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     16.12.2009 10:06:46
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Sync/CxAutoMutex.h>


/****************************************************************************
*    public                                                           
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxAutoMutex ()
CxAutoMutex::CxAutoMutex(CxMutex &mtMutex) : 
	_m_mtMutex(mtMutex) 
{
	BOOL bRes = FALSE;

	bRes = _m_mtMutex.bWait(INFINITE);
	/*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
//TODO: - ~CxAutoMutex ()
CxAutoMutex::~CxAutoMutex() {
	BOOL bRes = FALSE;

	bRes = _m_mtMutex.bRelease();
	/*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------