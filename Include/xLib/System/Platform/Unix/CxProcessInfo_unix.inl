/**
 * \file   CxProcessInfo.inl
 * \brief  process information
 */


#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxDll.h>
#include <xLib/System/CxEnvironment.h>


xNAMESPACE_BEGIN2(xlib, system)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxProcessInfo::CxProcessInfo() :
    _id(0)
{
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxProcessInfo::setProcessId(
    const CxProcess::id_t &a_id
)
{
    _id = a_id;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::cpuUsage() const
{
    ulong_t ulRv = 0UL;

#if   xENV_WIN
    // TODO: CxProcessInfo::cpuUsage()
#elif xENV_UNIX
    // TODO: CxProcessInfo::cpuUsage()
#elif xENV_APPLE
    // TODO: CxProcessInfo::cpuUsage()
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::ramUsage() const
{
    ulong_t ulRv = 0UL;

#if   xENV_WIN
    // TODO: CxProcessInfo::ramUsage()
#elif xENV_UNIX
    if (CxProcess::isCurrent( CxProcess::currentId() )) {
        // TODO: CxProcessInfo::ramUsage()
    } else {
        // TODO: CxProcessInfo::ramUsage()
    }
#elif xENV_APPLE
    // TODO: CxProcessInfo::ramUsage()
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::ioBytes() const
{
    ulong_t ulRv = 0UL;

#if   xENV_WIN
    // TODO: CxProcessInfo::ioBytes()
#elif xENV_UNIX
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

    // xTRACEV("\readBytes: %lu, writeBytes: %lu", readBytes, writeBytes);
#elif xENV_APPLE
    xNOT_IMPLEMENTED
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxProcessInfo::exeName() const
{
    std::tstring_t sRv;

#if   xENV_WIN
    sRv.resize(xPATH_MAX);

    CxProcess::handle_t handle = CxProcess::handleById(_id);

    DWORD stored = ::GetModuleFileNameEx(handle, xPTR_NULL, &sRv.at(0), static_cast<DWORD>(sRv.size()));
    xTEST_DIFF(stored, 0UL);

    sRv.resize(stored);
#elif xENV_UNIX
    #if   xOS_LINUX
        std::ctstring_t procFile = CxString::format(xT("/proc/%ld/exe"), _id);

        bool_t bRv = CxFile::isExists(procFile);
        xCHECK_RET(!bRv, std::tstring_t());

        ssize_t readed = - 1;
        sRv.resize(xPATH_MAX);

        for ( ; ; ) {
            readed = ::readlink(procFile.c_str(), &sRv.at(0), sRv.size() *
                sizeof(std::tstring_t::value_type));
            xTEST_DIFF(readed, ssize_t(- 1));

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

            int_t iRv = ::sysctl(mib, xARRAY_SIZE(mib), buff, &buffSize, xPTR_NULL, 0U);
            xTEST_DIFF(iRv, - 1);

            sRv.assign(buff);
        #else
            // TODO: CxProcessInfo::exeName()
            xNOT_IMPLEMENTED_RET(std::tstring_t());
        #endif
    #endif
#elif xENV_APPLE
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::parentId() const
{
    ulong_t ulRv = 0UL;

#if   xENV_WIN
    // TODO: CxProcessInfo::parentId()
#elif xENV_UNIX
    #if   xOS_LINUX
        // TODO: CxProcessInfo::parentId()
    #elif xOS_FREEBSD
        // TODO: CxProcessInfo::parentId()
    #endif
#elif xENV_APPLE
    xNOT_IMPLEMENTED
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxProcessInfo::commandLine(
    std::vec_tstring_t *a_args
) const
{
    xTEST_PTR(a_args);

    std::string        sRv;
    std::vec_tstring_t args;

#if   xENV_WIN
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
#elif xENV_UNIX
    #if   xOS_LINUX
        // TODO: CxProcessInfo::commandLine() - review
        std::ctstring_t procPath = CxString::format(xT("/proc/%ld/cmdline"), _id);

        FILE *procFile = std::fopen(procPath.c_str(), "r");
        xTEST_PTR(procFile);

        std::csize_t bufferSize       = 2048;
        char         buff[bufferSize] = {0};

        while ( std::fgets(buff, static_cast<int_t>(bufferSize), procFile) ) {
            size_t pos = 0;
            while (pos < bufferSize && buff[pos] != '\0' ) {
                args.push_back(buff + pos);

                pos += std::strlen(buff + pos) + 1;
            }
        }

        xFCLOSE(procFile);
    #elif xOS_FREEBSD
        int_t iRv    = - 1;
        int_t mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ARGS, _id};

        std::string buff;
        size_t      buffSize = 0;

        // get buffSize
        iRv = ::sysctl(mib, xARRAY_SIZE(mib), xPTR_NULL, &buffSize, xPTR_NULL, 0);
        xTEST_DIFF(iRv, - 1);

        buff.resize(buffSize);

        iRv = ::sysctl(mib, xARRAY_SIZE(mib), &buff.at(0), &buffSize, xPTR_NULL, 0U);
        xTEST_DIFF(iRv, - 1);

        // remove xPTR_NULL terminating symbol
        buff.resize(buffSize - 1);

        CxString::split(buff, CxConst::space(), &args);
    #endif
#elif xENV_APPLE
    xNOT_IMPLEMENTED
#endif

    // out
    a_args->swap(args);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline long_t
CxProcessInfo::commandLineArgsMax()
{
    long_t liRv = 0L;

#if   xENV_WIN
    liRv = 32L * 1024L;
#elif xENV_UNIX
    liRv = ::sysconf(_SC_ARG_MAX) / sizeof(std::tstring_t::value_type);
    xTEST_DIFF(liRv, - 1L);
#endif

    return liRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
