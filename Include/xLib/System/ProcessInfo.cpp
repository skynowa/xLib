/**
 * \file   ProcessInfo.inl
 * \brief  process information
 */


#include "ProcessInfo.h"

#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/File.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/Dll.h>
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

xNAMESPACE_BEGIN2(xl, system)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
ProcessInfo::ProcessInfo() :
    _id(0)
{
}
//-------------------------------------------------------------------------------------------------
void_t
ProcessInfo::setProcessId(
    const Process::id_t &a_id
)
{
    _id = a_id;
}
//-------------------------------------------------------------------------------------------------
ulong_t
ProcessInfo::cpuUsage() const
{
    return _cpuUsage_impl();
}
//-------------------------------------------------------------------------------------------------
ulong_t
ProcessInfo::ramUsage() const
{
    return _ramUsage_impl();
}
//-------------------------------------------------------------------------------------------------
ulong_t
ProcessInfo::ioBytes() const
{
    return _ioBytes_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
ProcessInfo::exeName() const
{
    return _exeName_impl();
}
//-------------------------------------------------------------------------------------------------
ulong_t
ProcessInfo::parentId() const
{
    return _parentId_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
ProcessInfo::commandLine(
    std::vec_tstring_t *a_args
) const
{
    xTEST_PTR(a_args);

    xCHECK_DO(a_args != xPTR_NULL, a_args->clear());

    _commandLine_impl(a_args);
}
//-------------------------------------------------------------------------------------------------
/* static */
long_t
ProcessInfo::commandLineArgsMax()
{
    return _commandLineArgsMax_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
ProcessInfo::commandLine(
    cint_t             &a_argsNum,
    cptr_ctchar_t       a_argv[],
    std::vec_tstring_t *a_args
)
{
    xTEST_GR_EQ(a_argsNum, 0);
    xTEST_PTR(a_argv);
    xTEST_PTR(a_args);

    xCHECK_DO(a_args != xPTR_NULL, a_args->clear());

    for (int_t i = 0; i < a_argsNum; ++ i) {
         a_args->push_back( a_argv[i] );
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, system)
