/**
 * \file  CxEnvironment.cpp
 * \brief system environment variables
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>


#if !xOS_ENV_WIN
    extern char **environ;  // from <env.h>
#endif

xNAMESPACE2_BEGIN(xlib, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxEnvironment::isExists(
    std::ctstring_t &a_varName
)
{
    xTEST_NA(a_varName);

    xCHECK_RET(a_varName.empty(), false);

#if   xOS_ENV_WIN
    std::tstring_t sRv;
    sRv.resize(xPATH_MAX);

    DWORD length = ::GetEnvironmentVariable(a_varName.c_str(), &sRv.at(0),
        static_cast<DWORD>( sRv.size() ));
    xTEST_NA(length);

    xCHECK_RET(length == 0UL && CxLastError::get() == ERROR_ENVVAR_NOT_FOUND, false);
#elif xOS_ENV_UNIX
    const char *pcszRv = ::getenv(a_varName.c_str());
    xTEST_NA(pcszRv);

    xCHECK_RET(pcszRv == xPTR_NULL, false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxEnvironment::isVarValid(
    std::ctstring_t &a_varName
)
{
    xTEST_NA(a_varName);

    xCHECK_RET(a_varName.empty(),                                     false);
    xCHECK_RET(a_varName.find(CxConst::equal()) != std::string::npos, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxEnvironment::isValueValid(
    std::ctstring_t &a_varValue
)
{
    xTEST_NA(a_varValue);

    xCHECK_RET(xENV_MAX < a_varValue.size(), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxEnvironment::var(
    std::ctstring_t &a_varName
)
{
    xTEST_NA(a_varName);

    xCHECK_RET(!isExists(a_varName), std::tstring_t());

    std::tstring_t sRv;

#if   xOS_ENV_WIN
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
#elif xOS_ENV_UNIX
    const char *pcszRv = ::getenv(a_varName.c_str());
    xTEST_PTR(pcszRv);

    sRv.assign(pcszRv);
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxEnvironment::setVar(
    std::ctstring_t &a_varName,
    std::ctstring_t &a_value
)
{
    xTEST_EQ(isVarValid(a_varName), true);
    xTEST_EQ(isVarValid(a_value), true);

#if   xOS_ENV_WIN
    BOOL blRv = ::SetEnvironmentVariable(a_varName.c_str(), a_value.c_str());
    xTEST_DIFF(blRv, FALSE);
#elif xOS_ENV_UNIX
    int_t iRv = ::setenv(a_varName.c_str(), a_value.c_str(), true);
    xTEST_DIFF(iRv, - 1);
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxEnvironment::deleteVar(
    std::ctstring_t &a_varName
)
{
    xTEST_NA(a_varName);

    xCHECK_DO(!isExists(a_varName), return);

#if   xOS_ENV_WIN
    BOOL blRv = ::SetEnvironmentVariable(a_varName.c_str(), xPTR_NULL);
    xTEST_DIFF(blRv, FALSE);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        int_t iRv = ::unsetenv(a_varName.c_str());
        xTEST_DIFF(iRv, - 1);
    #elif xOS_FREEBSD
        (void_t)::unsetenv(a_varName.c_str());
    #endif
#elif xOS_ENV_APPLE
    int_t iRv = ::unsetenv(a_varName.c_str());
    xTEST_DIFF(iRv, - 1);
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxEnvironment::values(
    std::vec_tstring_t *a_values
)
{
    xTEST_PTR(a_values);

    std::vec_tstring_t args;

#if   xOS_ENV_WIN
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
#elif xOS_ENV_UNIX
    xTEST_PTR(environ);

    for (size_t i = 0; 0 != environ[i]; ++ i) {
        args.push_back(environ[i]);
    }
#endif

    // out
    a_values->swap(args);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxEnvironment::expandStrings(
    std::ctstring_t &a_var
)
{
    xTEST_EQ(a_var.empty(), false);

    std::tstring_t sRv;

#if   xOS_ENV_WIN
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
#elif xOS_ENV_UNIX
    std::ctstring_t sep = xT("%");

    sRv = a_var;

    xFOREVER {
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
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, system)
