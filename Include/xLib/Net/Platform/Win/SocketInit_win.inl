/**
 * \file  SocketInit.inl
 * \brief initiates use of the Winsock DLL by a process
 */


#include <xLib/Test/Test.h>
#include <xLib/Core/Format.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>


namespace xl::net
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
SocketInit::_ctor_impl(
    cushort_t a_versionMajor,
    cushort_t a_versionMinor
) const
{
    WSADATA wdData = {0};

    int_t iRv = ::WSAStartup(MAKEWORD(a_versionMajor, a_versionMinor), &wdData);
    xTEST_EQ(iRv, 0);
    xTEST_EQ(a_versionMajor, (ushort_t)LOBYTE(wdData.wVersion));
    xTEST_EQ(a_versionMinor, (ushort_t)HIBYTE(wdData.wVersion));
}
//-------------------------------------------------------------------------------------------------
void_t
SocketInit::_dtor_impl() const
{
    int_t iRv = ::WSACleanup();
    xTEST_EQ(iRv, 0);
}
//-------------------------------------------------------------------------------------------------

} // namespace
