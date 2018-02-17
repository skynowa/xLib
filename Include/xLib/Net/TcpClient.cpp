/**
 * \file  TcpClient.inl
 * \brief client socket
 */


#include "TcpClient.h"

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Log/Trace.h>
#include <xLib/Core/Utils.h>

#if   xENV_WIN
    #include "Platform/Win/TcpClient_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/TcpClient_unix.inl"
#endif


xNAMESPACE_BEGIN2(xl, net)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
TcpClient::TcpClient() :
    _timeout()
{
    setTimeout(0L, SOCKET_TIMEOUT);
}
//-------------------------------------------------------------------------------------------------
void_t
TcpClient::connect(
    std::ctstring_t &a_ip,
    cushort_t       &a_port
) const
{
    xTEST_EQ(_handle.isValid(), true);
    xTEST_EQ(a_ip.empty(), false);
    xTEST_EQ((65535 > a_port) && (0 < a_port), true);

    sockaddr_in sockAddr;   Utils::structZeroT(sockAddr);
    sockAddr.sin_family      = static_cast<sa_family_t>(_family);
    sockAddr.sin_addr.s_addr = ::inet_addr( xT2A(a_ip).c_str());
    sockAddr.sin_port        = htons(a_port); // TODO: [skynowa] TcpClient::connect() - htons

    int_t iRv = ::connect(_handle.get(), Utils::reinterpretCastT<sockaddr *>( &sockAddr ),
        sizeof(sockAddr));
    xTEST_DIFF(iRv, xSOCKET_ERROR);
}
//-------------------------------------------------------------------------------------------------
void_t
TcpClient::ioctl(
    clong_t &a_command,
    ulong_t *a_args
) const
{
    xTEST_EQ(_handle.isValid(), true);

    int_t iRv = xIOCTLSOCKET(_handle.get(), static_cast<ulong_t>(a_command), a_args);
    xTEST_DIFF(iRv, xSOCKET_ERROR);
}
//-------------------------------------------------------------------------------------------------
void_t
TcpClient::setNonBlockingMode(
    cbool_t &a_flag
) const
{
    _setNonBlockingMode_impl(a_flag);
}
//-------------------------------------------------------------------------------------------------
void_t
TcpClient::timeout(
    long_t *a_seconds,
    long_t *a_microsec
) const
{
    xTEST_NA(a_seconds);
    xTEST_NA(a_microsec);

    Utils::ptrAssignT(a_seconds,  static_cast<long_t>( _timeout.tv_sec  ));
    Utils::ptrAssignT(a_microsec, static_cast<long_t>( _timeout.tv_usec ));
}
//-------------------------------------------------------------------------------------------------
void_t
TcpClient::setTimeout(
    clong_t &a_seconds,
    clong_t &a_microsec
)
{
    xTEST_NA(a_seconds);
    xTEST_NA(a_microsec);

    _timeout.tv_sec  = a_seconds;
    _timeout.tv_usec = a_microsec;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
bool_t
TcpClient::isServerAlive(
    std::ctstring_t &a_ip,
    cushort_t       &a_port
)
{
    xTEST_EQ(a_ip.empty(), false);
    xTEST_EQ((65535 > a_port) && (0 < a_port), true);

    TcpClient client;
    client.create(ISocket::afInet, ISocket::tpStream, ISocket::ptIp);

    sockaddr_in sockAddr;   Utils::structZeroT(sockAddr);
    sockAddr.sin_family      = ISocket::afInet;
    sockAddr.sin_addr.s_addr = ::inet_addr( xT2A(a_ip).c_str());
    sockAddr.sin_port        = htons(a_port); // TODO: [skynowa] TcpClient::isServerAlive() - htons

    int_t iRv = ::connect(client.handle().get(), Utils::reinterpretCastT<sockaddr *>( &sockAddr ),
        sizeof(sockAddr));
    xTEST_NA(iRv);

    xCHECK_RET(iRv != 0, false);

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, net)
