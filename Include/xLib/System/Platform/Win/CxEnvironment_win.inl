/**
 * \file  CxEnvironment.inl
 * \brief system environment variables
 */


xNAMESPACE_BEGIN2(xlib, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxEnvironment::_isExists_impl(
    std::ctstring_t &a_varName
)
{
    std::tstring_t sRv;
    sRv.resize(xPATH_MAX);

    DWORD length = ::GetEnvironmentVariable(a_varName.c_str(), &sRv.at(0),
        static_cast<DWORD>( sRv.size() ));
    xTEST_NA(length);

    xCHECK_RET(length == 0UL && CxLastError::get() == ERROR_ENVVAR_NOT_FOUND, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxEnvironment::_var_impl(
    std::ctstring_t &a_varName
)
{
    std::tstring_t sRv;

    sRv.resize(xPATH_MAX);

    DWORD length = ::GetEnvironmentVariable(a_varName.c_str(), &sRv.at(0),
        static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(length, 0UL);

    sRv.resize(length);

    if (sRv.size() < length) {
        length = ::GetEnvironmentVariable(a_varName.c_str(), &sRv.at(0),
            static_cast<DWORD>( sRv.size() ));
        xTEST_DIFF(length, 0UL);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxEnvironment::_setVar_impl(
    std::ctstring_t &a_varName,
    std::ctstring_t &a_value
)
{
    BOOL blRv = ::SetEnvironmentVariable(a_varName.c_str(), a_value.c_str());
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxEnvironment::_deleteVar_impl(
    std::ctstring_t &a_varName
)
{
    BOOL blRv = ::SetEnvironmentVariable(a_varName.c_str(), xPTR_NULL);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxEnvironment::_values_impl(
    std::vec_tstring_t *a_values
)
{
    std::vec_tstring_t args;

    LPTCH lpvEnv = ::GetEnvironmentStrings();
    xTEST_PTR(lpvEnv);

    // variable strings are separated by xPTR_NULL byte,
    // and the block is terminated by a xPTR_NULL byte
    for (
        LPTSTR var = static_cast<LPTSTR>( lpvEnv );
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
inline std::tstring_t
CxEnvironment::_expandStrings_impl(
    std::ctstring_t &a_var
)
{
    std::tstring_t sRv;

    sRv.resize(xPATH_MAX);

    DWORD length = ::ExpandEnvironmentStrings(a_var.c_str(), &sRv.at(0),
        static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(length, 0UL);

    sRv.resize(length);

    if (sRv.size() < length) {
        length = ::ExpandEnvironmentStrings(a_var.c_str(), &sRv.at(0),
            static_cast<DWORD>( sRv.size() ));
        xTEST_DIFF(length, 0UL);
    }

    sRv.resize(length - 1);   // remove '\0'

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
