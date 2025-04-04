/**
 * \file  Env.inl
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
Env::_isExists_impl() const
{
    const char *pcszRv = ::getenv(xT2A(_nsName).c_str());
    xTEST_NA(pcszRv);
    xCHECK_RET(pcszRv == nullptr, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Env::_value_impl() const
{
    std::tstring_t sRv;

    const char *pcszRv = ::getenv(xT2A(_nsName).c_str());
    xTEST_PTR(pcszRv);

    sRv.assign(xA2T(pcszRv));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Env::_setValue_impl(
    std::ctstring_t &a_value
) const
{
    cint_t isReplaced {1};

    int_t iRv = ::setenv(xT2A(_nsName).c_str(), xT2A(a_value).c_str(), isReplaced);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
void_t
Env::_remove_impl() const
{
#if   xENV_LINUX
    int_t iRv = ::unsetenv(xT2A(_nsName).c_str());
    xTEST_DIFF(iRv, - 1);
#elif xENV_BSD
    (void_t)::unsetenv(xT2A(_nsName).c_str());
#elif xENV_APPLE
    int_t iRv = ::unsetenv(xT2A(_nsName).c_str());
    xTEST_DIFF(iRv, - 1);
#endif
}
//-------------------------------------------------------------------------------------------------
std::vec_tstring_t
Envs::_vars_impl() const
{
    const auto env = ::environ;

    xTEST_PTR(env);

    std::vec_tstring_t args;

    for (size_t i = 0; env[i] != 0; ++ i) {
        std::ctstring_t &it_str = xA2T(env[i]);
        // Check namespace
        xCHECK_DO(!it_str.starts_with(_ns), continue);

        args.emplace_back(it_str);
    }

    return std::move(args);
}
//-------------------------------------------------------------------------------------------------

} // namespace
