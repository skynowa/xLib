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
#include <xLib/Log/CxTracer.h>

#if xOS_ENV_WIN
    #if xCOMPILER_MS
        #pragma comment(lib, "ws2_32.Lib")
    #endif
#endif


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE_HO
CxSocketInit::CxSocketInit(
    cushort_t &a_majorVersion,
    cushort_t &a_minorVersion
)
{
#if xOS_ENV_WIN
    WSADATA wdData = {0};

    int_t iRv = ::WSAStartup(MAKEWORD(a_majorVersion, a_minorVersion), &wdData);
    xTEST_EQ(0, iRv);
    xTEST_EQ((ushort_t)HIBYTE(wdData.wVersion), a_minorVersion);
    xTEST_EQ((ushort_t)LOBYTE(wdData.wVersion), a_majorVersion);
#endif
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO
CxSocketInit::~CxSocketInit()
{
#if xOS_ENV_WIN
    int_t iRv = ::WSACleanup();
    xTEST_EQ(0, iRv);
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
