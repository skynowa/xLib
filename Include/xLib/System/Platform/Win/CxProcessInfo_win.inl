/**
 * \file   CxProcessInfo.inl
 * \brief  process information
 */


xNAMESPACE_BEGIN2(xlib, system)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::_cpuUsage_impl() const
{
    ulong_t ulRv = 0UL;

    // TODO: CxProcessInfo::cpuUsage()
    xNOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::_ramUsage_impl() const
{
    ulong_t ulRv = 0UL;

    // TODO: CxProcessInfo::ramUsage()
    xNOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::_ioBytes_impl() const
{
    ulong_t ulRv = 0UL;

    // TODO: CxProcessInfo::ioBytes()
    xNOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxProcessInfo::_exeName_impl() const
{
    std::tstring_t sRv;
    sRv.resize(xPATH_MAX);

    CxProcess::handle_t handle = CxProcess::handleById(_id);

    DWORD stored = ::GetModuleFileNameEx(handle, xPTR_NULL, &sRv.at(0), static_cast<DWORD>(sRv.size()));
    xTEST_DIFF(stored, 0UL);

    sRv.resize(stored);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::_parentId_impl() const
{
    ulong_t ulRv = 0UL;

    // TODO: CxProcessInfo::parentId()
    xNOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxProcessInfo::_commandLine_impl(
    std::vec_tstring_t *a_args
) const
{
    std::string        sRv;
    std::vec_tstring_t args;

    // process with PID 4
    {
        // System process for WinXP and later is PID 4 and we cannot access
        // PEB, but we know it is aka ntoskrnl.exe so we will manually define it.
        // ntkrnlpa.exe if Physical Address Extension (PAE)
        // ntkrnlmp.exe if Symmetric MultiProcessing (SMP)
        // Actual filename is ntoskrnl.exe, but other name will be in
        // Original Filename field of version block.

        const CxProcess::id_t ntoskrnlId = 4UL;  // MAGIC: ntoskrnlId

        if (_id == ntoskrnlId) {
            sRv = CxEnvironment::expandStrings(xT("%SystemRoot%\\System32\\ntoskrnl.exe"));
            CxString::split(sRv, CxConst::space(), &args);

            // out
            a_args->swap(args);

            return;
        }
    }

#if xCOMPILER_MINGW || xCOMPILER_CODEGEAR
    // typedef __success(return >= 0) LONG NTSTATUS;
    typedef LONG NTSTATUS;

    enum PROCESSINFOCLASS
        // process info type
    {
        ProcessBasicInformation = 0,
        ProcessWow64Information = 26
    };
#endif

    typedef NTSTATUS (WINAPI *func_t) (HANDLE ProcessHandle,
        PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation,
        ULONG ProcessInformationLength, PULONG ReturnLength);

    struct _Functor
    {
        static PVOID
        pebAddress(
            HANDLE a_process
        )
        {
            CxDll dll;

            dll.load(xT("ntdll.dll"));

            bool_t bRv = dll.isProcExists(xT("NtQueryInformationProcess"));
            xTEST_EQ(Rv, true);

            func_t func = (func_t)dll.procAddress(xT("NtQueryInformationProcess"));
            xTEST_PTR(func);

        #if xARCH_BITS_32
            const PROCESSINFOCLASS    info            = ProcessBasicInformation;
        #else
            const PROCESSINFOCLASS    info            = ProcessWow64Information;
        #endif
            PROCESS_BASIC_INFORMATION basicInfo       = {0};
            const DWORD               basicInfoSize   = sizeof(basicInfo);   // in bytes
            DWORD                     returnSizeBytes = 0UL;

            // TODO: ProcessBasicInformation (for x64)
            NTSTATUS nsRv = func(a_process, info, &basicInfo, basicInfoSize, &returnSizeBytes);
            xTEST_EQ(NT_SUCCESS(nsRv), true);
            xTEST_EQ(basicInfoSize, returnSizeBytes);
            xTEST_PTR(basicInfo.PebBaseAddress);

            PVOID pvRv = basicInfo.PebBaseAddress;

            return pvRv;
        }
    };


    CxHandle processHandle;

    processHandle = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE,
        static_cast<DWORD>( _id ));
    xTEST_EQ(processHandle.isValid(), true);

    PVOID pebAddress               = _Functor::pebAddress(processHandle.get());
    PVOID rtlUserProcParamsAddress = xPTR_NULL;

    // get the address of ProcessParameters
    BOOL blRv = ::ReadProcessMemory(processHandle.get(), static_cast<PCHAR>(pebAddress) + 0x10,
        &rtlUserProcParamsAddress, sizeof(PVOID), xPTR_NULL);
    xTEST_DIFF(blRv, FALSE);

    // read the commandLine UNICODE_STRING structure
    UNICODE_STRING commandLine = {0};

    blRv = ::ReadProcessMemory(processHandle.get(), static_cast<PCHAR>(rtlUserProcParamsAddress) +
        0x40, &commandLine, sizeof(commandLine), xPTR_NULL);
    xTEST_DIFF(blRv, FALSE);

    // allocate memory to hold the command line
    {
        WCHAR *commandLineContents = static_cast<WCHAR *>( ::malloc(commandLine.Length) );
        xTEST_PTR(commandLineContents);

        // read the command line
        blRv = ::ReadProcessMemory(processHandle.get(), commandLine.Buffer, commandLineContents,
            commandLine.Length, xPTR_NULL);
        xTEST_DIFF(blRv, FALSE);

        // length specifier is in characters, but commandLine.Length is in bytes a WCHAR is 2 bytes
        std::wstring wsRv;
        wsRv.assign(commandLineContents, commandLine.Length / 2);

    #if xUNICODE
        sRv = wsRv;
    #else
        sRv = CxString::castA(wsRv, CP_ACP);
    #endif

        (void_t)::free(commandLineContents); commandLineContents = xPTR_NULL;
    }

    CxString::split(sRv, CxConst::space(), &args);

    // out
    a_args->swap(args);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline long_t
CxProcessInfo::_commandLineArgsMax_impl()
{
    return 32L * 1024L;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
