/**
 * \file   CxProcessInfo.cpp
 * \brief
 */


#include <xLib/System/CxProcessInfo.h>

#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxDll.h>
#include <xLib/Filesystem/CxFinder.h>
#include <xLib/System/CxEnvironment.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxProcessInfo::setProcessId(
    const CxProcess::id_t &a_id
)
{
    _id = a_id;
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO ulong_t
CxProcessInfo::cpuUsage()
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    // TODO: CxProcessInfo::cpuUsage
#elif xOS_ENV_UNIX
    // TODO: CxProcessInfo::cpuUsage
#elif xOS_ENV_MAC
    // TODO: CxProcessInfo::cpuUsage
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO ulong_t
CxProcessInfo::ramUsage()
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    // TODO: CxProcessInfo::ramUsage
#elif xOS_ENV_UNIX
    // TODO: CxProcessInfo::ramUsage
#elif xOS_ENV_MAC
    // TODO: CxProcessInfo::ramUsage
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO ulong_t
CxProcessInfo::ioBytes()
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    // TODO: CxProcessInfo::ulIOBytes
#elif xOS_ENV_UNIX
    #if xCOMMENT
        "/proc/[pid]/io"

        1366    rchar: 323934931
        1367    wchar: 323929600
        1368    syscr: 632687
        1369    syscw: 632675
        1370    read_bytes: 0
        1371    write_bytes: 323932160
        1372    cancelled_write_bytes: 0
    #endif

    std::tstring_t procPath  = CxString::format(xT("/proc/%lu/io"), _id);

    ulong_t readBytes = 0UL;
    {
        std::tstring_t value = CxPath::procValue(procPath, xT("read_bytes"));

        readBytes = CxString::cast<ulong_t>( value );
    }

    ulong_t writeBytes = 0UL;
    {
        std::tstring_t value = CxPath::procValue(procPath, xT("write_bytes"));

        writeBytes = CxString::cast<ulong_t>( value );
    }

    ulRv = readBytes + writeBytes;

    // xTRACEV("\tulReadBytes: %lu, writeBytes: %lu", readBytes, writeBytes);
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxProcessInfo::exeName()
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    sRv.resize(xPATH_MAX);

    CxProcess::handle_t handle = CxProcess::handleById(_id);

    DWORD stored = ::GetModuleFileNameEx(handle, NULL, &sRv.at(0),
        static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(0UL, stored);

    sRv.resize(stored);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        std::ctstring_t procFile = CxString::format(xT("/proc/%ld/exe"), _id);

        bool_t bRv = CxFile::isExists(procFile);
        xCHECK_RET(!bRv, std::tstring_t());

        int_t readed = - 1;
        sRv.resize(xPATH_MAX);

        xFOREVER {
            readed = ::readlink(procFile.c_str(), &sRv.at(0), sRv.size() *
                sizeof(std::tstring_t::value_type));
            xTEST_DIFF(- 1, readed);

            xCHECK_DO(sRv.size() * sizeof(std::tstring_t::value_type) >
                static_cast<size_t>( readed ), break);

            sRv.resize(sRv.size() * 2);
        }

        sRv.resize(readed);
    #elif xOS_FREEBSD
        #if defined(KERN_PROC_PATHNAME)
            int_t   mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, _id};

            tchar_t buff[PATH_MAX + 1] = {0};
            size_t  buffSize           = sizeof(buff) - 1;

            int_t iRv = ::sysctl(mib, xARRAY_SIZE(mib), buff, &buffSize, NULL, 0U);
            xTEST_DIFF(- 1, iRv);

            sRv.assign(buff);
        #else
            // TODO: CxProcessInfo::sGetExeName
            xNOT_IMPLEMENTED_RET(std::tstring_t());
        #endif
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO ulong_t
CxProcessInfo::parentId()
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    // TODO: CxProcessInfo::ulParentProcessId
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // TODO: CxProcessInfo::ulParentProcessId
    #elif xOS_FREEBSD
        // TODO: CxProcessInfo::ulParentProcessId
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxProcessInfo::commandLine(
    std::vec_tstring_t *a_args
)
{
    xTEST_PTR(a_args);

    std::string        sRv;
    std::vec_tstring_t args;

#if   xOS_ENV_WIN
    // process with PID 4
    {
        // System process for WinXP and later is PID 4 and we cannot access
        // PEB, but we know it is aka ntoskrnl.exe so we will manually define it.
        // ntkrnlpa.exe if Physical Address Extension (PAE)
        // ntkrnlmp.exe if Symmetric MultiProcessing (SMP)
        // Actual filename is ntoskrnl.exe, but other name will be in
        // Original Filename field of version block.

        const CxProcess::id_t ntoskrnlId = 4UL;  // MAGIC: ntoskrnlId

        if (ntoskrnlId == _id) {
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

    struct _SFunctor
    {
        static PVOID
        pebAddress(
            HANDLE a_process
        )
        {
            CxDll dll;

            dll.load(xT("ntdll.dll"));

            bool_t bRv = dll.isProcExists(xT("NtQueryInformationProcess"));
            xTEST_EQ(true, bRv);

            Dll_NtQueryInformationProcess_t
            DllNtQueryInformationProcess = (Dll_NtQueryInformationProcess_t)
                dll.procAddress(xT("NtQueryInformationProcess"));
            xTEST_PTR(DllNtQueryInformationProcess);

        #if xARCH_X86
            const PROCESSINFOCLASS    info            = ProcessBasicInformation;
        #else
            const PROCESSINFOCLASS    info            = ProcessWow64Information;
        #endif
            PROCESS_BASIC_INFORMATION basicInfo       = {0};
            const DWORD               basicInfoSize   = sizeof(basicInfo);   // in bytes
            DWORD                     returnSizeBytes = 0UL;

            // TODO: ProcessBasicInformation (for x64)
            NTSTATUS nsRv = DllNtQueryInformationProcess(a_process, info, &basicInfo,
                basicInfoSize, &returnSizeBytes);
            xTEST_EQ(true, NT_SUCCESS(nsRv));
            xTEST_EQ(basicInfoSize, returnSizeBytes);
            xTEST_PTR(basicInfo.PebBaseAddress);

            PVOID pvRv = basicInfo.PebBaseAddress;

            return pvRv;
        }
    };


    CxHandle processHandle;

    processHandle = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE,
        static_cast<DWORD>( _id ));
    xTEST_EQ(true, processHandle.isValid());

    PVOID pebAddress               = _SFunctor::pebAddress(processHandle.get());
    PVOID rtlUserProcParamsAddress = NULL;

    // get the address of ProcessParameters
    BOOL blRv = ::ReadProcessMemory(processHandle.get(), static_cast<PCHAR>(pebAddress) + 0x10,
        &rtlUserProcParamsAddress, sizeof(PVOID), NULL);
    xTEST_DIFF(FALSE, blRv);

    // read the commandLine UNICODE_STRING structure
    UNICODE_STRING commandLine = {0};

    blRv = ::ReadProcessMemory(processHandle.get(), static_cast<PCHAR>(rtlUserProcParamsAddress) +
        0x40, &commandLine, sizeof(commandLine), NULL);
    xTEST_DIFF(FALSE, blRv);

    // allocate memory to hold the command line
    {
        WCHAR *commandLineContents = static_cast<WCHAR *>( ::malloc(commandLine.Length) );
        xTEST_PTR(commandLineContents);

        // read the command line
        blRv = ::ReadProcessMemory(processHandle.get(), commandLine.Buffer, commandLineContents,
            commandLine.Length, NULL);
        xTEST_DIFF(FALSE, blRv);

        // length specifier is in characters, but commandLine.Length is in bytes a WCHAR is 2 bytes
        std::wstring wsRv;
        wsRv.assign(commandLineContents, commandLine.Length / 2);

    #if xUNICODE
        sRv = wsRv;
    #else
        sRv = CxString::wstrToStr(wsRv, CP_ACP);
    #endif

        (void_t)::free(commandLineContents); commandLineContents = NULL;
    }
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // FIX: content of "/proc/%ld/cmdline" - missing spaces
        std::ctstring_t procFile = CxString::format(xT("/proc/%ld/cmdline"), _id);

        std::vec_tstring_t vsProcFile;

        CxPath::proc(procFile, &vsProcFile);
        xTEST_EQ(size_t(1), vsProcFile.size())

        sRv = vsProcFile.at(0);
    #elif xOS_FREEBSD
        int_t iRv      = - 1;
        int_t mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ARGS, _id};

        std::string buff;
        size_t      buffSize = 0;

        // get buffSize
        iRv = ::sysctl(mib, xARRAY_SIZE(mib), NULL, &buffSize, NULL, 0);
        xTEST_DIFF(- 1, iRv);

        buff.resize(buffSize);

        iRv = ::sysctl(mib, xARRAY_SIZE(mib), &buff.at(0), &buffSize, NULL, 0U);
        xTEST_DIFF(- 1, iRv);

        sRv = buff;    // BUG: buff or buff.c_str() - FreeBSD crazy!!!
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

#if xTEMP_DISABLED
    #if xOS_ENV_WIN
        LPCTSTR pcszRv = ::GetCommandLine();
        xTEST_PTR(pcszRv);

        sRv = CxString::trimSpace(pcszRv);
    #else
        sRv = CxString::join(_args, CxConst::space());
    #endif
#endif

    CxString::split(sRv, CxConst::space(), &args);

    // out
    a_args->swap(args);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE_HO long_t
CxProcessInfo::commandLineArgsMax()
{
    long_t liRv = 0L;

#if xOS_ENV_WIN
    liRv = 32L * 1024L;
#else
    liRv = ::sysconf(_SC_ARG_MAX) / sizeof(std::tstring_t::value_type);
    xTEST_DIFF(- 1L, liRv);
#endif

    return liRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
