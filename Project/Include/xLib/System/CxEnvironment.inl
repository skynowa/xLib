/**
 * \file  CxEnvironment.cpp
 * \brief system environment variables
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Filesystem/CxPath.h>


#if !xOS_ENV_WIN
    extern char **environ;  // from <env.h>
#endif

xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE_HO bool_t
CxEnvironment::isExists(
    std::ctstring_t &a_varName
)
{
    xTEST_NA(a_varName);

    xCHECK_RET(a_varName.empty(), false);

#if xOS_ENV_WIN
    std::tstring_t sRv;

    sRv.resize(xPATH_MAX);

    DWORD length = ::GetEnvironmentVariable(a_varName.c_str(), &sRv.at(0),
        static_cast<DWORD>( sRv.size() ));
    xTEST_NA(length);

    xCHECK_RET(0UL == length && ERROR_ENVVAR_NOT_FOUND == CxLastError::get(), false);
#else
    const char *pcszRv = ::getenv(a_varName.c_str());
    xTEST_NA(pcszRv);

    xCHECK_RET(NULL == pcszRv, false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE_HO bool_t
CxEnvironment::isVarValid(
    std::ctstring_t &a_varName
)
{
    xTEST_NA(a_varName);

    xCHECK_RET(a_varName.empty(),                                     false);
    xCHECK_RET(std::string::npos != a_varName.find(CxConst::equal()), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE_HO bool_t
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
xINLINE_HO std::tstring_t
CxEnvironment::var(
    std::ctstring_t &a_varName
)
{
    xTEST_NA(a_varName);

    xCHECK_RET(!isExists(a_varName), std::tstring_t());

    std::tstring_t sRv;

#if xOS_ENV_WIN
    sRv.resize(xPATH_MAX);

    DWORD length = ::GetEnvironmentVariable(a_varName.c_str(), &sRv.at(0),
        static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(0UL, length);

    sRv.resize(length);

    if (sRv.size() < length) {
        length = ::GetEnvironmentVariable(a_varName.c_str(), &sRv.at(0),
            static_cast<DWORD>( sRv.size() ));
        xTEST_DIFF(0UL, length);
    }
#else
    const char *pcszRv = ::getenv(a_varName.c_str());
    xTEST_PTR(pcszRv);

    sRv.assign(pcszRv);
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxEnvironment::setVar(
    std::ctstring_t &a_varName,
    std::ctstring_t &a_value
)
{
    xTEST_EQ(true, isVarValid(a_varName));
    xTEST_EQ(true, isVarValid(a_value));

#if xOS_ENV_WIN
    BOOL blRv = ::SetEnvironmentVariable(a_varName.c_str(), a_value.c_str());
    xTEST_DIFF(FALSE, blRv);
#else
    int_t iRv = ::setenv(a_varName.c_str(), a_value.c_str(), true);
    xTEST_DIFF(- 1, iRv);
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxEnvironment::deleteVar(
    std::ctstring_t &a_varName
)
{
    xTEST_NA(a_varName);

    xCHECK_DO(!isExists(a_varName), return);

#if     xOS_ENV_WIN
    BOOL blRv = ::SetEnvironmentVariable(a_varName.c_str(), NULL);
    xTEST_DIFF(FALSE, blRv);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        int_t iRv = ::unsetenv(a_varName.c_str());
        xTEST_DIFF(- 1, iRv);
    #elif xOS_FREEBSD
        (void_t)::unsetenv(a_varName.c_str());
    #endif
#elif xOS_ENV_MAC
    int_t iRv = ::unsetenv(a_varName.c_str());
    xTEST_DIFF(- 1, iRv);
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxEnvironment::values(
    std::vec_tstring_t *a_values
)
{
    xTEST_PTR(a_values);

    std::vec_tstring_t args;

#if xOS_ENV_WIN
    LPTCH lpvEnv = ::GetEnvironmentStrings();
    xTEST_PTR(lpvEnv);

    // variable strings are separated by NULL byte,
    // and the block is terminated by a NULL byte
    for (
        LPTSTR var = static_cast<LPTSTR>( lpvEnv );
        xT('\0') != *var;
        var += ::lstrlen(var) + 1)
    {
        args.push_back(var);
    }

    BOOL blRv = ::FreeEnvironmentStrings(lpvEnv);
    xTEST_DIFF(FALSE, blRv);
#else
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
xINLINE_HO std::tstring_t
CxEnvironment::expandStrings(
    std::ctstring_t &a_var
)
{
    xTEST_EQ(false, a_var.empty());

    std::tstring_t sRv;

#if xOS_ENV_WIN
    sRv.resize(xPATH_MAX);

    DWORD length = ::ExpandEnvironmentStrings(a_var.c_str(), &sRv.at(0),
        static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(0UL, length);

    sRv.resize(length);

    if (sRv.size() < length) {
        length = ::ExpandEnvironmentStrings(a_var.c_str(), &sRv.at(0),
            static_cast<DWORD>( sRv.size() ));
        xTEST_DIFF(0UL, length);
    }

    sRv.resize(length - 1);   // remove '\0'
#else
    std::ctstring_t sep = xT("%");

    sRv = a_var;

    xFOREVER {
        //--------------------------------------------------
        // find from left two first chars '%'
        std::csize_t startSepPos = sRv.find(sep);
        xCHECK_DO(std::tstring_t::npos == startSepPos, break);

        std::csize_t stopSepPos  = sRv.find(sep, startSepPos + sep.size());
        xCHECK_DO(std::tstring_t::npos == stopSepPos, break);

        //--------------------------------------------------
        // copy %var% to temp string
        std::tstring_t rawEnvVar; // %var%

        rawEnvVar = CxString::cut(sRv, startSepPos, stopSepPos + sep.size());
        xTEST_EQ(false, rawEnvVar.empty());

        std::tstring_t envVar;    // var

        envVar = CxString::trimChars(rawEnvVar, sep);

        //--------------------------------------------------
        // expand var to temp string
        std::tstring_t expandedEnvVar;

        expandedEnvVar = var(envVar);

        //--------------------------------------------------
        // replace envVar(%var%) by expandedEnvVar
        sRv.replace(startSepPos, rawEnvVar.size(), expandedEnvVar);
    }
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
