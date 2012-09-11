/**
 * \file  CxTcpClient.cpp
 * \brief client socket
 */


#include <xLib/Net/CxTcpClient.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*virtual*/
CxTcpClient::CxTcpClient() :
    _m_tvTimeout()
{
    bool bRv = bSetTimeout(0, SOCKET_TIMEOUT);
    /*DEBUG*/xASSERT_DO(true == bRv, return);
}
//---------------------------------------------------------------------------
CxTcpClient::~CxTcpClient() {

}
//---------------------------------------------------------------------------
bool
CxTcpClient::bIsReadable() {
    timeval tvTimeout = {1, 0};     /*seconds, microseconds*/
    fd_set  fds;        FD_ZERO(&fds);

    FD_SET(_m_sktSocket, &fds);

    int iRv = ::select(0, &fds, NULL, NULL, &tvTimeout);
    xCHECK_RET(iRv <= 0 || !FD_ISSET(_m_sktSocket, &fds), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxTcpClient::bIsWritable() {
    timeval tvTimeout = {1, 0};     /*seconds, microseconds*/
    fd_set  fds;        FD_ZERO(&fds);

    FD_SET(_m_sktSocket, &fds);

    int iRv = ::select(0, NULL, &fds, NULL, &tvTimeout);
    xCHECK_RET(iRv <= 0 || !FD_ISSET(_m_sktSocket, &fds), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxTcpClient::bConnect(
    const std::tstring_t &csIp,
    ushort_t              usPort
)
{
    /*DEBUG*/xASSERT_RET(etInvalid != _m_sktSocket,        false);
    /*DEBUG*/xASSERT_RET(false     == csIp.empty(),        false);
    /*DEBUG*/xASSERT_RET((65535 > usPort) && (0 < usPort), false);

    //конверт из UNICODE
    std::string asIp(csIp.begin(), csIp.end());

    sockaddr_in saSockAddr = {0};
    saSockAddr.sin_family      = _m_siFamily;
    saSockAddr.sin_addr.s_addr = ::inet_addr(asIp.c_str());
    saSockAddr.sin_port        = htons(usPort); //???????

    int iRv = ::connect(_m_sktSocket, CxMacros::reinterpretCastT<sockaddr *>( &saSockAddr ), sizeof(saSockAddr));
    /*DEBUG*/xASSERT_RET(etError != iRv, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxTcpClient::bIoctl(
    long_t   liCmd,
    ulong_t *pulArgp
)
{
    /*DEBUG*/xASSERT_RET(etInvalid != _m_sktSocket, false);

    int iRv = etError;

#if xOS_ENV_WIN
    iRv = ioctlsocket(_m_sktSocket, liCmd, pulArgp);
    /*DEBUG*/xASSERT_RET(etError != iRv, false);
#elif xOS_ENV_UNIX
    iRv = ::ioctl    (_m_sktSocket, liCmd, pulArgp);
    /*DEBUG*/xASSERT_RET(etError != iRv, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxTcpClient::bSetNonBlockingMode(
    const bool cbFlag
)
{
    /*DEBUG*/

#if xOS_ENV_WIN
    ulong_t ulNonBlockingMode = static_cast<ulong_t>(cbFlag);

    bool bRv = bIoctl(FIONBIO, static_cast<ulong_t FAR *>(&ulNonBlockingMode));
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    /*
    int bOptVal = true;
    int bOptLen = sizeof(int);

    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&bOptVal, bOptLen);
    */
#elif xOS_ENV_UNIX
    int iFlags = - 1;

    iFlags = ::fcntl(_m_sktSocket, F_GETFL);
    /*DEBUG*/xASSERT_RET(etError != iFlags, false);

    if (true == cbFlag) {
        iFlags = (iFlags |  O_NONBLOCK);
    } else {
        iFlags = (iFlags & ~O_NONBLOCK);
    }

    iFlags = ::fcntl(_m_sktSocket, F_SETFL, iFlags);
    /*DEBUG*/xASSERT_RET(etError != iFlags, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxTcpClient::bGetTimeout(
    long_t *pliSec,
    long_t *pliMicroSec
)
{
    /*DEBUG*/
    /*DEBUG*/// pliSec      - n/a
    /*DEBUG*/// pliMicroSec - n/a

    xCHECK_DO(NULL != pliSec,      *pliSec      = _m_tvTimeout.tv_sec );
    xCHECK_DO(NULL != pliMicroSec, *pliMicroSec = _m_tvTimeout.tv_usec);

    return true;
}
//---------------------------------------------------------------------------
bool
CxTcpClient::bSetTimeout(
    long_t liSec,
    long_t liMicroSec
)
{
    /*DEBUG*/
    /*DEBUG*/// liSec      - n/a
    /*DEBUG*/// liMicroSec - n/a

    _m_tvTimeout.tv_sec  = liSec;
    _m_tvTimeout.tv_usec = liMicroSec;

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: static
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
bool
CxTcpClient::bIsServerAlive(
    const std::tstring_t &csIp,
    ushort_t              usPort
)
{
    /*DEBUG*/xASSERT_RET(false == csIp.empty(),            false);
    /*DEBUG*/xASSERT_RET((65535 > usPort) && (0 < usPort), false);

    bool bRv     = false;
    int  iRv     = - 1;

    CxTcpClient objSocket;

    //-------------------------------------
    //bCreate
    bRv = objSocket.bCreate(CxSocket::afInet, CxSocket::tpStream, CxSocket::ptIp);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    //-------------------------------------
    //bConnect
    //convert from UNICODE
    std::string asIp(csIp.begin(), csIp.end());

    sockaddr_in saSockAddr = {0};
    saSockAddr.sin_family      = CxSocket::afInet;
    saSockAddr.sin_addr.s_addr = ::inet_addr(asIp.c_str());
    saSockAddr.sin_port        = htons(usPort); //TODO: htons

    //connect - [+] 0 [-] SOCKET_ERROR
    iRv = ::connect(objSocket.iGetSocket(), CxMacros::reinterpretCastT<sockaddr *>( &saSockAddr ), sizeof(saSockAddr));
    /*DEBUG*/// n/a

    xCHECK_RET(0 != iRv, false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
