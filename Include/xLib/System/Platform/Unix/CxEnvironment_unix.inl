/**
 * \file  CxEnvironment.inl
 * \brief system environment variables
 */


extern char **environ;  // from <env.h>

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
    const char *pcszRv = ::getenv(a_varName.c_str());
    xTEST_NA(pcszRv);
    xCHECK_RET(pcszRv == xPTR_NULL, false);

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

    const char *pcszRv = ::getenv(a_varName.c_str());
    xTEST_PTR(pcszRv);

    sRv.assign(pcszRv);

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
    int_t iRv = ::setenv(a_varName.c_str(), a_value.c_str(), true);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxEnvironment::_deleteVar_impl(
    std::ctstring_t &a_varName
)
{
#if   xENV_LINUX
    int_t iRv = ::unsetenv(a_varName.c_str());
    xTEST_DIFF(iRv, - 1);
#elif xENV_BSD
    (void_t)::unsetenv(a_varName.c_str());
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxEnvironment::_values_impl(
    std::vec_tstring_t *a_values
)
{
    std::vec_tstring_t args;

    xTEST_PTR(environ);

    for (size_t i = 0; 0 != environ[i]; ++ i) {
        args.push_back(environ[i]);
    }

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

    std::ctstring_t sep = xT("%");

    sRv = a_var;

    for ( ; ; ) {
        // find from left two first chars '%'
        std::csize_t startSepPos = sRv.find(sep);
        xCHECK_DO(startSepPos == std::tstring_t::npos, break);

        std::csize_t stopSepPos  = sRv.find(sep, startSepPos + sep.size());
        xCHECK_DO(stopSepPos == std::tstring_t::npos, break);

        // copy %var% to temp string
        std::tstring_t rawEnvVar; // %var%

        rawEnvVar = CxString::cut(sRv, startSepPos, stopSepPos + sep.size());
        xTEST_EQ(rawEnvVar.empty(), false);

        std::tstring_t envVar;    // var

        envVar = CxString::trimChars(rawEnvVar, sep);

        // expand var to temp string
        std::tstring_t expandedEnvVar;

        expandedEnvVar = var(envVar);

        // replace envVar(%var%) by expandedEnvVar
        sRv.replace(startSepPos, rawEnvVar.size(), expandedEnvVar);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
