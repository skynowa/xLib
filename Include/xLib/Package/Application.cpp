/**
 * \file  Application.cpp
 * \brief Console application
 */


#include "Application.h"

#include <xLib/Core/Locale.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Log/FileLog.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Log/LogStream.h>
#include <xLib/System/ProcessInfo.h>
#include <xLib/System/User.h>

//-------------------------------------------------------------------------------------------------
namespace xl::package
{

class CrashCallback
{
public:
///\name ctors, dtor
///\{
	CrashCallback()= default;
	~CrashCallback()= default;

	xNO_COPY_ASSIGN(CrashCallback);
///\}

    static void_t onSignals(int_t a_signal)
    {
        xUNUSED(a_signal);

        xTRACE_FUNC;
        // LogCout() << Signal::decription(a_signal) << "\n";

        Application::exitFailure();
    }

#if xENV_WIN
    static void_t onInfo(int_t a_signal)
    {
        xTRACE_FUNC;

        // LogCout() << Signal::decription(0) << "\n";

        FileLog log(xT("crash.log"), FileLog::LogSizes::DefaultMb);

        std::ctstring_t msg = Format::str(
            xT("Crash info:\n\n")
            xT("Signal:\n{}\n\n")
            xT("StackTrace:\n{}"),
            a_signal,
            StackTrace().str());

        log.write(xT("%s\n"), msg.c_str());

        std::tcout << StackTrace().str() << std::endl;

        Application::exitFailure();
    }
#elif xENV_UNIX
    static void_t onInfo(int_t a_signal, siginfo_t *a_info, void_t *a_context)
    {
        xTEST_EQ(a_signal, a_info->si_signo);
        xUNUSED((ucontext_t *)a_context);

        xTRACE_FUNC;

        LogCout() << Signal::infoDescription(*a_info) << "\n";
        LogCout() << Signal::decription(0) << "\n";

        FileLog log(xT("crash.log"), FileLog::LogSizes::DefaultMb);

        std::ctstring_t msg = Format::str(
            xT("Crash info:\n\n")
            xT("Signal:\n{}\n\n")
            xT("StackTrace:\n{}"),
            Signal::infoDescription(*a_info),
            StackTrace().str());

        log.trace(xT("%s\n"), msg.c_str());

        std::tcout << StackTrace().str() << std::endl;

        Application::exitFailure();
    }
#endif

    static void_t onExit()
    {
        xTRACE_FUNC;
    }

    static void_t onTerminate()
    {
        xTRACE_FUNC;
    }

    static void_t onUnexpected()
    {
        xTRACE_FUNC;
    }
};

} // namespace
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
namespace
{

xl::cbool_t     isDevel       = false;

std::ctstring_t backupDirName = xT("Backup");
std::ctstring_t configDirName = xT("Config");
std::ctstring_t logDirName    = xT("Log");
std::ctstring_t dbDirName     = xT("Db");
std::ctstring_t tempDirName   = xT("Temp");
std::ctstring_t langDirName   = xT("Lang");

}
//-------------------------------------------------------------------------------------------------

namespace xl::package
{

///\cond Doxygen_OFF
ApplicationInfo Application::_info;
///\endcond
//-------------------------------------------------------------------------------------------------
Application::Application(
    std::ctstring_t &a_appGuid, ///< application GUID
    std::ctstring_t &a_locale   ///< locale, empty value for current locale
) :
    _isDevel{::isDevel},
    _appGuid{a_appGuid}
{
	xTEST(!a_appGuid.empty());
    xTEST_NA(a_locale);

    Locale locale;
    locale.setCurrent(a_locale);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Application::setDevel(
    cbool_t a_flag
)
{
    _isDevel = a_flag;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Application::isDevel() const
{
    return _isDevel;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   actions
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Application::args(
    cbool_t             a_withoutFirstArg,  ///< erase first argument
    std::vec_tstring_t *a_args              ///< [out] command line arguments
) const
{
    ProcessInfo info( Process::currentId() );
    info.commandLine(a_args);

    if (a_withoutFirstArg) {
        a_args->erase(a_args->cbegin(), a_args->cbegin() + 1);
    }
}
//-------------------------------------------------------------------------------------------------
bool_t
Application::isRunAsAdmin() const
{
    User user;

    return user.isAdmin();
}
//-------------------------------------------------------------------------------------------------
bool_t
Application::isRunnig() const
{
    xUNUSED(_appGuid);

    // TODO: [skynowa] Application::isRunnig()

    return false;
}
//-------------------------------------------------------------------------------------------------
void_t
Application::dirsCreate()
{
    Dir( configDirPath() ).pathCreate();
    Dir( logDirPath() ).pathCreate();
    Dir( dbDirPath() ).pathCreate();
    Dir( backupDirPath() ).pathCreate();
    Dir( tempDirPath() ).pathCreate();
    Dir( langDirPath() ).pathCreate();
}
//-------------------------------------------------------------------------------------------------
bool_t
Application::selfCheck() const
{
#if xLIB_QT
    bool_t bRv {};

    bRv = std::tstring_t(QT_VERSION_STR) == std::tstring_t( qVersion() );
    if (!bRv) {
        std::wcerr
            << "QtLib/Application: "
            << "Qt compile version \"" << QT_VERSION_STR << "\" and "
            << "Qt runtime version \"" << qVersion()     << "\" mismatch" << std::endl;
        return false;
    }
#endif

    // TODO: check configs

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Application::exit(
    cExitCode a_status
)
{
    (void_t)std::exit(a_status);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Application::exitFailure()
{
    exit(ExitCode::Failure);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Application::exitSuccess()
{
    exit(ExitCode::Success);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Application::terminate()
{
    (void_t)std::terminate();
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Application::abort()
{
    (void_t)std::abort();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   handles
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
#if xENV_UNIX

const Signal &
Application::signal() const
{
    static Signal signal;

    return signal;
}

#endif
//-------------------------------------------------------------------------------------------------
/* static */
const BuildInfo &
Application::buildInfo()
{
    static BuildInfo info;

    return info;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   files
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::filePath()
{
    return Path::exe().str();
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::configPath()
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();
    std::ctstring_t ext      = Path::fileDotExt(Path::FileExt::Config);

    return Format::str(xT("{}/{}{}"), configDirPath(), basename, ext);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::logPath()
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();
    std::ctstring_t ext      = Path::fileDotExt(Path::FileExt::Log);

    return Format::str(xT("{}/{}{}"), logDirPath(), basename, ext);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::dbPath()
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();
    std::ctstring_t ext      = Path::fileDotExt(Path::FileExt::Db);

    return Format::str(xT("{}/{}{}"), dbDirPath(), basename, ext);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   directories
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::dirPath()
{
#if xOS_ANDROID
    return Dir::current().str();
#else
    return Path::exe().dir();
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::configDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), ::configDirName);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::logDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), ::logDirName);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::dbDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), ::dbDirName);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::backupDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), ::backupDirName);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::tempDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), ::tempDirName);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::langDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), ::langDirName);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
Application::ExitCode
Application::run()
{
    cbool_t opt_useException {false};

    ExitCode iRv {};

#if xENV_UNIX
#if 0
	signal().connectInfoAll(internal::CrashCallback::onInfo);
#endif

#if 0
    signal().connectExit(internal::CrashCallback::onExit);
    signal().connectTerminate(internal::CrashCallback::onTerminate);
    signal().connectUnexpected(internal::CrashCallback::onUnexpected);
#else
    signal().connectExit(nullptr);
    signal().connectTerminate(nullptr);
    signal().connectUnexpected(nullptr);
#endif
#endif

    if (opt_useException) {
        try {
            iRv = onRun();
        }
        catch (const Exception &a_ex) {
            xTEST_FAIL_MSG(a_ex.what());
        }
        catch (const std::exception &a_ex) {
            std::string msg = a_ex.what();
            xTEST_FAIL_MSG(xA2T(msg));
        }
        catch (...) {
            xTEST_FAIL_MSG(xT("unknown error"));
        }
    } else {
        iRv = onRun();
    }

    return iRv;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
Application::ExitCode
Application::onRun()
{
    xTEST(false);

    return ExitCode::Failure;
}
//-------------------------------------------------------------------------------------------------

} // namespace
