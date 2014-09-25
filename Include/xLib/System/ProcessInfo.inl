/**
 * \file   ProcessInfo.inl
 * \brief  process information
 */


#if !xOPTION_HEADER_ONLY
    #include "ProcessInfo.h"
#endif

#include <xLib/Core/String.h>
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
inline
ProcessInfo::ProcessInfo() :
    _id(0)
{
}
//-------------------------------------------------------------------------------------------------
inline void_t
ProcessInfo::setProcessId(
    const Process::id_t &a_id
)
{
    _id = a_id;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
ProcessInfo::cpuUsage() const
{
    return _cpuUsage_impl();
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
ProcessInfo::ramUsage() const
{
    return _ramUsage_impl();
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
ProcessInfo::ioBytes() const
{
    return _ioBytes_impl();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
ProcessInfo::exeName() const
{
    return _exeName_impl();
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
ProcessInfo::parentId() const
{
    return _parentId_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
ProcessInfo::commandLine(
    std::vec_tstring_t *a_args
) const
{
    xTEST_PTR(a_args);

    _commandLine_impl(a_args);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline long_t
ProcessInfo::commandLineArgsMax()
{
    return _commandLineArgsMax_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
