/**
 * \file  Process.inl
 * \brief process
 */


#include <xLib/Sync/Pipe.h>

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
// TODO: out_stdError - impl
void_t
Process::_create_impl(
    std::ctstring_t                     &a_filePath,
    std::cvec_tstring_t                 &a_params,
    const std::set<std::pair_tstring_t> &a_envs,
    std::tstring_t                      *out_stdOut,  ///< [out] std::cout (maybe as nullptr)
    std::tstring_t                      *out_stdError ///< [out] std::cerr (maybe as nullptr)
)
{
	if (out_stdOut != nullptr) {
		out_stdOut->clear();
	}

	if (out_stdError != nullptr) {
		out_stdError->clear();
	}

	int_t iRv {};

	enum ProcessStatus : pid_t
	{
		ChildError = - 1, ///< returned in the parent, no child process is created, errno is set
		ChildOk    = 0,   ///< PID of the child process - in parent, 0 - in child
		ParentOk          ///< value > 0, creates a new child process (waitpid)
	};

	#define _XLIB_PIPE_OLD 0

	// Create pipes
	Pipe pipeIn;
	pipeIn.create();

	Pipe pipeOut;
	pipeOut.create();

	Pipe pipeErr;
	pipeErr.create();

	// Create process
	const pid_t pid = ::fork();
	switch (pid) {
	case ProcessStatus::ChildError:
		{
			// Cout() << "\n::::: ChildError :::::";

			xTEST(false);
			std::exit(EXIT_FAILURE);
		}
		break;
	case ProcessStatus::ChildOk:
		{
			// Cout() << "\n::::: ChildOk :::::";
			// printf("[CHILD] PID: %d, parent PID: %d\n", getpid(), getppid());

			std::vector<char *> cmds;
			{
				cmds.push_back( const_cast<char *>(xT2A(a_filePath).c_str()) );
				for (auto &it_param : a_params) {
					cmds.push_back( const_cast<char *>(xT2A(it_param).c_str()) );
				}
				cmds.push_back(nullptr);
			}

			std::vector<char *> envs;
			{
				for (auto &[var, value] : a_envs) {
					std::ctstring_t &envVarValue = var + Const::equal() + value;
					envs.push_back( const_cast<char *>(xT2A(envVarValue).c_str()) );
				}
				envs.push_back(nullptr);
			}

			if (out_stdOut != nullptr) {
				// close all other inherited descriptors child doesn't need
			#if _XLIB_PIPE_OLD
				::close(pipeOut[FdIndex::Read]);

				::close(STDOUT_FILENO);
				::close(STDERR_FILENO);

				::dup2(pipeOut[FdIndex::Write], STDOUT_FILENO);
				::dup2(pipeOut[FdIndex::Write], STDERR_FILENO);
			#else
				::dup2(pipeIn.handleRead(),   STDIN_FILENO);
				::dup2(pipeOut.handleWrite(), STDOUT_FILENO);
				::dup2(pipeErr.handleWrite(), STDERR_FILENO);

				// close all other inherited descriptors child doesn't need
				pipeIn.closeRead();
				pipeOut.closeWrite();
				pipeErr.closeWrite();
			#endif
			}

		#if 1
			cint_t status = ::execve(xT2A(a_filePath).c_str(), cmds.data(), envs.data());
			xTEST_DIFF(status, - 1);
		#else
			cint_t status = 0;

			Cout()    << "ChildOk - Stop execve (cout), " << xTRACE_VAR(status);
			std::cerr << "ChildOk - Stop execve (cerr), " << xTRACE_VAR(status) << std::endl;
		#endif

			if (out_stdOut != nullptr) {
			#if _XLIB_PIPE_OLD
				::close(pipeOut[FdIndex::Write]);
			#else

			#endif
			}

			// Cout() << "\n::::: ChildOk - Finished :::::";

			(void_t)::_exit(status);  // not std::exit()
		}
		break;
	case ProcessStatus::ParentOk:
	default:
		// Cout() << "\n::::: ParentOk :::::";
		// printf("[PARENT] PID: %d, parent PID: %d\n", getpid(), pid);

		// read
		if (out_stdOut != nullptr) {
			// binds streams to pipes
			{
				// pipeOut - for read
				pipeOut.closeWrite();
				iRv = ::dup2(pipeOut.handleRead(), STDIN_FILENO);
				xTEST_DIFF(iRv, - 1);

				// pipeErr - for read
				pipeErr.closeWrite();
				iRv = ::dup2(pipeErr.handleRead(), STDIN_FILENO);
				xTEST_DIFF(iRv, - 1);
			}

			// reads
			*out_stdOut   += pipeOut.readAll();
			*out_stdError += pipeErr.readAll();

			// wait
			{
				// ::waitpid(pid, nullptr, 0);
				pipeOut.closeRead();
				pipeErr.closeRead();
			}
		}

		break;
	}

	_handle = pid;
	_pid    = pid;

	// Cout() << "\n::::: Finished :::::";
}
//-------------------------------------------------------------------------------------------------
Process::WaitStatus
Process::_wait_impl(
    culong_t &a_timeoutMsec
)
{
    WaitStatus waitStatus = WaitStatus::Failed;

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
    waitStatus  = static_cast<WaitStatus>( WEXITSTATUS(status) );

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
std::tstring_t
Process::_name_impl() const
{
#if   xENV_LINUX
    // MAN: The buffer should allow space for up to 16 bytes,
    // the returned string will be null-terminated.
    char szRv[16 + 1] {};

    int_t iRv = ::prctl(PR_GET_NAME, (unsigned long)szRv);
    xTEST_DIFF(iRv, - 1);

    return xA2T(szRv);
#elif xENV_BSD
    kinfo_proc *proc = kinfo_getproc( id() );
    xTEST_PTR(proc);

    std::ctstring_t sRv = xA2T(proc->ki_comm);

    Utils::free(proc, std::free);

    return sRv;
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
Process::_setName_impl(
	std::ctstring_t &a_name
) const
{
#if   xENV_LINUX
    int_t iRv = ::prctl(PR_SET_NAME, (unsigned long)xT2A(a_name).c_str(), 0L, 0L, 0L	);
    xTEST_DIFF(iRv, - 1);
#elif xENV_BSD
    (void_t)::setproctitle("%s", xT2A(a_name).c_str());
#endif
}
//-------------------------------------------------------------------------------------------------
bool_t
Process::_isExists_impl() const
{
	errno = 0;

	// If sig is 0, then no signal is sent, but error checking is still performed;
	// this can be used to check for the existence of a process ID or process group ID
	constexpr int sigExistence {0};

	int_t iRv = ::kill(_pid, sigExistence);
	xTEST_DIFF(iRv, - 1);

	// Cout() << xTRACE_VAR_4(_pid, iRv, errno, isRunning(_pid)) << std::endl;

	if (iRv >= 0) {
		return true;
	}

	if (errno == ESRCH) {
		// proc doesn't exist
		return false;
	}

	// some oether error
	return false;
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
