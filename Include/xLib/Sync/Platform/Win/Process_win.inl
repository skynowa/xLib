/**
 * \file  Process.inl
 * \brief process
 */


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Process::_dtor_impl()
{
    BOOL blRv = FALSE;

    blRv = ::CloseHandle(_thread);
    xTEST_DIFF(blRv, FALSE);

    blRv = ::CloseHandle(_handle);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
void_t
Process::_create_impl(
    std::ctstring_t                     &a_filePath,  ///< file path
    std::cvec_tstring_t                 &a_params,    ///< cmd paramas
    const std::set<std::pair_tstring_t> &a_envs,      ///< env variables
    std::tstring_t                      *out_stdOut,  ///< [out] std::cout (maybe as nullptr)
    std::tstring_t                      *out_stdError ///< [out] std::cerr (maybe as nullptr)
)
{
	// TODO: out_stdOut, out_stdError - impl
	xUNUSED(out_stdOut);
	xUNUSED(out_stdError);

	std::ctstring_t params = String::join(a_params, xT(" "));

    STARTUPINFO startupInfo {};
    startupInfo.cb = sizeof(startupInfo);

    PROCESS_INFORMATION processInfo {};

	std::vector<char *> envs;
	{
		for (const auto &[it_var, it_value]  : a_envs) {
			std::ctstring_t &envVarValue = it_var + Const::equal() + it_value;
			envs.push_back( const_cast<tchar_t *>(envVarValue.c_str()) );
		}

		if ( !envs.empty() ) {
			envs.push_back(nullptr);
		}
	}

	auto environment = (LPVOID)envs.data();

    BOOL blRv = ::CreateProcess(a_filePath.c_str(), const_cast<LPTSTR>( params.c_str() ),
        nullptr, nullptr, FALSE, NORMAL_PRIORITY_CLASS, environment, nullptr, &startupInfo,
        &processInfo);
    xTEST_DIFF(blRv, FALSE);

    _handle = processInfo.hProcess;
    _thread = processInfo.hThread;
    _pid    = processInfo.dwProcessId;

    // TODO: out_stdOut, out_stdError - impl
}
//-------------------------------------------------------------------------------------------------
Process::WaitStatus
Process::_wait_impl(
    culong_t &a_timeoutMsec
)
{
    WaitStatus waitStatus = WaitStatus::Failed;

    DWORD dwRv = ::WaitForSingleObject(_handle, a_timeoutMsec);
    xTEST_EQ(dwRv, WAIT_OBJECT_0);

    waitStatus = static_cast<WaitStatus>( dwRv );

    return waitStatus;
}
//-------------------------------------------------------------------------------------------------
void_t
Process::_kill_impl(
    culong_t &a_timeoutMsec
)
{
    xTEST_DIFF(_handle, xNATIVE_HANDLE_NULL);
    xTEST_NA(a_timeoutMsec);

   /**
    * TODO: [skynowa] Process::_kill_impl()
    *
    * I would attempt to close a (Process with) Window(s) in the following order:
    *
    * - WM_CLOSE
    * - WM_QUIT
    * - WM_DESTROY
    * - TerminateProcess()
    */

    _exitStatus = 0U;

    BOOL blRv = ::TerminateProcess(_handle, _exitStatus);
    xTEST_DIFF(blRv, FALSE);

    for ( ; ; ) {
        xCHECK_DO(!isExists(), break);

        ThreadCurrent::currentSleep(a_timeoutMsec);
    }
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Process::_name_impl() const
{
    std::ctstring_t sRv = Path::exe().fileBaseName();

    return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Process::_setName_impl(
	std::ctstring_t &a_name
) const
{
	xUNUSED(a_name);

	xTRACE_OS_NOT_SUPPORTED
}
//-------------------------------------------------------------------------------------------------
bool_t
Process::_isExists_impl() const
{
	cbool_t bRv = (exitStatus() == STILL_ACTIVE);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
Process::_exitStatus_impl() const
{
    ulong_t ulRv {};

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
Process::id_t
Process::_idByHandle_impl(
    const handle_t &a_handle    ///< handle
)
{
    id_t ulRv = ::GetProcessId(a_handle);
    xTEST_NA(ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
Process::handle_t
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
Process::id_t
Process::_idByName_impl(
    std::ctstring_t &a_processName
)
{
    id_t ulRv {};

    HandleNativeInvalid snapshot;

    PROCESSENTRY32 processEntry {};
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0UL);
    xTEST(snapshot.isValid());

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
void_t
Process::_ids_impl(
    std::vector<Process::id_t> *a_ids
)
{
    std::vector<id_t> vidRv;

    HandleNativeInvalid snapshot;

    PROCESSENTRY32 processEntry {};
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0UL);
    xTEST(snapshot.isValid());

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
bool_t
Process::_isCurrent_impl(
    const Process::id_t &a_id
)
{
    bool_t bRv = (currentId() == a_id);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
Process::id_t
Process::_currentId_impl()
{
    id_t ulRv = ::GetCurrentProcessId();
    // n/a

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
Process::id_t
Process::_currentParentId_impl()
{
    id_t ulRv;

#if xCOMPILER_MINGW
	// using NTSTATUS = __success(return >= 0) LONG;
	using NTSTATUS = LONG;

	enum class PROCESSINFOCLASS
		/// process info type
	{
		ProcessBasicInformation = 0,
		ProcessWow64Information = 26
	};
#endif

    using func_t = xFUNC_PTR(NTSTATUS,
        HANDLE           ProcessHandle,
        PROCESSINFOCLASS ProcessInformationClass,
        PVOID            ProcessInformation,
        ULONG            ProcessInformationLength,
        PULONG           ReturnLength);

    const id_t invalidId = (DWORD)- 1;

    Dll dll(xT("ntdll.dll"));
    dll.load();
    xCHECK_RET(!dll, invalidId);

#if xARCH_BITS_32
    const PROCESSINFOCLASS    infoClass             = ProcessBasicInformation;
#else
    const PROCESSINFOCLASS    infoClass             = ProcessWow64Information;
#endif
    ULONG                     processInformation[6] {};
    DWORD                     returnSizeBytes       {};

    auto func = dll.symbol<func_t>(xT("NtQueryInformationProcess"));
    xTEST_PTR(func);

    // TODO: [skynowa] ProcessBasicInformation (for x64)
    NTSTATUS ntsRv = func(currentHandle(), infoClass, &processInformation,
        sizeof(processInformation), &returnSizeBytes);
    xTEST(NT_SUCCESS(ntsRv));
    xTEST_EQ(size_t(returnSizeBytes), sizeof(processInformation));

    ulRv = processInformation[5];

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
Process::handle_t
Process::_currentHandle_impl()
{
    // n/a

    handle_t hRv = ::GetCurrentProcess();
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Process::_currentExit_impl(
    cuint_t &a_exitCode
)
{
    (void_t)::ExitProcess(a_exitCode);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Process::_shellExecute_impl(
    std::ctstring_t &a_filePathOrURL, ///< full file path or URL
	std::ctstring_t &a_params         ///< command line params
)
{
	BOOL blRv {};

	HRESULT hrRv = ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	xTEST(hrRv == S_OK);

	ScopeExit on_exit( [&]() { ::CoUninitialize(); } );

	SHELLEXECUTEINFO execInfo {};
	execInfo.cbSize       = sizeof(SHELLEXECUTEINFO);
	execInfo.fMask        = SEE_MASK_NOCLOSEPROCESS;
	execInfo.hwnd         = nullptr;
	execInfo.lpVerb       = xT("open");
	execInfo.lpFile       = a_filePathOrURL.c_str();
	execInfo.lpParameters = a_params.c_str();
	execInfo.lpDirectory  = nullptr;
	execInfo.nShow        = SW_SHOWNORMAL;
	execInfo.hInstApp     = nullptr;

	blRv = ::ShellExecuteEx(&execInfo);
	xTEST_EQ(blRv, TRUE);
	xTEST_PTR(execInfo.hProcess);

	DWORD dwRv = ::WaitForSingleObject(execInfo.hProcess, xTIMEOUT_INFINITE);
	xTEST_EQ(dwRv, WAIT_OBJECT_0);

	blRv = ::CloseHandle(execInfo.hProcess);
	xTEST_EQ(blRv, TRUE);
}
//-------------------------------------------------------------------------------------------------

} // namespace
