/**
 * \file  Socket.inl
 * \brief blocking socket
 */


xNAMESPACE_BEGIN2(xl, net)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
Socket::_close_impl()
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
xINLINE ssize_t
Socket::_send_impl(
    cptr_ctchar_t  a_buff,
    std::csize_t  &a_buffSize,
    cint_t        &a_flags
)
{
    xUNUSED(a_flags);

    // TODO: a_flags as MSG_NOSIGNAL
#if !defined(MSG_NOSIGNAL)
    cint_t MSG_NOSIGNAL = 0x20000;
#endif

    ssize_t iRv = ::send(_handle, a_buff, a_buffSize, MSG_NOSIGNAL);
    xTEST_DIFF(iRv, ssize_t(xSOCKET_ERROR));
    xTEST_GR_EQ(ssize_t(a_buffSize * sizeof(tchar_t)), iRv);

    return iRv / static_cast< ::ssize_t >( sizeof(tchar_t) );
}
//-------------------------------------------------------------------------------------------------
xINLINE ssize_t
Socket::_receive_impl(
    cptr_ctchar_t  a_buff,
    std::csize_t  &a_buffSize,
    cint_t        &a_flags
)
{
    ssize_t iRv = ::recv(_handle, (char *)a_buff, a_buffSize * sizeof(tchar_t), a_flags);
    xTEST_DIFF(iRv, (ssize_t)xSOCKET_ERROR);
    xTEST_DIFF(iRv, (ssize_t)0);  // gracefully closed
    xTEST_GR_EQ(ssize_t(a_buffSize * sizeof(tchar_t)), iRv);

    return iRv / static_cast< ::ssize_t >( sizeof(tchar_t) );
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
* ...
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
Socket::_peerName_impl(
    std::tstring_t *a_peerAddr,
    ushort_t       *a_peerPort
)
{
    sockaddr_in sockAddr;   xSTRUCT_ZERO(sockAddr);
    socklen_t   sockAddrLen = sizeof(sockAddr);

    int_t iRv = ::getpeername(_handle, Utils::reinterpretCastT<sockaddr *>( &sockAddr ),
        &sockAddrLen);
    xTEST_DIFF(iRv, xSOCKET_ERROR);

    // out
    if (a_peerAddr != xPTR_NULL) {
        std::string peerAddr = ::inet_ntoa(sockAddr.sin_addr);

        *a_peerAddr = xA2T(peerAddr);
    }

    if (a_peerPort != xPTR_NULL) {
        *a_peerPort = ntohs(sockAddr.sin_port);
    }

}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Socket::_socketName_impl(
    std::tstring_t *a_socketAddr,
    ushort_t       *a_socketPort
)
{
    sockaddr_in sockAddr;   xSTRUCT_ZERO(sockAddr);
    socklen_t   sockAddrLen = sizeof(sockAddr);

    int_t iRv = ::getsockname(_handle, Utils::reinterpretCastT<sockaddr *>( &sockAddr ),
        &sockAddrLen);
    xTEST_DIFF(iRv, xSOCKET_ERROR);

    // out
    if (a_socketAddr != xPTR_NULL) {
        std::string socketAddr = ::inet_ntoa(sockAddr.sin_addr);

        *a_socketAddr = xA2T(socketAddr);
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
xINLINE int_t
Socket::_nativeError_impl()
{
    return errno;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, net)
