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

    bool      bRes   = false;
    CxDll     objDll;

    ULONG_PTR pbi[6] = {0}; 
    ulong_t   ulSize = 0UL;
    typedef long_t (WINAPI *fpProcAddress)(HANDLE ProcessHandle, PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ulong_t ProcessInformationLength, PULONG ReturnLength);

    bRes = objDll.bLoad(xT("ntdll.dll"));
    /*DEBUG*/xASSERT_RET(true == bRes, culInvalidId);

    fpProcAddress NtQueryInformationProcess = (fpProcAddress)objDll.fpGetProcAddress("NtQueryInformationProcess");
    /*DEBUG*/xASSERT_RET(NULL != NtQueryInformationProcess, culInvalidId);

    NTSTATUS ntsRes = NtQueryInformationProcess(hGetHandle(), ProcessBasicInformation, &pbi, sizeof(pbi), &ulSize);
    bRes = (ntsRes >= 0) && (ulSize == sizeof(pbi));
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
