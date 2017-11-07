/**
 * \file  Process.inl
 * \brief process
 */


xNAMESPACE_BEGIN2(xl, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
Process::_destruct_impl()
{
    BOOL blRv = FALSE;

    blRv = ::CloseHandle(_thread);
    xTEST_DIFF(blRv, FALSE);

    blRv = ::CloseHandle(_handle);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Process::_create_impl(
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
xINLINE Process::WaitResult
Process::_wait_impl(
    culong_t &a_timeoutMsec
)
{
    WaitResult waitStatus = wrFailed;

    DWORD dwRv = ::WaitForSingleObject(_handle, a_timeoutMsec);
    xTEST_EQ(dwRv, WAIT_OBJECT_0);

    waitStatus = static_cast<WaitResult>( dwRv );

    return waitStatus;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Process::_kill_impl(
    culong_t &a_timeoutMsec
)
{
    xTEST_DIFF(_handle, xNATIVE_HANDLE_NULL);
    xTEST_NA(a_timeoutMsec);

#if 0
    // TODO: Process::_kill_impl()
    I would attempt to close a (Process with) Window(s) in the following order:
        WM_CLOSE
        WM_QUIT
        WM_DESTROY
        TerminateProcess().
#endif

    _exitStatus = 0U;

    BOOL blRv = ::TerminateProcess(_handle, _exitStatus);
    xTEST_DIFF(blRv, FALSE);

    for ( ; ; ) {
        xCHECK_DO(exitStatus() != STILL_ACTIVE, break);

        Thread::currentSleep(a_timeoutMsec);
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
Process::_exitStatus_impl() const
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
xINLINE Process::id_t
Process::_idByHandle_impl(
    const handle_t &a_handle    ///< handle
)
{
    id_t ulRv = ::GetProcessId(a_handle);
    xTEST_NA(ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE Process::handle_t
Process::_handleById_impl(
    const id_t &a_id   ///< ID
)
{
    handle_t hRv = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, a_id);
    xTEST_NA(hRv);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE
Process::id_t
Process::_idByName_impl(
    std::ctstring_t &a_processName
)
{
    id_t ulRv;

    Handle       snapshot;
    PROCESSENTRY32 processEntry = {0};
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0UL);
    xTEST_EQ(snapshot.isValid(), true);

    BOOL blRv = ::Process32First(snapshot.get(), &processEntry);
    xTEST_DIFF(blRv, FALSE);

    for ( ; ; ) {
        bool_t bRv = StringCI::compare(a_processName, processEntry.szExeFile);
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
xINLINE void_t
Process::_ids_impl(
    std::vector<Process::id_t> *a_ids
)
{
    std::vector<id_t> vidRv;

    Handle       snapshot;
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
xINLINE bool_t
Process::_isCurrent_impl(
    const Process::id_t &a_id
)
{
    bool_t bRv = (currentId() == a_id);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE Process::id_t
Process::_currentId_impl()
{
    id_t ulRv = ::GetCurrentProcessId();
    // n/a

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE Process::id_t
Process::_currentParentId_impl()
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

    Dll dll;

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
xINLINE Process::handle_t
Process::_currentHandle_impl()
{
    // n/a

    handle_t hRv = ::GetCurrentProcess();
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Process::_currentExit_impl(
    cuint_t &a_exitCode
)
{
    (void_t)::ExitProcess(a_exitCode);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
