/**
 * \file  NativeError.inl
 * \brief system last error
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
NativeError::_format_impl(
    culong_t a_code
)
{
    std::string asRv;

    char buff[64 + 1] = {0};

    const char *error = ::strerror_r(static_cast<int_t>( a_code ), &buff[0], xARRAY_SIZE(buff));
    xCHECK_RET(error == nullptr, xT("[Cann't format error message]"));

    asRv.append(error);

    return xA2T(asRv);
}
//-------------------------------------------------------------------------------------------------

} // namespace
