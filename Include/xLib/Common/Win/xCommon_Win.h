/****************************************************************************
* Class name:  xCommon_Win
* Description: Windows common header for xLib
* File name:   xCommon_Win.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     23.12.2010 23:25:16
*
*****************************************************************************/


#ifndef xLib_Common_Win_xCommon_WinH
#define xLib_Common_Win_xCommon_WinH
//---------------------------------------------------------------------------
//win version
#define xWINVER      WINVER
#define xWIN32_NT4   0x0400    //Windows NT 4.0
#define xWIN32_2K    0x0500    //Windows 2000
#define xWIN32_XP    0x0501    //Windows Server 2003, Windows XP
#define xWIN32_S03   0x0502    //Windows Server 2003 with SP1, Windows XP with SP2
#define xWIN32_VISTA 0x0600    //Windows Vista, Windows Server 2008
#define xWIN32_7     0x0601    //Windows 7, Windows Server 2008 R2


//xCOMPILER_MS
#if defined(xCOMPILER_MS)
	#pragma warning (disable : 4996)    //function or variable may be unsafe (deprecated)
	#pragma warning (disable : 4355)    //'this' : used in base member initializer list
	#pragma warning (disable : 4101)    //'e' : unreferenced local variable

    #define VC_EXTRALEAN

    #if !defined(WIN32_LEAN_AND_MEAN)
        #define WIN32_LEAN_AND_MEAN
    #endif

    ////#define _CRT_SECURE_NO_WARNINGS 
    ////#define _SCL_SECURE_NO_WARNINGS 
    ////#define _SECURE_SCL

    #if !defined(STRICT)
        #define STRICT 1
    #endif

    //Required for VS 2008 (fails on XP and Win2000 without this fix)
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

    //OBM_ (#include <winuser.h>)
    #define OEMRESOURCE

    //Prevent winsock.h #include's
    #define _WINSOCKAPI_
#endif

//xCOMPILER_MINGW32
#if defined(xCOMPILER_MINGW32)

#endif

//xCOMPILER_CODEGEAR
#if defined(xCOMPILER_CODEGEAR)
    #pragma option -w-8027  //function not expanded inline
    #pragma option -w-8057  //parameter is never used
    #pragma option -w-8058  //cannot create pre-compiled header: initialized data in header
    #pragma option -w-8004  //is assigned a value that is never used
    #pragma option -w-8022  //hides virtual function 'Image::Clone()'
    #pragma option -w-8008  //Condition is always true
#endif
//---------------------------------------------------------------------------
#include <winsock2.h>
#include <ws2tcpip.h>

#include <windows.h>
#include <tchar.h>
#include <windowsx.h>
#include <winuser.h>
#include <Objbase.h>
#include <process.h>
#include <Lmcons.h>

#include <sys/locking.h>
#include <io.h>
#include <errno.h>

#if defined(xCOMPILER_CODEGEAR)
    #include <xVCL/xCommon.h>
#endif
//---------------------------------------------------------------------------
#endif  //xLib_Common_Win_xCommon_WinH
