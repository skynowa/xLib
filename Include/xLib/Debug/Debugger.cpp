/**
 * \file  Debugger.cpp
 * \brief debugger
 */


#include "Debugger.h"

#include <xLib/Core/Char.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/DateTime.h>
#include <xLib/System/ConsoleUI.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Fs/Path.h>
#include <xLib/Log/LogStream.h>

#if   xENV_WIN
    #include "Platform/Win/Debugger_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Debugger_unix.inl"

    #if   xENV_LINUX
        #include "Platform/Linux/Debugger_linux.inl"
    #elif xENV_BSD
        #include "Platform/Bsd/Debugger_bsd.inl"
    #elif xENV_APPLE
        #include "Platform/Apple/Debugger_apple.inl"
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
    cbool_t a_flag
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
    cbool_t a_flag
)
{
    xTEST_NA(a_flag);

    bool_t isEnable {};
    _coreDumpsEnable_impl(a_flag, &isEnable);

    xCHECK_DO(!isEnable, LogCoutWarning() << xT("xLib: Debugger::coreDumpsEnable() - n/a"));
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

    switch ( a_report.type() ) {
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
        throw Exception() << a_report.str();
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
Debugger::_stdoutPlain(
    const ErrorReport &a_report
) const
{
    xCHECK_DO(!isEnabled(), return);

    ConsoleUI ui;

    ConsoleUI::cResult rRv = ui.msgBox(xLIB_NAME, a_report.str());
    switch (rRv) {
    case ConsoleUI::Result::Abort:
        (void_t)::exit(EXIT_FAILURE);
        break;
    case ConsoleUI::Result::Ignore:
        break;
    case ConsoleUI::Result::Retry:
        if ( isActive() ) {
            breakPoint();
        } else {
            (void_t)ui.msgBox(xLIB_NAME, xT("OS debugger is not detected. Abort."));

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
        filePath = Path::exe().setExt(xT("debug")).str();
    } else {
        filePath = logPath();
    }

    // write to file
    try {
        std::tofstream_t ofs(filePath);
        xCHECK_DO(ofs.fail(), return);

        std::ctstring_t msg = Format::str(
            xT("\n")
            xT("####################################################################################################\n")
            xT(" ") xLIB_NAME xT("\n")
            xT("{}\n")
            xT("####################################################################################################\n"),
            a_report.str()
        );

        ofs << msg;
    }
    catch (...) {
    }
}
//-------------------------------------------------------------------------------------------------

} // namespace
