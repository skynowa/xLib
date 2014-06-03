/**
 * \file  CxProcess.inl
 * \brief process
 */


#if !xCOMPILER_MINGW
    #pragma comment(lib, "psapi.lib")
#endif


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxProcess::_destruct_impl()
{
    BOOL blRv = FALSE;

    blRv = ::CloseHandle(_thread);
    xTEST_DIFF(blRv, FALSE);

    blRv = ::CloseHandle(_handle);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxProcess::_create_impl(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_params
)
{
    STARTUPINFO         startupInfo = {0};  startupInfo.cb = sizeof(startupInfo);
    PROCESS_INFORMATION processInfo = {0};

    BOOL blRv = ::CreateProcess(a_filePath.c_str(), const_cast<LPTSTR>( a_params.c_str() ),
        xPTR_NULL, xPTR_NULL, FALSE, NORMAL_PRIORITY_CLASS, xPTR_NULL, xPTR_NULL, &startupInfo,
        &processInfo);
    xTEST_DIFF(blRv, FALSE);

    _handle = processInfo.hProcess;
    _thread = processInfo.hThread;
    _pid    = processInfo.dwProcessId;
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::ExWaitResult
CxProcess::_wait_impl(
    culong_t &a_timeoutMsec
)
{
    ExWaitResult waitStatus = wrFailed;

    DWORD dwRv = ::WaitForSingleObject(_handle, a_timeoutMsec);
    xTEST_EQ(dwRv, WAIT_OBJECT_0);

    waitStatus = static_cast<ExWaitResult>( dwRv );

    return waitStatus;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxProcess::_kill_impl(
    culong_t &a_timeoutMsec
)
{
    xTEST_DIFF(_handle, xNATIVE_HANDLE_NULL);
    xTEST_NA(a_timeoutMsec);

    _exitStatus = 0U;

    BOOL blRv = ::TerminateProcess(_handle, _exitStatus);
    xTEST_DIFF(blRv, FALSE);

    for ( ; ; ) {
        xCHECK_DO(exitStatus() != STILL_ACTIVE, break);

        CxThread::currentSleep(a_timeoutMsec);
    }
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcess::_exitStatus_impl() const
{
    ulong_t ulRv = 0UL;

    BOOL blRv = ::GetExitCodeProcess(_handle, &ulRv);
    xTEST_DIFF(blRv, FALSE);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxProcess::id_t
CxProcess::_idByHandle_impl(
    const handle_t &a_handle    ///< handle
)
{
    id_t ulRv = ::GetProcessId(a_handle);
    xTEST_NA(ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::handle_t
CxProcess::_handleById_impl(
    const id_t &a_id   ///< ID
)
{
    handle_t hRv = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, a_id);
    xTEST_NA(hRv);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline
CxProcess::id_t
CxProcess::_idByName_impl(
    std::ctstring_t &a_processName
)
{
    id_t ulRv;

    CxHandle       snapshot;
    PROCESSENTRY32 processEntry = {0};
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0UL);
    xTEST_EQ(snapshot.isValid(), true);

    BOOL blRv = ::Process32First(snapshot.get(), &processEntry);
    xTEST_DIFF(blRv, FALSE);

    for ( ; ; ) {
        bool_t bRv = CxStringCI::compare(a_processName, processEntry.szExeFile);
        xCHECK_DO(bRv, break);   // OK

        blRv = ::Process32Next(snapshot.get(), &processEntry);
        xCHECK_DO(blRv == FALSE, break);
    }

    ulRv = processEntry.th32ProcessID;
    xTEST_DIFF(ulRv, 0UL);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxProcess::_ids_impl(
    std::vector<CxProcess::id_t> *a_ids
)
{
    std::vector<id_t> vidRv;

    CxHandle       snapshot;
    PROCESSENTRY32 processEntry = {0};
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0UL);
    xTEST_EQ(snapshot.isValid(), true);

    BOOL blRv = ::Process32First(snapshot.get(), &processEntry);
    xTEST_DIFF(blRv, FALSE);

    for ( ; ; ) {
        DWORD pid = processEntry.th32ProcessID;

        vidRv.push_back(pid);

        blRv = ::Process32Next(snapshot.get(), &processEntry);
        xCHECK_DO(blRv == FALSE, break);
    }

    // out
    a_ids->swap(vidRv);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxProcess::_isCurrent_impl(
    const CxProcess::id_t &a_id
)
{
    bool_t bRv = (currentId() == a_id);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::id_t
CxProcess::_currentId_impl()
{
    id_t ulRv = ::GetCurrentProcessId();
    // n/a

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::id_t
CxProcess::_currentParentId_impl()
{
    id_t ulRv;

    #if xCOMPILER_MINGW || xCOMPILER_CODEGEAR
        // typedef __success(return >= 0) LONG NTSTATUS;
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

    const id_t invalidId = (DWORD)- 1;

    CxDll dll;

    dll.load(xT("ntdll.dll"));

    bool_t bRv = dll.isProcExists(xT("NtQueryInformationProcess"));
    xCHECK_RET(!bRv, invalidId);

#if xARCH_BITS_32
    const PROCESSINFOCLASS    infoClass             = ProcessBasicInformation;
#else
    const PROCESSINFOCLASS    infoClass             = ProcessWow64Information;
#endif
    ULONG                     processInformation[6] = {0};
    DWORD                     returnSizeBytes       = 0UL;
    Dll_NtQueryInformationProcess_t
    DllNtQueryInformationProcess = (Dll_NtQueryInformationProcess_t)
        dll.procAddress(xT("NtQueryInformationProcess"));
    xTEST_PTR(DllNtQueryInformationProcess);

    // TODO: ProcessBasicInformation (for x64)
    NTSTATUS ntsRv = DllNtQueryInformationProcess(currentHandle(), infoClass, &processInformation,
        sizeof(processInformation), &returnSizeBytes);
    xTEST_EQ(NT_SUCCESS(ntsRv), true);
    xTEST_EQ(size_t(returnSizeBytes), sizeof(processInformation));

    ulRv = processInformation[5];

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::handle_t
CxProcess::_currentHandle_impl()
{
    // n/a

    handle_t hRv = ::GetCurrentProcess();
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxProcess::_currentExit_impl(
    cuint_t &a_exitCode
)
{
    (void_t)::ExitProcess(a_exitCode);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
