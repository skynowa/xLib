/**
 * \file  CxEvent.h
 * \brief event (using between threads)
 */


#ifndef xLib_Sync_CxEventH
#define xLib_Sync_CxEventH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleT.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxEvent :
    private CxNonCopyable
    /// event
{
    public:
    #if   xOS_ENV_WIN
        typedef CxHandle       handle_t;   ///< handle
    #elif xOS_ENV_UNIX
        typedef pthread_cond_t handle_t;   ///< handle
    #endif

        enum ExObjectState
            /// current object state
        {
            #if   xOS_ENV_WIN
                osSignaled = WAIT_OBJECT_0, ///< signaled
                osTimeout  = WAIT_TIMEOUT,  ///< time-out interval elapsed and the object's state is nonsignaled
                osFailed   = WAIT_FAILED    ///< failed
            #elif xOS_ENV_UNIX
                osSignaled = 0,             ///< signaled
                osTimeout  = ETIMEDOUT,     ///< time-out interval elapsed and the object's state is nonsignaled
                osFailed /* other values */ ///< failed
            #endif
        };


                          CxEvent    (const bool &cbIsAutoReset, const bool &cbIsSignaled);
            ///< constructor
        virtual          ~CxEvent    ();
            ///< destructor

        const handle_t &  hHandle    () const;
            ///< get handle
        void              vSet       ();
            ///< signal the event for the waiting thread (!!! unlock !!!)
        void              vReset     ();
            ///< once signaled, the event class must be "reset" before responding to a new signal
        ExObjectState     osWait     (const ulong_t &culTimeout = xTIMEOUT_INFINITE);
            ///< wait either for the cxevent to be signaled by another thread or for the specified timeout duration
        bool              bIsSignaled();
            ///< is signaled

    private:
    #if   xOS_ENV_WIN
        CxHandle          _m_hEvent;        ///< event
    #elif xOS_ENV_UNIX
        pthread_mutex_t   _m_mtMutex;       ///< mutex
        handle_t          _m_cndCond;       ///< condition variable
        const bool        _m_cbIsAutoReset; ///< auto-reset flag
        const bool        _m_cbInitState;
        bool              _m_bIsSignaled;   ///< is signaled flag
    #endif
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxEventH
