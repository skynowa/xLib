/**
 * \file  CxWaitableTimer.h
 * \brief waitable timer
 */


#pragma once

#ifndef xLib_CxWaitableTimerH
#define xLib_CxWaitableTimerH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Core/CxHandleT.h>
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE2_BEGIN(xlib, sync)

class CxWaitableTimer
    /// waitable timer
{
public:
             CxWaitableTimer() {}
    virtual ~CxWaitableTimer() {}

    HANDLE   handle() const xWARN_UNUSED_RV;
    void_t   create(cbool_t &isManualReset, std::ctstring_t &name/* = NULL*/,
                 const LPSECURITY_ATTRIBUTES attrs/* = NULL*/);
    void_t   open(std::ctstring_t &name, culong_t &access = TIMER_ALL_ACCESS,
                 cbool_t &isInheritHandle = false);
    void_t   cancel() const;
    void_t   set(clonglong_t &dueTimeMsec, clong_t &period = 0L, PTIMERAPCROUTINE routine = NULL,
                 LPVOID routineArgs = NULL, cbool_t &isResume = false) const;
    void_t   wait(culong_t &timeoutMsec) const;

private:
    CxHandle _handle;

    xNO_COPY_ASSIGN(CxWaitableTimer)
};

xNAMESPACE2_END(xlib, sync)

#endif
//-------------------------------------------------------------------------------------------------
#include "CxWaitableTimer.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxWaitableTimerH
