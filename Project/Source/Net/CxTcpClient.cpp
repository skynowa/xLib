/**
 * \file  CxTcpClient.cpp
 * \brief client socket
 */


#include <xLib/Net/CxTcpClient.h>

#include <xLib/Core/CxUtils.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* virtual */
xINLINE_HO
CxTcpClient::CxTcpClient() :
    _timeout()
{
    setTimeout(0L, SOCKET_TIMEOUT);
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxTcpClient::isReadable()
{
    timeval tvTimeout = {1, 0};     /*seconds, microseconds*/
    fd_set  fds;        FD_ZERO(&fds);

    FD_SET(_socket, &fds);

    int_t iRv = ::select(0, &fds, NULL, NULL, &tvTimeout);
    xCHECK_RET(iRv <= 0 || !FD_ISSET(_socket, &fds), false);

    return true;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxTcpClient::isWritable()
{
    timeval tvTimeout = {1, 0};     /*seconds, microseconds*/
    fd_set  fds;        FD_ZERO(&fds);

    FD_SET(_socket, &fds);

    int_t iRv = ::select(0, NULL, &fds, NULL, &tvTimeout);
    xCHECK_RET(iRv <= 0 || !FD_ISSET(_socket, &fds), false);

    return true;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxTcpClient::connect(
    std::ctstring_t &a_ip,
    cushort_t       &a_port
)
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);
    xTEST_EQ(false, a_ip.empty());
    xTEST_EQ(true, (65535 > a_port) && (0 < a_port));

    //конверт из UNICODE
    std::string asIp(a_ip.begin(), a_ip.end());

    sockaddr_in saSockAddr = {0};
    saSockAddr.sin_family      = _family;
    saSockAddr.sin_addr.s_addr = ::inet_addr(asIp.c_str());
    saSockAddr.sin_port        = htons(a_port); //???????

    int_t iRv = ::connect(_socket, CxUtils::reinterpretCastT<sockaddr *>( &saSockAddr ), sizeof(saSockAddr));
    xTEST_DIFF(xSOCKET_ERROR, iRv);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxTcpClient::ioctl(
    clong_t &a_command,
    ulong_t *a_args
)
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);

    int_t iRv = xSOCKET_ERROR;

#if xOS_ENV_WIN
    iRv = ioctlsocket(_socket, a_command, a_args);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
#else
    iRv = ::ioctl    (_socket, a_command, a_args);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxTcpClient::setNonBlockingMode(
    cbool_t &a_flag
)
{
#if xOS_ENV_WIN
    ulong_t ulNonBlockingMode = static_cast<ulong_t>(a_flag);

    ioctl(FIONBIO, static_cast<ulong_t FAR *>(&ulNonBlockingMode));

    /*
    int_t bOptVal = true;
    int_t bOptLen = sizeof(int_t);

    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&bOptVal, bOptLen);
    */
#else
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
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxTcpClient::timeout(
    long_t *a_seconds,
    long_t *a_microsec
)
{
    // seconds      - n/a
    // microsec - n/a

    // BUG: static_cast<long_t>( _timeout.tv_sec  )
    CxUtils::ptrAssignT(a_seconds,      static_cast<long_t>( _timeout.tv_sec  ));
    CxUtils::ptrAssignT(a_microsec, static_cast<long_t>( _timeout.tv_usec ));
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
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
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: static
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
bool_t
CxTcpClient::isServerAlive(
    std::ctstring_t &a_ip,
    cushort_t       &a_port
)
{
    xTEST_EQ(false, a_ip.empty());
    xTEST_EQ(true, (65535 > a_port) && (0 < a_port));

    int_t iRv = - 1;

    CxTcpClient objSocket;

    //-------------------------------------
    //bCreate
    objSocket.create(CxSocket::afInet, CxSocket::tpStream, CxSocket::ptIp);

    //-------------------------------------
    //bConnect
    //convert from UNICODE
    std::string asIp(a_ip.begin(), a_ip.end());

    sockaddr_in saSockAddr = {0};
    saSockAddr.sin_family      = CxSocket::afInet;
    saSockAddr.sin_addr.s_addr = ::inet_addr(asIp.c_str());
    saSockAddr.sin_port        = htons(a_port); //TODO: htons

    //connect - [+] 0 [-] SOCKET_ERROR
    iRv = ::connect(objSocket.handle(), CxUtils::reinterpretCastT<sockaddr *>( &saSockAddr ), sizeof(saSockAddr));
    // n/a

    xCHECK_RET(0 != iRv, false);

    return true;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
