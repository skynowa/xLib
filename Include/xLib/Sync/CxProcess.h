/**
 * \file  CxProcess.h
 * \brief process
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxHandleT.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class CxProcess
    /// process
{
public:
#if   xENV_WIN
    typedef HANDLE  handle_t; ///< handle
    typedef DWORD   id_t;     ///< ID
#elif xENV_UNIX
    typedef pid_t   handle_t; ///< handle
    typedef pid_t   id_t;     ///< ID
#endif

    enum ExWaitResult
        /// wait result
    {
        #if   xENV_WIN
            wrFailed    = WAIT_FAILED,
            wrAbandoned = WAIT_ABANDONED,
            wrObject0   = WAIT_OBJECT_0,
            wrTimeout   = WAIT_TIMEOUT
        #elif xENV_UNIX
            wrFailed    = - 1,
            wrAbandoned = 0,
            wrObject0   = 1,
            wrTimeout   = 2
        #endif
    };

                 CxProcess();
    virtual     ~CxProcess();

    void_t       create(std::ctstring_t &filePath, ctchar_t *params, ...);
        ///< execute a file
    ExWaitResult wait(culong_t &timeoutMsec) xWARN_UNUSED_RV;
        ///< wait for termination
    void_t       kill(culong_t &timeoutMsec);
        ///< kills the calling process and all of its threads

    handle_t     handle() const xWARN_UNUSED_RV;
        ///< get handle
    id_t         id() const xWARN_UNUSED_RV;
        ///< get ID
    bool_t       isCurrent() const xWARN_UNUSED_RV;
        ///< is current
    ulong_t      exitStatus() const xWARN_UNUSED_RV;
        ///< get termination status

    static
    id_t         idByHandle(const handle_t &handle) xWARN_UNUSED_RV;
        ///< get ID by handle
    static
    handle_t     handleById(const id_t &id) xWARN_UNUSED_RV;
        ///< get handle by ID
    static
    id_t         idByName(std::ctstring_t &processName) xWARN_UNUSED_RV;
        ///< get ID by name
    static
    bool_t       isRunning(const id_t &id) xWARN_UNUSED_RV;
        ///< is process running by name (with extension)
    static
    void_t       ids(std::vector<CxProcess::id_t> *ids);
        ///< get all IDs of current processes

    // current process
    static
    bool_t       isCurrent(const CxProcess::id_t &id) xWARN_UNUSED_RV;
        ///< is current id
    static
    id_t         currentId() xWARN_UNUSED_RV;
        ///< process ID of the calling process
    static
    id_t         currentParentId() xWARN_UNUSED_RV;
        ///< process ID of the parent of the calling process
    static
    handle_t     currentHandle() xWARN_UNUSED_RV;
        ///< get pseudo handle for the calling process
    static
    void_t       currentExit(cuint_t &exitCode);
        ///< ends the calling process and all its threads

private:
    handle_t     _handle;
#if xENV_WIN
    HANDLE       _thread;
#endif
    id_t         _pid;
    uint_t       _exitStatus;            ///< exit code

    xNO_COPY_ASSIGN(CxProcess)
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxProcess.inl"
