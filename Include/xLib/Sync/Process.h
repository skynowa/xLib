/**
 * \file  Process.h
 * \brief process
 *
 * Features:
 * - get/set process name
 * - check file for xecutable writes
 * - set environments variables
 *
 * TODO: setLocale
 * TODO: use pipes
 * TODO: stopable, pause, ...  (exit by signal)
 * TODO: restartable (exit by signal)
 * TODO: command line params (usage, ...)
 * TODO: as singleton
 * TODO: multi-process
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, sync)

class Process
    /// process
{
public:
#if   xENV_WIN
    using handle_t = HANDLE; ///< handle
    using id_t     = DWORD;  ///< ID
#elif xENV_UNIX
    using handle_t = pid_t;  ///< handle
    using id_t     = pid_t;  ///< ID
#endif

    enum class WaitStatus
        /// wait status
    {
    #if   xENV_WIN
        Failed    = WAIT_FAILED,
        Abandoned = WAIT_ABANDONED,
        Object0   = WAIT_OBJECT_0,
        Timeout   = WAIT_TIMEOUT
    #elif xENV_UNIX
        Failed    = - 1,
        Abandoned = 0,
        Object0   = 1,
        Timeout   = 2
    #endif
    };

               Process();
    virtual   ~Process();

    void_t     create(std::ctstring_t &filePath, std::cvec_tstring_t &params,
                   const std::set<std::pair_tstring_t> &envs, std::tstring_t *stdOut,
                   std::tstring_t *stdError);
        ///< execute a file
    WaitStatus wait(culong_t &timeoutMsec) xWARN_UNUSED_RV;
        ///< wait for termination
    void_t     kill(culong_t &timeoutMsec);
        ///< kills the calling process and all of its threads

    handle_t   handle() const xWARN_UNUSED_RV;
        ///< get handle
    id_t       id() const xWARN_UNUSED_RV;
        ///< get ID
    std::tstring_t name() const xWARN_UNUSED_RV;
        ///< get name
    void_t     setName(std::ctstring_t &name) const;
        ///< set name
    bool_t     isValid() const xWARN_UNUSED_RV;
        ///< check for the handles, IDs validness
    bool_t     isExists() const xWARN_UNUSED_RV;
        ///< check for the existence of a process ID or process group ID, see isRunning()
    bool_t     isCurrent() const xWARN_UNUSED_RV;
        ///< is current
    ulong_t    exitStatus() const xWARN_UNUSED_RV;
        ///< get termination status

xPUBLIC_STATIC:
	// Hanfles, IDs
    static
    id_t       idByHandle(const handle_t &handle) xWARN_UNUSED_RV;
        ///< get ID by handle
    static
    handle_t   handleById(const id_t &id) xWARN_UNUSED_RV;
        ///< get handle by ID
    static
    id_t       idByName(std::ctstring_t &processName) xWARN_UNUSED_RV;
        ///< get ID by name
    static
    bool_t     isRunning(const id_t &id) xWARN_UNUSED_RV;
        ///< is process running by name (with extension)
    static
    void_t     ids(std::vector<Process::id_t> *ids);
        ///< get all IDs of current processes

    // current process
    static
    bool_t     isCurrent(const Process::id_t &id) xWARN_UNUSED_RV;
        ///< is current id
    static
    id_t       currentId() xWARN_UNUSED_RV;
        ///< process ID of the calling process
    static
    id_t       currentParentId() xWARN_UNUSED_RV;
        ///< process ID of the parent of the calling process
    static
    handle_t   currentHandle() xWARN_UNUSED_RV;
        ///< get pseudo handle for the calling process
    static
    void_t     currentExit(cuint_t &exitCode);
        ///< ends the calling process and all its threads
    static
    void_t     currenQuicktExit(cuint_t &exitCode);
        ///< Causes normal program termination to occur without completely cleaning the resources

	// Etc
    static
    void_t     execute(std::ctstring_t &filePath, std::cvec_tstring_t &params,
                   const std::set<std::pair_tstring_t> &envs, culong_t waitTimeoutMsec,
                   std::tstring_t *stdOut, std::tstring_t *stdError);
        ///< create, wait process

private:
    handle_t _handle {};
#if xENV_WIN
    HANDLE   _thread {};
#endif
    id_t     _pid {};

    uint_t _exitStatus {};    ///< exit code

    xNO_COPY_ASSIGN(Process)

xPLATFORM_IMPL:
    void_t     _destruct_impl();
    void_t     _create_impl(std::ctstring_t &filePath, std::cvec_tstring_t &params,
                    const std::set<std::pair_tstring_t> &envs, std::tstring_t *stdOut,
                    std::tstring_t *stdError);
    WaitStatus _wait_impl(culong_t &timeoutMsec) xWARN_UNUSED_RV;
    void_t     _kill_impl(culong_t &timeoutMsec);
    std::tstring_t _name_impl() const xWARN_UNUSED_RV;
    void_t     _setName_impl(std::ctstring_t &name) const;
    bool_t     _isExists_impl() const;
    ulong_t    _exitStatus_impl() const xWARN_UNUSED_RV;

    static
    id_t       _idByHandle_impl(const handle_t &handle) xWARN_UNUSED_RV;
    static
    handle_t   _handleById_impl(const id_t &id) xWARN_UNUSED_RV;
    static
    id_t       _idByName_impl(std::ctstring_t &processName) xWARN_UNUSED_RV;
    static
    void_t     _ids_impl(std::vector<Process::id_t> *ids);
    static
    bool_t     _isCurrent_impl(const Process::id_t &a_id);
    static
    id_t       _currentId_impl() xWARN_UNUSED_RV;

    static
    id_t       _currentParentId_impl() xWARN_UNUSED_RV;
    static
    handle_t   _currentHandle_impl() xWARN_UNUSED_RV;
    static
    void_t     _currentExit_impl(cuint_t &exitCode);
};

xNAMESPACE_END2(xl, sync)
//-------------------------------------------------------------------------------------------------
