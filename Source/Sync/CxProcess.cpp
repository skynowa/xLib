/**
 * \file  CxProcess.cpp
 * \brief process
 */


#include <xLib/Sync/CxProcess.h>

#if xOS_ENV_WIN
    #if !xCOMPILER_MINGW32
        #pragma comment(lib, "psapi.lib")
    #endif
#elif xOS_ENV_UNIX
    xNA;
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
    BOOL                blRes  = FALSE;
    STARTUPINFO         siInfo = {0};   siInfo.cb = sizeof(siInfo);
    PROCESS_INFORMATION piInfo = {0};

    blRes = ::CreateProcess(NULL, &sCmdLine.at(0), NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &siInfo, &piInfo);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    blRes = ::CloseHandle(piInfo.hThread);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    blRes = ::CloseHandle(piInfo.hProcess);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    pid_t pdId = ::fork();
    /*DEBUG*/xASSERT_RET(- 1 == pdId, false);

    if (0 == pdId) {
        //TODO: csFilePath is executable

        int iRes = ::execlp(csFilePath.c_str(), csFilePath.c_str(), sCmdLine.c_str(), static_cast<const tchar_t *>( NULL ));
        /*DEBUG*/xASSERT_RET(- 1 != iRes, false);

        (void)::_exit(EXIT_SUCCESS);  /* Note that we do not use exit() */

        return true;
    } else {
        return true;
    }
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxProcess::bExit(
    const TxId   culPid,
    const uint_t cuiExitCode
)
{
    /*DEBUG*/

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
    /*DEBUG*/

#if xOS_ENV_WIN
    CxHandle hProcess;

    hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, culPid);
    /*DEBUG*/xASSERT_RET(NULL != hProcess.hGet(), false);

    BOOL blRes = ::TerminateProcess(hProcess.hGet(), 0U);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    int iRes = ::kill(culPid, SIGKILL);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
CxProcess::TxId
CxProcess::ulGetIdByHandle(
    const TxHandle &chHandle    ///< handle
)
{
    TxId ulRes;

#if   xOS_ENV_WIN
    ulRes = ::GetProcessId(chHandle);
    xDEBUG_VAR_NA(ulRes);
#elif xOS_ENV_UNIX
    ulRes = static_cast<TxId>( chHandle );
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
/*static*/
CxProcess::TxHandle
CxProcess::ulGetHandleById(
    const TxId &culId   ///< ID
)
{
    TxHandle hRes;

#if   xOS_ENV_WIN
    hRes = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, culId);
    xDEBUG_VAR_NA(hRes);
#elif xOS_ENV_UNIX
    hRes = static_cast<TxHandle>( culId );
#endif

    return hRes;
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
