/**
 * \file  CxWaitableTimer.h
 * \brief waitable timer
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxHandleT.h>
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

    HANDLE   handle() const xWARN_UNUSED_RV;
    void_t   create(cbool_t &cbManualReset, std::ctstring_t &csName/* = NULL*/,
                 const LPSECURITY_ATTRIBUTES pcsaTimerAttributes/* = NULL*/);
    void_t   open(std::ctstring_t &csName, culong_t &culDesiredAccess = TIMER_ALL_ACCESS,
                 cbool_t &cbInheritHandle = false);
    void_t   cancel() const;
    void_t   set(clonglong_t &cllDueTime/*milliseconds*/, clong_t &cliPeriod = 0L,
                 PTIMERAPCROUTINE pfnCompletionRoutine = NULL,
                 LPVOID pvArgToCompletionRoutine = NULL, cbool_t &cbResume = false) const;
    void_t   wait(culong_t &ulTimeout) const;

private:
    CxHandle _handle;
};

xNAMESPACE_END(NxLib)

#endif
//------------------------------------------------------------------------------
