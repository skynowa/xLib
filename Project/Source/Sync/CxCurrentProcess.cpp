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

    bool bRes = false;

#if xOS_ENV_WIN
    bRes = (ulGetId() == culId);
#elif xOS_ENV_UNIX
    // TODO: If either thread1 or thread2 are not valid thread IDs, the behavior is undefined
    // bRes = ::pthread_equal(ulGetId(), culId);
#endif

    return bRes;
}
//---------------------------------------------------------------------------
/*static*/
CxProcess::TxId
CxCurrentProcess::ulGetId() {
    /*DEBUG*/// n/a

    CxProcess::TxId ulRes;

#if xOS_ENV_WIN
    ulRes = ::GetCurrentProcessId();
    /*DEBUG*/// n/a
#elif xOS_ENV_UNIX
    ulRes = ::getpid();
    /*DEBUG*/// n/a
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
/*static*/
CxProcess::TxId
CxCurrentProcess::ulGetParentId() {
    /*DEBUG*/// n/a

    CxProcess::TxId ulRes;

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

	bool  bRes   = false;
	CxDll dlDll;

	bRes = dlDll.bLoad(xT("ntdll.dll"));
	/*DEBUG*/xASSERT_RET(true == bRes, culInvalidId);

    bRes = dlDll.bIsProcExists(xT("NtQueryInformationProcess"));
    xCHECK_RET(false == bRes, culInvalidId);

	ULONG_PTR pulProcessInformation[6] = {0};
	ULONG     ulReturnLength           = 0UL;

	TDllNtQueryInformationProcess DllNtQueryInformationProcess = (TDllNtQueryInformationProcess)dlDll.fpGetProcAddress(xT("NtQueryInformationProcess"));
	/*DEBUG*/xASSERT_RET(NULL != DllNtQueryInformationProcess, culInvalidId);

	NTSTATUS ntsRes = DllNtQueryInformationProcess(hGetHandle(), ProcessBasicInformation, &pulProcessInformation, sizeof(pulProcessInformation), &ulReturnLength);
	bRes = (ntsRes >= 0 && ulReturnLength == sizeof(pulProcessInformation));
	/*DEBUG*/xASSERT_RET(true == bRes, culInvalidId);

	ulRes = pulProcessInformation[5];
#elif xOS_ENV_UNIX
    ulRes = ::getppid();
    /*DEBUG*/// n/a
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
// TODO: tests
/*static*/
CxProcess::TxHandle
CxCurrentProcess::hGetHandle() {
    /*DEBUG*/// n/a

    CxProcess::TxHandle hRes;

#if xOS_ENV_WIN
    #if xDEPRECIATE
        hRes = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, ulGetId());
    #else
        hRes = ::GetCurrentProcess();
    #endif
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);
#elif xOS_ENV_UNIX
    hRes = ::getpid();
    /*DEBUG*/// n/a
#endif

    return hRes;
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
