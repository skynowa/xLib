/**
 * \file  xCommon_Win.h
 * \brief Windows common header for xLib
 */


#ifndef xLib_Common_Win_xCommon_WinH
#define xLib_Common_Win_xCommon_WinH
//---------------------------------------------------------------------------
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
    #pragma option -w-8022  // hides virtual function 'Image::Clone()'
    #pragma option -w-8008  // Condition is always true
#endif
//---------------------------------------------------------------------------
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <tchar.h>
#include <windowsx.h>
#include <winuser.h>
#include <objbase.h>
#include <process.h>
#include <lmcons.h>
#include <sys/locking.h>
#include <io.h>
#include <winternl.h>
#include <psapi.h>

#if   xCOMPILER_MINGW32
    #include <intrin.h>
#elif xCOMPILER_MS
    #include <intrin.h>
#elif xCOMPILER_CODEGEAR
    #include <dir.h>
#endif
//---------------------------------------------------------------------------
#endif  //xLib_Common_Win_xCommon_WinH
