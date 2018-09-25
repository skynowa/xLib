/**
 * \file  WaitableTimer.h
 * \brief waitable timer
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
#if xENV_WIN

xNAMESPACE_BEGIN2(xl, sync)

class WaitableTimer
    /// waitable timer
{
public:
             WaitableTimer() {}
    virtual ~WaitableTimer() {}

    HANDLE   handle() const xWARN_UNUSED_RV;
    void_t   create(cbool_t &isManualReset, std::ctstring_t &name/* = nullptr*/,
                 const LPSECURITY_ATTRIBUTES attrs/* = nullptr*/);
    void_t   open(std::ctstring_t &name, culong_t &access = TIMER_ALL_ACCESS,
                 cbool_t &isInheritHandle = false);
    void_t   cancel() const;
    void_t   set(clonglong_t &dueTimeMsec, clong_t &period = 0L, PTIMERAPCROUTINE routine = nullptr,
                 LPVOID routineArgs = nullptr, cbool_t &isResume = false) const;
    void_t   wait(culong_t &timeoutMsec) const;

private:
    Handle _handle;

    xNO_COPY_ASSIGN(WaitableTimer)

xPLATFORM_IMPL:

};

xNAMESPACE_END2(xl, sync)

#endif
//-------------------------------------------------------------------------------------------------
