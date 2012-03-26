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
CxProcess::CxProcess() :
    _m_hHandle(0),
#if xOS_ENV_WIN
    _m_hThread(NULL),
#endif
    _m_ulPid  (0UL)
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxProcess::~CxProcess() {
#if xOS_ENV_WIN
    BOOL blRes = FALSE;

    blRes = ::CloseHandle(_m_hHandle);
    /*DEBUG*/xASSERT(FALSE != blRes);

    blRes = ::CloseHandle(_m_hThread);
    /*DEBUG*/xASSERT(FALSE != blRes);
#elif xOS_ENV_UNIX

#endif
}
//---------------------------------------------------------------------------
bool
CxProcess::bCreate(
    const std::tstring_t &csFilePath,
    const tchar_t        *pcszCmdLine, ...
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != pcszCmdLine,        false);

    std::tstring_t sCmdLine;

    va_list palArgs;
    xVA_START(palArgs, pcszCmdLine);

    sCmdLine = csFilePath + CxString::sFormatV(pcszCmdLine, palArgs);

    xVA_END(palArgs);

#if xOS_ENV_WIN
    BOOL                blRes  = FALSE;
    STARTUPINFO         siInfo = {0};   siInfo.cb = sizeof(siInfo);
    PROCESS_INFORMATION piInfo = {0};

    blRes = ::CreateProcess(NULL, &sCmdLine.at(0), NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &siInfo, &piInfo);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    _m_hHandle = piInfo.hProcess;
    _m_hThread = piInfo.hThread;
    _m_ulPid   = piInfo.dwProcessId;
#elif xOS_ENV_UNIX
    pid_t liPid = ::fork();
    /*DEBUG*/xASSERT_RET(- 1L != liPid, false);

    if (0L == liPid) {
        // TODO: csFilePath is executable

        int iRes = ::execlp(csFilePath.c_str(), csFilePath.c_str(), sCmdLine.c_str(), static_cast<const tchar_t *>( NULL ));
        /*DEBUG*/xASSERT_RET(- 1 != iRes, false);

        (void)::_exit(EXIT_SUCCESS);  /* not exit() */
    }

    _m_hHandle = liPid;
    _m_ulPid   = liPid;
#endif

    return true;
}
//---------------------------------------------------------------------------
// TODO: ulWait (not work)
CxProcess::EWaitResult
CxProcess::ulWait(
    const ulong_t culTimeout
)
{
    EWaitResult wrStatus = wrFailed;

#if xOS_ENV_WIN
    DWORD ulRes = ::WaitForSingleObject(_m_hHandle, culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == ulRes, static_cast<EWaitResult>( ulRes ));

    wrStatus = static_cast<EWaitResult>( ulRes );
#elif xOS_ENV_UNIX
    pid_t liRes   = - 1;
    int   iStatus = 0;

    do {
        liRes = ::waitpid(_m_ulPid, &iStatus, 0);
    }
    while (liRes < 0 && errno == EINTR);
    /*DEBUG*/xASSERT_RET(liRes == _m_ulPid, static_cast<EWaitResult>( iStatus ));

    wrStatus = static_cast<EWaitResult>( WEXITSTATUS(iStatus) );
#endif

    return wrStatus;
}
//---------------------------------------------------------------------------
bool
CxProcess::bKill() {
    /*DEBUG*/

#if xOS_ENV_WIN
    BOOL blRes = ::TerminateProcess(_m_hHandle, 0U);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    int iRes = ::kill(_m_ulPid, SIGKILL);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public, static
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
CxProcess::TxId
CxProcess::ulGetIdByHandle(
    const TxHandle chHandle    ///< handle
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
    const TxId culId   ///< ID
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

xNAMESPACE_END(NxLib)
