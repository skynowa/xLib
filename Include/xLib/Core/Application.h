/**
 * \file   Application.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/ApplicationInfo.h>
#include <xLib/Debug/BuildInfo.h>
#include <xLib/Sync/Signal.h>
#include <xLib/Package/Donate.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

class Application
    /// application
{
public:
                   Application(std::ctstring_t &appGuid, std::ctstring_t &locale);
        ///< constructor
    virtual       ~Application();
        ///< destructor

    bool_t         setDevel(cbool_t flag);
        ///< set devel
    bool_t         isDevel() const;
        ///< is devel

    // actions
    void_t         args(cbool_t &withoutFirstArg, std::vec_tstring_t *args) const;
        ///< command line arguments
    const Signal  &signal() const;
        ///< signal
    bool_t         isRunAsAdmin() const;
        ///< check for running as admin
    bool_t         isRunnig() const;
        ///< check if application already running
    void_t         dirsCreate();
        ///< create all application directories
    bool_t         selfCheck() const;
        ///< self check
    int_t          run();
        ///< run
    virtual int_t  onRun() = 0;
        ///< run handle

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

    // info
    static
    ApplicationInfo & info();
        ///< application information
    static
    void           setInfo(const ApplicationInfo &info);
        ///< set application information
    static
    const BuildInfo &buildInfo();
        ///< build information
    static
    Donate &       donate();
        ///< application donate
    static
    void           setDonate(const Donate &info);
        ///< set application donate

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

protected:
    bool_t                 _isDevel;
    std::ctstring_t        _appGuid;
    static ApplicationInfo _info;
    static Donate          _donate;

    xNO_COPY_ASSIGN(Application)
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
