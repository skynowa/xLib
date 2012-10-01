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
/* static */
bool
CxCurrentProcess::bIsCurrent(
    const CxProcess::id_t &a_culId
)
{
    /*DEBUG*/

    bool bRv = false;

#if   xOS_ENV_WIN
    bRv = (ulGetId() == a_culId);
#elif xOS_ENV_UNIX
    // TODO: If either thread1 or thread2 are not valid thread IDs, the behavior is undefined
    // bRv = ::pthread_equal(ulGetId(), a_culId);
#endif

    return bRv;
}
//---------------------------------------------------------------------------
/* static */
CxProcess::id_t
CxCurrentProcess::ulGetId() {
    /*DEBUG*/// n/a

    CxProcess::id_t ulRv;

#if   xOS_ENV_WIN
    ulRv = ::GetCurrentProcessId();
    /*DEBUG*/// n/a
#elif xOS_ENV_UNIX
    ulRv = ::getpid();
    /*DEBUG*/// n/a
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/* static */
CxProcess::id_t
CxCurrentProcess::ulGetParentId() {
    /*DEBUG*/// n/a

    CxProcess::id_t ulRv;

#if   xOS_ENV_WIN
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

    typedef NTSTATUS (WINAPI *Dll_NtQueryInformationProcess_t)(HANDLE ProcessHandle, PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);

    const CxProcess::id_t culInvalidId = (ulong_t)- 1;

    bool  bRv   = false;
    CxDll dlDll;

    bRv = dlDll.bLoad(xT("ntdll.dll"));
    /*DEBUG*/xTEST_EQ(true, bRv);

    bRv = dlDll.bIsProcExists(xT("NtQueryInformationProcess"));
    xCHECK_RET(false == bRv, culInvalidId);

    ULONG_PTR pulProcessInformation[6] = {0};
    ULONG     ulReturnLength           = 0UL;

    Dll_NtQueryInformationProcess_t DllNtQueryInformationProcess = (Dll_NtQueryInformationProcess_t)dlDll.fpGetProcAddress(xT("NtQueryInformationProcess"));
    /*DEBUG*/xTEST_PTR(DllNtQueryInformationProcess);

    NTSTATUS ntsRes = DllNtQueryInformationProcess(hGetHandle(), ProcessBasicInformation, &pulProcessInformation, sizeof(pulProcessInformation), &ulReturnLength);
    bRv = (ntsRes >= 0 && ulReturnLength == sizeof(pulProcessInformation));
    /*DEBUG*/xTEST_EQ(true, bRv);

    ulRv = pulProcessInformation[5];
#elif xOS_ENV_UNIX
    ulRv = ::getppid();
    /*DEBUG*/// n/a
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
// TODO: tests
/* static */
CxProcess::handle_t
CxCurrentProcess::hGetHandle() {
    /*DEBUG*/// n/a

    CxProcess::handle_t hRv;

#if   xOS_ENV_WIN
    #if xDEPRECIATE
        hRv = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, ulGetId());
    #else
        hRv = ::GetCurrentProcess();
    #endif
    /*DEBUG*/xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
#elif xOS_ENV_UNIX
    hRv = ::getpid();
    /*DEBUG*/// n/a
#endif

    return hRv;
}
//---------------------------------------------------------------------------
// TODO: tests
/* static */
bool
CxCurrentProcess::bExit(
    const uint_t &a_cuiExitCode
)
{
    /*DEBUG*/

#if   xOS_ENV_WIN
    (void)::ExitProcess(a_cuiExitCode);
#elif xOS_ENV_UNIX
    (void)::exit(static_cast<int>( a_cuiExitCode ));
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
/* virtual */
CxCurrentProcess::~CxCurrentProcess() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
