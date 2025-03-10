/**
 * \file   BuildInfo.inl  (header only)
 * \brief  build information
 */


#include <xLib/Core/String.h>
#include <xLib/Core/Const.h>
#include <xLib/Core/Format.h>
#include <xLib/Fs/Path.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/SourceInfo.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/Debugger.h>


namespace xl::debug
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
BuildInfo::isRelease() const
{
#if xBUILD_DEBUG
    return false;
#else
    return true;
#endif
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
BuildInfo::datetime() const
{
    std::tstring_t sRv;

    sRv = Format::str(xT("{} {}"), xDATE, xTIME);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
BuildInfo::langStandart() const
{
    std::tstring_t sRv;

    std::tstring_t langStandartC;
    {
    #if   xLANG_C89
        langStandartC += xT("C89");
    #elif xLANG_C90
        langStandartC += xT("C90");
    #elif xLANG_C94
        langStandartC += xT("C94");
    #elif xLANG_C99
        langStandartC += xT("C99");
    #elif xLANG_C11
        langStandartC += xT("C11");
    #elif xLANG_C14
        langStandartC += xT("C14");
    #elif xLANG_C17
        langStandartC += xT("C17");
    #elif xLANG_C20
        langStandartC += xT("C20");
    #else
        xBUILD_UNKNOWN("BuildInfo::langStandart() - C standart");
    #endif
    }

    std::tstring_t langStandartCpp;
    {
    #if   sxLANG_ECPP
        langStandartCpp += xT("EC++");
    #elif xLANG_CPP98
        langStandartCpp += xT("C++98");
    #elif xLANG_CPP11
        langStandartCpp += xT("C++11");
    #elif xLANG_CPP14
        langStandartCpp += xT("C++14");
    #elif xLANG_CPP17
        langStandartCpp += xT("C++17");
    #elif xLANG_CPP20
        langStandartCpp += xT("C++20");
    #else
        xBUILD_UNKNOWN("BuildInfo::langStandart() - C++ standart");
    #endif
    }

    sRv = Format::str(xT("{}, {}"), langStandartC, langStandartCpp);
    sRv = String::trimRightChars(sRv, xT(", "));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
BuildInfo::osEnvironment() const
{
    std::tstring_t sRv;

#if   xENV_WIN
    sRv = xT("Windows");
#elif xENV_LINUX
    sRv = xT("Unix/Linux");
#elif xENV_BSD
    sRv = xT("Unix/BSD");
#elif xENV_APPLE
    sRv = xT("Unix/Apple");
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
BuildInfo::os() const
{
    std::tstring_t sRv;

    std::tstring_t osName;
    {
    #if   xOS_WIN
        osName = xT("Windows");
    #elif xOS_ANDROID
        osName = xT("Andriod");
    #elif xOS_LINUX
        osName = xT("Linux");
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
        #elif (xOS_WIN_VER == xOS_WIN_WIN8)
            osVersion = xT("8");
        #elif (xOS_WIN_VER == xOS_WIN_WIN8_1)
            osVersion = xT("8.1");
        #elif (xOS_WIN_VER == xOS_WIN_WIN10)
            osVersion = xT("10");
        #endif
    #elif (xOS_ANDROID || xOS_LINUX)
        cint_t versionMajor = (xOS_LINUX_VER & 0x00FF0000) >> 16;
        cint_t versionMinor = (xOS_LINUX_VER & 0x0000FF00) >> 8;
        cint_t versionPatch = (xOS_LINUX_VER & 0x000000FF) >> 0;

        osVersion = Format::str(xT("{}.{}.{}"), versionMajor, versionMinor, versionPatch);
        xTEST_EQ(LINUX_VERSION_CODE, xLINUX_KERNEL_VER(versionMajor, versionMinor, versionPatch));
    #elif xOS_FREEBSD
        osVersion = String::cast(xOS_FREEBSD_VER);
    #elif xOS_MACOSX
        // TODO: [skynowa] BuildInfo::os() - OS version
        osVersion = Const::strUnknown();
    #endif
    }

    sRv = Format::str(xT("{} {}"), osName, osVersion);
    sRv = String::trimRightChars(sRv, Const::space());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
BuildInfo::arch() const
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
BuildInfo::bitsArch() const
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
BuildInfo::compiler() const
{
    std::tstring_t sRv;
    std::tstring_t compilerName;
    std::tstring_t compilerVersion;

#if   xCOMPILER_MINGW
    #if   defined(__MINGW32__)
        compilerName    = xT("MinGW32");
        compilerVersion = xCOMPILER_MINGW32_VER_STR;
    #elif defined(__MINGW64__)
        compilerName    = xT("MinGW64");
        compilerVersion = xCOMPILER_MINGW64_VER_STR;
    #endif
#elif xCOMPILER_MS
    compilerName    = xT("MSVC");
    compilerVersion = xCOMPILER_MS_VER_STR;
#elif xCOMPILER_CLANG
    compilerName    = xT("CLang");
    compilerVersion = xCOMPILER_CLANG_VER_STR;
#elif xCOMPILER_GNUC
    compilerName    = xT("GNUC");

	#if   defined(xCOMPILER_GCC)
        compilerName += xT(" (GCC)");
	#elif defined(xCOMPILER_CLANG)
        compilerName += xT(" (CLang)");
	#else
        compilerName += xT(" (n/a)");
	#endif

    compilerVersion = xCOMPILER_GNUC_VER_STR;
#endif

    sRv = Format::str(xT("{} {}"), compilerName, compilerVersion);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
BuildInfo::compilerFlags() const
{
    std::tstring_t sRv;

    sRv = String::trimSpace(xCOMPILER_FLAGS);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
BuildInfo::libs() const
{
    std::tstring_t sRv;

    std::vec_tstring_t libPathes;
    String::split(xXLIB_LIBRARIES, xT(";"), &libPathes);

    for (const auto &it : libPathes) {
        sRv += Path(it).fileName() + xT("; ");
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
BuildInfo::isUnicodeEncoding() const
{
#if xUNICODE
    return true;
#else
    return false;
#endif
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
BuildInfo::stdLibC() const
{
    std::tstring_t sRv;
    std::tstring_t stdLibCName;
    std::tstring_t stdLibCVersion;

#if   xSTD_LIBC_MSVCRT
    stdLibCName    = xT("Microsoft CRT");
    stdLibCVersion = xSTD_LIBC_MSVCRT_VER_STR;
#elif xSTD_LIBC_GNUSTDC
    stdLibCName    = xT("GNU libstdc++");
    stdLibCVersion = xSTD_LIBC_GNUSTDC_VER_STR;
#elif xSTD_LIBC_GNU
    stdLibCName    = xT("GNU glibc");
    stdLibCVersion = xSTD_LIBC_GNU_VER_STR;
#elif xSTD_LIBC_UC
    stdLibCName    = xT("uClibc");
    stdLibCVersion = xSTD_LIBC_UC_VER_STR;
#elif xSTD_LIBC_VMS
    stdLibCName    = xT("VMS libc");
    stdLibCVersion = xSTD_LIBC_VMS_VER_STR;
#elif xSTD_LIBC_ZOS
    stdLibCName    = xT("z/OS libc");
    stdLibCVersion = xSTD_LIBC_ZOS_VER_STR;
#elif xSTD_LIBC_BIONIC
    stdLibCName    = xT("Bionic libc");
    stdLibCVersion = xSTD_LIBC_BIONIC_VER_STR;
#elif xSTD_LIBC_K
    stdLibCName    = xT("Klibc");
    stdLibCVersion = xSTD_LIBC_K_VER_STR;
#endif

    sRv = Format::str(xT("{} {}"), stdLibCName, stdLibCVersion);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
BuildInfo::stdLibCpp() const
{
    std::tstring_t sRv;
    std::tstring_t stdLibCppName;
    std::tstring_t stdLibCppVersion;

#if   xSTD_LIBCPP_MSVCRT
    stdLibCppName    = xT("Microsoft CRT");
    stdLibCppVersion = xSTD_LIBCPP_MSVCRT_VER_STR;
#elif xSTD_LIBCPP_GNUSTDCPP
    stdLibCppName    = xT("GNU libstdc++");
    stdLibCppVersion = xSTD_LIBCPP_GNUSTDCPP_VER_STR;
#elif XSTD_LIBCPP_DINKUMWARE
    stdLibCppName    = xT("Dinkumware");
    stdLibCppVersion = XSTD_LIBCPP_DINKUMWARE_VER_STR;
#elif xSTD_LIBCPP_GNUSTDCPP
    stdLibCppName    = xT("GNU libstdc++");
    stdLibCppVersion = xSTD_LIBCPP_GNUSTDCPP_VER_STR;
#elif xSTD_LIBCPP_INTEL
    stdLibCppName    = xT("Intel C++ Run-Time Libraries");
    stdLibCppVersion = xSTD_LIBCPP_INTEL_VER_STR;
#elif xSTD_LIBCPP_LIBCPP
    stdLibCppName    = xT("libc++");
    stdLibCppVersion = xSTD_LIBCPP_LIBCPP_VER_STR;
#endif

    sRv = Format::str(xT("{} {}"), stdLibCppName, stdLibCppVersion);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
BuildInfo::qt() const
{
    std::tstring_t sRv;
    std::tstring_t qtName;
    std::tstring_t qtVersion;

#if xLIB_QT
    qtName    = xT("Qt");
    qtVersion = QT_VERSION_STR;
#else
    qtName    = Const::strUnknown();
    qtVersion = Const::strUnknown();
#endif

    sRv = Format::str(xT("{} {}"), qtName, qtVersion);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
BuildInfo::xlibVersion() const
{
    std::tstring_t sRv;

    sRv = Format::str(xT("{} {} {}/{}"), xLIB_VERSION, xLIB_VERSION_SUFFIX,
        xLIB_GIT_REVISION_BRANCH, xLIB_GIT_REVISION_HASH);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
BuildInfo::xlibBinaryType() const
{
	std::tstring_t sRv = xUNKNOWN_CSTRING;

	constexpr std::tstring_view_t type {cmOPTION_PROJECT_LIB_TYPE};
	if      (type == xT("STATIC")) {
		sRv = xT("Static library");
	}
	else if (type == xT("SHARED")) {
		sRv = xT("Share library");
	}
	else if (type == xT("MODULE")) {
		sRv = xT("Dynamic link library");
	}

	return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
BuildInfo::xlibBuildType() const
{
    return cmCMAKE_BUILD_TYPE;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
BuildInfo::cmake() const
{
    std::tstring_t sRv;
    std::tstring_t name;
    std::tstring_t version;

#if defined(cmCMAKE_VERSION)
    name    = xT("CMake");
    version = cmCMAKE_VERSION;
#else
    name    = Const::strUnknown();
    version = Const::strUnknown();
#endif

    sRv = Format::str(xT("{} {}"), name, version);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
