/**
 * \file  xSysDefines.h
 * \brief predefined macros
 */


#pragma once

#ifndef xLib_xSysDefinesH
#define xLib_xSysDefinesH
//-------------------------------------------------------------------------------------------------
#include <cstdlib> // compilers
#include <climits> // standard C libraries
//-------------------------------------------------------------------------------------------------
// Language standards
#if defined(__STDC__)
    #define xLANG_STANDART_C89 1
        ///< ANSI X3.159-1989
#endif

#if defined(__STDC_VERSION__)
    #define xLANG_STANDART_C90 1
        ///< ISO/IEC 9899:1990
#endif

#if (__STDC_VERSION__ >= 199409L)
    #define xLANG_STANDART_C94 1
        ///< ISO/IEC 9899-1:1994
#endif

#if (__STDC_VERSION__ >= 199901L)
    #define xLANG_STANDART_C99 1
        ///< ISO/IEC 9899:1999
#endif

#if (__STDC_VERSION__ >= 201112L)
    #define xLANG_STANDART_C11 1
        ///< ISO/IEC 9899:2011
#endif

#if (__cplusplus >= 199711L)
    #define xLANG_STANDART_CPP98 1
        ///< ISO/IEC 14882:1998
#endif

#if (__cplusplus >= 201103L)
    #define xLANG_STANDART_CPP11 1
        ///< ISO/IEC 14882:2011
#endif

#if (__cplusplus_cli >= 200406L)
    #define xLANG_STANDART_CPP_CLI 1
        ///< ECMA-372
#endif

#if defined(__embedded_cplusplus)
    #define xLANG_STANDART_ECPP 1
        ///< Embedded C++
#endif
//-------------------------------------------------------------------------------------------------
// OS environment
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || \
        defined(__WINDOWS__)
    #define xENV_WIN   1
        ///< Windows environment
#elif defined(__unix__) || defined(__unix)
    #define xENV_UNIX  1
        ///< Unix environment

    #if   defined(linux) || defined(__linux) || defined(__linux__)
        #define xENV_LINUX   1
            ///< Linux environment
    #elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || \
            defined(__bsdi__) || defined(__DragonFly__)
        #define xENV_BSD   1
            ///< BSD environment
    #elif defined(macintosh) || defined(Macintosh) || defined(__APPLE__) || defined(__MACH__)
        #define xENV_APPLE   1
            ///< Apple environment
    #else
        #error xLib: unsupported OS environment
    #endif
#else
    #error xLib: unsupported OS environment
#endif

//-------------------------------------------------------------------------------------------------
// OS family
#if   xENV_WIN
    #define xOS_WIN 1
        ///< OS Windows
#elif xENV_UNIX
    #if   xENV_LINUX
        #if  !defined(__ANDROID__)
            #define xOS_LINUX 1
                ///< OS Linux
        #elif defined(__ANDROID__)
            #define xOS_ANDROID 1
                ///< OS Android
        #else
            #error xLib: unsupported OS
        #endif
    #elif xENV_BSD
        #if defined(__FreeBSD__)
            #define xOS_FREEBSD 1
                ///< OS FreeBSD
        #else
                #error xLib: unsupported OS
        #endif
    #elif xENV_APPLE
        #if defined(__APPLE__ && __MACH__)
            #define xOS_MACOSX 1
                ///< OS MacOSX
        #else
                #error xLib: unsupported OS
        #endif
    #endif
#endif

//-------------------------------------------------------------------------------------------------
// OS version
#define xOS_WIN_VER     WINVER
    ///< Windows version
#define xOS_WIN_NT4     0x0400
    ///< Windows NT 4.0
#define xOS_WIN_2K      0x0500
    ///< Windows 2000
#define xOS_WIN_XP      0x0501
    ///< Windows Server 2003, Windows XP
#define xOS_WIN_S03     0x0502
    ///< Windows Server 2003 SP1, Windows XP SP2
#define xOS_WIN_VISTA   0x0600
    ///< Windows Vista, Windows Server 2008
#define xOS_WIN_7       0x0601
    ///< Windows 7, Windows Server 2008 R2

#if !defined(KERNEL_VERSION)
    #define xLINUX_KERNEL_VER(a, b, c) (((a) << 16) + ((b) << 8) + (c))
#else
    #define xLINUX_KERNEL_VER KERNEL_VERSION
#endif
    ///< get Linux kernel version

#define xOS_LINUX_VER   LINUX_VERSION_CODE
    ///< Linux version

#define xOS_ANDROID_VER __ANDROID_API__
    ///< Android version from <android/api-level.h>

#define xOS_FREEBSD_VER __FreeBSD__
    ///< FreeBSD version

//-------------------------------------------------------------------------------------------------
// OS architecture
#if   defined(__alpha__) || defined(__alpha) || defined(_M_ALPHA)
    #define xARCH_ALPHA 1
        ///< architecture Alpha
#elif defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || \
        defined(_M_X64) || defined(_M_AMD64)
    #define xARCH_AMD64 1
        ///< architecture AMD64
#elif defined(__arm__) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) || \
        defined(__TARGET_ARCH_THUMB) || defined(_ARM) || defined(_M_ARM) || defined(_M_ARMT)
    #define xARCH_ARM 1 // ???
        ///< architecture ARM
#elif defined(__aarch64__)
    #define xARCH_ARM64 1
        ///< architecture ARM64
#elif defined(__bfin) || defined(__BFIN__)
    #define xARCH_BLACKFIN 1
        ///< architecture Blackfin
#elif defined(__convex__)
    #define xARCH_CONVEX 1    // ???
        ///< architecture Convex
#elif defined(__epiphany__)
    #define xARCH_EPIPHANY 1    // ???
        ///< architecture Epiphany
#elif defined(__hppa__) || defined(__HPPA__) || defined(__hppa)
    #define xARCH_HP_PA_RISC 1
        ///< architecture HP/PA RISC
#elif defined(i386) || defined(__i386) || defined(__i386__) || defined(__i486__) || \
        defined(__i586__) || defined(__i686__) || defined(__IA32__) || defined(_M_I86) || \
        defined(_M_IX86) || defined(__X86__) || defined(_X86_) || defined(__THW_INTEL__) || \
        defined(__I86__) || defined(__INTEL__)
    #define xARCH_INTEL_X86 1
        ///< architecture Intel x86
#elif defined(__ia64__) || defined(_IA64) || defined(__IA64__) || defined(__ia64) || \
        defined(_M_IA64) || defined(__itanium__)
    #define xARCH_IA64 1
        ///< architecture Intel Itanium (IA-64)
#elif defined(__m68k__) || defined(M68000) || defined(__MC68K__)
    #define xARCH_MOTOROLA_68K 1
        ///< architecture Motorola 68k
#elif defined(__mips__) || defined(mips) || defined(__mips) || defined(__MIPS__)
    #define xARCH_MIPS 1
        ///< architecture MIPS
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || \
        defined(__POWERPC__) || defined(__ppc__) || defined(__ppc64__) || defined(_M_PPC) || \
        defined(_ARCH_PPC)
    #define xARCH_POWERPC 1
        ///< architecture PowerPC
#elif defined(pyr)
    #define xARCH_PYRAMID_9810 1 // ???
        ///< architecture Pyramid 9810
#elif defined(__THW_RS6000) || defined(_IBMR2) || defined(_POWER) || defined(_ARCH_PWR) || \
        defined(_ARCH_PWR2) || defined(_ARCH_PWR3) || defined(_ARCH_PWR4)
    #define xARCH_RS_6000 1 // ???
        ///< architecture RS/6000
#elif defined(__sparc__) || defined(__sparc)
    #define xARCH_SPARC 1
        ///< architecture SPARC
#elif defined(__sh__)
    #define xARCH_SUPERH 1
        ///< architecture SuperH
#elif defined(__370__) || defined(__THW_370__) || defined(__s390__) || defined(__s390x__) || \
        defined(__zarch__)|| defined(__SYSC_ZARCH__)
    #define xARCH_SYSTEMZ 1 // ???
        ///< architecture SystemZ
#elif defined(_TMS320C2XX) || defined(__TMS320C2000__) || defined(_TMS320C5X) || \
        defined(__TMS320C55X__) || defined(_TMS320C6X) || defined(__TMS320C6X__)
    #define xARCH_TMS320 1 // ???
        ///< architecture TMS320
#elif defined(__TMS470__)
    #define xARCH_TMS470 1 // ???
        ///< architecture TMS470
#else
    #error xLib: unsupported architecture
#endif

//-------------------------------------------------------------------------------------------------
// OS bits architecture
#if   defined(xARCH_ARM) || defined(xARCH_BLACKFIN) || defined(xARCH_INTEL_X86) || \
        defined(xARCH_MOTOROLA_68K) || defined(xARCH_SUPERH)
    #define xARCH_BITS_32 1
        ///< architecture 32-bit
#elif defined(xARCH_ALPHA) || defined(xARCH_AMD64) || defined(xARCH_ARM64) || \
        defined(xARCH_HP_PA_RISC) || defined(xARCH_IA64) || defined(xARCH_MIPS) || \
        defined(xARCH_POWERPC) || defined(xARCH_SPARC)
    #define xARCH_BITS_64 1
        ///< architecture 64-bit
#else
    #error xLib: unsupported bits architecture
#endif

//-------------------------------------------------------------------------------------------------
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
#elif defined(__clang__)
    // xCOMPILER_CLANG also __GNUC__
    #define xCOMPILER_CLANG    1
    #define xCOMPILER_GNUC     1
        ///< compiler Clang
#elif defined(__GNUC__)
    #define xCOMPILER_GNUC     1
        ///< compiler GNU C/C++
#else
    #error xLib: unsupported compiler
#endif

//-------------------------------------------------------------------------------------------------
// compiler version
#define xVER_FULL(major, minor, patch) \
    (major * 10000 + minor * 100 + patch)
    ///< version builder

// xCOMPILER_MINGW
#define xCOMPILER_MINGW32_VER_MAJOR   __MINGW32_MAJOR_VERSION
#define xCOMPILER_MINGW32_VER_MINOR   __MINGW32_MINOR_VERSION
#define xCOMPILER_MINGW32_VER \
    xVER_FULL(xCOMPILER_MINGW32_VER_MAJOR, xCOMPILER_MINGW32_VER_MINOR, 0)

#define xCOMPILER_MINGW64_VER_MAJOR   __MINGW64_VERSION_MAJOR // defined if <stdlib.h> is included
#define xCOMPILER_MINGW64_VER_MINOR   __MINGW64_VERSION_MINOR
#define xCOMPILER_MINGW64_VER\
    xVER_FULL(xCOMPILER_MINGW64_VER_MAJOR, xCOMPILER_MINGW64_VER_MINOR, 0)

// xCOMPILER_MS
#define xCOMPILER_MS_VER              _MSC_VER

// xCOMPILER_CODEGEAR
#define xCOMPILER_CODEGEAR_VER        __CODEGEARC__

// xCOMPILER_CLANG
#define xCOMPILER_CLANG_VER_MAJOR      __clang_major__
#define xCOMPILER_CLANG_VER_MINOR      __clang_minor__
#define xCOMPILER_CLANG_VER_PATCHLEVEL __clang_patchlevel__
#define xCOMPILER_CLANG_VER \
    xVER_FULL(xCOMPILER_CLANG_VER_MAJOR, xCOMPILER_CLANG_VER_MINOR, xCOMPILER_CLANG_VER_PATCHLEVEL)

// xCOMPILER_GNUC
#define xCOMPILER_GNUC_VER_MAJOR      __GNUC__
#define xCOMPILER_GNUC_VER_MINOR      __GNUC_MINOR__
#define xCOMPILER_GNUC_VER_PATCHLEVEL __GNUC_PATCHLEVEL__
#define xCOMPILER_GNUC_VER \
    xVER_FULL(xCOMPILER_GNUC_VER_MAJOR, xCOMPILER_GNUC_VER_MINOR, xCOMPILER_GNUC_VER_PATCHLEVEL)

//-------------------------------------------------------------------------------------------------
// standard C libraries
#if xENV_WIN
    // TODO: xSysDefines - standard C libraries
    #if   xCOMPILER_MINGW
        #include <bits/c++config.h> // standard C++ libraries
    #endif

    #if defined(__MSVCRT__)
        #define xSTD_LIBC_MSVCRT 1
            ///< Microsoft CRT
    #endif
#elif xENV_UNIX
    #if xOS_FREEBSD
        // TODO: xSysDefines - standard C libraries
    #else
        #include <features.h> // standard C libraries
    #endif

    #include <bits/c++config.h> // standard C++ libraries
#elif xENV_APPLE
    #include <bits/c++config.h> // standard C++ libraries
#endif

#if xENV_WIN
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

//-------------------------------------------------------------------------------------------------
// TODO: xSysDefines - standard C libraries versions
#define xSTD_LIBC_GNU_VER_MAJOR __GLIBC__
#define xSTD_LIBC_GNU_VER_MINOR __GLIBC_MINOR__

#define xSTD_LIBC_UC_VER        0
#define xSTD_LIBC_VMS_VER       0
#define xSTD_LIBC_ZOS_VER       0

//-------------------------------------------------------------------------------------------------
// standard C++ libraries
#if xENV_WIN
    #if defined(__GLIBCXX__)
        #define xSTD_LIBCPP_GNUSTDCPP  1
            ///< GNU libstdc++
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

//-------------------------------------------------------------------------------------------------
// TODO: xSysDefines - standard C++ libraries versions
#define xSTD_LIBCPP_GNU_VER 0
#define xSTD_LIBCPP_UC_VER  0
#define xSTD_LIBCPP_VMS_VER 0
#define xSTD_LIBCPP_ZOS_VER 0

//-------------------------------------------------------------------------------------------------
// static, share library
// NOTE: In Unix this defines (_LIB, _DLL) must be set from Makefile
#if   defined(_LIB)
    #define xLIB 1
        ///< static library
#elif defined(_DLL)
    #define xDLL 1
        ///< dynamic-link library
#else
    #define xEXE 1
        ///< executable binary
#endif

//-------------------------------------------------------------------------------------------------
// unicode, ansi
#if defined(UNICODE) || defined(_UNICODE)
    #define xUNICODE 1
        ///< unicode
#else
    #define xANSI    1
        ///< ansi
#endif

//-------------------------------------------------------------------------------------------------
// debug, release build
#if defined(NDEBUG) || defined(_NDEBUG)
    #define xBUILD_RELEASE 1
        ///< release build
#else
    #define xBUILD_DEBUG   1
        ///< debug build
#endif

//-------------------------------------------------------------------------------------------------
#endif // xLib_xSysDefinesH
