/**
 * \file  Config_gen.h
 * \brief configurations for xLib
 */


#pragma once

//-------------------------------------------------------------------------------------------------
///@name project type: executable binary, static library, share (dynamic-link) library
///@{
/* #undef cmOPTION_PROJECT_HEADER_ONLY */
#define cmOPTION_PROJECT_LIB_STATIC 1
/* #undef cmOPTION_PROJECT_LIB_SHARE */
/* #undef cmOPTION_PROJECT_LIB_MODULE */
///@}

/* #undef cmOPTION_BUILD_MSG */
    ///< build message

///@name debug mode (only one mode can be activated)
///@{
// log mode (only one mode can be activated)
/* #undef cmOPTION_DEBUG_MODE_MSGBOX */
    ///< debug mode "message box"
#define cmOPTION_DEBUG_MODE_STDOUT 1
    ///< debug mode "std::cout"
/* #undef cmOPTION_DEBUG_MODE_LOG */
    ///< debug mode "logging"
/* #undef cmOPTION_DEBUG_MODE_STDOUT_LOG */
    ///< debug mode "std::cout and log"
/* #undef cmOPTION_DEBUG_MODE_EXCEPTION */
    ///< debug mode "no debugging"
/* #undef cmOPTION_DEBUG_MODE_NO */
    ///< debug mode "no debugging"
///@}

///@name tests
///@{
/* #undef cmOPTION_TEST_PRIVATE */
    ///< for tests private data
#define cmOPTION_TEST_TRACING 1
    ///< use tracing in tests
///@}

//-------------------------------------------------------------------------------------------------
#define CMAKE_BUILD_TYPE xT("RelWithDebInfo")

///@name Git information
///@{
#define cmGIT_REVISION_FOUND 1
#define cmGIT_REVISION_BRANCH xT("master")
#define cmGIT_REVISION_HASH xT("5ee34c6")
///@}

#define cmXLIB_COMPILER_FLAGS xT(" -w -fmax-errors=1 ")
    ///< Compiler flags
#define cmXLIB_LIBRARIES      xT("/usr/lib/x86_64-linux-gnu/libssl.so;/usr/lib/x86_64-linux-gnu/libcrypto.so;/usr/lib/x86_64-linux-gnu/libmysqlclient.so;/usr/lib/x86_64-linux-gnu/libssh2.so;/usr/lib/x86_64-linux-gnu/libxcb.so;/usr/lib/x86_64-linux-gnu/libX11-xcb.so;dl;pthread;rt;m;z")
    ///< xLib linked libraries
#define cmCMAKE_VERSION       xT("3.5.1")
    ///< CMake version

///@name detecting features
///@{
#define cmOPENSSL_CRYPTO_FOUND 1
#define cmPR_SET_DUMPABLE_FOUND 1
#define cmRLIMIT_CORE_FOUND 1
/* #undef cmPT_DENY_ATTACH_FOUND */
#define cmSCHED_GETCPU_FOUND 1
/* #undef cmGETCPU_FOUND */
#define cmGETLOGIN_R_FOUND 1
#define cmGNU_GET_LIBC_FOUND 1
#define cmCS_GNU_LIBPTHREAD_VERSION_FOUND 1
#define cmSCHED_SETAFFINITY_FOUND 1
#define cmGETSID_FOUND 1
#define cmGETPWUID_R_FOUND 1
#define cmSETMNTENT_FOUND 1
#define cmGETMNTENT_R_FOUND 1
#define cmENDMNTENT_FOUND 1
#define cmRAND_R_FOUND 1
#define cmSRANDOM_R_FOUND 1
#define cmRANDOM_R_FOUND 1

#define cmMYSQL_FOUND 1
#define cmEXECINFO_FOUND 1
#define cmXCB_FOUND 1
#define cmADDR2LINE_FOUND 1
#define cmADDR2LINE_FILE_PATH xT("/usr/bin/addr2line")
///@}

//-------------------------------------------------------------------------------------------------
///@name OS specific defines
///@{
#if   xENV_WIN
    #if xCOMPILER_MS
        #include <SDKDDKVer.h>
    #endif

    #if !defined(WIN32_LEAN_AND_MEAN)
        #define WIN32_LEAN_AND_MEAN 1
    #endif
        ///< exclude APIs such as Cryptography, DDE, RPC, Shell, Windows Sockets
    #if !defined(STRICT)
        #undef  NO_STRICT
        #define STRICT 1
    #endif
        ///< type checking
    #define _CRT_SECURE_NO_WARNINGS 1
        ///< disable Win CRT warnings
    #define _SCL_SECURE_NO_WARNINGS 1
        ///< disable Win SCL warnings
    #define _CRT_SECURE_NO_DEPRECATE 1
        ///< don't complain about all the deprecated functions

    #if   xCOMPILER_MINGW
        //
    #elif xCOMPILER_MS
        // Disable warnings
        #pragma warning(disable: 4996) // function or variable may be unsafe (deprecated)
        #pragma warning(disable: 4355) // 'this' : used in base member initializer list
        #pragma warning(disable: 4101) // 'e' : unreferenced local variable

        #if !defined(VC_EXTRALEAN)
            #define VC_EXTRALEAN 1
        #endif
            ///< exclude rarely-used stuff from Windows headers
    #elif xCOMPILER_CODEGEAR
        // Disable warnings
        #pragma option -w-8027  // function not expanded inline
        #pragma option -w-8057  // parameter is never used
        #pragma option -w-8058  // cannot create pre-compiled header: initialized data in header
        #pragma option -w-8004  // is assigned a value that is never used
        #pragma option -w-8008  // Condition is always true
    #elif xCOMPILER_CLANG
        //
    #endif
#elif xENV_UNIX
    #if !defined(_GNU_SOURCE)
        #define _GNU_SOURCE 1
    #endif
#endif
///@}

//-------------------------------------------------------------------------------------------------
