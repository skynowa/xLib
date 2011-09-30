/**
 * \file  CxWaitableTimer.h
 * \brief waitable timer
 */


#ifndef xLib_Sync_CxWaitableTimerH
#define xLib_Sync_CxWaitableTimerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_ENV_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#elif defined(xOS_ENV_UNIX)

#endif
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxWaitableTimer  :
    public CxNonCopyable
    /// waitable timer
{
    public:
                 CxWaitableTimer();
        virtual ~CxWaitableTimer();

        HANDLE   hGetHandle     () const;
        BOOL     bCreate        (const BOOL cbManualReset, const std::tstring &csName/* = NULL*/, const LPSECURITY_ATTRIBUTES pcsaTimerAttributes/* = NULL*/);
        BOOL     bOpen          (const std::tstring &csName, const ULONG culDesiredAccess = TIMER_ALL_ACCESS, const BOOL cbInheritHandle = FALSE);
        BOOL     bCancel        () const;
        BOOL     bSet           (const LONGLONG cllDueTime/*milliseconds*/, const LONG cliPeriod = 0, PTIMERAPCROUTINE pfnCompletionRoutine = NULL, LPVOID pvArgToCompletionRoutine = NULL, const BOOL cbResume = FALSE) const;
        BOOL     bWait          (const ULONG ulTimeout) const;

    private:
        CxHandle _m_hWaitableTimer;
};
#elif defined(xOS_ENV_UNIX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxWaitableTimerH
