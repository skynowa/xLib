/**
 * \file   CxProcessInfo.cpp
 * \brief
 */


#include <xLib/Common/CxProcessInfo.h>

#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxDll.h>
#include <xLib/Filesystem/CxEnvironment.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
void
CxProcessInfo::vCurrentIds(
    std::vector<CxProcess::id_t> *a_pvidIds
)
{
    std::vector<CxProcess::id_t> vidRv;

#if   xOS_ENV_WIN
    CxHandle       hSnapshot;
    PROCESSENTRY32 peProcess = {0};    peProcess.dwSize = sizeof(PROCESSENTRY32);

    hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0UL);
    xTEST_EQ(true, hSnapshot.bIsValid());

    BOOL blRv = ::Process32First(hSnapshot.hGet(), &peProcess);
    xTEST_DIFF(FALSE, blRv);

    xFOREVER {
        DWORD dwPid = peProcess.th32ProcessID;

        vidRv.push_back(dwPid);

        blRv = ::Process32Next(hSnapshot.hGet(), &peProcess);
        xCHECK_DO(FALSE == blRv, break);
    }
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        std::vec_tstring_t a_vsDirPathes;

        CxDir::vFindDirs(xT("/proc"), CxConst::xMASK_ALL, false, &a_vsDirPathes);

        // skip non-numeric entries
        xFOREACH_CONST(std::vec_tstring_t, it, a_vsDirPathes) {
            int iPid = 0;
            {
                std::tstring_t sDirName = CxPath::sFileName(*it);

                iPid = ::atoi(sDirName.c_str());
                xCHECK_DO(0 >= iPid, continue);
            }

            vidRv.push_back( static_cast<CxProcess::id_t>( iPid ));
        }
    #elif xOS_FREEBSD
        int    aiMib[3]   = {CTL_KERN, KERN_PROC, KERN_PROC_ALL};
        size_t uiBuffSize = 0U;

        int iRv = ::sysctl(aiMib, xARRAY_SIZE(aiMib), NULL, &uiBuffSize, NULL, 0U);
        xTEST_DIFF(- 1, iRv);

        // allocate memory and populate info in the  processes structure
        kinfo_proc *pkpProcesses = NULL;

        xFOREVER {
            uiBuffSize += uiBuffSize / 10;

            kinfo_proc *pkpNewProcesses = static_cast<kinfo_proc *>( realloc(pkpProcesses, uiBuffSize) );
            xTEST_PTR(pkpNewProcesses);

            pkpProcesses = pkpNewProcesses;

            iRv = ::sysctl(aiMib, xARRAY_SIZE(aiMib), pkpProcesses, &uiBuffSize, NULL, 0U);
            xCHECK_DO(!(- 1 == iRv && errno == ENOMEM), break);
        }

        // search for the given process name and return its pid
        const size_t cuiProcsNum = uiBuffSize / sizeof(kinfo_proc);

        for (size_t i = 0; i < cuiProcsNum; ++ i) {
            pid_t iPid = pkpProcesses[i].ki_pid;

            vidRv.push_back(iPid);
        }

        xBUFF_FREE(pkpProcesses);
    #endif
#endif

    // out
    (*a_pvidIds).swap(vidRv);
}
//---------------------------------------------------------------------------
/* static */
ulong_t
CxProcessInfo::ulCpuUsage(
    const CxProcess::id_t &a_cidId
)
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    // TODO: CxProcessInfo::ulCpuUsage
#elif xOS_ENV_UNIX
    // TODO: CxProcessInfo::ulCpuUsage
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/* static */
ulong_t
CxProcessInfo::ulRamUsage(
    const CxProcess::id_t &a_cidId
)
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    // TODO: CxProcessInfo::ulRamUsage
#elif xOS_ENV_UNIX
    // TODO: CxProcessInfo::ulRamUsage
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/* static */
ulong_t
CxProcessInfo::ulIOBytes(
    const CxProcess::id_t &a_cidId
)
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

    std::tstring_t sProcPath  = CxString::sFormat(xT("/proc/%lu/io"), a_cidId);

    ulong_t ulReadBytes = 0UL;
    {
        std::tstring_t sValue = CxPath::sProcValue(sProcPath, xT("read_bytes"));

        ulReadBytes = CxString::cast<ulong_t>( sValue );
    }

    ulong_t ulWriteBytes = 0UL;
    {
        std::tstring_t sValue = CxPath::sProcValue(sProcPath, xT("write_bytes"));

        ulWriteBytes = CxString::cast<ulong_t>( sValue );
    }

    ulRv = ulReadBytes + ulWriteBytes;

    // xTRACEV("\tulReadBytes: %lu, ulWriteBytes: %lu", ulReadBytes, ulWriteBytes);
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxProcessInfo::sExeName(
    const CxProcess::id_t &a_cidId
)
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    sRv.resize(xPATH_MAX);

    CxProcess::handle_t hHandle = CxProcess::ulHandleById(a_cidId);

    DWORD ulStored = ::GetModuleFileNameEx(hHandle, NULL, &sRv.at(0), sRv.size());
    xTEST_DIFF(0UL, ulStored);

    sRv.resize(ulStored);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        const std::tstring_t csProcFile = CxString::sFormat(xT("/proc/%ld/exe"), a_cidId);

        bool bRv = CxFile::bIsExists(csProcFile);
        xCHECK_RET(false == bRv, std::tstring_t());

        int iReaded = - 1;
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
            int aiMib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, a_cidId};

            tchar_t szBuff[PATH_MAX + 1] = {0};
            size_t  uiBuffSize           = sizeof(szBuff) - 1;

            int iRv = ::sysctl(aiMib, xARRAY_SIZE(aiMib), szBuff, &uiBuffSize, NULL, 0U);
            xTEST_DIFF(- 1, iRv);

            sRv.assign(szBuff);
        #else
            // TODO: CxProcessInfo::sGetExeName
            xNOT_IMPLEMENTED_RET(std::tstring_t());
        #endif
    #endif
#endif

    return sRv;
}
//----------------------------------------------------------------------------------------------------
/* static */
ulong_t
CxProcessInfo::ulParentId(
    const CxProcess::id_t &a_cidId
)
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
#endif

    return ulRv;
}
//----------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
CxProcessInfo::sCommandLine(
    const CxProcess::id_t &a_cidId
)
{
    std::tstring_t sRv;

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

        if (cidNtoskrnlId == a_cidId) {
            sRv = CxEnvironment::sExpandStrings(xT("%SystemRoot%\\System32\\ntoskrnl.exe"));

            return sRv;
        }
    }


    #if xCOMPILER_MINGW32 || xCOMPILER_CODEGEAR
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
        pvPebAddress(HANDLE hProcessHandle) {
            CxDll dlDll;

            dlDll.vLoad(xT("ntdll.dll"));

            bool bRv = dlDll.bIsProcExists(xT("NtQueryInformationProcess"));
            xTEST_EQ(true, bRv);

            Dll_NtQueryInformationProcess_t
            DllNtQueryInformationProcess = (Dll_NtQueryInformationProcess_t)dlDll.fpProcAddress(xT("NtQueryInformationProcess"));
            xTEST_PTR(DllNtQueryInformationProcess);

            const PROCESSINFOCLASS    cpicInfo86       = ProcessBasicInformation;
            const PROCESSINFOCLASS    cpicInfo64       = ProcessWow64Information;   xUNUSED(cpicInfo64);
            PROCESS_BASIC_INFORMATION pbiBasicInfo     = {0};
            const DWORD               cdwBasicInfoSize = sizeof(pbiBasicInfo);   // in bytes
            DWORD                     dwReturnSize     = 0UL;   // in bytes

            // TODO: ProcessBasicInformation (for x64)
            NTSTATUS nsRv = DllNtQueryInformationProcess(hProcessHandle,
                                                         cpicInfo64,
                                                         &pbiBasicInfo, cdwBasicInfoSize, &dwReturnSize);
            xTEST_EQ(true, NT_SUCCESS(nsRv));
            xTEST_EQ(cdwBasicInfoSize, dwReturnSize);
            xTEST_PTR(pbiBasicInfo.PebBaseAddress);

            PVOID pvRv = pbiBasicInfo.PebBaseAddress;

            return pvRv;
        }
    };


    CxHandle processHandle;

    processHandle = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, a_cidId);
    xTEST_EQ(true, processHandle.bIsValid());

    PVOID pebAddress               = _SNested::pvPebAddress(processHandle.hGet());
    PVOID rtlUserProcParamsAddress = NULL;

    // get the address of ProcessParameters
    BOOL blRv = ::ReadProcessMemory(processHandle.hGet(), static_cast<PCHAR>(pebAddress) + 0x10,  &rtlUserProcParamsAddress, sizeof(PVOID), NULL);
    xTEST_DIFF(FALSE, blRv);

    // read the usCommandLine UNICODE_STRING structure
    UNICODE_STRING usCommandLine = {0};

    blRv = ::ReadProcessMemory(processHandle.hGet(), static_cast<PCHAR>(rtlUserProcParamsAddress) + 0x40, &usCommandLine, sizeof(usCommandLine), NULL);
    xTEST_DIFF(FALSE, blRv);

    // allocate memory to hold the command line
    {
        WCHAR *pCommandLineContents = static_cast<WCHAR *>( ::malloc(usCommandLine.Length) );
        xTEST_PTR(pCommandLineContents);

        // read the command line
        blRv = ::ReadProcessMemory(processHandle.hGet(), usCommandLine.Buffer, pCommandLineContents, usCommandLine.Length, NULL);
        xTEST_DIFF(FALSE, blRv);

        // length specifier is in characters, but usCommandLine.Length is in bytes a WCHAR is 2 bytes
        std::wstring wsRv;
        wsRv.assign(pCommandLineContents, usCommandLine.Length / 2);

    #if xUNICODE
        sRv = wsRv;
    #else
        sRv = CxString::sWStrToStr(wsRv, CP_ACP);
    #endif

        (void)::free(pCommandLineContents); pCommandLineContents = NULL;
    }
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // FIX: content of "/proc/%ld/cmdline" - missing spaces
        const std::tstring_t csProcFile = CxString::sFormat(xT("/proc/%ld/cmdline"), a_cidId);

        std::vec_tstring_t vsProcFile;

        CxPath::vProc(csProcFile, &vsProcFile);
        xTEST_EQ(size_t(1), vsProcFile.size())

        sRv = vsProcFile.at(0);
    #elif xOS_FREEBSD
        int iRv      = - 1;
        int aiMib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ARGS, a_cidId};

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
#endif


    return sRv;
}
//----------------------------------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxProcessInfo::CxProcessInfo() {

}
//---------------------------------------------------------------------------
/* virtual */
CxProcessInfo::~CxProcessInfo() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
