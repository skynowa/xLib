/**
 * \file  CxEvent.h
 * \brief event
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
        typedef HANDLE          TxHandle;
    #elif defined(xOS_LINUX)
        typedef pthread_cond_t	TxHandle;
    #endif

                 		  CxEvent    ();
            ///< constructor
        virtual 		 ~CxEvent    ();
            ///< destructor

        const TxHandle &  hGet       () const;
            ///< get handle
        BOOL     		  bReset     ();
            ///< once signaled, the event class must be "reset" before responding to a new signal
        BOOL     		  bSet       ();
            ///< signal the event for the waiting thread
        BOOL     		  bWait      (const ULONG culTimeout);
            ///< \brief  wait either for the cxevent to be signaled by another thread or for the specified timeout duration
            ///< \param  timer timeout in milliseconds to wait for a signal
            ///< \return true if signaled, false if timed out
        BOOL     		  bWait      ();
            ///< wait either for the cxevent to be signaled by another thread
        BOOL     		  bIsSignaled() const;
            ///< is signaled

    private:
    #if defined(xOS_WIN)
        CxHandle          _m_hEvent;
    #elif defined(xOS_LINUX)
        CxCriticalSection _m_csCS;
        pthread_cond_t    _m_cndCond;
        volatile BOOL     _m_bIsSignaled;
        LONG              _m_liCount;
    #endif
};
//---------------------------------------------------------------------------













//---------------------------------------------------------------------------
#if defined(xOS_WIN) && 0
class CxEvent :
    public CxNonCopyable
    /// event
{
    public:
                 CxEvent    ();
        virtual ~CxEvent    ();

        HANDLE   hGetHandle () const;
        BOOL     bCreate    (const PSECURITY_ATTRIBUTES pcsaAttributes, const BOOL cbManualReset, const BOOL cbInitialState, const std::tstring &csName);
        BOOL     bOpen      (const ULONG culAccess, BOOL cbInheritHandle, const std::tstring &csName);
        BOOL     bPulse     () const;
        BOOL     bReset     () const;
        BOOL     bSet       () const;
        BOOL     bWait      (const ULONG culTimeout) const;

        BOOL     bIsSignaled() const;

    private:
        CxHandle _m_hEvent;
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxEventH
