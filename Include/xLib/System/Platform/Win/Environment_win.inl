/**
 * \file  Environment.inl
 * \brief system environment variables
 */


namespace xl::system
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Environment::_isExists_impl() const
{
    std::tstring_t sRv;
    sRv.resize(xPATH_MAX);

    DWORD length = ::GetEnvironmentVariable(_varName.c_str(), &sRv.at(0),
        static_cast<DWORD>( sRv.size() ));
    xTEST_NA(length);

    xCHECK_RET(length == 0UL && NativeError::get() == ERROR_ENVVAR_NOT_FOUND, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Environment::_var_impl() const
{
    std::tstring_t sRv;

    sRv.resize(xPATH_MAX);

    DWORD length = ::GetEnvironmentVariable(_varName.c_str(), &sRv.at(0),
        static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(length, 0UL);

    sRv.resize(length);

    if (sRv.size() < length) {
        length = ::GetEnvironmentVariable(_varName.c_str(), &sRv.at(0),
            static_cast<DWORD>( sRv.size() ));
        xTEST_DIFF(length, 0UL);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Environment::_setVar_impl(
    std::ctstring_t &a_value
) const
{
    BOOL blRv = ::SetEnvironmentVariable(_varName.c_str(), a_value.c_str());
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
void_t
Environment::_removeVar_impl() const
{
    BOOL blRv = ::SetEnvironmentVariable(_varName.c_str(), nullptr);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Environment::_values_impl(
    std::vec_tstring_t *a_values
)
{
    std::vec_tstring_t args;

    LPTCH lpvEnv = ::GetEnvironmentStrings();
    xTEST_PTR(lpvEnv);

    // variable strings are separated by nullptr byte,
    // and the block is terminated by a nullptr byte
    for (
        LPTSTR var = static_cast<LPTSTR>(lpvEnv);
        *var != xT('\0');
        var += ::lstrlen(var) + 1)
    {
        args.push_back(var);
    }

    BOOL blRv = ::FreeEnvironmentStrings(lpvEnv);
    xTEST_DIFF(blRv, FALSE);

    // out
    a_values->swap(args);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Environment::_expandStrings_impl(
    std::ctstring_t &a_varName
)
{
    std::tstring_t sRv;

    sRv.resize(xPATH_MAX);

    DWORD length = ::ExpandEnvironmentStrings(a_varName.c_str(), &sRv.at(0),
        static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(length, 0UL);

    sRv.resize(length);

    if (sRv.size() < length) {
        length = ::ExpandEnvironmentStrings(a_varName.c_str(), &sRv.at(0),
            static_cast<DWORD>( sRv.size() ));
        xTEST_DIFF(length, 0UL);
    }

    sRv.resize(length - 1);   // remove '\0'

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
