/**
 * \file  Process.inl
 * \brief process
 */


xNAMESPACE_BEGIN2(xl, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Process::_destruct_impl()
{
    xNA;
}
//-------------------------------------------------------------------------------------------------
void_t
Process::_create_impl(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_params
)
{
	std::ctstring_t fileName = Path(a_filePath).fileName();

    const pid_t pid = ::fork();
    switch (pid) {
	case - 1:
		// child - error
		{
			xTEST(false);
			std::exit(EXIT_FAILURE);
		}
		break;
	case 0:
		// child - OK
		{
			// TODO: [skynowa] Process::_create_impl() - a_filePath is executable
			// printf("[CHILD] PID: %d, parent PID: %d\n", getpid(), getppid());

			int_t status = ::execlp(xT2A(a_filePath).c_str(), xT2A(fileName).c_str(),
				xT2A(a_params).c_str(), nullptr);	// this is the child
			xTEST_DIFF(status, - 1);

			(void_t)::_exit(status);  // not std::exit()
		}
		break;
	default:
		// parent - OK (waitpid)
		// printf("[PARENT] PID: %d, parent PID: %d\n", getpid(), pid);
		break;
	}

    _handle = pid;
    _pid    = pid;
}
//-------------------------------------------------------------------------------------------------
Process::WaitResult
Process::_wait_impl(
    culong_t &a_timeoutMsec
)
{
    WaitResult waitStatus = WaitResult::wrFailed;

    xUNUSED(a_timeoutMsec);

    // TODO: [skynowa] Process::_wait_impl() - a_timeoutMsec
    // Thread::currentSleep(a_timeoutMsec);

    pid_t liRv   = - 1L;
    int_t status = 0;

    do {
        liRv = ::waitpid(_pid, &status, 0);
    }
    while (liRv < 0L && NativeError::get() == EINTR);
    xTEST_EQ(liRv, _pid);

    _exitStatus = static_cast<uint_t>( WEXITSTATUS(status) );
    waitStatus  = static_cast<WaitResult>( WEXITSTATUS(status) );

    return waitStatus;
}
//-------------------------------------------------------------------------------------------------
void_t
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
ulong_t
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
Process::id_t
Process::_idByHandle_impl(
    const handle_t &a_handle    ///< handle
)
{
    id_t ulRv = static_cast<id_t>( a_handle );

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
Process::handle_t
Process::_handleById_impl(
    const id_t &a_id   ///< ID
)
{
    handle_t hRv = static_cast<handle_t>( a_id );

    return hRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Process::_isCurrent_impl(
    const Process::id_t &a_id
)
{
    return (currentId() == a_id);
}
//-------------------------------------------------------------------------------------------------
Process::id_t
Process::_currentId_impl()
{
    id_t ulRv = ::getpid();
    // n/a

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
Process::id_t
Process::_currentParentId_impl()
{
    id_t ulRv = ::getppid();
    xTEST_NA(ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
Process::handle_t
Process::_currentHandle_impl()
{
    handle_t hRv = ::getpid();
    // n/a

    return hRv;
}
//-------------------------------------------------------------------------------------------------
// TODO: [skynowa] tests
void_t
Process::_currentExit_impl(
    cuint_t &a_exitCode
)
{
    (void_t)::exit(static_cast<int_t>( a_exitCode ));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
