/**
 * \file   Application.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/ApplicationInfo.h>
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

    xPROPERTY_STATIC(ApplicationInfo, info);
        ///< information
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

    xNO_COPY_ASSIGN(Application)
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#if 0
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
#endif
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "Application.cpp"
#else
    extern xlib::core::Application application;
#endif
