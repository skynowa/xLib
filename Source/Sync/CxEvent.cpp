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
CxEvent::CxEvent() :
#if defined(xOS_WIN)
	_m_hEvent     ()
#elif defined(xOS_LINUX)
	_m_csCS       (),
	_m_cndCond    (),
	_m_bIsSignaled(FALSE)
#endif
{
#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(FALSE == _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/

    HANDLE hRes = NULL;

    hRes = ::CreateEvent(NULL, TRUE/*manual reset*/, FALSE/*initial state*/, NULL);
    /*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

    _m_hEvent.bSet(hRes);
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    INT iRes = pthread_cond_init(const_cast<TxHandle *>( &hGet() ), NULL);
    /*DEBUG*/xASSERT_DO(0 == iRes, return);

    _m_bIsSignaled = FALSE;
#endif
}
//---------------------------------------------------------------------------
CxEvent::~CxEvent() {
#if defined(xOS_WIN)
    // n/a
#elif defined(xOS_LINUX)
    INT iRes = pthread_cond_destroy(const_cast<TxHandle *>( &hGet() ));
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

        INT iRes = pthread_cond_broadcast(const_cast<TxHandle *>( &hGet() ));
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
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);

    osRes = static_cast<EObjectState>( ::WaitForSingleObject(hGet(), culTimeout) );
#elif defined(xOS_LINUX)
    {
        CxAutoCriticalSection acsAutoCS(_m_csCS);

        for ( ; ; ) {
            xCHECK_DO(TRUE == bIsSignaled(), break);

            if (m_culTimeoutInfinite != culTimeout) {
                timespec tsTime = {0};
                timeval  tvNow  = {0};

                INT iRes = gettimeofday(&tvNow, NULL);
                /*DEBUG*/xASSERT_DO(- 1 != iRes, break);

                tsTime.tv_sec  = tvNow.tv_sec + ((culTimeout + tvNow.tv_usec / 1000) / 1000);
                tsTime.tv_nsec = ((tvNow.tv_usec / 1000 + culTimeout) % 1000) * 1000000;

                osRes = static_cast<EObjectState>( pthread_cond_timedwait(
                                                        const_cast<TxHandle *>( &hGet() ),
                                                        const_cast<CxCriticalSection::TxHandle *>( &_m_csCS.hGet() ),
                                                        &tsTime) );
                xCHECK_DO(osTimeout == osRes, break);
            } else {
                osRes = static_cast<EObjectState>( pthread_cond_wait(
                                                        const_cast<TxHandle *>( &hGet() ),
                                                        const_cast<CxCriticalSection::TxHandle *>( &_m_csCS.hGet() )) );
                xCHECK_DO(osTimeout == osRes, break);
            }
        } // for
    }
#endif

    /*DEBUG*/xASSERT_RET(osSignaled == osRes || osTimeout == osRes, osFailed);

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


/****************************************************************************
*	private
*
*****************************************************************************/

//---------------------------------------------------------------------------
#if defined(xOS_LINUX)
    #if xDEPRECIATE
        timespec *
        CxEvent::_ptsGetTimeout(
            timespec    *ptsTime,
            const ULONG  culTimeout
        )
        {
            /*DEBUG*/// n/a

            static timespec s_tsTime = {0};

            xCHECK_DO(NULL == ptsTime, ptsTime = &s_tsTime);

            timeval tvNow = {0};

            INT iRes = gettimeofday(&tvNow, NULL);
            /*DEBUG*/xASSERT_RET(- 1 != iRes, NULL);

            ptsTime->tv_sec  = tvNow.tv_sec + ((culTimeout + tvNow.tv_usec / 1000) / 1000);
            ptsTime->tv_nsec = ((tvNow.tv_usec / 1000 + culTimeout) % 1000) * 1000000;

            return ptsTime;
        }
    #endif
#endif
//---------------------------------------------------------------------------
