/**
 * \file  CxEvent.h
 * \brief event
 */


#ifndef xLib_Sync_CxEventH
#define xLib_Sync_CxEventH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#elif defined(xOS_LINUX)

#endif
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
#if defined(xOS_WIN)
    typedef DWORD   timeout_t;
#elif defined(xOS_LINUX)
    typedef unsigned long   timeout_t;

    #define TIMEOUT_INF ~((timeout_t) 0)
#endif


// FIXME: not in win32 implementation
#if !defined(xOS_WIN)
    // FIXME: private declaration ???
    struct  timespec *getTimeout(struct timespec *spec, timeout_t timeout);
#endif // !WIN32

class CxEvent :
    public CxNonCopyable
    /// event
{
    public:
                 CxEvent();
            ///< constructor
        virtual ~CxEvent();
            ///< destructor

    #if defined(xOS_WIN)
        HANDLE   hGetHandle () const;
    #elif defined(xOS_LINUX)

    #endif
            ///< get handle
        BOOL     bCreate();
            ///< create
        BOOL     bReset();
            ///< once signaled, the event class must be "reset" before responding to a new signal
        BOOL     bSet();
            ///< signal the event for the waiting thread
        BOOL     bWait(timeout_t timer) const;
            ///< \brief  wait either for the cxevent to be signaled by another thread or for the specified timeout duration
            ///< \param  timer timeout in milliseconds to wait for a signal
            ///< \return true if signaled, false if timed out
        BOOL     bWait() const;
            ///< wait either for the cxevent to be signaled by another thread            
        BOOL     bIsSignaled() const;
            ///< is signaled

    private:
    #if defined(xOS_WIN)
        CxHandle        _m_hEvent;
    #elif defined(xOS_LINUX)
        pthread_mutex_t _m_mtMutex;
        pthread_cond_t  _m_cndCond;
        BOOL            _m_bIsSignaled;
        LONG            _m_liCount;
    #endif
};
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxEventH
