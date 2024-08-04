/**
 * \file  Os.cpp
 * \brief OS information
 */


#include "Os.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/Fs/FileText.h>
#include <xLib/System/Environment.h>

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
Os::Type
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
Os::Arch
Os::arch() const
{
    return _arch_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Os::formatArch() const
{
    std::tstring_t sRv;

    cArch arch_ = arch();
    switch (arch_) {
    case Arch::Bit32:
        sRv = xT("32-bit");
        break;
    case Arch::Bit64:
        sRv = xT("64-bit");
        break;
    case Arch::Unknown:
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
