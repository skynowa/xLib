/**
 * \file  StdError_unix.inl
 * \brief standard C library last error
 */


xNAMESPACE_BEGIN2(xlib, debug)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
StdError::_format_impl(
    cint_t &a_code
)
{
    std::tstring_t sRv;

    char buff[64 + 1] = {0};

    int_t iRv = ::strerror_r(a_code, &buff[0], xARRAY_SIZE(buff));
    xCHECK_RET(iRv == - 1, sRv.append(xT("[Cann't format error message]")));

    sRv.append(&buff[0]);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
