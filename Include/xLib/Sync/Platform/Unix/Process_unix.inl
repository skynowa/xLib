/**
 * \file  Process.inl
 * \brief process
 */


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
Process::_destruct_impl()
{
    xNA;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Process::_create_impl(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_params
)
{
    pid_t pid = ::fork();
    xTEST_EQ(pid != - 1L, true);

    if (pid == 0L) {
        // TODO: Process::_create_impl() - a_filePath is executable

        int_t iRv = ::execlp(xT2A(a_filePath).c_str(), xT2A(a_filePath).c_str(),
            xT2A(a_params).c_str(), static_cast<const char *>( xPTR_NULL ));
        xTEST_DIFF(iRv, - 1);

        (void_t)::_exit(EXIT_SUCCESS);  /* not std::exit() */
    }

    _handle = pid;
    _pid    = pid;
}
//-------------------------------------------------------------------------------------------------
xINLINE Process::ExWaitResult
Process::_wait_impl(
    culong_t &a_timeoutMsec
)
{
    ExWaitResult waitStatus = wrFailed;

    xUNUSED(a_timeoutMsec);

    // TODO: Process::_wait_impl() - a_timeoutMsec
    pid_t liRv   = - 1L;
    int_t status = 0;

    do {
        liRv = ::waitpid(_pid, &status, 0);
    }
    while (liRv < 0L && NativeError::get() == EINTR);
    xTEST_EQ(liRv, _pid);

    _exitStatus = WEXITSTATUS(status);
    waitStatus  = static_cast<ExWaitResult>( WEXITSTATUS(status) );

    return waitStatus;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Process::_kill_impl(
    culong_t &a_timeoutMsec
)
{
    int_t iRv = ::kill(_pid, SIGKILL);
    xTEST_DIFF(iRv, - 1);

    Thread::currentSleep(a_timeoutMsec);

    _exitStatus = 0U;
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
Process::_exitStatus_impl() const
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
xINLINE Process::id_t
Process::_idByHandle_impl(
    const handle_t &a_handle    ///< handle
)
{
    id_t ulRv = static_cast<id_t>( a_handle );

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE Process::handle_t
Process::_handleById_impl(
    const id_t &a_id   ///< ID
)
{
    handle_t hRv = static_cast<handle_t>( a_id );

    return hRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Process::_isCurrent_impl(
    const Process::id_t &a_id
)
{
    bool_t bRv = ::pthread_equal(static_cast<pthread_t>( currentId() ), static_cast<pthread_t>(a_id));

    return bRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE Process::id_t
Process::_currentId_impl()
{
    id_t ulRv = ::getpid();
    // n/a

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE Process::id_t
Process::_currentParentId_impl()
{
    id_t ulRv = ::getppid();
    xTEST_NA(ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE Process::handle_t
Process::_currentHandle_impl()
{
    handle_t hRv = ::getpid();
    // n/a

    return hRv;
}
//-------------------------------------------------------------------------------------------------
// TODO: tests
xINLINE void_t
Process::_currentExit_impl(
    cuint_t &a_exitCode
)
{
    (void_t)::exit(static_cast<int_t>( a_exitCode ));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
