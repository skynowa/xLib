/**
 * \file   CxCurrentProcess.cpp
 * \brief
 */


#include <xLib/Sync/CxCurrentProcess.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
CxProcess::TxId
CxCurrentProcess::ulGetId() {
    /*DEBUG*/// n/a

    CxProcess::TxId ulRes;

#if defined(xOS_ENV_WIN)
    ulRes = ::GetCurrentProcessId();
    /*DEBUG*/// n/a
#elif defined(xOS_ENV_UNIX)
    ulRes = getpid();
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

#if defined(xOS_ENV_WIN)
    const CxProcess::TxId culInvalidId = (ULONG)- 1;

    ULONG_PTR pbi[6] = {0};
    ULONG     ulSize = 0UL;
    LONG (WINAPI *NtQueryInformationProcess)(HANDLE ProcessHandle, ULONG ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);

    HMODULE hModule = ::GetModuleHandle(xT("ntdll.dll"));
    /*DEBUG*/xASSERT_RET(NULL != hModule, culInvalidId);

    *(FARPROC *)&NtQueryInformationProcess = ::GetProcAddress(hModule, "NtQueryInformationProcess");
    /*DEBUG*/xASSERT_RET(NULL != NtQueryInformationProcess, culInvalidId);

    BOOL bRes = ( NtQueryInformationProcess(CxHandleT<hvNull>::hGetCurrentProcess(), 0, &pbi, sizeof(pbi), &ulSize) >= 0 && ulSize == sizeof(pbi) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, culInvalidId);

    ulRes = pbi[5];
#elif defined(xOS_ENV_UNIX)
    ulRes = getppid();
    /*DEBUG*/// n/a
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
/*static*/
CxProcess::TxHandle
CxCurrentProcess::hGetHandle() {
    /*DEBUG*/// n/a

    CxProcess::TxHandle hRes;

#if defined(xOS_ENV_WIN)
    hRes = ::GetCurrentProcess();
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);
#elif defined(xOS_ENV_UNIX)
    hRes = getpid();
    /*DEBUG*/// n/a
#endif

    return hRes;
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