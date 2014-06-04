/**
 * \file  CxProcess.inl
 * \brief process
 */


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxProcess::_destruct_impl()
{
    xNA;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxProcess::_create_impl(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_params
)
{
    pid_t pid = ::fork();
    xTEST_EQ(pid != - 1L, true);

    if (pid == 0L) {
        // TODO: CxProcess::_create_impl() - a_filePath is executable

        int_t iRv = ::execlp(a_filePath.c_str(), a_filePath.c_str(), a_params.c_str(),
            static_cast<ctchar_t *>( xPTR_NULL ));
        xTEST_DIFF(iRv, - 1);

        (void_t)::_exit(EXIT_SUCCESS);  /* not exit() */
    }

    _handle = pid;
    _pid    = pid;
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::ExWaitResult
CxProcess::_wait_impl(
    culong_t &a_timeoutMsec
)
{
    ExWaitResult waitStatus = wrFailed;

    xUNUSED(a_timeoutMsec);

    // TODO: CxProcess::_wait_impl() - a_timeoutMsec
    pid_t liRv   = - 1L;
    int_t status = 0;

    do {
        liRv = ::waitpid(_pid, &status, 0);
    }
    while (liRv < 0L && CxLastError::get() == EINTR);
    xTEST_EQ(liRv, _pid);

    _exitStatus = WEXITSTATUS(status);
    waitStatus  = static_cast<ExWaitResult>( WEXITSTATUS(status) );

    return waitStatus;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxProcess::_kill_impl(
    culong_t &a_timeoutMsec
)
{
    int_t iRv = ::kill(_pid, SIGKILL);
    xTEST_DIFF(iRv, - 1);

    CxThread::currentSleep(a_timeoutMsec);

    _exitStatus = 0U;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcess::_exitStatus_impl() const
{
    ulong_t ulRv = _exitStatus;

    return ulRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxProcess::id_t
CxProcess::_idByHandle_impl(
    const handle_t &a_handle    ///< handle
)
{
    id_t ulRv = static_cast<id_t>( a_handle );

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::handle_t
CxProcess::_handleById_impl(
    const id_t &a_id   ///< ID
)
{
    handle_t hRv = static_cast<handle_t>( a_id );

    return hRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxProcess::_isCurrent_impl(
    const CxProcess::id_t &a_id
)
{
    bool_t bRv = ::pthread_equal(currentId(), a_id);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::id_t
CxProcess::_currentId_impl()
{
    id_t ulRv = ::getpid();
    // n/a

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::id_t
CxProcess::_currentParentId_impl()
{
    id_t ulRv = ::getppid();
    xTEST_NA(ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::handle_t
CxProcess::_currentHandle_impl()
{
    handle_t hRv = ::getpid();
    // n/a

    return hRv;
}
//-------------------------------------------------------------------------------------------------
// TODO: tests
inline void_t
CxProcess::_currentExit_impl(
    cuint_t &a_exitCode
)
{
    (void_t)::exit(static_cast<int_t>( a_exitCode ));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
