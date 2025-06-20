/**
 * \file  Process.cpp
 * \brief process
 */


#include "Process.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/ScopeExit.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/FileInfo.h>
#include <xLib/Fs/Dll.h>
#include <xLib/Fs/Finder.h>
#include <xLib/Log/LogStream.h>
#include <xLib/Sync/Thread.h>
#include <xLib/System/Env.h>

#if   xENV_WIN
    #include "Platform/Win/Process_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Process_unix.inl"

    #if   xENV_LINUX
        #include "Platform/Linux/Process_linux.inl"
    #elif xENV_BSD
        #include "Platform/Bsd/Process_bsd.inl"
    #elif xENV_APPLE
        #include "Platform/Apple/Process_apple.inl"
    #endif
#endif


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Process::Process()
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
Process::~Process()
{
    _dtor_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Process::create(
    std::ctstring_t                     &a_filePath,  ///< binary file path
    std::cvec_tstring_t                 &a_params,    ///< command line params
    const std::set<std::pair_tstring_t> &a_envs,      ///< evironments ({"HOME=/usr/home", "LOGNAME=home"})
    std::tstring_t                      *out_stdOut,  ///< [out] std::cout (maybe as nullptr)
    std::tstring_t                      *out_stdError ///< [out] std::cerr (maybe as nullptr)
)
{
#if 0
	LogCout() << xTRACE_VAR(a_filePath) << std::endl;
	LogCout() << xTRACE_VAR(a_params) << std::endl;
	LogCout() << xTRACE_VAR(a_envs) << std::endl;
#endif

	xTEST(!a_filePath.empty());
    xTEST_NA(a_params);
    xTEST_NA(a_envs);
    xTEST_NA(out_stdOut);
    xTEST_NA(out_stdError);

	xCHECK_DO(!FileInfo(a_filePath).isExists(),
		LogCout() << xTRACE_VAR(a_filePath) << xT(" not exists"); return);
	xCHECK_DO(!FileType(a_filePath).isExecutable(),
		LogCout() << xTRACE_VAR(a_filePath) << xT(" not executable"); return);

    _create_impl(a_filePath, a_params, a_envs, out_stdOut, out_stdError);
}
//-------------------------------------------------------------------------------------------------
Process::WaitStatus
Process::wait(
    culong_t &a_timeoutMsec    ///< waiting timeout
)
{
    xCHECK_RET(handle() == 0, WaitStatus::Failed);

    return _wait_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
void_t
Process::kill(
    culong_t &a_timeoutMsec    ///< waiting timeout
)
{
	if ( !isExists() ) {
		return;
	}

	if (exitStatus() == EXIT_SUCCESS) {
		return;
	}

	LogCout() << xT("Kill: ") << xTRACE_VAR(_pid) << std::endl;

    _kill_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
Process::handle_t
Process::handle() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
Process::id_t
Process::id() const
{
    return _pid;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Process::name() const
{
	return _name_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Process::setName(
	std::ctstring_t &a_name
) const
{
	_setName_impl(a_name);
}
//-------------------------------------------------------------------------------------------------
bool_t
Process::isValid() const
{
    if (_handle == 0 ||
	#if xENV_WIN
		_thread == 0 ||
	#endif
        _pid == 0)
    {
		return false;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
Process::isCurrent() const
{
    return isCurrent( currentId() );
}
//-------------------------------------------------------------------------------------------------
bool_t
Process::isExists() const
{
	return _isExists_impl();
}
//-------------------------------------------------------------------------------------------------
ulong_t
Process::exitStatus() const
{
    return _exitStatus_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Process::id_t
Process::idByHandle(
    const handle_t &a_handle    ///< handle
)
{
    return _idByHandle_impl(a_handle);
}
//-------------------------------------------------------------------------------------------------
Process::handle_t
Process::handleById(
    const id_t &a_id   ///< ID
)
{
    return _handleById_impl(a_id);
}
//-------------------------------------------------------------------------------------------------
/* static */
Process::id_t
Process::idByName(
    std::ctstring_t &a_processName
)
{
    return _idByName_impl(a_processName);
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Process::isRunning(
    const id_t &a_id
)
{
    std::vector<id_t> _ids;
    ids(&_ids);

    return Algos::isContains(_ids, a_id);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Process::ids(
    std::vector<Process::id_t> *a_ids
)
{
    a_ids->clear();

    _ids_impl(a_ids);
}
//-------------------------------------------------------------------------------------------------
bool_t
Process::isCurrent(
    const Process::id_t &a_id
)
{
    return _isCurrent_impl(a_id);
}
//-------------------------------------------------------------------------------------------------
Process::id_t
Process::currentId()
{
    // n/a

    return _currentId_impl();
}
//-------------------------------------------------------------------------------------------------
Process::id_t
Process::currentParentId()
{
    // n/a

    return _currentParentId_impl();
}
//-------------------------------------------------------------------------------------------------
// TODO: [skynowa] tests
Process::handle_t
Process::currentHandle()
{
    // n/a

    return _currentHandle_impl() ;
}
//-------------------------------------------------------------------------------------------------
// TODO: [skynowa] Process::currentExit() - tests
void_t
Process::currentExit(
    cuint_t &a_exitCode
)
{
    _currentExit_impl(a_exitCode);
}
//-------------------------------------------------------------------------------------------------
// TODO: [skynowa] Process::currenQuicktExit() - tests
// FAQ: https://github.com/boostorg/core/blob/develop/include/boost/core/quick_exit.hpp
void_t
Process::currenQuicktExit(
    cuint_t &a_exitCode
)
{
	/// TOOD: [xENV_APPLE] currenQuicktExit
#if xENV_APPLE
	std::exit( static_cast<int_t>(a_exitCode) );
#else
	std::quick_exit( static_cast<int_t>(a_exitCode) );
#endif
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
void_t
Process::execute(
    std::ctstring_t                     &a_filePath,        ///< binary file path
    std::cvec_tstring_t                 &a_params,          ///< command line params
    const std::set<std::pair_tstring_t> &a_envs,            ///< evironments ({"HOME=/usr/home", "LOGNAME=home"})
    culong_t                             a_waitTimeoutMsec, ///< waiting timeout
    std::tstring_t                      *out_stdOut,        ///< [out] std::cout (maybe as nullptr)
    std::tstring_t                      *out_stdError       ///< [out] std::cerr (maybe as nullptr)
)
{
    Process proc;
    proc.create(a_filePath, a_params, a_envs, out_stdOut, out_stdError);
    xCHECK_DO(!proc.isValid(), return);

    cWaitStatus wrRes = proc.wait(a_waitTimeoutMsec);
    xTEST_EQ((int)wrRes,   (int)Process::WaitStatus::Ok);
    xTEST_DIFF((int)wrRes, (int)Process::WaitStatus::Abandoned);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Process::execute(
    std::ctstring_t     &a_filePath,  ///< binary file path
    std::cvec_tstring_t &a_params,    ///< command line params
    std::tstring_t      *out_stdOut,  ///< [out] std::cout (maybe as nullptr)
    std::tstring_t      *out_stdError ///< [out] std::cerr (maybe as nullptr)
)
{
    const std::set<std::pair_tstring_t> envs;
    culong_t                            waitTimeoutMsec {xTIMEOUT_INFINITE};

    execute(a_filePath, a_params, envs, waitTimeoutMsec, out_stdOut, out_stdError);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Process::shellExecute(
    std::ctstring_t     &a_filePathOrURL, ///< full file path or URL
    std::cvec_tstring_t &a_params         ///< command line params
)
{
    xTEST(Path(a_filePathOrURL).isAbsolute() || _isUrlFull(a_filePathOrURL));

    std::ctstring_t params = String::join(a_params, Const::space());

    _shellExecute_impl(a_filePathOrURL, params);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Process::_isUrlFull(
    std::ctstring_t &a_url	///< URL
)
{
    // List of known URL schemes
    constexpr std::ctstring_view_t schemes[] =
    {
        xT("http://"), xT("https://"), xT("ftp://"), xT("ftps://"), xT("sftp://"),
        xT("mailto:"), xT("www."), xT("file://")
    };

    // Check if the URL starts with any of the known schemes
    for (const auto &it_scheme : schemes) {
        if (a_url.compare(0, it_scheme.size(), it_scheme) == 0) {
            return true;
        }
    }

    return false;
}
//-------------------------------------------------------------------------------------------------

} // namespace
