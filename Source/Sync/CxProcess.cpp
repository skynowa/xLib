/**
 * \file  CxProcess.cpp
 * \brief process
 */
 

#include <xLib/Sync/CxProcess.h>

#if xOS_ENV_WIN
    #include <xLib/Common/Win/CxHandleT.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//http://www-theorie.physik.unizh.ch/~dpotter/howto/daemonize
/*static*/
bool
CxProcess::bExec(
    const std::tstring_t &csFilePath,
    const tchar_t        *pcszCmdLine, ...
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != pcszCmdLine,        false);

    std::tstring_t sCmdLine;

    va_list palArgs;
    xVA_START(palArgs, pcszCmdLine);
    sCmdLine = CxString::sFormatV(pcszCmdLine, palArgs);
    xVA_END(palArgs);

#if xOS_ENV_WIN
    BOOL blRes = FALSE;

    STARTUPINFO         siInfo = {0};   siInfo.cb = sizeof(siInfo);
    PROCESS_INFORMATION piInfo = {0};

    blRes = ::CreateProcess(NULL, &sCmdLine.at(0), NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, NULL, &siInfo, &piInfo);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    blRes = ::CloseHandle(piInfo.hThread);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    blRes = ::CloseHandle(piInfo.hProcess);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    #if xDEPRECIATE
        int iRes = execlp(csFilePath.c_str(), sCmdLine.c_str(), static_cast<LPCTSTR>( NULL ));
        /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
    #else
        pid_t pid = ::fork();
        /*DEBUG*/xASSERT_RET(- 1 == pid, false);

        if (0 == pid) {
            //TODO: csFilePath is executable

            int iRes = ::execlp(csFilePath.c_str(), csFilePath.c_str(), sCmdLine.c_str(), static_cast<const tchar_t *>( NULL ));
            /*DEBUG*/xASSERT_RET(- 1 != iRes, false);

            ::_exit(EXIT_SUCCESS);  /* Note that we do not use exit() */

            return true;
        } else {
            return true;
        }
    #endif
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxProcess::bExit(
    const TxId culPid,
    const uint_t cuiExitCode
)
{
    /*DEBUG*/// uiExitCode - n/a

#if xOS_ENV_WIN
    (void)::ExitProcess(cuiExitCode);
#elif xOS_ENV_UNIX
    (void)::exit(static_cast<int>( cuiExitCode ));
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxProcess::bTerminate(
    const TxId culPid
)
{
    /*DEBUG*/// uiExitCode - n/a

#if xOS_ENV_WIN
    CxHandle hProcess;

    hProcess = ::OpenProcess(PROCESS_TERMINATE, false, culPid);
    /*DEBUG*/xASSERT_RET(NULL != hProcess, false);

    BOOL blRes = ::TerminateProcess(hProcess, 0/*uiExitCode*/);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    int iRes = ::kill(culPid, SIGKILL);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    return true;
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

xNAMESPACE_END(NxLib)
