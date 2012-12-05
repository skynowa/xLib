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


    bool bRv = false;

#if   xOS_ENV_WIN
    bRv = (ulId() == a_culId);
#elif xOS_ENV_UNIX
    // TODO: If either thread1 or thread2 are not valid thread IDs, the behavior is undefined
    // bRv = ::pthread_equal(ulGetId(), a_culId);
#endif

    return bRv;
}
//---------------------------------------------------------------------------
/* static */
CxProcess::id_t
CxCurrentProcess::ulId() {
    // n/a

    CxProcess::id_t ulRv;

#if   xOS_ENV_WIN
    ulRv = ::GetCurrentProcessId();
    // n/a
#elif xOS_ENV_UNIX
    ulRv = ::getpid();
    // n/a
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/* static */
CxProcess::id_t
CxCurrentProcess::ulParentId() {
    // n/a

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

    typedef NTSTATUS (WINAPI *Dll_NtQueryInformationProcess_t) (
        HANDLE           ProcessHandle,
        PROCESSINFOCLASS ProcessInformationClass,
        PVOID            ProcessInformation,
        ULONG            ProcessInformationLength,
        PULONG           ReturnLength
    );

    const CxProcess::id_t culInvalidId = (DWORD)- 1;

    CxDll dlDll;

    dlDll.vLoad(xT("ntdll.dll"));

    bool bRv = dlDll.bIsProcExists(xT("NtQueryInformationProcess"));
    xCHECK_RET(false == bRv, culInvalidId);

    const PROCESSINFOCLASS    cpicInfo86               = ProcessBasicInformation;
    const PROCESSINFOCLASS    cpicInfo64               = ProcessWow64Information;   xUNUSED(cpicInfo64);
    ULONG_PTR                 pulProcessInformation[6] = {0};
    DWORD                     dwReturnSize             = 0UL;   // in bytes

    Dll_NtQueryInformationProcess_t
    DllNtQueryInformationProcess = (Dll_NtQueryInformationProcess_t)dlDll.fpProcAddress(xT("NtQueryInformationProcess"));
    xTEST_PTR(DllNtQueryInformationProcess);

    // TODO: ProcessBasicInformation (for x64)
    NTSTATUS ntsRes = DllNtQueryInformationProcess(hHandle(),
                                                   cpicInfo86,
                                                   &pulProcessInformation, sizeof(pulProcessInformation), &dwReturnSize);
    xTEST_EQ(true, NT_SUCCESS(ntsRes));
    xTEST_EQ(size_t(dwReturnSize), sizeof(pulProcessInformation));

    ulRv = pulProcessInformation[5];
#elif xOS_ENV_UNIX
    ulRv = ::getppid();
    // n/a
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
// TODO: tests
/* static */
CxProcess::handle_t
CxCurrentProcess::hHandle() {
    // n/a

    CxProcess::handle_t hRv;

#if   xOS_ENV_WIN
    #if xDEPRECIATE
        hRv = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, ulGetId());
    #else
        hRv = ::GetCurrentProcess();
    #endif
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
#elif xOS_ENV_UNIX
    hRv = ::getpid();
    // n/a
#endif

    return hRv;
}
//---------------------------------------------------------------------------
// TODO: tests
/* static */
void
CxCurrentProcess::vExit(
    const uint_t &a_cuiExitCode
)
{


#if   xOS_ENV_WIN
    (void)::ExitProcess(a_cuiExitCode);
#elif xOS_ENV_UNIX
    (void)::exit(static_cast<int>( a_cuiExitCode ));
#endif
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
