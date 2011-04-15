/****************************************************************************
* Class name:  CxMutex
* Description: ������ � ����������
* File name:   CxMutex.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     19.05.2009 18:48:30
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Sync_CxMutexH
#define xLib_Sync_CxMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/Win/CxHandleT.h>
//---------------------------------------------------------------------------
class CxMutex : public CxNonCopyable {
	public:
		         CxMutex   ();
		virtual ~CxMutex   ();

	    HANDLE   hGetHandle() const;
		BOOL     bCreate   (LPSECURITY_ATTRIBUTES lpsaAttributes, BOOL bInitialOwner, LPCTSTR pcszName);
		BOOL     bOpen     (ULONG ulAccess, BOOL bInheritHandle, LPCTSTR pcszName);
		BOOL     bRelease  () const;
		BOOL     bWait     (ULONG ulTimeout) const;

	private:
		CxHandleT<NULL>  _m_hMutex;
};
//---------------------------------------------------------------------------
#endif	//xLib_Sync_CxMutexH
