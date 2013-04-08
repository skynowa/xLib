/**
 * \file  CxEvent.h
 * \brief event (using between threads)
 */


#ifndef xLib_Sync_CxEventH
#define xLib_Sync_CxEventH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleT.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxEvent :
    private CxNonCopyable
    /// event
{
public:
#if xOS_ENV_WIN
    typedef CxHandle       handle_t;   ///< handle
#else
    typedef pthread_cond_t handle_t;   ///< handle
#endif

    enum ExObjectState
        /// current object state
    {
        #if xOS_ENV_WIN
            osSignaled = WAIT_OBJECT_0, ///< signaled
            osTimeout  = WAIT_TIMEOUT,  ///< time-out interval elapsed and the object's state is nonsignaled
            osFailed   = WAIT_FAILED    ///< failed
        #else
            osSignaled = 0,             ///< signaled
            osTimeout  = ETIMEDOUT,     ///< time-out interval elapsed and the object's state is nonsignaled
            osFailed /* other values */ ///< failed
        #endif
    };


                      CxEvent   (cbool_t &cbIsAutoReset, cbool_t &cbIsSignaled);
        ///< constructor
    virtual          ~CxEvent   ();
        ///< destructor

    const handle_t &  handle    () const xWARN_UNUSED_RV;
        ///< get handle
    void_t            create    ();
        ///< create
    void_t            set       ();
        ///< signal the event for the waiting thread (!!! unlock !!!)
    void_t            reset     ();
        ///< once signaled, the event class must be "reset" before responding to a new signal
    ExObjectState     wait      (culong_t &culTimeout = xTIMEOUT_INFINITE) xWARN_UNUSED_RV;
        ///< wait either for the CxEvent to be signaled by another thread or for the specified timeout duration
    bool_t            isSignaled() xWARN_UNUSED_RV;
        ///< is signaled

private:
#if xOS_ENV_WIN
    CxHandle          _m_hEvent;        ///< event
#else
    pthread_mutex_t   _m_mtMutex;       ///< mutex
    handle_t          _m_cndCond;       ///< condition variable
    bool_t            _m_bIsSignaled;   ///< is signaled flag
#endif

    cbool_t           _m_cbIsAutoReset; ///< auto-reset flag
    cbool_t           _m_cbInitState;   ///< initial state
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Sync_CxEventH
