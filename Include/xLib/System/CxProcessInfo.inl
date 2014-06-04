/**
 * \file   CxProcessInfo.inl
 * \brief  process information
 */


#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxDll.h>
#include <xLib/System/CxEnvironment.h>

#if   xENV_WIN
    #include "Platform/Win/CxProcessInfo_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/CxProcessInfo_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/CxProcessInfo_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/CxProcessInfo_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/CxProcessInfo_apple.inl"
    #endif
#endif

xNAMESPACE_BEGIN2(xlib, system)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxProcessInfo::CxProcessInfo() :
    _id(0)
{
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxProcessInfo::setProcessId(
    const CxProcess::id_t &a_id
)
{
    _id = a_id;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::cpuUsage() const
{
    return _cpuUsage_impl();
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::ramUsage() const
{
    return _ramUsage_impl();
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::ioBytes() const
{
    return _ioBytes_impl();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxProcessInfo::exeName() const
{
    return _exeName_impl();
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::parentId() const
{
    return _parentId_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxProcessInfo::commandLine(
    std::vec_tstring_t *a_args
) const
{
    xTEST_PTR(a_args);

    _commandLine_impl(a_args);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline long_t
CxProcessInfo::commandLineArgsMax()
{
    return _commandLineArgsMax_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
