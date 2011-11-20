/**
 * \file  CxEvent.h
 * \brief event (using between threads)
 */


#include <xLib/Sync/CxEvent.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxEvent::CxEvent(
    const bool cbIsAutoReset,
    const bool cbIsSignaled     ///< false - wait, lock
) :
#if xOS_ENV_WIN
    _m_hEvent      ()
#elif xOS_ENV_UNIX
    _m_csCS        (),
    _m_cndCond     (),
    _m_bIsAutoReset(false),
    _m_bIsSignaled (false)
#endif
{
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_DO(false == _m_hEvent.bIsValid(), return);
    /*DEBUG*/

    HANDLE hRes = NULL;

    hRes = ::CreateEvent(NULL, ! cbIsAutoReset, cbIsSignaled, NULL);
    /*DEBUG*/xASSERT_DO(NULL != hRes, return);

    _m_hEvent.bSet(hRes);
    /*DEBUG*/// n/a
#elif xOS_ENV_UNIX
    int iRes = ::pthread_cond_init(&_m_cndCond, NULL);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);

    _m_bIsAutoReset = cbIsAutoReset;
    _m_bIsSignaled  = cbIsSignaled;
#endif
}
//---------------------------------------------------------------------------
CxEvent::~CxEvent() {
#if xOS_ENV_WIN
    // n/a
#elif xOS_ENV_UNIX
    int iRes = ::pthread_cond_destroy(&_m_cndCond);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);
#endif
}
//---------------------------------------------------------------------------
const CxEvent::TxHandle &
CxEvent::hGet() const {
    /*DEBUG*/

#if xOS_ENV_WIN
    return _m_hEvent;
#elif xOS_ENV_UNIX
    return _m_cndCond;
#endif
}
//---------------------------------------------------------------------------
//NOTE: unblock threads blocked on a condition variable
bool
CxEvent::bSet() {
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hEvent.bIsValid(), false);
    /*DEBUG*/

    BOOL bRes = ::SetEvent(hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, false);
#elif xOS_ENV_UNIX
    {
        CxAutoCriticalSection acsAutoCS(_m_csCS);

        if (false == _m_bIsAutoReset) {
            int iRes = ::pthread_cond_broadcast(&_m_cndCond);
            /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), false);
        } else {
            int iRes = ::pthread_cond_signal(&_m_cndCond);
            /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), false);
        }

        _m_bIsSignaled = true;
    }
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxEvent::bReset() {
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hEvent.bIsValid(), false);
    /*DEBUG*/

    BOOL bRes = ::ResetEvent(hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, false);
#elif xOS_ENV_UNIX
    {
        CxAutoCriticalSection acsAutoCS(_m_csCS);

        _m_bIsSignaled = false;
    }
#endif

    return true;
}
//---------------------------------------------------------------------------
CxEvent::EObjectState
CxEvent::osWait(
    const ULONG culTimeout /*= xTIMEOUT_INFINITE*/  ///< in milliseconds
)
{
    /*DEBUG*/// culTimeout - n/a

    EObjectState osRes = osFailed;

#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hEvent.bIsValid(), osFailed);

    osRes = static_cast<EObjectState>( ::WaitForSingleObject(hGet(), culTimeout) );
#elif xOS_ENV_UNIX
    {
        CxAutoCriticalSection acsAutoCS(_m_csCS);

        int iRes = 0;

        if (false == _m_bIsSignaled) {
            ////xCHECK_RET(! culTimeout, osTimeout);    // no time for waiting

            timespec tsTime = {0};

            if (xTIMEOUT_INFINITE != culTimeout) {
                // set timeout
                timeval tvNow  = {0};

                iRes = ::gettimeofday(&tvNow, NULL);
                /*DEBUG*/xASSERT_RET(- 1 != iRes, osFailed);

                tsTime.tv_sec  = tvNow.tv_sec + culTimeout / 1000;
                tsTime.tv_nsec = (((culTimeout % 1000) * 1000 + tvNow.tv_usec) % 1000000) * 1000;
            }

            // wait until condition thread returns control
            do {
                if (xTIMEOUT_INFINITE != culTimeout) {
                    iRes = ::pthread_cond_timedwait(&_m_cndCond, const_cast<CxCriticalSection::TxHandle *>( &_m_csCS.hGet() ), &tsTime);
                } else {
                    iRes = ::pthread_cond_wait     (&_m_cndCond, const_cast<CxCriticalSection::TxHandle *>( &_m_csCS.hGet() ));
                }
            }
            while (!iRes && !_m_bIsSignaled);
        } else {
            iRes = 0;
        }

        // adjust signaled member
        switch (iRes) {
            case 0:         { xCHECK_DO(false != _m_bIsAutoReset, _m_bIsSignaled = false);
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
bool
CxEvent::bIsSignaled() {
    /*DEBUG*/// n/a

#if xOS_ENV_WIN
    ULONG ulRes = ::WaitForSingleObject(hGet(), 0UL);
    /*DEBUG*/// n/a

    return (false != _m_hEvent.bIsValid()) && (osSignaled == ulRes);
#elif xOS_ENV_UNIX
    return _m_bIsSignaled;
#endif
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
