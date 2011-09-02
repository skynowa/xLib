/**
 * \file  CxEvent.h
 * \brief event
 */


#include <xLib/Sync/CxEvent.h>


/****************************************************************************
*    public
*
*****************************************************************************/

#if defined(xOS_WIN) || 0
//---------------------------------------------------------------------------
//DONE: CxEvent
CxEvent::CxEvent() :
    _m_hEvent()
{

}
//---------------------------------------------------------------------------
//DONE: ~CxEvent
/*virtual*/
CxEvent::~CxEvent() {

}
//---------------------------------------------------------------------------
//DONE: hGetHandle (A handle to the event object)
HANDLE
CxEvent::hGetHandle() const {
    /*DEBUG*/// n/a

    return _m_hEvent.hGet();
}
//---------------------------------------------------------------------------
//DONE: bCreate (Creates or opens a named or unnamed event object)
BOOL
CxEvent::bCreate(
    const LPSECURITY_ATTRIBUTES  pcsaAttributes,
    const BOOL                   cbManualReset,
    const BOOL                   cbInitialState,
    const std::tstring          &csName
) {
    /*DEBUG*/xASSERT_RET(FALSE == _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/

    HANDLE hRes = NULL;

    hRes = ::CreateEvent(pcsaAttributes, cbManualReset, cbInitialState, CxMacros::pcszAsCString(csName));
    /*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

    _m_hEvent.bSet(hRes);
    /*DEBUG*/// n/a

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bOpen (Opens an existing named event object)
BOOL
CxEvent::bOpen(
    const ULONG         culAccess,
    const BOOL          cbInheritHandle,
    const std::tstring &csName
) {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/

    HANDLE hRes = NULL;

    hRes = ::OpenEvent(culAccess, cbInheritHandle, csName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

    _m_hEvent.bSet(hRes);
    /*DEBUG*/// n/a

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bPulse (Sets the specified event object to the signaled state and then resets it to the nonsignaled state after releasing the appropriate number of waiting threads)
BOOL
CxEvent::bPulse() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/

    BOOL bRes = FALSE;

    bRes = ::PulseEvent(_m_hEvent.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bReset (Sets the specified event object to the nonsignaled state)
BOOL
CxEvent::bReset() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/

    BOOL bRes = FALSE;

    bRes = ::ResetEvent(_m_hEvent.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSet (Sets the specified event object to the signaled state)
BOOL
CxEvent::bSet() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/

    BOOL bRes = FALSE;

    bRes = ::SetEvent(_m_hEvent.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWait (Waits until the specified event is in the signaled state or the time-out interval elapses)
BOOL
CxEvent::bWait(
    const ULONG culTimeout
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/// n/a

    ULONG ulRes = ::WaitForSingleObject(_m_hEvent.hGet(), culTimeout);
    /*DEBUG*/// n/a

    return (WAIT_OBJECT_0 == ulRes);
}
//---------------------------------------------------------------------------
//DONE: bIsSignaled (is signaled)
BOOL
CxEvent::bIsSignaled() const {
    /*DEBUG*/// n/a

    ULONG ulRes = ::WaitForSingleObject(_m_hEvent.hGet(), 0);
    /*DEBUG*/// n/a

    return (FALSE != _m_hEvent.bIsValid()) && (WAIT_OBJECT_0 == ulRes);
}
//---------------------------------------------------------------------------
#elif defined(xOS_LINUX)

#endif


//---------------------------------------------------------------------------
timespec *
getTimeout(
    struct timespec *spec,
    timeout_t        timer
)
{
    static  struct timespec myspec;

    if(spec == NULL)
        spec = &myspec;

#ifdef  PTHREAD_GET_EXPIRATION_NP
    struct timespec offset;

    offset.tv_sec  = timer / 1000;
    offset.tv_nsec = (timer % 1000) * 1000000;
    pthread_get_expiration_np(&offset, sec);
#else
    struct timeval current;

    #if xDEPRECIATE
        SysTime::getTimeOfDay(&current);
    #else
        gettimeofday(&current, NULL);
    #endif

    spec->tv_sec  = current.tv_sec + ((timer + current.tv_usec / 1000) / 1000);
    spec->tv_nsec = ((current.tv_usec / 1000 + timer) % 1000) * 1000000;

#endif
    return spec;
}
//---------------------------------------------------------------------------
CxEvent::CxEvent() {
#if defined(xOS_WIN)
    cond = ::CreateEvent(NULL, TRUE, FALSE, NULL);
    /*DEBUG*/
#elif defined(xOS_LINUX)
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
    pthread_mutex_init(&_mutex, &attr);
    pthread_mutexattr_destroy(&attr);
    pthread_cond_init(&_cond, NULL);

    _signaled = FALSE;
    _count    = 0;
#endif
}
//---------------------------------------------------------------------------
CxEvent::~CxEvent() {
#if defined(xOS_WIN)
    ::CloseHandle(cond);
#elif defined(xOS_LINUX)
    pthread_cond_destroy(&_cond);
    pthread_mutex_destroy(&_mutex);
#endif
}
//---------------------------------------------------------------------------
BOOL
CxEvent::bSignal() {
#if defined(xOS_WIN)
    ::SetEvent(cond);
#elif defined(xOS_LINUX)
    pthread_mutex_lock(&_mutex);

    _signaled = TRUE;
    ++_count;

    pthread_cond_broadcast(&_cond);
    pthread_mutex_unlock(&_mutex);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxEvent::bReset() {
#if defined(xOS_WIN)
    ::ResetEvent(cond);
#elif defined(xOS_LINUX)
    _signaled = FALSE;
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxEvent::bWait() {
#ifdef WIN32
    return (Thread::waitThread(cond, INFINITE) == WAIT_OBJECT_0);
#elif defined(xOS_LINUX)
    return bWait(TIMEOUT_INF);
#endif
}
//---------------------------------------------------------------------------
BOOL
CxEvent::bWait(
    timeout_t timer
)
{
#if defined(xOS_WIN)
    return WAIT_OBJECT_0 == Thread::waitThread(cond, timer);
#elif defined(xOS_LINUX)
    int             rc = 0;
    struct timespec spec;

    pthread_mutex_lock(&_mutex);
    long count = _count;

    while (!_signaled && _count == count) {
        if (TIMEOUT_INF != timer) {
            rc = pthread_cond_timedwait(&_cond, &_mutex, getTimeout(&spec, timer));
        } else {
            pthread_cond_wait(&_cond, &_mutex);
        }

        xCHECK_DO(rc == ETIMEDOUT, break);
    }

    pthread_mutex_unlock(&_mutex);
    xCHECK_RET(rc == ETIMEDOUT, FALSE);

    return TRUE;
#endif
}
//---------------------------------------------------------------------------
