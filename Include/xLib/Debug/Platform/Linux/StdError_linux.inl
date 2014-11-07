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

    ctchar_t *error = ::strerror_r(a_code, &buff[0], xARRAY_SIZE(buff));
    xCHECK_RET(error == xPTR_NULL, sRv.append(xT("[Cann't format error message]")));

    sRv.append(error);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
