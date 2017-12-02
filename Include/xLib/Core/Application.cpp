/**
 * \file   Application.inl
 * \brief
 */


#include "Application.h"

#include <xLib/Core/Locale.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Log/Trace.h>
#include <xLib/Log/FileLog.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/Dir.h>
#include <xLib/System/ProcessInfo.h>
#include <xLib/System/User.h>

//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, internal)

class CrashCallback
{
public:
    xNO_INLINE
    CrashCallback()
    {
    }

    xNO_INLINE static void_t
    onSignals(int_t a_signal)
    {
        xTRACE_FUNC;
        Trace() << Signal::decription(a_signal) << "\n";

        Application::exit(EXIT_FAILURE);
    }

    xNO_INLINE static void_t
    onInfo(int_t a_signal, siginfo_t *a_info, void_t *a_context)
    {
        xTEST_EQ(a_signal, a_info->si_signo);
        xUNUSED((ucontext_t *)a_context);

        xTRACE_FUNC;

        Trace() << Signal::infoDescription(*a_info) << "\n";
        Trace() << Signal::decription(0) << "\n";

        FileLog log(FileLog::lsDefaultMb);
        log.setFilePath(xT("crash.log"));

        std::ctstring_t msg = Format::str(
            xT("Crash info:\n\n")
            xT("Signal:\n{}\n\n")
            xT("StackTrace:\n{}"),
            Signal::infoDescription(*a_info),
            StackTrace().toString());

        log.write(xT("%s\n"), msg.c_str());

        std::tcout << StackTrace().toString() << std::endl;

        Application::exit(EXIT_FAILURE);
    }

    xNO_INLINE static void_t
    onExit()
    {
        xTRACE_FUNC;
    }

    xNO_INLINE static void_t
    onTerminate()
    {
        xTRACE_FUNC;
    }

    xNO_INLINE static void_t
    onUnexpected()
    {
        xTRACE_FUNC;
    }

private:
    xNO_COPY_ASSIGN(CrashCallback)
};

xNAMESPACE_END2(xl, internal)
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

xl::cbool_t     isDevel        = false;

std::ctstring_t _backupDirName = xT("Backup");
std::ctstring_t _configDirName = xT("Config");
std::ctstring_t _logDirName    = xT("Log");
std::ctstring_t _dbDirName     = xT("Db");
std::ctstring_t _tempDirName   = xT("Temp");
std::ctstring_t _langDirName   = xT("Lang");

xNAMESPACE_ANONYM_END
//-------------------------------------------------------------------------------------------------

xNAMESPACE_BEGIN2(xl, core)

ApplicationInfo Application::_info;
Donate          Application::_donate;
//-------------------------------------------------------------------------------------------------
Application::Application(
    std::ctstring_t &a_appGuid, ///< application GUID
    std::ctstring_t &a_locale   ///< locale, empty value for current locale
) :
    _isDevel(::isDevel),
    _appGuid(a_appGuid)
{
    xTEST_EQ(a_appGuid.empty(), false);
    xTEST_NA(a_locale);

    Locale locale;
    locale.setCurrent(a_locale);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
Application::~Application()
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
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
    cbool_t            &a_withoutFirstArg,  ///< erase first argument
    std::vec_tstring_t *a_args              ///< [out] command line arguments
) const
{
    ProcessInfo info;
    info.setProcessId( Process::currentId() );
    info.commandLine(a_args);

    if (a_withoutFirstArg) {
        a_args->erase(a_args->begin(), a_args->begin() + 1);
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

    // TODO: Application::isRunnig()

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
    bool_t bRv = false;

    bRv = std::tstring_t(QT_VERSION_STR) == std::tstring_t( qVersion() );
    if (!bRv) {
        std::wcerr
            << "QtLib/Application: "
            << "Qt compile version \"" << QT_VERSION_STR << "\" and "
            << "Qt runtime version \"" << qVersion()     << "\" mismatch" << std::endl;
        return false;
    }
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Application::exit(
    cint_t &a_status
)
{
    (void_t)std::exit(a_status);
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
const Signal &
Application::signal() const
{
    static Signal signal;

    return signal;
}
//-------------------------------------------------------------------------------------------------
/* static */
ApplicationInfo &
Application::info()
{
    return _info;
}
//-------------------------------------------------------------------------------------------------
/* static */
void
Application::setInfo(
    const ApplicationInfo &a_info
)
{
    _info = a_info;
}
//-------------------------------------------------------------------------------------------------
/* static */
const BuildInfo &
Application::buildInfo()
{
    static BuildInfo info;

    return info;
}
//-------------------------------------------------------------------------------------------------
/* static */
Donate &
Application::donate()
{
    return _donate;
}
//-------------------------------------------------------------------------------------------------
/* static */
void
Application::setDonate(
    const Donate &a_donate
)
{
    _donate = a_donate;
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
    return Path::exe();
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::configPath()
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();
    std::ctstring_t ext      = Path::fileExt(Path::seConfig);

    return Format::str(xT("{}/{}.{}"), configDirPath(), basename, ext);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::logPath()
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();
    std::ctstring_t ext      = Path::fileExt(Path::seLog);

    return Format::str(xT("{}/{}.{}"), logDirPath(), basename, ext);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::dbPath()
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();
    std::ctstring_t ext      = Path::fileExt(Path::seDb);

    return Format::str(xT("{}/{}.{}"), dbDirPath(), basename, ext);
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
    return Dir::current();
#else
    return Path::exeDir();
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::configDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), _configDirName);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::logDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), _logDirName);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::dbDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), _dbDirName);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::backupDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), _backupDirName);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::tempDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), _tempDirName);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Application::langDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), _langDirName);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
int_t
Application::run()
{
    cbool_t opt_useException = false;

    int_t iRv = EXIT_FAILURE;

    signal().connectInfoAll(internal::CrashCallback::onInfo);
#if 0
    signal().connectExit(internal::CrashCallback::onExit);
    signal().connectTerminate(internal::CrashCallback::onTerminate);
    signal().connectUnexpected(internal::CrashCallback::onUnexpected);
#else
    signal().connectExit(xPTR_NULL);
    signal().connectTerminate(xPTR_NULL);
    signal().connectUnexpected(xPTR_NULL);
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
int_t
Application::onRun()
{
    xTEST(false);

    return EXIT_FAILURE;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
