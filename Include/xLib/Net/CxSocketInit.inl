/**
 * \file  CxSocketInit.cpp
 * \brief initiates use of the Winsock DLL by a process
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTrace.h>

#if xOS_ENV_WIN
    #if xCOMPILER_MS
        #pragma comment(lib, "ws2_32.Lib")
    #endif
#endif


xNAMESPACE2_BEGIN(xlib, net)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxSocketInit::CxSocketInit(
    cushort_t &a_versionMajor,
    cushort_t &a_versionMinor
)
{
#if   xOS_ENV_WIN
    WSADATA wdData = {0};

    int_t iRv = ::WSAStartup(MAKEWORD(a_versionMajor, a_versionMinor), &wdData);
    xTEST_EQ(iRv, 0);
    xTEST_EQ(a_versionMajor, (ushort_t)LOBYTE(wdData.wVersion));
    xTEST_EQ(a_versionMinor, (ushort_t)HIBYTE(wdData.wVersion));
#elif xOS_ENV_UNIX
    xUNUSED(a_versionMajor);
    xUNUSED(a_versionMinor);
#endif
}
//-------------------------------------------------------------------------------------------------
inline
CxSocketInit::~CxSocketInit()
{
#if xOS_ENV_WIN
    int_t iRv = ::WSACleanup();
    xTEST_EQ(iRv, 0);
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, net)
