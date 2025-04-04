/**
 * \file  Env.inl
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
Env::_isExists_impl() const
{
    std::tstring_t sRv;
    sRv.resize(_envMax());

    DWORD length = ::GetEnvironmentVariable(_nsName.c_str(), &sRv.at(0),
        static_cast<DWORD>( sRv.size() ));
    xTEST_NA(length);

    xCHECK_RET(length == 0UL && NativeError::get() == ERROR_ENVVAR_NOT_FOUND, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Env::_value_impl() const
{
    std::tstring_t sRv;

    sRv.resize(_envMax());

    DWORD length = ::GetEnvironmentVariable(_nsName.c_str(), &sRv.at(0),
        static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(length, 0UL);

    sRv.resize(length);

    if (sRv.size() < length) {
        length = ::GetEnvironmentVariable(_nsName.c_str(), &sRv.at(0),
            static_cast<DWORD>( sRv.size() ));
        xTEST_DIFF(length, 0UL);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Env::_setValue_impl(
    std::ctstring_t &a_value
) const
{
    BOOL blRv = ::SetEnvironmentVariable(_nsName.c_str(), a_value.c_str());
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
void_t
Env::_remove_impl() const
{
    BOOL blRv = ::SetEnvironmentVariable(_nsName.c_str(), nullptr);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
std::vec_tstring_t
Envs::_vars_impl() const
{
    std::vec_tstring_t args;

    LPTCH lpvEnv = ::GetEnvironmentStrings();
    xTEST_PTR(lpvEnv);

    // variable strings are separated by nullptr byte,
    // and the block is terminated by a nullptr byte
    for (
        auto var = static_cast<LPTSTR>(lpvEnv);
        *var != xT('\0');
        var += ::lstrlen(var) + 1)
    {
        args.push_back(var);
    }

    BOOL blRv = ::FreeEnvironmentStrings(lpvEnv);
    xTEST_DIFF(blRv, FALSE);

    return std::move(args);
}
//-------------------------------------------------------------------------------------------------

} // namespace
