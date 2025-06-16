/**
 * \file  Process.h
 * \brief process
 *
 * \feat
 *
 * - get/set process name
 * - check file for xecutable writes
 * - set environments variables
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
namespace xl::sync
{

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

    enum class WaitStatus : ulong_t
        /// wait status
    {
    #if   xENV_WIN
        Failed    = WAIT_FAILED,    // 0xFFFFFFFF
        Ok        = WAIT_OBJECT_0,  // 0x00000000L
        Abandoned = WAIT_ABANDONED,	// 0x00000080L (Not Ok)
        Timeout   = WAIT_TIMEOUT    // 0x00000102L
    #elif xENV_UNIX
        Failed    = 0,
        Ok        = 1,
        Abandoned = 2,
        Timeout   = 3
    #endif
    };
    xUSING_CONST(WaitStatus);

///\name ctors, dtor
///\{
			 Process();
	virtual ~Process();

	xNO_COPY_ASSIGN(Process);
///\}

    void_t     create(std::ctstring_t &filePath, std::cvec_tstring_t &params,
                   const std::set<std::pair_tstring_t> &envs, std::tstring_t *stdOut,
                   std::tstring_t *stdError);
        ///< execute a file
        ///< TODO: envs as system::Env
    WaitStatus wait(culong_t &timeoutMsec);
        ///< wait for termination
    void_t     kill(culong_t &timeoutMsec);
        ///< kills the calling process and all of its threads

    handle_t   handle() const;
        ///< get handle
    id_t       id() const;
        ///< get ID
    std::tstring_t name() const;
        ///< get name
    void_t     setName(std::ctstring_t &name) const;
        ///< set name
    bool_t     isValid() const;
        ///< check for the handles, IDs validness
    bool_t     isExists() const;
        ///< check for the existence of a process ID or process group ID, see isRunning()
    bool_t     isCurrent() const;
        ///< is current
    ulong_t    exitStatus() const;
        ///< get termination status

xPUBLIC_STATIC:
///\name Handles, IDs
///\{
	static id_t     idByHandle(const handle_t &handle);
		///< get ID by handle
	static handle_t handleById(const id_t &id);
		///< get handle by ID
	static id_t     idByName(std::ctstring_t &processName);
		///< get ID by name
	static bool_t   isRunning(const id_t &id);
		///< is process running by name (with extension)
	static void_t   ids(std::vector<Process::id_t> *ids);
		///< get all IDs of current processes
///\}

///\name Current process
///\{
	static bool_t   isCurrent(const Process::id_t &id);
		///< is current id
	static id_t     currentId();
		///< process ID of the calling process
	static id_t     currentParentId();
		///< process ID of the parent of the calling process
	static handle_t currentHandle();
		///< get pseudo handle for the calling process
	static void_t   currentExit(cuint_t &exitCode);
		///< ends the calling process and all its threads
	static void_t   currenQuicktExit(cuint_t &exitCode);
		///< Causes normal program termination to occur without completely cleaning the resources
///\}

///\name Execute
///\{
	static void_t execute(std::ctstring_t &filePath, std::cvec_tstring_t &params,
					 const std::set<std::pair_tstring_t> &envs, culong_t waitTimeoutMsec,
					 std::tstring_t *stdOut, std::tstring_t *stdError);
		///< create, wait process
	static void_t execute(std::ctstring_t &filePath, std::cvec_tstring_t &params,
					 std::tstring_t *stdOut, std::tstring_t *stdError);
		///< create, wait process (Without envs, with infinite wait timeout)
	static void_t shellExecute(std::ctstring_t &filePathOrURL, std::cvec_tstring_t &params);
		///< opens a file or URL in the user's preferred application
///\}

private:
    handle_t _handle {};
#if xENV_WIN
    HANDLE   _thread {};
#endif
    id_t     _pid {};
    uint_t   _exitStatus {};    ///< exit code

xPLATFORM_IMPL:
    void_t         _dtor_impl();
    void_t         _create_impl(std::ctstring_t &filePath, std::cvec_tstring_t &params,
                        const std::set<std::pair_tstring_t> &envs, std::tstring_t *stdOut,
                        std::tstring_t *stdError);
    WaitStatus     _wait_impl(culong_t &timeoutMsec);
    void_t         _kill_impl(culong_t &timeoutMsec);
    std::tstring_t _name_impl() const;
    void_t         _setName_impl(std::ctstring_t &name) const;
    bool_t         _isExists_impl() const;
    ulong_t        _exitStatus_impl() const;

    // static
    static id_t     _idByHandle_impl(const handle_t &handle);
    static handle_t _handleById_impl(const id_t &id);
    static id_t     _idByName_impl(std::ctstring_t &processName);
    static void_t   _ids_impl(std::vector<Process::id_t> *ids);
    static bool_t   _isCurrent_impl(const Process::id_t &a_id);
    static id_t     _currentId_impl();

    static id_t     _currentParentId_impl();
    static handle_t _currentHandle_impl();
    static void_t   _currentExit_impl(cuint_t &exitCode);

    static void_t   _shellExecute_impl(std::ctstring_t &filePathOrURL, std::ctstring_t &params);
        ///< TODO: QProcess::startDetached()
        ///< TODO: Process::create() - use ?
    static bool_t   _isUrlFull(std::ctstring_t &url);
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * \file  Process.h
 * \todo
 *
 * - get/set process name
 * - check file for xecutable writes
 * - set environments variables
 *
 * - setLocale
 * - use pipes
 * - stopable, pause, ...  (exit by signal)
 * - restartable (exit by signal)
 * - command line params (usage, ...)
 * - as singleton
 * - multi-process
 */
