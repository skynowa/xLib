/**
 * \file  SysDefines.h
 * \brief predefined macros
 */


#pragma once

#include <cstdlib> // compilers
#include <climits> // standard C libraries
//-------------------------------------------------------------------------------------------------
///@name Utils
///@{
#define xVER_FULL(major, minor, patch) \
    (major * 10000 + minor * 100 + patch)
    ///< version builder
#define xVER_FULL_STR(major, minor, patch) \
    (xSTRINGIZE(major) xT(".") xSTRINGIZE(minor) xT(".") xSTRINGIZE(patch))
    ///< version builder

#if !defined(KERNEL_VERSION)
    #define xLINUX_KERNEL_VER(a, b, c) (((a) << 16) + ((b) << 8) + (c))
#else
    #define xLINUX_KERNEL_VER KERNEL_VERSION
#endif
    ///< get Linux kernel version
///@}
//-------------------------------------------------------------------------------------------------
///@name Language standards
///@{
#if defined(__STDC__)
    #define xLANG_C89 1
        ///< ANSI X3.159-1989
#endif

#if defined(__STDC_VERSION__)
    #define xLANG_C90 1
        ///< ISO/IEC 9899:1990
#endif

#if (__STDC_VERSION__ >= 199409L)
    #define xLANG_C94 1
        ///< ISO/IEC 9899-1:1994
#endif

#if (__STDC_VERSION__ >= 199901L)
    #define xLANG_C99 1
        ///< ISO/IEC 9899:1999
#endif

#if (__STDC_VERSION__ >= 201112L)
    #define xLANG_C11 1
        ///< ISO/IEC 9899:2011
#endif

#if (__cplusplus >= 199711L)
    #define xLANG_CPP98 1
        ///< ISO/IEC 14882:1998
#endif

#if (__cplusplus >= 201103L)
	// TODO: xLANG_CPP11 (Android)
	#define xLANG_CPP11 1
		///< ISO/IEC 14882:2011
#endif

#if (__cplusplus_cli >= 200406L)
    #define xLANG_CPP_CLI 1
        ///< ECMA-372
#endif

#if defined(__embedded_cplusplus)
    #define xLANG_ECPP 1
        ///< Embedded C++
#endif
///@}
//-------------------------------------------------------------------------------------------------
///@name OS environment
///@{
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
///@}
//-------------------------------------------------------------------------------------------------
///@name OS family
///@{
#if   xENV_WIN
    #define xOS_WIN 1
        ///< OS Windows
#elif xENV_UNIX
    #if   xENV_LINUX
        #define xOS_LINUX 1
            ///< OS Linux
        #if defined(__ANDROID__)
            #define xOS_ANDROID 1
                ///< OS Android
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

    // ANDROID: xOS_ANDROID
#if !xOS_ANDROID
    #define xTODO_ANDROID 1
#endif
///@}
//-------------------------------------------------------------------------------------------------
///@name OS version
///@{
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

#define xOS_LINUX_VER   LINUX_VERSION_CODE
    ///< Linux version

#define xOS_ANDROID_VER __ANDROID_API__
    ///< Android version from <android/api-level.h>

#define xOS_FREEBSD_VER __FreeBSD__
    ///< FreeBSD version
///@}
//-------------------------------------------------------------------------------------------------
///@name OS architecture
///@{
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
///@}
//-------------------------------------------------------------------------------------------------
///@name OS bits architecture
///@{
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
///@}
//-------------------------------------------------------------------------------------------------
///@name Compiler types
///@{
#if   defined(__MINGW32__) || defined(__MINGW64__)
    #define xCOMPILER_MINGW 1
        ///< compiler MinGW

    ///@name Compiler version
    ///@{
    #define xCOMPILER_MINGW32_VER_MAJOR __MINGW32_MAJOR_VERSION
    #define xCOMPILER_MINGW32_VER_MINOR __MINGW32_MINOR_VERSION
    #define xCOMPILER_MINGW32_VER_PATCH 0
    #define xCOMPILER_MINGW32_VER \
        xVER_FULL(xCOMPILER_MINGW32_VER_MAJOR, xCOMPILER_MINGW32_VER_MINOR, xCOMPILER_MINGW32_VER_PATCH)
    #define xCOMPILER_MINGW32_VER_STR \
        xVER_FULL_STR(xCOMPILER_MINGW32_VER_MAJOR, xCOMPILER_MINGW32_VER_MINOR, xCOMPILER_MINGW32_VER_PATCH)

    #define xCOMPILER_MINGW64_VER_MAJOR __MINGW64_VERSION_MAJOR // defined if <stdlib.h> is included
    #define xCOMPILER_MINGW64_VER_MINOR __MINGW64_VERSION_MINOR
    #define xCOMPILER_MINGW64_VER_PATCH 0
    #define xCOMPILER_MINGW64_VER \
        xVER_FULL(xCOMPILER_MINGW64_VER_MAJOR, xCOMPILER_MINGW64_VER_MINOR, xCOMPILER_MINGW64_VER_PATCH)
    #define xCOMPILER_MINGW64_VER_STR \
        xVER_FULL_STR(xCOMPILER_MINGW64_VER_MAJOR, xCOMPILER_MINGW64_VER_MINOR, xCOMPILER_MINGW64_VER_PATCH)
    ///@}
#elif defined(_MSC_VER) || defined(_MSC_FULL_VER) || defined(_MSC_BUILD)
    #define xCOMPILER_MS 1
        ///< compiler Microsoft Visual C++

    ///@name Compiler version
    ///@{
    #define xCOMPILER_MS_VER_MAJOR _MSC_VER
    #define xCOMPILER_MS_VER_MINOR 0
    #define xCOMPILER_MS_VER_PATCH 0
    #define xCOMPILER_MS_VER \
        xVER_FULL(xCOMPILER_MS_VER_MAJOR, xCOMPILER_MS_VER_MINOR, xCOMPILER_MS_VER_MINOR)
    #define xCOMPILER_MS_VER_STR \
        xVER_FULL_STR(xCOMPILER_MS_VER_MAJOR, xCOMPILER_MS_VER_MINOR, xCOMPILER_MS_VER_MINOR)
    ///@}
#elif defined(__BORLANDC__) || defined(__CODEGEARC__)
    #define xCOMPILER_CODEGEAR 1
        ///< compiler Borland C++, Code Gear

    ///@name Compiler version
    ///@{
    #define xCOMPILER_CODEGEAR_VER_MAJOR __CODEGEARC__
    #define xCOMPILER_CODEGEAR_VER_MINOR 0
    #define xCOMPILER_CODEGEAR_VER_PATCH 0
    #define xCOMPILER_CODEGEAR_VER \
        xVER_FULL(xCOMPILER_CODEGEAR_VER_MAJOR, xCOMPILER_CODEGEAR_VER_MINOR, xCOMPILER_CODEGEAR_VER_MINOR)
    #define xCOMPILER_CODEGEAR_VER_STR \
        xVER_FULL_STR(xCOMPILER_CODEGEAR_VER_MAJOR, xCOMPILER_CODEGEAR_VER_MINOR, xCOMPILER_CODEGEAR_VER_MINOR)
    ///@}
#elif defined(__clang__)
    // xCOMPILER_CLANG also __GNUC__
    #define xCOMPILER_CLANG 1
    #define xCOMPILER_GNUC 1
        ///< compiler Clang

    ///@name Compiler version
    ///@{
    #define xCOMPILER_CLANG_VER_MAJOR __clang_major__
    #define xCOMPILER_CLANG_VER_MINOR __clang_minor__
    #define xCOMPILER_CLANG_VER_PATCH __clang_patchlevel__
    #define xCOMPILER_CLANG_VER \
        xVER_FULL(xCOMPILER_CLANG_VER_MAJOR, xCOMPILER_CLANG_VER_MINOR, xCOMPILER_CLANG_VER_PATCH)
    #define xCOMPILER_CLANG_VER_STR \
        xVER_FULL_STR(xCOMPILER_CLANG_VER_MAJOR, xCOMPILER_CLANG_VER_MINOR, xCOMPILER_CLANG_VER_PATCH)
    ///@}
#elif defined(__GNUC__)
    #define xCOMPILER_GNUC 1
        ///< compiler GNU C/C++

    ///@name Compiler version
    ///@{
    #define xCOMPILER_GNUC_VER_MAJOR __GNUC__
    #define xCOMPILER_GNUC_VER_MINOR __GNUC_MINOR__
    #define xCOMPILER_GNUC_VER_PATCH __GNUC_PATCHLEVEL__
    #define xCOMPILER_GNUC_VER \
        xVER_FULL(xCOMPILER_GNUC_VER_MAJOR, xCOMPILER_GNUC_VER_MINOR, xCOMPILER_GNUC_VER_PATCH)
    #define xCOMPILER_GNUC_VER_STR \
        xVER_FULL_STR(xCOMPILER_GNUC_VER_MAJOR, xCOMPILER_GNUC_VER_MINOR, xCOMPILER_GNUC_VER_PATCH)
    ///@}
#else
    #error xLib: unsupported compiler
#endif
///@}
//-------------------------------------------------------------------------------------------------
#define xCOMPILER_FLAGS \
	cmXLIB_COMPILER_FLAGS
	///< Compiler flags
#define xXLIB_LIBRARIES \
	cmXLIB_LIBRARIES
	///< xLib linked linraries
//-------------------------------------------------------------------------------------------------
///@name Standard C libraries
///@{
#if   xENV_WIN
    #if xCOMPILER_MINGW
        #include <bits/c++config.h>
    #endif
#elif xENV_UNIX
	#if cmHAVE_FEATURES_H
		#include <features.h>
		#include <bits/c++config.h>
	#else
       /**
        * <features.h>
        *
        * Notice that the <features.h> header file does not exist on all platforms, so it cannot be
        * included without further ado. However, since it is included by other GNU glibc header
        * files, a better way to obtain the above-mentioned macros is to include the <limits.h>
        * header file (see e.g. paragraph 4/6 in ISO/IEC 9899:1999).
        */
		#include <climits>
	#endif
#endif

#if   xENV_WIN
    #if   defined(__MSVCRT__)
        #define xSTD_LIBC_MSVCRT           1
        #define xSTD_LIBC_MSVCRT_VER_MAJOR 0
        #define xSTD_LIBC_MSVCRT_VER_MINOR 0
        #define xSTD_LIBC_MSVCRT_VER_PATCH 0
        #define xSTD_LIBC_MSVCRT_VER \
            xVER_FULL(xSTD_LIBC_MSVCRT_VER_MAJOR, xSTD_LIBC_MSVCRT_VER_MINOR, xSTD_LIBC_MSVCRT_VER_PATCH)
        #define xSTD_LIBC_MSVCRT_VER_STR \
            xVER_FULL_STR(xSTD_LIBC_MSVCRT_VER_MAJOR, xSTD_LIBC_MSVCRT_VER_MINOR, xSTD_LIBC_MSVCRT_VER_PATCH)
            ///< Microsoft CRT
    #elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
        // GNU libstdc++ detect as C library
        #define xSTD_LIBC_GNUSTDC           1
        #define xSTD_LIBC_GNUSTDC_VER_MAJOR __GLIBCXX__
        #define xSTD_LIBC_GNUSTDC_VER_MINOR 0
        #define xSTD_LIBC_GNUSTDC_VER_PATCH 0
        #define xSTD_LIBC_GNUSTDC_VER \
            xVER_FULL(xSTD_LIBC_GNUSTDC_VER_MAJOR, xSTD_LIBC_GNUSTDC_VER_MINOR, xSTD_LIBC_GNUSTDC_VER_PATCH)
        #define xSTD_LIBC_GNUSTDC_VER_STR \
            xVER_FULL_STR(xSTD_LIBC_GNUSTDC_VER_MAJOR, xSTD_LIBC_GNUSTDC_VER_MINOR, xSTD_LIBC_GNUSTDC_VER_PATCH)
            ///< GNU libstdc++
    #else
        #warning xLib: unknown standard C library
    #endif
#elif xENV_UNIX
    #if   defined(__GNU_LIBRARY__) || defined(__GLIBC__)
        #define xSTD_LIBC_GNU           1
        #define xSTD_LIBC_GNU_VER_MAJOR __GLIBC__
        #define xSTD_LIBC_GNU_VER_MINOR __GLIBC_MINOR__
        #define xSTD_LIBC_GNU_VER_PATCH 0
        #define xSTD_LIBC_GNU_VER \
            xVER_FULL(xSTD_LIBC_GNU_VER_MAJOR, xSTD_LIBC_GNU_VER_MINOR, xSTD_LIBC_GNU_VER_PATCH)
        #define xSTD_LIBC_GNU_VER_STR \
            xVER_FULL_STR(xSTD_LIBC_GNU_VER_MAJOR, xSTD_LIBC_GNU_VER_MINOR, xSTD_LIBC_GNU_VER_PATCH)
            ///< GNU glibc
    #elif defined(__UCLIBC__)
        #define xSTD_LIBC_UC           1
        #define xSTD_LIBC_UC_VER_MAJOR __UCLIBC_MAJOR__
        #define xSTD_LIBC_UC_VER_MINOR __UCLIBC_MINOR__
        #define xSTD_LIBC_UC_VER_PATCH __UCLIBC_SUBLEVEL__
        #define xSTD_LIBC_UC_VER \
            xVER_FULL(xSTD_LIBC_UC_VER_MAJOR, xSTD_LIBC_UC_VER_MINOR, xSTD_LIBC_UC_VER_PATCH)
        #define xSTD_LIBC_UC_VER_STR \
            xVER_FULL_STR(xSTD_LIBC_UC_VER_MAJOR, xSTD_LIBC_UC_VER_MINOR, xSTD_LIBC_UC_VER_PATCH)
            ///< uClibc
    #elif defined(__CRTL_VER)
        #define xSTD_LIBC_VMS           1
        #define xSTD_LIBC_VMS_VER_MAJOR __CRTL_VER
        #define xSTD_LIBC_VMS_VER_MINOR 0
        #define xSTD_LIBC_VMS_VER_PATCH 0
        #define xSTD_LIBC_VMS_VER \
            xVER_FULL(xSTD_LIBC_VMS_VER_MAJOR, xSTD_LIBC_VMS_VER_MINOR, xSTD_LIBC_VMS_VER_PATCH)
        #define xSTD_LIBC_VMS_VER_STR \
            xVER_FULL_STR(xSTD_LIBC_VMS_VER_MAJOR, xSTD_LIBC_VMS_VER_MINOR, xSTD_LIBC_VMS_VER_PATCH)
            ///< VMS libc
    #elif defined(__LIBREL__) || defined(__TARGET_LIB__)
        #define xSTD_LIBC_ZOS           1
        #define xSTD_LIBC_ZOS_VER_MAJOR __LIBREL__
        #define xSTD_LIBC_ZOS_VER_MINOR 0
        #define xSTD_LIBC_ZOS_VER_PATCH 0
        #define xSTD_LIBC_ZOS_VERSTR \
            xVER_FULL(xSTD_LIBC_ZOS_VER_MAJOR, xSTD_LIBC_ZOS_VER_MINOR, xSTD_LIBC_ZOS_VER_PATCH)
        #define xSTD_LIBC_ZOS_VER_STR \
            xVER_FULL_STR(xSTD_LIBC_ZOS_VER_MAJOR, xSTD_LIBC_ZOS_VER_MINOR, xSTD_LIBC_ZOS_VER_PATCH)
            ///< z/OS libc
    #elif defined(__BIONIC__)
        #define xSTD_LIBC_BIONIC           1
        #define xSTD_LIBC_BIONIC_VER_MAJOR 0
        #define xSTD_LIBC_BIONIC_VER_MINOR 0
        #define xSTD_LIBC_BIONIC_VER_PATCH 0
        #define xSTD_LIBC_BIONIC_VER \
            xVER_FULL(xSTD_LIBC_BIONIC_VER_MAJOR, xSTD_LIBC_BIONIC_VER_MINOR, xSTD_LIBC_BIONIC_VER_PATCH)
        #define xSTD_LIBC_BIONIC_VER_STR \
            xVER_FULL_STR(xSTD_LIBC_BIONIC_VER_MAJOR, xSTD_LIBC_BIONIC_VER_MINOR, xSTD_LIBC_BIONIC_VER_PATCH)
            ///< Bionic libc
    #elif defined(__KLIBC__)
        #define xSTD_LIBC_K           1
        #define xSTD_LIBC_K_VER_MAJOR __KLIBC__
        #define xSTD_LIBC_K_VER_MINOR __KLIBC_MINOR__
        #define xSTD_LIBC_K_VER_PATCH __KLIBC_PATCHLEVEL__
        #define xSTD_LIBC_K_VER \
            xVER_FULL(xSTD_LIBC_K_VER_MAJOR, xSTD_LIBC_K_VER_MINOR, xSTD_LIBC_K_VER_PATCH)
        #define xSTD_LIBC_K_VER_STR \
            xVER_FULL_STR(xSTD_LIBC_K_VER_MAJOR, xSTD_LIBC_K_VER_MINOR, xSTD_LIBC_K_VER_PATCH)
            ///< klibc
    #else
        /// #pragma message "xLib: unknown standard C library"
    #endif
#endif
///@}
//-------------------------------------------------------------------------------------------------
///@name Standard C++ libraries
///@{
#if   xENV_WIN
    #if   defined(__MSVCRT__)
        #define xSTD_LIBCPP_MSVCRT           1
        #define xSTD_LIBCPP_MSVCRT_VER_MAJOR 0
        #define xSTD_LIBCPP_MSVCRT_VER_MINOR 0
        #define xSTD_LIBCPP_MSVCRT_VER_PATCH 0
        #define xSTD_LIBCPP_MSVCRT_VER \
            xVER_FULL(xSTD_LIBCPP_MSVCRT_VER_MAJOR, xSTD_LIBCPP_MSVCRT_VER_MINOR, xSTD_LIBCPP_MSVCRT_VER_PATCH)
        #define xSTD_LIBCPP_MSVCRT_VER_STR \
            xVER_FULL_STR(xSTD_LIBCPP_MSVCRT_VER_MAJOR, xSTD_LIBCPP_MSVCRT_VER_MINOR, xSTD_LIBCPP_MSVCRT_VER_PATCH)
            ///< Microsoft CRT
    #elif defined(__GLIBCXX__)
        #define xSTD_LIBCPP_GNUSTDCPP           1
        #define xSTD_LIBCPP_GNUSTDCPP_VER_MAJOR __GLIBCXX__
        #define xSTD_LIBCPP_GNUSTDCPP_VER_MINOR 0
        #define xSTD_LIBCPP_GNUSTDCPP_VER_PATCH 0
        #define xSTD_LIBCPP_GNUSTDCPP_VER \
            xVER_FULL(xSTD_LIBCPP_GNUSTDCPP_VER_MAJOR, xSTD_LIBCPP_GNUSTDCPP_VER_MINOR, xSTD_LIBCPP_GNUSTDCPP_VER_PATCH)
        #define xSTD_LIBCPP_GNUSTDCPP_VER_STR \
            xVER_FULL_STR(xSTD_LIBCPP_GNUSTDCPP_VER_MAJOR, xSTD_LIBCPP_GNUSTDCPP_VER_MINOR, xSTD_LIBCPP_GNUSTDCPP_VER_PATCH)
            ///< GNU libstdc++
    #endif
#elif xENV_UNIX
    #if   defined(_CPPLIB_VER)
        #define XSTD_LIBCPP_DINKUMWARE           1
        #define xSTD_LIBCPP_DINKUMWARE_VER_MAJOR _CPPLIB_VER
        #define xSTD_LIBCPP_DINKUMWARE_VER_MINOR 0
        #define xSTD_LIBCPP_DINKUMWARE_VER_PATCH 0
        #define xSTD_LIBCPP_DINKUMWARE_VER \
            xVER_FULL(xSTD_LIBCPP_DINKUMWARE_VER_MAJOR, xSTD_LIBCPP_DINKUMWARE_VER_MINOR, xSTD_LIBCPP_DINKUMWARE_VER_PATCH)
        #define xSTD_LIBCPP_DINKUMWARE_VER_STR \
            xVER_FULL_STR(xSTD_LIBCPP_DINKUMWARE_VER_MAJOR, xSTD_LIBCPP_DINKUMWARE_VER_MINOR, xSTD_LIBCPP_DINKUMWARE_VER_PATCH)
            ///< Dinkumware
    #elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
        #define xSTD_LIBCPP_GNUSTDCPP           1
        #define xSTD_LIBCPP_GNUSTDCPP_VER_MAJOR __GLIBCXX__
        #define xSTD_LIBCPP_GNUSTDCPP_VER_MINOR 0
        #define xSTD_LIBCPP_GNUSTDCPP_VER_PATCH 0
        #define xSTD_LIBCPP_GNUSTDCPP_VER \
            xVER_FULL(xSTD_LIBCPP_GNUSTDCPP_VER_MAJOR, xSTD_LIBCPP_GNUSTDCPP_VER_MINOR, xSTD_LIBCPP_GNUSTDCPP_VER_PATCH)
        #define xSTD_LIBCPP_GNUSTDCPP_VER_STR \
            xVER_FULL_STR(xSTD_LIBCPP_GNUSTDCPP_VER_MAJOR, xSTD_LIBCPP_GNUSTDCPP_VER_MINOR, xSTD_LIBCPP_GNUSTDCPP_VER_PATCH)
            ///< GNU libstdc++
    #elif defined(__INTEL_CXXLIB_ICC)
        #define xSTD_LIBCPP_INTEL           1
        #define xSTD_LIBCPP_INTEL_VER_MAJOR 0
        #define xSTD_LIBCPP_INTEL_VER_MINOR 0
        #define xSTD_LIBCPP_INTEL_VER_PATCH 0
        #define xSTD_LIBCPP_INTEL_VER \
            xVER_FULL(xSTD_LIBCPP_INTEL_VER_MAJOR, xSTD_LIBCPP_INTEL_VER_MINOR, xSTD_LIBCPP_INTEL_VER_PATCH)
        #define xSTD_LIBCPP_INTEL_VER_STR \
            xVER_FULL_STR(xSTD_LIBCPP_INTEL_VER_MAJOR, xSTD_LIBCPP_INTEL_VER_MINOR, xSTD_LIBCPP_INTEL_VER_PATCH)
            ///< Intel C++ Run-Time Libraries
    #elif defined(_LIBCPP_VERSION) || defined(_LIBCPP_ABI_VERSION)
        #define xSTD_LIBCPP_LIBCPP           1
        #define xSTD_LIBCPP_LIBCPP_VER_MAJOR _LIBCPP_ABI_VERSION
        #define xSTD_LIBCPP_LIBCPP_VER_MINOR 0
        #define xSTD_LIBCPP_LIBCPP_VER_PATCH 0
        #define xSTD_LIBCPP_LIBCPP_VERSTR \
            xVER_FULL(xSTD_LIBCPP_LIBCPP_VER_MAJOR, xSTD_LIBCPP_LIBCPP_VER_MINOR, xSTD_LIBCPP_LIBCPP_VER_PATCH)
        #define xSTD_LIBCPP_LIBCPP_VER_STR \
            xVER_FULL_STR(xSTD_LIBCPP_LIBCPP_VER_MAJOR, xSTD_LIBCPP_LIBCPP_VER_MINOR, xSTD_LIBCPP_LIBCPP_VER_PATCH)
            ///< libc++
    #else
        #pragma message "xLib: unknown standard C++ library"
    #endif
#endif
///@}
//-------------------------------------------------------------------------------------------------
///@name Unicode, ansi
///@{
#if defined(UNICODE) || defined(_UNICODE)
    #define xUNICODE 1
        ///< unicode
#else
    #define xANSI 1
        ///< ansi
#endif
///@}
//-------------------------------------------------------------------------------------------------
///@name Debug, release build
///@{
#if defined(NDEBUG) || defined(_NDEBUG)
    #define xBUILD_RELEASE 1
        ///< release build
#else
    #define xBUILD_DEBUG 1
        ///< debug build
#endif
///@}
//-------------------------------------------------------------------------------------------------
///@name Detect third-party libraries
///@{
#if defined(BOOST_VERSION)
    #define xLIB_BOOST 1
        ///< Boost library
#endif

#if defined(QT_VERSION_STR)
    #define xLIB_QT 1
        ///< Qt library
#endif
///@}
//-------------------------------------------------------------------------------------------------
