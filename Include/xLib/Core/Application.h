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
    std::tstring_t versionSring() const;
        ///< full version information ({versionMajor}.{versionMinor}.{versionPatch}-{versionType})
    std::tstring_t versionRevision() const;
        ///< distributed revision control revision

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

    void_t         args(std::vec_tstring_t *args) const;
        ///< directory
    std::tstring_t dirPath() const;
        ///< directory
    std::tstring_t filePath() const;
        ///< file
    std::tstring_t configFilePath() const;
        ///< config file
    std::tstring_t dbDirPath() const;
        ///< database directory
    std::tstring_t dbFilePath() const;
        ///< database file
    std::tstring_t backupDirPath() const;
        ///< database backup directory
    std::tstring_t debugTracePath() const;
        ///< debug trace file
    std::tstring_t tempDirPath() const;
        ///< temporary directory

    bool_t         isRunnig(std::ctstring_t &appGuid) const;
        ///< check if application already running
    bool_t         selfCheck() const;
        ///< self check
    std::tstring_t buildInfo() const;
        ///< build information

private:
    xNO_COPY_ASSIGN(Application)
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Application.h>
