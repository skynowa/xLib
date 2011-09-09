/**
 * \file  CxEvent.h
 * \brief event (using between threads)
 */


#include <xLib/Sync/CxEvent.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxEvent::CxEvent(
    const BOOL cbIsAutoReset,
    const BOOL cbInitialState
) :
#if defined(xOS_WIN)
	_m_hEvent      ()
#elif defined(xOS_LINUX)
	_m_csCS        (),
	_m_cndCond     (),
    _m_bIsAutoReset(cbIsAutoReset),
	_m_bIsSignaled (cbInitialState)
#endif
{
#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_DO(FALSE == _m_hEvent.bIsValid(), return);
    /*DEBUG*/

    HANDLE hRes = NULL;

    hRes = ::CreateEvent(NULL, (FALSE == _m_bIsAutoReset) ? TRUE : FALSE, cbInitialState, NULL);
    /*DEBUG*/xASSERT_DO(NULL != hRes, return);

    _m_hEvent.bSet(hRes);
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    INT iRes = pthread_cond_init(&_m_cndCond, NULL);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);

    #if 0
        if (FALSE == cbInitialState) {
            BOOL bRes = bReset();
            /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
        } else {
            BOOL bRes = bSet();
            /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
        }
    #else
        _m_bIsSignaled = cbInitialState;
    #endif
#endif
}
//---------------------------------------------------------------------------
CxEvent::~CxEvent() {
#if defined(xOS_WIN)
    // n/a
#elif defined(xOS_LINUX)
    INT iRes = pthread_cond_destroy(&_m_cndCond);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);
#endif
}
//---------------------------------------------------------------------------
CxEvent::TxHandle
CxEvent::hGet() const {
    /*DEBUG*/

#if defined(xOS_WIN)
    return _m_hEvent.hGet();
#elif defined(xOS_LINUX)
    return _m_cndCond;
#endif
}
//---------------------------------------------------------------------------
//NOTE: unblock threads blocked on a condition variable
BOOL
CxEvent::bSet() {
#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/

    BOOL bRes = ::SetEvent(hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    {
        CxAutoCriticalSection acsAutoCS(_m_csCS);

        _m_bIsSignaled = TRUE;

        INT iRes = pthread_cond_broadcast(&_m_cndCond);
        /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);
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

    BOOL bRes = ::ResetEvent(hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    {
        CxAutoCriticalSection acsAutoCS(_m_csCS);

        _m_bIsSignaled = FALSE;
    }
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
CxEvent::EObjectState
CxEvent::osWait(
    const ULONG culTimeout /*= m_culTimeoutInfinite*/  ///< in milliseconds
)
{
    /*DEBUG*/// culTimeout - n/a

    EObjectState osRes = osFailed;

#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), osFailed);

    osRes = static_cast<EObjectState>( ::WaitForSingleObject(hGet(), culTimeout) );
#elif defined(xOS_LINUX)
    {
        CxAutoCriticalSection acsAutoCS(_m_csCS);

        for ( ; ; ) {
            xCHECK_DO(TRUE == _m_bIsSignaled, break);

            if (m_culTimeoutInfinite != culTimeout) {
                timespec tsTime = {0};
                timeval  tvNow  = {0};

                INT iRes = gettimeofday(&tvNow, NULL);
                /*DEBUG*/xASSERT_DO(- 1 != iRes, break);

                tsTime.tv_sec  = tvNow.tv_sec + ((culTimeout + tvNow.tv_usec / 1000) / 1000);
                tsTime.tv_nsec = ((tvNow.tv_usec / 1000 + culTimeout) % 1000) * 1000000;

                osRes = static_cast<EObjectState>( pthread_cond_timedwait(
                                                        &_m_cndCond,
                                                        const_cast<CxCriticalSection::TxHandle *>( &_m_csCS.hGet() ),
                                                        &tsTime) );
                xCHECK_DO(osTimeout == osRes, break);
            } else {
                osRes = static_cast<EObjectState>( pthread_cond_wait(
                                                        &_m_cndCond,
                                                        const_cast<CxCriticalSection::TxHandle *>( &_m_csCS.hGet() )) );
                xCHECK_DO(osTimeout == osRes, break);
            }
        } // for

        xCHECK_DO(FALSE != _m_bIsAutoReset && osSignaled == osRes, _m_bIsSignaled = FALSE);
    }
#endif

    /*DEBUG*/xASSERT_MSG_RET(osSignaled == osRes || osTimeout == osRes, CxLastError::sFormat(osRes), osFailed);

    return osRes;
}
//---------------------------------------------------------------------------
BOOL
CxEvent::bIsSignaled() {
    /*DEBUG*/// n/a

#if defined(xOS_WIN)
    ULONG ulRes = ::WaitForSingleObject(hGet(), 0UL);
    /*DEBUG*/// n/a

    return (FALSE != _m_hEvent.bIsValid()) && (osSignaled == ulRes);
#elif defined(xOS_LINUX)
    return _m_bIsSignaled;
#endif
}
//---------------------------------------------------------------------------
