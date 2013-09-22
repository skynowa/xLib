/**
 * \file  xTracing.h
 * \brief compile time tracing
 */


#pragma once

//------------------------------------------------------------------------------
#if xIS_COMPILE_TIME_TRACING
    //--------------------------------------------------
    // OS environment
    #if   xOS_ENV_WIN
        #pragma message("xLib: xOS_ENV_WIN")
    #elif xOS_ENV_UNIX
        #pragma message("xLib: xOS_ENV_UNIX")
    #elif xOS_ENV_BSD
        #pragma message("xLib: xOS_ENV_BSD")
    #elif xOS_ENV_MAC
        #pragma message("xLib: xOS_ENV_MAC")
    #else
        #pragma message("xLib: unsupported OS environment")
    #endif

    //--------------------------------------------------
    // OS family
    #if   xOS_WIN
        #pragma message("xLib: xOS_WIN")
    #elif xOS_LINUX
        #pragma message("xLib: xOS_LINUX")
    #elif xOS_FREEBSD
        #pragma message("xLib: xOS_FREEBSD")
    #elif xOS_MACOS
        #pragma message("xLib: xOS_MACOS")
    #else
        #pragma message("xLib: unsupported OS")
    #endif

    //--------------------------------------------------
    // OS architecture
    #if   xARCH_X86
        #pragma message("xLib: xARCH_X86")
    #elif xARCH_X64
        #pragma message("xLib: xARCH_X64")
    #else
        #pragma message("xLib: unsupported architectures")
    #endif

    //--------------------------------------------------
    // Compilers
    #if   xCOMPILER_MINGW
        #pragma message("xLib: xCOMPILER_MINGW")
    #elif xCOMPILER_MS
        #pragma message("xLib: xCOMPILER_MS")
    #elif xCOMPILER_CODEGEAR
        #pragma message("xLib: xCOMPILER_CODEGEAR")
    #elif xCOMPILER_GNUC
        #pragma message("xLib: xCOMPILER_GNUC")
    #else
        #pragma message("xLib: unsupported compiler")
    #endif

    //--------------------------------------------------
    // standard C libraries
    #if   xSTD_LIBC_MSVCRT
        #pragma message("xLib: xSTD_LIBC_MSVCRT")
    #elif xSTD_LIBC_GNU
        #pragma message("xLib: xSTD_LIBC_GNU")
    #elif xSTD_LIBC_UC
        #pragma message("xLib: xSTD_LIBC_UC")
    #elif xSTD_LIBC_VMS
        #pragma message("xLib: xSTD_LIBC_VMS")
    #elif xSTD_LIBC_ZOS
        #pragma message("xLib: xSTD_LIBC_ZOS")
    #else
        #pragma message("xLib: unsupported standard C library")
    #endif

    //--------------------------------------------------
    // standard C++ libraries
    #if   xSTD_LIBCPP_GNUSTDCPP
        #pragma message("xLib: xSTD_LIBCPP_GNUSTDCPP")
    #elif XSTD_LIBCPP_DINKUMWARE
        #pragma message("xLib: XSTD_LIBCPP_DINKUMWARE")
    #elif xSTD_LIBCPP_GNUSTDCPP
        #pragma message("xLib: xSTD_LIBCPP_GNUSTDCPP")
    #elif xSTD_LIBCPP_INTEL
        #pragma message("xLib: xSTD_LIBCPP_INTEL")
    #elif XSTD_LIBCPP_LIBCPP
        #pragma message("xLib: XSTD_LIBCPP_LIBCPP")
    #else
        #pragma message("xLib: unsupported standard C++ library")
    #endif

    //--------------------------------------------------
    // static, share library, executable
    #if   xLIB
        #pragma message("xLib: xLIB")
    #elif xDLL
        #pragma message("xLib: xDLL")
    #elif xEXE
        #pragma message("xLib: xEXE")
    #else
        #pragma message("xLib: unsupported binary type")
    #endif

    //--------------------------------------------------
    // unicode, ansi
    #if xUNICODE
        #pragma message("xLib: xUNICODE")
    #else
        #pragma message("xLib: xANSI")
    #endif

    //--------------------------------------------------
    // debug mode
    #if   xDEBUG_MODE_MSGBOX_PLAIN
        #pragma message("xLib: xDEBUG_MODE_MSGBOX_PLAIN")
    #elif xDEBUG_MODE_STDOUT_PLAIN
        #pragma message("xLib: xDEBUG_MODE_STDOUT_PLAIN")
    #elif xDEBUG_MODE_LOGGING_PLAIN
        #pragma message("xLib: xDEBUG_MODE_LOGGING_PLAIN")
    #elif xDEBUG_MODE_NO
        #pragma message("xLib: xDEBUG_MODE_NO")
    #else
        #pragma message("xLib: unsupported debug mode")
    #endif

    //--------------------------------------------------
    // build mode
    #if   xBUILD_DEBUG
        #pragma message("xLib: xBUILD_DEBUG")
    #elif xBUILD_RELEASE
        #pragma message("xLib: xBUILD_RELEASE")
    #else
        #pragma message("xLib: unsupported build")
    #endif

#endif
//------------------------------------------------------------------------------
