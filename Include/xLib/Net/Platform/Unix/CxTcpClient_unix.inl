/**
 * \file  CxTcpClient.inl
 * \brief client socket
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTrace.h>
#include <xLib/Core/CxUtils.h>


xNAMESPACE_BEGIN2(xlib, net)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxTcpClient::CxTcpClient() :
    _timeout()
{
    setTimeout(0L, SOCKET_TIMEOUT);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxTcpClient::isReadable() const
{
    timeval timeoutVal = {1, 0};
    fd_set  fds;         FD_ZERO(&fds);

    FD_SET(_handle, &fds);

    int_t iRv = ::select(0, &fds, xPTR_NULL, xPTR_NULL, &timeoutVal);
    xCHECK_RET(iRv <= 0 || !FD_ISSET(_handle, &fds), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxTcpClient::isWritable() const
{
    timeval timeoutVal = {1, 0};
    fd_set  fds;         FD_ZERO(&fds);

    FD_SET(_handle, &fds);

    int_t iRv = ::select(0, xPTR_NULL, &fds, xPTR_NULL, &timeoutVal);
    xCHECK_RET(iRv <= 0 || !FD_ISSET(_handle, &fds), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxTcpClient::connect(
    std::ctstring_t &a_ip,
    cushort_t       &a_port
) const
{
    xTEST_DIFF(_handle, xSOCKET_HANDLE_INVALID);
    xTEST_EQ(a_ip.empty(), false);
    xTEST_EQ((65535 > a_port) && (0 < a_port), true);

    // convert from UNICODE
    std::string ip(a_ip.begin(), a_ip.end());

    sockaddr_in sockAddr;   xSTRUCT_ZERO(sockAddr);
    sockAddr.sin_family      = _family;
    sockAddr.sin_addr.s_addr = ::inet_addr(ip.c_str());
    sockAddr.sin_port        = htons(a_port); // TODO: CxTcpClient::connect() - htons

    int_t iRv = ::connect(_handle, CxUtils::reinterpretCastT<sockaddr *>( &sockAddr ),
        sizeof(sockAddr));
    xTEST_DIFF(iRv, xSOCKET_ERROR);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxTcpClient::ioctl(
    clong_t &a_command,
    ulong_t *a_args
) const
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _handle);

    int_t iRv = xSOCKET_ERROR;

#if   xENV_WIN
    iRv = ::ioctlsocket(_handle, a_command, a_args);
    xTEST_DIFF(iRv, xSOCKET_ERROR);
#elif xENV_UNIX
    iRv = ::ioctl(_handle, a_command, a_args);
    xTEST_DIFF(iRv, xSOCKET_ERROR);
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxTcpClient::setNonBlockingMode(
    cbool_t &a_flag
) const
{
#if   xENV_WIN
    ulong_t nonBlockingMode = static_cast<ulong_t>(a_flag);

    ::ioctl(FIONBIO, static_cast<ulong_t FAR *>(&nonBlockingMode));

#if 0
    int_t optVal = true;
    int_t optLen = sizeof(int_t);

    ::setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *)&optVal, optLen);
#endif
#elif xENV_UNIX
    int_t flags = - 1;

    flags = ::fcntl(_handle, F_GETFL);
    xTEST_DIFF(flags, xSOCKET_ERROR);

    if (a_flag) {
        flags = (flags |  O_NONBLOCK);
    } else {
        flags = (flags & ~O_NONBLOCK);
    }

    flags = ::fcntl(_handle, F_SETFL, flags);
    xTEST_DIFF(flags, xSOCKET_ERROR);
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxTcpClient::timeout(
    long_t *a_seconds,
    long_t *a_microsec
) const
{
    xTEST_NA(a_seconds);
    xTEST_NA(a_microsec);

    CxUtils::ptrAssignT(a_seconds,  static_cast<long_t>( _timeout.tv_sec  ));
    CxUtils::ptrAssignT(a_microsec, static_cast<long_t>( _timeout.tv_usec ));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxTcpClient::setTimeout(
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
inline bool_t
CxTcpClient::isServerAlive(
    std::ctstring_t &a_ip,
    cushort_t       &a_port
)
{
    xTEST_EQ(a_ip.empty(), false);
    xTEST_EQ((65535 > a_port) && (0 < a_port), true);

    int_t iRv = - 1;

    CxTcpClient client;

    client.create(CxSocket::afInet, CxSocket::tpStream, CxSocket::ptIp);

    // convert from UNICODE
    std::string ip(a_ip.begin(), a_ip.end());

    sockaddr_in sockAddr;   xSTRUCT_ZERO(sockAddr);
    sockAddr.sin_family      = CxSocket::afInet;
    sockAddr.sin_addr.s_addr = ::inet_addr(ip.c_str());
    sockAddr.sin_port        = htons(a_port); // TODO: CxTcpClient::isServerAlive() - htons

    iRv = ::connect(client.handle(), CxUtils::reinterpretCastT<sockaddr *>( &sockAddr ),
        sizeof(sockAddr));
    xTEST_NA(iRv);

    xCHECK_RET(iRv != 0, false);

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
