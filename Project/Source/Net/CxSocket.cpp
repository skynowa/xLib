/**
 * \file  CxSocket.cpp
 * \brief blocking socket
 */


#include <xLib/Net/CxSocket.h>

#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTracer.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxSocket::CxSocket() :
    _socket(xSOCKET_HANDLE_INVALID),
    _family(- 1),
    _ip    (),
    _port  (0)
{
}
//------------------------------------------------------------------------------
CxSocket::~CxSocket()
{
    close();
}
//------------------------------------------------------------------------------
void_t
CxSocket::assign(
    csocket_t &a_socket
)
{
    // _socket - n/a
    // socket    - n/a

    _socket = a_socket;
}
//------------------------------------------------------------------------------


/*******************************************************************************
* operators
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxSocket &
CxSocket::operator = (
    csocket_t &a_socket
)
{
    // _socket - n/a
    // scktSocket   - n/a

    _socket = a_socket;

    return *this;
}
//------------------------------------------------------------------------------
CxSocket::operator socket_t () {
    // _socket - n/a
    // scktSocket   - n/a

    return _socket;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*
*
*******************************************************************************/

//------------------------------------------------------------------------------
void_t
CxSocket::create(
    const ExAddressFamily &a_family,
    const ExType          &a_type,
    const ExProtocol      &a_protocol
)
{
    xTEST_EQ(xSOCKET_HANDLE_INVALID, _socket);

    _socket = ::socket(a_family, a_type, a_protocol);
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);

    _family = a_family;
}
//------------------------------------------------------------------------------
socket_t
CxSocket::handle() const {
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);

    return _socket;
}
//------------------------------------------------------------------------------
bool_t
CxSocket::isValid() const {
    // n/a

#if xOS_ENV_WIN
    return (_socket >= 0);
#else
    return (_socket >= 0);
#endif
}
//------------------------------------------------------------------------------
void_t
CxSocket::close() {
    xCHECK_DO(!isValid(), return);

    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);

    int_t iRv = xSOCKET_ERROR;

#if xOS_ENV_WIN
    iRv = shutdown(_socket, SD_BOTH);
    xTEST_DIFF(xSOCKET_ERROR, iRv);

    iRv = ::closesocket(_socket);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
#else
    iRv = ::close(_socket);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
#endif

    _socket = xSOCKET_HANDLE_INVALID;
}
//------------------------------------------------------------------------------



/*******************************************************************************
* I/O
*
*******************************************************************************/

//------------------------------------------------------------------------------
//TODO: iSend
//TODO: LINUX: ssize_t send(int_t sockfd, cvoid_t *buf, size_t len, int_t flags);
int_t
CxSocket::send(
    ctchar_t *a_buff,
    cint_t   &a_buffSize,
    cint_t   &a_flags
)
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);
    xTEST_PTR(a_buff);
    /////xTEST_LESS(0, ::lstrlen(buff));

#if xOS_ENV_WIN
    int_t iRv = ::send(_socket, (LPCSTR)a_buff, a_buffSize * sizeof(tchar_t), a_flags);
    xTEST_EQ(true, xSOCKET_ERROR != iRv && WSAEWOULDBLOCK != lastError());
    xTEST_GR_EQ(a_buffSize * (int_t)sizeof(tchar_t), iRv);
#else
    #if !defined(MSG_NOSIGNAL)
        #define MSG_NOSIGNAL  0x20000
    #endif

    ssize_t iRv = ::send(_socket, a_buff, a_buffSize, MSG_NOSIGNAL);
    xTEST_DIFF(ssize_t(xSOCKET_ERROR), iRv);
    xTEST_GR_EQ(ssize_t(a_buffSize * sizeof(tchar_t)), iRv);
#endif

    return iRv / sizeof(tchar_t);
}
//------------------------------------------------------------------------------
//TODO: bSendAll
void_t
CxSocket::sendAll(
    std::ctstring_t &a_buff,
    cint_t          &a_flags
)
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);
    xTEST_EQ(false, a_buff.empty());
    xTEST_LESS(size_t(0U), a_buff.size());

    //-------------------------------------
    //������ �� ������ ������� � ����� � ������
    int_t iCurrPos  = 0;
    int_t iLeftSize = static_cast<int_t>( a_buff.size() * sizeof(tchar_t) );            //TODO: !!!!!!  bSendAll (overflow)

    //if size of data more than size of buffer - sizeof buffer SOCKET_BUFF_SIZE
    int_t iBuffOutSize  = 0;
    if (iLeftSize >= SOCKET_BUFF_SIZE) {
        iBuffOutSize = SOCKET_BUFF_SIZE;
    } else {
        iBuffOutSize = iLeftSize;
    }

    xFOREVER {        /*uiLeftSize > 0*/
        int_t iRv = send(&a_buff.at(0) + iCurrPos, iBuffOutSize, a_flags);
        xCHECK_DO(xSOCKET_ERROR == iRv, break);
        xCHECK_DO(0             == iRv, break);

        iCurrPos  += iRv;
        iLeftSize -= iRv;

        xCHECK_DO(iLeftSize < iBuffOutSize, iBuffOutSize = iLeftSize);

        //id data is finished - exit from loop
        if (0 >= iLeftSize) {
            xTEST_EQ((int_t)a_buff.size() * (int_t)sizeof(tchar_t), iCurrPos);
            break;
        }
    }
}
//------------------------------------------------------------------------------
int_t
CxSocket::recv(
    tchar_t *a_buff,
    cint_t  &a_buffSize,
    cint_t  &a_flags
)
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);
    xTEST_PTR(a_buff);
    xTEST_LESS(0, a_buffSize);

    std::memset(a_buff, 0, a_buffSize * sizeof(tchar_t));

#if xOS_ENV_WIN
    int_t   iRv = ::recv(_socket, (LPSTR)a_buff, a_buffSize * sizeof(tchar_t), a_flags);
    xTEST_EQ(true, xSOCKET_ERROR != iRv && WSAEWOULDBLOCK != lastError());
    xTEST_DIFF(0, iRv);  //gracefully closed
    xTEST_GR_EQ(a_buffSize * (int_t)sizeof(tchar_t), iRv);
#else
    ssize_t iRv = ::recv(_socket, (char *)a_buff, a_buffSize * sizeof(tchar_t), a_flags);
    xTEST_DIFF(ssize_t(xSOCKET_ERROR), iRv);
    xTEST_DIFF(ssize_t(0), iRv);  //gracefully closed
    xTEST_GR_EQ(ssize_t(a_buffSize * sizeof(tchar_t)), iRv);
#endif

    return iRv / sizeof(tchar_t);
}
//------------------------------------------------------------------------------
std::tstring_t
CxSocket::recvAll(
    cint_t &a_flags
)
{
    std::tstring_t sRv;

    std::csize_t   cuiBuffSize             = 1024 * sizeof(tchar_t);
    tchar_t        szBuff[cuiBuffSize + 1] = {0};

    xFOREVER {
        int_t   iRv  = - 1;
        ulong_t ulArg = (ulong_t)false;

    #if xOS_ENV_WIN
        iRv = ::ioctlsocket(_socket, FIONREAD, &ulArg);
    #else
        iRv = ::ioctl      (_socket, FIONREAD, &ulArg);
    #endif

        xCHECK_DO(0 != iRv,            break);
        xCHECK_DO(0 == ulArg,          break);
        xCHECK_DO(cuiBuffSize < ulArg, ulArg = cuiBuffSize);

        iRv = ::recv(_socket, (char *)&szBuff[0], ulArg, 0);
        xCHECK_DO(iRv <= 0, break);

        sRv.append(szBuff, iRv);
    }

    return sRv;
}
//------------------------------------------------------------------------------
std::tstring_t
CxSocket::recvAll(
    cint_t          &a_flags,
    std::ctstring_t &a_csDelimiter
)
{
    std::tstring_t sRv;
    std::csize_t   cuiInSize = SOCKET_BUFF_SIZE * sizeof(tchar_t);
    std::tstring_t sIn(cuiInSize, xT('\0'));

    //-------------------------------------
    //read from socket by blocks, write to string
    xFOREVER {
        int_t iRv = recv(&sIn.at(0), cuiInSize, a_flags);
        xCHECK_DO(xSOCKET_ERROR == iRv, break);
        xCHECK_DO(0             == iRv, break);

        sRv.append(sIn.begin(), sIn.begin() + iRv);

        // if delimiter was find - break
        size_t uiDelimiterPos = sRv.find(a_csDelimiter);        //TODO: from unicode ???
        xCHECK_DO(std::tstring_t::npos != uiDelimiterPos, break);
    }

    return sRv;
}
//------------------------------------------------------------------------------
//TODO: iSendBytes
int_t
CxSocket::sendBytes(
    char   *a_buff,
    cint_t &a_messageLength
)
{
    int_t   iRC            = 0;
    int_t   iSendStatus    = 0;
    timeval SendTimeout    = {0};
    int_t   iMessageLength = a_messageLength;

    //sSetting the timeout
    SendTimeout.tv_sec  = 0;
    SendTimeout.tv_usec = SOCKET_TIMEOUT;

    fd_set fds;    FD_ZERO(&fds);
    FD_SET(_socket, &fds);

    //..as long_t as we need to send data...
    while (iMessageLength > 0) {
        iRC = ::select(0, NULL, &fds, NULL, &SendTimeout);

        //timed out, return error
        xCHECK_RET(!iRC, xSOCKET_ERROR);

        //An error occurred
        xCHECK_RET(iRC < 0, lastError());

        //send a few bytes
        iSendStatus = ::send(_socket, a_buff, iMessageLength, 0);

        //An error occurred when sending data
        xCHECK_RET(iSendStatus < 0, lastError());

        //update the buffer and the counter
        iMessageLength -= iSendStatus;
        a_buff      += iSendStatus;
    }

    return 0;
}
//------------------------------------------------------------------------------
//TODO: ReceiveNBytes
int_t
CxSocket::receiveBytes(
    char   *a_buff,
    cint_t &a_stillToReceive
)
{
    int_t   iRC             = 0;
    int_t   iReceiveStatus  = 0;
    timeval ReceiveTimeout  = {0};
    int_t   iStillToReceive = a_stillToReceive;

    //Setting the timeout
    ReceiveTimeout.tv_sec  = 0;
    ReceiveTimeout.tv_usec = SOCKET_TIMEOUT;             //500 ms

    fd_set fds;    FD_ZERO(&fds);
    FD_SET(_socket, &fds);

    //.. Until the data is sent ..
    while (iStillToReceive > 0) {
        iRC = ::select(0, &fds, NULL, NULL, &ReceiveTimeout);

        //return by timeout
        xCHECK_RET(!iRC, xSOCKET_ERROR);

        //An error occurred
        xCHECK_RET(iRC < 0, lastError());

        //receive a few bytes
        iReceiveStatus = ::recv(_socket, a_buff, iStillToReceive, 0);

        //An error occurred when the function recv ()
        xCHECK_RET(iReceiveStatus < 0, lastError());

        //changed the value of the counter and the buffer
        iStillToReceive -= iReceiveStatus;
        a_buff       += iReceiveStatus;
    }

    return 0;
}
//------------------------------------------------------------------------------


/*******************************************************************************
* ...
*
*******************************************************************************/

//------------------------------------------------------------------------------
void_t
CxSocket::peerName(
    std::tstring_t *a_peerAddr,
    ushort_t       *a_peerPort
)
{
    //peerAddr  - n/a
    //peerPort - n/a

#if xOS_ENV_WIN
    SOCKADDR_IN sockAddr     = {0};
    int_t       iSockAddrLen = sizeof(sockAddr);

    int_t iRv = ::getpeername(_socket, CxUtils::reinterpretCastT<SOCKADDR *>( &sockAddr ), &iSockAddrLen);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
#else
    sockaddr_in sockAddr      = {0};
    socklen_t   uiSockAddrLen = sizeof(sockAddr);

    int_t iRv = ::getpeername(_socket, CxUtils::reinterpretCastT<sockaddr *>( &sockAddr ), &uiSockAddrLen);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
#endif

    if (NULL != a_peerAddr) {
        //convert to UNICODE
        std::string asPeerAddr = ::inet_ntoa(sockAddr.sin_addr);

        (*a_peerAddr).assign(asPeerAddr.begin(), asPeerAddr.end());
    }

    if (NULL != a_peerPort) {
        *a_peerPort = ntohs(sockAddr.sin_port);
    }
}
//------------------------------------------------------------------------------
void_t
CxSocket::socketName(
    std::tstring_t *a_socketAddr,
    ushort_t       *a_socketPort
)
{
    //peerAddr  - n/a
    //peerPort - n/a

#if xOS_ENV_WIN
    SOCKADDR_IN sockAddr     = {0};
    int_t         iSockAddrLen = sizeof(sockAddr);

    int_t iRv = ::getsockname(_socket, CxUtils::reinterpretCastT<SOCKADDR *>( &sockAddr ), &iSockAddrLen);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
#else
    sockaddr_in sockAddr     = {0};
    socklen_t   iSockAddrLen = sizeof(sockAddr);

    int_t iRv = ::getsockname(_socket, CxUtils::reinterpretCastT<sockaddr *>( &sockAddr ), &iSockAddrLen);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
#endif

    if (NULL != a_socketAddr) {
        //convert to UNICODE
        std::string asSocketAddr = ::inet_ntoa(sockAddr.sin_addr);

        (*a_socketAddr).assign(asSocketAddr.begin(), asSocketAddr.end());
    }

    if (NULL != a_socketPort) {
        *a_socketPort = ntohs(sockAddr.sin_port);
    }
}
//------------------------------------------------------------------------------


/*******************************************************************************
* static
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
int_t
CxSocket::select(
    int_t    a_nfds,
    fd_set  *a_readfds,
    fd_set  *a_writefds,
    fd_set  *a_exceptfds,
    timeval *a_timeout
)
{
    // nfds
    // pReadfds
    // pWritefds
    // pExceptfds

     int_t iRv = ::select(a_nfds, a_readfds, a_writefds, a_exceptfds, a_timeout);
     xTEST_DIFF(xSOCKET_ERROR, iRv);
     xTEST_DIFF(0, iRv);  //zero if the time limit expired

     return iRv;
}
//------------------------------------------------------------------------------
/* static */
int_t
CxSocket::lastError()
{
    // n/a

#if xOS_ENV_WIN
    return ::WSAGetLastError();
#else
    return errno;
#endif
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
