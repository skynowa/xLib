/**
 * \file  CxEnvironment.cpp
 * \brief system environment variables
 */


#include <xLib/Filesystem/CxEnvironment.h>

#include <xLib/Filesystem/CxPath.h>


extern char **environ;  //from <env.h>

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
BOOL
CxEnvironment::bIsExists(
    const std::string_t &csVarName
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(true == csVarName.empty(), FALSE);

#if xOS_ENV_WIN
    std::string_t sRes;
    ULONG        ulStored = 0UL;

    sRes.resize(xPATH_MAX);

    ulStored = ::GetEnvironmentVariable(csVarName.c_str(), &sRes.at(0), sRes.size());
    /*DEBUG*/// n/a
    xCHECK_RET(0 == ulStored && ERROR_ENVVAR_NOT_FOUND == CxLastError::ulGet(), FALSE);
#elif xOS_ENV_UNIX
    const char *pcszRes = ::getenv(csVarName.c_str());
    /*DEBUG*/// n/a
    xCHECK_RET(NULL == pcszRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxEnvironment::sGetVar(
    const std::string_t &csVarName
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(FALSE == bIsExists(csVarName), std::string_t());

    std::string_t sRes;

#if xOS_ENV_WIN
    ULONG ulStored = 0UL;

    sRes.resize(xPATH_MAX);

    ulStored = ::GetEnvironmentVariable(csVarName.c_str(), &sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(0 != ulStored, std::string_t());

    sRes.resize(ulStored);

    if (sRes.size() < ulStored) {
        ulStored = ::GetEnvironmentVariable(csVarName.c_str(), &sRes.at(0), sRes.size());
        /*DEBUG*/xASSERT_RET(0UL != ulStored, std::string_t());
    }
#elif xOS_ENV_UNIX
    const char *pcszRes = ::getenv(csVarName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != pcszRes, std::string_t());

    sRes.assign(pcszRes);
#endif

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
BOOL
CxEnvironment::bSetVar(
    const std::string_t &csVarName,
    const std::string_t &csValue
)
{
    /*DEBUG*/xASSERT_RET(false == csVarName.empty(), FALSE);
    /*DEBUG*/// csValue - n/a

#if xOS_ENV_WIN
    BOOL bRes = ::SetEnvironmentVariable(csVarName.c_str(), csValue.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif xOS_ENV_UNIX
    int iRes = ::setenv(csVarName.c_str(), csValue.c_str(), TRUE);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxEnvironment::bDeleteVar(
    const std::string_t &csVarName
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(FALSE == bIsExists(csVarName), TRUE);

#if xOS_ENV_WIN
    BOOL bRes = ::SetEnvironmentVariable(csVarName.c_str(), NULL);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif xOS_ENV_UNIX
    #if xOS_FREEBSD
        (void)::unsetenv(csVarName.c_str());
    #else
        int iRes = ::unsetenv(csVarName.c_str());
        /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
    #endif
#endif

    return TRUE;
}
//--------------------------------------------------------------------------
/*static*/
BOOL
CxEnvironment::bGetValues(
    std::vector<std::string_t> *pvsValues
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvsValues, FALSE);

    std::vector<std::string_t> vsArgs;

#if xOS_ENV_WIN
    LPTSTR pszVar = NULL;
    LPTCH  lpvEnv = NULL;

    lpvEnv = ::GetEnvironmentStrings();
    /*DEBUG*/xASSERT_RET(NULL != lpvEnv, FALSE);

    //Variable strings are separated by NULL byte, and the block is terminated by a NULL byte
    pszVar = static_cast<LPTSTR>( lpvEnv );

    while (NULL != *pszVar)    {
        vsArgs.push_back(pszVar);
        pszVar += ::lstrlen(pszVar) + 1;
    }

    BOOL bRes = ::FreeEnvironmentStrings(lpvEnv);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif xOS_ENV_UNIX
    /*DEBUG*/xASSERT_RET(NULL != environ, FALSE);

    for (size_t i = 0; NULL != environ[i]; ++ i) {
        vsArgs.push_back(environ[i]);
    }
#endif

    //out
    std::swap(*pvsValues, vsArgs);

    return TRUE;
}
//--------------------------------------------------------------------------
/*static*/
std::string_t
CxEnvironment::sExpandStrings(
    const std::string_t &csVar
)
{
    /*DEBUG*/xASSERT_RET(false == csVar.empty(), std::string_t());

    std::string_t sRes;

#if xOS_ENV_WIN
    ULONG ulStored = 0UL;

    sRes.resize(xPATH_MAX);

    ulStored = ::ExpandEnvironmentStrings(csVar.c_str(), &sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(0UL != ulStored, std::string_t());

    sRes.resize(ulStored);

    if (sRes.size() < ulStored) {
        ulStored = ::ExpandEnvironmentStrings(csVar.c_str(), &sRes.at(0), sRes.size());
        /*DEBUG*/xASSERT_RET(0UL != ulStored, std::string_t());
    }

    sRes.resize(ulStored - sizeof('\0'));
#elif xOS_ENV_UNIX
    const std::string_t csSep = xT("%");

    sRes.assign(csVar);

    for ( ; ; ) {
        //--------------------------------------------------
        //find from left two first chars '%'
        const size_t cuiStartSepPos = sRes.find(csSep);
        xCHECK_DO(std::string_t::npos == cuiStartSepPos, break);

        const size_t cuiStopSepPos  = sRes.find(csSep, cuiStartSepPos + csSep.size());
        xCHECK_DO(std::string_t::npos == cuiStopSepPos, break);

        //--------------------------------------------------
        //copy %var% to temp string
        std::string_t sRawEnvVar; // %var%

        sRawEnvVar = CxString::sCut(sRes, cuiStartSepPos, cuiStopSepPos + csSep.size());
        xASSERT(false == sRawEnvVar.empty());

        std::string_t sEnvVar;    // var

        sEnvVar = CxString::sTrimChars(sRawEnvVar, csSep);

        //--------------------------------------------------
        //expand var to temp string
        std::string_t sExpandedEnvVar;

        sExpandedEnvVar = sGetVar(sEnvVar);

        //--------------------------------------------------
        //replace sEnvVar(%var%) by sExpandedEnvVar
        sRes.replace(cuiStartSepPos, sRawEnvVar.size(), sExpandedEnvVar);
    }
#endif

    return sRes;
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
/*virtual*/
CxEnvironment::~CxEnvironment() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
