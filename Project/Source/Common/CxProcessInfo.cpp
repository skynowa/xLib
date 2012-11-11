/**
 * \file   CxProcessInfo.cpp
 * \brief
 */


#include <xLib/Common/CxProcessInfo.h>

#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>


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
    CxProcess::id_t              ulRv;

#if   xOS_ENV_WIN
    CxHandle       hSnapshot;
    PROCESSENTRY32 peProcess = {0};    peProcess.dwSize = sizeof(PROCESSENTRY32);

    hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0UL);
    /*DEBUG*/xTEST_EQ(true, hSnapshot.bIsValid());

    BOOL blRv = ::Process32First(hSnapshot.hGet(), &peProcess);
    /*DEBUG*/xTEST_DIFF(FALSE, blRv);

    xFOREVER {
        vidRv.push_back(peProcess.th32ProcessID);

        blRv = ::Process32Next(hSnapshot.hGet(), &peProcess);
        xCHECK_DO(FALSE == blRv, break);
    }
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        int iPid = -1;

        // open the /proc directory
        DIR *pDir = ::opendir("/proc");
        xTEST_PTR(pDir);

        // enumerate all entries in directory until process found
        xFOREVER {
            struct dirent *dirp = ::readdir(pDir);
            xCHECK_DO(NULL == dirp, break);

            // skip non-numeric entries
            int iId = ::atoi(dirp->d_name);
            xCHECK_DO(0 >= iId, continue);

            // read contents of virtual /proc/{pid}/cmdline file
            std::string   cmdPath = std::string("/proc/") + dirp->d_name + "/cmdline";
            std::ifstream cmdFile(cmdPath.c_str());
            std::string   cmdLine;

            std::getline(cmdFile, cmdLine);
            xCHECK_DO(true == cmdLine.empty(), continue);

            // keep first cmdline item which contains the program path
            size_t uiPos = cmdLine.find('\0');
            if (std::string::npos != uiPos) {
                cmdLine = cmdLine.substr(0, uiPos);
            }

            cmdLine = CxPath::sFileName(cmdLine);
            if (a_csProcessName == cmdLine) {
                iPid = iId;
                break;
            }
        }

        int iRv = ::closedir(pDir); pDir = NULL;
        /*DEBUG*/xTEST_DIFF(- 1, iRv);

        ulRv = iPid;
    #elif xOS_FREEBSD
        int    aiMib[3]   = {CTL_KERN, KERN_PROC, KERN_PROC_ALL};
        size_t uiBuffSize = 0U;

        int iRv = ::sysctl(aiMib, xARRAY_SIZE(aiMib), NULL, &uiBuffSize, NULL, 0U);
        /*DEBUG*/xTEST_DIFF(- 1, iRv);

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
        size_t uiNumProcs = uiBuffSize / sizeof(kinfo_proc);

        for (size_t i = 0; i < uiNumProcs; ++ i) {
            if (0 == strncmp(a_csProcessName.c_str(), pkpProcesses[i].ki_comm, MAXCOMLEN)) {
                ulRv = pkpProcesses[i].ki_pid;

                break;
            } else {
                ulRv = - 1;
            }
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

        ulReadBytes = CxString::string_cast<ulong_t>( sValue );
    }

    ulong_t ulWriteBytes = 0UL;
    {
        std::tstring_t sValue = CxPath::sProcValue(sProcPath, xT("write_bytes"));

        ulWriteBytes = CxString::string_cast<ulong_t>( sValue );
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
    /*DEBUG*/xTEST_DIFF(0UL, ulStored);

    sRv.resize(ulStored);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        const std::tstring_t csProcFile = CxString::sFormat(xT("/proc/%ld/exe"), a_cidId);

        bool bRv = CxFile::bIsExists(csProcFile);
        xCHECK_RET(false == bRv, std::tstring_t());

        int iReaded = - 1;
        sRv.resize(xPATH_MAX);

        for ( ; ; ) {
            iReaded = ::readlink(csProcFile.c_str(), &sRv.at(0), sRv.size() * sizeof(std::tstring_t::value_type));
            /*DEBUG*/xTEST_DIFF(- 1, iReaded);

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
            /*DEBUG*/xTEST_DIFF(- 1, iRv);

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
CxProcessInfo::sArgs(
    const CxProcess::id_t &a_cidId
)
{
    // TODO: tests for CxProcessInfo::sArgs

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    // TODO: CxProcessInfo::sArgs
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // TODO: CxProcessInfo::sGetArgs
    #elif xOS_FREEBSD
        int iRv      = - 1;
        int aiMib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ARGS, a_cidId};

        std::string sBuff;
        size_t      uiBuffSize = 0;

        // get uiBuffSize
        iRv = ::sysctl(aiMib, xARRAY_SIZE(aiMib), NULL,         &uiBuffSize, NULL, 0);
        /*DEBUG*/xTEST_DIFF(- 1, iRv);

        sBuff.resize(uiBuffSize);

        iRv = ::sysctl(aiMib, xARRAY_SIZE(aiMib), &sBuff.at(0), &uiBuffSize, NULL, 0U);
        /*DEBUG*/xTEST_DIFF(- 1, iRv);

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
