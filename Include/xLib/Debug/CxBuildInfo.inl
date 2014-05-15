/**
 * \file   CxBuildInfo.inl
 * \brief  build information
 */


#include <xLib/Core/CxString.h>

#include <xLib/Core/CxConst.h>


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
#elif xOS_ENV_LINUX
    sRv = xT("Unix/Linux");
#elif xOS_ENV_BSD
    sRv = xT("Unix/BSD");
#elif xOS_ENV_APPLE
    sRv = xT("Unix/Apple");
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxBuildInfo::os() const
{
    std::tstring_t sRv;

    std::tstring_t osName;
    {
    #if   xOS_WIN
        osName = xT("Windows");
    #elif xOS_LINUX
        osName = xT("Linux");
    #elif xOS_ANDROID
        osName = xT("Andriod");
    #elif xOS_FREEBSD
        osName = xT("FreeBSD");
    #elif xOS_MACOSX
        osName = xT("MacOSX");
    #endif
    }

    std::tstring_t osVersion;
    {
    #if   xOS_WIN
        #if   (xOS_WIN_VER == xOS_WIN_NT4)
            osVersion = xT("NT 4.0");
        #elif (xOS_WIN_VER == xOS_WIN_2K)
            osVersion = xT("2000");
        #elif (xOS_WIN_VER == xOS_WIN_XP)
            osVersion = xT("Server 2003, Windows XP");
        #elif (xOS_WIN_VER == xOS_WIN_S03)
            osVersion = xT("Server 2003 SP1, Windows XP SP2");
        #elif (xOS_WIN_VER == xOS_WIN_VISTA)
            osVersion = xT("Vista, Windows Server 2008");
        #elif (xOS_WIN_VER == xOS_WIN_7)
            osVersion = xT("7, Windows Server 2008 R2");
        #endif
    #elif xOS_LINUX
        cint_t version1 = (xOS_LINUX_VER & 0x00FF0000) >> 16;
        cint_t version2 = (xOS_LINUX_VER & 0x0000FF00) >> 8;
        cint_t version3 = (xOS_LINUX_VER & 0x000000FF) >> 0;

        osVersion = CxString::format(xT("%d.%d.%d"), version1, version2, version3);
        xTEST_EQ(LINUX_VERSION_CODE, KERNEL_VERSION(version1, version2, version3));
    #elif xOS_ANDROID
        osVersion = CxString::cast(xOS_ANDROID);
    #elif xOS_FREEBSD
        osVersion = CxString::cast(xOS_FREEBSD_VER);
    #elif xOS_MACOSX
        // TODO: CxBuildInfo::os() - OS version
        osVersion = CxConst::strUnknown();
    #endif
    }

    sRv = CxString::format(xT("%s %s"), osName.c_str(), osVersion.c_str());
    sRv = CxString::trimRightChars(sRv, CxConst::space());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxBuildInfo::arch() const
{
    std::tstring_t sRv;

#if   xARCH_ALPHA
    sRv = xT("Alpha");
#elif xARCH_AMD64
    sRv = xT("AMD64");
#elif xARCH_ARM
    sRv = xT("ARM");
#elif xARCH_ARM64
    sRv = xT("ARM64");
#elif xARCH_BLACKFIN
    sRv = xT("Blackfin");
#elif xARCH_CONVEX
    sRv = xT("Convex");
#elif xARCH_EPIPHANY
    sRv = xT("Epiphany");
#elif xARCH_HP_PA_RISC
    sRv = xT("HP/PA RISC");
#elif xARCH_INTEL_X86
    sRv = xT("Intel x86");
#elif xARCH_IA64
    sRv = xT("Intel Itanium (IA-64)");
#elif xARCH_MOTOROLA_68K
    sRv = xT("Motorola 68k");
#elif xARCH_MIPS
    sRv = xT("MIPS");
#elif xARCH_POWERPC
    sRv = xT("PowerPC");
#elif xARCH_PYRAMID_9810
    sRv = xT("Pyramid 9810");
#elif xARCH_RS_6000
    sRv = xT("RS/6000");
#elif xARCH_SPARC
    sRv = xT("SPARC");
#elif xARCH_SUPERH
    sRv = xT("SuperH");
#elif xARCH_SYSTEMZ
    sRv = xT("SystemZ");
#elif xARCH_TMS320
    sRv = xT("TMS320");
#elif xARCH_TMS470
    sRv = xT("TMS470");
#else
    #error xLib: unsupported architecture
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxBuildInfo::bitsArch() const
{
    std::tstring_t sRv;

#if   xARCH_BITS_32
    sRv = xT("32-bit");
#elif xARCH_BITS_64
    sRv = xT("64-bit");
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxBuildInfo::compiler() const
{
    std::tstring_t sRv;

    std::tstring_t compilerName;
    {
    #if   xCOMPILER_MINGW
        compilerName = xT("MinGW");
    #elif xCOMPILER_MS
        compilerName = xT("MSVC");
    #elif xCOMPILER_CODEGEAR
        compilerName = xT("CodeGear");
    #elif xCOMPILER_CLANG
        compilerName = xT("CLang");
    #elif xCOMPILER_GNUC
        compilerName = xT("GNUC");
    #endif
    }

    std::tstring_t compilerVersion;
    {
    #if   xCOMPILER_MINGW
        #if   defined(__MINGW32__)
            compilerVersion = CxString::cast(xCOMPILER_MINGW32_VER);
        #elif defined(__MINGW64__)
            compilerVersion = CxString::cast(xCOMPILER_MINGW64_VER);
        #endif
    #elif xCOMPILER_MS
        compilerVersion = CxString::cast(xCOMPILER_MS_VER);
    #elif xCOMPILER_CODEGEAR
        compilerVersion = CxString::cast(xCOMPILER_CODEGEAR_VER);
    #elif xCOMPILER_CLANG
        compilerVersion = CxString::cast(xCOMPILER_CLANG_VER);
    #elif xCOMPILER_GNUC
        compilerVersion = CxString::cast(xCOMPILER_GNUC_VER);
    #endif
    }

    sRv = CxString::format(xT("%s %s"), compilerName.c_str(), compilerVersion.c_str());

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

    sRv = CxString::format(xT("%s %s %s/%s"), xLIB_VERSION, xLIB_VERSION_SUFFIX,
        xLIB_GIT_REVISION_BRANCH, xLIB_GIT_REVISION_HASH);

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
