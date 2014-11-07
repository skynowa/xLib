/**
 * \file  Event.h
 * \brief event (using between threads)
 */


#if !xOPTION_HEADER_ONLY
    #include "Event.h"
#endif

#include <xLib/Log/Trace.h>

#if   xENV_WIN
    #include "Platform/Win/Event_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Event_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/Event_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/Event_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/Event_apple.inl"
    #endif
#endif

xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Event::Event(
    cbool_t &a_isAutoReset,    ///< is auto reset
    cbool_t &a_isSignaled      ///< is signaled (false - wait, lock)
) :
#if   xENV_WIN
    _event      (),
#elif xENV_UNIX
    _mutex      (),
    _cond       (),
    _isSignaled (a_isSignaled),
#endif
    _isAutoReset(a_isAutoReset),
    _initState  (a_isSignaled)
{
}
//-------------------------------------------------------------------------------------------------
xINLINE
Event::~Event()
{
    _dectruct_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE const Event::handle_t &
Event::handle() const
{
    return _handle_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Event::create()
{
    _create_impl();
}
//-------------------------------------------------------------------------------------------------
// NOTE: unblock threads blocked on a condition variable
xINLINE void_t
Event::set()
{
    _set_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Event::reset()
{
    _reset_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE Event::ExObjectState
Event::wait(
    culong_t &a_timeoutMs /* = xTIMEOUT_INFINITE */  ///< timeout (msec)
)
{
    xTEST_NA(a_timeoutMs);

    ExObjectState osRv = _wait_impl(a_timeoutMs);

    xTEST_MSG_EQ((osRv == osSignaled) || (osRv == osTimeout), true, NativeError::format(osRv));

    return osRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Event::isSignaled() const
{
    // n/a

    return _isSignaled_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
