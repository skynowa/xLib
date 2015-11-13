/**
 * \file   Application.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Debug/BuildInfo.h>
#include <xLib/Sync/Signal.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

class Application
    /// application
{
public:
                   Application(std::ctstring_t &appGuid, std::ctstring_t &locale);
        ///< constructor
    virtual       ~Application();
        ///< destructor

    // actions
    void_t         args(cbool_t &withoutFirstArg, std::vec_tstring_t *args) const;
        ///< command line arguments
    bool_t         isRunAsAdmin() const;
        ///< check for running as admin
    bool_t         isRunnig() const;
        ///< check if application already running
    void_t         dirsCreate();
        ///< create all application directories
    bool_t         selfCheck() const;
        ///< self check
    static
    void_t         exit(cint_t &status);
        ///< terminates the process normally, performing the regular cleanup,
        ///< objects with automatic storage are not destroyed
    static
    void_t         terminate();
        ///< calls the current terminate handler
    static
    void_t         abort();
        ///< aborts the current process, producing an abnormal program termination

    // handles
    const Signal  &signal() const;
        ///< signal

    // info
    static
    std::tstring_t name();
        ///< name
    static
    void_t         setName(std::cstring_t &name);
        ///< set name

    static
    std::tstring_t decription();
        ///< decription
    static
    void_t         setDecription(std::cstring_t &decription);
        ///< set decription

    static
    std::tstring_t copyrightYears();
        ///< copyright years (2009-2014)
    static
    void_t         setCopyrightYears(std::cstring_t &copyrightYears);
        ///< set copyright years

    static
    std::tstring_t usage();
        ///< usage
    static
    void_t         setUsage(std::cstring_t &usage);
        ///< set usage

    static
    std::tstring_t help();
        ///< help
    static
    void_t         setHelp(std::cstring_t &help);
        ///< set help

    static
    std::tstring_t versionMajor();
        ///< major version
    static
    void_t         setVersionMajor(std::cstring_t &versionMajor);
        ///< set major version

    static
    std::tstring_t versionMinor();
        ///< minor version
    static
    void_t         setVersionMinor(std::cstring_t &versionMinor);
        ///< set minor version

    static
    std::tstring_t versionPatch();
        ///< patch version
    static
    void_t         setVersionPatch(std::cstring_t &versionPatch);
        ///< set patch version

    static
    std::tstring_t versionType();
        ///< version type (RC, alpha, beta, snapshot)
    static
    void_t         setVersionType(std::cstring_t &versionType);
        ///< set version type

    static
    std::tstring_t versionRevision();
        ///< distributed revision control revision
    static
    void_t         setVersionRevision(std::cstring_t &versionRevision);
        ///< set distributed revision control revision

    static
    std::tstring_t versionFull();
        ///< full version information

    static
    std::tstring_t vendorName();
        ///< vendor name
    static
    void_t         setVendorName(std::cstring_t &vendorName);
        ///< set vendor name

    static
    std::tstring_t vendorDomain();
        ///< vendor domain
    static
    void_t         setVendorDomain(std::cstring_t &vendorDomain);
        ///< set vendor domain

    static
    std::tstring_t vendorAuthor();
        ///< vendor author
    static
    void_t         setVendorAuthor(std::cstring_t &vendorAuthor);
        ///< set vendor author

    static
    std::tstring_t vendorUrl();
        ///< vendor home page
    static
    void_t         setVendorUrl(std::cstring_t &vendorUrl);
        ///< set vendor home page

    static
    std::tstring_t vendorEmail();
        ///< vendor email
    static
    void_t         setVendorEmail(std::cstring_t &vendorEmail);
        ///< set vendor email

    static
    std::tstring_t vendorSkype();
        ///< vendor skype
    static
    void_t         setVendorSkype(std::cstring_t &vendorSkype);
        ///< set vendor skype


    static
    std::tstring_t vendorJabber();
        ///< vendor jabber
    static
    void_t         setVendorJabber(std::cstring_t &vendorJabber);
        ///< set vendor jabber

    static
    std::tstring_t vendorIcq();
        ///< vendor ICQ
    static
    void_t         setVendorIcq(std::cstring_t &vendorIcq);
        ///< set vendor ICQ

    static
    const BuildInfo &buildInfo();
        ///< build information

    // files
    static
    std::tstring_t filePath();
        ///< application file path
    static
    std::tstring_t configPath();
        ///< config file
    static
    std::tstring_t logPath();
        ///< log file
    static
    std::tstring_t dbPath();
        ///< database file

    // directories
    static
    std::tstring_t dirPath();
        ///< application directory
    static
    std::tstring_t configDirPath();
        ///< config directory
    static
    std::tstring_t logDirPath();
        ///< log directory
    static
    std::tstring_t dbDirPath();
        ///< database directory
    static
    std::tstring_t backupDirPath();
        ///< database backup directory
    static
    std::tstring_t tempDirPath();
        ///< temporary directory
    static
    std::tstring_t langDirPath();
        ///< language translation directory

private:
    std::ctstring_t _appGuid;

    // static
    static
    std::tstring_t _name;
    static
    std::tstring_t _decription;
    static
    std::tstring_t _copyrightYears;
    static
    std::tstring_t _usage;
    static
    std::tstring_t _help;
    static
    std::tstring_t _versionMajor;
    static
    std::tstring_t _versionMinor;
    static
    std::tstring_t _versionPatch;
    static
    std::tstring_t _versionType;
    static
    std::tstring_t _versionRevision;
    static
    std::tstring_t _vendorName;
    static
    std::tstring_t _vendorDomain;
    static
    std::tstring_t _vendorAuthor;
    static
    std::tstring_t _vendorUrl;
    static
    std::tstring_t _vendorEmail;
    static
    std::tstring_t _vendorSkype;
    static
    std::tstring_t _vendorJabber;
    static
    std::tstring_t _vendorIcq;

    xNO_COPY_ASSIGN(Application)
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#define xLIB_CORE_APPLICATION_STATIC_DECLARE \
    std::tstring_t xlib::core::Application::_name; \
    std::tstring_t xlib::core::Application::_decription; \
    std::tstring_t xlib::core::Application::_copyrightYears; \
    std::tstring_t xlib::core::Application::_usage; \
    std::tstring_t xlib::core::Application::_help; \
    std::tstring_t xlib::core::Application::_versionMajor; \
    std::tstring_t xlib::core::Application::_versionMinor; \
    std::tstring_t xlib::core::Application::_versionPatch; \
    std::tstring_t xlib::core::Application::_versionType; \
    std::tstring_t xlib::core::Application::_versionRevision; \
    std::tstring_t xlib::core::Application::_vendorName; \
    std::tstring_t xlib::core::Application::_vendorDomain; \
    std::tstring_t xlib::core::Application::_vendorAuthor; \
    std::tstring_t xlib::core::Application::_vendorUrl; \
    std::tstring_t xlib::core::Application::_vendorEmail; \
    std::tstring_t xlib::core::Application::_vendorSkype; \
    std::tstring_t xlib::core::Application::_vendorJabber; \
    std::tstring_t xlib::core::Application::_vendorIcq;
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Application.cpp"
#else
    extern xlib::core::Application application;
#endif
