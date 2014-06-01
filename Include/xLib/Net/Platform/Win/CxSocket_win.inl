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

    xTEST_DIFF(_handle, xSOCKET_HANDLE_INVALID);

    int_t iRv = shutdown(_handle, SD_BOTH);
    xTEST_DIFF(iRv, xSOCKET_ERROR);

    iRv = ::closesocket(_handle);
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
    ssize_t iRv = ::send(_handle, (LPCSTR)a_buff, a_buffSize * sizeof(tchar_t), a_flags);
    xTEST_EQ(iRv != xSOCKET_ERROR && CxSocket::lastError() != WSAEWOULDBLOCK, true);
    xTEST_GR_EQ(ssize_t(a_buffSize * sizeof(tchar_t)), iRv);

    return iRv / sizeof(tchar_t);
}
//-------------------------------------------------------------------------------------------------
inline ssize_t
CxSocket::_receive_impl(
    tchar_t      *a_buff,
    std::csize_t &a_buffSize,
    cint_t       &a_flags
)
{
#if xENV_WIN
    int_t iRv = ::recv(_handle, (LPSTR)a_buff, a_buffSize * sizeof(tchar_t), a_flags);
    xTEST_EQ(iRv != xSOCKET_ERROR && CxSocket::lastError() != WSAEWOULDBLOCK, true);
    xTEST_DIFF(iRv, 0);  // gracefully closed
    xTEST_GR_EQ(int_t(a_buffSize * sizeof(tchar_t)), iRv);
#endif

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
    SOCKADDR_IN sockAddr    = {0};
    int_t       sockAddrLen = sizeof(sockAddr);

    int_t iRv = ::getpeername(_handle, CxUtils::reinterpretCastT<SOCKADDR *>( &sockAddr ),
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
    SOCKADDR_IN sockAddr     = {0};
    int_t       sockAddrLen = sizeof(sockAddr);

    int_t iRv = ::getsockname(_handle, CxUtils::reinterpretCastT<SOCKADDR *>( &sockAddr ),
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
    return ::WSAGetLastError();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
