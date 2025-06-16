/**
 * \file  Process.inl
 * \brief process
 *
 * \see   https://github.com/SuperSodaSea/Corecat/blob/master/include/Cats/Corecat/System/Process.hpp
 */


#include <xLib/Sync/Pipe.h>


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Process::_dtor_impl()
{
    xNA;
}
//-------------------------------------------------------------------------------------------------
// TODO: out_stdError - impl
void_t
Process::_create_impl(
    std::ctstring_t                     &a_filePath,  ///< file path
    std::cvec_tstring_t                 &a_params,    ///< cmd paramas
    const std::set<std::pair_tstring_t> &a_envs,      ///< env variables
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

	// Create pipes
	Pipe pipeIn;
	pipeIn.create();

	Pipe pipeOut;
	pipeOut.create();

	Pipe pipeErr;
	pipeErr.create();

	// Create process
	const pid_t pid = ::fork();
	if      (pid == -1) {
		// LogCout() << "\n::::: ChildError :::::";

		xTEST(false);
		std::exit(EXIT_FAILURE);
	}
	// Child
	else if (pid == 0) {
		// LogCout() << "\n::::: ChildOk :::::";

		std::vector<char *> cmds;
		{
			cmds.push_back( const_cast<char *>(xT2A(a_filePath).c_str()) );

			for (const auto &it_param : a_params) {
				cmds.push_back( const_cast<char *>(xT2A(it_param).c_str()) );
			}

			if ( !cmds.empty() ) {
				cmds.push_back(nullptr);
			}
		}

		std::vector<char *> envs;
		{
			for (const auto &[it_var, it_value] : a_envs) {
				std::ctstring_t &envVarValue = it_var + Const::equal() + it_value;

				const auto str = const_cast<char *>(xT2A(envVarValue).c_str());
				envs.push_back(str);
			}

		    /**
			* For GUI app
			*
			* It probably can't find the X Display. Try adding DISPLAY=:0 to the environment
			*
			* \see https://stackoverflow.com/questions/646930/cannot-connect-to-x-server-0-0-with-a-qt-application
			*/
			if (Env env(xT("DISPLAY"));
				env.isExists())
			{
				const auto str = const_cast<char *>( xT2A(env.str()).c_str() );
				envs.push_back(str);
			}

			if ( !envs.empty() ) {
				envs.push_back(nullptr);
			}
		}

		if (out_stdOut != nullptr) {
			// close all other inherited descriptors child doesn't need
			::dup2(pipeIn.handleRead(),   STDIN_FILENO);
			::dup2(pipeOut.handleWrite(), STDOUT_FILENO);
			::dup2(pipeErr.handleWrite(), STDERR_FILENO);

			// TODO: close all other inherited descriptors child doesn't need ?????????
			pipeIn.closeRead();
			pipeOut.closeWrite();
			pipeErr.closeWrite();
		}

		char *const *cmd = cmds.empty() ? nullptr : cmds.data();
		xTEST_PTR(cmd);
		char *const *env = envs.empty() ? nullptr : envs.data();

		cint_t status = ::execve(xT2A(a_filePath).c_str(), cmd, env);
		xTEST_DIFF(status, - 1);

		// LogCout() << "\n::::: ChildOk - Finished :::::";

		(void_t)::_exit(status);  // not std::exit()
	}
	// Parent
	else if (pid > 0) {
		// LogCout() << "\n::::: ParentOk :::::";
		// printf("[PARENT] PID: %lld, parent PID: %d\n", getpid(), pid);

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
	}

	_handle = pid;
	_pid    = pid;

	// LogCout() << "\n::::: Finished :::::";
}
//-------------------------------------------------------------------------------------------------
/**
 * https://www.ibm.com/support/knowledgecenter/SSLTBW_2.1.0/com.ibm.zos.v2r1.bpxbd00/rtwaip.htm
 * https://linux.die.net/man/2/waitpid
 */
Process::WaitStatus
Process::_wait_impl(
    culong_t &a_timeoutMsec
)
{
    xUNUSED(a_timeoutMsec);

    WaitStatus waitStatus = WaitStatus::Failed;

    // TODO: [skynowa] Process::_wait_impl() - a_timeoutMsec
    // Thread::currentSleep(a_timeoutMsec);

    pid_t iRv {-1};

	do {
		int_t status {};
		iRv = ::waitpid(_pid, &status, WUNTRACED | WCONTINUED /* or WNOHANG */ );
		if      (iRv == -1) {
		   /**
			* If unsuccessful, waitpid() returns -1 and sets errno to one of the following values:
			*
			* ECHILD - The process specified by pid does not exist or
			*          is not a child of the calling process, or
			*          the process group specified by pid does not exist or
			*          does not have any member process that is a child of the calling process
			* EINTR  - waitpid() was interrupted by a signal. The value of *status_ptr is undefined
			* EINVAL - The value of options is incorrect
			*/

			LogCout() << "wait() - error";

			_exitStatus = static_cast<uint_t>( NativeError::get() );
			waitStatus  = WaitStatus::Failed;
		}
		else if (iRv == 0) {
		   /**
			* If WNOHANG was given, and if there is at least one process (usually a child)
			* whose status information is not available, waitpid() returns 0
			*/

			// LogCout() << "Child - running";
		}
		else {
		   /**
			* If successful, waitpid() returns a value of the process (usually a child)
			* whose status information has been obtained
			*/

			xTEST_EQ(iRv, _pid);
			xTEST_GR(iRv, 0);

			if      ( WIFEXITED(status) ) {
				// LogCout() << "Child - exited status: " << WEXITSTATUS(status) << " (" << status << ")";

				// WEXITSTATUS - macro should be employed only if WIFEXITED returned true
				_exitStatus = static_cast<uint_t>( WEXITSTATUS(status) );
				waitStatus  = WaitStatus::Ok;
			}
			else if ( WIFSIGNALED(status) ) {
				LogCout() << "Child - killed by signal " << WTERMSIG(status);
			}
			else if ( WIFSTOPPED(status) ) {
				LogCout() << "Child - stopped by signal " << WSTOPSIG(status);
			}
			else if ( WIFCONTINUED(status) ) {
				LogCout() << "Child - continued";
			}
			else {
				LogCout() << "Child - did not exit successfully";

				_exitStatus = static_cast<uint_t>( NativeError::get() );
				waitStatus  = WaitStatus::Abandoned;
			}
		}
	}
	while (iRv == 0);

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
#elif xENV_APPLE
    /// TOOD: [Apple] _name_impl
    return {};
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
#elif xENV_APPLE
    /// TOOD: [Apple] _setName_impl
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

	// LogCout() << xTRACE_VAR_4(_pid, iRv, errno, isRunning(_pid)) << std::endl;

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
	auto ulRv = static_cast<id_t>( a_handle );

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
Process::handle_t
Process::_handleById_impl(
    const id_t &a_id   ///< ID
)
{
	auto hRv = static_cast<handle_t>( a_id );

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
/* static */
void_t
Process::_shellExecute_impl(
    std::ctstring_t &a_filePathOrURL, ///< full file path or URL
	std::ctstring_t &a_params         ///< command line params
)
{
	std::tstring_t cmdLine;

	if (FileType type(a_filePathOrURL); type.isExecutable()) {
		cmdLine = Format::str(xT("{} {}"), String::quoted(a_filePathOrURL), a_params);
	} else {
		std::tstring_t appPath;
		{
		#if   xENV_LINUX
			appPath = xT("xdg-open");
		#elif xENV_BSD
			appPath = xT("open");
		#elif xENV_APPLE
			appPath = xT("open");
		#endif
		}

		cmdLine = Format::str(xT("{} {} {}"), appPath, String::quoted(a_filePathOrURL), a_params);
	}

	cint_t iRv = std::system(cmdLine.c_str());
	xTEST_EQ(iRv, 0);
}
//-------------------------------------------------------------------------------------------------

} // namespace
