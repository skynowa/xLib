/**
 * \file  CxEvent.h
 * \brief event (using between threads)
 */


#include <xLib/Sync/CxEvent.h>

#include <xLib/Common/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxEvent::CxEvent(
    cbool_t &a_cbIsAutoReset,    ///< is auto reset
    cbool_t &a_cbIsSignaled      ///< is signaled (false - wait, lock)
) :
#if xOS_ENV_WIN
    _m_hEvent       (),
#else
    _m_mtMutex      (),
    _m_cndCond      (),
    _m_bIsSignaled  (a_cbIsSignaled),
#endif
    _m_cbIsAutoReset(a_cbIsAutoReset),
    _m_cbInitState  (a_cbIsSignaled)
{
}
//------------------------------------------------------------------------------
CxEvent::~CxEvent() {
#if xOS_ENV_WIN
    xNA;
#else
    int_t iRv = - 1;

    iRv = ::pthread_cond_destroy(&_m_cndCond);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    iRv = ::pthread_mutex_destroy(&_m_mtMutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
const CxEvent::handle_t &
CxEvent::handle() const {
#if xOS_ENV_WIN
    return _m_hEvent;
#else
    return _m_cndCond;
#endif
}
//------------------------------------------------------------------------------
void_t
CxEvent::create() {
#if xOS_ENV_WIN
    xTEST_EQ(false, _m_hEvent.isValid());

    HANDLE hRv = ::CreateEvent(NULL, ! _m_cbIsAutoReset, _m_cbInitState, NULL);
    xTEST_DIFF(static_cast<HANDLE>(NULL), hRv);

    _m_hEvent.set(hRv);
    // n/a
#else
    int_t iRv = - 1;

    iRv = ::pthread_mutex_init(&_m_mtMutex, NULL);   // mutex not recursive
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    iRv = ::pthread_cond_init(&_m_cndCond, NULL);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
// NOTE: unblock threads blocked on a condition variable
void_t
CxEvent::set() {
#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hEvent.isValid());

    BOOL blRes = ::SetEvent(handle().get());
    xTEST_DIFF(FALSE, blRes);
#else
    int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_m_mtMutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    {
        if (_m_cbIsAutoReset) {
            int_t iRv = ::pthread_cond_signal(&_m_cndCond);
            xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
        } else {
            int_t iRv = ::pthread_cond_broadcast(&_m_cndCond);
            xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
        }

        _m_bIsSignaled = true;
    }

    iRv = ::pthread_mutex_unlock(&_m_mtMutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
void_t
CxEvent::reset() {
#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hEvent.isValid());

    BOOL blRes = ::ResetEvent(handle().get());
    xTEST_DIFF(FALSE, blRes);
#else
    int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_m_mtMutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    {
        _m_bIsSignaled = false;
    }

    iRv = ::pthread_mutex_unlock(&_m_mtMutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
CxEvent::ExObjectState
CxEvent::wait(
    culong_t &a_culTimeout /* = xTIMEOUT_INFINITE */  ///< in milliseconds
)
{
    // culTimeout - n/a

    ExObjectState osRes = osFailed;

#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hEvent.isValid());

    osRes = static_cast<ExObjectState>( ::WaitForSingleObject(handle().get(), a_culTimeout) );
#else
    int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_m_mtMutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    {
        int_t iRv = 0;

        // if (!_m_bIsSignaled) {
            timespec tsTimeoutMs = {0};

            if (xTIMEOUT_INFINITE != a_culTimeout) {
                timeval tvNow  = {0};

                iRv = ::gettimeofday(&tvNow, NULL);
                xTEST_DIFF(- 1, iRv);

                tsTimeoutMs.tv_sec  = tvNow.tv_sec + a_culTimeout / 1000;
                tsTimeoutMs.tv_nsec = tvNow.tv_usec * 1000 + (a_culTimeout % 1000) * 1000000;

                // handle overflow
                if (tsTimeoutMs.tv_nsec >= 1000000000) {
                    CxTracer() << xT("::: xLib: CxEvent::osWait - handle overflow :::");

                    ++ tsTimeoutMs.tv_sec;
                    tsTimeoutMs.tv_nsec -= 1000000000;
                }
            }

            // wait until condition thread returns control
            do {
                if (xTIMEOUT_INFINITE == a_culTimeout) {
                    iRv = ::pthread_cond_wait     (&_m_cndCond, &_m_mtMutex);
                } else {
                    iRv = ::pthread_cond_timedwait(&_m_cndCond, &_m_mtMutex, &tsTimeoutMs);
                }
            }
            while (!iRv && !_m_bIsSignaled);
        // } else {
        //    iRv = 0;
        // }
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

    iRv = ::pthread_mutex_unlock(&_m_mtMutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif

    xTEST_MSG_EQ(true, osSignaled == osRes || osTimeout == osRes, CxLastError::format(osRes));

    return osRes;
}
//------------------------------------------------------------------------------
bool_t
CxEvent::isSignaled() {
    // n/a

    bool_t bRv = false;

#if xOS_ENV_WIN
    DWORD dwRv = ::WaitForSingleObject(handle().get(), 0UL);
    // n/a

    bRv = (_m_hEvent.isValid() && osSignaled == dwRv);
#else
    bRv = _m_bIsSignaled;
#endif

    return bRv;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
