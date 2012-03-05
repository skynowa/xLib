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

#if xOS_ENV_WIN
    #include <xLib/Gui/Win/Dialogs/CxMsgBoxRtf.h>
#elif xOS_ENV_UNIX
    #if xTEMP_DISABLED
        #include <linux/kd.h>   //bBeep
        #include <X11/Xlib.h>   //bBeep -lX11
    #endif
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

bool           CxDebugger::_ms_bIsEnabled = true;
std::tstring_t CxDebugger::_ms_sLogPath;

//---------------------------------------------------------------------------
/*static*/
bool
CxDebugger::bGetEnabled() {
    return _ms_bIsEnabled;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDebugger::bSetEnabled(
    const bool cbFlag
)
{
    _ms_bIsEnabled = cbFlag;

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDebugger::bIsPresent() {
#if xOS_ENV_WIN
    BOOL blRes = ::IsDebuggerPresent();
    xCHECK_RET(FALSE != blRes, true);

    BOOL blIsRemoteDebuggerPresent = FALSE;

    blRes = ::CheckRemoteDebuggerPresent(CxCurrentProcess::hGetHandle(), &blIsRemoteDebuggerPresent);
    xCHECK_RET(FALSE == blRes || FALSE == blIsRemoteDebuggerPresent, false);
#elif xOS_ENV_UNIX
    std::tstring_t sRes = CxEnvironment::sGetVar(xT("xLIB_ENABLE_DEBUGGER"));
    xCHECK_RET(false == CxString::bCompareNoCase(xT("yes"), sRes), false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDebugger::bIsDebugBuild() {
    bool bRes = false;

#if xBUILD_DEBUG
    bRes = true;
#else
    bRes = false;
#endif

    return bRes;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDebugger::bBreak() {
    xCHECK_RET(false == bGetEnabled(), true);

#if xOS_ENV_WIN
    #if xCOMPILER_MS || xCOMPILER_CODEGEAR
        _asm {int 3}
    #elif xCOMPILER_MINGW32
        asm("int $3");
    #else
        ::abort();
    #endif
#elif xOS_ENV_UNIX
    int iRes = ::kill(CxCurrentProcess::ulGetId(), SIGALRM);
    xCHECK_RET(- 1 == iRes, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDebugger::bSetLogPath(
    const std::tstring_t &csFilePath
)
{
    _ms_sLogPath = csFilePath;

    return true;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxDebugger::sGetLogPath() {
    return _ms_sLogPath;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDebugger::bReportMake(
    const CxErrorReport &crpReport
)
{
    //-------------------------------------
    //never corrupt the last error value
    const ulong_t culLastError = crpReport.ulGetLastError();

    CxErrorReport::EType rtRes = crpReport.rtGetType();
    switch (rtRes) {
        case CxErrorReport::rtMsgboxPlain:    { _bMsgboxPlain   (crpReport); } break;
        case CxErrorReport::rtMsgboxFormated: { _bMsgboxFormated(crpReport); } break;
        case CxErrorReport::rtStdoutPlain:    { _bStdoutPlain   (crpReport); } break;
        case CxErrorReport::rtStdoutHtml:     { _bStdoutHtml    (crpReport); } break;
        case CxErrorReport::rtLoggingPlain:   { _bLoggingPlain  (crpReport); } break;
        case CxErrorReport::rtLoggingHtml:    { _bLoggingHtml   (crpReport); } break;

        default:                         { _bStdoutPlain   (crpReport); } break;
    }

    //-------------------------------------
    //never corrupt the last error value
    (void)CxLastError::bSet(culLastError);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDebugger::bTrace(
    const tchar_t *pcszFormat, ...
)
{
    xCHECK_RET(false == bGetEnabled(), true);

    std::tstring_t sRes;

    va_list palArgs;
    xVA_START(palArgs, pcszFormat);
    sRes = CxString::sFormatV(pcszFormat, palArgs);
    xVA_END(palArgs);

#if xOS_ENV_WIN
    (void)::OutputDebugString(sRes.c_str());
#elif xOS_ENV_UNIX
    // n/a
#endif

    std::tcout << sRes << std::endl;

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDebugger::bTrace(
    const std::tstring_t &csMsg
)
{
    xCHECK_RET(false == bGetEnabled(), true);

    return bTrace(csMsg.c_str());
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDebugger::bBeep(
    const ulong_t culFrequency /*= 800*/,
    const ulong_t culDuration  /*= 100*/
)
{
#if xOS_ENV_WIN
    #if xTODO
        bool bRes = ::Beep(culFrequency, culDuration);
        xCHECK_RET(false == bRes, false);
    #endif
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        #if xTODO
            int iRes = std::xTSYSTEM(xT("xkbbell"));
            xASSERT_RET(- 1 == iRes, false);
        #endif
    #elif xOS_FREEBSD
        //TODO: bBeep
    #endif

    #if xTEMP_DISABLED
        Display *display = ::XOpenDisplay(NULL);
        xCHECK_RET(NULL == display, false);

        XKeyboardControl xkc;
        xkc.bell_percent  = 10;
        xkc.bell_pitch    = culFrequency;   /* Hz 800 */
        xkc.bell_duration = culDuration;    /* ms 100 */

        iRes = ::XChangeKeyboardControl(display, KBBellPercent | KBBellPitch | KBBellDuration, &xkc);
        xCHECK_RET(- 1 == iRes, false);

        iRes = ::XBell(display, 0);
        xCHECK_RET(- 1 == iRes, false);

        iRes = ::XCloseDisplay(display);
        xCHECK_RET(- 1 == iRes, false);
    #endif
#endif

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxDebugger::CxDebugger() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxDebugger::~CxDebugger() {

}
//---------------------------------------------------------------------------
/*static*/
bool
CxDebugger::_bMsgboxPlain(
    const CxErrorReport &crpReport
)
{
    xCHECK_RET(false == bGetEnabled(), true);

#if xOS_ENV_WIN
    ulong_t ulType = MB_ABORTRETRYIGNORE | MB_ICONSTOP;
#elif xOS_ENV_UNIX
    ulong_t ulType = 1UL;
#endif

    CxMsgBoxT::EModalResult mrRes = CxMsgBoxT::iShow(crpReport.sGetReport(), CxPath::sGetExe(), ulType);
    switch (mrRes) {
        case CxMsgBoxT::mrAbort: {
                CxProcess::bExit(CxCurrentProcess::ulGetId(), false);
            }
            break;

        default:
        case CxMsgBoxT::mrIgnore: {
                // n/a
            }
            break;

        case CxMsgBoxT::mrRetry: {
                if (true == bIsPresent()) {
                    (void)bBreak();
                } else {
                    CxMsgBoxT::iShow(xT("Debugger is not present.\nThe application will be terminated."), xT("xLib"));
                    CxProcess::bExit(CxCurrentProcess::ulGetId(), false);
                }
            }
            break;
    }

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDebugger::_bMsgboxFormated(
    const CxErrorReport &crpReport
)
{
    xCHECK_RET(false == bGetEnabled(), true);

#if xOS_ENV_WIN
    //-------------------------------------
    //show message
    CxMsgBoxRtf::EModalResult mrRes = CxMsgBoxRtf::iShow(NULL, crpReport.sGetReport(), CxPath::sGetExe());
    switch (mrRes) {
        case CxMsgBoxRtf::mrAbort: {
                CxProcess::bExit(CxCurrentProcess::ulGetId(), false);
            }
            break;

        default:
        case CxMsgBoxRtf::mrIgnore: {
                // n/a
            }
            break;

        case CxMsgBoxRtf::mrRetry: {
                if (true == bIsPresent()) {
                    (void)bBreak();
                } else {
                    CxMsgBoxT::iShow(xT("Debugger is not present.\nThe application will be terminated."), xT("xLib"), MB_OK | MB_ICONWARNING);
                    CxProcess::bExit(CxCurrentProcess::ulGetId(), false);
                }
            }
            break;
    }
#elif xOS_ENV_UNIX
    enum EConsoleCmd {
        cmAbort  = xT('a'),
        cmIgnore = xT('i'),
        cmRetry  = xT('r')
    };

    std::tcerr << CxConsole().bSetTextColor( xT("\n####################################################################################################\n"), CxConsole::fgWhite, true, false, CxConsole::bgBlack, false );
    std::tcerr << crpReport.sGetReport();
    std::tcerr << CxConsole().bSetTextColor( xT("\n####################################################################################################\n"), CxConsole::fgWhite, true, false, CxConsole::bgBlack, false );
    std::tcerr << xT("\n");
    std::tcerr << xT("\nAbort (a), Ignore (i), Retry (r): ");
    std::tcerr.flush();

    #if 1
        EConsoleCmd cmRes = static_cast<EConsoleCmd>( std::tcin.get() );   std::tcin.ignore();
    #else
        EConsoleCmd cmRes = cmIgnore;
    #endif
    switch (cmRes) {
        case cmAbort: {
                std::tcerr << xT("Abort...\n\n");  std::tcerr.flush();

                CxProcess::bExit(CxCurrentProcess::ulGetId(), false);
            }
            break;

        default:
        case cmIgnore: {
                std::tcerr << xT("Ignore...\n\n");  std::tcerr.flush();
            }
            break;

        case cmRetry: {
                std::tcerr << xT("Retry...\n\n");

                if (true == bIsPresent()) {
                    (void)bBreak();
                } else {
                    std::tcerr << xT("\n####################################################################################################\n");
                    std::tcerr << xT("CxDebugger\n");
                    std::tcerr << xT("\n");
                    std::tcerr << xT("OS debugger is not present.\nThe application will be terminated.\n");
                    std::tcerr << xT("####################################################################################################\n");
                    std::tcerr << xT("\n\n");
                    std::tcerr.flush();

                    CxProcess::bExit(CxCurrentProcess::ulGetId(), false);
                }
            }
            break;
    }
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDebugger::_bStdoutPlain(
    const CxErrorReport &crpReport
)
{
    xCHECK_RET(false == bGetEnabled(), true);

    enum EConsoleCmd {
        cmAbort  = xT('a'),
        cmIgnore = xT('i'),
        cmRetry  = xT('r')
    };

    std::tcout << xT("\n####################################################################################################\n");
    std::tcout << crpReport.sGetReport();
    std::tcout << xT("\n####################################################################################################\n");
    std::tcout << xT("\n");
    std::tcout << xT("\nAbort (a), Ignore (i), Retry (r): ");
    std::tcout.flush();

    EConsoleCmd cmRes = static_cast<EConsoleCmd>( std::tcin.get() );   std::tcin.ignore();
    switch (cmRes) {
        case cmAbort: {
                std::tcout << xT("Abort...\n\n");  std::tcout.flush();

                CxProcess::bExit(CxCurrentProcess::ulGetId(), false);
            }
            break;

        default:
        case cmIgnore: {
                std::tcout << xT("Ignore...\n\n");  std::tcout.flush();
            }
            break;

        case cmRetry: {
                std::tcout << xT("Retry...\n\n");

                if (true == bIsPresent()) {
                    (void)bBreak();
                } else {
                    std::tcout << xT("\n####################################################################################################\n");
                    std::tcout << xT("CxDebugger\n");
                    std::tcout << xT("\n");
                    std::tcout << xT("OS debugger is not present.\nThe application will be terminated.\n");
                    std::tcout << xT("####################################################################################################\n");
                    std::tcout << xT("\n\n");
                    std::tcout.flush();

                    CxProcess::bExit(CxCurrentProcess::ulGetId(), false);
                }
            }
            break;
    }

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDebugger::_bStdoutHtml(
    const CxErrorReport &crpReport
)
{
    xCHECK_RET(false == bGetEnabled(), true);

    enum EConsoleCmd {
        cmAbort  = xT('a'),
        cmIgnore = xT('i'),
        cmRetry  = xT('r')
    };

    std::tcout << xT("<pre>");
    std::tcout << xT("\n####################################################################################################\n");
    std::tcout << crpReport.sGetReport();
    std::tcout << xT("\n####################################################################################################\n");
    std::tcout << xT("\n");
    std::tcout << xT("\nAbort (a), Ignore (i), Retry (r): ");
    std::tcout.flush();

    EConsoleCmd cmRes = static_cast<EConsoleCmd>( std::tcin.get() );   std::tcin.ignore();
    switch (cmRes) {
        case cmAbort: {
                std::tcout << xT("Abort...\n\n");  std::tcout.flush();

                CxProcess::bExit(CxCurrentProcess::ulGetId(), false);
            }
            break;

        default:
        case cmIgnore: {
                std::tcout << xT("Ignore...\n\n");  std::tcout.flush();
            }
            break;

        case cmRetry: {
                std::tcout << xT("Retry...\n\n");

                if (true == bIsPresent()) {
                    (void)bBreak();
                } else {
                    std::tcout << xT("\n####################################################################################################\n");
                    std::tcout << xT("CxDebugger\n");
                    std::tcout << xT("\n");
                    std::tcout << xT("OS debugger is not present.\nThe application will be terminated.\n");
                    std::tcout << xT("####################################################################################################\n");
                    std::tcout << xT("\n\n");
                    std::tcout.flush();

                    CxProcess::bExit(CxCurrentProcess::ulGetId(), false);
                }
            }
            break;
    }

    std::tcout << xT("</pre>");  std::tcout.flush();

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDebugger::_bLoggingPlain(
    const CxErrorReport &crpReport
)
{
    xCHECK_RET(false == bGetEnabled(), true);

    //--------------------------------------------------
    //get log file path
    std::tstring_t sFilePath;

    if (true == sGetLogPath().empty()) {
        sFilePath = CxPath::sSetExt(CxPath::sGetExe(), xT("debug"));
    } else {
        sFilePath = sGetLogPath();
    }

    //--------------------------------------------------
    //write to file
    std::FILE *pFile = std::xTFOPEN(sFilePath.c_str(), xT("ab"));
    xCHECK_RET(NULL == pFile, false);

    try {
        const std::tstring_t csMsg = CxString::sFormat(
            xT("\n")
            xT("####################################################################################################\n")
            xT("%s\n")
            xT("####################################################################################################\n"),
            crpReport.sGetReport().c_str()
        );

        std::xTFPRINTF(pFile, xT("%s"), csMsg.data());
    }
    catch (...) { }

    xFCLOSE(pFile);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDebugger::_bLoggingHtml(
    const CxErrorReport &crpReport
)
{
    //TODO: bLoggingHtml

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
