/**
 * \file  CxDebugger.inl
 * \brief debugger
 */


#include <xLib/Core/CxDateTime.h>
#include <xLib/System/CxSystemInfo.h>
#include <xLib/System/CxConsole.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Gui/CxMsgBox.h>
#include <xLib/System/CxEnvironment.h>

#if   xENV_WIN
    #include "Platform/Win/CxDebugger_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxDebugger_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxDebugger_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxDebugger_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, debug)

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
    return _isActive_impl();
}
//-------------------------------------------------------------------------------------------------
inline void
CxDebugger::coreDumpsEnable(
    cbool_t &a_flag
)
{
    xTEST_NA(a_flag);

    bool_t isEnable = false;

    _coreDumpsEnable_impl(a_flag, &isEnable);

    xCHECK_DO(!isEnable, CxTrace() << xT("xLib: CxDebugger::coreDumpsEnable() - n/a"));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDebugger::breakPoint() const
{
    xCHECK_DO(!isEnabled(), return);

    _breakPoint_impl();
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

#if xHAVE_DEBUG_DIALOG
    mrRv = CxMsgBox().show(a_report.toString(), xT(""), CxMsgBox::tpAbortRetryIgnore);
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

#if xHAVE_DEBUG_DIALOG
    ctchar_t    cmd = static_cast<ctchar_t>( std::tcin.get() );   std::tcin.ignore();
    EConsoleCmd cmRv = static_cast<EConsoleCmd>( CxChar(cmd).toLower() );
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

    // get log file path
    std::tstring_t filePath;

    if (logPath().empty()) {
        filePath = CxPath( CxPath::exe() ).setExt(xT("debug"));
    } else {
        filePath = logPath();
    }

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

xNAMESPACE_END2(xlib, debug)
