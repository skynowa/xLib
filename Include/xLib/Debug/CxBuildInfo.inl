/**
 * \file   CxBuildInfo.inl
 * \brief  build information
 */


#include <xLib/Core/CxString.h>


xNAMESPACE2_BEGIN(xlib, debug)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxBuildInfo::isRelease() const
{
#if xBUILD_DEBUG
    return false;
#else
    return true;
#endif
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxBuildInfo::datetime() const
{
    std::tstring_t sRv;

    sRv = CxString::format(xT("%s %s"), xDATE, xTIME);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxBuildInfo::langStandart() const
{
    std::tstring_t  sRv;
    std::ctstring_t separator = xT(", ");

#if xLANG_STANDART_C89
    sRv += xT("C89");
    sRv += separator;
#endif

#if xLANG_STANDART_C90
    sRv += xT("C90");
    sRv += separator;
#endif

#if xLANG_STANDART_C94
    sRv += xT("C94");
    sRv += separator;
#endif

#if xLANG_STANDART_C99
    sRv += xT("C99");
    sRv += separator;
#endif

#if xLANG_STANDART_C11
    sRv += xT("C11");
    sRv += separator;
#endif

#if xLANG_STANDART_CPP98
    sRv += xT("C++98");
    sRv += separator;
#endif

#if xLANG_STANDART_CPP11
    sRv += xT("C++11");
    sRv += separator;
#endif

#if xLANG_STANDART_CPP_CLI
    sRv += xT("C++/CLI");
    sRv += separator;
#endif

#if xLANG_STANDART_ECPP
    sRv += xT("EC++");
    sRv += separator;
#endif

    sRv = CxString::trimRightChars(sRv, separator);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxBuildInfo::osEnvironment() const
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    sRv = xT("Windows");
#elif xOS_ENV_UNIX
    sRv = xT("Unix");
#elif xOS_ENV_APPLE
    sRv = xT("Mac");
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxBuildInfo::os() const
{
    std::tstring_t sRv;

    // TODO: CxBuildInfo::os() - add version

#if   xOS_WIN
    sRv = xT("Windows");
#elif xOS_LINUX
    sRv = xT("Linux");
#elif xOS_FREEBSD
    sRv = xT("FreeBSD");
#elif xOS_MACOS
    sRv = xT("MacOS");
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxBuildInfo::arch() const
{
    std::tstring_t sRv;

#if   xARCH_X86
    sRv = xT("32 bit");
#elif xARCH_X64
    sRv = xT("64 bit");
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxBuildInfo::compiler() const
{
    std::tstring_t sRv;

    // TODO: CxBuildInfo::compiler() - add version

#if   xCOMPILER_MINGW
    sRv = xT("MinGW");
#elif xCOMPILER_MS
    sRv = xT("MSVC");
#elif xCOMPILER_CODEGEAR
    sRv = xT("CodeGear");
#elif xCOMPILER_CLANG
    sRv = xT("CLang");
#elif xCOMPILER_GNUC
    sRv = xT("GNUC");
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxBuildInfo::isUnicodeEncoding() const
{
#if xUNICODE
    return true;
#else
    return false;
#endif
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxBuildInfo::stdLibC() const
{
    std::tstring_t sRv;

    // TODO: CxBuildInfo::stdLibC() - add version

#if   xSTD_LIBC_MSVCRT
    sRv = xT("Microsoft CRT");
#elif xSTD_LIBCPP_GNUSTDCPP
    sRv = xT("GNU libstdc++");
#elif xSTD_LIBC_GNU
    sRv = xT("GNU glibc");
#elif xSTD_LIBC_UC
    sRv = xT("uClibc");
#elif xSTD_LIBC_VMS
    sRv = xT("VMS libc");
#elif xSTD_LIBC_ZOS
    sRv = xT("z/OS libc");
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxBuildInfo::stdLibCpp() const
{
    std::tstring_t sRv;

    // TODO: CxBuildInfo::stdLibC() - add version

#if   xSTD_LIBCPP_GNUSTDCPP
    sRv = xT("GNU libstdc++");
#elif XSTD_LIBCPP_DINKUMWARE
    sRv = xT("Dinkumware");
#elif xSTD_LIBCPP_GNUSTDCPP
    sRv = xT("GNU libstdc++");
#elif xSTD_LIBCPP_INTEL
    sRv = xT("Intel C++ Run-Time Libraries");
#elif xSTD_LIBCPP_LIBCPP
    sRv = xT("libc++");
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxBuildInfo::xlibVersion() const
{
    std::tstring_t sRv;

    sRv = CxString::format(xT("%s %s"), xLIB_VERSION, xLIB_VERSION_SUFFIX);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxBuildInfo::binaryType() const
{
    std::tstring_t sRv;

#if   xLIB
    sRv = xT("Static library");
#elif xDLL
    sRv = xT("Dynamic-link library");
#else
    sRv = xT("Executable binary");
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, debug)
