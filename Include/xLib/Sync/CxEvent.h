/**
 * \file  CxEvent.h
 * \brief event (using between threads)
 */


#ifndef xLib_Sync_CxEventH
#define xLib_Sync_CxEventH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxCriticalSection.h>
#include <xLib/Sync/CxAutoCriticalSection.h>

#if xOS_ENV_WIN
    #include <xLib/Common/Win/CxHandleT.h>
#elif xOS_ENV_UNIX

#endif
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxEvent :
    public CxNonCopyable
    /// event
{
    public:
        #if xOS_ENV_WIN
        typedef CxHandle        TxHandle;   ///< handle
    #elif xOS_ENV_UNIX
        typedef pthread_cond_t  TxHandle;   ///< handle
    #endif

        enum EObjectState
            /// current object state
        {
            #if xOS_ENV_WIN
                osSignaled = WAIT_OBJECT_0, ///< signaled
                osTimeout  = WAIT_TIMEOUT,  ///< time-out interval elapsed and the object's state is nonsignaled
                osFailed   = WAIT_FAILED    ///< failed
            #elif xOS_ENV_UNIX
                osSignaled = 0,             ///< signaled
                osTimeout  = ETIMEDOUT,     ///< time-out interval elapsed and the object's state is nonsignaled
                osFailed /* other values */ ///< failed
            #endif
        };


                           CxEvent    (const bool bIsAutoReset, const bool cbIsSignaled);
            ///< constructor
        virtual          ~CxEvent    ();
            ///< destructor

        const TxHandle &  hGet       () const;
            ///< get handle
        bool              bSet       ();
            ///< signal the event for the waiting thread (!!! unlock !!!)
        bool               bReset     ();
            ///< once signaled, the event class must be "reset" before responding to a new signal
        EObjectState      osWait     (const ulong_t culTimeout = xTIMEOUT_INFINITE);
            ///< wait either for the cxevent to be signaled by another thread or for the specified timeout duration
        bool               bIsSignaled();
            ///< is signaled

    private:
    #if xOS_ENV_WIN
        CxHandle          _m_hEvent;        ///< event
    #elif xOS_ENV_UNIX
        CxCriticalSection _m_csCS;          ///< critical section
        TxHandle          _m_cndCond;       ///< condition variable
        volatile bool     _m_bIsAutoReset;  ///< auto-reset flag
        volatile bool     _m_bIsSignaled;   ///< is signaled flag
    #endif
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxEventH
