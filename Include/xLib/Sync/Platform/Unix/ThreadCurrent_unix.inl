/**
 * \file  ThreadCurrent.inl
 * \brief thread
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
    bool_t bRv = ::pthread_equal(currentId(), a_id);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
Thread::id_t
ThreadCurrent::_currentId_impl()
{
    id_t ulRv = ::pthread_self();
    //-- xTEST(isIdValid(ulRv));

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
Thread::handle_t
ThreadCurrent::_currentHandle_impl()
{
	Thread::handle_t hRv = ::pthread_self();
    //-- xTEST(isHandleValid(hRv));

    return hRv;
}
//-------------------------------------------------------------------------------------------------
void_t
ThreadCurrent::_currentYield_impl()
{
    int_t iRv = ::sched_yield();
    xTEST_DIFF_MSG(iRv, - 1, NativeError::format( static_cast<ulong_t>(iRv) ));
}
//-------------------------------------------------------------------------------------------------
void_t
ThreadCurrent::_currentSleep_impl(
    culong_t a_timeoutMsec
)
{
    timespec timeSleep  {};
    timespec timeRemain {};

    timeSleep.tv_sec  = a_timeoutMsec / 1000;
    timeSleep.tv_nsec = (a_timeoutMsec % 1000) * (1000 * 1000);

    for ( ; ; ) {
        int_t iRv = ::nanosleep(&timeSleep, &timeRemain);
        xTEST_NA(iRv);
        xCHECK_DO(!(- 1 == iRv && EINTR == NativeError::get()), break);

        timeSleep = timeRemain;
    }
}
//-------------------------------------------------------------------------------------------------

} // namespace
