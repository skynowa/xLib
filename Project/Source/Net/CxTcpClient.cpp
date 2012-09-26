/**
 * \file  CxTcpClient.cpp
 * \brief client socket
 */


#include <xLib/Net/CxTcpClient.h>

#include <xLib/Common/CxMacros.h>


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
    const std::tstring_t &a_csIp,
    ushort_t              a_usPort
)
{
    /*DEBUG*/xASSERT_RET(etInvalid != _m_sktSocket,            false);
    /*DEBUG*/xASSERT_RET(false     == a_csIp.empty(),          false);
    /*DEBUG*/xASSERT_RET((65535 > a_usPort) && (0 < a_usPort), false);

    //конверт из UNICODE
    std::string asIp(a_csIp.begin(), a_csIp.end());

    sockaddr_in saSockAddr = {0};
    saSockAddr.sin_family      = _m_siFamily;
    saSockAddr.sin_addr.s_addr = ::inet_addr(asIp.c_str());
    saSockAddr.sin_port        = htons(a_usPort); //???????

    int iRv = ::connect(_m_sktSocket, CxMacros::reinterpretCastT<sockaddr *>( &saSockAddr ), sizeof(saSockAddr));
    /*DEBUG*/xASSERT_RET(etError != iRv, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxTcpClient::bIoctl(
    long_t   a_liCmd,
    ulong_t *a_pulArgp
)
{
    /*DEBUG*/xASSERT_RET(etInvalid != _m_sktSocket, false);

    int iRv = etError;

#if xOS_ENV_WIN
    iRv = ioctlsocket(_m_sktSocket, a_liCmd, a_pulArgp);
    /*DEBUG*/xASSERT_RET(etError != iRv, false);
#elif xOS_ENV_UNIX
    iRv = ::ioctl    (_m_sktSocket, a_liCmd, a_pulArgp);
    /*DEBUG*/xASSERT_RET(etError != iRv, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxTcpClient::bSetNonBlockingMode(
    const bool a_cbFlag
)
{
    /*DEBUG*/

#if xOS_ENV_WIN
    ulong_t ulNonBlockingMode = static_cast<ulong_t>(a_cbFlag);

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

    if (true == a_cbFlag) {
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
    long_t *a_pliSec,
    long_t *a_pliMicroSec
)
{
    /*DEBUG*/
    /*DEBUG*/// pliSec      - n/a
    /*DEBUG*/// pliMicroSec - n/a

    // BUG: static_cast<long_t>( _m_tvTimeout.tv_sec  )
    CxMacros::ptrAssignT(a_pliSec,      static_cast<long_t>( _m_tvTimeout.tv_sec  ));
    CxMacros::ptrAssignT(a_pliMicroSec, static_cast<long_t>( _m_tvTimeout.tv_usec ));

    return true;
}
//---------------------------------------------------------------------------
bool
CxTcpClient::bSetTimeout(
    long_t a_liSec,
    long_t a_liMicroSec
)
{
    /*DEBUG*/
    /*DEBUG*/// liSec      - n/a
    /*DEBUG*/// liMicroSec - n/a

    _m_tvTimeout.tv_sec  = a_liSec;
    _m_tvTimeout.tv_usec = a_liMicroSec;

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
    const std::tstring_t &a_csIp,
    ushort_t              a_usPort
)
{
    /*DEBUG*/xASSERT_RET(false == a_csIp.empty(),              false);
    /*DEBUG*/xASSERT_RET((65535 > a_usPort) && (0 < a_usPort), false);

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
    std::string asIp(a_csIp.begin(), a_csIp.end());

    sockaddr_in saSockAddr = {0};
    saSockAddr.sin_family      = CxSocket::afInet;
    saSockAddr.sin_addr.s_addr = ::inet_addr(asIp.c_str());
    saSockAddr.sin_port        = htons(a_usPort); //TODO: htons

    //connect - [+] 0 [-] SOCKET_ERROR
    iRv = ::connect(objSocket.iGetSocket(), CxMacros::reinterpretCastT<sockaddr *>( &saSockAddr ), sizeof(saSockAddr));
    /*DEBUG*/// n/a

    xCHECK_RET(0 != iRv, false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
