/**
 * \file  CxDebugger.cpp
 * \brief debugger
 */


#include <xLib/Debug/CxDebugger.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Common/CxSystemInfo.h>
#include <xLib/Common/CxConsole.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxEnvironment.h>
#include <xLib/Sync/CxCurrentProcess.h>
#include <xLib/Gui/Dialogs/CxMsgBoxT.h>

#if   xOS_ENV_WIN
    xNA
#elif xOS_ENV_UNIX
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

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxDebugger::CxDebugger() :
    _m_bIsEnabled(true),
    _m_sLogPath  ()
{

}
//---------------------------------------------------------------------------
/* virtual */
CxDebugger::~CxDebugger() {

}
//---------------------------------------------------------------------------


/****************************************************************************
*    public static
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxDebugger::isEnabled() {
    return _m_bIsEnabled;
}
//---------------------------------------------------------------------------
void
CxDebugger::setEnabled(
    const bool &a_cbFlag
)
{
    _m_bIsEnabled = a_cbFlag;
}
//---------------------------------------------------------------------------
bool
CxDebugger::isActive() {
#if   xOS_ENV_WIN
    // local debugger
    BOOL blRes = ::IsDebuggerPresent();
    xCHECK_RET(FALSE != blRes, true);

    // remote debugger
    BOOL blIsRemoteDebuggerPresent = FALSE;

    blRes = ::CheckRemoteDebuggerPresent(CxCurrentProcess::handle(), &blIsRemoteDebuggerPresent);
    xCHECK_RET(FALSE == blRes || FALSE == blIsRemoteDebuggerPresent, false);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // if ppid != sid, some process spawned our app, probably a debugger
        bool bRv = ( ::getsid(::getpid()) != ::getppid() );
        xCHECK_RET(false == bRv, false);
    #elif xOS_FREEBSD
        int               aiMib[4]   = {0};
        struct kinfo_proc kiInfo     = {0};
        size_t            uiInfoSize = 0;

        aiMib[0] = CTL_KERN;
        aiMib[1] = KERN_PROC;
        aiMib[2] = KERN_PROC_PID;
        aiMib[3] = CxCurrentProcess::id();

        // if sysctl fails for some bizarre reason, we get a predictable result
        kiInfo.ki_flag = 0;

        uiInfoSize = sizeof(kiInfo);

        int iRv = ::sysctl(aiMib, xARRAY_SIZE(aiMib), &kiInfo, &uiInfoSize, NULL, 0);
        xCHECK_RET(- 1 == iRv, false);

        // we're being debugged if the P_TRACED flag is set.
        xCHECK_RET(0 == (kiInfo.ki_flag & P_TRACED), false);
    #endif
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxDebugger::isDebugBuild() {
#if xBUILD_DEBUG
    return true;
#else
    return false;
#endif
}
//---------------------------------------------------------------------------
void
CxDebugger::breakPoint() {
    xCHECK_DO(false == isEnabled(), return);

#if   xOS_ENV_WIN
    (void)::DebugBreak();
#elif xOS_ENV_UNIX
    int iRv = ::raise(SIGTRAP);
    xTEST_DIFF(- 1, iRv);

    //// int iRv = ::kill(CxCurrentProcess::id(), SIGALRM);
    //// xTEST_DIFF(- 1, iRv);
#endif
}
//---------------------------------------------------------------------------
void
CxDebugger::setLogPath(
    const std::tstring_t &a_csFilePath
)
{
    _m_sLogPath = a_csFilePath;
}
//---------------------------------------------------------------------------
std::tstring_t
CxDebugger::logPath() {
    return _m_sLogPath;
}
//---------------------------------------------------------------------------
void
CxDebugger::reportMake(
    const CxErrorReport &a_crpReport
)
{
    //-------------------------------------
    // never corrupt the last error value
    const ulong_t culLastError = CxLastError::get();

    switch (a_crpReport.m_rtType) {
        case CxErrorReport::rtMsgboxPlain:  { _msgboxPlain (a_crpReport); } break;
        case CxErrorReport::rtStdoutPlain:  { _stdoutPlain (a_crpReport); } break;
        case CxErrorReport::rtLoggingPlain: { _loggingPlain(a_crpReport); } break;

        default:                            { _stdoutPlain (a_crpReport); } break;
    }

    //-------------------------------------
    // never corrupt the last error value
    CxLastError::set(culLastError);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxDebugger::_msgboxPlain(
    const CxErrorReport &a_crpReport
)
{
    xCHECK_DO(false == isEnabled(), return);

#if xDEBUG_USE_PROMPT_DIALOG
    #if   xOS_ENV_WIN
        uint_t uiType = MB_ABORTRETRYIGNORE | MB_ICONSTOP;
    #elif xOS_ENV_UNIX
        uint_t uiType = 1U;
    #endif

    CxMsgBoxT::ExModalResult mrRes = CxMsgBoxT::show(a_crpReport.m_sReport, CxPath::exe(), uiType);
#else
    CxMsgBoxT::ExModalResult mrRes = CxMsgBoxT::mrIgnore;
#endif
    switch (mrRes) {
        case CxMsgBoxT::mrAbort: {
                CxCurrentProcess::exit(0U);
            }
            break;

        default:
        case CxMsgBoxT::mrIgnore: {
                xNA;
            }
            break;

        case CxMsgBoxT::mrRetry: {
                if (true == isActive()) {
                    breakPoint();
                } else {
                    CxMsgBoxT::show(xT("Debugger is not present.\nThe application will be terminated."), xT("xLib"));
                    CxCurrentProcess::exit(0U);
                }
            }
            break;
    }
}
//---------------------------------------------------------------------------
void
CxDebugger::_stdoutPlain(
    const CxErrorReport &a_crpReport
)
{
    xCHECK_DO(false == isEnabled(), return);

    enum EConsoleCmd {
        cmAbort  = xT('a'),
        cmIgnore = xT('i'),
        cmRetry  = xT('r')
    };

    std::tcout << xT("\n####################################################################################################\n");
    std::tcout << a_crpReport.m_sReport;
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
        case cmAbort: {
                std::tcout << xT("Abort...\n\n");  std::tcout.flush();

                CxCurrentProcess::exit(0U);
            }
            break;

        default:
        case cmIgnore: {
                std::tcout << xT("Ignore...\n\n");  std::tcout.flush();
            }
            break;

        case cmRetry: {
                std::tcout << xT("Retry...\n\n");

                if (true == isActive()) {
                    breakPoint();
                } else {
                    std::tcout << xT("\n####################################################################################################\n");
                    std::tcout << xT("CxDebugger\n");
                    std::tcout << xT("\n");
                    std::tcout << xT("OS debugger is not present.\nThe application will be terminated.\n");
                    std::tcout << xT("####################################################################################################\n");
                    std::tcout << xT("\n\n");
                    std::tcout.flush();

                    CxCurrentProcess::exit(0U);
                }
            }
            break;
    }
}
//---------------------------------------------------------------------------
void
CxDebugger::_loggingPlain(
    const CxErrorReport &a_crpReport
)
{
    xCHECK_DO(false == isEnabled(), return);

    //--------------------------------------------------
    // get log file path
    std::tstring_t sFilePath;

    if (true == logPath().empty()) {
        sFilePath = CxPath( CxPath::exe() ).setExt(xT("debug"));
    } else {
        sFilePath = logPath();
    }

    //--------------------------------------------------
    // write to file
    std::FILE *pFile = ::xTFOPEN(sFilePath.c_str(), xT("ab"));
    xTEST_PTR(pFile);

    try {
        const std::tstring_t csMsg = CxString::format(
            xT("\n")
            xT("####################################################################################################\n")
            xT("%s\n")
            xT("####################################################################################################\n"),
            a_crpReport.m_sReport.c_str()
        );

        std::xTFPRINTF(pFile, xT("%s"), csMsg.data());
    }
    catch (...) { }

    xFCLOSE(pFile);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
