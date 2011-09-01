/**
 * \file  CxEnvironment.cpp
 * \brief system environment variables
 */


#include <xLib/Filesystem/CxEnvironment.h>

#include <xLib/Filesystem/CxFile.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
BOOL
CxEnvironment::bIsExists(
    const std::tstring &csVarName
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(true == csVarName.empty(), FALSE);

#if defined(xOS_WIN)
    std::tstring sRes;
    ULONG   ulStored = 0;

    sRes.resize(xPATH_MAX);

    ulStored = ::GetEnvironmentVariable(csVarName.c_str(), &sRes.at(0), sRes.size());
    /*DEBUG*/// n/a
    xCHECK_RET(0 == ulStored && ERROR_ENVVAR_NOT_FOUND == CxLastError::ulGet(), FALSE);
#elif defined(xOS_LINUX)
    char *pszRes = NULL;

    pszRes = getenv(csVarName.c_str());
    /*DEBUG*/// n/a
    xCHECK_RET(NULL == pszRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxEnvironment::sGetVar(
    const std::tstring &csVarName
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(FALSE == bIsExists(csVarName), std::tstring());

    std::tstring sRes;

#if defined(xOS_WIN)
    ULONG ulStored = 0;

    sRes.resize(xPATH_MAX);

    ulStored = ::GetEnvironmentVariable(csVarName.c_str(), &sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(0 != ulStored, std::tstring());

    sRes.resize(ulStored);

    if (sRes.size() < ulStored) {
        ulStored = ::GetEnvironmentVariable(csVarName.c_str(), &sRes.at(0), sRes.size());
        /*DEBUG*/xASSERT_RET(0 != ulStored, std::tstring());
    }
#elif defined(xOS_LINUX)
    char *pszRes = NULL;

    pszRes = getenv(csVarName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != pszRes, std::tstring());

    sRes.assign(pszRes);
#endif

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
BOOL
CxEnvironment::bSetVar(
    const std::tstring &csVarName,
    const std::tstring &csValue
)
{
    /*DEBUG*/xASSERT_RET(false == csVarName.empty(), FALSE);
    /*DEBUG*/// csValue - n/a

#if defined(xOS_WIN)
    BOOL bRes = ::SetEnvironmentVariable(csVarName.c_str(), csValue.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    INT iRes = setenv(csVarName.c_str(), csValue.c_str(), TRUE);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxEnvironment::bDeleteVar(
    const std::tstring &csVarName
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(FALSE == bIsExists(csVarName), TRUE);

#if defined(xOS_WIN)
    BOOL bRes = ::SetEnvironmentVariable(csVarName.c_str(), NULL);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    #if defined(xOS_FREEBSD)
        unsetenv(csVarName.c_str());
        /*DEBUG*/// n/a
    #else
        INT iRes = unsetenv(csVarName.c_str());
        /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
    #endif
#endif

    return TRUE;
}
//--------------------------------------------------------------------------
/*static*/
BOOL
CxEnvironment::bGetValues(
    std::vector<std::tstring> *pvsValues
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvsValues, FALSE);

    std::vector<std::tstring> vsArgs;

#if defined(xOS_WIN)
    BOOL   bRes   = FALSE;
    LPTSTR pszVar = NULL;
    LPTCH  lpvEnv = NULL;

    lpvEnv = ::GetEnvironmentStrings();
    /*DEBUG*/xASSERT_RET(NULL != lpvEnv, FALSE);

    //Variable strings are separated by NULL byte, and the block is terminated by a NULL byte
    pszVar = static_cast<LPTSTR>( lpvEnv );

    while (*pszVar)    {
        vsArgs.push_back(pszVar);
        pszVar += ::lstrlen(pszVar) + 1;
    }

    bRes = ::FreeEnvironmentStrings(lpvEnv);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    extern char **environ;  //from <env.h>
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
std::tstring
CxEnvironment::sExpandStrings(
    const std::tstring &csVar
)
{
    /*DEBUG*/xASSERT_RET(false == csVar.empty(), std::tstring());

    std::tstring sRes;

#if defined(xOS_WIN)
    ULONG ulStored = FALSE;

    sRes.resize(xPATH_MAX);

    ulStored = ::ExpandEnvironmentStrings(csVar.c_str(), &sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(0 != ulStored, std::tstring());

    sRes.resize(ulStored);

    if (sRes.size() < ulStored) {
        ulStored = ::ExpandEnvironmentStrings(csVar.c_str(), &sRes.at(0), sRes.size());
        /*DEBUG*/xASSERT_RET(0 != ulStored, std::tstring());
    }

    sRes.resize(ulStored - sizeof('\0'));
#elif defined(xOS_LINUX)
    const std::tstring csSep = xT("%");

    sRes.assign(csVar);

    for ( ; ; ) {
        //--------------------------------------------------
        //find from left two first chars '%'
        const size_t cuiStartSepPos = sRes.find(csSep);
        xCHECK_DO(std::tstring::npos == cuiStartSepPos, break);

        const size_t cuiStopSepPos  = sRes.find(csSep, cuiStartSepPos + csSep.size());
        xCHECK_DO(std::tstring::npos == cuiStopSepPos, break);

        //--------------------------------------------------
        //copy %var% to temp string
        std::tstring sRawEnvVar; // %var%

        sRawEnvVar = CxString::sCut(sRes, cuiStartSepPos, cuiStopSepPos + csSep.size());
        xASSERT(false == sRawEnvVar.empty());

        std::tstring sEnvVar;    // var

        sEnvVar = CxString::sTrimChars(sRawEnvVar, csSep);

        //--------------------------------------------------
        //expand var to temp string
        std::tstring sExpandedEnvVar;

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
*	command line args
*
*****************************************************************************/

//--------------------------------------------------------------------------
/*static*/ std::vector<std::tstring> CxEnvironment::_m_vsCommandLineArgs;
//--------------------------------------------------------------------------
/*static*/
std::tstring
CxEnvironment::sGetCommandLine() {
    /*DEBUG*/// n/a

    std::tstring sRes;

#if defined(xOS_WIN)
    LPCTSTR pcszRes = ::GetCommandLine();
    /*DEBUG*/xASSERT_RET(NULL != pcszRes, std::tstring());

    sRes.assign( CxString::sTrimSpace(pcszRes) );
#elif defined(xOS_LINUX)
    sRes.assign( CxString::sJoin(_m_vsCommandLineArgs, CxConst::xSPACE) );
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxEnvironment::bGetCommandLineArgs(
    std::vector<std::tstring> *pvsArgs
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvsArgs, FALSE);

    xCHECK_DO(true == _m_vsCommandLineArgs.empty(), CxDebugger::bTrace(xT("xLib: warning (command line is empty)")));

    (*pvsArgs).assign(_m_vsCommandLineArgs.begin(), _m_vsCommandLineArgs.end());

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxEnvironment::bSetCommandLineArgs(
    const INT  ciArgsCount,
    TCHAR     *paszArgs[]
)
{
    /*DEBUG*/// n/a (because we'll have a recursion)

    std::vector<std::tstring> vsArgs;

    for (INT i = 0; i < ciArgsCount; ++ i) {
        vsArgs.push_back(paszArgs[i]);
    }

    //out
    std::swap(_m_vsCommandLineArgs, vsArgs);

    xCHECK_DO(true == _m_vsCommandLineArgs.empty(), CxDebugger::bTrace(xT("xLib: warning (command line is empty)")));

    return TRUE;
}
//---------------------------------------------------------------------------


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
