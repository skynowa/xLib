/**
 * \file  CxSocket.cpp
 * \brief blocking socket
 */


#include <xLib/Net/CxSocket.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxSocket::CxSocket() :
    _m_sktSocket(xSOCKET_HANDLE_INVALID),
    _m_siFamily (- 1),
    _m_sIp      (),
    _m_usPort   (0)
{

}
//---------------------------------------------------------------------------
CxSocket::~CxSocket() {
    /*DEBUG*/// n/a

    xCHECK_DO(true == bIsValid(), bClose());
}
//---------------------------------------------------------------------------
bool
CxSocket::bAssign(
    const socket_t &a_csktSocket
)
{
    /*DEBUG*/// _m_sktSocket - n/a
    /*DEBUG*/// csktSocket    - n/a

    _m_sktSocket = a_csktSocket;

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
* operators
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxSocket &
CxSocket::operator = (
    const socket_t &a_csktSocket
)
{
    /*DEBUG*/// _m_sktSocket - n/a
    /*DEBUG*/// scktSocket   - n/a

    _m_sktSocket = a_csktSocket;

    return *this;
}
//---------------------------------------------------------------------------
CxSocket::operator socket_t () {
    /*DEBUG*/// _m_sktSocket - n/a
    /*DEBUG*/// scktSocket   - n/a

    return _m_sktSocket;
}
//---------------------------------------------------------------------------


/****************************************************************************
*
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxSocket::bCreate(
    ExAddressFamily a_afFamily,
    ExType          a_tpType,
    ExProtocol      a_ptProtocol
)
{
    /*DEBUG*/xTEST_EQ(xSOCKET_HANDLE_INVALID, _m_sktSocket);

    _m_sktSocket = ::socket(a_afFamily, a_tpType, a_ptProtocol);
    /*DEBUG*/xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_sktSocket);

    _m_siFamily = a_afFamily;

    return true;
}
//---------------------------------------------------------------------------
socket_t
CxSocket::iGetSocket() const {
    /*DEBUG*/xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_sktSocket);

    return _m_sktSocket;
}
//---------------------------------------------------------------------------
bool
CxSocket::bIsValid() const {
    /*DEBUG*/// n/a

#if   xOS_ENV_WIN
    return (_m_sktSocket >= 0);
#elif xOS_ENV_UNIX
    return (_m_sktSocket >= 0);
#endif
}
//---------------------------------------------------------------------------
bool
CxSocket::bClose() {
    /*DEBUG*/xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_sktSocket);

    int iRv = xSOCKET_ERROR;

#if   xOS_ENV_WIN
    iRv = shutdown(_m_sktSocket, SD_BOTH);
    /*DEBUG*/xTEST_DIFF(xSOCKET_ERROR, iRv);

    iRv = ::closesocket(_m_sktSocket);
    /*DEBUG*/xTEST_DIFF(xSOCKET_ERROR, iRv);
#elif xOS_ENV_UNIX
    iRv = ::close(_m_sktSocket);
    /*DEBUG*/xTEST_DIFF(xSOCKET_ERROR, iRv);
#endif

    _m_sktSocket = xSOCKET_HANDLE_INVALID;

    return true;
}
//---------------------------------------------------------------------------



/****************************************************************************
* I/O
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: iSend
//TODO: LINUX: ssize_t send(int sockfd, const void *buf, size_t len, int flags);
int
CxSocket::iSend(
    const tchar_t *a_pcszBuff,
    int            a_iBuffSize,
    int            a_iFlags
)
{
    /*DEBUG*/xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_sktSocket);
    /*DEBUG*/xTEST_PTR(a_pcszBuff);
    /*DEBUG*//////xASSERT_RET(0         <  ::lstrlen(pcszBuff), xSOCKET_ERROR);

#if   xOS_ENV_WIN
    int     iRv = ::send(_m_sktSocket, (LPCSTR)a_pcszBuff, a_iBuffSize * sizeof(tchar_t), a_iFlags);
    /*DEBUG*/xTEST_EQ(true, xSOCKET_ERROR != iRv && WSAEWOULDBLOCK != iGetLastError());
    /*DEBUG*/xTEST_GR_EQ(a_iBuffSize * (int)sizeof(tchar_t), iRv);
#elif xOS_ENV_UNIX
    #if !defined(MSG_NOSIGNAL)
        #define MSG_NOSIGNAL  0x20000
    #endif

    ssize_t iRv = ::send(_m_sktSocket, a_pcszBuff, a_iBuffSize, MSG_NOSIGNAL);
    /*DEBUG*/xTEST_DIFF(ssize_t(xSOCKET_ERROR), iRv);
    /*DEBUG*/xTEST_GR_EQ(ssize_t(a_iBuffSize * sizeof(tchar_t)), iRv);
#endif

    return iRv / sizeof(tchar_t);
}
//---------------------------------------------------------------------------
//TODO: bSendAll
bool
CxSocket::bSendAll(
    const std::tstring_t &a_csBuff,
    int                   a_iFlags
)
{
    /*DEBUG*/xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_sktSocket);
    /*DEBUG*/xTEST_EQ(false, a_csBuff.empty());
    /*DEBUG*/xTEST_LESS(size_t(0U), a_csBuff.size());

    //-------------------------------------
    //������ �� ������ ������� � ����� � ������
    int iCurrPos  = 0;
    int iLeftSize = a_csBuff.size() * sizeof(tchar_t);            //TODO: !!!!!!  bSendAll (overflow)

    //if size of data more than size of buffer - sizeof buffer SOCKET_BUFF_SIZE
    int iBuffOutSize  = 0;
    if (iLeftSize >= SOCKET_BUFF_SIZE) {
        iBuffOutSize = SOCKET_BUFF_SIZE;
    } else {
        iBuffOutSize = iLeftSize;
    }

    for (;;) {        /*uiLeftSize > 0*/
        int iRv = iSend(&a_csBuff.at(0) + iCurrPos, iBuffOutSize, a_iFlags);
        xCHECK_DO(xSOCKET_ERROR == iRv, break);
        xCHECK_DO(0       == iRv, break);

        iCurrPos  += iRv;
        iLeftSize -= iRv;

        xCHECK_DO(iLeftSize < iBuffOutSize, iBuffOutSize = iLeftSize);

        //id data is finished - exit from loop
        if (0 >= iLeftSize) {
            /*DEBUG*/xTEST_EQ((int)a_csBuff.size() * (int)sizeof(tchar_t), iCurrPos);
            break;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
int
CxSocket::iRecv(
    tchar_t *a_pszBuff,
    int      a_iBuffSize,
    int      a_iFlags
)
{
    /*DEBUG*/xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_sktSocket);
    /*DEBUG*/xTEST_PTR(a_pszBuff);
    /*DEBUG*/xTEST_LESS(0, a_iBuffSize);

    std::memset(a_pszBuff, 0, a_iBuffSize * sizeof(tchar_t));

#if   xOS_ENV_WIN
    int     iRv = ::recv(_m_sktSocket, (LPSTR)a_pszBuff, a_iBuffSize * sizeof(tchar_t), a_iFlags);
    /*DEBUG*/xTEST_EQ(true, xSOCKET_ERROR != iRv && WSAEWOULDBLOCK != iGetLastError());
    /*DEBUG*/xTEST_DIFF(0, iRv);  //gracefully closed
    /*DEBUG*/xTEST_GR_EQ(a_iBuffSize * (int)sizeof(tchar_t), iRv);
#elif xOS_ENV_UNIX
    ssize_t iRv = ::recv(_m_sktSocket, (char *)a_pszBuff, a_iBuffSize * sizeof(tchar_t), a_iFlags);
    /*DEBUG*/xTEST_DIFF(ssize_t(xSOCKET_ERROR), iRv);
    /*DEBUG*/xTEST_DIFF(ssize_t(0), iRv);  //gracefully closed
    /*DEBUG*/xTEST_GR_EQ(ssize_t(a_iBuffSize * sizeof(tchar_t)), iRv);
#endif

    return iRv / sizeof(tchar_t);
}
//---------------------------------------------------------------------------
std::tstring_t
CxSocket::sRecvAll(
    int a_iFlags
)
{
    std::tstring_t sRv;

    const size_t   cuiBuffSize             = 1024 * sizeof(tchar_t);
    tchar_t        szBuff[cuiBuffSize + 1] = {0};

    for (;;) {
        int   iRv  = - 1;
        ulong_t ulArg = (ulong_t)false;

    #if   xOS_ENV_WIN
        iRv = ::ioctlsocket(_m_sktSocket, FIONREAD, &ulArg);
    #elif xOS_ENV_UNIX
        iRv = ::ioctl      (_m_sktSocket, FIONREAD, &ulArg);
    #endif

        xCHECK_DO(0 != iRv,           break);
        xCHECK_DO(0 == ulArg,          break);
        xCHECK_DO(cuiBuffSize < ulArg, ulArg = cuiBuffSize);

        iRv = ::recv(_m_sktSocket, (char *)&szBuff[0], ulArg, 0);
        xCHECK_DO(iRv <= 0, break);

        sRv.append(szBuff, iRv);
    }

    return sRv;
}
//---------------------------------------------------------------------------
std::tstring_t
CxSocket::sRecvAll(
    int                   a_iFlags,
    const std::tstring_t &a_csDelimiter
)
{
    std::tstring_t sRv;
    const size_t   cuiInSize = SOCKET_BUFF_SIZE * sizeof(tchar_t);
    std::tstring_t sIn(cuiInSize, xT('\0'));

    //-------------------------------------
    //read from socket by blocks, write to string
    for (;;) {
        int iRv = iRecv(&sIn.at(0), cuiInSize, a_iFlags);
        xCHECK_DO(xSOCKET_ERROR == iRv, break);
        xCHECK_DO(0       == iRv, break);

        sRv.append(sIn.begin(), sIn.begin() + iRv);

        //if delimiter was finded - break
        size_t uiDelimiterPos = sRv.find(a_csDelimiter);        //TODO: from unicode ???
        xCHECK_DO(std::tstring_t::npos != uiDelimiterPos, break);
    }

    return sRv;
}
//---------------------------------------------------------------------------
//TODO: iSendBytes
int
CxSocket::iSendBytes(
    char *a_pszBuff,
    int   a_iMessageLength
)
{
    int     iRC         = 0;
    int     iSendStatus = 0;
    timeval SendTimeout = {0};

    //sSetting the timeout
    SendTimeout.tv_sec  = 0;
    SendTimeout.tv_usec = SOCKET_TIMEOUT;

    fd_set fds;    FD_ZERO(&fds);
    FD_SET(_m_sktSocket, &fds);

    //..as long_t as we need to send data...
    while (a_iMessageLength > 0) {
        iRC = ::select(0, NULL, &fds, NULL, &SendTimeout);

        //timed out, return error
        xCHECK_RET(!iRC, xSOCKET_ERROR);

        //An error occurred
        xCHECK_RET(iRC < 0, iGetLastError());

        //send a few bytes
        iSendStatus = ::send(_m_sktSocket, a_pszBuff, a_iMessageLength, 0);

        //An error occurred when sending data
        xCHECK_RET(iSendStatus < 0, iGetLastError());

        //update the buffer and the counter
        a_iMessageLength -= iSendStatus;
        a_pszBuff        += iSendStatus;
    }

    return 0;
}
//---------------------------------------------------------------------------
//TODO: ReceiveNBytes
int
CxSocket::iReceiveBytes(
    char *a_pszBuff,
    int   a_iStillToReceive
)
{
    int     iRC            = 0;
    int     iReceiveStatus = 0;
    timeval ReceiveTimeout = {0};

    //Setting the timeout
    ReceiveTimeout.tv_sec  = 0;
    ReceiveTimeout.tv_usec = SOCKET_TIMEOUT;             //500 ms

    fd_set fds;    FD_ZERO(&fds);
    FD_SET(_m_sktSocket, &fds);

    //.. Until the data is sent ..
    while (a_iStillToReceive > 0) {
        iRC = ::select(0, &fds, NULL, NULL, &ReceiveTimeout);

        //return by timeout
        xCHECK_RET(!iRC, xSOCKET_ERROR);

        //An error occurred
        xCHECK_RET(iRC < 0, iGetLastError());

        //recive a few bytes
        iReceiveStatus = ::recv(_m_sktSocket, a_pszBuff, a_iStillToReceive, 0);

        //An error occurred when the function recv ()
        xCHECK_RET(iReceiveStatus < 0, iGetLastError());

        //changed the value of the counter and the buffer
        a_iStillToReceive -= iReceiveStatus;
        a_pszBuff         += iReceiveStatus;
    }

    return 0;
}
//---------------------------------------------------------------------------


/****************************************************************************
* ...
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxSocket::bGetPeerName(
    std::tstring_t *a_psPeerAddr,
    ushort_t       *a_pusPeerPort
)
{
    /*DEBUG*///psPeerAddr  - n/a
    /*DEBUG*///pusPeerPort - n/a

#if   xOS_ENV_WIN
    SOCKADDR_IN sockAddr     = {0};
    int         iSockAddrLen = sizeof(sockAddr);

    int iRv = ::getpeername(_m_sktSocket, CxUtils::reinterpretCastT<SOCKADDR *>( &sockAddr ), &iSockAddrLen);
    /*DEBUG*/xTEST_DIFF(xSOCKET_ERROR, iRv);
#elif xOS_ENV_UNIX
    sockaddr_in sockAddr      = {0};
    socklen_t   uiSockAddrLen = sizeof(sockAddr);

    int iRv = ::getpeername(_m_sktSocket, CxUtils::reinterpretCastT<sockaddr *>( &sockAddr ), &uiSockAddrLen);
    /*DEBUG*/xTEST_DIFF(xSOCKET_ERROR, iRv);
#endif

    if (NULL != a_psPeerAddr) {
        //convert to UNICODE
        std::string asPeerAddr = ::inet_ntoa(sockAddr.sin_addr);

        (*a_psPeerAddr).assign(asPeerAddr.begin(), asPeerAddr.end());
    }

    if (NULL != a_pusPeerPort) {
        *a_pusPeerPort = ntohs(sockAddr.sin_port);
    }

    return true;
}
//---------------------------------------------------------------------------
bool
CxSocket::bGetSocketName(
    std::tstring_t *a_psSocketAddr,
    ushort_t       *a_pusSocketPort
)
{
    /*DEBUG*///psPeerAddr  - n/a
    /*DEBUG*///pusPeerPort - n/a

#if   xOS_ENV_WIN
    SOCKADDR_IN sockAddr     = {0};
    int         iSockAddrLen = sizeof(sockAddr);

    int iRv = ::getsockname(_m_sktSocket, CxUtils::reinterpretCastT<SOCKADDR *>( &sockAddr ), &iSockAddrLen);
    /*DEBUG*/xTEST_DIFF(xSOCKET_ERROR, iRv);
#elif xOS_ENV_UNIX
    sockaddr_in sockAddr     = {0};
    socklen_t   iSockAddrLen = sizeof(sockAddr);

    int iRv = ::getsockname(_m_sktSocket, CxUtils::reinterpretCastT<sockaddr *>( &sockAddr ), &iSockAddrLen);
    /*DEBUG*/xTEST_DIFF(xSOCKET_ERROR, iRv);
#endif

    if (NULL != a_psSocketAddr) {
        //convert to UNICODE
        std::string asSocketAddr = ::inet_ntoa(sockAddr.sin_addr);

        (*a_psSocketAddr).assign(asSocketAddr.begin(), asSocketAddr.end());
    }

    if (NULL != a_pusSocketPort) {
        *a_pusSocketPort = ntohs(sockAddr.sin_port);
    }

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
* static
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
int
CxSocket::iSelect(
    int      a_nfds,
    fd_set  *a_pReadfds,
    fd_set  *a_pWritefds,
    fd_set  *a_pExceptfds,
    timeval *a_tvTimeout
)
{
    /*DEBUG*/// nfds
    /*DEBUG*/// pReadfds
    /*DEBUG*/// pWritefds
    /*DEBUG*/// pExceptfds

     int iRv = ::select(a_nfds, a_pReadfds, a_pWritefds, a_pExceptfds, a_tvTimeout);
     /*DEBUG*/xTEST_DIFF(xSOCKET_ERROR, iRv);
     /*DEBUG*/xTEST_DIFF(0, iRv);  //zero if the time limit expired

     return iRv;
}
//---------------------------------------------------------------------------
/* static */
int
CxSocket::iGetLastError() {
    /*DEBUG*/// n/a

#if   xOS_ENV_WIN
    return ::WSAGetLastError();
#elif xOS_ENV_UNIX
    return errno;
#endif
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
