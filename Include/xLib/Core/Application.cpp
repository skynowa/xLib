/**
 * \file   Application.inl
 * \brief
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Application.h"
#endif

xLIB_CORE_APPLICATION_STATIC_DECLARE

#include <xLib/Core/Locale.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
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
    std::ctstring_t &a_name
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
    std::ctstring_t &a_decription
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
    std::ctstring_t &a_copyrightYears
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
    std::ctstring_t &a_usage
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
    std::ctstring_t &a_help
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
    std::ctstring_t &a_versionMajor
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
    std::ctstring_t &a_versionMinor
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
    std::ctstring_t &a_versionPatch
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
    std::ctstring_t &a_versionType
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
    std::ctstring_t &a_versionRevision
)
{
    _versionRevision = a_versionRevision;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::versionFull()
{
    return Format::str(xT("{}.{}.{} {} {}"), versionMajor(), versionMinor(), versionPatch(),
        versionType(), versionRevision());
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
    std::ctstring_t &a_vendorName
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
    std::ctstring_t &a_vendorDomain
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
    std::ctstring_t &a_vendorAuthor
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
    std::ctstring_t &a_vendorUrl
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
    std::ctstring_t &a_vendorEmail
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
    std::ctstring_t &a_vendorSkype
)
{
    _vendorSkype = a_vendorSkype;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::vendorJabber()
{
    return _vendorJabber;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setVendorJabber(
    std::ctstring_t &a_vendorJabber
)
{
    _vendorJabber = a_vendorJabber;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Application::vendorIcq()
{
    return _vendorIcq;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Application::setVendorIcq(
    std::ctstring_t &a_vendorIcq
)
{
    _vendorIcq = a_vendorIcq;
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

xNAMESPACE_END2(xlib, core)
