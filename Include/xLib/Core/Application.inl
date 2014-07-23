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
inline std::tstring_t
Application::name() const
{
    return ::name;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::decription() const
{
    return ::decription;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::copyrightYears() const
{
    return ::copyrightYears;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::usage() const
{
    return ::usage;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::help() const
{
    return ::help;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::versionMajor() const
{
    return ::versionMajor;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::versionMinor() const
{
    return ::versionMinor;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::versionPatch() const
{
    return ::versionPatch;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::versionType() const
{
    return ::versionType;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::versionRevision() const
{
    return ::versionRevision;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::versionFull() const
{
    return String::format(xT("%s.%s.%s %s %s"), versionMajor().c_str(), versionMinor().c_str(),
        versionPatch().c_str(), versionType().c_str(), versionRevision().c_str());
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::vendorName() const
{
    return ::vendorName;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::vendorDomain() const
{
    return ::vendorDomain;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::vendorAuthor() const
{
    return ::vendorAuthor;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::vendorUrl() const
{
    return ::vendorUrl;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::vendorEmail() const
{
    return ::vendorEmail;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::vendorSkype() const
{
    return ::vendorSkype;
}
//-------------------------------------------------------------------------------------------------
inline const BuildInfo &
Application::buildInfo() const
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
inline std::tstring_t
Application::filePath() const
{
    return Path::exe();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::configPath() const
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();
    std::ctstring_t ext      = Path::fileExt(Path::seConfig);

    return String::format(xT("%s/%s.%s"), configDirPath().c_str(), basename.c_str(), ext.c_str());
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::logPath() const
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();
    std::ctstring_t ext      = Path::fileExt(Path::seLog);

    return String::format(xT("%s/%s.%s"), dirPath().c_str(), basename().c_str(), ext.c_str());
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::dbPath() const
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();
    std::ctstring_t ext      = Path::fileExt(Path::seDb);

    return String::format(xT("%s/%s.%s"), dirPath().c_str(), basename().c_str(), ext.c_str());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   directories
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::dirPath() const
{
    return Path::exeDir();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::configDirPath() const
{
    return String::format(xT("%s/%s"), dirPath().c_str(), ::configDirName.c_str());
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::logDirPath() const
{
    return String::format(xT("%s/%s"), dirPath().c_str(), ::logDirName.c_str());
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::dbDirPath() const
{
    return String::format(xT("%s/%s"), dirPath().c_str(), ::dbDirName.c_str());
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::backupDirPath() const
{
    return String::format(xT("%s/%s"), dirPath().c_str(), ::backupDirName.c_str());
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::tempDirPath() const
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


/**************************************************************************************************
*   actions
*
**************************************************************************************************/

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
