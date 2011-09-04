/**
 * \file  CxEvent.h
 * \brief event
 */


#include <xLib/Sync/CxEvent.h>


/****************************************************************************
*    public
*
*****************************************************************************/

#if defined(xOS_WIN) && 0
//---------------------------------------------------------------------------
CxEvent::CxEvent() :
    _m_hEvent()
{

}
//---------------------------------------------------------------------------
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
#if !defined(xOS_WIN)
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
#endif
//---------------------------------------------------------------------------
CxEvent::CxEvent() :
#if defined(xOS_WIN)
    _m_hEvent     ()
#elif defined(xOS_LINUX)
    _m_mtMutex    (),
    _m_cndCond    (),
    _m_bIsSignaled(FALSE),
    _m_liCount    (0L)
#endif
{

}
//---------------------------------------------------------------------------
CxEvent::~CxEvent() {
#if defined(xOS_WIN)
    // n/a
#elif defined(xOS_LINUX)
    pthread_cond_destroy(&_m_cndCond);
    pthread_mutex_destroy(&_m_mtMutex);
#endif
}
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
HANDLE
CxEvent::hGetHandle() const {
    /*DEBUG*/// n/a

    return _m_hEvent.hGet();
}
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
BOOL
CxEvent::bCreate()

{
#if defined(xOS_WIN)
    _m_hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
    /*DEBUG*/
#elif defined(xOS_LINUX)
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
    pthread_mutex_init(&_m_mtMutex, &attr);
    pthread_mutexattr_destroy(&attr);

    pthread_cond_init(&_m_cndCond, NULL);

    _m_bIsSignaled = FALSE;
    _m_liCount     = 0;
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxEvent::bSet() {
#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/

    BOOL bRes = FALSE;

    bRes = ::SetEvent(_m_hEvent.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    pthread_mutex_lock(&_m_mtMutex);

    _m_bIsSignaled = TRUE;
    ++ _m_liCount;

    pthread_cond_broadcast(&_m_cndCond);
    pthread_mutex_unlock(&_m_mtMutex);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxEvent::bReset() {
#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/

    BOOL bRes = FALSE;

    bRes = ::ResetEvent(_m_hEvent);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    _m_bIsSignaled = FALSE;
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxEvent::bWait() const {
#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/// n/a

    ULONG ulRes = ::WaitForSingleObject(_m_hEvent, INFINITE);
    /*DEBUG*/// n/a

    return (WAIT_OBJECT_0 == ulRes);
#elif defined(xOS_LINUX)
    return bWait(TIMEOUT_INF);
#endif
}
//---------------------------------------------------------------------------
BOOL
CxEvent::bWait(
    timeout_t culTimeout
) const
{
#if 0
	#if defined(xOS_WIN)
		/*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
		/*DEBUG*/// n/a

		ULONG ulRes = ::WaitForSingleObject(_m_hEvent, culTimeout);
		/*DEBUG*/// n/a

		return (WAIT_OBJECT_0 == ulRes);
	#elif defined(xOS_LINUX)
		int             rc = 0;
		struct timespec spec;

		pthread_mutex_lock(&_m_mtMutex);
		LONG liCount = _m_liCount;

		while (!_m_bIsSignaled && _m_liCount == liCount) {
			if (TIMEOUT_INF != timer) {
				rc = pthread_cond_timedwait(&_m_cndCond, &_m_mtMutex, getTimeout(&spec, timer));
			} else {
				pthread_cond_wait(&_m_cndCond, &_m_mtMutex);
			}

			xCHECK_DO(rc == ETIMEDOUT, break);
		}

		pthread_mutex_unlock(&_m_mtMutex);
		xCHECK_RET(rc == ETIMEDOUT, FALSE);

		return TRUE;
	#endif
#endif

	return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxEvent::bIsSignaled() const {
    /*DEBUG*/// n/a

#if defined(xOS_WIN)
    ULONG ulRes = ::WaitForSingleObject(_m_hEvent, 0);
    /*DEBUG*/// n/a

    return (FALSE != _m_hEvent.bIsValid()) && (WAIT_OBJECT_0 == ulRes);
#elif defined(xOS_LINUX)
    return _m_bIsSignaled;
#endif
}
//---------------------------------------------------------------------------
