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
    const CxProcess::TxId culInvalidId = (ulong_t)- 1;

    ULONG_PTR pbi[6] = {0};
    ulong_t     ulSize = 0UL;
    long_t (WINAPI *NtQueryInformationProcess)(HANDLE ProcessHandle, ulong_t ProcessInformationClass, PVOID ProcessInformation, ulong_t ProcessInformationLength, PULONG ReturnLength);

    HMODULE hModule = ::GetModuleHandle(xT("ntdll.dll"));
    /*DEBUG*/xASSERT_RET(NULL != hModule, culInvalidId);

    *(FARPROC *)&NtQueryInformationProcess = ::GetProcAddress(hModule, "NtQueryInformationProcess");
    /*DEBUG*/xASSERT_RET(NULL != NtQueryInformationProcess, culInvalidId);

    bool bRes = ( NtQueryInformationProcess(hGetHandle(), 0, &pbi, sizeof(pbi), &ulSize) >= 0 && ulSize == sizeof(pbi) );
    /*DEBUG*/xASSERT_RET(false != bRes, culInvalidId);

    ulRes = pbi[5];
#elif xOS_ENV_UNIX
    ulRes = ::getppid();
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

#if xOS_ENV_WIN
    #if xDEPRECIATE
        hRes = ::OpenProcess(PROCESS_ALL_ACCESS, false, CxProcess::ulGetCurrId());
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
