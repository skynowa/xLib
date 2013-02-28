/**
 * \file  CxWaitableTimer.h
 * \brief waitable timer
 */


#ifndef xLib_Sync_CxWaitableTimerH
#define xLib_Sync_CxWaitableTimerH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleT.h>
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxWaitableTimer  :
    private CxNonCopyable
    /// waitable timer
{
public:
             CxWaitableTimer();
    virtual ~CxWaitableTimer();

    HANDLE   handle         () const xWARN_UNUSED_RV;
    void     create         (const bool &cbManualReset, const std::tstring_t &csName/* = NULL*/, const LPSECURITY_ATTRIBUTES pcsaTimerAttributes/* = NULL*/);
    void     open           (const std::tstring_t &csName, const ulong_t &culDesiredAccess = TIMER_ALL_ACCESS, const bool &cbInheritHandle = false);
    void     cancel         () const;
    void     set            (const longlong_t &cllDueTime/*milliseconds*/, const long_t &cliPeriod = 0L, PTIMERAPCROUTINE pfnCompletionRoutine = NULL, LPVOID pvArgToCompletionRoutine = NULL, const bool &cbResume = false) const;
    void     wait           (const ulong_t &ulTimeout) const;

private:
    CxHandle _m_hHandle;
};

xNAMESPACE_END(NxLib)

#endif
//------------------------------------------------------------------------------
#endif // xLib_Sync_CxWaitableTimerH
