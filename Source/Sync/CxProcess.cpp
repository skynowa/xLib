/**
 * \file  CxProcess.cpp
 * \brief process
 */


#include <xLib/Sync/CxProcess.h>

#if defined(xOS_ENV_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#endif


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
CxProcess::TxId
CxProcess::ulGetCurrId() {
    /*DEBUG*/// n/a

    TxId ulRes;

#if defined(xOS_ENV_WIN)
    ulRes = ::GetCurrentProcessId();
    /*DEBUG*/// n/a
#elif defined(xOS_ENV_UNIX)
    ulRes = getpid();
    /*DEBUG*/// n/a
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
/*static*/
CxProcess::TxId
CxProcess::ulGetCurrParentId() {
    /*DEBUG*/// n/a

    TxId ulRes;

#if defined(xOS_ENV_WIN)
    const TxId culInvalidId = (ULONG)- 1;

    ULONG_PTR pbi[6] = {0};
    ULONG     ulSize = 0UL;
    LONG (WINAPI *NtQueryInformationProcess)(HANDLE ProcessHandle, ULONG ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);

    HMODULE hModule = ::GetModuleHandle(xT("ntdll.dll"));
    /*DEBUG*/xASSERT_RET(NULL != hModule, culInvalidId);

    *(FARPROC *)&NtQueryInformationProcess = ::GetProcAddress(hModule, "NtQueryInformationProcess");
    /*DEBUG*/xASSERT_RET(NULL != NtQueryInformationProcess, culInvalidId);

    BOOL bRes = ( NtQueryInformationProcess(CxHandleT<hvNull>::hGetCurrentProcess(), 0, &pbi, sizeof(pbi), &ulSize) >= 0 && ulSize == sizeof(pbi) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, culInvalidId);

    ulRes = pbi[5];
#elif defined(xOS_ENV_UNIX)
    ulRes = getppid();
    /*DEBUG*/// n/a
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
//http://www-theorie.physik.unizh.ch/~dpotter/howto/daemonize
/*static*/
BOOL
CxProcess::bExec(
    const std::string_t &csFilePath,
    const char_t        *pcszCmdLine, ...
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pcszCmdLine,        FALSE);

    std::string_t sCmdLine;

    va_list palArgs;
    xVA_START(palArgs, pcszCmdLine);
    sCmdLine = CxString::sFormatV(pcszCmdLine, palArgs);
    xVA_END(palArgs);

#if defined(xOS_ENV_WIN)
    BOOL bRes = FALSE;

    STARTUPINFO         siInfo = {0};   siInfo.cb = sizeof(siInfo);
    PROCESS_INFORMATION piInfo = {0};

    bRes = ::CreateProcess(NULL, &sCmdLine.at(0), NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &siInfo, &piInfo);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = ::CloseHandle(piInfo.hThread);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = ::CloseHandle(piInfo.hProcess);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    #if xDEPRECIATE
        INT iRes = execlp(csFilePath.c_str(), sCmdLine.c_str(), static_cast<LPCTSTR>( NULL ));
        /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
    #else
        pid_t pid = fork();
        /*DEBUG*/xASSERT_RET(- 1 == pid, FALSE);

        if (0 == pid) {
            //TODO: csFilePath is executable

            INT iRes = execlp(csFilePath.c_str(), csFilePath.c_str(), sCmdLine.c_str(), static_cast<const char_t *>( NULL ));
            /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);

            _exit(EXIT_SUCCESS);  /* Note that we do not use exit() */

            return TRUE;
        } else {
            return TRUE;
        }
    #endif
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxProcess::bExit(
    const TxId culPid,
    const UINT cuiExitCode
)
{
    /*DEBUG*/// uiExitCode - n/a

#if defined(xOS_ENV_WIN)
    (VOID)::ExitProcess(cuiExitCode);
#elif defined(xOS_ENV_UNIX)
    (VOID)exit(static_cast<INT>( cuiExitCode ));
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxProcess::bTerminate(
    const TxId culPid
)
{
    /*DEBUG*/// uiExitCode - n/a

#if defined(xOS_ENV_WIN)
    CxHandle hProcess;

    hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, culPid);
    /*DEBUG*/xASSERT_RET(NULL != hProcess, FALSE);

    BOOL bRes = ::TerminateProcess(hProcess, 0/*uiExitCode*/);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    INT iRes = kill(culPid, SIGKILL);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxProcess::CxProcess() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxProcess::~CxProcess() {

}
//---------------------------------------------------------------------------
