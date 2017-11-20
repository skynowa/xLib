/**
 * \file  TcpClient.inl
 * \brief client socket
 */


xNAMESPACE_BEGIN2(xl, net)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
TcpClient::_setNonBlockingMode_impl(
    cbool_t &a_flag
) const
{
    int_t flags = - 1;

    flags = ::fcntl(_handle.get(), F_GETFL);
    xTEST_DIFF(flags, xSOCKET_ERROR);

    if (a_flag) {
        flags = (flags |  O_NONBLOCK);
    } else {
        flags = (flags & ~O_NONBLOCK);
    }

    flags = ::fcntl(_handle.get(), F_SETFL, flags);
    xTEST_DIFF(flags, xSOCKET_ERROR);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, net)
