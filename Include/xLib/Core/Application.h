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
    std::tstring_t name() const;
        ///< name
    std::tstring_t decription() const;
        ///< decription
    std::tstring_t copyrightYears() const;
        ///< 2009-2014
    std::tstring_t usage() const;
        ///< usage
    std::tstring_t help() const;
        ///< help

    std::tstring_t versionMajor() const;
        ///< major version
    std::tstring_t versionMinor() const;
        ///< minor version
    std::tstring_t versionPatch() const;
        ///< patch version
    std::tstring_t versionType() const;
        ///< version type (RC, alpha, beta, snapshot)
    std::tstring_t versionRevision() const;
        ///< distributed revision control revision
    std::tstring_t versionFull() const;
        ///< full version information

    std::tstring_t vendorName() const;
        ///< vendor name
    std::tstring_t vendorDomain() const;
        ///< vendor domain
    std::tstring_t vendorAuthor() const;
        ///< vendor author
    std::tstring_t vendorUrl() const;
        ///< vendor home page
    std::tstring_t vendorEmail() const;
        ///< vendor email
    std::tstring_t vendorSkype() const;
        ///< vendor skype
    const BuildInfo &buildInfo() const;
        ///< build information

    // files
    std::tstring_t filePath() const;
        ///< application file path
    std::tstring_t configPath() const;
        ///< config file
    std::tstring_t logPath() const;
        ///< log file
    std::tstring_t dbPath() const;
        ///< database file

    // directories
    std::tstring_t dirPath() const;
        ///< application directory
    std::tstring_t configDirPath() const;
        ///< config directory
    std::tstring_t logDirPath() const;
        ///< log directory
    std::tstring_t dbDirPath() const;
        ///< database directory
    std::tstring_t backupDirPath() const;
        ///< database backup directory
    std::tstring_t tempDirPath() const;
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
