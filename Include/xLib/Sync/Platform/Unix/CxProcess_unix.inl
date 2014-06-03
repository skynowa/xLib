/**
 * \file  CxProcess.inl
 * \brief process
 */


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxProcess::_destruct_impl()
{
    xNA;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxProcess::_create_impl(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_params
)
{
    pid_t pid = ::fork();
    xTEST_EQ(pid != - 1L, true);

    if (pid == 0L) {
        // TODO: CxProcess::_create_impl() - a_filePath is executable

        int_t iRv = ::execlp(a_filePath.c_str(), a_filePath.c_str(), a_params.c_str(),
            static_cast<ctchar_t *>( xPTR_NULL ));
        xTEST_DIFF(iRv, - 1);

        (void_t)::_exit(EXIT_SUCCESS);  /* not exit() */
    }

    _handle = pid;
    _pid    = pid;
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::ExWaitResult
CxProcess::_wait_impl(
    culong_t &a_timeoutMsec
)
{
    ExWaitResult waitStatus = wrFailed;

    xUNUSED(a_timeoutMsec);

    // TODO: CxProcess::_wait_impl() - a_timeoutMsec
    pid_t liRv   = - 1L;
    int_t status = 0;

    do {
        liRv = ::waitpid(_pid, &status, 0);
    }
    while (liRv < 0L && CxLastError::get() == EINTR);
    xTEST_EQ(liRv, _pid);

    _exitStatus = WEXITSTATUS(status);
    waitStatus  = static_cast<ExWaitResult>( WEXITSTATUS(status) );

    return waitStatus;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxProcess::_kill_impl(
    culong_t &a_timeoutMsec
)
{
    int_t iRv = ::kill(_pid, SIGKILL);
    xTEST_DIFF(iRv, - 1);

    CxThread::currentSleep(a_timeoutMsec);

    _exitStatus = 0U;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcess::_exitStatus_impl() const
{
    ulong_t ulRv = _exitStatus;

    return ulRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxProcess::id_t
CxProcess::_idByHandle_impl(
    const handle_t &a_handle    ///< handle
)
{
    id_t ulRv = static_cast<id_t>( a_handle );

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::handle_t
CxProcess::_handleById_impl(
    const id_t &a_id   ///< ID
)
{
    handle_t hRv = static_cast<handle_t>( a_id );

    return hRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline
CxProcess::id_t
CxProcess::_idByName_impl(
    std::ctstring_t &a_processName
)
{
    id_t ulRv;

#if   xOS_LINUX
    int_t pid = -1;

    // open the /proc directory
    DIR *dir = ::opendir("/proc");
    xTEST_PTR(dir);

    // enumerate all entries in directory until process found
    for ( ; ; ) {
        dirent *dirEntry = ::readdir(dir);
        xCHECK_DO(dirEntry == xPTR_NULL, break);

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
        if (pos != std::string::npos) {
            cmdLine = cmdLine.substr(0, pos);
        }

        cmdLine = CxPath(cmdLine).fileName();
        if (cmdLine == a_processName) {
            pid = id;
            break;
        }
    }

    int_t iRv = ::closedir(dir); dir = xPTR_NULL;
    xTEST_DIFF(iRv, - 1);

    ulRv = pid;
#elif xOS_FREEBSD
    int_t  mib[3]   = {CTL_KERN, KERN_PROC, KERN_PROC_ALL};
    size_t buffSize = 0U;

    int_t iRv = ::sysctl(mib, xARRAY_SIZE(mib), xPTR_NULL, &buffSize, xPTR_NULL, 0U);
    xTEST_DIFF(iRv, - 1);

    // allocate memory and populate info in the  processes structure
    kinfo_proc *infoProc = xPTR_NULL;

    for ( ; ; ) {
        buffSize += buffSize / 10;

        kinfo_proc *infoProcNew = static_cast<kinfo_proc *>( realloc(infoProc, buffSize) );
        xTEST_PTR(infoProcNew);

        infoProc = infoProcNew;

        iRv = ::sysctl(mib, xARRAY_SIZE(mib), infoProc, &buffSize, xPTR_NULL, 0U);
        xCHECK_DO(!(iRv == - 1 && errno == ENOMEM), break);
    }

    // search for the given process name and return its pid
    size_t uiNumProcs = buffSize / sizeof(kinfo_proc);

    for (size_t i = 0; i < uiNumProcs; ++ i) {
        if (std::strncmp(a_processName.c_str(), infoProc[i].ki_comm, MAXCOMLEN) == 0) {
            ulRv = infoProc[i].ki_pid;

            break;
        } else {
            ulRv = - 1;
        }
    }

    xBUFF_FREE(infoProc);
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxProcess::_ids_impl(
    std::vector<CxProcess::id_t> *a_ids
)
{
    std::vector<id_t> vidRv;

#if   xOS_LINUX
    std::vec_tstring_t dirPaths;

    CxFinder::dirs(xT("/proc"), CxConst::maskAll(), false, &dirPaths);

    // skip non-numeric entries
    xFOREACH_CONST(std::vec_tstring_t, it, dirPaths) {
        int_t pid = 0;
        {
            std::tstring_t dirName = CxPath(*it).fileName();

            pid = std::atoi(dirName.c_str());
            xCHECK_DO(0 >= pid, continue);
        }

        vidRv.push_back( static_cast<id_t>( pid ));
    }
#elif xOS_FREEBSD
    int_t  mib[3]   = {CTL_KERN, KERN_PROC, KERN_PROC_ALL};
    size_t buffSize = 0U;

    int_t iRv = ::sysctl(mib, xARRAY_SIZE(mib), xPTR_NULL, &buffSize, xPTR_NULL, 0U);
    xTEST_DIFF(iRv, - 1);

    // allocate memory and populate info in the  processes structure
    kinfo_proc *infoProc = xPTR_NULL;

    for ( ; ; ) {
        buffSize += buffSize / 10;

        kinfo_proc *infoProcNew = static_cast<kinfo_proc *>( realloc(infoProc, buffSize) );
        xTEST_PTR(infoProcNew);

        infoProc = infoProcNew;

        iRv = ::sysctl(mib, xARRAY_SIZE(mib), infoProc, &buffSize, xPTR_NULL, 0U);
        xCHECK_DO(!(iRv == - 1 && errno == ENOMEM), break);
    }

    // search for the given process name and return its pid
    std::csize_t procsNum = buffSize / sizeof(kinfo_proc);

    for (size_t i = 0; i < procsNum; ++ i) {
        pid_t pid = infoProc[i].ki_pid;

        vidRv.push_back(pid);
    }

    xBUFF_FREE(infoProc);
#endif

    // out
    a_ids->swap(vidRv);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxProcess::_isCurrent_impl(
    const CxProcess::id_t &a_id
)
{
    bool_t bRv = ::pthread_equal(currentId(), a_id);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::id_t
CxProcess::_currentId_impl()
{
    id_t ulRv = ::getpid();
    // n/a

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::id_t
CxProcess::_currentParentId_impl()
{
    id_t ulRv = ::getppid();
    xTEST_NA(ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline CxProcess::handle_t
CxProcess::_currentHandle_impl()
{
    handle_t hRv = ::getpid();
    // n/a

    return hRv;
}
//-------------------------------------------------------------------------------------------------
// TODO: tests
inline void_t
CxProcess::_currentExit_impl(
    cuint_t &a_exitCode
)
{
    (void_t)::exit(static_cast<int_t>( a_exitCode ));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
