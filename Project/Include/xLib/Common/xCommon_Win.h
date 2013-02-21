/**
 * \file  xCommon_Win.h
 * \brief Windows common header for xLib
 */


#ifndef xLib_Common_Win_xCommon_WinH
#define xLib_Common_Win_xCommon_WinH
//------------------------------------------------------------------------------
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
#include <psapi.h>
#include <TlHelp32.h>

#if   xCOMPILER_MINGW
    #include <winternl.h>
    #include <intrin.h>
#elif xCOMPILER_MS
    #include <winternl.h>
    #include <intrin.h>
#elif xCOMPILER_CODEGEAR
    #include <dir.h>
#endif
//------------------------------------------------------------------------------
#endif  // xLib_Common_Win_xCommon_WinH
