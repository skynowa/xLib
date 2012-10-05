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
    const std::tstring_t &csVarName
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(true == csVarName.empty(), false);

#if   xOS_ENV_WIN
    std::tstring_t sRv;
    DWORD          ulStored = 0UL;

    sRv.resize(xPATH_MAX);

    ulStored = ::GetEnvironmentVariable(csVarName.c_str(), &sRv.at(0), sRv.size());
    /*DEBUG*/// n/a
    xCHECK_RET(0UL == ulStored && ERROR_ENVVAR_NOT_FOUND == CxLastError::ulGet(), false);
#elif xOS_ENV_UNIX
    const char *pcszRes = ::getenv(csVarName.c_str());
    /*DEBUG*/// n/a
    xCHECK_RET(NULL == pcszRes, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxEnvironment::bIsVarValid(
    const std::tstring_t &csVarName
)
{
    xDEBUG_VAR_NA(csVarName);

    xCHECK_RET(true              == csVarName.empty(),               false);
    xCHECK_RET(std::string::npos != csVarName.find(CxConst::xEQUAL), false);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxEnvironment::bIsValueValid(
    const std::tstring_t &csVarValue
)
{
    xDEBUG_VAR_NA(csVarValue);

    xCHECK_RET(xENV_MAX < csVarValue.size(), false);

    return true;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxEnvironment::sGetVar(
    const std::tstring_t &csVarName
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(false == bIsExists(csVarName), std::tstring_t());

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    DWORD ulStored = 0UL;

    sRv.resize(xPATH_MAX);

    ulStored = ::GetEnvironmentVariable(csVarName.c_str(), &sRv.at(0), sRv.size());
    /*DEBUG*/xTEST_DIFF(0UL, ulStored);

    sRv.resize(ulStored);

    if (sRv.size() < ulStored) {
        ulStored = ::GetEnvironmentVariable(csVarName.c_str(), &sRv.at(0), sRv.size());
        /*DEBUG*/xTEST_DIFF(0UL, ulStored);
    }
#elif xOS_ENV_UNIX
    const char *pcszRes = ::getenv(csVarName.c_str());
    /*DEBUG*/xTEST_PTR(pcszRes);

    sRv.assign(pcszRes);
#endif

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
void
CxEnvironment::vSetVar(
    const std::tstring_t &csVarName,
    const std::tstring_t &csValue
)
{
    /*DEBUG*/xTEST_EQ(true, bIsVarValid(csVarName));
    /*DEBUG*/xTEST_EQ(true, bIsVarValid(csValue));

#if   xOS_ENV_WIN
    BOOL blRes = ::SetEnvironmentVariable(csVarName.c_str(), csValue.c_str());
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::setenv(csVarName.c_str(), csValue.c_str(), true);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
#endif
}
//---------------------------------------------------------------------------
/* static */
void
CxEnvironment::vDeleteVar(
    const std::tstring_t &csVarName
)
{
    /*DEBUG*/// n/a
    xCHECK_DO(false == bIsExists(csVarName), return);

#if   xOS_ENV_WIN
    BOOL blRes = ::SetEnvironmentVariable(csVarName.c_str(), NULL);
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        int iRv = ::unsetenv(csVarName.c_str());
        /*DEBUG*/xTEST_DIFF(- 1, iRv);
    #elif xOS_FREEBSD
        (void)::unsetenv(csVarName.c_str());
    #endif
#endif
}
//--------------------------------------------------------------------------
/* static */
void
CxEnvironment::vGetValues(
    std::vec_tstring_t *pvsValues
)
{
    /*DEBUG*/xTEST_PTR(pvsValues);

    std::vec_tstring_t vsArgs;

#if   xOS_ENV_WIN
    LPTSTR pszVar = NULL;
    LPTCH  lpvEnv = NULL;

    lpvEnv = ::GetEnvironmentStrings();
    /*DEBUG*/xTEST_PTR(lpvEnv);

    //Variable strings are separated by NULL byte, and the block is terminated by a NULL byte
    pszVar = static_cast<LPTSTR>( lpvEnv );

    while (NULL != *pszVar)    {
        vsArgs.push_back(pszVar);
        pszVar += ::lstrlen(pszVar) + 1;
    }

    BOOL blRes = ::FreeEnvironmentStrings(lpvEnv);
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    /*DEBUG*/xTEST_PTR(environ);

    for (size_t i = 0; NULL != environ[i]; ++ i) {
        vsArgs.push_back(environ[i]);
    }
#endif

    //out
    std::swap(*pvsValues, vsArgs);
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxEnvironment::sExpandStrings(
    const std::tstring_t &csVar
)
{
    /*DEBUG*/xTEST_EQ(false, csVar.empty());

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    DWORD ulStored = 0UL;

    sRv.resize(xPATH_MAX);

    ulStored = ::ExpandEnvironmentStrings(csVar.c_str(), &sRv.at(0), sRv.size());
    /*DEBUG*/xTEST_DIFF(0UL, ulStored);

    sRv.resize(ulStored);

    if (sRv.size() < ulStored) {
        ulStored = ::ExpandEnvironmentStrings(csVar.c_str(), &sRv.at(0), sRv.size());
        /*DEBUG*/xTEST_DIFF(0UL, ulStored);
    }

    sRv.resize(ulStored - sizeof('\0'));
#elif xOS_ENV_UNIX
    const std::tstring_t csSep = xT("%");

    sRv = csVar;

    for ( ; ; ) {
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

        sExpandedEnvVar = sGetVar(sEnvVar);

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
