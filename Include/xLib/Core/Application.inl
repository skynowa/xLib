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

#if 0
    std::ctstring_t localeCodec     = "UTF-8";
#endif

#if 0

#endif

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
    return _name;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
Application::setName(
    std::cstring_t &a_name
)
{
    _name = a_name;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::decription()
{
    return _decription;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
Application::setDecription(
    std::cstring_t &a_decription
)
{
    _decription = a_decription;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::copyrightYears()
{
    return _copyrightYears;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
Application::setCopyrightYears(
    std::cstring_t &a_copyrightYears
)
{
    _copyrightYears = a_copyrightYears;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::usage()
{
    return _usage;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
Application::setUsage(
    std::cstring_t &a_usage
)
{
    _usage = a_usage;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::help()
{
    return _help;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
Application::setHelp(
    std::cstring_t &a_help
)
{
    _help = a_help;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::versionMajor()
{
    return _versionMajor;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
Application::setVersionMajor(
    std::cstring_t &a_versionMajor
)
{
    _versionMajor = a_versionMajor;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::versionMinor()
{
    return _versionMinor;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
Application::setVersionMinor(
    std::cstring_t &a_versionMinor
)
{
    _versionMinor = a_versionMinor;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::versionPatch()
{
    return _versionPatch;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
Application::setVersionPatch(
    std::cstring_t &a_versionPatch
)
{
    _versionPatch = a_versionPatch;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::versionType()
{
    return _versionType;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
Application::setVersionType(
    std::cstring_t &a_versionType
)
{
    _versionType = a_versionType;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::versionRevision()
{
    return _versionRevision;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
Application::setVersionRevision(
    std::cstring_t &a_versionRevision
)
{
    _versionRevision = a_versionRevision;
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
    return _vendorName;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
Application::setVendorName(
    std::cstring_t &a_vendorName
)
{
    _vendorName = a_vendorName;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::vendorDomain()
{
    return _vendorDomain;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
Application::setVendorDomain(
    std::cstring_t &a_vendorDomain
)
{
    _vendorDomain = a_vendorDomain;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::vendorAuthor()
{
    return _vendorAuthor;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
Application::setVendorAuthor(
    std::cstring_t &a_vendorAuthor
)
{
    _vendorAuthor = a_vendorAuthor;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::vendorUrl()
{
    return _vendorUrl;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
Application::setVendorUrl(
    std::cstring_t &a_vendorUrl
)
{
    _vendorUrl = a_vendorUrl;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::vendorEmail()
{
    return _vendorEmail;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
Application::setVendorEmail(
    std::cstring_t &a_vendorEmail
)
{
    _vendorEmail = a_vendorEmail;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Application::vendorSkype()
{
    return _vendorSkype;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
Application::setVendorSkype(
    std::cstring_t &a_vendorSkype
)
{
    _vendorSkype = a_vendorSkype;
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
