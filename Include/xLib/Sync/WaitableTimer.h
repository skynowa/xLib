/**
 * \file  WaitableTimer.h
 * \brief waitable timer
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/HandleT.h>
//-------------------------------------------------------------------------------------------------
#if xENV_WIN

xNAMESPACE_BEGIN2(xlib, sync)

class WaitableTimer
    /// waitable timer
{
public:
             WaitableTimer() {}
    virtual ~WaitableTimer() {}

    HANDLE   handle() const xWARN_UNUSED_RV;
    void_t   create(cbool_t &isManualReset, std::ctstring_t &name/* = xPTR_NULL*/,
                 const LPSECURITY_ATTRIBUTES attrs/* = xPTR_NULL*/);
    void_t   open(std::ctstring_t &name, culong_t &access = TIMER_ALL_ACCESS,
                 cbool_t &isInheritHandle = false);
    void_t   cancel() const;
    void_t   set(clonglong_t &dueTimeMsec, clong_t &period = 0L, PTIMERAPCROUTINE routine = xPTR_NULL,
                 LPVOID routineArgs = xPTR_NULL, cbool_t &isResume = false) const;
    void_t   wait(culong_t &timeoutMsec) const;

private:
    Handle _handle;

    xNO_COPY_ASSIGN(WaitableTimer)

xPLATFORM:

};

xNAMESPACE_END2(xlib, sync)

#endif
//-------------------------------------------------------------------------------------------------
#if xENV_WIN

#if xOPTION_HEADER_ONLY
    #include "WaitableTimer.inl"
#endif

#endif

