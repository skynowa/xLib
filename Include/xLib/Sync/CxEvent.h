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

#if defined(xOS_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
class CxEvent :
    public CxNonCopyable
    /// event
{
    public:
        #if defined(xOS_WIN)
        typedef HANDLE          TxHandle;   ///< handle
    #elif defined(xOS_LINUX)
        typedef pthread_cond_t  TxHandle;   ///< handle
    #endif

        enum EObjectState
            /// current object state
        {
            #if defined(xOS_WIN)
                osSignaled = WAIT_OBJECT_0, ///< signaled
                osTimeout  = WAIT_TIMEOUT,  ///< time-out interval elapsed and the object's state is nonsignaled
                osFailed   = WAIT_FAILED    ///< failed
            #elif defined(xOS_LINUX)
                osSignaled = 0,             ///< signaled
                osTimeout  = ETIMEDOUT,     ///< time-out interval elapsed and the object's state is nonsignaled
                osFailed /* other values */ ///< failed
            #endif
        };

    #if defined(xOS_WIN)
        static const ULONG m_culTimeoutInfinite = INFINITE; ///< infinite timeout
    #elif defined(xOS_LINUX)
        static const ULONG m_culTimeoutInfinite = ~(0UL);   ///< infinite timeout
    #endif


                 		  CxEvent    ();
            ///< constructor
        virtual 		 ~CxEvent    ();
            ///< destructor

        TxHandle          hGet       () const;
            ///< get handle
        BOOL              bSet       ();
            ///< signal the event for the waiting thread
        BOOL     		  bReset     ();
            ///< once signaled, the event class must be "reset" before responding to a new signal
        EObjectState      osWait     (const ULONG culTimeout = m_culTimeoutInfinite);
            ///< wait either for the cxevent to be signaled by another thread or for the specified timeout duration
        BOOL     		  bIsSignaled();
            ///< is signaled

    private:
    #if defined(xOS_WIN)
        CxHandle          _m_hEvent;        ///< event
    #elif defined(xOS_LINUX)
        CxCriticalSection _m_csCS;          ///< critical section
        pthread_cond_t    _m_cndCond;       ///< condition variable
        volatile BOOL     _m_bIsSignaled;   ///< is signaled flag
    #endif
};
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxEventH
