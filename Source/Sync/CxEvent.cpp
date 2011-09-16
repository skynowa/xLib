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
    const BOOL cbIsSignaled     ///< FALSE - wait, lock
) :
#if defined(xOS_WIN)
	_m_hEvent      ()
#elif defined(xOS_LINUX)
	_m_csCS        (),
	_m_cndCond     (),
    _m_bIsAutoReset(FALSE),
	_m_bIsSignaled (FALSE)
#endif
{
#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_DO(FALSE == _m_hEvent.bIsValid(), return);
    /*DEBUG*/

    HANDLE hRes = NULL;

    hRes = ::CreateEvent(NULL, ! cbIsAutoReset, cbIsSignaled, NULL);
    /*DEBUG*/xASSERT_DO(NULL != hRes, return);

    _m_hEvent.bSet(hRes);
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    INT iRes = pthread_cond_init(&_m_cndCond, NULL);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);

    _m_bIsAutoReset = cbIsAutoReset;
    _m_bIsSignaled  = cbIsSignaled;
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
const CxEvent::TxHandle &
CxEvent::hGet() const {
    /*DEBUG*/

#if defined(xOS_WIN)
    return _m_hEvent;
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

        if (FALSE == _m_bIsAutoReset) {
            INT iRes = pthread_cond_broadcast(&_m_cndCond);
            /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);
        } else {
            INT iRes = pthread_cond_signal(&_m_cndCond);
            /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);
        }

        _m_bIsSignaled = TRUE;
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
    const ULONG culTimeout /*= xTIMEOUT_INFINITE*/  ///< in milliseconds
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

        INT iRes = 0;

        if (FALSE == _m_bIsSignaled) {
            ////xCHECK_RET(! culTimeout, osTimeout);    // no time for waiting

            timespec tsTime = {0};

            if (xTIMEOUT_INFINITE != culTimeout) {
                // set timeout
                timeval tvNow  = {0};

                iRes = gettimeofday(&tvNow, NULL);
                /*DEBUG*/xASSERT_RET(- 1 != iRes, osFailed);

                tsTime.tv_sec  = tvNow.tv_sec + culTimeout / 1000;
                tsTime.tv_nsec = (((culTimeout % 1000) * 1000 + tvNow.tv_usec) % 1000000) * 1000;
            }

            // wait until condition thread returns control
            do {
                if (xTIMEOUT_INFINITE != culTimeout) {
                    iRes = pthread_cond_timedwait(&_m_cndCond, const_cast<CxCriticalSection::TxHandle *>( &_m_csCS.hGet() ), &tsTime);
                } else {
                    iRes = pthread_cond_wait     (&_m_cndCond, const_cast<CxCriticalSection::TxHandle *>( &_m_csCS.hGet() ));
                }
            }
            while (!iRes && !_m_bIsSignaled);
        } else {
            iRes = 0;
        }

        // adjust signaled member
        switch (iRes) {
            case 0:         { xCHECK_DO(FALSE != _m_bIsAutoReset, _m_bIsSignaled = FALSE);
                              osRes = osSignaled; }  break;
            case ETIMEDOUT: { osRes = osTimeout;  }  break;
            default:        { osRes = osFailed;   }  break;
        }
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
