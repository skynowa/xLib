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
    _m_puiSocket(etInvalid),
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
    SOCKET scktSocket
)
{
    /*DEBUG*/// _m_puiSocket - n/a
    /*DEBUG*/// scktSocket   - n/a

    _m_puiSocket = scktSocket;

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
    SOCKET puiSocket
)
{
    /*DEBUG*/// _m_puiSocket - n/a
    /*DEBUG*/// scktSocket   - n/a

    _m_puiSocket = puiSocket;

    return *this;
}
//---------------------------------------------------------------------------
CxSocket::operator SOCKET () {
    /*DEBUG*/// _m_puiSocket - n/a
    /*DEBUG*/// scktSocket   - n/a

    return _m_puiSocket;
}
//---------------------------------------------------------------------------


/****************************************************************************
*
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxSocket::bCreate(
    EAddressFamily afFamily,
    EType          tpType,
    EProtocol      ptProtocol
)
{
    /*DEBUG*/xASSERT_RET(etInvalid == _m_puiSocket, false);

    _m_puiSocket = ::socket(afFamily, tpType, ptProtocol);
    /*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket, false);

    _m_siFamily = afFamily;

    return true;
}
//---------------------------------------------------------------------------
SOCKET
CxSocket::iGetSocket() const {
    /*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket, etInvalid);

    return _m_puiSocket;
}
//---------------------------------------------------------------------------
bool
CxSocket::bIsValid() const {
    /*DEBUG*/// n/a

#if xOS_ENV_WIN
    return (_m_puiSocket >= 0);
#elif xOS_ENV_UNIX
    return (_m_puiSocket >= 0);
#endif
}
//---------------------------------------------------------------------------
bool
CxSocket::bClose() {
    /*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket, false);

    int iRes = etError;

#if xOS_ENV_WIN
    iRes = shutdown(_m_puiSocket, SD_BOTH);
    /*DEBUG*/xASSERT_RET(etError != iRes, false);

    iRes = ::closesocket(_m_puiSocket);
    /*DEBUG*/xASSERT_RET(etError != iRes, false);
#elif xOS_ENV_UNIX
    iRes = ::close(_m_puiSocket);
    /*DEBUG*/xASSERT_RET(etError != iRes, false);
#endif

    _m_puiSocket = etInvalid;

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
    const tchar_t *pcszBuff,
    int            iBuffSize,
    int            iFlags
)
{
    /*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket,        etError);
    /*DEBUG*/xASSERT_RET(NULL      != pcszBuff,            etError);
    /*DEBUG*//////xASSERT_RET(0         <  ::lstrlen(pcszBuff), etError);

#if xOS_ENV_WIN
    int     iRes = ::send(_m_puiSocket, (LPCSTR)pcszBuff, iBuffSize * sizeof(tchar_t), iFlags);
    /*DEBUG*/xASSERT_RET(etError                        != iRes && WSAEWOULDBLOCK != iGetLastError(), etError);
    /*DEBUG*/xASSERT_RET(iBuffSize * (int)sizeof(tchar_t) >= iRes,                                      etError);
#elif xOS_ENV_UNIX
    #if !defined(MSG_NOSIGNAL)
        #define MSG_NOSIGNAL  0x20000
    #endif

    ssize_t iRes = ::send(_m_puiSocket, pcszBuff, iBuffSize, MSG_NOSIGNAL);
    /*DEBUG*/xASSERT_RET(etError                        != iRes, etError);
    /*DEBUG*/xASSERT_RET(iBuffSize * (int)sizeof(tchar_t) >= iRes, etError);
#endif

    return iRes / sizeof(tchar_t);
}
//---------------------------------------------------------------------------
//TODO: bSendAll
bool
CxSocket::bSendAll(
    const std::tstring_t &csBuff,
    int                   iFlags
)
{
    /*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket,   false);
    /*DEBUG*/xASSERT_RET(false     == csBuff.empty(), false);
    /*DEBUG*/xASSERT_RET(0         <  csBuff.size(),  false);

    //-------------------------------------
    //������ �� ������ ������� � ����� � ������
    int iCurrPos  = 0;
    int iLeftSize = csBuff.size() * sizeof(tchar_t);            //TODO: !!!!!!  bSendAll (overflow)

    //if size of data more than size of buffer - sizeof buffer SOCKET_BUFF_SIZE
    int iBuffOutSize  = 0;
    if (iLeftSize >= SOCKET_BUFF_SIZE) {
        iBuffOutSize = SOCKET_BUFF_SIZE;
    } else {
        iBuffOutSize = iLeftSize;
    }

    for (;;) {        /*uiLeftSize > 0*/
        int iRes = iSend(&csBuff.at(0) + iCurrPos, iBuffOutSize, iFlags);
        xCHECK_DO(etError == iRes, break);
        xCHECK_DO(0       == iRes, break);

        iCurrPos  += iRes;
        iLeftSize -= iRes;

        xCHECK_DO(iLeftSize < iBuffOutSize, iBuffOutSize = iLeftSize);

        //id data is finished - exit from loop
        if (0 >= iLeftSize) {
            /*DEBUG*/xASSERT_RET((int)csBuff.size() * (int)sizeof(tchar_t) == iCurrPos, false);
            break;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
int
CxSocket::iRecv(
    tchar_t *pszBuff,
    int      iBuffSize,
    int      iFlags
)
{
    /*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket, etError);
    /*DEBUG*/xASSERT_RET(NULL      != pszBuff,      etError);
    /*DEBUG*/xASSERT_RET(0          < iBuffSize,    etError);

    std::memset(pszBuff, 0, iBuffSize * sizeof(tchar_t));

#if xOS_ENV_WIN
    int     iRes = ::recv(_m_puiSocket, (LPSTR)pszBuff, iBuffSize * sizeof(tchar_t), iFlags);
    /*DEBUG*/xASSERT_RET(etError                        != iRes && WSAEWOULDBLOCK != iGetLastError(), etError);
    /*DEBUG*/xASSERT_RET(0                              != iRes,                                      etError);  //gracefully closed
    /*DEBUG*/xASSERT_RET(iBuffSize * (int)sizeof(tchar_t) >= iRes,                                      etError);
#elif xOS_ENV_UNIX
    ssize_t iRes = ::recv(_m_puiSocket, (char *)pszBuff, iBuffSize * sizeof(tchar_t), iFlags);
    /*DEBUG*/xASSERT_RET(etError                        != iRes,                                      etError);
    /*DEBUG*/xASSERT_RET(0                              != iRes,                                      etError);  //gracefully closed
    /*DEBUG*/xASSERT_RET(iBuffSize * (int)sizeof(tchar_t) >= iRes,                                      etError);
#endif

    return iRes / sizeof(tchar_t);
}
//---------------------------------------------------------------------------
std::tstring_t
CxSocket::sRecvAll(
    int iFlags
)
{
    std::tstring_t sRes;

    const size_t   cuiBuffSize             = 1024 * sizeof(tchar_t);
    tchar_t        szBuff[cuiBuffSize + 1] = {0};

    for (;;) {
        int   iRes  = - 1;
        ulong_t ulArg = (ulong_t)false;

    #if xOS_ENV_WIN
        iRes = ::ioctlsocket(_m_puiSocket, FIONREAD, &ulArg);
    #elif xOS_ENV_UNIX
        iRes = ::ioctl      (_m_puiSocket, FIONREAD, &ulArg);
    #endif

        xCHECK_DO(0 != iRes,           break);
        xCHECK_DO(0 == ulArg,          break);
        xCHECK_DO(cuiBuffSize < ulArg, ulArg = cuiBuffSize);

        iRes = ::recv(_m_puiSocket, (char *)&szBuff[0], ulArg, 0);
        xCHECK_DO(iRes <= 0, break);

        sRes.append(szBuff, iRes);
    }

    return sRes;
}
//---------------------------------------------------------------------------
std::tstring_t
CxSocket::sRecvAll(
    int                   iFlags,
    const std::tstring_t &csDelimiter
)
{
    std::tstring_t sRes;
    const size_t cuiInSize = SOCKET_BUFF_SIZE * sizeof(tchar_t);
    std::tstring_t sIn(cuiInSize, xT('\0'));

    //-------------------------------------
    //read from socket by blocks, write to string
    for (;;) {
        int iRes = iRecv(&sIn.at(0), cuiInSize, iFlags);
        xCHECK_DO(etError == iRes, break);
        xCHECK_DO(0       == iRes, break);

        sRes.append(sIn.begin(), sIn.begin() + iRes);

        //if delimiter was finded - break
        size_t uiDelimiterPos = sRes.find(csDelimiter);        //TODO: from unicode ???
        xCHECK_DO(std::tstring_t::npos != uiDelimiterPos, break);
    }

    return sRes;
}
//---------------------------------------------------------------------------
//TODO: iSendBytes
int
CxSocket::iSendBytes(
    char *pszBuff,
    int   iMessageLength
)
{
    int     iRC         = 0;
    int     iSendStatus = 0;
    timeval SendTimeout = {0};

    //sSetting the timeout
    SendTimeout.tv_sec  = 0;
    SendTimeout.tv_usec = SOCKET_TIMEOUT;

    fd_set fds;    FD_ZERO(&fds);
    FD_SET(_m_puiSocket, &fds);

    //..as long_t as we need to send data...
    while (iMessageLength > 0) {
        iRC = ::select(0, NULL, &fds, NULL, &SendTimeout);

        //timed out, return error
        xCHECK_RET(!iRC, etError);

        //An error occurred
        xCHECK_RET(iRC < 0, iGetLastError());

        //send a few bytes
        iSendStatus = ::send(_m_puiSocket, pszBuff, iMessageLength, 0);

        //An error occurred when sending data
        xCHECK_RET(iSendStatus < 0, iGetLastError());

        //update the buffer and the counter
        iMessageLength -= iSendStatus;
        pszBuff        += iSendStatus;
    }

    return 0;
}
//---------------------------------------------------------------------------
//TODO: ReceiveNBytes
int
CxSocket::iReceiveBytes(
    char *pszBuff,
    int   iStillToReceive
)
{
    int     iRC            = 0;
    int     iReceiveStatus = 0;
    timeval ReceiveTimeout = {0};

    //Setting the timeout
    ReceiveTimeout.tv_sec  = 0;
    ReceiveTimeout.tv_usec = SOCKET_TIMEOUT;             //500 ms

    fd_set fds;    FD_ZERO(&fds);
    FD_SET(_m_puiSocket, &fds);

    //.. Until the data is sent ..
    while (iStillToReceive > 0) {
        iRC = ::select(0, &fds, NULL, NULL, &ReceiveTimeout);

        //return by timeout
        xCHECK_RET(!iRC, etError);

        //An error occurred
        xCHECK_RET(iRC < 0, iGetLastError());

        //recive a few bytes
        iReceiveStatus = ::recv(_m_puiSocket, pszBuff, iStillToReceive, 0);

        //An error occurred when the function recv ()
        xCHECK_RET(iReceiveStatus < 0, iGetLastError());

        //changed the value of the counter and the buffer
        iStillToReceive -= iReceiveStatus;
        pszBuff         += iReceiveStatus;
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
    std::tstring_t *psPeerAddr,
    ushort_t       *pusPeerPort
)
{
    /*DEBUG*///psPeerAddr  - n/a
    /*DEBUG*///pusPeerPort - n/a

#if xOS_ENV_WIN
    SOCKADDR_IN sockAddr     = {0};
    int         iSockAddrLen = sizeof(sockAddr);

    int iRes = ::getpeername(_m_puiSocket, CxMacros::xreinterpret_cast<SOCKADDR *>( &sockAddr ), &iSockAddrLen);
    /*DEBUG*/xASSERT_RET(etError != iRes, false);
#elif xOS_ENV_UNIX
    sockaddr_in sockAddr      = {0};
    socklen_t   uiSockAddrLen = sizeof(sockAddr);

    int iRes = ::getpeername(_m_puiSocket, CxMacros::xreinterpret_cast<sockaddr *>( &sockAddr ), &uiSockAddrLen);
    /*DEBUG*/xASSERT_RET(etError != iRes, false);
#endif

    if (NULL != psPeerAddr) {
        //convert to UNICODE
        std::string asPeerAddr = ::inet_ntoa(sockAddr.sin_addr);

        (*psPeerAddr).assign(asPeerAddr.begin(), asPeerAddr.end());
    }

    if (NULL != pusPeerPort) {
        *pusPeerPort = ntohs(sockAddr.sin_port);
    }

    return true;
}
//---------------------------------------------------------------------------
bool
CxSocket::bGetSocketName(
    std::tstring_t *psSocketAddr,
    ushort_t       *pusSocketPort
)
{
    /*DEBUG*///psPeerAddr  - n/a
    /*DEBUG*///pusPeerPort - n/a

#if xOS_ENV_WIN
    SOCKADDR_IN sockAddr     = {0};
    int         iSockAddrLen = sizeof(sockAddr);

    int iRes = ::getsockname(_m_puiSocket, CxMacros::xreinterpret_cast<SOCKADDR *>( &sockAddr ), &iSockAddrLen);
    /*DEBUG*/xASSERT_RET(etError != iRes, false);
#elif xOS_ENV_UNIX
    sockaddr_in sockAddr     = {0};
    socklen_t   iSockAddrLen = sizeof(sockAddr);

    int iRes = ::getsockname(_m_puiSocket, CxMacros::xreinterpret_cast<sockaddr *>( &sockAddr ), &iSockAddrLen);
    /*DEBUG*/xASSERT_RET(etError != iRes, false);
#endif

    if (NULL != psSocketAddr) {
        //convert to UNICODE
        std::string asSocketAddr = ::inet_ntoa(sockAddr.sin_addr);

        (*psSocketAddr).assign(asSocketAddr.begin(), asSocketAddr.end());
    }

    if (NULL != pusSocketPort) {
        *pusSocketPort = ntohs(sockAddr.sin_port);
    }

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
* static
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
int
CxSocket::iSelect(
    int      nfds,
    fd_set  *pReadfds,
    fd_set  *pWritefds,
    fd_set  *pExceptfds,
    timeval *tvTimeout
)
{
    /*DEBUG*/// nfds
    /*DEBUG*/// pReadfds
    /*DEBUG*/// pWritefds
    /*DEBUG*/// pExceptfds

     int iRes = ::select(nfds, pReadfds, pWritefds, pExceptfds, tvTimeout);
     /*DEBUG*/xASSERT_RET(etError != iRes, etError);
     /*DEBUG*/xASSERT_RET(0       != iRes, 0);  //zero if the time limit expired

     return iRes;
}
//---------------------------------------------------------------------------
/*static*/
int
CxSocket::iGetLastError() {
    /*DEBUG*/// n/a

#if xOS_ENV_WIN
    return ::WSAGetLastError();
#elif xOS_ENV_UNIX
    return errno;
#endif
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
