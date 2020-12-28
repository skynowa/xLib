/**
 * \file  Debugger.inl
 * \brief debugger
 */


#include "Debugger.h"

#include <xLib/Core/Char.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/DateTime.h>
#include <xLib/System/SystemInfo.h>
#include <xLib/System/Console.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Log/Trace.h>
#include <xLib/Fs/PathExe.h>
#include <xLib/Ui/MsgBox.h>
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


namespace xl::debug
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Debugger::isEnabled() const
{
    return _isEnabled;
}
//-------------------------------------------------------------------------------------------------
void_t
Debugger::setEnabled(
    cbool_t &a_flag
)
{
    _isEnabled = a_flag;
}
//-------------------------------------------------------------------------------------------------
bool_t
Debugger::isActive() const
{
    return _isActive_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
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
void_t
Debugger::breakPoint() const
{
    xCHECK_DO(!isEnabled(), return);

    _breakPoint_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Debugger::setLogPath(
    std::ctstring_t &a_filePath
)
{
    _logPath = a_filePath;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Debugger::logPath() const
{
    return _logPath;
}
//-------------------------------------------------------------------------------------------------
void_t
Debugger::reportMake(
    const ErrorReport &a_report
) const
{
    // never corrupt last error value
    culong_t nativeError = NativeError::get();

    switch (a_report.type()) {
    case ErrorReport::Type::Msgbox:
        _msgboxPlain(a_report);
        break;
    case ErrorReport::Type::Stdout:
        _stdoutPlain(a_report);
        break;
    case ErrorReport::Type::Log:
        _loggingPlain(a_report);
        break;
    case ErrorReport::Type::StdoutLog:
        _stdoutPlain(a_report);
        _loggingPlain(a_report);
        break;
    case ErrorReport::Type::Exception:
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
void_t
Debugger::_msgboxPlain(
    const ErrorReport &a_report
) const
{
    xCHECK_DO(!isEnabled(), return);

    MsgBox msgBox;
    MsgBox::ModalResult mrRv = msgBox.show(a_report.toString(), xT("xLib"),
    	MsgBox::Type::AbortRetryIgnore);
    switch (mrRv) {
    case MsgBox::ModalResult::Abort:
        (void_t)::exit(EXIT_FAILURE);
        break;
    default:
    case MsgBox::ModalResult::Ignore:
        xNA;
        break;
    case MsgBox::ModalResult::Retry:
        if ( isActive() ) {
            breakPoint();
        } else {
            MsgBox::ModalResult nrRv = MsgBox().show(xT("Debugger is not present.\n"
                "The application will be terminated."), xT("xLib"));
            xUNUSED(nrRv);
            (void_t)::exit(EXIT_FAILURE);
        }
        break;
    }
}
//-------------------------------------------------------------------------------------------------
void_t
Debugger::_stdoutPlain(
    const ErrorReport &a_report
) const
{
    xCHECK_DO(!isEnabled(), return);

    Console console;
    Console::ModalResult mrRv = console.msgBox(a_report.toString(), xT("xLib"), 0);
    switch (mrRv) {
    case Console::ModalResult::Abort:
        (void_t)::exit(EXIT_FAILURE);
        break;
    case Console::ModalResult::Ignore:
        break;
    case Console::ModalResult::Retry:
        if ( isActive() ) {
            breakPoint();
        } else {
            (void_t)console.msgBox(xT("OS debugger is not present.\nThe application will be terminated."), xT("xLib"), 0);

            (void_t)::exit(EXIT_FAILURE);
        }

        break;
    default:
        break;
    }
}
//-------------------------------------------------------------------------------------------------
void_t
Debugger::_loggingPlain(
    const ErrorReport &a_report
) const
{
    xCHECK_DO(!isEnabled(), return);

    // get log file path
    std::tstring_t filePath;

    if ( logPath().empty() ) {
        filePath = PathExe().setExt(xT("debug")).str();
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
            xT(" xLib\n")
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

} // namespace
