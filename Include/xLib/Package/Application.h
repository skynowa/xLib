/**
 * \file  Application.h
 * \brief
 *
 * Features:
 * - arguments
 * - signals
 * - build info
 * - configs
 * - donate
 * - locale
 *
 * TODO:
 * - singleton
 * - log
 * - MT
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Package/ApplicationInfo.h>
#include <xLib/Debug/BuildInfo.h>
#include <xLib/Sync/Signal.h>
#include <xLib/Package/Donate.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package
{

class Application
    /// application
{
public:
    enum ExitCode : int
        // exit code (not only as enum)
    {
        Failure = EXIT_FAILURE,
        Success = EXIT_SUCCESS
    };
    xUSING_CONST(ExitCode);

///@name ctors, dtor
///@{
			 Application(std::ctstring_t &appGuid, std::ctstring_t &locale);
	virtual ~Application() = default;

	xNO_DEFAULT_CONSTRUCT(Application)
	xNO_COPY_ASSIGN(Application)
///@}

    void_t         setDevel(cbool_t flag);
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
    ExitCode       run();
        ///< run
    virtual ExitCode onRun() = 0;
        ///< run handle

xPUBLIC_STATIC:
    static
    void_t         exit(cExitCode status);
        ///< terminates the process normally, performing the regular cleanup,
        ///< objects with automatic storage are not destroyed
    static
    void_t         exitFailure();
        ///<
    static
    void_t         exitSuccess();
        ///<
    static
    void_t         terminate();
        ///< calls the current terminate handler
    static
    void_t         abort();
        ///< aborts the current process, producing an abnormal program termination

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

    // info
    static
    const BuildInfo &buildInfo();
        ///< build information
    xPROPERTY_STATIC(ApplicationInfo, info, Info);
        ///< application information
	xPROPERTY_STATIC(Donate, donate, Donate);
        ///< application donate

protected:
    bool_t          _isDevel {};
    std::ctstring_t _appGuid;
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * TODO: Application
 *
 * - usage
 * - params
 */
