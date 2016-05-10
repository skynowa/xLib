/**
 * \file  Debugger.inl
 * \brief debugger
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Debugger.h"
#endif

#include <xLib/Core/Char.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/DateTime.h>
#include <xLib/System/SystemInfo.h>
#include <xLib/System/Console.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Log/Trace.h>
#include <xLib/IO/Path.h>
#include <xLib/Gui/MsgBox.h>
#include <xLib/System/Environment.h>

#if   xENV_WIN
    #include "Platform/Win/Debugger_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Debugger_unix.inl"

    #if   xENV_LINUX
        #include "Platform/Linux/Debugger_linux.inl"
    #elif xENV_BSD
        #include "Platform/Bsd/Debugger_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/Debugger_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, debug)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Debugger::Debugger() :
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
xINLINE bool_t
Debugger::isEnabled() const
{
    return _isEnabled;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Debugger::setEnabled(
    cbool_t &a_flag
)
{
    _isEnabled = a_flag;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Debugger::isActive() const
{
    return _isActive_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Debugger::coreDumpsEnable(
    cbool_t &a_flag
)
{
    xTEST_NA(a_flag);

    bool_t isEnable = false;

    _coreDumpsEnable_impl(a_flag, &isEnable);

    xCHECK_DO(!isEnable, Trace() << xT("xLib: Debugger::coreDumpsEnable() - n/a"));
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Debugger::breakPoint() const
{
    xCHECK_DO(!isEnabled(), return);

    _breakPoint_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Debugger::setLogPath(
    std::ctstring_t &a_filePath
)
{
    _logPath = a_filePath;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Debugger::logPath() const
{
    return _logPath;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Debugger::reportMake(
    const ErrorReport &a_report
)
{
    // never corrupt last error value
    culong_t nativeError = NativeError::get();

    switch (a_report.type()) {
    case ErrorReport::rtMsgbox:
        _msgboxPlain(a_report);
        break;
    case ErrorReport::rtStdout:
        _stdoutPlain(a_report);
        break;
    case ErrorReport::rtLog:
        _loggingPlain(a_report);
        break;
    case ErrorReport::rtStdoutLog:
        _stdoutPlain(a_report);
        _loggingPlain(a_report);
        break;
    case ErrorReport::rtException:
        throw Exception() << a_report.toString();
        break;
    default:
        _stdoutPlain(a_report);
        break;
    }

    // never corrupt last error value
    NativeError::set(nativeError);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
Debugger::_msgboxPlain(
    const ErrorReport &a_report
) const
{
    xCHECK_DO(!isEnabled(), return);

    MsgBox::ExModalResult mrRv;

#if xOPTION_DEBUG_DIALOG
    mrRv = MsgBox().show(a_report.toString(), xT(""), MsgBox::tpAbortRetryIgnore);
#else
    xUNUSED(a_report);

    mrRv = MsgBox::mrIgnore;
#endif

    switch (mrRv) {
    case MsgBox::mrAbort:
        (void_t)::exit(EXIT_FAILURE);
        break;
    default:
    case MsgBox::mrIgnore:
        xNA;
        break;
    case MsgBox::mrRetry:
        if (isActive()) {
            breakPoint();
        } else {
            MsgBox::ExModalResult nrRv = MsgBox().show(xT("Debugger is not present.\n"
                "The application will be terminated."), xT("xLib"));
            xUNUSED(nrRv);
            (void_t)::exit(EXIT_FAILURE);
        }
        break;
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Debugger::_stdoutPlain(
    const ErrorReport &a_report
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
    std::tcout << Format::str(xT("\nAbort ({}), Ignore ({}), Retry ({}): "),
        tchar_t(cmAbort), tchar_t(cmIgnore), tchar_t(cmRetry));
    std::tcout.flush();

#if xOPTION_DEBUG_DIALOG
    ctchar_t    cmd = static_cast<ctchar_t>( std::tcin.get() );   std::tcin.ignore();
    EConsoleCmd cmRv = static_cast<EConsoleCmd>( Char(cmd).toLower() );
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
            std::tcout << xT("Debugger\n");
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
xINLINE void_t
Debugger::_loggingPlain(
    const ErrorReport &a_report
) const
{
    xCHECK_DO(!isEnabled(), return);

    // get log file path
    std::tstring_t filePath;

    if (logPath().empty()) {
        filePath = Path( Path::exe() ).setExt(xT("debug"));
    } else {
        filePath = logPath();
    }

    // write to file
    try {
        std::tofstream_t ofs( xT2A(filePath).c_str() );
        xCHECK_DO(ofs.fail(), return);

        std::ctstring_t msg = Format::str(
            xT("\n")
            xT("####################################################################################################\n")
            xT("{}\n")
            xT("####################################################################################################\n"),
            a_report.toString()
        );

        ofs << msg;
    }
    catch (...) {
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
