/****************************************************************************
* Class name:  CxProcess
* Description: process
* File name:   CxProcess.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     19.01.2011 22:42:07
*
*****************************************************************************/


#include <xLib/Sync/CxProcess.h>

#if defined(xOS_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#elif defined(xOS_LINUX)

#endif


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: ulGetCurrId (process ID of the calling process)
/*static*/
ULONG
CxProcess::ulGetCurrId() {
    /*DEBUG*/// n/a

    ULONG ulRes = (ULONG)- 1;

#if defined(xOS_WIN)
    ulRes = ::GetCurrentProcessId();
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    ulRes = static_cast<ULONG>( getpid() );
    /*DEBUG*/// n/a
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
//DONE: ulGetCurrParentId (process ID of the parent of the calling process)
/*static*/
ULONG
CxProcess::ulGetCurrParentId() {
    /*DEBUG*/// n/a

    ULONG ulRes = 0;

#if defined(xOS_WIN)
    const ULONG culInvalidId = (ULONG)- 1;

    ULONG_PTR pbi[6] = {0};
    ULONG     ulSize = 0;
    LONG (WINAPI *NtQueryInformationProcess)(HANDLE ProcessHandle, ULONG ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);

    *(FARPROC *)&NtQueryInformationProcess = ::GetProcAddress(::LoadLibraryA("NTDLL.DLL"), "NtQueryInformationProcess");
    /*DEBUG*/xASSERT_RET(NULL != NtQueryInformationProcess, culInvalidId);

    BOOL bRes = ( NtQueryInformationProcess(::GetCurrentProcess(), 0, &pbi, sizeof(pbi), &ulSize) >= 0 && ulSize == sizeof(pbi) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, culInvalidId);

    ulRes = pbi[5];
#elif defined(xOS_LINUX)
    ulRes = static_cast<ULONG>( getppid() );
    /*DEBUG*/// n/a
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
//TODO: bExec (execute a file)
//http://www-theorie.physik.unizh.ch/~dpotter/howto/daemonize
/*static*/
BOOL
CxProcess::bExec(
    const tString &csFilePath,
    LPCTSTR        pcszCmdLine, ...
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pcszCmdLine,        FALSE);

    tString sCmdLine;

    va_list palArgs;
    xVA_START(palArgs, pcszCmdLine);
    sCmdLine = CxString::sFormatV(pcszCmdLine, palArgs);
    xVA_END(palArgs);

#if defined(xOS_WIN)
    BOOL bRes = FALSE;

    STARTUPINFO         siInfo = {0};   siInfo.cb = sizeof(siInfo);
    PROCESS_INFORMATION piInfo = {0};

    bRes = ::CreateProcess(NULL, &sCmdLine.at(0), NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &siInfo, &piInfo);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = ::CloseHandle(piInfo.hThread);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = ::CloseHandle(piInfo.hProcess);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    #if xDEPRECIATE
        INT iRes = execlp(csFilePath.c_str(), sCmdLine.c_str(), static_cast<LPCTSTR>( NULL ));
        /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
    #else
        pid_t pid = fork();
        /*DEBUG*/xASSERT_RET(- 1 == pid, FALSE);

        if (0 == pid) {
            //TODO: csFilePath is executable

            INT iRes = execlp(csFilePath.c_str(), csFilePath.c_str(), sCmdLine.c_str(), static_cast<LPCTSTR>( NULL ));
            /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);

            _exit(0);  /* Note that we do not use exit() */

            return TRUE;
        } else {
            return TRUE;
        }
    #endif
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bExit (Ends the calling process and all its threads)
/*static*/
BOOL
CxProcess::bExit(
    const ULONG culPid,
    const UINT  cuiExitCode
)
{
    /*DEBUG*/// uiExitCode - n/a

#if defined(xOS_WIN)
    ::ExitProcess(cuiExitCode);
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    exit(static_cast<INT>( cuiExitCode ));
    /*DEBUG*/// n/a
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bTerminate (kills the calling process and all of its threads)
/*static*/
BOOL
CxProcess::bTerminate(
    const ULONG culPid
)
{
    /*DEBUG*/// uiExitCode - n/a

#if defined(xOS_WIN)
    CxHandle hProcess;

    hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, culPid);
    /*DEBUG*/xASSERT_RET(NULL != hProcess, FALSE);

    BOOL bRes = ::TerminateProcess(hProcess, 0/*uiExitCode*/);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    INT iRes = kill(static_cast<pid_t>( culPid ), SIGKILL);
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
//DONE: CxProcess
CxProcess::CxProcess() {

}
//---------------------------------------------------------------------------
//DONE: ~CxProcess
/*virtual*/
CxProcess::~CxProcess() {

}
//---------------------------------------------------------------------------
