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
    int_t flags = - 1;

    flags = ::fcntl(_handle, F_GETFL);
    xTEST_DIFF(flags, xSOCKET_ERROR);

    if (a_flag) {
        flags = (flags |  O_NONBLOCK);
    } else {
        flags = (flags & ~O_NONBLOCK);
    }

    flags = ::fcntl(_handle, F_SETFL, flags);
    xTEST_DIFF(flags, xSOCKET_ERROR);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
