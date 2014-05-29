/**
 * \file  CxSocketInit.inl
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

#if xCOMPILER_MS
    #pragma comment(lib, "ws2_32.Lib")
#endif


xNAMESPACE_BEGIN2(xlib, net)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxSocketInit::_construct_impl(
    cushort_t &a_versionMajor,
    cushort_t &a_versionMinor
) const
{
    WSADATA wdData = {0};

    int_t iRv = ::WSAStartup(MAKEWORD(a_versionMajor, a_versionMinor), &wdData);
    xTEST_EQ(iRv, 0);
    xTEST_EQ(a_versionMajor, (ushort_t)LOBYTE(wdData.wVersion));
    xTEST_EQ(a_versionMinor, (ushort_t)HIBYTE(wdData.wVersion));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxSocketInit::_destruct_impl() const
{
    int_t iRv = ::WSACleanup();
    xTEST_EQ(iRv, 0);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
