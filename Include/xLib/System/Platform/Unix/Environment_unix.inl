/**
 * \file  Environment.inl
 * \brief system environment variables
 */


extern char **environ;  // from <env.h>

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
    const char *pcszRv = ::getenv(xT2A(_varName).c_str());
    xTEST_NA(pcszRv);
    xCHECK_RET(pcszRv == nullptr, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Environment::_var_impl() const
{
    std::tstring_t sRv;

    const char *pcszRv = ::getenv(xT2A(_varName).c_str());
    xTEST_PTR(pcszRv);

    sRv.assign(xA2T(pcszRv));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Environment::_setVar_impl(
    std::ctstring_t &a_value
) const
{
    int_t iRv = ::setenv(xT2A(_varName).c_str(), xT2A(a_value).c_str(), true);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
void_t
Environment::_removeVar_impl() const
{
#if   xENV_LINUX
    int_t iRv = ::unsetenv(xT2A(_varName).c_str());
    xTEST_DIFF(iRv, - 1);
#elif xENV_BSD
    (void_t)::unsetenv(xT2A(_varName).c_str());
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Environment::_vars_impl(
    std::vec_tstring_t *a_values
)
{
    std::vec_tstring_t args;

    xTEST_PTR(::environ);

    for (size_t i = 0; ::environ[i] != 0; ++ i) {
        args.push_back( xA2T(::environ[i]) );
    }

    // out
    a_values->swap(args);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Environment::_expandVars_impl(
    std::ctstring_t &a_strWithVars
)
{
    std::tstring_t sRv = a_strWithVars;

    std::ctstring_t sep = xT("%");

    for ( ; ; ) {
        // find from left two first chars '%'
        std::csize_t startSepPos = sRv.find(sep);
        xCHECK_DO(startSepPos == std::tstring_t::npos, break);

        std::csize_t stopSepPos = sRv.find(sep, startSepPos + sep.size());
        xCHECK_DO(stopSepPos == std::tstring_t::npos, break);

        // copy %var% to temp string
        std::tstring_t rawEnvVar = String::cut(sRv, startSepPos, stopSepPos + sep.size());
        xTEST_EQ(rawEnvVar.empty(), false);

        std::tstring_t envVar = String::trimChars(rawEnvVar, sep);

        // expand var to temp string
        std::ctstring_t &expandedEnvVar = Environment(envVar).var();

        // replace envVar(%var%) by expandedEnvVar
        sRv.replace(startSepPos, rawEnvVar.size(), expandedEnvVar);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
