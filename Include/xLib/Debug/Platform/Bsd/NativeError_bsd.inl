/**
 * \file  NativeError.inl
 * \brief system last error
 */


xNAMESPACE_BEGIN2(xl, debug)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
NativeError::_format_impl(
    culong_t &a_code
)
{
    std::tstring_t sRv;

    char buff[64 + 1] = {0};

    int_t iRv = ::strerror_r(static_cast<int_t>( a_code ), &buff[0], xARRAY_SIZE(buff));
    xCHECK_RET(iRv == - 1, sRv.append(xT("[Cann't format error message]")));

    sRv.append(&buff[0]);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, debug)
