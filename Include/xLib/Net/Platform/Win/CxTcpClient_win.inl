/**
 * \file  CxTcpClient.inl
 * \brief client socket
 */


xNAMESPACE_BEGIN2(xlib, net)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxTcpClient::_setNonBlockingMode_impl(
    cbool_t &a_flag
) const
{
    ulong_t nonBlockingMode = static_cast<ulong_t>(a_flag);

    ::ioctl(FIONBIO, static_cast<ulong_t FAR *>(&nonBlockingMode));

#if 0
    int_t optVal = true;
    int_t optLen = sizeof(int_t);

    ::setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *)&optVal, optLen);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
