/**
 * \file   Application.inl
 * \brief
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Application.h"
#endif

#if   cmOPTION_PROJECT_HEADER_ONLY
    xLIB_CORE_APPLICATION_STATIC_DECLARE    // add to main.cpp
#elif cmOPTION_PROJECT_LIB_STATIC
    xLIB_CORE_APPLICATION_STATIC_DECLARE
#elif cmOPTION_PROJECT_LIB_SHARE
    xLIB_CORE_APPLICATION_STATIC_DECLARE
#elif cmOPTION_PROJECT_LIB_MODULE
    xLIB_CORE_APPLICATION_STATIC_DECLARE
#elif
    #error Invalid option
#endif


#include <xLib/Core/Locale.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Log/Trace.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/Dir.h>
#include <xLib/System/ProcessInfo.h>
#include <xLib/System/User.h>

xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
namespace
{

std::ctstring_t backupDirName = xT("Backup");
std::ctstring_t configDirName = xT("Config");
std::ctstring_t logDirName    = xT("Log");
std::ctstring_t dbDirName     = xT("Db");
std::ctstring_t tempDirName   = xT("Temp");
std::ctstring_t langDirName   = xT("Lang");

}
//-------------------------------------------------------------------------------------------------
xINLINE
Application::Application(
    std::ctstring_t &a_appGuid, ///< application GUID
    std::ctstring_t &a_locale   ///< locale, empty value for current locale
) :
    _appGuid(a_appGuid)
{
    xTEST_EQ(a_appGuid.empty(), false);
    xTEST_NA(a_locale);

    Locale locale;
    locale.setCurrent(a_locale);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
Application::~Application()
{
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   actions
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
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
xINLINE bool_t
Application::isRunAsAdmin() const
{
    system::User user;

    return user.isAdmin();
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Application::isRunnig() const
{
    xUNUSED(_appGuid);

    // TODO: Application::isRunnig()

    return false;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
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
xINLINE bool_t
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
xINLINE void_t
Application::exit(
    cint_t &a_status
)
{
    (void_t)std::exit(a_status);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::terminate()
{
    (void_t)std::terminate();
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
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
xINLINE const Signal &
Application::signal() const
{
    static Signal signal;

    return signal;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE ApplicationInfo &
Application::info()
{
    return _info;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Application::setInfo(
    const ApplicationInfo &a_info
)
{
    _info = a_info;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE const BuildInfo &
Application::buildInfo()
{
    static BuildInfo info;

    return info;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE Donate &
Application::donate()
{
    return _donate;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
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
xINLINE std::tstring_t
Application::filePath()
{
    return Path::exe();
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::configPath()
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();
    std::ctstring_t ext      = Path::fileExt(Path::seConfig);

    return Format::str(xT("{}/{}.{}"), configDirPath(), basename, ext);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::logPath()
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();
    std::ctstring_t ext      = Path::fileExt(Path::seLog);

    return Format::str(xT("{}/{}.{}"), logDirPath(), basename, ext);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
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
xINLINE std::tstring_t
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
xINLINE std::tstring_t
Application::configDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), configDirName);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::logDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), logDirName);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::dbDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), dbDirName);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::backupDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), backupDirName);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::tempDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), tempDirName);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::langDirPath()
{
    return Format::str(xT("{}/{}"), dirPath(), langDirName);
}
//-------------------------------------------------------------------------------------------------

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
class SignalsHandler
{
public:
	xNO_INLINE
	SignalsHandler()
	{
	}

    xNO_INLINE static void_t
    onSignals(int_t a_signal)
    {
        xTRACE_FUNC;

        Trace() << Signal::decription(a_signal) << "\n";
        // Trace() << StackTrace().toString()      << "\n";

	#if 1
		Application::exit(EXIT_FAILURE);
	#else
		xTHROW_REPORT("TEST MESSAGE");
	#endif
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

    xNO_INLINE static void_t
    onRestart()
    {
        xTRACE_FUNC;
    }

private:
    xNO_COPY_ASSIGN(SignalsHandler)
};
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE int_t
Application::run()
{
    cbool_t opt_useException = false;

    int_t iRv = EXIT_FAILURE;

	signal().connectAll(SignalsHandler::onSignals);
	signal().connectExit(SignalsHandler::onExit);
	signal().connectTerminate(SignalsHandler::onTerminate);
	signal().connectUnexpected(SignalsHandler::onUnexpected);
	signal().connectRestart(SignalsHandler::onRestart);

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
xINLINE int_t
Application::onRun()
{
    xTEST(false);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
