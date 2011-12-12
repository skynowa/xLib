/**
 * \file  xTracing.h
 * \brief compile time tracing
 */


#ifndef xLib_Common_xTracingH
#define xLib_Common_xTracingH
//---------------------------------------------------------------------------
#if xIS_COMPILE_TIME_TRACING
    //--------------------------------------------------
    //OS family
    #if   xOS_WIN
        #pragma message("xLib: xOS_WIN")
    #elif xOS_LINUX
        #pragma message("xLib: xOS_LINUX")
    #elif xOS_FREEBSD
        #pragma message("xLib: xOS_FREEBSD")
    #else
        #pragma message("xLib: unsupported OS")
    #endif

    //--------------------------------------------------
    //OS environment
    #if   xOS_ENV_WIN
        #pragma message("xLib: xOS_ENV_WIN")
    #elif xOS_ENV_UNIX
        #pragma message("xLib: xOS_ENV_UNIX")
    #elif xOS_ENV_BSD
        #pragma message("xLib: xOS_ENV_BSD")
    #else
        #pragma message("xLib: unsupported OS environment")
    #endif

    //--------------------------------------------------
    //OS architecture
    #if   xCPU_32BIT
        #pragma message("xLib: xCPU_32BIT")
    #elif xCPU_64BIT
        #pragma message("xLib: xCPU_64BIT")
    #else
        #pragma message("xLib: unsupported architectures")
    #endif

    //--------------------------------------------------
    //Compilers
    #if   xCOMPILER_MINGW32
        #pragma message("xLib: xCOMPILER_MINGW32")
    #elif xCOMPILER_MS
        #pragma message("xLib: xCOMPILER_MS")
    #elif xCOMPILER_CODEGEAR
        #pragma message("xLib: xCOMPILER_CODEGEAR")
    #elif xCOMPILER_INTEL
        #pragma message("xLib: xCOMPILER_INTEL")
    #elif xCOMPILER_GNUC
        #pragma message("xLib: xCOMPILER_GNUC")
    #else
        #pragma message("xLib: unsupported compiler")
    #endif

    //--------------------------------------------------
    //standard C libraries
    #if   xSTD_LIBC_GNU
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
    //standard C++ libraries
    #if   XSTD_LIBCPP_DINKUMWARE
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
    //unicode, ansi
    #if xUNICODE
        #pragma message("xLib: xUNICODE")
    #else
        #pragma message("xLib: xANSI")
    #endif

    //--------------------------------------------------
    //debug mode
    #if   xDEBUG_MODE_MSGBOX_PLAIN
        #pragma message("xLib: xDEBUG_MODE_MSGBOX_PLAIN")
    #elif xDEBUG_MODE_MSGBOX_FORMATED
        #pragma message("xLib: xDEBUG_MODE_MSGBOX_FORMATED")
    #elif xDEBUG_MODE_STDOUT_PLAIN
        #pragma message("xLib: xDEBUG_MODE_STDOUT_PLAIN")
    #elif xDEBUG_MODE_STDOUT_HTML
        #pragma message("xLib: xDEBUG_MODE_STDOUT_HTML")
    #elif xDEBUG_MODE_LOGGING_PLAIN
        #pragma message("xLib: xDEBUG_MODE_LOGGING_PLAIN")
    #elif xDEBUG_MODE_LOGGING_HTML
        #pragma message("xLib: xDEBUG_MODE_LOGGING_HTML")
    #elif xDEBUG_MODE_NOLOGGING
        #pragma message("xLib: xDEBUG_MODE_NOLOGGING")
    #elif xDEBUG_MODE_NO
        #pragma message("xLib: xDEBUG_MODE_NO")
    #else
        #pragma message("xLib: unsupported debug mode")
    #endif

    //--------------------------------------------------
    //debug mode
    #if   xBUILD_DEBUG
        #pragma message("xLib: xBUILD_DEBUG")
    #elif xBUILD_RELEASE
        #pragma message("xLib: xBUILD_RELEASE")
    #else
        #pragma message("xLib: unsupported build")
    #endif

#endif
//---------------------------------------------------------------------------
#endif //xLib_Common_xTracingH
