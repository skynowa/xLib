/**
 * \file  Process.inl
 * \brief process
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Process.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/File.h>
#include <xLib/IO/Dll.h>
#include <xLib/IO/Finder.h>
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


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Process::Process() :
    _handle    (0),
#if xENV_WIN
    _thread    (xPTR_NULL),
#endif
    _pid       (0UL),
    _exitStatus(0U)
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
Process::~Process()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Process::create(
    std::ctstring_t &a_filePath,
    ctchar_t        *a_params, ...
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_EQ(File::isExists(a_filePath), true);
    xTEST_PTR(a_params);

    std::tstring_t cmdLine;

    va_list args;
    xVA_START(args, a_params);
    cmdLine = FormatC::strV(a_params, args);
    xVA_END(args);

    // xTRACEV(xT("cmdLine: %s"), cmdLine.c_str());

    _create_impl(a_filePath, cmdLine);
}
//-------------------------------------------------------------------------------------------------
xINLINE Process::ExWaitResult
Process::wait(
    culong_t &a_timeoutMsec
)
{
    return _wait_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Process::kill(
    culong_t &a_timeoutMsec
)
{
    _kill_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
xINLINE Process::handle_t
Process::handle() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
xINLINE Process::id_t
Process::id() const
{
    return _pid;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Process::isCurrent() const
{
    return isCurrent( currentId() );
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
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
xINLINE Process::id_t
Process::idByHandle(
    const handle_t &a_handle    ///< handle
)
{
    return _idByHandle_impl(a_handle);
}
//-------------------------------------------------------------------------------------------------
xINLINE Process::handle_t
Process::handleById(
    const id_t &a_id   ///< ID
)
{
    return _handleById_impl(a_id);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE
Process::id_t
Process::idByName(
    std::ctstring_t &a_processName
)
{
    return _idByName_impl(a_processName);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE bool_t
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
xINLINE void_t
Process::ids(
    std::vector<Process::id_t> *a_ids
)
{
    a_ids->clear();

    _ids_impl(a_ids);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Process::isCurrent(
    const Process::id_t &a_id
)
{
    return _isCurrent_impl(a_id);
}
//-------------------------------------------------------------------------------------------------
xINLINE Process::id_t
Process::currentId()
{
    // n/a

    return _currentId_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE Process::id_t
Process::currentParentId()
{
    // n/a

    return _currentParentId_impl();
}
//-------------------------------------------------------------------------------------------------
// TODO: tests
xINLINE Process::handle_t
Process::currentHandle()
{
    // n/a

    return _currentHandle_impl() ;
}
//-------------------------------------------------------------------------------------------------
// TODO: Process::currentExit() - tests
xINLINE void_t
Process::currentExit(
    cuint_t &a_exitCode
)
{
    _currentExit_impl(a_exitCode);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
