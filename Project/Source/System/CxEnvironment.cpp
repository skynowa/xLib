/**
 * \file  CxEnvironment.cpp
 * \brief system environment variables
 */


#include <xLib/System/CxEnvironment.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>


#if !xOS_ENV_WIN
    extern char **environ;  // from <env.h>
#endif

xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
bool_t
CxEnvironment::isExists(
    std::ctstring_t &a_csVarName
)
{
    xTEST_NA(a_csVarName);

    xCHECK_RET(a_csVarName.empty(), false);

#if xOS_ENV_WIN
    std::tstring_t sRv;

    sRv.resize(xPATH_MAX);

    DWORD dwLength = ::GetEnvironmentVariable(a_csVarName.c_str(), &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_NA(dwLength);

    xCHECK_RET(0UL == dwLength && ERROR_ENVVAR_NOT_FOUND == CxLastError::get(), false);
#else
    const char *pcszRes = ::getenv(a_csVarName.c_str());
    xTEST_NA(pcszRes);

    xCHECK_RET(NULL == pcszRes, false);
#endif

    return true;
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxEnvironment::isVarValid(
    std::ctstring_t &a_csVarName
)
{
    xTEST_NA(a_csVarName);

    xCHECK_RET(true              == a_csVarName.empty(),               false);
    xCHECK_RET(std::string::npos != a_csVarName.find(CxConst::xEQUAL), false);

    return true;
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxEnvironment::isValueValid(
    std::ctstring_t &a_csVarValue
)
{
    xTEST_NA(a_csVarValue);

    xCHECK_RET(xENV_MAX < a_csVarValue.size(), false);

    return true;
}
//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxEnvironment::var(
    std::ctstring_t &a_csVarName
)
{
    xTEST_NA(a_csVarName);

    xCHECK_RET(!isExists(a_csVarName), std::tstring_t());

    std::tstring_t sRv;

#if xOS_ENV_WIN
    sRv.resize(xPATH_MAX);

    DWORD dwLength = ::GetEnvironmentVariable(a_csVarName.c_str(), &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(0UL, dwLength);

    sRv.resize(dwLength);

    if (sRv.size() < dwLength) {
        dwLength = ::GetEnvironmentVariable(a_csVarName.c_str(), &sRv.at(0), static_cast<DWORD>( sRv.size() ));
        xTEST_DIFF(0UL, dwLength);
    }
#else
    const char *pcszRes = ::getenv(a_csVarName.c_str());
    xTEST_PTR(pcszRes);

    sRv.assign(pcszRes);
#endif

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
void_t
CxEnvironment::setVar(
    std::ctstring_t &a_csVarName,
    std::ctstring_t &a_csValue
)
{
    xTEST_EQ(true, isVarValid(a_csVarName));
    xTEST_EQ(true, isVarValid(a_csValue));

#if xOS_ENV_WIN
    BOOL blRes = ::SetEnvironmentVariable(a_csVarName.c_str(), a_csValue.c_str());
    xTEST_DIFF(FALSE, blRes);
#else
    int_t iRv = ::setenv(a_csVarName.c_str(), a_csValue.c_str(), true);
    xTEST_DIFF(- 1, iRv);
#endif
}
//------------------------------------------------------------------------------
/* static */
void_t
CxEnvironment::deleteVar(
    std::ctstring_t &a_csVarName
)
{
    xTEST_NA(a_csVarName);

    xCHECK_DO(!isExists(a_csVarName), return);

#if     xOS_ENV_WIN
    BOOL blRes = ::SetEnvironmentVariable(a_csVarName.c_str(), NULL);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        int_t iRv = ::unsetenv(a_csVarName.c_str());
        xTEST_DIFF(- 1, iRv);
    #elif xOS_FREEBSD
        (void_t)::unsetenv(a_csVarName.c_str());
    #endif
#elif xOS_ENV_MAC
    int_t iRv = ::unsetenv(a_csVarName.c_str());
    xTEST_DIFF(- 1, iRv);
#endif
}
//--------------------------------------------------------------------------
/* static */
void_t
CxEnvironment::values(
    std::vec_tstring_t *a_pvsValues
)
{
    xTEST_PTR(a_pvsValues);

    std::vec_tstring_t vsArgs;

#if xOS_ENV_WIN
    LPTCH lpvEnv = ::GetEnvironmentStrings();
    xTEST_PTR(lpvEnv);

    // variable strings are separated by NULL byte,
    // and the block is terminated by a NULL byte
    for (
        LPTSTR pszVar = static_cast<LPTSTR>( lpvEnv );
        xT('\0') != *pszVar;
        pszVar += ::lstrlen(pszVar) + 1)
    {
        vsArgs.push_back(pszVar);
    }

    BOOL blRes = ::FreeEnvironmentStrings(lpvEnv);
    xTEST_DIFF(FALSE, blRes);
#else
    xTEST_PTR(environ);

    for (size_t i = 0; 0 != environ[i]; ++ i) {
        vsArgs.push_back(environ[i]);
    }
#endif

    // out
    std::swap(*a_pvsValues, vsArgs);
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxEnvironment::expandStrings(
    std::ctstring_t &a_csVar
)
{
    xTEST_EQ(false, a_csVar.empty());

    std::tstring_t sRv;

#if xOS_ENV_WIN
    sRv.resize(xPATH_MAX);

    DWORD dwLength = ::ExpandEnvironmentStrings(a_csVar.c_str(), &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(0UL, dwLength);

    sRv.resize(dwLength);

    if (sRv.size() < dwLength) {
        dwLength = ::ExpandEnvironmentStrings(a_csVar.c_str(), &sRv.at(0), static_cast<DWORD>( sRv.size() ));
        xTEST_DIFF(0UL, dwLength);
    }

    sRv.resize(dwLength - 1);   // remove '\0'
#else
    std::ctstring_t csSep = xT("%");

    sRv = a_csVar;

    xFOREVER {
        //--------------------------------------------------
        // find from left two first chars '%'
        std::csize_t cuiStartSepPos = sRv.find(csSep);
        xCHECK_DO(std::tstring_t::npos == cuiStartSepPos, break);

        std::csize_t cuiStopSepPos  = sRv.find(csSep, cuiStartSepPos + csSep.size());
        xCHECK_DO(std::tstring_t::npos == cuiStopSepPos, break);

        //--------------------------------------------------
        // copy %var% to temp string
        std::tstring_t sRawEnvVar; // %var%

        sRawEnvVar = CxString::cut(sRv, cuiStartSepPos, cuiStopSepPos + csSep.size());
        xTEST_EQ(false, sRawEnvVar.empty());

        std::tstring_t sEnvVar;    // var

        sEnvVar = CxString::trimChars(sRawEnvVar, csSep);

        //--------------------------------------------------
        // expand var to temp string
        std::tstring_t sExpandedEnvVar;

        sExpandedEnvVar = var(sEnvVar);

        //--------------------------------------------------
        // replace sEnvVar(%var%) by sExpandedEnvVar
        sRv.replace(cuiStartSepPos, sRawEnvVar.size(), sExpandedEnvVar);
    }
#endif

    return sRv;
}
//--------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxEnvironment::CxEnvironment() {

}
//------------------------------------------------------------------------------
/* virtual */
CxEnvironment::~CxEnvironment() {

}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
