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
CxEnvironment::bIsExists(const tString &csVarName) {
    /*DEBUG*/xASSERT_RET(false == csVarName.empty(), FALSE);

#if defined(xOS_WIN)
    tString sRes;
    ULONG   ulStored = 0;

    sRes.resize(MAX_PATH);

    //not including the terminating null character
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
CxEnvironment::sGetVar(const tString &csVarName) {
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
CxEnvironment::bSetVar(const tString &csVarName, const tString &csValue) {
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
//TODO: - bDeleteVar (delete var)
/*static*/
BOOL
CxEnvironment::bDeleteVar(const tString &csVarName) {
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
CxEnvironment::bGetValues(std::vector<tString> *pvecsValues) {
    /*DEBUG*/xASSERT_RET(NULL != pvecsValues, FALSE);

    BOOL bRes = FALSE;

    (*pvecsValues).clear();

#if defined(xOS_WIN)
    //TODO: xOS_WIN
    LPTSTR pszVar = NULL;
    LPTCH  lpvEnv = NULL;

    lpvEnv = ::GetEnvironmentStrings();
    /*DEBUG*/xASSERT_RET(NULL != lpvEnv, FALSE);

    //Variable strings are separated by NULL byte, and the block is terminated by a NULL byte.
    pszVar = static_cast<LPTSTR>( lpvEnv );

    while (*pszVar)    {
        //printf("%s\n", lpszVariable);
        (*pvecsValues).push_back(pszVar);
        pszVar += ::lstrlen(pszVar) + 1;
    }

    bRes = ::FreeEnvironmentStrings(lpvEnv);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    xUNUSED(bRes);
/*
    #define _POSIX_SOURCE 1
    #include <env.h>
    #include <stdio.h>

    extern char **environ;

    int count_env() {
        for (int num = 0; environ[num] != NULL; ++ num);

        return num;
    }
*/
/*
//  for (int i = 0; _environ[i]; i++) {
//      sRes += tString(_environ[i]);
//      sRes += "\n";
//  }
*/

    extern char **environ;  //from <env.h>
    xASSERT_RET(NULL != environ, FALSE);

    for (char **pszVar = environ; *pszVar; ++ pszVar) {
        (*pvecsValues).push_back(*pszVar);
    }
#endif

    return TRUE;
}
//--------------------------------------------------------------------------
//DONE: sExpandStrings
/*static*/
tString
CxEnvironment::sExpandStrings(const tString &csVar) {
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

    sRes.resize(ulStored - 1);    //cut '\0', including the terminating null character
#elif defined(xOS_LINUX)
    const tString csSep = xT("%");

    sRes.assign(csVar);

    for ( ;; ) {
        /*TRACE*///CxDebugger::bTrace(xT("sRes (in): %s"), sRes.c_str());
        /*TRACE*///CxDebugger::bTrace(xT("csSep:     %s"), csSep.c_str());

        std::size_t uiStartSepPos = 0;
        std::size_t uiStopSepPos  = 0;

        //--------------------------------------------------
        //find from left two first chars '%'
        uiStartSepPos = sRes.find(csSep);
        xCHECK_DO(tString::npos == uiStartSepPos, break);

        uiStopSepPos  = sRes.find(csSep, uiStartSepPos + csSep.size());
        xCHECK_DO(tString::npos == uiStopSepPos, break);

        /*DEBUG*///CxDebugger::bTrace(xT("StartPos: %u, StopPos: %u"), uiStartSepPos, uiStopSepPos);

        //--------------------------------------------------
        //copy %var% to temp string
        tString sRawEnvVar; // %var%

        sRawEnvVar = CxString::sCut(sRes, uiStartSepPos, uiStopSepPos + csSep.size());
        xASSERT(false == sRawEnvVar.empty());
        /*TRACE*///CxDebugger::bTrace(xT("sRawEnvVar: %s"), sRawEnvVar.c_str());

        tString sEnvVar;    // var

        sEnvVar = CxString::sTrimChars(sRawEnvVar, csSep);
        /*TRACE*///CxDebugger::bTrace(xT("sEnvVar: %s"), sEnvVar.c_str());

        //--------------------------------------------------
        //expand var to temp string
        tString sExpandedEnvVar;

        sExpandedEnvVar = sGetVar(sEnvVar);
        /*TRACE*///CxDebugger::bTrace(xT("sExpandedEnvVar: %s"), sExpandedEnvVar.c_str());

        //--------------------------------------------------
        //replace sEnvVar(%var%) by sExpandedEnvVar
        sRes.replace(uiStartSepPos, sRawEnvVar.size(), sExpandedEnvVar);
        /*TRACE*///CxDebugger::bTrace(xT("sRes (replaced): %s"), sRes.c_str());
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

    BOOL bRes = sfFile.bOpen(xT("/proc/self/cmdline"), CxStdioFile::CxOpenMode::omRead);
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
//DONE: bGetCommandLineArgs ()
/*static*/
BOOL
CxEnvironment::bGetCommandLineArgs(std::vector<tString> *pvecsArgs) {
    /*DEBUG*/xASSERT_RET(NULL != pvecsArgs, FALSE);

    (*pvecsArgs).clear();

#if defined(xOS_WIN)
//    extern int        __argc;   /* count of cmd line args */
//    extern char    ** __argv;   /* pointer to table of cmd line args */
    extern wchar_t ** __wargv;  /* pointer to table of wide cmd line args */

#if defined(UNICODE) || defined(_UNICODE)
    TCHAR **targv = __wargv;
#else
    TCHAR **targv = __argv;
#endif  /*_UNICODE*/

    /*DEBUG*/xASSERT_RET(NULL != targv, FALSE);

    for (TCHAR **pszVar = targv; *pszVar; ++ pszVar) {
        pvecsArgs->push_back(*pszVar);
    }
#elif defined(xOS_LINUX)
    BOOL bRes = FALSE;

    bRes = CxString::bSplit(sGetCommandLine(), CxConst::xSPACE, pvecsArgs) ;
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*
http://www.codeguru.com/Cpp/W-P/win32/article.php/c1427
*/

/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxEnvironment (constructor)
/*virtual*/
CxEnvironment::CxEnvironment() {

}
//---------------------------------------------------------------------------
//DONE: ~CxEnvironment (dectructor)
CxEnvironment::~CxEnvironment() {

}
//---------------------------------------------------------------------------
