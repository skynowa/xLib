/****************************************************************************
* Class name:  CxDebugger
* Description: debugger
* File name:   CxDebugger.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     27.11.2009 16:39:23
*
*****************************************************************************/


#include <xLib/Debug/CxDebugger.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Common/CxSystemInfo.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Sync/CxProcess.h>

#if defined(xOS_WIN)
    #include <xLib/Gui/Win/Dialogs/CxMsgBoxT.h>
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

BOOL    CxDebugger::_ms_bIsEnabled = TRUE;
tString CxDebugger::_ms_sLogPath;

//---------------------------------------------------------------------------
//DONE: bGetEnabled (is debugging enabled)
/*static*/
BOOL
CxDebugger::bGetEnabled() {
    /*DEBUG*/// n/a

    return _ms_bIsEnabled;
}
//---------------------------------------------------------------------------
//DONE: bSetEnabled (set debugging mode on/off)
/*static*/
BOOL
CxDebugger::bSetEnabled(
    const BOOL cbFlag
)
{
    /*DEBUG*/// n/a

    _ms_bIsEnabled = cbFlag;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bIsPresent (is OS debugger presents)
/*static*/
BOOL
CxDebugger::bIsPresent() {
    /*DEBUG*/// n/a

    BOOL bRes = FALSE;

#if defined(xOS_WIN)
    bRes = ::IsDebuggerPresent();
    xCHECK_RET(FALSE == bRes, FALSE);
    ////::CheckRemoteDebuggerPresent()
#elif defined(xOS_LINUX)
    xUNUSED(bRes);
    //TODO: bIsPresent
    ////bRes = std::getenv("xLIB_ENABLE_DEBUGGER");
    ////xCHECK_RET(FALSE == bRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bBreak (attach to OS debugger)
/*static*/
BOOL
CxDebugger::bBreak() {
    /*CHECK*/xCHECK_RET(FALSE == bGetEnabled(), TRUE);
    /*DEBUG*/// n/a

#if defined(xOS_WIN)
    #if defined(xCOMPILER_MS) || defined(xCOMPILER_CODEGEAR)
        _asm {int 3}
    #elif defined(xCOMPILER_MINGW32)
        asm("int 3");
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
//DONE: bSetLogPath (set log file path)
/*static*/
BOOL
CxDebugger::bSetLogPath(
    const tString &csFilePath
)
{
    /*DEBUG*/

    _ms_sLogPath = csFilePath;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetLogPath (get log file path)
/*static*/
tString
CxDebugger::sGetLogPath() {
    /*DEBUG*/

    return _ms_sLogPath;
}
//---------------------------------------------------------------------------
//DONE: bReportMake (make report)
/*static*/
BOOL
CxDebugger::bReportMake(
    const CxReport &crpReport
)
{
    /*DEBUG*/

    //-------------------------------------
    //Never corrupt the last error value
    ULONG _ulLastError = crpReport.ulGetLastError();

    INT iRes = crpReport.rtGetType();
    switch (iRes) {
        case CxReport::rtMsgboxPlain:  { _bMsgboxPlain (crpReport); } break;
        case CxReport::rtMsgboxRtf:    { _bMsgboxRtf   (crpReport); } break;
        case CxReport::rtStdoutPlain:  { _bStdoutPlain (crpReport); } break;
        case CxReport::rtStdoutHtml:   { _bStdoutHtml  (crpReport); } break;
        case CxReport::rtLoggingPlain: { _bLoggingPlain(crpReport); } break;
        case CxReport::rtLoggingHtml:  { _bLoggingHtml (crpReport); } break;

        default:                       { _bStdoutPlain (crpReport); } break;
    }

    //-------------------------------------
    //Never corrupt the last error value
    CxLastError::bSet(_ulLastError);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bTrace (tracing to debugger, std::cout)
/*static*/
BOOL
CxDebugger::bTrace(
    LPCTSTR pcszFormat, ...
)
{
    /*DEBUG*/
    /*CHECK*/xCHECK_RET(FALSE == bGetEnabled(), TRUE);

    tString sRes;

    va_list palArgs;
    va_start(palArgs, pcszFormat);
    sRes = CxString::sFormatV(pcszFormat, palArgs);
    va_end(palArgs);

#if defined(xOS_WIN)
    ::OutputDebugString(sRes.c_str());
    /*CHECK*/// n/a
#elif defined(xOS_LINUX)
    // n/a
#endif

    tcout << sRes << tendl;  tcout.flush();

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bTrace (tracing to debugger, std::cout)
/*static*/
BOOL
CxDebugger::bTrace(
    const tString &csMsg
)
{
    /*DEBUG*/
    /*CHECK*/xCHECK_RET(FALSE == bGetEnabled(), TRUE);

    return bTrace(csMsg.c_str());
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: bBeep (play sound)
/*static*/
BOOL
CxDebugger::bBeep(
    const ULONG culFrequency /*= 800*/,
    const ULONG culDuration  /*= 100*/
) {
    /*DEBUG*/

#if defined(xOS_WIN)
    BOOL bRes = FALSE;

    bRes = ::Beep(culFrequency, culDuration);
    xCHECK_RET(FALSE == bRes, FALSE);
#elif defined(xOS_LINUX)
    INT iRes = - 1;

    #if 1
        iRes = system("xkbbell");
        /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
    #endif

    #if xTEMP_DISABLED
        Display *display = XOpenDisplay(NULL);
        /*DEBUG*/xASSERT_RET(NULL != display, FALSE);

        XKeyboardControl xkc;
        xkc.bell_percent  = 10;
        xkc.bell_pitch    = culFrequency;   /* Hz 800 */
        xkc.bell_duration = culDuration;    /* ms 100 */

        iRes = XChangeKeyboardControl(display, KBBellPercent | KBBellPitch | KBBellDuration, &xkc);
        /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);

        iRes = XBell(display, 0);
        /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);

        iRes = XCloseDisplay(display);
        /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
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
//DONE: CxDebugger ()
CxDebugger::CxDebugger() {

}
//---------------------------------------------------------------------------
//DONE: ~CxDebugger ()
/*virtual*/
CxDebugger::~CxDebugger() {

}
//---------------------------------------------------------------------------
//DONE: _bMsgboxPlain (show MessageBox)
/*static*/
BOOL
CxDebugger::_bMsgboxPlain(
    const CxReport &crpReport
)
{
    /*CHECK*/xCHECK_RET(FALSE == bGetEnabled(), TRUE);
    /*DEBUG*/

#if defined(xOS_WIN)
    CxMsgBoxT::EModalResult mrRes = CxMsgBoxT::iShow(crpReport.sGetReport(), CxPath::sGetExe(), MB_ABORTRETRYIGNORE | MB_ICONSTOP);
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
                    CxMsgBoxT::iShow(xT("Debugger is not present.\nThe application will be terminated."), xT("xLib"), MB_OK | MB_ICONWARNING);
                    CxProcess::bExit(CxProcess::ulGetCurrId(), FALSE);
                }
            }
            break;
    }
#elif defined(xOS_LINUX)
    //TODO: bMsgboxPlain
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: _bMsgboxRtf (show MessageBox or std::out)
/*static*/
BOOL
CxDebugger::_bMsgboxRtf(
    const CxReport &crpReport
)
{
    /*CHECK*/xCHECK_RET(FALSE == bGetEnabled(), TRUE);
    /*DEBUG*/

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

    tcerr << CxString::sFormatNixTerminal( xT("\n####################################################################################################\n"), CxString::fgWhite, TRUE, FALSE, CxString::bgBlack, FALSE );
    tcerr << crpReport.sGetReport();
    tcerr << CxString::sFormatNixTerminal( xT("\n####################################################################################################\n"), CxString::fgWhite, TRUE, FALSE, CxString::bgBlack, FALSE );
    tcerr << xT("\n");
    tcerr << xT("\nAbort (a), Ignore (i), Retry (r): ");
    tcerr.flush();

    EConsoleCmd cmRes = static_cast<EConsoleCmd>( tcin.get() );   tcin.ignore();
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
//DONE: _bStdoutPlain ()
/*static*/
BOOL
CxDebugger::_bStdoutPlain(
    const CxReport &crpReport
)
{
    /*CHECK*/xCHECK_RET(FALSE == bGetEnabled(), TRUE);
    /*DEBUG*/

    //commands from console
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
//DONE: _bStdoutHtml ()
/*static*/
BOOL
CxDebugger::_bStdoutHtml(
    const CxReport &crpReport
)
{
    /*CHECK*/xCHECK_RET(FALSE == bGetEnabled(), TRUE);
    /*DEBUG*/

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
//DONE: _bLoggingPlain (log to file, tracing)
/*static*/
BOOL
CxDebugger::_bLoggingPlain(
    const CxReport &crpReport
)
{
    /*CHECK*/xCHECK_RET(FALSE == bGetEnabled(), TRUE);
    /*DEBUG*/

    #if xTEMP_DISABLED
        _tsetlocale(LC_ALL, xT(""));
    #endif

    //--------------------------------------------------
    //get log file path
    tString sFilePath;

    if (true == _ms_sLogPath.empty()) {
        sFilePath = CxPath::sSetExt(CxPath::sGetExe(), xT("debug"));
    } else {
        sFilePath = sGetLogPath();
    }

    //--------------------------------------------------
    //write to file
    FILE *pFile = _tfopen(sFilePath.c_str(), xT("ab"));
    xCHECK_RET(NULL == pFile, FALSE);

    try {
        //formating
        const tString csMsg = CxString::sFormat(
            xT("\n")
            xT("####################################################################################################\n")
            xT("[%s]\n")
            xT("\n")
            xT("%s\n"),
            CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftDateTime).c_str(),
            crpReport.sGetReport().c_str()
        );

        //tracing
        bTrace(csMsg.data());

        //to file
        _ftprintf(pFile, xT("%s"), csMsg.data());
    }
    catch (...) {}

    xFCLOSE(pFile);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: _bLoggingHtml ()
/*static*/
BOOL
CxDebugger::_bLoggingHtml(
    const CxReport &crpReport
)
{
    /*DEBUG*/

    //TODO: bLoggingHtml

    return TRUE;
}
//---------------------------------------------------------------------------
