/**
 * \file  CxProcess.cpp
 * \brief process
 */


#include <xLib/Sync/CxProcess.h>

#include <xLib/Common/CxString.h>
#include <xLib/Common/CxSystemInfo.h>
#include <xLib/Common/CxProcessInfo.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Sync/CxCurrentThread.h>
#include <xLib/Sync/CxCurrentProcess.h>

#if   xOS_ENV_WIN
    #if !xCOMPILER_MINGW
        #pragma comment(lib, "psapi.lib")
    #endif
#elif xOS_ENV_UNIX
    xNA
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxProcess::CxProcess() :
    _m_hHandle     (0),
#if   xOS_ENV_WIN
    _m_hThread     (NULL),
#endif
    _m_ulPid       (0UL),
    _m_uiExitStatus(0U)
{

}
//------------------------------------------------------------------------------
/* virtual */
CxProcess::~CxProcess() {
#if   xOS_ENV_WIN
    BOOL blRes = FALSE;

    blRes = ::CloseHandle(_m_hThread);
    xTEST_DIFF(FALSE, blRes);

    blRes = ::CloseHandle(_m_hHandle);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    xNA;
#endif
}
//------------------------------------------------------------------------------
void_t
CxProcess::create(
    std::ctstring_t &a_csFilePath,
    ctchar_t        *a_pcszParams, ...
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_EQ(true, CxFile::isExists(a_csFilePath));
    xTEST_PTR(a_pcszParams);

    std::tstring_t sCmdLine;

    va_list palArgs;
    xVA_START(palArgs, a_pcszParams);
    sCmdLine = CxString::formatV(a_pcszParams, palArgs);
    xVA_END(palArgs);

    //xTRACEV(xT("sCmdLine: %s"), sCmdLine.c_str());

#if   xOS_ENV_WIN
    STARTUPINFO         siInfo = {0};   siInfo.cb = sizeof(siInfo);
    PROCESS_INFORMATION piInfo = {0};

    BOOL blRes = ::CreateProcess(a_csFilePath.c_str(), const_cast<LPTSTR>( sCmdLine.c_str() ),
                                 NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL,
                                 &siInfo, &piInfo);
    xTEST_DIFF(FALSE, blRes);

    _m_hHandle = piInfo.hProcess;
    _m_hThread = piInfo.hThread;
    _m_ulPid   = piInfo.dwProcessId;
#elif xOS_ENV_UNIX
    pid_t liPid = ::fork();
    xTEST_EQ(true, - 1L != liPid);

    if (0L == liPid) {
        // TODO: csFilePath is executable

        int_t iRv = ::execlp(a_csFilePath.c_str(), a_csFilePath.c_str(), sCmdLine.c_str(), static_cast<ctchar_t *>( NULL ));
        xTEST_DIFF(- 1, iRv);

        (void_t)::_exit(EXIT_SUCCESS);  /* not exit() */
    }

    _m_hHandle = liPid;
    _m_ulPid   = liPid;
#endif
}
//------------------------------------------------------------------------------
CxProcess::ExWaitResult
CxProcess::wait(
    culong_t &a_culTimeout
)
{
    ExWaitResult wrStatus = wrFailed;

#if   xOS_ENV_WIN
    DWORD ulRv = ::WaitForSingleObject(_m_hHandle, a_culTimeout);
    xTEST_EQ(WAIT_OBJECT_0, ulRv);

    wrStatus = static_cast<ExWaitResult>( ulRv );
#elif xOS_ENV_UNIX
    // TODO: a_culTimeout
    pid_t liRv    = - 1L;
    int_t   iStatus = 0;

    do {
        liRv = ::waitpid(_m_ulPid, &iStatus, 0);
    }
    while (liRv < 0L && EINTR == CxLastError::get());
    xTEST_EQ(liRv, _m_ulPid);

    _m_uiExitStatus = WEXITSTATUS(iStatus);
    wrStatus        = static_cast<ExWaitResult>( WEXITSTATUS(iStatus) );
#endif

    return wrStatus;
}
//------------------------------------------------------------------------------
void_t
CxProcess::kill(
    culong_t &a_culTimeout    // FIX: culTimeout not used
)
{
#if   xOS_ENV_WIN
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _m_hHandle);
    // ulTimeout - n/a

    _m_uiExitStatus = 0U;

    BOOL blRes = ::TerminateProcess(_m_hHandle, _m_uiExitStatus);
    xTEST_DIFF(FALSE, blRes);

    xFOREVER {
        ulong_t ulRv = exitStatus();
        xCHECK_DO(STILL_ACTIVE != ulRv, break);

        CxCurrentThread::sleep(a_culTimeout);
    }
#elif xOS_ENV_UNIX
    int_t iRv = ::kill(_m_ulPid, SIGKILL);
    xTEST_DIFF(- 1, iRv);

    CxCurrentThread::sleep(a_culTimeout);

    _m_uiExitStatus = 0U;
#endif
}
//------------------------------------------------------------------------------
CxProcess::handle_t
CxProcess::handle() const {
    return _m_hHandle;
}
//------------------------------------------------------------------------------
CxProcess::id_t
CxProcess::id() const {
    return _m_ulPid;
}
//------------------------------------------------------------------------------
bool_t
CxProcess::isCurrent() const {
    return CxCurrentProcess::isCurrent( CxCurrentProcess::id() );
}
//------------------------------------------------------------------------------
ulong_t
CxProcess::exitStatus() const {
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    BOOL blRes = ::GetExitCodeProcess(_m_hHandle, &ulRv);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    ulRv = _m_uiExitStatus;
#endif

    return ulRv;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public, static
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
CxProcess::id_t
CxProcess::idByHandle(
    const handle_t &a_chHandle    ///< handle
)
{
    id_t ulRv;

#if   xOS_ENV_WIN
    ulRv = ::GetProcessId(a_chHandle);
    xTEST_NA(ulRv);
#elif xOS_ENV_UNIX
    ulRv = static_cast<id_t>( a_chHandle );
#endif

    return ulRv;
}
//------------------------------------------------------------------------------
/* static */
CxProcess::handle_t
CxProcess::handleById(
    const id_t &a_culId   ///< ID
)
{
    handle_t hRv;

#if   xOS_ENV_WIN
    hRv = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, a_culId);
    xTEST_NA(hRv);
#elif xOS_ENV_UNIX
    hRv = static_cast<handle_t>( a_culId );
#endif

    return hRv;
}
//------------------------------------------------------------------------------
/* static */
CxProcess::id_t
CxProcess::idByName(
    std::ctstring_t &a_csProcessName
)
{
    id_t ulRv;

#if   xOS_ENV_WIN
    CxHandle       hSnapshot;
    PROCESSENTRY32 peProcess = {0};    peProcess.dwSize = sizeof(PROCESSENTRY32);

    hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0UL);
    xTEST_EQ(true, hSnapshot.isValid());

    BOOL blRv = ::Process32First(hSnapshot.get(), &peProcess);
    xTEST_DIFF(FALSE, blRv);

    xFOREVER {
        bool_t bRv = CxString::compareNoCase(a_csProcessName, peProcess.szExeFile);
        xCHECK_DO(true == bRv, break);   // OK

        blRv = ::Process32Next(hSnapshot.get(), &peProcess);
        xCHECK_DO(FALSE == blRv, break);
    }

    ulRv = peProcess.th32ProcessID;
    xTEST_DIFF(0UL, ulRv);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        int_t iPid = -1;

        // open the /proc directory
        DIR *pDir = ::opendir("/proc");
        xTEST_PTR(pDir);

        // enumerate all entries in directory until process found
        xFOREVER {
            struct dirent *dirp = ::readdir(pDir);
            xCHECK_DO(NULL == dirp, break);

            // skip non-numeric entries
            int_t iId = ::atoi(dirp->d_name);
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

            cmdLine = CxPath(cmdLine).fileName();
            if (a_csProcessName == cmdLine) {
                iPid = iId;
                break;
            }
        }

        int_t iRv = ::closedir(pDir); pDir = NULL;
        xTEST_DIFF(- 1, iRv);

        ulRv = iPid;
    #elif xOS_FREEBSD
        int_t    aiMib[3]   = {CTL_KERN, KERN_PROC, KERN_PROC_ALL};
        size_t uiBuffSize = 0U;

        int_t iRv = ::sysctl(aiMib, xARRAY_SIZE(aiMib), NULL, &uiBuffSize, NULL, 0U);
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

    return ulRv;
}
//--------------------------------------------------------------------------
/* static */
bool_t
CxProcess::isRunning(
    const id_t &culId
)
{
    std::vector<CxProcess::id_t> vidIds;

    CxProcessInfo::currentIds(&vidIds);

    std::vector<CxProcess::id_t>::iterator it;
    it = std::find(vidIds.begin(), vidIds.end(), culId);
    xCHECK_RET(it == vidIds.end(), false);

    return true;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
