/**
 * \file  Os.inl
 * \brief system information
 */


#include "Os.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/Dll.h>
#include <xLib/Fs/File.h>
#include <xLib/System/Environment.h>
#include <xLib/System/Info/Os.h>

#if   xENV_WIN
    #include <xLib/System/Info/Platform/Win/Os_win.inl>
#elif xENV_UNIX
    #include <xLib/System/Info/Platform/Unix/Os_unix.inl>

    #if   xENV_LINUX
        #include <xLib/System/Info/Platform/Linux/Os_linux.inl>
    #elif xENV_BSD
        #include <xLib/System/Info/Platform/Bsd/Os_bsd.inl>
    #elif xENV_APPLE
        #include <xLib/System/Info/Platform/Apple/Os_apple.inl>
    #endif
#endif


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
Os::OsType
Os::os() const
{
    return _os_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Os::formatOs() const
{
    return _formatOs_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Os::distro() const
{
    return _distro_impl();
}
//-------------------------------------------------------------------------------------------------
Os::OsArch
Os::osArch() const
{
    return _osArch_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Os::formatOsArch() const
{
    std::tstring_t sRv;

    cOsArch arch = osArch();
    switch (arch) {
    case OsArch::Bit32:
        sRv = xT("32-bit");
        break;
    case OsArch::Bit64:
        sRv = xT("64-bit");
        break;
    case OsArch::Unknown:
        sRv = Const::strUnknown();
        break;
    default:
        sRv = Const::strUnknown();
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Os::desktopName() const
{
    return _desktopName_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
