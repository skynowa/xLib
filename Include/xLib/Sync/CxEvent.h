/****************************************************************************
* Class name:  CxEvent
* Description: ������
* File name:   CxEvent.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     19.05.2009 17:53:15
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Sync_CxEventH
#define xLib_Sync_CxEventH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/Win/CxHandleT.h>
//---------------------------------------------------------------------------
class CxEvent : public CxNonCopyable {
	public:
                 CxEvent    ();
		virtual ~CxEvent    ();

        HANDLE   hGetHandle () const ;
		BOOL     bCreate    (PSECURITY_ATTRIBUTES lpsaAttributes, BOOL bManualReset, BOOL bInitialState, LPCTSTR pcszName);
		BOOL     bOpen      (ULONG ulAccess, BOOL bInheritHandle, LPCTSTR lpcszName);
		BOOL     bPulse     () const;
		BOOL     bReset     () const;
		BOOL     bSet       () const;
		BOOL     bWait      (ULONG ulTimeout) const;

		BOOL     bIsSignaled() const;
		//BOOL   bIsExists  () const;

	private:
		CxHandleT<NULL_HANDLE_VALUE> _m_hEvent;
};
//---------------------------------------------------------------------------
#endif	//xLib_Sync_CxEventH
