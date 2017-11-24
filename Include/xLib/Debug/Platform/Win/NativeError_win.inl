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
bool_t
NativeError::_isSuccess_impl()
{
    bool_t bRv = (::GetLastError() == _nativeCodeSuccess());

    return bRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
ulong_t
NativeError::_get_impl()
{
    culong_t code = ::GetLastError();

    return code;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
NativeError::_set_impl(
    culong_t &a_code
)
{
    (void_t)::SetLastError(a_code);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
NativeError::_format_impl(
    culong_t &a_code
)
{
    std::tstring_t sRv;

    DWORD  dwRv = 0UL;
    LPVOID buff = xPTR_NULL;

    dwRv = ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS, xPTR_NULL, a_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPTSTR>( &buff ), 0UL, xPTR_NULL);

    xCHECK_RET(get() == ERROR_MR_MID_NOT_FOUND, sRv.append(xT("Unknown error")));
    xCHECK_RET(dwRv  == 0UL,                    sRv.append(xT("[Cann't format error message]")));

    std::tstring_t msg;

    msg.assign( static_cast<LPCTSTR>( buff ), dwRv );
    msg = String::removeEol(msg);
    msg = String::trimRightChars(msg, Const::dot());

    sRv.append(msg);

    (void_t)::LocalFree(buff);

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
ulong_t
NativeError::_nativeCodeSuccess_impl()
{
    return ERROR_SUCCESS;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, debug)
