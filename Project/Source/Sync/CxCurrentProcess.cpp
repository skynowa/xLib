/**
 * \file   CxCurrentProcess.cpp
 * \brief
 */


#include <xLib/Sync/CxCurrentProcess.h>

#include <xLib/Filesystem/CxDll.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
bool
CxCurrentProcess::bIsCurrent(
    const CxProcess::TxId culId
)
{
    /*DEBUG*/

    bool bRv = false;

#if xOS_ENV_WIN
    bRv = (ulGetId() == culId);
#elif xOS_ENV_UNIX
    // TODO: If either thread1 or thread2 are not valid thread IDs, the behavior is undefined
    // bRv = ::pthread_equal(ulGetId(), culId);
#endif

    return bRv;
}
//---------------------------------------------------------------------------
/*static*/
CxProcess::TxId
CxCurrentProcess::ulGetId() {
    /*DEBUG*/// n/a

    CxProcess::TxId ulRv;

#if xOS_ENV_WIN
    ulRv = ::GetCurrentProcessId();
    /*DEBUG*/// n/a
#elif xOS_ENV_UNIX
    ulRv = ::getpid();
    /*DEBUG*/// n/a
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/*static*/
CxProcess::TxId
CxCurrentProcess::ulGetParentId() {
    /*DEBUG*/// n/a

    CxProcess::TxId ulRv;

#if xOS_ENV_WIN
    #if xCOMPILER_MINGW32 || xCOMPILER_CODEGEAR
        //typedef __success(return >= 0) LONG NTSTATUS;
        typedef LONG NTSTATUS;

        enum PROCESSINFOCLASS
            /// process info type
        {
            ProcessBasicInformation = 0,
            ProcessWow64Information = 26
        };
    #endif

    typedef NTSTATUS (WINAPI *TDllNtQueryInformationProcess)(HANDLE ProcessHandle, PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);

    const CxProcess::TxId culInvalidId = (ulong_t)- 1;

    bool  bRv   = false;
    CxDll dlDll;

    bRv = dlDll.bLoad(xT("ntdll.dll"));
    /*DEBUG*/xASSERT_RET(true == bRv, culInvalidId);

    bRv = dlDll.bIsProcExists(xT("NtQueryInformationProcess"));
    xCHECK_RET(false == bRv, culInvalidId);

    ULONG_PTR pulProcessInformation[6] = {0};
    ULONG     ulReturnLength           = 0UL;

    TDllNtQueryInformationProcess DllNtQueryInformationProcess = (TDllNtQueryInformationProcess)dlDll.fpGetProcAddress(xT("NtQueryInformationProcess"));
    /*DEBUG*/xASSERT_RET(NULL != DllNtQueryInformationProcess, culInvalidId);

    NTSTATUS ntsRes = DllNtQueryInformationProcess(hGetHandle(), ProcessBasicInformation, &pulProcessInformation, sizeof(pulProcessInformation), &ulReturnLength);
    bRv = (ntsRes >= 0 && ulReturnLength == sizeof(pulProcessInformation));
    /*DEBUG*/xASSERT_RET(true == bRv, culInvalidId);

    ulRv = pulProcessInformation[5];
#elif xOS_ENV_UNIX
    ulRv = ::getppid();
    /*DEBUG*/// n/a
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
// TODO: tests
/*static*/
CxProcess::TxHandle
CxCurrentProcess::hGetHandle() {
    /*DEBUG*/// n/a

    CxProcess::TxHandle hRv;

#if xOS_ENV_WIN
    #if xDEPRECIATE
        hRv = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, ulGetId());
    #else
        hRv = ::GetCurrentProcess();
    #endif
    /*DEBUG*/xASSERT_RET(NULL != hRv, NULL);
#elif xOS_ENV_UNIX
    hRv = ::getpid();
    /*DEBUG*/// n/a
#endif

    return hRv;
}
//---------------------------------------------------------------------------
// TODO: tests
/*static*/
bool
CxCurrentProcess::bExit(
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


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCurrentProcess::CxCurrentProcess() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxCurrentProcess::~CxCurrentProcess() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
