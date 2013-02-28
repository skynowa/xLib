/**
 * \file  CxProcess.h
 * \brief process
 */


#ifndef xLib_Sync_CxProcessH
#define xLib_Sync_CxProcessH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleT.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxProcess :
    private CxNonCopyable
    /// process
{
public:
#if   xOS_ENV_WIN
    typedef HANDLE  handle_t; ///< handle
    typedef DWORD   id_t;     ///< ID
#elif xOS_ENV_UNIX
    typedef pid_t   handle_t; ///< handle
    typedef pid_t   id_t;     ///< ID
#endif

    enum ExWaitResult
        /// wait result
    {
        #if   xOS_ENV_WIN
            wrFailed    = WAIT_FAILED,
            wrAbandoned = WAIT_ABANDONED,
            wrObject0   = WAIT_OBJECT_0,
            wrTimeout   = WAIT_TIMEOUT
        #elif xOS_ENV_UNIX
            wrFailed    = - 1,
            wrAbandoned = 0,
            wrObject0   = 1,
            wrTimeout   = 2
        #endif
    };

                    CxProcess ();
    virtual        ~CxProcess ();

    void            create    (const std::tstring_t &csFilePath, const tchar_t *pcszParams, ...);
        ///< execute a file
    ExWaitResult    wait      (const ulong_t &culTimeout) xWARN_UNUSED_RV;
        ///< wait for termination
    void            kill      (const ulong_t &culTimeout);
        ///< kills the calling process and all of its threads

    handle_t        handle    () const xWARN_UNUSED_RV;
        ///< get handle
    id_t            id        () const xWARN_UNUSED_RV;
        ///< get ID
    bool            isCurrent () const xWARN_UNUSED_RV;
        ///< is current
    ulong_t         exitStatus() const xWARN_UNUSED_RV;
        ///< get termination status

    static id_t     idByHandle(const handle_t &chHandle) xWARN_UNUSED_RV;
        ///< get ID by handle
    static handle_t handleById(const id_t &culId) xWARN_UNUSED_RV;
        ///< get handle by ID
    static id_t     idByName  (const std::tstring_t &csProcessName) xWARN_UNUSED_RV;
        ///< get ID by name
    static bool     isRunning (const id_t &culId) xWARN_UNUSED_RV;
        ///< is process running by name (with extension)

private:
    handle_t        _m_hHandle;
#if   xOS_ENV_WIN
    HANDLE          _m_hThread;
#endif
    id_t            _m_ulPid;
    uint_t          _m_uiExitStatus;            ///< exit code
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Sync_CxProcessH
