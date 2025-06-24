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
ThreadCurrent::currentId()
{
    // n/a

    return _currentId_impl();
}
//-------------------------------------------------------------------------------------------------
Thread::handle_t
ThreadCurrent::currentHandle()
{
    // n/a

    return _currentHandle_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
ThreadCurrent::currentYield()
{
    // n/a

    _currentYield_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
ThreadCurrent::currentSleep(
    culong_t a_timeoutMsec
)
{
    // n/a

    xCHECK_DO(a_timeoutMsec == 0UL, return);

    _currentSleep_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------

} // namespace
