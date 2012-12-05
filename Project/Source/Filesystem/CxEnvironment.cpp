/**
 * \file  CxEnvironment.cpp
 * \brief system environment variables
 */


#include <xLib/Filesystem/CxEnvironment.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxPath.h>


#if xOS_ENV_UNIX
    extern char **environ;  //from <env.h>
#endif

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
bool
CxEnvironment::bIsExists(
    const std::tstring_t &a_csVarName
)
{
    // n/a
    xCHECK_RET(true == a_csVarName.empty(), false);

#if   xOS_ENV_WIN
    std::tstring_t sRv;
    DWORD          ulStored = 0UL;

    sRv.resize(xPATH_MAX);

    ulStored = ::GetEnvironmentVariable(a_csVarName.c_str(), &sRv.at(0), sRv.size());
    // n/a
    xCHECK_RET(0UL == ulStored && ERROR_ENVVAR_NOT_FOUND == CxLastError::ulGet(), false);
#elif xOS_ENV_UNIX
    const char *pcszRes = ::getenv(a_csVarName.c_str());
    // n/a
    xCHECK_RET(NULL == pcszRes, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxEnvironment::bIsVarValid(
    const std::tstring_t &a_csVarName
)
{
    xTEST_NA(csVarName);

    xCHECK_RET(true              == a_csVarName.empty(),               false);
    xCHECK_RET(std::string::npos != a_csVarName.find(CxConst::xEQUAL), false);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxEnvironment::bIsValueValid(
    const std::tstring_t &a_csVarValue
)
{
    xTEST_NA(csVarValue);

    xCHECK_RET(xENV_MAX < a_csVarValue.size(), false);

    return true;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxEnvironment::sVar(
    const std::tstring_t &a_csVarName
)
{
    // n/a
    xCHECK_RET(false == bIsExists(a_csVarName), std::tstring_t());

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    DWORD ulStored = 0UL;

    sRv.resize(xPATH_MAX);

    ulStored = ::GetEnvironmentVariable(a_csVarName.c_str(), &sRv.at(0), sRv.size());
    xTEST_DIFF(0UL, ulStored);

    sRv.resize(ulStored);

    if (sRv.size() < ulStored) {
        ulStored = ::GetEnvironmentVariable(a_csVarName.c_str(), &sRv.at(0), sRv.size());
        xTEST_DIFF(0UL, ulStored);
    }
#elif xOS_ENV_UNIX
    const char *pcszRes = ::getenv(a_csVarName.c_str());
    xTEST_PTR(pcszRes);

    sRv.assign(pcszRes);
#endif

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
void
CxEnvironment::vSetVar(
    const std::tstring_t &a_csVarName,
    const std::tstring_t &a_csValue
)
{
    xTEST_EQ(true, bIsVarValid(a_csVarName));
    xTEST_EQ(true, bIsVarValid(a_csValue));

#if   xOS_ENV_WIN
    BOOL blRes = ::SetEnvironmentVariable(a_csVarName.c_str(), a_csValue.c_str());
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::setenv(a_csVarName.c_str(), a_csValue.c_str(), true);
    xTEST_DIFF(- 1, iRv);
#endif
}
//---------------------------------------------------------------------------
/* static */
void
CxEnvironment::vDeleteVar(
    const std::tstring_t &a_csVarName
)
{
    // n/a
    xCHECK_DO(false == bIsExists(a_csVarName), return);

#if   xOS_ENV_WIN
    BOOL blRes = ::SetEnvironmentVariable(a_csVarName.c_str(), NULL);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        int iRv = ::unsetenv(a_csVarName.c_str());
        xTEST_DIFF(- 1, iRv);
    #elif xOS_FREEBSD
        (void)::unsetenv(a_csVarName.c_str());
    #endif
#endif
}
//--------------------------------------------------------------------------
/* static */
void
CxEnvironment::vValues(
    std::vec_tstring_t *a_pvsValues
)
{
    xTEST_PTR(a_pvsValues);

    std::vec_tstring_t vsArgs;

#if   xOS_ENV_WIN
    LPTCH lpvEnv = ::GetEnvironmentStrings();
    xTEST_PTR(lpvEnv);

    // variable strings are separated by NULL byte, and the block is terminated by a NULL byte
    for (
        LPTSTR pszVar = static_cast<LPTSTR>( lpvEnv );
        xT('\0') != *pszVar;
        pszVar += ::lstrlen(pszVar) + 1)
    {
        vsArgs.push_back(pszVar);
    }

    BOOL blRes = ::FreeEnvironmentStrings(lpvEnv);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
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
CxEnvironment::sExpandStrings(
    const std::tstring_t &a_csVar
)
{
    xTEST_EQ(false, a_csVar.empty());

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    DWORD ulStored = 0UL;

    sRv.resize(xPATH_MAX);

    ulStored = ::ExpandEnvironmentStrings(a_csVar.c_str(), &sRv.at(0), sRv.size());
    xTEST_DIFF(0UL, ulStored);

    sRv.resize(ulStored);

    if (sRv.size() < ulStored) {
        ulStored = ::ExpandEnvironmentStrings(a_csVar.c_str(), &sRv.at(0), sRv.size());
        xTEST_DIFF(0UL, ulStored);
    }

    sRv.resize(ulStored - sizeof('\0'));
#elif xOS_ENV_UNIX
    const std::tstring_t csSep = xT("%");

    sRv = a_csVar;

    xFOREVER {
        //--------------------------------------------------
        //find from left two first chars '%'
        const size_t cuiStartSepPos = sRv.find(csSep);
        xCHECK_DO(std::tstring_t::npos == cuiStartSepPos, break);

        const size_t cuiStopSepPos  = sRv.find(csSep, cuiStartSepPos + csSep.size());
        xCHECK_DO(std::tstring_t::npos == cuiStopSepPos, break);

        //--------------------------------------------------
        //copy %var% to temp string
        std::tstring_t sRawEnvVar; // %var%

        sRawEnvVar = CxString::sCut(sRv, cuiStartSepPos, cuiStopSepPos + csSep.size());
        xTEST_EQ(false, sRawEnvVar.empty());

        std::tstring_t sEnvVar;    // var

        sEnvVar = CxString::sTrimChars(sRawEnvVar, csSep);

        //--------------------------------------------------
        //expand var to temp string
        std::tstring_t sExpandedEnvVar;

        sExpandedEnvVar = sVar(sEnvVar);

        //--------------------------------------------------
        //replace sEnvVar(%var%) by sExpandedEnvVar
        sRv.replace(cuiStartSepPos, sRawEnvVar.size(), sExpandedEnvVar);
    }
#endif

    return sRv;
}
//--------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxEnvironment::CxEnvironment() {

}
//---------------------------------------------------------------------------
/* virtual */
CxEnvironment::~CxEnvironment() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
