/**
 * \file  CxProcess.cpp
 * \brief process
 */


#include <xLib/Sync/CxProcess.h>

#include <xLib/Common/CxString.h>
#include <xLib/Common/CxSystemInfo.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Sync/CxCurrentThread.h>
#include <xLib/Sync/CxCurrentProcess.h>

#if   xOS_ENV_WIN
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
#if   xOS_ENV_WIN
    _m_hThread     (NULL),
#endif
    _m_ulPid       (0UL),
    _m_uiExitStatus(0U)
{

}
//---------------------------------------------------------------------------
/* virtual */
CxProcess::~CxProcess() {
#if   xOS_ENV_WIN
    BOOL blRes = FALSE;

    blRes = ::CloseHandle(_m_hThread);
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);

    blRes = ::CloseHandle(_m_hHandle);
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX

#endif
}
//---------------------------------------------------------------------------
bool
CxProcess::bCreate(
    const std::tstring_t &a_csFilePath,
    const tchar_t        *a_pcszParams, ...
)
{
    /*DEBUG*/xASSERT_RET(false == a_csFilePath.empty(),            false);
    /*DEBUG*/xASSERT_RET(true  == CxFile::bIsExists(a_csFilePath), false);
    /*DEBUG*/xASSERT_RET(NULL  != a_pcszParams,                    false);

    std::tstring_t sCmdLine;

    va_list palArgs;
    xVA_START(palArgs, a_pcszParams);
    sCmdLine = CxString::sFormatV(a_pcszParams, palArgs);
    xVA_END(palArgs);

    //xTRACEV(xT("sCmdLine: %s"), sCmdLine.c_str());

#if   xOS_ENV_WIN
    STARTUPINFO         siInfo = {0};   siInfo.cb = sizeof(siInfo);
    PROCESS_INFORMATION piInfo = {0};

    BOOL blRes = ::CreateProcess(a_csFilePath.c_str(), const_cast<LPTSTR>( sCmdLine.c_str() ),
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

        int iRv = ::execlp(a_csFilePath.c_str(), a_csFilePath.c_str(), sCmdLine.c_str(), static_cast<const tchar_t *>( NULL ));
        /*DEBUG*/xASSERT_RET(- 1 != iRv, false);

        (void)::_exit(EXIT_SUCCESS);  /* not exit() */
    }

    _m_hHandle = liPid;
    _m_ulPid   = liPid;
#endif

    return true;
}
//---------------------------------------------------------------------------
CxProcess::ExWaitResult
CxProcess::ulWait(
    const ulong_t &a_culTimeout
)
{
    ExWaitResult wrStatus = wrFailed;

#if   xOS_ENV_WIN
    DWORD ulRv = ::WaitForSingleObject(_m_hHandle, a_culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == ulRv, static_cast<ExWaitResult>( ulRv ));

    wrStatus = static_cast<ExWaitResult>( ulRv );
#elif xOS_ENV_UNIX
    // TODO: a_culTimeout
    pid_t liRv    = - 1L;
    int   iStatus = 0;

    do {
        liRv = ::waitpid(_m_ulPid, &iStatus, 0);
    }
    while (liRv < 0L && EINTR == CxLastError::ulGet());
    /*DEBUG*/xASSERT_RET(liRv == _m_ulPid, static_cast<ExWaitResult>( iStatus ));

    _m_uiExitStatus = WEXITSTATUS(iStatus);
    wrStatus        = static_cast<ExWaitResult>( WEXITSTATUS(iStatus) );
#endif

    return wrStatus;
}
//---------------------------------------------------------------------------
bool
CxProcess::bKill(
    const ulong_t &a_culTimeout    // FIX: culTimeout not used
)
{
    /*DEBUG*/

    bool    bRv  = false;
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, false);
    /*DEBUG*/// ulTimeout - n/a

    _m_uiExitStatus = 0U;

    BOOL blRes = ::TerminateProcess(_m_hHandle, _m_uiExitStatus);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    for ( ; ; ) {
        ulRv = ulGetExitStatus();
        xCHECK_DO(STILL_ACTIVE != ulRv, break);

        bRv = CxCurrentThread::bSleep(a_culTimeout);
        /*DEBUG*/xTEST_EQ(true, bRv);
    }
#elif xOS_ENV_UNIX
    int iRv = ::kill(_m_ulPid, SIGKILL);
    /*DEBUG*/xASSERT_RET(- 1 != iRv, false);

    bRv = CxCurrentThread::bSleep(a_culTimeout);
    /*DEBUG*/xASSERT(true == bRv);

    _m_uiExitStatus = 0U;
#endif

    return true;
}
//---------------------------------------------------------------------------
CxProcess::handle_t
CxProcess::hGet() const {
    /*DEBUG*/

    return _m_hHandle;
}
//---------------------------------------------------------------------------
CxProcess::id_t
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

#if   xOS_ENV_WIN
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
/* static */
CxProcess::id_t
CxProcess::ulGetIdByHandle(
    const handle_t &a_chHandle    ///< handle
)
{
    id_t ulRv;

#if   xOS_ENV_WIN
    ulRv = ::GetProcessId(a_chHandle);
    xDEBUG_VAR_NA(ulRv);
#elif xOS_ENV_UNIX
    ulRv = static_cast<id_t>( a_chHandle );
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/* static */
CxProcess::handle_t
CxProcess::ulGetHandleById(
    const id_t &a_culId   ///< ID
)
{
    handle_t hRv;

#if   xOS_ENV_WIN
    hRv = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, a_culId);
    xDEBUG_VAR_NA(hRv);
#elif xOS_ENV_UNIX
    hRv = static_cast<handle_t>( a_culId );
#endif

    return hRv;
}
//--------------------------------------------------------------------------
/* static */
bool
CxProcess::bIsRunning(
    const std::tstring_t &a_csProcessName
)
{
#if   xOS_ENV_WIN
    typedef CxHandleT<hvInvalid> snapshot_t;

    snapshot_t      hSnapshot;
    PROCESSENTRY32  peProcess = {0};    peProcess.dwSize = sizeof(PROCESSENTRY32);

    hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0UL);
    /*DEBUG*/xASSERT_RET(true == hSnapshot.bIsValid(), false);

    BOOL blRv = ::Process32First(hSnapshot.hGet(), &peProcess);
    /*DEBUG*/xASSERT_RET(FALSE != blRv, false);

    for ( ; ; ) {
        bool bRv = CxString::bCompareNoCase(a_csProcessName, peProcess.szExeFile);
        xCHECK_RET(true == bRv, true);   // OK

        blRv = ::Process32Next(hSnapshot.hGet(), &peProcess);
        xCHECK_DO(FALSE == blRv, break);
    }
#elif xOS_ENV_UNIX
    // TODO: CxProcess::bIsRunning
#endif

    return false;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
