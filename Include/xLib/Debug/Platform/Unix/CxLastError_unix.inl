/**
 * \file  CxLastError.inl
 * \brief system last error
 */


xNAMESPACE_BEGIN2(xlib, debug)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxLastError::_isSuccess_impl()
{
    bool_t bRv = (static_cast<ulong_t>( errno ) == _nativeCodeSuccess());

    return bRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline ulong_t
CxLastError::_get_impl()
{
    culong_t code = static_cast<ulong_t>( errno );

    return code;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxLastError::_set_impl(
    culong_t &a_code
)
{
    errno = static_cast<int_t>( a_code );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxLastError::_format_impl(
    culong_t &a_code
)
{
    std::tstring_t sRv;

#if   xENV_LINUX
    char buff[64 + 1] = {0};

    ctchar_t *error = ::strerror_r(static_cast<int_t>( a_code ), &buff[0], xARRAY_SIZE(buff));
    xCHECK_RET(error == xPTR_NULL, sRv.append(xT("[Cann't format error message]")));

    sRv.append(error);
#elif xENV_BSD
    char buff[64 + 1] = {0};

    int_t iRv = ::strerror_r(static_cast<int_t>( a_code ), &buff[0], xARRAY_SIZE(buff));
    xCHECK_RET(iRv == - 1, sRv.append(xT("[Cann't format error message]")));

    sRv.append(&buff[0]);
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline ulong_t
CxLastError::_nativeCodeSuccess_impl()
{
    return 0UL;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
