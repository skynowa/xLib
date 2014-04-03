/**
 * \file  CxTcpClient.cpp
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


xNAMESPACE2_BEGIN(xlib, net)

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
    timeval timeout_ = {1, 0};   /* seconds, microseconds */
    fd_set  fds;       FD_ZERO(&fds);

    FD_SET(_socket, &fds);

    int_t iRv = ::select(0, &fds, xPTR_NULL, xPTR_NULL, &timeout_);
    xCHECK_RET(iRv <= 0 || !FD_ISSET(_socket, &fds), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxTcpClient::isWritable() const
{
    timeval timeout_ = {1, 0};   /* seconds, microseconds */
    fd_set  fds;       FD_ZERO(&fds);

    FD_SET(_socket, &fds);

    int_t iRv = ::select(0, xPTR_NULL, &fds, xPTR_NULL, &timeout_);
    xCHECK_RET(iRv <= 0 || !FD_ISSET(_socket, &fds), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxTcpClient::connect(
    std::ctstring_t &a_ip,
    cushort_t       &a_port
) const
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);
    xTEST_EQ(false, a_ip.empty());
    xTEST_EQ(true, (65535 > a_port) && (0 < a_port));

    //конверт из UNICODE
    std::string ip(a_ip.begin(), a_ip.end());

    sockaddr_in sockAddr;   xSTRUCT_ZERO(sockAddr);
    sockAddr.sin_family      = _family;
    sockAddr.sin_addr.s_addr = ::inet_addr(ip.c_str());
    sockAddr.sin_port        = htons(a_port); //???????

    int_t iRv = ::connect(_socket, CxUtils::reinterpretCastT<sockaddr *>( &sockAddr ),
        sizeof(sockAddr));
    xTEST_DIFF(xSOCKET_ERROR, iRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxTcpClient::ioctl(
    clong_t &a_command,
    ulong_t *a_args
) const
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);

    int_t iRv = xSOCKET_ERROR;

#if   xOS_ENV_WIN
    iRv = ioctlsocket(_socket, a_command, a_args);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
#elif xOS_ENV_UNIX
    iRv = ::ioctl    (_socket, a_command, a_args);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxTcpClient::setNonBlockingMode(
    cbool_t &a_flag
) const
{
#if   xOS_ENV_WIN
    ulong_t nonBlockingMode = static_cast<ulong_t>(a_flag);

    ioctl(FIONBIO, static_cast<ulong_t FAR *>(&nonBlockingMode));

    /*
    int_t bOptVal = true;
    int_t bOptLen = sizeof(int_t);

    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&bOptVal, bOptLen);
    */
#elif xOS_ENV_UNIX
    int_t iFlags = - 1;

    iFlags = ::fcntl(_socket, F_GETFL);
    xTEST_DIFF(xSOCKET_ERROR, iFlags);

    if (a_flag) {
        iFlags = (iFlags |  O_NONBLOCK);
    } else {
        iFlags = (iFlags & ~O_NONBLOCK);
    }

    iFlags = ::fcntl(_socket, F_SETFL, iFlags);
    xTEST_DIFF(xSOCKET_ERROR, iFlags);
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxTcpClient::timeout(
    long_t *a_seconds,
    long_t *a_microsec
) const
{
    // seconds      - n/a
    // microsec - n/a

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
    // liSec      - n/a
    // liMicroSec - n/a

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
    xTEST_EQ(false, a_ip.empty());
    xTEST_EQ(true, (65535 > a_port) && (0 < a_port));

    int_t iRv = - 1;

    CxTcpClient client;

    //-------------------------------------
    //bCreate
    client.create(CxSocket::afInet, CxSocket::tpStream, CxSocket::ptIp);

    //-------------------------------------
    //bConnect
    //convert from UNICODE
    std::string ip(a_ip.begin(), a_ip.end());

    sockaddr_in sockAddr;   xSTRUCT_ZERO(sockAddr);
    sockAddr.sin_family      = CxSocket::afInet;
    sockAddr.sin_addr.s_addr = ::inet_addr(ip.c_str());
    sockAddr.sin_port        = htons(a_port); // TODO: CxTcpClient::isServerAlive() - htons

    // connect - [+] 0 [-] SOCKET_ERROR
    iRv = ::connect(client.handle(), CxUtils::reinterpretCastT<sockaddr *>( &sockAddr ),
        sizeof(sockAddr));
    // n/a

    xCHECK_RET(0 != iRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, net)
