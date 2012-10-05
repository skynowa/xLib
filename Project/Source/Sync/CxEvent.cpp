/**
 * \file  CxEvent.h
 * \brief event (using between threads)
 */


#include <xLib/Sync/CxEvent.h>

#include <xLib/Common/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxEvent::CxEvent(
    const bool &a_cbIsAutoReset,
    const bool &a_cbIsSignaled     ///< false - wait, lock
) :
#if   xOS_ENV_WIN
    _m_hEvent       ()
#elif xOS_ENV_UNIX
    _m_mtMutex      (),
    _m_cndCond      (),
    _m_cbIsAutoReset(a_cbIsAutoReset),
    _m_cbInitState  (a_cbIsSignaled),
    _m_bIsSignaled  (false)
#endif
{
#if   xOS_ENV_WIN
    /*DEBUG*/xTEST_EQ(false, _m_hEvent.bIsValid());
    /*DEBUG*/

    HANDLE hRv = ::CreateEvent(NULL, ! a_cbIsAutoReset, a_cbIsSignaled, NULL);
    /*DEBUG*/xTEST_DIFF(static_cast<HANDLE>(NULL), hRv);

    _m_hEvent.vSet(hRv);
    /*DEBUG*/// n/a
#elif xOS_ENV_UNIX
    int iRv = ::pthread_cond_init(&_m_cndCond, NULL);
    /*DEBUG*/xTEST_MSG_EQ(0, iRv, CxLastError::sFormat(iRv));

    _m_bIsSignaled  = a_cbIsSignaled;
#endif
}
//---------------------------------------------------------------------------
CxEvent::~CxEvent() {
#if   xOS_ENV_WIN
    xNA;
#elif xOS_ENV_UNIX
    int iRv = ::pthread_cond_destroy(&_m_cndCond);
    /*DEBUG*/xTEST_MSG_EQ(0, iRv, CxLastError::sFormat(iRv));
#endif
}
//---------------------------------------------------------------------------
const CxEvent::handle_t &
CxEvent::hGet() const {
    /*DEBUG*/

#if   xOS_ENV_WIN
    return _m_hEvent;
#elif xOS_ENV_UNIX
    return _m_cndCond;
#endif
}
//---------------------------------------------------------------------------
// NOTE: unblock threads blocked on a condition variable
void
CxEvent::vSet() {
#if   xOS_ENV_WIN
    /*DEBUG*/xTEST_EQ(true, _m_hEvent.bIsValid());
    /*DEBUG*/

    BOOL blRes = ::SetEvent(hGet().hGet());
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    {
        CxAutoMutex amtAutoMutex(_m_mtMutex);

        if (true == _m_cbIsAutoReset) {
            int iRv = ::pthread_cond_signal(&_m_cndCond);
            /*DEBUG*/xTEST_MSG_EQ(0, iRv, CxLastError::sFormat(iRv));
        } else {
            int iRv = ::pthread_cond_broadcast(&_m_cndCond);
            /*DEBUG*/xTEST_MSG_EQ(0, iRv, CxLastError::sFormat(iRv));
        }

        _m_bIsSignaled = true;
    }
#endif
}
//---------------------------------------------------------------------------
void
CxEvent::vReset() {
#if   xOS_ENV_WIN
    /*DEBUG*/xTEST_EQ(true, _m_hEvent.bIsValid());
    /*DEBUG*/

    BOOL blRes = ::ResetEvent(hGet().hGet());
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    {
        CxAutoMutex amtAutoMutex(_m_mtMutex);

        _m_bIsSignaled = false;
    }
#endif
}
//---------------------------------------------------------------------------
CxEvent::ExObjectState
CxEvent::osWait(
    const ulong_t &a_culTimeout /* = xTIMEOUT_INFINITE */  ///< in milliseconds
)
{
    /*DEBUG*/// culTimeout - n/a

    ExObjectState osRes = osFailed;

#if   xOS_ENV_WIN
    /*DEBUG*/xTEST_EQ(true, _m_hEvent.bIsValid());

    osRes = static_cast<ExObjectState>( ::WaitForSingleObject(hGet().hGet(), a_culTimeout) );
#elif xOS_ENV_UNIX
    {
        CxAutoMutex amtAutoMutex(_m_mtMutex);

        int iRv = 0;

        //if (false == _m_bIsSignaled) {
            timespec tsTimeoutMs = {0};

            if (xTIMEOUT_INFINITE != a_culTimeout) {
                timeval tvNow  = {0};

                iRv = ::gettimeofday(&tvNow, NULL);
                /*DEBUG*/xTEST_DIFF(- 1, iRv);

                tsTimeoutMs.tv_sec  = tvNow.tv_sec + a_culTimeout / 1000;
                tsTimeoutMs.tv_nsec = tvNow.tv_usec * 1000 + (a_culTimeout % 1000) * 1000000;

                // handle overflow
                if (tsTimeoutMs.tv_nsec >= 1000000000) {
                    CxTracer() << xT("xLib: CxEvent::osWait - handle overflow");

                    ++ tsTimeoutMs.tv_sec;
                    tsTimeoutMs.tv_nsec -= 1000000000;
                }
            }

            // wait until condition thread returns control
            do {
                if (xTIMEOUT_INFINITE == a_culTimeout) {
                    iRv = ::pthread_cond_wait     (&_m_cndCond, const_cast<CxMutex::handle_t *>( &_m_mtMutex.hGet() ));
                } else {
                    iRv = ::pthread_cond_timedwait(&_m_cndCond, const_cast<CxMutex::handle_t *>( &_m_mtMutex.hGet() ), &tsTimeoutMs);
                }
            }
            while (!iRv && !_m_bIsSignaled);
        //} else {
        //    iRv = 0;
        //}
        CxTracer() << xTRACE_VAR(iRv);

        // adjust signaled member
        switch (iRv) {
            case 0:
                if (_m_cbIsAutoReset) {
                    _m_bIsSignaled = false;
                }

                osRes = osSignaled;
                break;

            case ETIMEDOUT:
                    osRes = osTimeout;

                    if (_m_cbIsAutoReset) {
                        _m_bIsSignaled = false;
                    } else {
                        osRes = _m_cbInitState ? osSignaled : osTimeout;
                        _m_bIsSignaled = _m_cbInitState;
                    }


                break;

        }

    }
#endif

    /*DEBUG*/xTEST_MSG_EQ(true, osSignaled == osRes || osTimeout == osRes, CxLastError::sFormat(osRes));

    return osRes;
}
//---------------------------------------------------------------------------
bool
CxEvent::bIsSignaled() {
    /*DEBUG*/// n/a

    bool bRv = false;

#if   xOS_ENV_WIN
    DWORD dwRv = ::WaitForSingleObject(hGet().hGet(), 0UL);
    /*DEBUG*/// n/a

    bRv = (false != _m_hEvent.bIsValid() && osSignaled == dwRv);
#elif xOS_ENV_UNIX
    bRv = _m_bIsSignaled;
#endif

    return bRv;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
