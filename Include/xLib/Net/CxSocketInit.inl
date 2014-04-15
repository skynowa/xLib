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
    cushort_t &a_majorVersion,
    cushort_t &a_minorVersion
)
{
#if   xOS_ENV_WIN
    WSADATA wdData = {0};

    int_t iRv = ::WSAStartup(MAKEWORD(a_majorVersion, a_minorVersion), &wdData);
    xTEST_EQ(iRv, 0);
    xTEST_EQ(a_minorVersion, (ushort_t)HIBYTE(wdData.wVersion));
    xTEST_EQ(a_majorVersion, (ushort_t)LOBYTE(wdData.wVersion));
#elif xOS_ENV_UNIX
    xUNUSED(a_majorVersion);
    xUNUSED(a_minorVersion);
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
