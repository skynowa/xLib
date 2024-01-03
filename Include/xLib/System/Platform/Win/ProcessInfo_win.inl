/**
 * \file   ProcessInfo.inl
 * \brief  process information
 */


namespace xl::system
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
ulong_t
ProcessInfo::_cpuUsage_impl() const
{
    ulong_t ulRv {};

    // TODO: [skynowa] ProcessInfo::cpuUsage()
    xTRACE_NOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
ProcessInfo::_ramUsage_impl() const
{
    ulong_t ulRv {};

    // TODO: [skynowa] ProcessInfo::ramUsage()
    xTRACE_NOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
ProcessInfo::_ioBytes_impl() const
{
    ulong_t ulRv {};

    // TODO: [skynowa] ProcessInfo::ioBytes()
    xTRACE_NOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
ProcessInfo::_exeName_impl() const
{
    std::tstring_t sRv(Path::maxSize() + 1, {});

    Process::handle_t handle = Process::handleById(_id);

    DWORD stored = ::GetModuleFileNameEx(handle, nullptr, &sRv.at(0), static_cast<DWORD>(sRv.size()));
    xTEST_DIFF(stored, 0UL);

    sRv.resize(stored);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
ProcessInfo::_parentId_impl() const
{
    ulong_t ulRv {};

    // TODO: [skynowa] ProcessInfo::parentId()
    xTRACE_NOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
ProcessInfo::_commandLine_impl(
    std::vec_tstring_t *out_args
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

        const Process::id_t ntoskrnlId {4UL};  // MAGIC: ntoskrnlId

        if (_id == ntoskrnlId) {
            sRv = Environment::expandVars(xT("%SystemRoot%\\System32\\ntoskrnl.exe"));
            String::split(sRv, Const::space(), &args);

            // out
            out_args->swap(args);

            return;
        }
    }

#if xCOMPILER_MINGW
    // using NTSTATUS = __success(return >= 0) LONG;
    using NTSTATUS = LONG ;

    enum class PROCESSINFOCLASS
        // process info type
    {
        ProcessBasicInformation = 0,
        ProcessWow64Information = 26
    };
#endif

    using func_t = NTSTATUS (WINAPI *) (HANDLE ProcessHandle,
        PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation,
        ULONG ProcessInformationLength, PULONG ReturnLength);

    struct _Functor
    {
        static PVOID
        pebAddress(
            HANDLE a_process
        )
        {
            Dll dll;

            dll.load(xT("ntdll.dll"));

            bool_t bRv = dll.isProcExists(xT("NtQueryInformationProcess"));
            xTEST(bRv);

            func_t func = (func_t)dll.procAddress(xT("NtQueryInformationProcess"));
            xTEST_PTR(func);

        #if xARCH_BITS_32
            const PROCESSINFOCLASS    info            = ProcessBasicInformation;
        #else
            const PROCESSINFOCLASS    info            = ProcessWow64Information;
        #endif
            PROCESS_BASIC_INFORMATION basicInfo       {};
            const DWORD               basicInfoSize   { sizeof(basicInfo) };   // in bytes
            DWORD                     returnSizeBytes {};

            // TODO: [skynowa] ProcessBasicInformation (for x64)
            NTSTATUS nsRv = func(a_process, info, &basicInfo, basicInfoSize, &returnSizeBytes);
            xTEST(NT_SUCCESS(nsRv));
            xTEST_EQ(basicInfoSize, returnSizeBytes);
            xTEST_PTR(basicInfo.PebBaseAddress);

            PVOID pvRv = basicInfo.PebBaseAddress;

            return pvRv;
        }
    };


    HandleNative processHandle;

    processHandle = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE,
        static_cast<DWORD>( _id ));
    xTEST(processHandle.isValid());

    PVOID pebAddress               = _Functor::pebAddress(processHandle.get());
    PVOID rtlUserProcParamsAddress {};

    // get the address of ProcessParameters
    BOOL blRv = ::ReadProcessMemory(processHandle.get(), static_cast<PCHAR>(pebAddress) + 0x10,
        &rtlUserProcParamsAddress, sizeof(PVOID), nullptr);
    xTEST_DIFF(blRv, FALSE);

    // read the commandLine UNICODE_STRING structure
    UNICODE_STRING commandLine {};

    blRv = ::ReadProcessMemory(processHandle.get(), static_cast<PCHAR>(rtlUserProcParamsAddress) +
        0x40, &commandLine, sizeof(commandLine), nullptr);
    xTEST_DIFF(blRv, FALSE);

    // allocate memory to hold the command line
    {
        WCHAR *commandLineContents = static_cast<WCHAR *>( ::malloc(commandLine.Length) );
        xTEST_PTR(commandLineContents);

        // read the command line
        blRv = ::ReadProcessMemory(processHandle.get(), commandLine.Buffer, commandLineContents,
            commandLine.Length, nullptr);
        xTEST_DIFF(blRv, FALSE);

        // length specifier is in characters, but commandLine.Length is in bytes a WCHAR is 2 bytes
        std::wstring wsRv;
        wsRv.assign(commandLineContents, commandLine.Length / 2);

    #if xUNICODE
        sRv = wsRv;
    #else
        sRv = String::castA(wsRv, CP_ACP);
    #endif

        (void_t)::free(commandLineContents); commandLineContents = nullptr;
    }

    String::split(sRv, Const::space(), &args);

    // out
    out_args->swap(args);
}
//-------------------------------------------------------------------------------------------------
/* static */
long_t
ProcessInfo::_commandLineArgsMax_impl()
{
    return {32L * 1024L};
}
//-------------------------------------------------------------------------------------------------

} // namespace
