/**
 * \file  CxEvent.h
 * \brief event (using between threads)
 */


#include <xLib/Log/CxTrace.h>


#if   xENV_WIN
    #include "Platform/Win/CxEvent_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/CxEvent_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/CxEvent_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/CxEvent_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/CxEvent_apple.inl"
    #endif
#endif

xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxEvent::CxEvent(
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
inline
CxEvent::~CxEvent()
{
    _dectruct_impl();
}
//-------------------------------------------------------------------------------------------------
inline const CxEvent::handle_t &
CxEvent::handle() const
{
    return _handle_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxEvent::create()
{
    _create_impl();
}
//-------------------------------------------------------------------------------------------------
// NOTE: unblock threads blocked on a condition variable
inline void_t
CxEvent::set()
{
    _set_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxEvent::reset()
{
    _reset_impl();
}
//-------------------------------------------------------------------------------------------------
inline CxEvent::ExObjectState
CxEvent::wait(
    culong_t &a_timeoutMs /* = xTIMEOUT_INFINITE */  ///< timeout (msec)
)
{
    xTEST_NA(a_timeoutMs);

    ExObjectState osRv = _wait_impl(a_timeoutMs);

    xTEST_MSG_EQ((osRv == osSignaled) || (osRv == osTimeout), true, CxLastError::format(osRv));

    return osRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxEvent::isSignaled() const
{
    // n/a

    return _isSignaled_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
