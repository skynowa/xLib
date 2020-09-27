/**
 * \file  StdError_unix.inl
 * \brief standard C library last error
 */


namespace xl::debug
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
StdError::_format_impl(
    cint_t &a_code
)
{
    char buff[64 + 1] = {0};

    const char *error = ::strerror_r(a_code, &buff[0], xARRAY_SIZE(buff));
    xCHECK_RET(error == nullptr, xT("[Cann't format error message]"));

    return xA2T(error);
}
//-------------------------------------------------------------------------------------------------

} // namespace
