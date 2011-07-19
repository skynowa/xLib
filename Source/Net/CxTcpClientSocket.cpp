/****************************************************************************
* Class name:  CxTcpClientSocket
* Description: client socket
* File name:   CxTcpClientSocket.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     04.04.2009 6:21:18
*
*****************************************************************************/


#include <xLib/Net/CxTcpClientSocket.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxTcpClientSocket
/*virtual*/
CxTcpClientSocket::CxTcpClientSocket() :
    _m_tvTimeout()
{
    _m_bRes = bSetTimeout(0, SOCKET_TIMEOUT);
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: ~CxTcpClientSocket
CxTcpClientSocket::~CxTcpClientSocket() {

}
//---------------------------------------------------------------------------
//DONE: bIsReadible (checking for readability)
BOOL
CxTcpClientSocket::bIsReadable() {
    timeval tvTimeout = {1, 0};     /*seconds, microseconds*/
    fd_set  fds       = {{0}};  FD_ZERO(&fds);

    FD_SET(_m_puiSocket, &fds);

    INT iRes = select(0, &fds, NULL, NULL, &tvTimeout);
    xCHECK_RET(iRes <= 0 || !FD_ISSET(_m_puiSocket, &fds), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bIsWritable (checking for writability)
BOOL
CxTcpClientSocket::bIsWritable() {
    timeval tvTimeout = {1, 0};     /*seconds, microseconds*/
    fd_set  fds       = {{0}};  FD_ZERO(&fds);

    FD_SET(_m_puiSocket, &fds);

    INT iRes = select(0, NULL, &fds, NULL, &tvTimeout);
    xCHECK_RET(iRes <= 0 || !FD_ISSET(_m_puiSocket, &fds), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bConnect (connecting)
BOOL
CxTcpClientSocket::bConnect(const tString &csIp, USHORT usPort) {
    /*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket,        FALSE);
    /*DEBUG*/xASSERT_RET(false     == csIp.empty(),        FALSE);
    /*DEBUG*/xASSERT_RET((65535 > usPort) && (0 < usPort), FALSE);

    //конверт из UNICODE
    std::string asIp(csIp.begin(), csIp.end());

    sockaddr_in saSockAddr = {0};
    saSockAddr.sin_family      = _m_siFamily;
    saSockAddr.sin_addr.s_addr = inet_addr(asIp.c_str());
    saSockAddr.sin_port        = htons(usPort); //???????

    INT iRes = connect(_m_puiSocket, CxMacros::xreinterpret_cast<sockaddr *>( &saSockAddr ), sizeof(saSockAddr));
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bIoctl (controls the i/o mode)
BOOL
CxTcpClientSocket::bIoctl(LONG liCmd, ULONG *pulArgp) {
    /*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket, FALSE);

    INT iRes = etError;

#if defined(xOS_WIN)
    iRes = ioctlsocket(_m_puiSocket, liCmd, pulArgp);
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
#elif defined(xOS_LINUX)
    iRes = ioctl        (_m_puiSocket, liCmd, pulArgp);
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSetNonBlockingMode (set nonblocking mode)
BOOL
CxTcpClientSocket::bSetNonBlockingMode(const BOOL cbFlag) {
    /*DEBUG*/

#if defined(xOS_WIN)
    ULONG ulNonBlockingMode = static_cast<ULONG>(cbFlag);

    _m_bRes = bIoctl(FIONBIO, static_cast<ULONG FAR *>(&ulNonBlockingMode));
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    /*
    int bOptVal = TRUE;
    int bOptLen = sizeof(int);

    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&bOptVal, bOptLen);
    */
#elif defined(xOS_LINUX)
    INT iFlags = - 1;

    iFlags = fcntl(_m_puiSocket, F_GETFL);
    /*DEBUG*/xASSERT_RET(etError != iFlags, FALSE);

    if (TRUE == cbFlag) {
        iFlags = (iFlags |  O_NONBLOCK);
    } else {
        iFlags = (iFlags & ~O_NONBLOCK);
    }

    iFlags = fcntl(_m_puiSocket, F_SETFL, iFlags);
    /*DEBUG*/xASSERT_RET(etError != iFlags, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetTimeout (get timeout)
BOOL
CxTcpClientSocket::bGetTimeout(LONG *pliSec, LONG *pliMicroSec) {
    /*DEBUG*/
    /*DEBUG*/// pliSec      - n/a
    /*DEBUG*/// pliMicroSec - n/a

    xCHECK_DO(NULL != pliSec,      *pliSec      = _m_tvTimeout.tv_sec );
    xCHECK_DO(NULL != pliMicroSec, *pliMicroSec = _m_tvTimeout.tv_usec);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSetTimeout (set timeout)
BOOL
CxTcpClientSocket::bSetTimeout(LONG liSec, LONG liMicroSec) {
    /*DEBUG*/
    /*DEBUG*/// liSec      - n/a
    /*DEBUG*/// liMicroSec - n/a

    _m_tvTimeout.tv_sec  = liSec;
    _m_tvTimeout.tv_usec = liMicroSec;

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: static
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bIsServerAlive (is sever socket available)
/*static*/
BOOL
CxTcpClientSocket::bIsServerAlive(const tString &csIp, USHORT usPort) {
    /*DEBUG*/xASSERT_RET(false == csIp.empty(),            FALSE);
    /*DEBUG*/xASSERT_RET((65535 > usPort) && (0 < usPort), FALSE);

    BOOL bRes     = FALSE;
    INT  iRes     = - 1;

    CxTcpClientSocket objSocket;

    //-------------------------------------
    //bCreate
    bRes = objSocket.bCreate(CxSocket::afInet, CxSocket::tpStream, CxSocket::ptIp);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //bConnect
    //convert from UNICODE
    std::string asIp(csIp.begin(), csIp.end());

    sockaddr_in saSockAddr = {0};
    saSockAddr.sin_family      = CxSocket::afInet;
    saSockAddr.sin_addr.s_addr = inet_addr(asIp.c_str());
    saSockAddr.sin_port        = htons(usPort); //???????

    //connect - [+] 0 [-] SOCKET_ERROR
    iRes = connect(objSocket.iGetSocket(), CxMacros::xreinterpret_cast<sockaddr *>( &saSockAddr ), sizeof(saSockAddr));
    /*DEBUG*/// n/a

    xCHECK_RET(0 != iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------

