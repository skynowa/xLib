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
#include <xLib/Sync/CxProcess.h>
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
    BOOL blRes = ::IsDebuggerPresent();
    xCHECK_RET(FALSE != blRes, true);

    // remote debugger
    BOOL blIsRemoteDebuggerPresent = FALSE;

    blRes = ::CheckRemoteDebuggerPresent(CxProcess::currentHandle(), &blIsRemoteDebuggerPresent);
    xCHECK_RET(FALSE == blRes || FALSE == blIsRemoteDebuggerPresent, false);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // if ppid != sid, some process spawned our app, probably a debugger
        bool_t bRv = ( ::getsid(::getpid()) != ::getppid() );
        xCHECK_RET(!bRv, false);
    #elif xOS_FREEBSD
        int_t             aiMib[4]   = {0};
        struct kinfo_proc kiInfo     = {0};
        size_t            uiInfoSize = 0;

        aiMib[0] = CTL_KERN;
        aiMib[1] = KERN_PROC;
        aiMib[2] = KERN_PROC_PID;
        aiMib[3] = CxProcess::currentId();

        // if sysctl fails for some bizarre reason, we get a predictable result
        kiInfo.ki_flag = 0;

        uiInfoSize = sizeof(kiInfo);

        int_t iRv = ::sysctl(aiMib, xARRAY_SIZE(aiMib), &kiInfo, &uiInfoSize, NULL, 0);
        xCHECK_RET(- 1 == iRv, false);

        // we're being debugged if the P_TRACED flag is set.
        xCHECK_RET(0 == (kiInfo.ki_flag & P_TRACED), false);
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

    iRv = ::kill(CxProcess::currentId(), SIGALRM);
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
    culong_t culLastError = CxLastError::get();

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
    CxLastError::set(culLastError);
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
        uint_t uiType = MB_ABORTRETRYIGNORE | MB_ICONSTOP;
    #else
        uint_t uiType = 1U;
    #endif

    CxMsgBoxT::ExModalResult mrRes = CxMsgBoxT::show(a_report.report, CxPath::exe(), uiType);
#else
    CxMsgBoxT::ExModalResult mrRes = CxMsgBoxT::mrIgnore;
#endif
    switch (mrRes) {
        case CxMsgBoxT::mrAbort:
            CxProcess::currentExit(EXIT_FAILURE);
            break;
        default:
        case CxMsgBoxT::mrIgnore:
            xNA;
            break;
        case CxMsgBoxT::mrRetry:
            if (isActive()) {
                breakPoint();
            } else {
                CxMsgBoxT::ExModalResult nrRv = CxMsgBoxT::show(xT("Debugger is not present.\nThe application will be terminated."), xT("xLib"));
                xUNUSED(nrRv);
                CxProcess::currentExit(EXIT_FAILURE);
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
    EConsoleCmd cmRes = static_cast<EConsoleCmd>( std::tcin.get() );   std::tcin.ignore();
#else
    EConsoleCmd cmRes = cmIgnore;
#endif
    switch (cmRes) {
        case cmAbort:
            std::tcout << xT("Abort...\n\n");  std::tcout.flush();

            CxProcess::currentExit(EXIT_FAILURE);
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

                CxProcess::currentExit(EXIT_FAILURE);
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
    std::tstring_t sFilePath;

    if (logPath().empty()) {
        sFilePath = CxPath( CxPath::exe() ).setExt(xT("debug"));
    } else {
        sFilePath = logPath();
    }

    //--------------------------------------------------
    // write to file
    try {
        std::ofstream ofs(sFilePath.c_str(), std::ofstream::out);
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
