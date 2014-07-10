/**
 * \file   Application.inl
 * \brief
 */


#include "Application.h"

#include <xLib/Core/String.h>
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
std::ctstring_t dbDirName       = "Db";

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
inline void_t
Application::args(
    std::vec_tstring_t *a_args  ///< [out] command line arguments
) const
{
    ProcessInfo info;
    info.commandLine(a_args);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::dirPath() const
{
    return Path::exeDir();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::filePath() const
{
    return Path::exe();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::configFilePath() const
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();

    return dirPath() + Const::slash() + basename + Path::seConfig;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::dbDirPath() const
{
    return dirPath() + Const::slash() + ::dbDirName;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::dbFilePath() const
{
    return dbDirPath() + Const::slash() + name() + Path::seDb;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::backupDirPath() const
{
    return dbDirPath() + Const::slash() + ::backupDirName;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Application::debugTracePath() const
{
    return dirPath() + Const::slash() + name() + Path::seLog;
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
inline std::tstring_t
Application::buildInfo() const
{
#if 0
    return std::tstring_t("Qt %1")
                .arg(QT_VERSION_STR);
#endif

    return std::tstring_t();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
