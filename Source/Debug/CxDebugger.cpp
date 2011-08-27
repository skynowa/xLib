/**
 * \file  CxDebugger.cpp
 * \brief debugger
 */


#include <xLib/Debug/CxDebugger.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Common/CxSystemInfo.h>
#include <xLib/Common/CxConsole.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxEnvironment.h>
#include <xLib/Sync/CxProcess.h>
#include <xLib/Gui/Dialogs/CxMsgBoxT.h>

#if defined(xOS_WIN)
    #include <xLib/Gui/Win/Dialogs/CxMsgBoxRtf.h>
#elif defined(xOS_LINUX)
    #if xTEMP_DISABLED
        #include <linux/kd.h>   //bBeep
        #include <X11/Xlib.h>   //bBeep -lX11
    #endif
#endif


/****************************************************************************
*    public
*
*****************************************************************************/

BOOL         CxDebugger::_ms_bIsEnabled = TRUE;
std::tstring CxDebugger::_ms_sLogPath;

//---------------------------------------------------------------------------
/*static*/
BOOL
CxDebugger::bGetEnabled() {
    return _ms_bIsEnabled;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDebugger::bSetEnabled(
    const BOOL cbFlag
)
{
    _ms_bIsEnabled = cbFlag;

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDebugger::bIsPresent() {
#if defined(xOS_WIN)
    BOOL bRes = ::IsDebuggerPresent();
    xCHECK_RET(FALSE == bRes, FALSE);

    #if xTODO
        ::CheckRemoteDebuggerPresent()
    #endif
#elif defined(xOS_LINUX)
    std::tstring sRes = CxEnvironment::sGetVar(xT("xLIB_ENABLE_DEBUGGER"));
    xCHECK_RET(FALSE == CxString::bCompareNoCase(xT("yes"), sRes), FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDebugger::bBreak() {
    xCHECK_RET(FALSE == bGetEnabled(), TRUE);

#if defined(xOS_WIN)
    #if defined(xCOMPILER_MS) || defined(xCOMPILER_CODEGEAR)
        _asm {int 3}
    #elif defined(xCOMPILER_MINGW32)
        asm("int $3");
    #else
        abort();
    #endif
#elif defined(xOS_LINUX)
    INT iRes = kill(getpid(), SIGINT);
    xCHECK_RET(- 1 == iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDebugger::bSetLogPath(
    const std::tstring &csFilePath
)
{
    _ms_sLogPath = csFilePath;

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxDebugger::sGetLogPath() {
    return _ms_sLogPath;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDebugger::bReportMake(
    const CxReport &crpReport
)
{
    //-------------------------------------
    //Never corrupt the last error value
    const ULONG culLastError = crpReport.ulGetLastError();

    CxReport::EType rtRes = crpReport.rtGetType();
    switch (rtRes) {
        case CxReport::rtMsgboxPlain:    { _bMsgboxPlain   (crpReport); } break;
        case CxReport::rtMsgboxFormated: { _bMsgboxFormated(crpReport); } break;
        case CxReport::rtStdoutPlain:    { _bStdoutPlain   (crpReport); } break;
        case CxReport::rtStdoutHtml:     { _bStdoutHtml    (crpReport); } break;
        case CxReport::rtLoggingPlain:   { _bLoggingPlain  (crpReport); } break;
        case CxReport::rtLoggingHtml:    { _bLoggingHtml   (crpReport); } break;

        default:                         { _bStdoutPlain   (crpReport); } break;
    }

    //-------------------------------------
    //Never corrupt the last error value
    CxLastError::bSet(culLastError);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDebugger::bTrace(
    LPCTSTR pcszFormat, ...
)
{
    xCHECK_RET(FALSE == bGetEnabled(), TRUE);

    std::tstring sRes;

    va_list palArgs;
    xVA_START(palArgs, pcszFormat);
    sRes = CxString::sFormatV(pcszFormat, palArgs);
    xVA_END(palArgs);

#if defined(xOS_WIN)
    ::OutputDebugString(sRes.c_str());
#elif defined(xOS_LINUX)
    // n/a
#endif

    tcout << sRes << tendl;

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDebugger::bTrace(
    const std::tstring &csMsg
)
{
    xCHECK_RET(FALSE == bGetEnabled(), TRUE);

    return bTrace(csMsg.c_str());
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDebugger::bBeep(
    const ULONG culFrequency /*= 800*/,
    const ULONG culDuration  /*= 100*/
) {
#if defined(xOS_WIN)
    #if xTODO
        BOOL bRes = FALSE;

        bRes = ::Beep(culFrequency, culDuration);
        xCHECK_RET(FALSE == bRes, FALSE);
    #endif
#elif defined(xOS_LINUX)
    #if defined(xOS_FREEBSD)
        //TODO: bBeep
    #else
        #if xTODO
            INT iRes = _tsystem(xT("xkbbell"));
            xASSERT_RET(- 1 == iRes, FALSE);
        #endif
    #endif

    #if xTEMP_DISABLED
        Display *display = XOpenDisplay(NULL);
        xCHECK_RET(NULL == display, FALSE);

        XKeyboardControl xkc;
        xkc.bell_percent  = 10;
        xkc.bell_pitch    = culFrequency;   /* Hz 800 */
        xkc.bell_duration = culDuration;    /* ms 100 */

        iRes = XChangeKeyboardControl(display, KBBellPercent | KBBellPitch | KBBellDuration, &xkc);
        xCHECK_RET(- 1 == iRes, FALSE);

        iRes = XBell(display, 0);
        xCHECK_RET(- 1 == iRes, FALSE);

        iRes = XCloseDisplay(display);
        xCHECK_RET(- 1 == iRes, FALSE);
    #endif
#endif

    return TRUE;
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
BOOL
CxDebugger::_bMsgboxPlain(
    const CxReport &crpReport
)
{
    xCHECK_RET(FALSE == bGetEnabled(), TRUE);

#if defined(xOS_WIN)
    ULONG ulType = MB_ABORTRETRYIGNORE | MB_ICONSTOP;
#elif defined(xOS_LINUX)
    ULONG ulType = 1;
#endif

    CxMsgBoxT::EModalResult mrRes = CxMsgBoxT::iShow(crpReport.sGetReport(), CxPath::sGetExe(), ulType);
    switch (mrRes) {
        case CxMsgBoxT::mrAbort: {
                CxProcess::bExit(CxProcess::ulGetCurrId(), FALSE);
            }
            break;

        default:
        case CxMsgBoxT::mrIgnore: {
                //skip
            }
            break;

        case CxMsgBoxT::mrRetry: {
                if (TRUE == bIsPresent()) {
                    bBreak();
                } else {
                    CxMsgBoxT::iShow(xT("Debugger is not present.\nThe application will be terminated."), xT("xLib"));
                    CxProcess::bExit(CxProcess::ulGetCurrId(), FALSE);
                }
            }
            break;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDebugger::_bMsgboxFormated(
    const CxReport &crpReport
)
{
    xCHECK_RET(FALSE == bGetEnabled(), TRUE);

#if defined(xOS_WIN)
    //-------------------------------------
    //show message
    CxMsgBoxRtf::EModalResult mrRes = CxMsgBoxRtf::iShow(NULL, crpReport.sGetReport(), CxPath::sGetExe());
    switch (mrRes) {
        case CxMsgBoxRtf::mrAbort: {
                CxProcess::bExit(CxProcess::ulGetCurrId(), FALSE);
            }
            break;

        default:
        case CxMsgBoxRtf::mrIgnore: {
                //skip
            }
            break;

        case CxMsgBoxRtf::mrRetry: {
                if (TRUE == bIsPresent()) {
                    bBreak();
                } else {
                    CxMsgBoxT::iShow(xT("Debugger is not present.\nThe application will be terminated."), xT("xLib"), MB_OK | MB_ICONWARNING);
                    CxProcess::bExit(CxProcess::ulGetCurrId(), FALSE);
                }
            }
            break;
    }
#elif defined(xOS_LINUX)
    enum EConsoleCmd {
        cmAbort  = xT('a'),
        cmIgnore = xT('i'),
        cmRetry  = xT('r')
    };

    tcerr << CxConsole().bSetTextColor( xT("\n####################################################################################################\n"), CxConsole::fgWhite, TRUE, FALSE, CxConsole::bgBlack, FALSE );
    tcerr << crpReport.sGetReport();
    tcerr << CxConsole().bSetTextColor( xT("\n####################################################################################################\n"), CxConsole::fgWhite, TRUE, FALSE, CxConsole::bgBlack, FALSE );
    tcerr << xT("\n");
    tcerr << xT("\nAbort (a), Ignore (i), Retry (r): ");
    tcerr.flush();

    EConsoleCmd cmRes = static_cast<EConsoleCmd>( tcin.get() );   tcin.ignore();
    ////EConsoleCmd cmRes = cmIgnore;
    switch (cmRes) {
        case cmAbort: {
                tcerr << xT("Abort...\n\n");  tcerr.flush();

                CxProcess::bExit(CxProcess::ulGetCurrId(), FALSE);
            }
            break;

        default:
        case cmIgnore: {
                //skip
                tcerr << xT("Ignore...\n\n");  tcerr.flush();
            }
            break;

        case cmRetry: {
                tcerr << xT("Retry...\n\n");

                if (TRUE == bIsPresent()) {
                    bBreak();
                } else {
                    tcerr << xT("\n####################################################################################################\n");
                    tcerr << xT("CxDebugger\n");
                    tcerr << xT("\n");
                    tcerr << xT("OS debugger is not present.\nThe application will be terminated.\n");
                    tcerr << xT("####################################################################################################\n");
                    tcerr << xT("\n\n");
                    tcerr.flush();

                    CxProcess::bExit(CxProcess::ulGetCurrId(), FALSE);
                }
            }
            break;
    }
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDebugger::_bStdoutPlain(
    const CxReport &crpReport
)
{
    xCHECK_RET(FALSE == bGetEnabled(), TRUE);

    enum EConsoleCmd {
        cmAbort  = xT('a'),
        cmIgnore = xT('i'),
        cmRetry  = xT('r')
    };

    tcout << xT("\n####################################################################################################\n");
    tcout << crpReport.sGetReport();
    tcout << xT("\n####################################################################################################\n");
    tcout << xT("\n");
    tcout << xT("\nAbort (a), Ignore (i), Retry (r): ");
    tcout.flush();

    EConsoleCmd cmRes = static_cast<EConsoleCmd>( tcin.get() );   tcin.ignore();
    switch (cmRes) {
        case cmAbort: {
                tcout << xT("Abort...\n\n");  tcout.flush();

                CxProcess::bExit(CxProcess::ulGetCurrId(), FALSE);
            }
            break;

        default:
        case cmIgnore: {
                //skip
                tcout << xT("Ignore...\n\n");  tcout.flush();
            }
            break;

        case cmRetry: {
                tcout << xT("Retry...\n\n");

                if (TRUE == bIsPresent()) {
                    bBreak();
                } else {
                    tcout << xT("\n####################################################################################################\n");
                    tcout << xT("CxDebugger\n");
                    tcout << xT("\n");
                    tcout << xT("OS debugger is not present.\nThe application will be terminated.\n");
                    tcout << xT("####################################################################################################\n");
                    tcout << xT("\n\n");
                    tcout.flush();

                    CxProcess::bExit(CxProcess::ulGetCurrId(), FALSE);
                }
            }
            break;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDebugger::_bStdoutHtml(
    const CxReport &crpReport
)
{
    xCHECK_RET(FALSE == bGetEnabled(), TRUE);

    enum EConsoleCmd {
        cmAbort  = xT('a'),
        cmIgnore = xT('i'),
        cmRetry  = xT('r')
    };

    tcout << xT("<pre>");
    tcout << xT("\n####################################################################################################\n");
    tcout << crpReport.sGetReport();
    tcout << xT("\n####################################################################################################\n");
    tcout << xT("\n");
    tcout << xT("\nAbort (a), Ignore (i), Retry (r): ");
    tcout.flush();

    EConsoleCmd cmRes = static_cast<EConsoleCmd>( tcin.get() );   tcin.ignore();
    switch (cmRes) {
        case cmAbort: {
                tcout << xT("Abort...\n\n");  tcout.flush();

                CxProcess::bExit(CxProcess::ulGetCurrId(), FALSE);
            }
            break;

        default:
        case cmIgnore: {
                //skip
                tcout << xT("Ignore...\n\n");  tcout.flush();
            }
            break;

        case cmRetry: {
                tcout << xT("Retry...\n\n");

                if (TRUE == bIsPresent()) {
                    bBreak();
                } else {
                    tcout << xT("\n####################################################################################################\n");
                    tcout << xT("CxDebugger\n");
                    tcout << xT("\n");
                    tcout << xT("OS debugger is not present.\nThe application will be terminated.\n");
                    tcout << xT("####################################################################################################\n");
                    tcout << xT("\n\n");
                    tcout.flush();

                    CxProcess::bExit(CxProcess::ulGetCurrId(), FALSE);
                }
            }
            break;
    }

    tcout << xT("</pre>");  tcout.flush();

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDebugger::_bLoggingPlain(
    const CxReport &crpReport
)
{
    xCHECK_RET(FALSE == bGetEnabled(), TRUE);

    //--------------------------------------------------
    //get log file path
    std::tstring sFilePath;

    if (true == sGetLogPath().empty()) {
        sFilePath = CxPath::sSetExt(CxPath::sGetExe(), xT("debug"));
    } else {
        sFilePath = sGetLogPath();
    }

    //--------------------------------------------------
    //write to file
    FILE *pFile = _tfopen(sFilePath.c_str(), xT("ab"));
    xCHECK_RET(NULL == pFile, FALSE);

    try {
        const std::tstring csMsg = CxString::sFormat(
            xT("\n")
            xT("####################################################################################################\n")
            xT("%s\n")
            xT("####################################################################################################\n"),
            crpReport.sGetReport().c_str()
        );

        _ftprintf(pFile, xT("%s"), csMsg.data());
    }
    catch (...) { }

    xFCLOSE(pFile);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDebugger::_bLoggingHtml(
    const CxReport &crpReport
)
{
    //TODO: bLoggingHtml

    return TRUE;
}
//---------------------------------------------------------------------------
