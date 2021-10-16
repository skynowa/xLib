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

    ::ioctlsocket(_handle.get(), FIONBIO, &nonBlockingMode);
}
//-------------------------------------------------------------------------------------------------

} // namespace
