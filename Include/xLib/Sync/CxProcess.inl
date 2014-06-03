/**
 * \file  CxProcess.inl
 * \brief process
 */


#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDll.h>
#include <xLib/Filesystem/CxFinder.h>
#include <xLib/Sync/CxThread.h>

#if   xENV_WIN
    #include "Platform/Win/CxProcess_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/CxProcess_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/CxProcess_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/CxProcess_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/CxProcess_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxProcess::CxProcess() :
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
inline
CxProcess::~CxProcess()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxProcess::create(
    std::ctstring_t &a_filePath,
    ctchar_t        *a_params, ...
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_EQ(CxFile::isExists(a_filePath), true);
    xTEST_PTR(a_params);

    std::tstring_t cmdLine;

    va_list args;
    xVA_START(args, a_params);
    cmdLine = CxString::formatV(a_params, args);
    xVA_END(args);

    // xTRACEV(xT("cmdLine: %s"), cmdLine.c_str());

    _create_impl(a_filePath, cmdLine);
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::ExWaitResult
CxProcess::wait(
    culong_t &a_timeoutMsec
)
{
    return _wait_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxProcess::kill(
    culong_t &a_timeoutMsec
)
{
    _kill_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::handle_t
CxProcess::handle() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::id_t
CxProcess::id() const
{
    return _pid;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxProcess::isCurrent() const
{
    return isCurrent( currentId() );
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcess::exitStatus() const
{
    return _exitStatus_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxProcess::id_t
CxProcess::idByHandle(
    const handle_t &a_handle    ///< handle
)
{
    return _idByHandle_impl(a_handle);
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::handle_t
CxProcess::handleById(
    const id_t &a_id   ///< ID
)
{
    return _handleById_impl(a_id);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline
CxProcess::id_t
CxProcess::idByName(
    std::ctstring_t &a_processName
)
{
    return _idByName_impl(a_processName);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxProcess::isRunning(
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
inline void_t
CxProcess::ids(
    std::vector<CxProcess::id_t> *a_ids
)
{
    _ids_impl(a_ids);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxProcess::isCurrent(
    const CxProcess::id_t &a_id
)
{
    return _isCurrent_impl(a_id);
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::id_t
CxProcess::currentId()
{
    // n/a

    return _currentId_impl();
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::id_t
CxProcess::currentParentId()
{
    // n/a

    return _currentParentId_impl();
}
//-------------------------------------------------------------------------------------------------
// TODO: tests
inline CxProcess::handle_t
CxProcess::currentHandle()
{
    // n/a

    return _currentHandle_impl() ;
}
//-------------------------------------------------------------------------------------------------
// TODO: CxProcess::currentExit() - tests
inline void_t
CxProcess::currentExit(
    cuint_t &a_exitCode
)
{
    _currentExit_impl(a_exitCode);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
