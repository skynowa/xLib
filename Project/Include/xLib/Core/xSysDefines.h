/**
 * \file  xSysDefines.h
 * \brief predefined macros
 */


#pragma once

#include <cstdlib> // compilers
#include <climits> // standard C libraries
//------------------------------------------------------------------------------
// OS environment
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || \
        defined(__TOS_WIN__) || defined(__WINDOWS__)
    #define xOS_ENV_WIN   1
        ///< Windows environment
#elif defined(__unix__) || defined(__unix)
    #define xOS_ENV_UNIX  1
        ///< Unix environment
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || \
        defined(__bsdi__) || defined(__DragonFly__)
    #define xOS_ENV_BSD   1
        ///< BSD environment
#elif defined(macintosh) || defined(Macintosh) || defined(__APPLE__) || \
        defined(__MACH__)
    #define xOS_ENV_MAC   1
        ///< MacOS environment
#else
    #error xLib: unsupported OS environment
#endif

//------------------------------------------------------------------------------
// OS family
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || \
        defined(__TOS_WIN__) || defined(__WINDOWS__)
    #define xOS_WIN     1
        ///< operating system Windows
#elif defined(linux) || defined(__linux) || defined(__linux__)
    #define xOS_LINUX   1
        ///< operating system Linux
#elif defined(__FreeBSD__)
    #define xOS_FREEBSD 1
        ///< operating system FreeBSD
#elif defined(macintosh) || defined(Macintosh) || defined(__APPLE__) || \
        defined(__MACH__)
    #define xOS_MACOS   1
        ///< operating system MacOS
#else
    #error xLib: unsupported OS
#endif

//------------------------------------------------------------------------------
// OS version
#define xOS_WIN_VER     WINVER      ///< Windows version

#define xOS_WIN_NT4     0x0400      ///< Windows NT 4.0
#define xOS_WIN_2K      0x0500      ///< Windows 2000
#define xOS_WIN_XP      0x0501      ///< Windows Server 2003, Windows XP
#define xOS_WIN_S03     0x0502      ///< Windows Server 2003 SP1, Windows XP SP2
#define xOS_WIN_VISTA   0x0600      ///< Windows Vista, Windows Server 2008
#define xOS_WIN_7       0x0601      ///< Windows 7, Windows Server 2008 R2

#define xOS_LINUX_VER   0           ///< Linux version

#define xOS_FREEBSD_VER __FreeBSD__ ///< FreeBSD version

//------------------------------------------------------------------------------
// OS architecture
#if defined(i386) || defined(__i386__) || defined(__i486__) || \
        defined(__i586__) || defined(__i686__) || defined(__i386) || \
        defined(_M_IX86) || defined(__X86__) || defined(_X86_) || \
        defined(__THW_INTEL__) || defined(__I86__) || defined(__I86__) || \
        defined(__INTEL__)
    #define xARCH_X86 1
        ///< architecture x86
#elif defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || \
        defined(__x86_64) || defined(_M_X64) || defined(__ia64__) || \
        defined(_IA64) || defined(__IA64__) || defined(__ia64) || \
        defined(_M_IA64 )

    #define xARCH_X64 1
        ///< architecture x64
#else
    #error xLib: unsupported architectures
#endif

//------------------------------------------------------------------------------
// compiler types
#if   defined(__MINGW32__) || defined(__MINGW64__)
    #define xCOMPILER_MINGW    1
        ///< compiler MinGW
#elif defined(_MSC_VER) || defined(_MSC_FULL_VER) || defined(_MSC_BUILD)
    #define xCOMPILER_MS       1
        ///< compiler Microsoft Visual C++
#elif defined(__BORLANDC__) || defined(__CODEGEARC__)
    #define xCOMPILER_CODEGEAR 1
        ///< compiler Borland C++, Code Gear
#elif defined(__GNUC__)
    #define xCOMPILER_GNUC     1
        ///< compiler GNU C/C++
#else
    #error xLib: unsupported compiler
#endif

//------------------------------------------------------------------------------
// compiler version
#define xCOMPILER_MINGW32_VER_MAJOR   __MINGW32_MAJOR_VERSION
#define xCOMPILER_MINGW32_VER_MINOR   __MINGW32_MINOR_VERSION
#define xCOMPILER_MINGW64_VER_MAJOR   __MINGW64_VERSION_MAJOR // defined if <stdlib.h> is included
#define xCOMPILER_MINGW64_VER_MINOR   __MINGW64_VERSION_MINOR

#define xCOMPILER_MS_VER              _MSC_VER

#define xCOMPILER_CODEGEAR_VER        __CODEGEARC__

#define xCOMPILER_GNUC_VER_MAJOR      __GNUC__
#define xCOMPILER_GNUC_VER_MINOR      __GNUC_MINOR__
#define xCOMPILER_GNUC_VER_PATCHLEVEL __GNUC_PATCHLEVEL__

//------------------------------------------------------------------------------
// standard C libraries
#if xOS_ENV_WIN
    // TODO: standard C libraries
    #if   xCOMPILER_MINGW
        #include <bits/c++config.h> // standard C++ libraries
    #endif

    #if defined(__MSVCRT__)
        #define xSTD_LIBC_MSVCRT 1
            ///< Microsoft CRT
    #endif
#elif xOS_ENV_UNIX
    #if xOS_FREEBSD
        // TODO: standard C libraries
    #else
        #include <features.h> // standard C libraries
    #endif

    #include <bits/c++config.h> // standard C++ libraries
#elif xOS_ENV_MAC
    #include <bits/c++config.h> // standard C++ libraries
#endif

#if xOS_ENV_WIN
    #if defined(__GLIBCXX__)
        #define xSTD_LIBCPP_GNUSTDCPP 1
            ///< GNU libstdc++
    #endif
#else
    #if   defined(__GNU_LIBRARY__) || defined(__GLIBC__)
        #define xSTD_LIBC_GNU    1
            ///< GNU glibc
    #elif defined(__UCLIBC__)
        #define xSTD_LIBC_UC     1
            ///< uClibc
    #elif defined(__CRTL_VER)
        #define xSTD_LIBC_VMS    1
            ///< VMS libc
    #elif defined(__LIBREL__) || defined(__TARGET_LIB__)
        #define xSTD_LIBC_ZOS    1
            ///< z/OS libc
    #else
        // #warning xLib: unsupported standard C library
    #endif
#endif

//------------------------------------------------------------------------------
// TODO: standard C libraries versions
#define xSTD_LIBC_GNU_VER_MAJOR __GLIBC__
#define xSTD_LIBC_GNU_VER_MINOR __GLIBC_MINOR__

#define xSTD_LIBC_UC_VER        0
#define xSTD_LIBC_VMS_VER       0
#define xSTD_LIBC_ZOS_VER       0

//------------------------------------------------------------------------------
// standard C++ libraries
#if xOS_ENV_WIN
    #if   defined(__GLIBCXX__)
        #define xSTD_LIBCPP_GNUSTDCPP  1
    #endif
#else
    #if   defined(__CPPLIB_VER)
        #define XSTD_LIBCPP_DINKUMWARE 1
            ///< Dinkumware
    #elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
        #define xSTD_LIBCPP_GNUSTDCPP  1
            ///< GNU libstdc++
    #elif defined(__INTEL_CXXLIB_ICC)
        #define xSTD_LIBCPP_INTEL      1
            ///< Intel C++ Run-Time Libraries
    #elif defined(_LIBCPP_VERSION) || defined(_LIBCPP_ABI_VERSION)
        #define xSTD_LIBCPP_LIBCPP     1
            ///< libc++
    #else
        #warning xLib: unsupported standard C++ library
    #endif
#endif

//------------------------------------------------------------------------------
// TODO: standard C++ libraries versions
#define xSTD_LIBCPP_GNU_VER 0
#define xSTD_LIBCPP_UC_VER  0
#define xSTD_LIBCPP_VMS_VER 0
#define xSTD_LIBCPP_ZOS_VER 0

//------------------------------------------------------------------------------
// static, share library
// NOTE: In Unix this defines (_LIB, _DLL) must be set from Makefile
#if   defined(_LIB)
    #define  xLIB 1
        ///< static library
#elif defined(_DLL)
    #define  xDLL 1
        ///< dynamic-link library
#else
    #define  xEXE 1
        ///< executable binary
#endif

//------------------------------------------------------------------------------
// unicode, ansi
#if defined(UNICODE) || defined(_UNICODE)
    #define xUNICODE 1
        ///< unicode
#else
    #define xANSI    1
        ///< ansi
#endif

//------------------------------------------------------------------------------
// debug, release build
#if defined(NDEBUG) || defined(_NDEBUG)
    #define xBUILD_RELEASE 1
        ///< release build
#else
    #define xBUILD_DEBUG   1
        ///< debug build
#endif

//------------------------------------------------------------------------------
