/**
 * \file   Application.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

class Application
    /// application
{
public:
                   Application();
        ///< constructor
    virtual       ~Application();
        ///< destructor

    // info
    static
    std::tstring_t name();
        ///< name
    static
    std::tstring_t decription();
        ///< decription
    static
    std::tstring_t copyrightYears();
        ///< 2009-2014
    static
    std::tstring_t usage();
        ///< usage
    static
    std::tstring_t help();
        ///< help

    static
    std::tstring_t versionMajor();
        ///< major version
    static
    std::tstring_t versionMinor();
        ///< minor version
    static
    std::tstring_t versionPatch();
        ///< patch version
    static
    std::tstring_t versionType();
        ///< version type (RC, alpha, beta, snapshot)
    static
    std::tstring_t versionRevision();
        ///< distributed revision control revision
    static
    std::tstring_t versionFull();
        ///< full version information
    static

    std::tstring_t vendorName();
        ///< vendor name
    static
    std::tstring_t vendorDomain();
        ///< vendor domain
    static
    std::tstring_t vendorAuthor();
        ///< vendor author
    static
    std::tstring_t vendorUrl();
        ///< vendor home page
    static
    std::tstring_t vendorEmail();
        ///< vendor email
    static
    std::tstring_t vendorSkype();
        ///< vendor skype
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

    // actions
    void_t         args(std::vec_tstring_t *args) const;
        ///< command line arguments
    bool_t         isRunnig(std::ctstring_t &appGuid) const;
        ///< check if application already running
    bool_t         selfCheck() const;
        ///< self check
    //++ virtual int_t  run() = 0;
        ///< run application
    void_t         exit(cint_t &status) const;
        ///< terminates the process normally, performing the regular cleanup,
        ///< objects with automatic storage are not destroyed
    void_t         terminate() const;
        ///< calls the current terminate handler
    void_t         abort() const;
        ///< aborts the current process, producing an abnormal program termination

    // handles
    void_t         setOnSignals(const std::vector<int_t> &signalNums, sighandler_t callback);
        ///< set signal handle
    void_t         setOnExit(void_t (*callback)());
        ///< set exit handle
    void_t         setOnTerminate(void_t (*callback)());
        ///< set terminate handle (by default, the terminate handler calls abort)

private:
    xNO_COPY_ASSIGN(Application)
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Application.inl>
