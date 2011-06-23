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
#include <xLib/Common/Win/CxHandleT.h>
//---------------------------------------------------------------------------
class CxWaitableTimer  :
    public CxNonCopyable
{
    public:
                 CxWaitableTimer();
        virtual ~CxWaitableTimer();

        HANDLE   hGetHandle     () const;
        BOOL     bCreate        (const BOOL cbManualReset, const tString &csName/* = NULL*/, const LPSECURITY_ATTRIBUTES pcsaTimerAttributes/* = NULL*/);
        BOOL     bOpen          (const tString &csName, const ULONG culDesiredAccess = TIMER_ALL_ACCESS, const BOOL cbInheritHandle = FALSE);
        BOOL     bCancel        () const;
        BOOL     bSet           (const LONGLONG cllDueTime/*milliseconds*/, const LONG cliPeriod = 0, PTIMERAPCROUTINE pfnCompletionRoutine = NULL, LPVOID pvArgToCompletionRoutine = NULL, const BOOL cbResume = FALSE) const;
        BOOL     bWait          (const ULONG ulTimeout) const;

    private:
        CxHandle _m_hWaitableTimer;
};
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxWaitableTimerH
