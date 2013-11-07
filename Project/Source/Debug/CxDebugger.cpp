/**
 * \file  CxDebugger.cpp
 * \brief debugger
 */


#include <xLib/Debug/CxDebugger.h>

#include <xLib/Core/CxDateTime.h>
#include <xLib/System/CxSystemInfo.h>
#include <xLib/System/CxConsole.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Gui/Dialogs/CxMsgBoxT.h>
#include <xLib/System/CxEnvironment.h>

#if xOS_ENV_UNIX
    #if   xOS_LINUX
        #if xTEMP_DISABLED
            #include <linux/kd.h>   //bBeep
            #include <X11/Xlib.h>   //bBeep -lX11
        #endif
    #elif xOS_FREEBSD
        #include <sys/user.h>
        #include <sys/proc.h>
    #endif
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxDebugger::CxDebugger() :
    _isEnabled(true),
    _logPath  ()
{
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public static
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDebugger::isEnabled()
{
    return _isEnabled;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDebugger::setEnabled(
    cbool_t &a_flag
)
{
    _isEnabled = a_flag;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDebugger::isActive()
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
        int_t             mib[4]   = {0};
        struct kinfo_proc info     = {0};
        size_t            infoSize = 0;

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
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDebugger::isDebugBuild()
{
#if xBUILD_DEBUG
    return true;
#else
    return false;
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDebugger::breakPoint()
{
    xCHECK_DO(!isEnabled(), return);

#if xOS_ENV_WIN
    (void_t)::DebugBreak();
#else
    int_t iRv = ::raise(SIGTRAP);
    xTEST_DIFF(- 1, iRv);

    iRv = ::kill(::getpid(), SIGALRM);
    xTEST_DIFF(- 1, iRv);
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDebugger::setLogPath(
    std::ctstring_t &a_filePath
)
{
    _logPath = a_filePath;
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxDebugger::logPath()
{
    return _logPath;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDebugger::reportMake(
    const CxErrorReport &a_report
)
{
    //-------------------------------------
    // never corrupt the last error value
    culong_t lastError = CxLastError::get();

    switch (a_report.type) {
    case CxErrorReport::rtMsgboxPlain:
        _msgboxPlain(a_report);
        break;
    case CxErrorReport::rtStdoutPlain:
        _stdoutPlain(a_report);
        break;
    case CxErrorReport::rtLoggingPlain:
        _loggingPlain(a_report);
        break;
    default:
        _stdoutPlain(a_report);
        break;
    }

    //-------------------------------------
    // never corrupt the last error value
    CxLastError::set(lastError);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDebugger::_msgboxPlain(
    const CxErrorReport &a_report
)
{
    xCHECK_DO(!isEnabled(), return);

#if xDEBUG_USE_PROMPT_DIALOG
    #if xOS_ENV_WIN
        uint_t type = MB_ABORTRETRYIGNORE | MB_ICONSTOP;
    #else
        uint_t type = 1U;
    #endif

    CxMsgBoxT::ExModalResult mrRv = CxMsgBoxT::show(a_report.report, CxPath::exe(), type);
#else
    CxMsgBoxT::ExModalResult mrRv = CxMsgBoxT::mrIgnore;
#endif
    switch (mrRv) {
    case CxMsgBoxT::mrAbort:
        (void_t)::exit(EXIT_FAILURE);
        break;
    default:
    case CxMsgBoxT::mrIgnore:
        xNA;
        break;
    case CxMsgBoxT::mrRetry:
        if (isActive()) {
            breakPoint();
        } else {
            CxMsgBoxT::ExModalResult nrRv = CxMsgBoxT::show(xT("Debugger is not present.\n"
                "The application will be terminated."), xT("xLib"));
            xUNUSED(nrRv);
            (void_t)::exit(EXIT_FAILURE);
        }
        break;
    }
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDebugger::_stdoutPlain(
    const CxErrorReport &a_report
)
{
    xCHECK_DO(!isEnabled(), return);

    enum EConsoleCmd {
        cmAbort  = xT('a'),
        cmIgnore = xT('i'),
        cmRetry  = xT('r')
    };

    std::tcout << xT("\n####################################################################################################\n");
    std::tcout << a_report.report;
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
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDebugger::_loggingPlain(
    const CxErrorReport &a_report
)
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

        std::ctstring_t csMsg = CxString::format(
            xT("\n")
            xT("####################################################################################################\n")
            xT("%s\n")
            xT("####################################################################################################\n"),
            a_report.report.c_str()
        );

        ofs << csMsg;
        ofs.close();
    }
    catch (...) {
    }
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
