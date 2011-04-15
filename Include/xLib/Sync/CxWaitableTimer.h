/****************************************************************************
* Class name:  CxWaitableTimer
* Description: ������ � �������� ��������
* File name:   CxWaitableTimer.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     27.05.2009 17:07:46
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Sync_CxWaitableTimerH
#define xLib_Sync_CxWaitableTimerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/Win/CxHandleT.h>
//---------------------------------------------------------------------------
class CxWaitableTimer  : public CxNonCopyable {
	public:
			     CxWaitableTimer();
		virtual ~CxWaitableTimer();

	    HANDLE   hGetHandle     () const;
		BOOL     bCreate        (BOOL bManualReset, LPCTSTR pcszName/* = NULL*/, LPSECURITY_ATTRIBUTES lpTimerAttributes/* = NULL*/);
    	BOOL     bOpen          (LPCTSTR pcszName, ULONG ulDesiredAccess = TIMER_ALL_ACCESS, BOOL bInheritHandle = FALSE);
		BOOL     bCancel        () const;
		BOOL     bSet           (LONGLONG i64DueTime/*milliseconds*/, LONG liPeriod = 0, PTIMERAPCROUTINE pfnCompletionRoutine = NULL, LPVOID pvArgToCompletionRoutine = NULL, BOOL bResume = FALSE) const;
		BOOL     bWait          (ULONG ulTimeout) const;

	private:
		CxHandleT<NULL>         _m_hWaitableTimer;
};
//---------------------------------------------------------------------------
#endif	//xLib_Sync_CxWaitableTimerH
