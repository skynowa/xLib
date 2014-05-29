/**
 * \file  CxSocket.inl
 * \brief blocking socket
 */


xNAMESPACE_BEGIN2(xlib, net)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxSocket::_close_impl()
{
    xCHECK_DO(!isValid(), return);

    int_t iRv = ::close(_handle);
    xTEST_DIFF(iRv, xSOCKET_ERROR);

    _handle = xSOCKET_HANDLE_INVALID;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
* I/O
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline ssize_t
CxSocket::_send_impl(
    ctchar_t     *a_buff,
    std::csize_t &a_buffSize,
    cint_t       &a_flags
)
{
    xUNUSED(a_flags);

    #if !defined(MSG_NOSIGNAL)
        cint_t MSG_NOSIGNAL = 0x20000;
    #endif

    ssize_t iRv = ::send(_handle, a_buff, a_buffSize, MSG_NOSIGNAL);
    xTEST_DIFF(iRv, ssize_t(xSOCKET_ERROR));
    xTEST_GR_EQ(ssize_t(a_buffSize * sizeof(tchar_t)), iRv);

    return iRv / sizeof(tchar_t);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
* ...
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxSocket::_peerName_impl(
    std::tstring_t *a_peerAddr,
    ushort_t       *a_peerPort
)
{
    sockaddr_in sockAddr;   xSTRUCT_ZERO(sockAddr);
    socklen_t   sockAddrLen = sizeof(sockAddr);

    int_t iRv = ::getpeername(_handle, CxUtils::reinterpretCastT<sockaddr *>( &sockAddr ),
        &sockAddrLen);
    xTEST_DIFF(iRv, xSOCKET_ERROR);

    // out
    if (a_peerAddr != xPTR_NULL) {
        // convert to UNICODE
        std::string peerAddr = ::inet_ntoa(sockAddr.sin_addr);

        a_peerAddr->assign(peerAddr.begin(), peerAddr.end());
    }

    if (a_peerPort != xPTR_NULL) {
        *a_peerPort = ntohs(sockAddr.sin_port);
    }

}
//-------------------------------------------------------------------------------------------------
inline void_t
CxSocket::_socketName_impl(
    std::tstring_t *a_socketAddr,
    ushort_t       *a_socketPort
)
{
    sockaddr_in sockAddr;   xSTRUCT_ZERO(sockAddr);
    socklen_t   sockAddrLen = sizeof(sockAddr);

    int_t iRv = ::getsockname(_handle, CxUtils::reinterpretCastT<sockaddr *>( &sockAddr ),
        &sockAddrLen);
    xTEST_DIFF(iRv, xSOCKET_ERROR);

    // out
    if (a_socketAddr != xPTR_NULL) {
        // convert to UNICODE
        std::string socketAddr = ::inet_ntoa(sockAddr.sin_addr);

        a_socketAddr->assign(socketAddr.begin(), socketAddr.end());
    }

    if (a_socketPort != xPTR_NULL) {
        *a_socketPort = ntohs(sockAddr.sin_port);
    }
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
* static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline int_t
CxSocket::_lastError_impl()
{
    return errno;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
