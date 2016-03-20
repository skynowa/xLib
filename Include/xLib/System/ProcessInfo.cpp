/**
 * \file   ProcessInfo.inl
 * \brief  process information
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "ProcessInfo.h"
#endif

#include <xLib/Core/String.h>
#include <xLib/Core/Utils.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/File.h>
#include <xLib/IO/Dir.h>
#include <xLib/IO/Dll.h>
#include <xLib/System/Environment.h>

#if   xENV_WIN
    #include "Platform/Win/ProcessInfo_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/ProcessInfo_unix.inl"

    #if   xENV_LINUX
        #include "Platform/Linux/ProcessInfo_linux.inl"
    #elif xENV_BSD
        #include "Platform/Bsd/ProcessInfo_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/ProcessInfo_apple.inl"
    #endif
#endif

xNAMESPACE_BEGIN2(xlib, system)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
ProcessInfo::ProcessInfo() :
    _id(0)
{
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
ProcessInfo::setProcessId(
    const Process::id_t &a_id
)
{
    _id = a_id;
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
ProcessInfo::cpuUsage() const
{
    return _cpuUsage_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
ProcessInfo::ramUsage() const
{
    return _ramUsage_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
ProcessInfo::ioBytes() const
{
    return _ioBytes_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
ProcessInfo::exeName() const
{
    return _exeName_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
ProcessInfo::parentId() const
{
    return _parentId_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
ProcessInfo::commandLine(
    std::vec_tstring_t *a_args
) const
{
    xTEST_PTR(a_args);

    _commandLine_impl(a_args);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE long_t
ProcessInfo::commandLineArgsMax()
{
    return _commandLineArgsMax_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
ProcessInfo::commandLine(
    cint_t             &a_argsNum,
    ctchar_t           *a_argv[],
    std::vec_tstring_t *a_args
)
{
    xTEST_GR_EQ(a_argsNum, 0);
    xTEST_PTR(a_argv);
    xTEST_PTR(a_args);

    for (int_t count = 0; count < a_argsNum; ++ count) {
         a_args->push_back( a_argv[count] );
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
