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

    sRes.resize(MAX_PATH);

    ulStored = ::GetEnvironmentVariable(csVarName.c_str(), &sRes.at(0), sRes.size());
    /*DEBUG*/// n/a
    ULONG ulLastError = ::GetLastError();
    xCHECK_RET(0 == ulStored && ERROR_ENVVAR_NOT_FOUND == ulLastError, FALSE); 
#elif defined(xOS_LINUX)
    char *pszRes = NULL;

    pszRes = std::getenv(csVarName.c_str());
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

    sRes.resize(MAX_PATH);

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

    pszRes = std::getenv(csVarName.c_str());
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
    INT iRes = unsetenv(csVarName.c_str());
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
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
//DONE: sExpandStrings
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

    sRes.resize(MAX_PATH);

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
//DONE: sGetCommandLine (Retrieves the command-line string for the current process)
/*static*/
tString
CxEnvironment::sGetCommandLine() {
    /*DEBUG*/// n/a

    tString sRes;

#if defined(xOS_WIN)
    LPTSTR pszRes = ::GetCommandLine();
    /*DEBUG*/xASSERT_RET(NULL != pszRes, tString());

    sRes.assign(pszRes);

    sRes.assign( CxString::sTrimSpace(sRes) );
#elif defined(xOS_LINUX)
    CxStdioFile  sfFile;
    const size_t cuiBuffSize             = 1024 * 2;    //TODO: must be enough space for store data
    TCHAR        szBuff[cuiBuffSize + 1] = {0};
    std::size_t  uiBytes                 = 0;
    size_t       uiOffset                = 0;

    BOOL bRes = sfFile.bOpen(xT("/proc/self/cmdline"), CxStdioFile::omRead, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, tString());

    for (;;) {
        uiBytes = sfFile.uiRead(szBuff + uiOffset, cuiBuffSize - uiOffset);
        xCHECK_DO(0 >= uiBytes, break);

        char *pszCurrPtr = szBuff;

        for (size_t i = 0; i < uiBytes; ++ i) {
            xCHECK_DO(xT('\0') != szBuff[i], continue);

            sRes.append(pszCurrPtr);
            sRes.append(CxConst::xSPACE);   //xTRACEV(xT("%s"), sRes.c_str());

            if (i + 1 < uiBytes) {
                pszCurrPtr = szBuff + i + 1;
            } else {
                pszCurrPtr = NULL;
            }
        }

        if (NULL != pszCurrPtr)  {
            uiBytes  = 0;
            uiOffset = szBuff - pszCurrPtr + cuiBuffSize + 1;

            while (pszCurrPtr != szBuff + cuiBuffSize) {
                szBuff[uiBytes ++] = *pszCurrPtr ++;
            }

            szBuff[uiBytes] = xT('\0');
        }
    }

    sRes.assign( CxString::sTrimSpace(sRes) );
    /*DEBUG*/xASSERT_RET(false == sRes.empty(), tString());
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

    std::vector<tString> vsArgs;

#if defined(xOS_WIN)
	////extern int        __argc;   //count of cmd line args
    ////extern char    ** __argv;   //pointer to table of cmd line args
    extern wchar_t ** __wargv;  //pointer to table of wide cmd line args

    #if defined(xUNICODE)
        TCHAR **targv = __wargv;
    #else
        TCHAR **targv = __argv;
    #endif  /*_UNICODE*/

    /*DEBUG*/xASSERT_RET(NULL != targv, FALSE);

    for (TCHAR **pszVar = targv; *pszVar; ++ pszVar) {
        vsArgs.push_back(*pszVar);
    }
#elif defined(xOS_LINUX)
    BOOL bRes = FALSE;

    bRes = CxString::bSplit(sGetCommandLine(), CxConst::xSPACE, &vsArgs);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#endif

    //out
    std::swap(*pvsArgs, vsArgs);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxEnvironment (constructor)
CxEnvironment::CxEnvironment() {

}
//---------------------------------------------------------------------------
//DONE: ~CxEnvironment (dectructor)
/*virtual*/
CxEnvironment::~CxEnvironment() {

}
//---------------------------------------------------------------------------
