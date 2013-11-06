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
#include <xLib/Core/CxUtils.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxSocket::CxSocket() :
    _socket(xSOCKET_HANDLE_INVALID),
    _family(- 1),
    _ip    (),
    _port  (0)
{
}
//------------------------------------------------------------------------------
xINLINE_HO
CxSocket::~CxSocket()
{
    close();
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
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
xINLINE_HO CxSocket &
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
xINLINE_HO
CxSocket::operator socket_t ()
{
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
xINLINE_HO void_t
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
xINLINE_HO socket_t
CxSocket::handle() const {
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);

    return _socket;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxSocket::isValid() const {
    // n/a

#if xOS_ENV_WIN
    return (_socket >= 0);
#else
    return (_socket >= 0);
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
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
xINLINE_HO int_t
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
    xTEST_EQ(true, xSOCKET_ERROR != iRv && WSAEWOULDBLOCK != CxSocket::lastError());
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
xINLINE_HO void_t
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
    int_t currPos  = 0;
    // TODO: !!!!!!  bSendAll (overflow)
    int_t leftSize = static_cast<int_t>( a_buff.size() * sizeof(tchar_t) );

    //if size of data more than size of buffer - sizeof buffer SOCKET_BUFF_SIZE
    int_t buffOutSize  = 0;
    if (leftSize >= SOCKET_BUFF_SIZE) {
        buffOutSize = SOCKET_BUFF_SIZE;
    } else {
        buffOutSize = leftSize;
    }

    xFOREVER {        /*uiLeftSize > 0*/
        int_t iRv = send(&a_buff.at(0) + currPos, buffOutSize, a_flags);
        xCHECK_DO(xSOCKET_ERROR == iRv, break);
        xCHECK_DO(0             == iRv, break);

        currPos  += iRv;
        leftSize -= iRv;

        xCHECK_DO(leftSize < buffOutSize, buffOutSize = leftSize);

        //id data is finished - exit from loop
        if (0 >= leftSize) {
            xTEST_EQ((int_t)a_buff.size() * (int_t)sizeof(tchar_t), currPos);
            break;
        }
    }
}
//------------------------------------------------------------------------------
xINLINE_HO int_t
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
    int_t iRv = ::recv(_socket, (LPSTR)a_buff, a_buffSize * sizeof(tchar_t), a_flags);
    xTEST_EQ(true, xSOCKET_ERROR != iRv && WSAEWOULDBLOCK != CxSocket::lastError());
    xTEST_DIFF(0, iRv);  // gracefully closed
    xTEST_GR_EQ(a_buffSize * (int_t)sizeof(tchar_t), iRv);
#else
    ssize_t iRv = ::recv(_socket, (char *)a_buff, a_buffSize * sizeof(tchar_t), a_flags);
    xTEST_DIFF(ssize_t(xSOCKET_ERROR), iRv);
    xTEST_DIFF(ssize_t(0), iRv);  // gracefully closed
    xTEST_GR_EQ(ssize_t(a_buffSize * sizeof(tchar_t)), iRv);
#endif

    return iRv / sizeof(tchar_t);
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxSocket::recvAll(
    cint_t &a_flags
)
{
    std::tstring_t sRv;

    std::csize_t   buffSize           = 1024 * sizeof(tchar_t);
    tchar_t        buff[buffSize + 1] = {0};

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
        xCHECK_DO(buffSize < ulArg, ulArg = buffSize);

        iRv = ::recv(_socket, (char *)&buff[0], ulArg, 0);
        xCHECK_DO(iRv <= 0, break);

        sRv.append(buff, iRv);
    }

    return sRv;
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxSocket::recvAll(
    cint_t          &a_flags,
    std::ctstring_t &a_csDelimiter
)
{
    std::tstring_t sRv;
    std::csize_t   inSize = SOCKET_BUFF_SIZE * sizeof(tchar_t);
    std::tstring_t in(inSize, xT('\0'));

    //-------------------------------------
    //read from socket by blocks, write to string
    xFOREVER {
        int_t iRv = recv(&in.at(0), inSize, a_flags);
        xCHECK_DO(xSOCKET_ERROR == iRv, break);
        xCHECK_DO(0             == iRv, break);

        sRv.append(in.begin(), in.begin() + iRv);

        // if delimiter was find - break
        size_t delimiterPos = sRv.find(a_csDelimiter);        //TODO: from unicode ???
        xCHECK_DO(std::tstring_t::npos != delimiterPos, break);
    }

    return sRv;
}
//------------------------------------------------------------------------------
//TODO: iSendBytes
xINLINE_HO int_t
CxSocket::sendBytes(
    char   *a_buff,
    cint_t &a_messageLength
)
{
    int_t   iRC            = 0;
    int_t   sendStatus    = 0;
    timeval sendTimeout    = {0};
    int_t   messageLength = a_messageLength;

    //sSetting the timeout
    sendTimeout.tv_sec  = 0;
    sendTimeout.tv_usec = SOCKET_TIMEOUT;

    fd_set fds;    FD_ZERO(&fds);
    FD_SET(_socket, &fds);

    //..as long_t as we need to send data...
    while (messageLength > 0) {
        iRC = ::select(0, NULL, &fds, NULL, &sendTimeout);

        //timed out, return error
        xCHECK_RET(!iRC, xSOCKET_ERROR);

        //An error occurred
        xCHECK_RET(iRC < 0, lastError());

        //send a few bytes
        sendStatus = ::send(_socket, a_buff, messageLength, 0);

        //An error occurred when sending data
        xCHECK_RET(sendStatus < 0, lastError());

        //update the buffer and the counter
        messageLength -= sendStatus;
        a_buff        += sendStatus;
    }

    return 0;
}
//------------------------------------------------------------------------------
//TODO: ReceiveNBytes
xINLINE_HO int_t
CxSocket::receiveBytes(
    char   *a_buff,
    cint_t &a_stillToReceive
)
{
    int_t   iRC             = 0;
    int_t   receiveStatus  = 0;
    timeval receiveTimeout  = {0};
    int_t   stillToReceive = a_stillToReceive;

    //Setting the timeout
    receiveTimeout.tv_sec  = 0;
    receiveTimeout.tv_usec = SOCKET_TIMEOUT;             //500 ms

    fd_set fds;    FD_ZERO(&fds);
    FD_SET(_socket, &fds);

    //.. Until the data is sent ..
    while (stillToReceive > 0) {
        iRC = ::select(0, &fds, NULL, NULL, &receiveTimeout);

        //return by timeout
        xCHECK_RET(!iRC, xSOCKET_ERROR);

        //An error occurred
        xCHECK_RET(iRC < 0, lastError());

        //receive a few bytes
        receiveStatus = ::recv(_socket, a_buff, stillToReceive, 0);

        //An error occurred when the function recv ()
        xCHECK_RET(receiveStatus < 0, lastError());

        //changed the value of the counter and the buffer
        stillToReceive -= receiveStatus;
        a_buff         += receiveStatus;
    }

    return 0;
}
//------------------------------------------------------------------------------


/*******************************************************************************
* ...
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxSocket::peerName(
    std::tstring_t *a_peerAddr,
    ushort_t       *a_peerPort
)
{
    //peerAddr  - n/a
    //peerPort - n/a

#if xOS_ENV_WIN
    SOCKADDR_IN sockAddr     = {0};
    int_t       sockAddrLen = sizeof(sockAddr);

    int_t iRv = ::getpeername(_socket, CxUtils::reinterpretCastT<SOCKADDR *>( &sockAddr ),
        &sockAddrLen);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
#else
    sockaddr_in sockAddr      = {0};
    socklen_t   sockAddrLen = sizeof(sockAddr);

    int_t iRv = ::getpeername(_socket, CxUtils::reinterpretCastT<sockaddr *>( &sockAddr ),
        &sockAddrLen);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
#endif

    if (NULL != a_peerAddr) {
        //convert to UNICODE
        std::string peerAddr = ::inet_ntoa(sockAddr.sin_addr);

        (*a_peerAddr).assign(peerAddr.begin(), peerAddr.end());
    }

    if (NULL != a_peerPort) {
        *a_peerPort = ntohs(sockAddr.sin_port);
    }
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxSocket::socketName(
    std::tstring_t *a_socketAddr,
    ushort_t       *a_socketPort
)
{
    //peerAddr  - n/a
    //peerPort - n/a

#if xOS_ENV_WIN
    SOCKADDR_IN sockAddr     = {0};
    int_t       sockAddrLen = sizeof(sockAddr);

    int_t iRv = ::getsockname(_socket, CxUtils::reinterpretCastT<SOCKADDR *>( &sockAddr ),
        &sockAddrLen);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
#else
    sockaddr_in sockAddr     = {0};
    socklen_t   sockAddrLen = sizeof(sockAddr);

    int_t iRv = ::getsockname(_socket, CxUtils::reinterpretCastT<sockaddr *>( &sockAddr ),
        &sockAddrLen);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
#endif

    if (NULL != a_socketAddr) {
        //convert to UNICODE
        std::string socketAddr = ::inet_ntoa(sockAddr.sin_addr);

        (*a_socketAddr).assign(socketAddr.begin(), socketAddr.end());
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
xINLINE_HO int_t
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
xINLINE_HO int_t
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
