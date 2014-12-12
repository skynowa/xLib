/**
 * \file   Application.inl
 * \brief
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Application.h"

    xLIB_CORE_APPLICATION_STATIC_DECLARE
#endif

#include <xLib/Core/Locale.h>
#include <xLib/Core/String.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/Dir.h>
#include <xLib/System/ProcessInfo.h>

xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
namespace {

std::ctstring_t backupDirName = "Backup";
std::ctstring_t configDirName = "Config";
std::ctstring_t logDirName    = "Log";
std::ctstring_t dbDirName     = "Db";
std::ctstring_t tempDirName   = "Temp";
std::ctstring_t langDirName   = "Lang";

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


/**************************************************************************************************
*   info
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::name()
{
    return _name;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setName(
    std::cstring_t &a_name
)
{
    _name = a_name;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::decription()
{
    return _decription;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setDecription(
    std::cstring_t &a_decription
)
{
    _decription = a_decription;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::copyrightYears()
{
    return _copyrightYears;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setCopyrightYears(
    std::cstring_t &a_copyrightYears
)
{
    _copyrightYears = a_copyrightYears;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::usage()
{
    return _usage;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setUsage(
    std::cstring_t &a_usage
)
{
    _usage = a_usage;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::help()
{
    return _help;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setHelp(
    std::cstring_t &a_help
)
{
    _help = a_help;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::versionMajor()
{
    return _versionMajor;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setVersionMajor(
    std::cstring_t &a_versionMajor
)
{
    _versionMajor = a_versionMajor;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::versionMinor()
{
    return _versionMinor;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setVersionMinor(
    std::cstring_t &a_versionMinor
)
{
    _versionMinor = a_versionMinor;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::versionPatch()
{
    return _versionPatch;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setVersionPatch(
    std::cstring_t &a_versionPatch
)
{
    _versionPatch = a_versionPatch;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::versionType()
{
    return _versionType;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setVersionType(
    std::cstring_t &a_versionType
)
{
    _versionType = a_versionType;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::versionRevision()
{
    return _versionRevision;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setVersionRevision(
    std::cstring_t &a_versionRevision
)
{
    _versionRevision = a_versionRevision;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::versionFull()
{
    return String::format(xT("%s.%s.%s %s %s"), versionMajor().c_str(), versionMinor().c_str(),
        versionPatch().c_str(), versionType().c_str(), versionRevision().c_str());
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::vendorName()
{
    return _vendorName;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setVendorName(
    std::cstring_t &a_vendorName
)
{
    _vendorName = a_vendorName;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::vendorDomain()
{
    return _vendorDomain;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setVendorDomain(
    std::cstring_t &a_vendorDomain
)
{
    _vendorDomain = a_vendorDomain;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::vendorAuthor()
{
    return _vendorAuthor;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setVendorAuthor(
    std::cstring_t &a_vendorAuthor
)
{
    _vendorAuthor = a_vendorAuthor;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::vendorUrl()
{
    return _vendorUrl;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setVendorUrl(
    std::cstring_t &a_vendorUrl
)
{
    _vendorUrl = a_vendorUrl;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::vendorEmail()
{
    return _vendorEmail;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setVendorEmail(
    std::cstring_t &a_vendorEmail
)
{
    _vendorEmail = a_vendorEmail;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::vendorSkype()
{
    return _vendorSkype;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setVendorSkype(
    std::cstring_t &a_vendorSkype
)
{
    _vendorSkype = a_vendorSkype;
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

    return String::format(xT("%s/%s.%s"), configDirPath().c_str(), basename.c_str(), ext.c_str());
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::logPath()
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();
    std::ctstring_t ext      = Path::fileExt(Path::seLog);

    return String::format(xT("%s/%s.%s"), logDirPath().c_str(), basename.c_str(), ext.c_str());
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::dbPath()
{
    std::ctstring_t basename = Path( filePath() ).fileBaseName();
    std::ctstring_t ext      = Path::fileExt(Path::seDb);

    return String::format(xT("%s/%s.%s"), dbDirPath().c_str(), basename.c_str(), ext.c_str());
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
    return Path::exeDir();
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::configDirPath()
{
    return String::format(xT("%s/%s"), dirPath().c_str(), configDirName.c_str());
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::logDirPath()
{
    return String::format(xT("%s/%s"), dirPath().c_str(), logDirName.c_str());
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::dbDirPath()
{
    return String::format(xT("%s/%s"), dirPath().c_str(), dbDirName.c_str());
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::backupDirPath()
{
    return String::format(xT("%s/%s"), dirPath().c_str(), backupDirName.c_str());
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::tempDirPath()
{
    return String::format(xT("%s/%s"), dirPath().c_str(), tempDirName.c_str());
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::langDirPath()
{
    return String::format(xT("%s/%s"), dirPath().c_str(), langDirName.c_str());
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
