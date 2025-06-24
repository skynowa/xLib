/**
 * \file  ThreadCurrent_win.inl
 * \brief Current thread
 */


namespace xl::sync
{


/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
ThreadCurrent::_isCurrent_impl(
	Thread::cid_t &a_id
)
{
	bool_t bRv = (currentId() == a_id);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
Thread::id_t
ThreadCurrent::_currentId_impl()
{
    id_t ulRv = ::GetCurrentThreadId();
    xTEST_LESS(0UL, ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
Thread::handle_t
ThreadCurrent::_currentHandle_impl()
{
	Thread::handle_t hRv = ::GetCurrentThread();
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
void_t
ThreadCurrent::_currentYield_impl()
{
    (void_t)::SwitchToThread();
}
//-------------------------------------------------------------------------------------------------
void_t
ThreadCurrent::_currentSleep_impl(
    culong_t a_timeoutMsec
)
{
    (void_t)::Sleep(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------

} // namespace
