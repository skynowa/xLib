/****************************************************************************
* Class name:  CxDebugger
* Description: отладка кода
* File name:   CxDebugger.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     27.11.2009 16:39:23
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Debug/CxDebugger.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Common/CxSystemInfo.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Sync/CxProcess.h>

#if defined(xOS_WIN)
    #include <xLib/Gui/Win/Dialogs/CxMsgBoxRtf.h>
#elif defined(xOS_LINUX)

#endif


/****************************************************************************
*	public
*
*****************************************************************************/

BOOL CxDebugger::_ms_bIsEnabled = TRUE;

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
CxDebugger::bSetEnabled(BOOL bFlag) {
    /*DEBUG*/// n/a

    _ms_bIsEnabled = bFlag;

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
    //TODO: xOS_LINUX
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
    _asm {int 3}
    ////asm {"int 3"}
#elif defined(xOS_LINUX)
    INT iRes = kill(getpid(), SIGINT);
    xCHECK_RET(- 1 == iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bReportMake ()
/*static*/
BOOL
CxDebugger::bReportMake(const CxReport &crpReport) {
    /*DEBUG*/

    //-------------------------------------
    //Never corrupt the last error value
    ULONG _ulLastError = crpReport.ulGetLastError();

    INT iRes = crpReport.rtGetType();
	switch (iRes) {
        case CxReport::rtMsgboxPlain:  { bMsgboxPlain (crpReport); } break;
        case CxReport::rtMsgboxRtf:    { bMsgboxRtf   (crpReport); } break;
        case CxReport::rtStdoutPlain:  { bStdoutPlain (crpReport); } break;
        case CxReport::rtStdoutHtml:   { bStdoutHtml  (crpReport); } break;
        case CxReport::rtLoggingPlain: { bLoggingPlain(crpReport); } break;
        case CxReport::rtLoggingHtml:  { bLoggingHtml (crpReport); } break;

    	default:                       { bStdoutPlain (crpReport); } break;
    }

    //-------------------------------------
    //Never corrupt the last error value
    CxLastError::bSet(_ulLastError);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bTrace (tracing)
/*static*/
BOOL
CxDebugger::bTrace(LPCTSTR pcszFormat, ...) {
    /*DEBUG*/
    /*CHECK*/xCHECK_RET(FALSE == bGetEnabled(), TRUE);

    tString sRes;

    va_list palArgs = NULL;
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
//DONE: bTrace (tracing)
/*static*/
BOOL
CxDebugger::bTrace(const tString &csMsg) {
    /*DEBUG*/
    /*CHECK*/xCHECK_RET(FALSE == bGetEnabled(), TRUE);

    return bTrace(csMsg.c_str());
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------



/****************************************************************************
*	private
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
//DONE: bMsgboxPlain (show MessageBox)
/*static*/
BOOL
CxDebugger::bMsgboxPlain(const CxReport &crpReport) {
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
    //TODO: xOS_LINUX
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bMsgboxRtf (show MessageBox or std::out)
/*static*/
BOOL
CxDebugger::bMsgboxRtf(const CxReport &crpReport) {
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
    //commands from console
    enum ECmd {
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

    ECmd cmRes = static_cast<ECmd>( tcin.get() );   tcin.ignore();
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
//DONE: bStdoutPlain ()
/*static*/
BOOL
CxDebugger::bStdoutPlain(const CxReport &crpReport) {
    /*CHECK*/xCHECK_RET(FALSE == bGetEnabled(), TRUE);
    /*DEBUG*/

    //commands from console
    enum ECmd {
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

    ECmd cmRes = static_cast<ECmd>( tcin.get() );   tcin.ignore();
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
//DONE: bStdoutHtml ()
/*static*/
BOOL
CxDebugger::bStdoutHtml(const CxReport &crpReport) {
    /*CHECK*/xCHECK_RET(FALSE == bGetEnabled(), TRUE);
    /*DEBUG*/

    //commands from console
    enum ECmd {
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

    ECmd cmRes = static_cast<ECmd>( tcin.get() );   tcin.ignore();
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
//DONE: bLoggingPlain (log to file)
/*static*/
BOOL
CxDebugger::bLoggingPlain(const CxReport &crpReport) {
    /*CHECK*/xCHECK_RET(FALSE == bGetEnabled(), TRUE);
    /*DEBUG*/

    #if xTEMP_DISABLED
        _tsetlocale(LC_ALL, xT(""));
    #endif

    tString sFilePath = CxPath::sSetExt(CxPath::sGetExe(), xT("debug"));

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

        //in file
        _ftprintf(pFile, xT("%s"), csMsg.data());
    }
    catch (...) {}

    xFCLOSE(pFile);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bLoggingHtml ()
/*static*/
BOOL
CxDebugger::bLoggingHtml(const CxReport &crpReport) {
    /*DEBUG*/

    //TODO:

    return TRUE;
}
//---------------------------------------------------------------------------
