/**
 * \file   Application.inl
 * \brief
 */


#include "Application.h"

#include <xLib/Core/String.h>
#include <xLib/Debug/BuildInfo.h>
#include <xLib/IO/Path.h>
#include <xLib/System/ProcessInfo.h>


xNAMESPACE_BEGIN2(xlib, core)


/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
namespace {

std::ctstring_t localeCodec     = "UTF-8";

std::ctstring_t name            = "[app_name]";
std::ctstring_t decription      = "[decription]";
std::ctstring_t usage           = "[usage]";
std::ctstring_t help            = "[help]";
std::ctstring_t copyrightYears  = "[2008-2014]";

std::ctstring_t versionMajor    = "[1]";
std::ctstring_t versionMinor    = "[0]";
std::ctstring_t versionPatch    = "[0]";
std::ctstring_t versionType     = "[alpha]";
std::ctstring_t versionRevision = "[develop/970f53b]";

std::ctstring_t vendorName      = "[Skynowa Studio]";
std::ctstring_t vendorDomain    = "[com]";
std::ctstring_t vendorAuthor    = "[skynowa]";
std::ctstring_t vendorUrl       = "[http://bitbucket.org/skynowa/xlib]";
std::ctstring_t vendorEmail     = "[skynowa@gmail.com]";
std::ctstring_t vendorSkype     = "[skynowa777]";

std::ctstring_t backupDirName   = "Backup";
std::ctstring_t configDirName   = "Config";
std::ctstring_t logDirName      = "Log";
std::ctstring_t dbDirName       = "Db";
std::ctstring_t tempDirName     = "Temp";

}
//-------------------------------------------------------------------------------------------------
inline
Application::Application()
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
Application::~Application()
{
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   info
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::name()
{
    return ::name;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::decription()
{
    return ::decription;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::copyrightYears()
{
    return ::copyrightYears;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::usage()
{
    return ::usage;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::help()
{
    return ::help;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::versionMajor()
{
    return ::versionMajor;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::versionMinor()
{
    return ::versionMinor;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::versionPatch()
{
    return ::versionPatch;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::versionType()
{
    return ::versionType;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::versionRevision()
{
    return ::versionRevision;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::versionFull()
{
    return String::format(xT("%s.%s.%s %s %s"), versionMajor().c_str(), versionMinor().c_str(),
        versionPatch().c_str(), versionType().c_str(), versionRevision().c_str());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::vendorName()
{
    return ::vendorName;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::vendorDomain()
{
    return ::vendorDomain;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::vendorAuthor()
{
    return ::vendorAuthor;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::vendorUrl()
{
    return ::vendorUrl;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::vendorEmail()
{
    return ::vendorEmail;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::vendorSkype()
{
    return ::vendorSkype;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline const BuildInfo &
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
inline std::tstring_t
Application::filePath()
{
    return Path::exe();
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::configPath()
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();
    std::ctstring_t ext      = Path::fileExt(Path::seConfig);

    return String::format(xT("%s/%s.%s"), configDirPath().c_str(), basename.c_str(), ext.c_str());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::logPath()
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();
    std::ctstring_t ext      = Path::fileExt(Path::seLog);

    return String::format(xT("%s/%s.%s"), dirPath().c_str(), basename.c_str(), ext.c_str());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::dbPath()
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();
    std::ctstring_t ext      = Path::fileExt(Path::seDb);

    return String::format(xT("%s/%s.%s"), dirPath().c_str(), basename.c_str(), ext.c_str());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   directories
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::dirPath()
{
    return Path::exeDir();
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::configDirPath()
{
    return String::format(xT("%s/%s"), dirPath().c_str(), ::configDirName.c_str());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::logDirPath()
{
    return String::format(xT("%s/%s"), dirPath().c_str(), ::logDirName.c_str());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::dbDirPath()
{
    return String::format(xT("%s/%s"), dirPath().c_str(), ::dbDirName.c_str());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::backupDirPath()
{
    return String::format(xT("%s/%s"), dirPath().c_str(), ::backupDirName.c_str());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::tempDirPath()
{
    return String::format(xT("%s/%s"), dirPath().c_str(), ::tempDirName.c_str());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   actions
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
Application::args(
    std::vec_tstring_t *a_args  ///< [out] command line arguments
) const
{
    ProcessInfo info;
    info.commandLine(a_args);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
Application::isRunnig(
    std::ctstring_t &a_appGuid
) const
{
    xUNUSED(a_appGuid);

    // TODO: Application::isRunnig()

    return false;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
Application::selfCheck() const
{
#if 0
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
inline void_t
Application::exit(
    cint_t &a_status
) const
{
    (void_t)std::exit(a_status);
}
//-------------------------------------------------------------------------------------------------
inline void_t
Application::terminate() const
{
    (void_t)std::terminate();
}
//-------------------------------------------------------------------------------------------------
inline void_t
Application::abort() const
{
    (void_t)std::abort();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   actions
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
Application::setOnSignals(
    const std::vector<int_t> &a_signalNums,
    sighandler_t              a_callback
)
{
   /**
    * FAQ: set handlers
    *
    * https://gist.github.com/jvranish/4441299
    */

    xFOREACH_CONST(std::vector<int_t>, it, a_signalNums) {
        sighandler_t shRv = std::signal(*it, a_callback);
        xTEST(shRv != SIG_ERR);
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
Application::setOnExit(
    void_t (*a_callback)()
)
{
    xCHECK_DO(a_callback == xPTR_NULL, return);

    int_t iRv = std::atexit(a_callback);
    xTEST(iRv == 0);
}
//-------------------------------------------------------------------------------------------------
inline void_t
Application::setOnTerminate(
    void_t (*a_callback)()
)
{
    xTEST_PTR(a_callback);

    void_t (*callback_old)() = xPTR_NULL;

    callback_old = std::set_terminate(a_callback);
    xUNUSED(callback_old);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
