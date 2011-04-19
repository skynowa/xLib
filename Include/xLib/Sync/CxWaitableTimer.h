/****************************************************************************
* Class name:  CxWaitableTimer
* Description: waitable timer
* File name:   CxWaitableTimer.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     27.05.2009 17:07:46
*
*****************************************************************************/


#ifndef xLib_Sync_CxWaitableTimerH
#define xLib_Sync_CxWaitableTimerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/Win/CxHandle.h>
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
		CxHandle _m_hWaitableTimer;
};
//---------------------------------------------------------------------------
#endif	//xLib_Sync_CxWaitableTimerH
