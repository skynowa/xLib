/**
 * \file  Process.inl
 * \brief process
 */


#include "Process.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/File.h>
#include <xLib/Fs/Dll.h>
#include <xLib/Fs/Finder.h>
#include <xLib/Sync/Thread.h>

#if   xENV_WIN
    #include "Platform/Win/Process_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Process_unix.inl"

    #if   xENV_LINUX
        #include "Platform/Linux/Process_linux.inl"
    #elif xENV_BSD
        #include "Platform/Bsd/Process_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/Process_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xl, sync)

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
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Process::create(
    std::ctstring_t                     &a_filePath, ///< binary file path
    std::cvec_tstring_t                 &a_params,   ///< command line params
    const std::set<std::pair_tstring_t> &a_envs      ///< evironments ({"HOME=/usr/home", "LOGNAME=home"})
)
{
#if 0
	Cout() << xTRACE_VAR(a_filePath) << std::endl;
	Cout() << xTRACE_VAR(a_params) << std::endl;
	Cout() << xTRACE_VAR(a_envs) << std::endl;
#endif

    xTEST_EQ(a_filePath.empty(), false);
    xTEST_EQ(File::isExists(a_filePath), true);
    xTEST_EQ(File::isExecutable(a_filePath), true);
    xTEST_NA(a_params);
    xTEST_NA(a_envs);

    _create_impl(a_filePath, a_params, a_envs);
}
//-------------------------------------------------------------------------------------------------
Process::WaitResult
Process::wait(
    culong_t &a_timeoutMsec    ///< waiting timeout
)
{
    return _wait_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
void_t
Process::kill(
    culong_t &a_timeoutMsec    ///< waiting timeout
)
{
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
bool_t
Process::isCurrent() const
{
    return isCurrent( currentId() );
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

    std::vector<id_t>::iterator it = std::find(_ids.begin(), _ids.end(), a_id);
    xCHECK_RET(it == _ids.end(), false);

    return true;
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


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
void_t
Process::create(
    std::ctstring_t                     &a_filePath,        ///< binary file path
    culong_t                             a_waitTimeoutMsec, ///< waiting timeout
    std::cvec_tstring_t                 &a_params,          ///< command line params
    const std::set<std::pair_tstring_t> &a_envs             ///< evironments ({"HOME=/usr/home", "LOGNAME=home"})
)
{
    Process proc;
    proc.create(a_filePath, a_params, a_envs);

    Process::WaitResult wrRes = proc.wait(xTIMEOUT_INFINITE);
    xTEST_EQ((int)Process::WaitResult::wrAbandoned, (int)wrRes);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
