/****************************************************************************
* Class name:  CxEnvironment
* Description: system environment variables
* File name:   CxEnvironment.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.04.2010 17:43:45
*
*****************************************************************************/


#include <xLib/Filesystem/CxEnvironment.h>

#include <xLib/Filesystem/CxStdioFile.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bIsExists (check for existence)
/*static*/
BOOL
CxEnvironment::bIsExists(
    const tString &csVarName
)
{
    /*DEBUG*/xASSERT_RET(false == csVarName.empty(), FALSE);

#if defined(xOS_WIN)
    tString sRes;
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
//DONE: sGetVar (get value by name)
/*static*/
tString
CxEnvironment::sGetVar(
    const tString &csVarName
)
{
    /*DEBUG*/xASSERT_RET(false == csVarName.empty(), tString());

    xCHECK_RET(FALSE == bIsExists(csVarName), tString());

    tString sRes;

#if defined(xOS_WIN)
    ULONG ulStored = 0;

    sRes.resize(xPATH_MAX);

    //not including the terminating null character
    ulStored = ::GetEnvironmentVariable(csVarName.c_str(), &sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(0 != ulStored, tString());

    sRes.resize(ulStored);

    if (sRes.size() < ulStored) {
        ulStored = ::GetEnvironmentVariable(csVarName.c_str(), &sRes.at(0), sRes.size());
        /*DEBUG*/xASSERT_RET(0 != ulStored, tString());
    }
#elif defined(xOS_LINUX)
    char *pszRes = NULL;

    pszRes = getenv(csVarName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != pszRes, tString());

    sRes.assign(pszRes);
#endif

    return sRes;
}
//--------------------------------------------------------------------------
//DONE: bSetVar (set or change value by name)
/*static*/
BOOL
CxEnvironment::bSetVar(
    const tString &csVarName,
    const tString &csValue
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
//DONE: bDeleteVar (delete var)
/*static*/
BOOL
CxEnvironment::bDeleteVar(
    const tString &csVarName
)
{
    /*DEBUG*/xASSERT_RET(false == csVarName.empty(), FALSE);

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
//DONE: bGetValues (get all values)
/*static*/
BOOL
CxEnvironment::bGetValues(
    std::vector<tString> *pvsValues
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvsValues, FALSE);

    std::vector<tString> vsArgs;

#if defined(xOS_WIN)
    BOOL   bRes   = FALSE;
    LPTSTR pszVar = NULL;
    LPTCH  lpvEnv = NULL;

    lpvEnv = ::GetEnvironmentStrings();
    /*DEBUG*/xASSERT_RET(NULL != lpvEnv, FALSE);

    //Variable strings are separated by NULL byte, and the block is terminated by a NULL byte.
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
//DONE: sExpandStrings (expands strings by separator "%")
/*static*/
tString
CxEnvironment::sExpandStrings(
    const tString &csVar
)
{
    /*DEBUG*/xASSERT_RET(false == csVar.empty(), tString());

    tString sRes;

#if defined(xOS_WIN)
    ULONG ulStored = FALSE;

    sRes.resize(xPATH_MAX);

    ulStored = ::ExpandEnvironmentStrings(csVar.c_str(), &sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(0 != ulStored, tString());

    sRes.resize(ulStored);

    if (sRes.size() < ulStored) {
        ulStored = ::ExpandEnvironmentStrings(csVar.c_str(), &sRes.at(0), sRes.size());
        /*DEBUG*/xASSERT_RET(0 != ulStored, tString());
    }

    sRes.resize(ulStored - sizeof('\0'));
#elif defined(xOS_LINUX)
    const tString csSep = xT("%");

    sRes.assign(csVar);

    for ( ; ; ) {
        //xTRACEV(xT("sRes (in): %s"), sRes.c_str());
        //xTRACEV(xT("csSep:     %s"), csSep.c_str());

        //--------------------------------------------------
        //find from left two first chars '%'
        const size_t cuiStartSepPos = sRes.find(csSep);
        xCHECK_DO(tString::npos == cuiStartSepPos, break);

        const size_t cuiStopSepPos  = sRes.find(csSep, cuiStartSepPos + csSep.size());
        xCHECK_DO(tString::npos == cuiStopSepPos, break);

        //xTRACEV(xT("StartPos: %u, StopPos: %u"), uiStartSepPos, uiStopSepPos);

        //--------------------------------------------------
        //copy %var% to temp string
        tString sRawEnvVar; // %var%

        sRawEnvVar = CxString::sCut(sRes, cuiStartSepPos, cuiStopSepPos + csSep.size());
        xASSERT(false == sRawEnvVar.empty());
        //xTRACEV(xT("sRawEnvVar: %s"), sRawEnvVar.c_str());

        tString sEnvVar;    // var

        sEnvVar = CxString::sTrimChars(sRawEnvVar, csSep);
        //xTRACEV(xT("sEnvVar: %s"), sEnvVar.c_str());

        //--------------------------------------------------
        //expand var to temp string
        tString sExpandedEnvVar;

        sExpandedEnvVar = sGetVar(sEnvVar);
        //xTRACEV(xT("sExpandedEnvVar: %s"), sExpandedEnvVar.c_str());

        //--------------------------------------------------
        //replace sEnvVar(%var%) by sExpandedEnvVar
        sRes.replace(cuiStartSepPos, sRawEnvVar.size(), sExpandedEnvVar);
        /*TRACE*///xTRACEV(xT("sRes (replaced): %s"), sRes.c_str());
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
/*static*/ std::vector<tString> CxEnvironment::_m_vsCommandLineArgs;
//--------------------------------------------------------------------------
//DONE: sGetCommandLine (get command-line string for the current process)
/*static*/
tString
CxEnvironment::sGetCommandLine() {
    /*DEBUG*/// n/a

    tString sRes;

#if defined(xOS_WIN)
    LPTCSTR pcszRes = ::GetCommandLine();
    /*DEBUG*/xASSERT_RET(NULL != pcszRes, tString());

    sRes.assign( CxString::sTrimSpace(pcszRes) );
#elif defined(xOS_LINUX)
    sRes.assign( CxString::sJoin(_m_vsCommandLineArgs, CxConst::xSPACE) );
#endif

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: bGetCommandLineArgs (get commandline arguments)
/*static*/
BOOL
CxEnvironment::bGetCommandLineArgs(
    std::vector<tString> *pvsArgs
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvsArgs, FALSE);

    xCHECK_DO(true == _m_vsCommandLineArgs.empty(), CxDebugger::bTrace(xT("xLib: warning (command line is empty)")));

    (*pvsArgs).assign(_m_vsCommandLineArgs.begin(), _m_vsCommandLineArgs.end());

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSetCommandLineArgs (set commandline arguments)
/*static*/
BOOL
CxEnvironment::bSetCommandLineArgs(
    const INT  ciArgsCount,
    TCHAR     *paszArgs[]
)
{
    /*DEBUG*/// n/a (because we'll have a recursion)
    /*DEBUG*/// n/a (because we'll have a recursion)

    const TCHAR  **pcaszCommandLineArgs     = const_cast<const TCHAR **>(paszArgs);
    const size_t   m_uiCommandLineArgsCount = ciArgsCount;

    std::vector<tString> vsArgs;

    for (const TCHAR **pszVar = pcaszCommandLineArgs; (NULL != pcaszCommandLineArgs) && (NULL != *pszVar); ++ pszVar) {
        vsArgs.push_back(*pszVar);
    }
    /*DEBUG*/xASSERT_RET(vsArgs.size() == m_uiCommandLineArgsCount, FALSE);

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
//DONE: CxEnvironment
CxEnvironment::CxEnvironment() {

}
//---------------------------------------------------------------------------
//DONE: ~CxEnvironment
/*virtual*/
CxEnvironment::~CxEnvironment() {

}
//---------------------------------------------------------------------------
