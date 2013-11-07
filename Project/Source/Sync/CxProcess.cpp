/**
 * \file  CxProcess.cpp
 * \brief process
 */


#include <xLib/Sync/CxProcess.h>

#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDll.h>
#include <xLib/Sync/CxThread.h>

#if xOS_ENV_WIN
    #if !xCOMPILER_MINGW
        #pragma comment(lib, "psapi.lib")
    #endif
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxProcess::CxProcess() :
    _handle    (0),
#if xOS_ENV_WIN
    _thread    (NULL),
#endif
    _pid       (0UL),
    _exitStatus(0U)
{
}
//------------------------------------------------------------------------------
/* virtual */
xINLINE_HO
CxProcess::~CxProcess()
{
#if xOS_ENV_WIN
    BOOL blRv = FALSE;

    blRv = ::CloseHandle(_thread);
    xTEST_DIFF(FALSE, blRv);

    blRv = ::CloseHandle(_handle);
    xTEST_DIFF(FALSE, blRv);
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxProcess::create(
    std::ctstring_t &a_filePath,
    ctchar_t        *a_params, ...
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_EQ(true, CxFile::isExists(a_filePath));
    xTEST_PTR(a_params);

    std::tstring_t cmdLine;

    va_list args;
    xVA_START(args, a_params);
    cmdLine = CxString::formatV(a_params, args);
    xVA_END(args);

    // xTRACEV(xT("cmdLine: %s"), cmdLine.c_str());

#if xOS_ENV_WIN
    STARTUPINFO         startupInfo = {0};  startupInfo.cb = sizeof(startupInfo);
    PROCESS_INFORMATION processInfo = {0};

    BOOL blRv = ::CreateProcess(a_filePath.c_str(), const_cast<LPTSTR>( cmdLine.c_str() ),
        NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInfo);
    xTEST_DIFF(FALSE, blRv);

    _handle = processInfo.hProcess;
    _thread = processInfo.hThread;
    _pid    = processInfo.dwProcessId;
#else
    pid_t id = ::fork();
    xTEST_EQ(true, - 1L != id);

    if (0L == id) {
        // TODO: filePath is executable

        int_t iRv = ::execlp(a_filePath.c_str(), a_filePath.c_str(), cmdLine.c_str(),
            static_cast<ctchar_t *>( NULL ));
        xTEST_DIFF(- 1, iRv);

        (void_t)::_exit(EXIT_SUCCESS);  /* not exit() */
    }

    _handle = id;
    _pid    = id;
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO CxProcess::ExWaitResult
CxProcess::wait(
    culong_t &a_timeoutMsec
)
{
    ExWaitResult waitStatus = wrFailed;

#if xOS_ENV_WIN
    DWORD ulRv = ::WaitForSingleObject(_handle, a_timeoutMsec);
    xTEST_EQ(WAIT_OBJECT_0, ulRv);

    waitStatus = static_cast<ExWaitResult>( ulRv );
#else
    // TODO: a_timeoutMsec
    pid_t liRv   = - 1L;
    int_t status = 0;

    do {
        liRv = ::waitpid(_pid, &status, 0);
    }
    while (liRv < 0L && EINTR == CxLastError::get());
    xTEST_EQ(liRv, _pid);

    _exitStatus = WEXITSTATUS(status);
    waitStatus  = static_cast<ExWaitResult>( WEXITSTATUS(status) );
#endif

    return waitStatus;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxProcess::kill(
    culong_t &a_timeoutMsec    // FIX: timeoutMSec not used
)
{
#if xOS_ENV_WIN
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _handle);
    // ulTimeout - n/a

    _exitStatus = 0U;

    BOOL blRv = ::TerminateProcess(_handle, _exitStatus);
    xTEST_DIFF(FALSE, blRv);

    xFOREVER {
        xCHECK_DO(STILL_ACTIVE != exitStatus(), break);

        CxThread::currentSleep(a_timeoutMsec);
    }
#else
    int_t iRv = ::kill(_pid, SIGKILL);
    xTEST_DIFF(- 1, iRv);

    CxThread::currentSleep(a_timeoutMsec);

    _exitStatus = 0U;
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO CxProcess::handle_t
CxProcess::handle() const
{
    return _handle;
}
//------------------------------------------------------------------------------
xINLINE_HO CxProcess::id_t
CxProcess::id() const
{
    return _pid;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxProcess::isCurrent() const
{
    return isCurrent( currentId() );
}
//------------------------------------------------------------------------------
xINLINE_HO ulong_t
CxProcess::exitStatus() const
{
    ulong_t ulRv = 0UL;

#if xOS_ENV_WIN
    BOOL blRv = ::GetExitCodeProcess(_handle, &ulRv);
    xTEST_DIFF(FALSE, blRv);
#else
    ulRv = _exitStatus;
#endif

    return ulRv;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public, static
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO CxProcess::id_t
CxProcess::idByHandle(
    const handle_t &a_handle    ///< handle
)
{
    id_t ulRv;

#if xOS_ENV_WIN
    ulRv = ::GetProcessId(a_handle);
    xTEST_NA(ulRv);
#else
    ulRv = static_cast<id_t>( a_handle );
#endif

    return ulRv;
}
//------------------------------------------------------------------------------
xINLINE_HO CxProcess::handle_t
CxProcess::handleById(
    const id_t &a_id   ///< ID
)
{
    handle_t hRv;

#if xOS_ENV_WIN
    hRv = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, a_id);
    xTEST_NA(hRv);
#else
    hRv = static_cast<handle_t>( a_id );
#endif

    return hRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO
CxProcess::id_t
CxProcess::idByName(
    std::ctstring_t &a_processName
)
{
    id_t ulRv;

#if xOS_ENV_WIN
    CxHandle       snapshot;
    PROCESSENTRY32 processEntry = {0};
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0UL);
    xTEST_EQ(true, snapshot.isValid());

    BOOL blRv = ::Process32First(snapshot.get(), &processEntry);
    xTEST_DIFF(FALSE, blRv);

    xFOREVER {
        bool_t bRv = CxString::compareNoCase(a_processName, processEntry.szExeFile);
        xCHECK_DO(bRv, break);   // OK

        blRv = ::Process32Next(snapshot.get(), &processEntry);
        xCHECK_DO(FALSE == blRv, break);
    }

    ulRv = processEntry.th32ProcessID;
    xTEST_DIFF(0UL, ulRv);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        int_t pid = -1;

        // open the /proc directory
        DIR *dir = ::opendir("/proc");
        xTEST_PTR(dir);

        // enumerate all entries in directory until process found
        xFOREVER {
            struct dirent *dirEntry = ::readdir(dir);
            xCHECK_DO(NULL == dirEntry, break);

            // skip non-numeric entries
            int_t id = ::atoi(dirEntry->d_name);
            xCHECK_DO(0 >= id, continue);

            // read contents of virtual /proc/{pid}/cmdline file
            std::string   cmdPath = std::string("/proc/") + dirEntry->d_name + "/cmdline";
            std::ifstream cmdFile(cmdPath.c_str());
            std::string   cmdLine;

            std::getline(cmdFile, cmdLine);
            xCHECK_DO(cmdLine.empty(), continue);

            // keep first cmdline item which contains the program path
            size_t pos = cmdLine.find('\0');
            if (std::string::npos != pos) {
                cmdLine = cmdLine.substr(0, pos);
            }

            cmdLine = CxPath(cmdLine).fileName();
            if (a_processName == cmdLine) {
                pid = id;
                break;
            }
        }

        int_t iRv = ::closedir(dir); dir = NULL;
        xTEST_DIFF(- 1, iRv);

        ulRv = pid;
    #elif xOS_FREEBSD
        int_t  mib[3]   = {CTL_KERN, KERN_PROC, KERN_PROC_ALL};
        size_t buffSize = 0U;

        int_t iRv = ::sysctl(mib, xARRAY_SIZE(mib), NULL, &buffSize, NULL, 0U);
        xTEST_DIFF(- 1, iRv);

        // allocate memory and populate info in the  processes structure
        kinfo_proc *infoProc = NULL;

        xFOREVER {
            buffSize += buffSize / 10;

            kinfo_proc *infoProcNew = static_cast<kinfo_proc *>( realloc(infoProc, buffSize) );
            xTEST_PTR(infoProcNew);

            infoProc = infoProcNew;

            iRv = ::sysctl(mib, xARRAY_SIZE(mib), infoProc, &buffSize, NULL, 0U);
            xCHECK_DO(!(- 1 == iRv && errno == ENOMEM), break);
        }

        // search for the given process name and return its pid
        size_t uiNumProcs = buffSize / sizeof(kinfo_proc);

        for (size_t i = 0; i < uiNumProcs; ++ i) {
            if (0 == strncmp(a_processName.c_str(), infoProc[i].ki_comm, MAXCOMLEN)) {
                ulRv = infoProc[i].ki_pid;

                break;
            } else {
                ulRv = - 1;
            }
        }

        xBUFF_FREE(infoProc);
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return ulRv;
}
//--------------------------------------------------------------------------
/* static */
xINLINE_HO bool_t
CxProcess::isRunning(
    const id_t &a_id
)
{
    std::vector<id_t> _ids;

    ids(&_ids);

    std::vector<id_t>::iterator it;
    it = std::find(_ids.begin(), _ids.end(), a_id);
    xCHECK_RET(it == _ids.end(), false);

    return true;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxProcess::ids(
    std::vector<CxProcess::id_t> *a_ids
)
{
    std::vector<id_t> vidRv;

#if   xOS_ENV_WIN
    CxHandle       snapshot;
    PROCESSENTRY32 processEntry = {0};
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0UL);
    xTEST_EQ(true, snapshot.isValid());

    BOOL blRv = ::Process32First(snapshot.get(), &processEntry);
    xTEST_DIFF(FALSE, blRv);

    xFOREVER {
        DWORD pid = processEntry.th32ProcessID;

        vidRv.push_back(pid);

        blRv = ::Process32Next(snapshot.get(), &processEntry);
        xCHECK_DO(FALSE == blRv, break);
    }
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        std::vec_tstring_t dirPaths;

        CxFinder::dirs(xT("/proc"), CxConst::maskAll(), false, &dirPaths);

        // skip non-numeric entries
        xFOREACH_CONST(std::vec_tstring_t, it, dirPaths) {
            int_t pid = 0;
            {
                std::tstring_t dirName = CxPath(*it).fileName();

                pid = ::atoi(dirName.c_str());
                xCHECK_DO(0 >= pid, continue);
            }

            vidRv.push_back( static_cast<id_t>( pid ));
        }
    #elif xOS_FREEBSD
        int_t  mib[3]   = {CTL_KERN, KERN_PROC, KERN_PROC_ALL};
        size_t buffSize = 0U;

        int_t iRv = ::sysctl(mib, xARRAY_SIZE(mib), NULL, &buffSize, NULL, 0U);
        xTEST_DIFF(- 1, iRv);

        // allocate memory and populate info in the  processes structure
        kinfo_proc *infoProc = NULL;

        xFOREVER {
            buffSize += buffSize / 10;

            kinfo_proc *infoProcNew = static_cast<kinfo_proc *>( realloc(infoProc, buffSize) );
            xTEST_PTR(infoProcNew);

            infoProc = infoProcNew;

            iRv = ::sysctl(mib, xARRAY_SIZE(mib), infoProc, &buffSize, NULL, 0U);
            xCHECK_DO(!(- 1 == iRv && errno == ENOMEM), break);
        }

        // search for the given process name and return its pid
        std::csize_t procsNum = buffSize / sizeof(kinfo_proc);

        for (size_t i = 0; i < procsNum; ++ i) {
            pid_t pid = infoProc[i].ki_pid;

            vidRv.push_back(pid);
        }

        xBUFF_FREE(infoProc);
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    // out
    (*a_ids).swap(vidRv);
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxProcess::isCurrent(
    const CxProcess::id_t &a_id
)
{
    bool_t bRv = false;

#if xOS_ENV_WIN
    bRv = (currentId() == a_id);
#else
    // TODO: If either thread1 or thread2 are not valid thread IDs, the behavior is undefined
    // bRv = ::pthread_equal(currentId(), a_id);
#endif

    return bRv;
}
//------------------------------------------------------------------------------
xINLINE_HO CxProcess::id_t
CxProcess::currentId()
{
    // n/a

    id_t ulRv;

#if xOS_ENV_WIN
    ulRv = ::GetCurrentProcessId();
    // n/a
#else
    ulRv = ::getpid();
    // n/a
#endif

    return ulRv;
}
//------------------------------------------------------------------------------
xINLINE_HO CxProcess::id_t
CxProcess::currentParentId()
{
    // n/a

    id_t ulRv;

#if xOS_ENV_WIN
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

    CxDll dll;

    dll.load(xT("ntdll.dll"));

    bool_t bRv = dll.isProcExists(xT("NtQueryInformationProcess"));
    xCHECK_RET(!bRv, invalidId);

#if xARCH_X86
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
    NTSTATUS ntsRv = DllNtQueryInformationProcess(
                            currentHandle(),
                            infoClass,
                           &processInformation, sizeof(processInformation), &returnSizeBytes);
    xTEST_EQ(true, NT_SUCCESS(ntsRv));
    xTEST_EQ(size_t(returnSizeBytes), sizeof(processInformation));

    ulRv = processInformation[5];
#else
    ulRv = ::getppid();
    xTEST_NA(ulRv);
#endif

    return ulRv;
}
//------------------------------------------------------------------------------
// TODO: tests
xINLINE_HO CxProcess::handle_t
CxProcess::currentHandle()
{
    // n/a

    handle_t hRv;

#if xOS_ENV_WIN
    #if xDEPRECIATE
        hRv = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, id());
    #else
        hRv = ::GetCurrentProcess();
    #endif
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
#else
    hRv = ::getpid();
    // n/a
#endif

    return hRv;
}
//------------------------------------------------------------------------------
// TODO: tests
xINLINE_HO void_t
CxProcess::currentExit(
    cuint_t &a_exitCode
)
{
#if xOS_ENV_WIN
    (void_t)::ExitProcess(a_exitCode);
#else
    (void_t)::exit(static_cast<int_t>( a_exitCode ));
#endif
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
