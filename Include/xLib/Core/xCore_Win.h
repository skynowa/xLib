/**
 * \file  xCommon_Win.h
 * \brief Windows common header for xLib
 */


#pragma once

#ifndef xLib_xCore_WinH
#define xLib_xCore_WinH
//-------------------------------------------------------------------------------------------------
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <tchar.h>
#include <windowsx.h>
#include <winuser.h>
#include <objbase.h>
#include <process.h>
#include <lmcons.h>
#include <lm.h>         // lib: netapi32.lib
#pragma comment(lib, "netapi32.lib")
#include <sys/locking.h>
#include <io.h>
#include <psapi.h>
#include <TlHelp32.h>
#include <BaseTsd.h>    // SIZE_T, SSIZE_T
#include <Wincrypt.h>

#if   xCOMPILER_MINGW
    #include <winternl.h>
    #include <intrin.h>
#elif xCOMPILER_MS
    #include <winternl.h>
    #include <intrin.h>
#elif xCOMPILER_CODEGEAR
    #include <dir.h>
#endif
//-------------------------------------------------------------------------------------------------
#endif // xLib_xCore_WinH
