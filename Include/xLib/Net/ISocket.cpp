/**
 * \file  ISocket.inl
 * \brief blocking socket
 */


#include "ISocket.h"

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>
#include <xLib/Core/Utils.h>

#if   xENV_WIN
    #include "Platform/Win/Socket_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Socket_unix.inl"
#endif


xNAMESPACE_BEGIN2(xl, net)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
ISocket::ISocket() :
    _handle(),
    _family(- 1),
    _ip    (),
    _port  (0)
{
}
//-------------------------------------------------------------------------------------------------
ISocket::~ISocket()
{
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
ISocket::create(
    cAddressFamily &a_family,
    cType          &a_type,
    cProtocol      &a_protocol
)
{
    xTEST_EQ(_handle.isValid(), false);

    _handle = ::socket(a_family, a_type, a_protocol);
    xTEST_DIFF(_handle.isValid(), true);

    _family = a_family;
}
//-------------------------------------------------------------------------------------------------
HandleSocket &
ISocket::handle()
{
    xTEST_EQ(_handle.isValid(), true);

    return _handle;
}
//-------------------------------------------------------------------------------------------------
bool_t
ISocket::isReadable() const
{
    timeval timeoutVal = {1, 0};
    fd_set  fds;         FD_ZERO(&fds);

    FD_SET(_handle.get(), &fds);

    int_t iRv = ::select(0, &fds, xPTR_NULL, xPTR_NULL, &timeoutVal);
    xCHECK_RET(iRv <= 0 || !FD_ISSET(_handle.get(), &fds), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
ISocket::isWritable() const
{
    timeval timeoutVal = {1, 0};
    fd_set  fds;         FD_ZERO(&fds);

    FD_SET(_handle.get(), &fds);

    int_t iRv = ::select(0, xPTR_NULL, &fds, xPTR_NULL, &timeoutVal);
    xCHECK_RET(iRv <= 0 || !FD_ISSET(_handle.get(), &fds), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
ISocket::assign(
    csocket_t &a_handle
)
{
    xTEST_NA(_handle);
    xTEST_NA(a_handle);

    _handle = a_handle;
}
//-------------------------------------------------------------------------------------------------
void_t
ISocket::close()
{
    xTESTS_NA;

    _handle.close();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
* I/O
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
ssize_t
ISocket::send(
    cptr_ctchar_t  a_buff,
    std::csize_t  &a_buffSize,
    cint_t        &a_flags
)
{
    // TODO: ISocket::send() - LINUX: ssize_t send(int_t sockfd, cptr_cvoid_t buf, size_t len, int_t flags);

    xTEST_EQ(_handle.isValid(), true);
    xTEST_PTR(a_buff);
    /////xTEST_LESS(0, ::lstrlen(buff));

    return _send_impl(a_buff, a_buffSize, a_flags);
}
//-------------------------------------------------------------------------------------------------
void_t
ISocket::sendAll(
    std::ctstring_t &a_buff,
    cint_t          &a_flags
)
{
    xTEST_EQ(_handle.isValid(), true);
    xTEST_EQ(a_buff.empty(), false);
    xTEST_LESS(size_t(0U), a_buff.size());

    size_t currPos  = 0;
    // TODO: ISocket::send() - overflow ISocket::sendAll()
    size_t leftSize = a_buff.size() * sizeof(tchar_t);

    // if size of data more than size of buffer - sizeof buffer SOCKET_BUFF_SIZE
    size_t buffOutSize  = 0;
    if (leftSize >= SOCKET_BUFF_SIZE) {
        buffOutSize = SOCKET_BUFF_SIZE;
    } else {
        buffOutSize = leftSize;
    }

    for ( ; ; ) {        /* uiLeftSize > 0 */
        ssize_t iRv = send(&a_buff.at(0) + currPos, buffOutSize, a_flags);
        xCHECK_DO(iRv == xSOCKET_ERROR, break);
        xCHECK_DO(iRv == 0,             break);

        currPos  += static_cast<std::size_t>(iRv);
        leftSize -= static_cast<std::size_t>(iRv);

        xCHECK_DO(leftSize < buffOutSize, buffOutSize = leftSize);

        // id data is finished - exit from loop
        if (0 >= leftSize) {
            xTEST_EQ(a_buff.size() * sizeof(tchar_t), currPos);
            break;
        }
    }
}
//-------------------------------------------------------------------------------------------------
ssize_t
ISocket::receive(
    tchar_t      *a_buff,
    std::csize_t &a_buffSize,
    cint_t       &a_flags
)
{
    xTEST_EQ(_handle.isValid(), true);
    xTEST_PTR(a_buff);
    xTEST_DIFF(a_buffSize, (size_t)0);

    std::memset(a_buff, 0, a_buffSize * sizeof(tchar_t));

    return _receive_impl(a_buff, a_buffSize, a_flags);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
ISocket::recvAll(
    cint_t &a_flags
)
{
    xTEST_NA(a_flags);

    std::tstring_t sRv;
    std::csize_t   buffSize           = 1024 * sizeof(tchar_t);
    tchar_t        buff[buffSize + 1] = {0};

    for ( ; ; ) {
        int_t   iRv = - 1;
        ulong_t arg = (ulong_t)a_flags;

        iRv = xIOCTLSOCKET(_handle.get(), FIONREAD, &arg);
        xCHECK_DO(iRv != 0,       break);
        xCHECK_DO(arg == 0,       break);
        xCHECK_DO(buffSize < arg, arg = buffSize);

        ssize_t uiRv = ::recv(_handle.get(), (char *)&buff[0], arg, 0);
        xCHECK_DO(uiRv <= 0, break);

        sRv.append(buff, static_cast<std::size_t>(uiRv));
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
ISocket::recvAll(
    cint_t          &a_flags,
    std::ctstring_t &a_delimiter
)
{
    std::tstring_t sRv;
    std::size_t    inSize = SOCKET_BUFF_SIZE * sizeof(tchar_t);
    std::tstring_t in(inSize, xT('\0'));

    // read from socket by blocks, write to string
    for ( ; ; ) {
        ssize_t iRv = receive(&in.at(0), inSize, a_flags);
        xCHECK_DO(iRv == xSOCKET_ERROR, break);
        xCHECK_DO(iRv == 0,             break);

        sRv.append(in.begin(), in.begin() + iRv);

        // if delimiter was find - break
        size_t delimiterPos = sRv.find(a_delimiter); // TODO: ISocket::recvAll() - from unicode ???
        xCHECK_DO(delimiterPos != std::tstring_t::npos, break);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
int_t
ISocket::sendBytes(
    char    *a_buff,
    ssize_t &a_messageLength
)
{
    // TODO: ISocket::sendBytes()

    int_t   iRv           = 0;
    ssize_t sendStatus    = 0;
    timeval sendTimeout   = {0, 0};
    ssize_t messageLength = a_messageLength;

    // setting the timeout
    sendTimeout.tv_sec  = 0;
    sendTimeout.tv_usec = SOCKET_TIMEOUT;

    fd_set fds;    FD_ZERO(&fds);
    FD_SET(_handle.get(), &fds);

    // ..as long_t as we need to send data...
    while (messageLength > 0) {
        iRv = ::select(0, xPTR_NULL, &fds, xPTR_NULL, &sendTimeout);

        // timed out, return error
        xCHECK_RET(!iRv, xSOCKET_ERROR);

        // An error occurred
        xCHECK_RET(iRv < 0, nativeError());

        // send a few bytes
        sendStatus = ::send(_handle.get(), a_buff, static_cast<std::size_t>(messageLength), 0);

        // An error occurred when sending data
        xCHECK_RET(sendStatus < 0, nativeError());

        // update the buffer and the counter
        messageLength -= sendStatus;
        a_buff        += sendStatus;
    }

    return 0;
}
//-------------------------------------------------------------------------------------------------
int_t
ISocket::receiveBytes(
    char    *a_buff,
    ssize_t &a_stillToReceive
)
{
    int_t   iRv            = 0;
    ssize_t receiveStatus  = 0;
    timeval receiveTimeout = {0, 0};
    ssize_t stillToReceive = a_stillToReceive;

    // Setting the timeout
    receiveTimeout.tv_sec  = 0;
    receiveTimeout.tv_usec = SOCKET_TIMEOUT;

    fd_set fds;    FD_ZERO(&fds);
    FD_SET(_handle.get(), &fds);

    // Until the data is sent
    while (stillToReceive > 0) {
        iRv = ::select(0, &fds, xPTR_NULL, xPTR_NULL, &receiveTimeout);

        // return by timeout
        xCHECK_RET(!iRv, xSOCKET_ERROR);

        // An error occurred
        xCHECK_RET(iRv < 0, nativeError());

        // receive a few bytes
        receiveStatus = ::recv(_handle.get(), a_buff, static_cast<std::size_t>(stillToReceive), 0);

        // An error occurred when the function recv ()
        xCHECK_RET(receiveStatus < 0, nativeError());

        // changed the value of the counter and the buffer
        stillToReceive -= receiveStatus;
        a_buff         += receiveStatus;
    }

    return 0;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
* ...
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
ISocket::peerName(
    std::tstring_t *a_peerAddr,
    ushort_t       *a_peerPort
)
{
    xTEST_NA(a_peerAddr);
    xTEST_NA(a_peerPort);

    _peerName_impl(a_peerAddr, a_peerPort);
}
//-------------------------------------------------------------------------------------------------
void_t
ISocket::socketName(
    std::tstring_t *a_socketAddr,
    ushort_t       *a_socketPort
)
{
    xTEST_NA(a_socketAddr);
    xTEST_NA(a_socketPort);

    _socketName_impl(a_socketAddr, a_socketPort);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
* static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
int_t
ISocket::select(
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
     xTEST_DIFF(iRv, xSOCKET_ERROR);
     xTEST_DIFF(iRv, 0);  // zero if the time limit expired

     return iRv;
}
//-------------------------------------------------------------------------------------------------
int_t
ISocket::nativeError()
{
    // n/a

    return _nativeError_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, net)
