/**
 * \file  xConfig_gen.h
 * \brief configurations for xLib
 */


#pragma once

#ifndef xLib_xConfig_genH
#define xLib_xConfig_genH
//-------------------------------------------------------------------------------------------------
#define xHAVE_GIT_REVISION    1
#define xGIT_REVISION_BRANCH  xT("develop")
#define xGIT_REVISION_HASH    xT("d9b82bd")

#define xHAVE_OPENSSL_CRYPTO  1
/* #undef xHAVE_MYSQL */
#define xHAVE_PR_SET_DUMPABLE 1
/* #undef xHAVE_RLIMIT_CORE */
/* #undef xHAVE_PT_DENY_ATTACH */
#define xHAVE_SCHED_GETCPU    1
/* #undef xHAVE_GETCPU */
#define xHAVE_ADDR2LINE       1
#define xHAVE_EXECINFO        1
#define xHAVE_XCB             1

#if xOS_ENV_WIN
    #if xCOMPILER_MS
        #include <SDKDDKVer.h>
    #endif

    #if !defined(WIN32_LEAN_AND_MEAN)
        #define WIN32_LEAN_AND_MEAN 1
    #endif

    #if !defined(STRICT)
        #define STRICT 1
    #endif

    #if xCOMPILER_MS
       /**
        * 4996: function or variable may be unsafe (deprecated)
        * 4355: 'this' : used in base member initializer list
        * 4101: 'e' : unreferenced local variable
        */
        #pragma warning(disable: 4996 4355 4101)

        #if !defined(VC_EXTRALEAN)
            #define VC_EXTRALEAN 1
        #endif
    #endif

    #if xCOMPILER_MINGW

    #endif

    #if xCOMPILER_CODEGEAR
        #pragma option -w-8027  // function not expanded inline
        #pragma option -w-8057  // parameter is never used
        #pragma option -w-8058  // cannot create pre-compiled header: initialized data in header
        #pragma option -w-8004  // is assigned a value that is never used
        #pragma option -w-8008  // Condition is always true
    #endif

    #define _CRT_SECURE_NO_WARNINGS  1
        ///< disable Win CRT warnings

    #define _SCL_SECURE_NO_WARNINGS  1
        ///< disable Win SCL warnings
#elif xOS_ENV_UNIX
    #if !defined(_GNU_SOURCE)
        #define _GNU_SOURCE 1
    #endif
#endif

#define xUSING_NAMESPACE_XLIB     1
    ///< automatically include the xlib namespace

#define xDEBUG_USE_PROMPT_DIALOG  1
    ///< debug prompt dialog:
    ///<    0 - don't stop executing, pass throw dialog prompt
    ///<    1 - stop executing on dialog prompt, wait for user choice

// log mode (only one mode can be activated)
/* #undef xDEBUG_MODE_MSGBOX */
    ///< debug mode "message box with plain text"
#define xDEBUG_MODE_STDOUT        1
    ///< debug mode "std::out with plain text"
/* #undef xDEBUG_MODE_LOG */
    ///< debug mode "logging with plain text"
/* #undef xDEBUG_MODE_NO */
    ///< debug mode "no debugging"

/* #undef xNEW_NO_STD_THROW */
    ///< new with std::notrow

/* #undef xTEST_PRIVATE_DATA */
    ///< for tests private data
#define xTEST_TRACING             1
    ///< use tracing in tests

//-------------------------------------------------------------------------------------------------
#endif // xLib_xConfig_genH
