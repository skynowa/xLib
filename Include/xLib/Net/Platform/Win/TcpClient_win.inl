/**
 * \file  TcpClient.inl
 * \brief client socket
 */


namespace xl::net
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
TcpClient::_setNonBlockingMode_impl(
    cbool_t a_flag
) const
{
    ulong_t nonBlockingMode = static_cast<ulong_t>(a_flag);

    ::ioctl(FIONBIO, static_cast<ulong_t FAR *>(&nonBlockingMode));

#if 0
    int_t optVal = true;
    int_t optLen = sizeof(int_t);

    ::setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *)&optVal, optLen);
#endif
}
//-------------------------------------------------------------------------------------------------

} // namespace
