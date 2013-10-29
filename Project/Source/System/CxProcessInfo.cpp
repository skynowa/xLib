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

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxProcessInfo::setProcessId(
    const CxProcess::id_t &a_id
)
{
    _id = a_id;
}
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
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

    std::tstring_t sProcPath  = CxString::format(xT("/proc/%lu/io"), _id);

    ulong_t ulReadBytes = 0UL;
    {
        std::tstring_t sValue = CxPath::procValue(sProcPath, xT("read_bytes"));

        ulReadBytes = CxString::cast<ulong_t>( sValue );
    }

    ulong_t ulWriteBytes = 0UL;
    {
        std::tstring_t sValue = CxPath::procValue(sProcPath, xT("write_bytes"));

        ulWriteBytes = CxString::cast<ulong_t>( sValue );
    }

    ulRv = ulReadBytes + ulWriteBytes;

    // xTRACEV("\tulReadBytes: %lu, ulWriteBytes: %lu", ulReadBytes, ulWriteBytes);
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return ulRv;
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxProcessInfo::exeName()
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    sRv.resize(xPATH_MAX);

    CxProcess::handle_t hHandle = CxProcess::handleById(_id);

    DWORD dwStored = ::GetModuleFileNameEx(hHandle, NULL, &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(0UL, dwStored);

    sRv.resize(dwStored);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        std::ctstring_t csProcFile = CxString::format(xT("/proc/%ld/exe"), _id);

        bool_t bRv = CxFile::isExists(csProcFile);
        xCHECK_RET(!bRv, std::tstring_t());

        int_t iReaded = - 1;
        sRv.resize(xPATH_MAX);

        xFOREVER {
            iReaded = ::readlink(csProcFile.c_str(), &sRv.at(0), sRv.size() * sizeof(std::tstring_t::value_type));
            xTEST_DIFF(- 1, iReaded);

            xCHECK_DO(sRv.size() * sizeof(std::tstring_t::value_type) > static_cast<size_t>( iReaded ), break);

            sRv.resize(sRv.size() * 2);
        }

        sRv.resize(iReaded);
    #elif xOS_FREEBSD
        #if defined(KERN_PROC_PATHNAME)
            int_t aiMib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, _id};

            tchar_t szBuff[PATH_MAX + 1] = {0};
            size_t  uiBuffSize           = sizeof(szBuff) - 1;

            int_t iRv = ::sysctl(aiMib, xARRAY_SIZE(aiMib), szBuff, &uiBuffSize, NULL, 0U);
            xTEST_DIFF(- 1, iRv);

            sRv.assign(szBuff);
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
//-------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxProcessInfo::commandLine(
    std::vec_tstring_t *a_args
)
{
    xTEST_PTR(a_args);

    std::string sRv;

#if   xOS_ENV_WIN
    // process with PID 4
    {
        // System process for WinXP and later is PID 4 and we cannot access
        // PEB, but we know it is aka ntoskrnl.exe so we will manually define it.
        // ntkrnlpa.exe if Physical Address Extension (PAE)
        // ntkrnlmp.exe if Symmetric MultiProcessing (SMP)
        // Actual filename is ntoskrnl.exe, but other name will be in
        // Original Filename field of version block.

        const CxProcess::id_t cidNtoskrnlId = 4UL;  // MAGIC: cidNtoskrnlId

        if (cidNtoskrnlId == _id) {
            sRv = CxEnvironment::expandStrings(xT("%SystemRoot%\\System32\\ntoskrnl.exe"));

            CxString::split(sRv, CxConst::xSPACE(), &args);
            a_args.swap(args);

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

    struct _SNested {
        static
        PVOID
        pvPebAddress(
            HANDLE hProcessHandle
        )
        {
            CxDll dlDll;

            dlDll.load(xT("ntdll.dll"));

            bool_t bRv = dlDll.isProcExists(xT("NtQueryInformationProcess"));
            xTEST_EQ(true, bRv);

            Dll_NtQueryInformationProcess_t
            DllNtQueryInformationProcess = (Dll_NtQueryInformationProcess_t)dlDll.procAddress(xT("NtQueryInformationProcess"));
            xTEST_PTR(DllNtQueryInformationProcess);

        #if xARCH_X86
            const PROCESSINFOCLASS    cpicInfo          = ProcessBasicInformation;
        #else
            const PROCESSINFOCLASS    cpicInfo          = ProcessWow64Information;
        #endif
            PROCESS_BASIC_INFORMATION pbiBasicInfo      = {0};
            const DWORD               cdwBasicInfoSize  = sizeof(pbiBasicInfo);   // in bytes
            DWORD                     dwReturnSizeBytes = 0UL;

            // TODO: ProcessBasicInformation (for x64)
            NTSTATUS nsRv = DllNtQueryInformationProcess(hProcessHandle,
                                                         cpicInfo,
                                                         &pbiBasicInfo, cdwBasicInfoSize, &dwReturnSizeBytes);
            xTEST_EQ(true, NT_SUCCESS(nsRv));
            xTEST_EQ(cdwBasicInfoSize, dwReturnSizeBytes);
            xTEST_PTR(pbiBasicInfo.PebBaseAddress);

            PVOID pvRv = pbiBasicInfo.PebBaseAddress;

            return pvRv;
        }
    };


    CxHandle processHandle;

    processHandle = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, static_cast<DWORD>( _id ));
    xTEST_EQ(true, processHandle.isValid());

    PVOID pebAddress               = _SNested::pvPebAddress(processHandle.get());
    PVOID rtlUserProcParamsAddress = NULL;

    // get the address of ProcessParameters
    BOOL blRv = ::ReadProcessMemory(processHandle.get(), static_cast<PCHAR>(pebAddress) + 0x10,  &rtlUserProcParamsAddress, sizeof(PVOID), NULL);
    xTEST_DIFF(FALSE, blRv);

    // read the usCommandLine UNICODE_STRING structure
    UNICODE_STRING usCommandLine = {0};

    blRv = ::ReadProcessMemory(processHandle.get(), static_cast<PCHAR>(rtlUserProcParamsAddress) + 0x40, &usCommandLine, sizeof(usCommandLine), NULL);
    xTEST_DIFF(FALSE, blRv);

    // allocate memory to hold the command line
    {
        WCHAR *pCommandLineContents = static_cast<WCHAR *>( ::malloc(usCommandLine.Length) );
        xTEST_PTR(pCommandLineContents);

        // read the command line
        blRv = ::ReadProcessMemory(processHandle.get(), usCommandLine.Buffer, pCommandLineContents, usCommandLine.Length, NULL);
        xTEST_DIFF(FALSE, blRv);

        // length specifier is in characters, but usCommandLine.Length is in bytes a WCHAR is 2 bytes
        std::wstring wsRv;
        wsRv.assign(pCommandLineContents, usCommandLine.Length / 2);

    #if xUNICODE
        sRv = wsRv;
    #else
        sRv = CxString::wstrToStr(wsRv, CP_ACP);
    #endif

        (void_t)::free(pCommandLineContents); pCommandLineContents = NULL;
    }
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // FIX: content of "/proc/%ld/cmdline" - missing spaces
        std::ctstring_t csProcFile = CxString::format(xT("/proc/%ld/cmdline"), _id);

        std::vec_tstring_t vsProcFile;

        CxPath::proc(csProcFile, &vsProcFile);
        xTEST_EQ(size_t(1), vsProcFile.size())

        sRv = vsProcFile.at(0);
    #elif xOS_FREEBSD
        int_t iRv      = - 1;
        int_t aiMib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ARGS, _id};

        std::string sBuff;
        size_t      uiBuffSize = 0;

        // get uiBuffSize
        iRv = ::sysctl(aiMib, xARRAY_SIZE(aiMib), NULL,         &uiBuffSize, NULL, 0);
        xTEST_DIFF(- 1, iRv);

        sBuff.resize(uiBuffSize);

        iRv = ::sysctl(aiMib, xARRAY_SIZE(aiMib), &sBuff.at(0), &uiBuffSize, NULL, 0U);
        xTEST_DIFF(- 1, iRv);

        sRv = sBuff;    // BUG: sBuff or sBuff.c_str() - FreeBSD crazy!!!
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

#if xTEMP_DISABLED
    #if xOS_ENV_WIN
        LPCTSTR pcszRes = ::GetCommandLine();
        xTEST_PTR(pcszRes);

        sRv = CxString::trimSpace(pcszRes);
    #else
        sRv = CxString::join(_args, CxConst::xSPACE());
    #endif
#endif

    std::vec_tstring_t args;
    CxString::split(sRv, CxConst::xSPACE(), &args);

    // out
    a_args->swap(args);
}
//-------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
