/**
 * \file   Condition.inl
 * \brief  condition variable
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/LastError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Log/Trace.h>

#if   xENV_WIN
    #include "Platform/Win/Condition_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Condition_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/Condition_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/Condition_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/Condition_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
Condition::Condition()
#if !xENV_WIN
    :
    _mutex (),
    _handle()
#endif
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
Condition::~Condition()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
Condition::create()
{
    _create_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
Condition::wait(
    culong_t &a_timeoutMs
)
{
    _wait_impl(a_timeoutMs);
}
//-------------------------------------------------------------------------------------------------
inline void_t
Condition::signal()
{
    _signal_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
Condition::broadcast()
{
    _broadcast_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
