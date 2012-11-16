/**
 * \file  xConfig.h
 * \brief configurations for xLib
 */


#ifndef xLib_Common_xConfigH
#define xLib_Common_xConfigH
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN
    #if xCOMPILER_MS
        #include <SDKDDKVer.h>
    #endif

    #if !defined(WIN32_LEAN_AND_MEAN)
        #define WIN32_LEAN_AND_MEAN 1
    #endif

    #if !defined(STRICT)
        #define STRICT 1
    #endif

    // Required for VS 2008 (fails on XP and Win2000 without this fix)
    #if xTEMP_DISABLED
        #if !defined(_WIN32_WINNT)
            #define _WIN32_WINNT 0x0600
        #endif

        #if WINVER
            #undef  WINVER
            #define WINVER 0x0600
        #else
            #define WINVER 0x0600
        #endif

        #if _WIN32_WINNT
            #undef  _WIN32_WINNT
            #define _WIN32_WINNT 0x0600
        #else
            #define _WIN32_WINNT 0x0600
        #endif
    #endif

    // OBM_ (#include <winuser.h>)
    #if !defined(OEMRESOURCE)
        #define OEMRESOURCE 1
    #endif

    // xCOMPILER_MS
    #if xCOMPILER_MS
        #pragma warning (disable: 4996)    // function or variable may be unsafe (deprecated)
        #pragma warning (disable: 4355)    // 'this' : used in base member initializer list
        #pragma warning (disable: 4101)    // 'e' : unreferenced local variable

        #if !defined(VC_EXTRALEAN)
            #define VC_EXTRALEAN 1
        #endif
    #endif

    // xCOMPILER_MINGW32
    #if xCOMPILER_MINGW32

    #endif

    // xCOMPILER_CODEGEAR
    #if xCOMPILER_CODEGEAR
        #pragma option -w-8027  // function not expanded inline
        #pragma option -w-8057  // parameter is never used
        #pragma option -w-8058  // cannot create pre-compiled header: initialized data in header
        #pragma option -w-8004  // is assigned a value that is never used
        #pragma option -w-8008  // Condition is always true
    #endif

    #define _CRT_SECURE_NO_WARNINGS         1
        ///< disable Win CRT warnings

    #define _SCL_SECURE_NO_WARNINGS         1
        ///< disable Win SCL warnings
#elif xOS_ENV_UNIX
    #if !defined(_GNU_SOURCE)
        #define _GNU_SOURCE 1
    #endif
#endif


#define xUSING_NAMESPACE_NXLIB          1
    ///< automatically include the NxLib namespace

#define xDEBUG_USE_PROMPT_DIALOG        1
    ///< debug prompt dialog:
    ///<    0 - don't stop executing, pass throw dialog prompt
    ///<    1 - stop executing on dialog prompt, wait for user choice

// log mode (only one mode can be activated)
#define xDEBUG_MODE_MSGBOX_PLAIN        0
    ///< debug mode "message box with plain text"
#define xDEBUG_MODE_MSGBOX_FORMATED     0
    ///< debug mode "message box with formated text"
#define xDEBUG_MODE_STDOUT_PLAIN        1
    ///< debug mode "std::out with plain text"
#define xDEBUG_MODE_LOGGING_PLAIN       0
    ///< debug mode "logging with plain text"
#define xDEBUG_MODE_NO                  0
    ///< debug mode "no debugging"

#define xIS_COMPILE_TIME_TRACING        0
    ///< is compile time tracing

#define xIS_AUTO_LINKING                0
    ///< auto linkage

#define xTEST_PRIVATE_DATA              0
    ///< for tests private data

#define xTEST_BLOCK_WITH_TRACE_POINT    0
    ///< test block uses with trace point

#define xNEW_NO_STD_THROW               0
    ///< new with std::notrow
//---------------------------------------------------------------------------
#endif  //xLib_Common_xConfigH
