/**
 * \file  SocketInit.inl
 * \brief initiates use of the Winsock DLL by a process
 */


#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>


xNAMESPACE_BEGIN2(xlib, net)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
SocketInit::_construct_impl(
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
xINLINE void_t
SocketInit::_destruct_impl() const
{
    int_t iRv = ::WSACleanup();
    xTEST_EQ(iRv, 0);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
