/**
 * \file  CxDebugger.cpp
 * \brief debugger
 */


#include <xLib/Core/CxDateTime.h>
#include <xLib/System/CxSystemInfo.h>
#include <xLib/System/CxConsole.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Gui/CxMsgBox.h>
#include <xLib/System/CxEnvironment.h>

#if xOS_ENV_UNIX
    #if   xOS_LINUX
        #if xTEMP_DISABLED
            #include <linux/kd.h>   // beep
            #include <X11/Xlib.h>   // beep -lX11
        #endif
    #elif xOS_FREEBSD
        #include <sys/user.h>
        #include <sys/proc.h>
    #endif
#endif

#if   xHAVE_PR_SET_DUMPABLE
    #include <sys/prctl.h>
#elif xHAVE_RLIMIT_CORE
    #include <sys/resource.h>
#endif


xNAMESPACE_BEGIN(xlib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxDebugger::CxDebugger() :
    _isEnabled(true),
    _logPath  ()
{
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxDebugger::isEnabled() const
{
    return _isEnabled;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDebugger::setEnabled(
    cbool_t &a_flag
)
{
    _isEnabled = a_flag;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDebugger::isActive() const
{
#if   xOS_ENV_WIN
    // local debugger
    BOOL blRv = ::IsDebuggerPresent();
    xCHECK_RET(FALSE != blRv, true);

    // remote debugger
    BOOL isRemoteDebuggerPresent = FALSE;

    blRv = ::CheckRemoteDebuggerPresent(::GetCurrentProcess(), &isRemoteDebuggerPresent);
    xCHECK_RET(FALSE == blRv || FALSE == isRemoteDebuggerPresent, false);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // if ppid != sid, some process spawned our app, probably a debugger
        bool_t bRv = ( ::getsid(::getpid()) != ::getppid() );
        xCHECK_RET(!bRv, false);
    #elif xOS_FREEBSD
        int_t      mib[4];  xSTRUCT_ZERO(mib);
        kinfo_proc info;    xSTRUCT_ZERO(info);
        size_t     infoSize = 0;

        mib[0] = CTL_KERN;
        mib[1] = KERN_PROC;
        mib[2] = KERN_PROC_PID;
        mib[3] = ::getpid();

        // if sysctl fails for some bizarre reason, we get a predictable result
        info.ki_flag = 0;

        infoSize = sizeof(info);

        int_t iRv = ::sysctl(mib, xARRAY_SIZE(mib), &info, &infoSize, NULL, 0);
        xCHECK_RET(- 1 == iRv, false);

        // we're being debugged if the P_TRACED flag is set.
        xCHECK_RET(0 == (info.ki_flag & P_TRACED), false);
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDebugger::isDebugBuild() const
{
#if xBUILD_DEBUG
    return true;
#else
    return false;
#endif
}
//-------------------------------------------------------------------------------------------------
inline void
CxDebugger::coreDumpsEnable(
    cbool_t &a_flag
)
{
    xUNUSED(a_flag);    // TODO: CxDebugger::coreDumpsEnable() - a_flag
    xTEST_NA(a_flag);

    bool_t isEnable = false;
    int_t  iRv      = 0;

#if   xOS_ENV_WIN
    isEnable = false;   // n/a
#elif xOS_ENV_UNIX
    #if   xHAVE_PR_SET_DUMPABLE
        // prefer PR_SET_DUMPABLE since that also prevents ptrace
        iRv = ::prctl(PR_SET_DUMPABLE, 0);
        isEnable = (iRv == 0);
    #elif xHAVE_RLIMIT_CORE
        rlimit limit = {0, 0};

        iRv = ::setrlimit(RLIMIT_CORE, &limit);
        isEnable = (iRv == 0);
    #else
        #pragma message("xLib: CxDebugger::coreDumpsEnable() - n/a")
    #endif
#elif xOS_ENV_MAC
    #if xHAVE_PT_DENY_ATTACH
        // make sure setrlimit() and ptrace() succeeded
        iRv = ::ptrace(PT_DENY_ATTACH, 0, 0, 0);
        isEnable = isEnable && (iRv == 0);
    #else
        #pragma message("xLib: CxDebugger::coreDumpsEnable() - n/a")
    #endif
#endif

    xCHECK_DO(!isEnable, CxTrace() << xT("xLib: CxDebugger::coreDumpsEnable() - n/a"));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDebugger::breakPoint() const
{
    xCHECK_DO(!isEnabled(), return);

#if   xOS_ENV_WIN
    (void_t)::DebugBreak();
#elif xOS_ENV_UNIX
    int_t iRv = ::raise(SIGTRAP);
    xTEST_DIFF(- 1, iRv);

    iRv = ::kill(::getpid(), SIGALRM);
    xTEST_DIFF(- 1, iRv);
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDebugger::setLogPath(
    std::ctstring_t &a_filePath
)
{
    _logPath = a_filePath;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxDebugger::logPath() const
{
    return _logPath;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDebugger::reportMake(
    const CxErrorReport &a_report
)
{
    // never corrupt last error value
    culong_t lastError = CxLastError::get();

    switch (a_report.type()) {
    case CxErrorReport::rtMsgbox:
        _msgboxPlain(a_report);
        break;
    case CxErrorReport::rtStdout:
        _stdoutPlain(a_report);
        break;
    case CxErrorReport::rtLog:
        _loggingPlain(a_report);
        break;
    default:
        _stdoutPlain(a_report);
        break;
    }

    // never corrupt last error value
    CxLastError::set(lastError);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxDebugger::_msgboxPlain(
    const CxErrorReport &a_report
) const
{
    xCHECK_DO(!isEnabled(), return);

    CxMsgBox::ExModalResult mrRv;

#if xDEBUG_USE_PROMPT_DIALOG || 1
    mrRv = CxMsgBox().show(a_report.toString(), "", CxMsgBox::tpAbortRetryIgnore);
#else
    mrRv = CxMsgBox::mrIgnore;
#endif
    switch (mrRv) {
    case CxMsgBox::mrAbort:
        (void_t)::exit(EXIT_FAILURE);
        break;
    default:
    case CxMsgBox::mrIgnore:
        xNA;
        break;
    case CxMsgBox::mrRetry:
        if (isActive()) {
            breakPoint();
        } else {
            CxMsgBox::ExModalResult nrRv = CxMsgBox().show(xT("Debugger is not present.\n"
                "The application will be terminated."), xT("xLib"));
            xUNUSED(nrRv);
            (void_t)::exit(EXIT_FAILURE);
        }
        break;
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDebugger::_stdoutPlain(
    const CxErrorReport &a_report
) const
{
    xCHECK_DO(!isEnabled(), return);

    enum EConsoleCmd {
        cmAbort  = xT('a'),
        cmIgnore = xT('i'),
        cmRetry  = xT('r')
    };

    std::tcout << xT("\n####################################################################################################\n");
    std::tcout << a_report.toString();
    std::tcout << xT("\n####################################################################################################\n");
    std::tcout << xT("\n");
    std::tcout << xT("\nAbort (a), Ignore (i), Retry (r): ");
    std::tcout.flush();

#if xDEBUG_USE_PROMPT_DIALOG
    EConsoleCmd cmRv = static_cast<EConsoleCmd>( std::tcin.get() );   std::tcin.ignore();
#else
    EConsoleCmd cmRv = cmIgnore;
#endif
    switch (cmRv) {
    case cmAbort:
        std::tcout << xT("Abort...\n\n");  std::tcout.flush();

        (void_t)::exit(EXIT_FAILURE);
        break;
    default:
    case cmIgnore:
        std::tcout << xT("Ignore...\n\n");  std::tcout.flush();
        break;
    case cmRetry:
        std::tcout << xT("Retry...\n\n");

        if (isActive()) {
            breakPoint();
        } else {
            std::tcout << xT("\n####################################################################################################\n");
            std::tcout << xT("CxDebugger\n");
            std::tcout << xT("\n");
            std::tcout << xT("OS debugger is not present.\nThe application will be terminated.\n");
            std::tcout << xT("####################################################################################################\n");
            std::tcout << xT("\n\n");
            std::tcout.flush();

            (void_t)::exit(EXIT_FAILURE);
        }
        break;
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDebugger::_loggingPlain(
    const CxErrorReport &a_report
) const
{
    xCHECK_DO(!isEnabled(), return);

    //--------------------------------------------------
    // get log file path
    std::tstring_t filePath;

    if (logPath().empty()) {
        filePath = CxPath( CxPath::exe() ).setExt(xT("debug"));
    } else {
        filePath = logPath();
    }

    //--------------------------------------------------
    // write to file
    try {
        std::ofstream ofs(filePath.c_str(), std::ofstream::out);
        xCHECK_DO(ofs.fail(), return);

        std::ctstring_t msg = CxString::format(
            xT("\n")
            xT("####################################################################################################\n")
            xT("%s\n")
            xT("####################################################################################################\n"),
            a_report.toString().c_str()
        );

        ofs << msg;
        ofs.close();
    }
    catch (...) {
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(xlib)
