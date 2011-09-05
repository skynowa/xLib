/**
 * \file  CxEvent.h
 * \brief event
 */


#include <xLib/Sync/CxEvent.h>


/****************************************************************************
*    public
*
*****************************************************************************/

#if defined(xOS_WIN)
    const ULONG culTimeoutInfinite = INFINITE;
#elif defined(xOS_LINUX)
    const ULONG culTimeoutInfinite = ~((ULONG) 0);
#endif

//---------------------------------------------------------------------------
// FIXME: getTimeout not in win32 implementation
// FIXME: getTimeout private declaration ???

#if defined(xOS_LINUX)

timespec *
getTimeout(
	struct timespec *spec,
	const ULONG      culTimeout
)
{
	static struct timespec myspec;

	xCHECK_DO(spec == NULL, spec = &myspec);

#ifdef PTHREAD_GET_EXPIRATION_NP
	struct timespec offset;

	offset.tv_sec  = culTimeout / 1000;
	offset.tv_nsec = (culTimeout % 1000) * 1000000;
	pthread_get_expiration_np(&offset, sec);
#else
	struct timeval current;

	#if xDEPRECIATE
		SysTime::getTimeOfDay(&current);
	#else
		gettimeofday(&current, NULL);
	#endif

	spec->tv_sec  = current.tv_sec + ((culTimeout + current.tv_usec / 1000) / 1000);
	spec->tv_nsec = ((current.tv_usec / 1000 + culTimeout) % 1000) * 1000000;

#endif
	return spec;
}

#endif
//---------------------------------------------------------------------------
CxEvent::CxEvent() :
#if defined(xOS_WIN)
	_m_hEvent     ()
#elif defined(xOS_LINUX)
	_m_csCS       (),
	_m_cndCond    (),
	_m_bIsSignaled(FALSE),
	_m_liCount    (0L)
#endif
{
#if defined(xOS_WIN)
    _m_hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
    /*DEBUG*/
#elif defined(xOS_LINUX)
    INT iRes = pthread_cond_init(&_m_cndCond, NULL);
    /*DEBUG*/xASSERT_DO(0 == iRes, return);

    _m_bIsSignaled = FALSE;
    _m_liCount     = 0L;
#endif
}
//---------------------------------------------------------------------------
CxEvent::~CxEvent() {
#if defined(xOS_WIN)
    // n/a
#elif defined(xOS_LINUX)
    INT iRes = pthread_cond_destroy(&_m_cndCond);
    /*DEBUG*/xASSERT_DO(0 == iRes, return);
#endif
}
//---------------------------------------------------------------------------
const CxEvent::TxHandle &
CxEvent::hGet() const {
    /*DEBUG*/

#if defined(xOS_WIN)
    return _m_hEvent.hGet();
#elif defined(xOS_LINUX)
    return _m_cndCond;
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
CxEvent::bSet() {
#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/

    BOOL bRes = ::SetEvent(_m_hEvent.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    {
        CxCriticalSection acsAutoCS(_m_csCS);

        _m_bIsSignaled = TRUE;
        ++ _m_liCount;

        INT iRes = pthread_cond_broadcast(&_m_cndCond);
        /*DEBUG*/xASSERT_RET(0 == iRes, FALSE);
    }
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxEvent::bReset() {
#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/

    BOOL bRes = ::ResetEvent(_m_hEvent);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    {
        CxCriticalSection acsAutoCS(_m_csCS);

        _m_bIsSignaled = FALSE;
        -- _m_liCount;
    }
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxEvent::bWait() {
#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/// n/a

    ULONG ulRes = ::WaitForSingleObject(_m_hEvent, culTimeoutInfinite);
    /*DEBUG*/// n/a

    return (WAIT_OBJECT_0 == ulRes);
#elif defined(xOS_LINUX)
    return bWait(culTimeoutInfinite);
#endif
}
//---------------------------------------------------------------------------
BOOL
CxEvent::bWait(
    const ULONG culTimeout
)
{
#if 1
	#if defined(xOS_WIN)
		/*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
		/*DEBUG*/// n/a

		ULONG ulRes = ::WaitForSingleObject(_m_hEvent, culTimeout);
		/*DEBUG*/// n/a

		return (WAIT_OBJECT_0 == ulRes);
	#elif defined(xOS_LINUX)
		INT             iRes = 0;
		struct timespec spec = {0};

        {
            CxCriticalSection acsAutoCS(_m_csCS);

            LONG liCount = _m_liCount;

            while (!_m_bIsSignaled && _m_liCount == liCount) {
                if (culTimeoutInfinite != culTimeout) {
                    iRes = pthread_cond_timedwait(&_m_cndCond, const_cast<CxCriticalSection::TxHandle *>( &_m_csCS.hGet() ), getTimeout(&spec, culTimeout));
                } else {
                    pthread_cond_wait(&_m_cndCond, const_cast<CxCriticalSection::TxHandle *>( &_m_csCS.hGet() ));
                }

                xCHECK_DO(ETIMEDOUT == iRes, break);
            }
        }

		xCHECK_RET(ETIMEDOUT == iRes, FALSE);

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
