/**
 * \file  CxStdError_unix.inl
 * \brief standard C library last error
 */


xNAMESPACE_BEGIN2(xlib, debug)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxStdError::_format_impl(
    cint_t &a_code
)
{
    std::tstring_t sRv;

#if   xENV_LINUX
    char buff[64 + 1] = {0};

    ctchar_t *error = ::strerror_r(a_code, &buff[0], xARRAY_SIZE(buff));
    xCHECK_RET(error == xPTR_NULL, sRv.append(xT("[Cann't format error message]")));

    sRv.append(error);
#elif xENV_BSD
    char buff[64 + 1] = {0};

    int_t iRv = ::strerror_r(a_code, &buff[0], xARRAY_SIZE(buff));
    xCHECK_RET(iRv == - 1, sRv.append(xT("[Cann't format error message]")));

    sRv.append(&buff[0]);
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
