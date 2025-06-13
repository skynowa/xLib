/**
 * \file  Event.h
 * \brief event (using between threads)
 */


#include "Event.h"

#include <xLib/Log/LogStream.h>

#if   xENV_WIN
    #include "Platform/Win/Event_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Event_unix.inl"
#endif

namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Event::Event(
    cbool_t a_isAutoReset,    ///< is auto reset
    cbool_t a_isSignaled      ///< is signaled (false - wait, lock)
) :
#if   xENV_WIN
    // n/a
#elif xENV_UNIX
    _isSignaled (a_isSignaled),
#endif
    _isAutoReset(a_isAutoReset),
    _initState  (a_isSignaled)
{
}
//-------------------------------------------------------------------------------------------------
Event::~Event()
{
    _dectruct_impl();
}
//-------------------------------------------------------------------------------------------------
const Event::handle_t &
Event::handle() const
{
    return _handle_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Event::create()
{
    _create_impl();
}
//-------------------------------------------------------------------------------------------------
// NOTE: unblock threads blocked on a condition variable
void_t
Event::set()
{
    _set_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Event::reset()
{
    _reset_impl();
}
//-------------------------------------------------------------------------------------------------
Event::ObjectState
Event::wait(
    culong_t &a_timeoutMs /* = xTIMEOUT_INFINITE */  ///< timeout (msec)
)
{
    xTEST_NA(a_timeoutMs);

    ObjectState osRv = _wait_impl(a_timeoutMs);

    xTEST_EQ_MSG((osRv == ObjectState::osSignaled) || (osRv == ObjectState::osTimeout), true,
    	NativeError::format( static_cast<ulong_t>(osRv) ));

    return osRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Event::isSignaled() const
{
    // n/a

    return _isSignaled_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
