/**
 * \file  CxProcess.cpp
 * \brief process
 */


#include <xLib/Sync/CxProcess.h>

#include <xLib/Filesystem/CxFile.h>
#include <xLib/Sync/CxCurrentThread.h>
#include <xLib/Sync/CxCurrentProcess.h>

#if xOS_ENV_WIN
    #if !xCOMPILER_MINGW32
        #pragma comment(lib, "psapi.lib")
    #endif
#elif xOS_ENV_UNIX
    xNA
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxProcess::CxProcess() :
    _m_hHandle     (0),
#if xOS_ENV_WIN
    _m_hThread     (NULL),
#endif
    _m_ulPid       (0UL),
    _m_uiExitStatus(0U)
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxProcess::~CxProcess() {
#if xOS_ENV_WIN
    BOOL blRes = FALSE;

    blRes = ::CloseHandle(_m_hThread);
    /*DEBUG*/xASSERT(FALSE != blRes);

    blRes = ::CloseHandle(_m_hHandle);
    /*DEBUG*/xASSERT(FALSE != blRes);
#elif xOS_ENV_UNIX

#endif
}
//---------------------------------------------------------------------------
bool
CxProcess::bCreate(
    const std::tstring_t &csFilePath,
    const tchar_t        *pcszParams, ...
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),            false);
    /*DEBUG*/xASSERT_RET(true  == CxFile::bIsExists(csFilePath), false);
    /*DEBUG*/xASSERT_RET(NULL  != pcszParams,                    false);

    std::tstring_t sCmdLine;

    va_list palArgs;
    xVA_START(palArgs, pcszParams);
    sCmdLine = CxString::sFormatV(pcszParams, palArgs);
    xVA_END(palArgs);

    //xTRACEV(xT("sCmdLine: %s"), sCmdLine.c_str());

#if xOS_ENV_WIN
    STARTUPINFO         siInfo = {0};   siInfo.cb = sizeof(siInfo);
    PROCESS_INFORMATION piInfo = {0};

    BOOL blRes = ::CreateProcess(csFilePath.c_str(), const_cast<LPTSTR>( sCmdLine.c_str() ),
                                 NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL,
                                 &siInfo, &piInfo);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    _m_hHandle = piInfo.hProcess;
    _m_hThread = piInfo.hThread;
    _m_ulPid   = piInfo.dwProcessId;
#elif xOS_ENV_UNIX
    pid_t liPid = ::fork();
    /*DEBUG*/xASSERT_RET(- 1L != liPid, false);

    if (0L == liPid) {
        // TODO: csFilePath is executable

        int iRv = ::execlp(csFilePath.c_str(), csFilePath.c_str(), sCmdLine.c_str(), static_cast<const tchar_t *>( NULL ));
        /*DEBUG*/xASSERT_RET(- 1 != iRv, false);

        (void)::_exit(EXIT_SUCCESS);  /* not exit() */
    }

    _m_hHandle = liPid;
    _m_ulPid   = liPid;
#endif

    return true;
}
//---------------------------------------------------------------------------
CxProcess::EWaitResult
CxProcess::ulWait(
    const ulong_t culTimeout
)
{
    EWaitResult wrStatus = wrFailed;

#if xOS_ENV_WIN
    DWORD ulRv = ::WaitForSingleObject(_m_hHandle, culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == ulRv, static_cast<EWaitResult>( ulRv ));

    wrStatus = static_cast<EWaitResult>( ulRv );
#elif xOS_ENV_UNIX
    pid_t liRv   = - 1L;
    int   iStatus = 0;

    do {
        liRv = ::waitpid(_m_ulPid, &iStatus, 0);
    }
    while (liRv < 0L && EINTR == CxLastError::ulGet());
    /*DEBUG*/xASSERT_RET(liRv == _m_ulPid, static_cast<EWaitResult>( iStatus ));

    _m_uiExitStatus = WEXITSTATUS(iStatus);
    wrStatus        = static_cast<EWaitResult>( WEXITSTATUS(iStatus) );
#endif

    return wrStatus;
}
//---------------------------------------------------------------------------
bool
CxProcess::bKill(
    const ulong_t culTimeout    // FIX: culTimeout not used
)
{
    /*DEBUG*/

    bool    bRv  = false;
    ulong_t ulRv = 0UL;

#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, false);
    /*DEBUG*/// ulTimeout - n/a

    _m_uiExitStatus = 0U;

    BOOL blRes = ::TerminateProcess(_m_hHandle, _m_uiExitStatus);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    for ( ; ; ) {
        ulRv = ulGetExitStatus();
        xCHECK_DO(STILL_ACTIVE != ulRv, break);

        bRv = CxCurrentThread::bSleep(culTimeout);
        /*DEBUG*/xASSERT_DO(true == bRv, break);
    }
#elif xOS_ENV_UNIX
    int iRv = ::kill(_m_ulPid, SIGKILL);
    /*DEBUG*/xASSERT_RET(- 1 != iRv, false);

    bRv = CxCurrentThread::bSleep(culTimeout);
    /*DEBUG*/xASSERT(true == bRv);

    _m_uiExitStatus = 0U;
#endif

    return true;
}
//---------------------------------------------------------------------------
CxProcess::TxHandle
CxProcess::hGet() const {
    /*DEBUG*/

    return _m_hHandle;
}
//---------------------------------------------------------------------------
CxProcess::TxId
CxProcess::ulGetId() const {
    /*DEBUG*/

    return _m_ulPid;
}
//---------------------------------------------------------------------------
bool
CxProcess::bIsCurrent() const {
    /*DEBUG*/

    return CxCurrentProcess::bIsCurrent( CxCurrentProcess::ulGetId() );
}
//---------------------------------------------------------------------------
ulong_t
CxProcess::ulGetExitStatus() const {
    /*DEBUG*/

    ulong_t ulRv = 0UL;

#if xOS_ENV_WIN
    BOOL blRes = ::GetExitCodeProcess(_m_hHandle, &ulRv);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, ulRv);
#elif xOS_ENV_UNIX
    ulRv = _m_uiExitStatus;
#endif

    return ulRv;
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
    TxId ulRv;

#if   xOS_ENV_WIN
    ulRv = ::GetProcessId(chHandle);
    xDEBUG_VAR_NA(ulRv);
#elif xOS_ENV_UNIX
    ulRv = static_cast<TxId>( chHandle );
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/*static*/
CxProcess::TxHandle
CxProcess::ulGetHandleById(
    const TxId culId   ///< ID
)
{
    TxHandle hRv;

#if   xOS_ENV_WIN
    hRv = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, culId);
    xDEBUG_VAR_NA(hRv);
#elif xOS_ENV_UNIX
    hRv = static_cast<TxHandle>( culId );
#endif

    return hRv;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
