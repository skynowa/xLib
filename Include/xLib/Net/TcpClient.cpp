/**
 * \file  TcpClient.inl
 * \brief client socket
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "TcpClient.h"
#endif

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


xNAMESPACE_BEGIN2(xlib, net)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
TcpClient::TcpClient() :
    _timeout()
{
    setTimeout(0L, SOCKET_TIMEOUT);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
TcpClient::connect(
    std::ctstring_t &a_ip,
    cushort_t       &a_port
) const
{
    xTEST_DIFF(_handle, xSOCKET_HANDLE_INVALID);
    xTEST_EQ(a_ip.empty(), false);
    xTEST_EQ((65535 > a_port) && (0 < a_port), true);

    sockaddr_in sockAddr;   xSTRUCT_ZERO(sockAddr);
    sockAddr.sin_family      = static_cast<ushort_t>(_family);
    sockAddr.sin_addr.s_addr = ::inet_addr( xT2A(a_ip).c_str());
    sockAddr.sin_port        = htons(a_port); // TODO: TcpClient::connect() - htons

    int_t iRv = ::connect(_handle, Utils::reinterpretCastT<sockaddr *>( &sockAddr ),
        sizeof(sockAddr));
    xTEST_DIFF(iRv, xSOCKET_ERROR);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
TcpClient::ioctl(
    clong_t &a_command,
    ulong_t *a_args
) const
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _handle);

    int_t iRv = xIOCTLSOCKET(_handle, static_cast<ulong_t>(a_command), a_args);
    xTEST_DIFF(iRv, xSOCKET_ERROR);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
TcpClient::setNonBlockingMode(
    cbool_t &a_flag
) const
{
    _setNonBlockingMode_impl(a_flag);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
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
xINLINE void_t
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
xINLINE bool_t
TcpClient::isServerAlive(
    std::ctstring_t &a_ip,
    cushort_t       &a_port
)
{
    xTEST_EQ(a_ip.empty(), false);
    xTEST_EQ((65535 > a_port) && (0 < a_port), true);

    TcpClient client;
    client.create(Socket::afInet, Socket::tpStream, Socket::ptIp);

    sockaddr_in sockAddr;   xSTRUCT_ZERO(sockAddr);
    sockAddr.sin_family      = Socket::afInet;
    sockAddr.sin_addr.s_addr = ::inet_addr( xT2A(a_ip).c_str());
    sockAddr.sin_port        = htons(a_port); // TODO: TcpClient::isServerAlive() - htons

    int_t iRv = ::connect(client.handle(), Utils::reinterpretCastT<sockaddr *>( &sockAddr ),
        sizeof(sockAddr));
    xTEST_NA(iRv);

    xCHECK_RET(iRv != 0, false);

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
