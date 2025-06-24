/**
 * \file  ThreadCurrent.cpp
 * \brief Current thread
 */


#include "ThreadCurrent.h"

#if   xENV_WIN
    #include "Platform/Win/ThreadCurrent_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/ThreadCurrent_unix.inl"
#endif

namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
ThreadCurrent::isCurrent(
	Thread::cid_t a_id
)
{
    return _isCurrent_impl(a_id);
}
//-------------------------------------------------------------------------------------------------
Thread::id_t
ThreadCurrent::id()
{
    // n/a

    return _id_impl();
}
//-------------------------------------------------------------------------------------------------
Thread::handle_t
ThreadCurrent::handle()
{
    // n/a

    return _handle_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
ThreadCurrent::yield()
{
    // n/a

	_yield_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
ThreadCurrent::sleep(
    culong_t a_timeoutMsec
)
{
    // n/a

    xCHECK_DO(a_timeoutMsec == 0UL, return);

    _sleep_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------

} // namespace
