/**
 * \file  CxWaitableTimer.h
 * \brief waitable timer
 */


#ifndef xLib_Sync_CxWaitableTimerH
#define xLib_Sync_CxWaitableTimerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if xOS_ENV_WIN
    #include <xLib/Common/Win/CxHandleT.h>
#elif xOS_ENV_UNIX

#endif
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxWaitableTimer  :
    public CxNonCopyable
    /// waitable timer
{
    public:
                 CxWaitableTimer();
        virtual ~CxWaitableTimer();

        HANDLE   hGetHandle     () const;
        bool     bCreate        (const bool cbManualReset, const std::tstring &csName/* = NULL*/, const LPSECURITY_ATTRIBUTES pcsaTimerAttributes/* = NULL*/);
        bool     bOpen          (const std::tstring &csName, const ULONG culDesiredAccess = TIMER_ALL_ACCESS, const bool cbInheritHandle = false);
        bool     bCancel        () const;
        bool     bSet           (const LONGLONG cllDueTime/*milliseconds*/, const LONG cliPeriod = 0, PTIMERAPCROUTINE pfnCompletionRoutine = NULL, LPVOID pvArgToCompletionRoutine = NULL, const bool cbResume = false) const;
        bool     bWait          (const ULONG ulTimeout) const;

    private:
        CxHandle _m_hWaitableTimer;
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxWaitableTimerH
