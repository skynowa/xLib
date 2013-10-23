/**
 * \file  CxEvent.h
 * \brief event (using between threads)
 */


#include <xLib/Sync/CxEvent.h>

#include <xLib/Core/CxString.h>
#include <xLib/Log/CxTracer.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxEvent::CxEvent(
    cbool_t &a_isAutoReset,    ///< is auto reset
    cbool_t &a_isSignaled      ///< is signaled (false - wait, lock)
) :
#if xOS_ENV_WIN
    _event       (),
#else
    _mutex      (),
    _cond      (),
    _isSignaled  (a_isSignaled),
#endif
    _isAutoReset(a_isAutoReset),
    _initState  (a_isSignaled)
{
}
//------------------------------------------------------------------------------
CxEvent::~CxEvent()
{
#if xOS_ENV_WIN
    xNA;
#else
    int_t iRv = - 1;

    iRv = ::pthread_cond_destroy(&_cond);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    iRv = ::pthread_mutex_destroy(&_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
const CxEvent::handle_t &
CxEvent::handle() const
{
#if xOS_ENV_WIN
    return _event;
#else
    return _cond;
#endif
}
//------------------------------------------------------------------------------
void_t
CxEvent::create()
{
#if xOS_ENV_WIN
    xTEST_EQ(false, _event.isValid());

    HANDLE hRv = ::CreateEvent(NULL, ! _isAutoReset, _initState, NULL);
    xTEST_DIFF(static_cast<HANDLE>(NULL), hRv);

    _event.set(hRv);
    // n/a
#else
    int_t iRv = - 1;

    iRv = ::pthread_mutex_init(&_mutex, NULL);   // mutex not recursive
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    iRv = ::pthread_cond_init(&_cond, NULL);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
// NOTE: unblock threads blocked on a condition variable
void_t
CxEvent::set()
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _event.isValid());

    BOOL blRes = ::SetEvent(handle().get());
    xTEST_DIFF(FALSE, blRes);
#else
    int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    {
        if (_isAutoReset) {
            int_t iRv = ::pthread_cond_signal(&_cond);
            xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
        } else {
            int_t iRv = ::pthread_cond_broadcast(&_cond);
            xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
        }

        _isSignaled = true;
    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
void_t
CxEvent::reset()
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _event.isValid());

    BOOL blRes = ::ResetEvent(handle().get());
    xTEST_DIFF(FALSE, blRes);
#else
    int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    {
        _isSignaled = false;
    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
CxEvent::ExObjectState
CxEvent::wait(
    culong_t &a_timeoutMs /* = xTIMEOUT_INFINITE */  ///< in milliseconds
)
{
    // timeoutMs - n/a

    ExObjectState osRes = osFailed;

#if xOS_ENV_WIN
    xTEST_EQ(true, _event.isValid());

    osRes = static_cast<ExObjectState>( ::WaitForSingleObject(handle().get(), a_timeoutMs) );
#else
    int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    {
        int_t iRv = 0;

        // if (!_isSignaled) {
            timespec tsTimeoutMs = {0};

            if (xTIMEOUT_INFINITE != a_timeoutMs) {
                timeval tvNow  = {0};

                iRv = ::gettimeofday(&tvNow, NULL);
                xTEST_DIFF(- 1, iRv);

                tsTimeoutMs.tv_sec  = tvNow.tv_sec + a_timeoutMs / 1000;
                tsTimeoutMs.tv_nsec = tvNow.tv_usec * 1000 + (a_timeoutMs % 1000) * 1000000;

                // handle overflow
                if (tsTimeoutMs.tv_nsec >= 1000000000) {
                    CxTracer() << xT("::: xLib: CxEvent::osWait - handle overflow :::");

                    ++ tsTimeoutMs.tv_sec;
                    tsTimeoutMs.tv_nsec -= 1000000000;
                }
            }

            // wait until condition thread returns control
            do {
                if (xTIMEOUT_INFINITE == a_timeoutMs) {
                    iRv = ::pthread_cond_wait     (&_cond, &_mutex);
                } else {
                    iRv = ::pthread_cond_timedwait(&_cond, &_mutex, &tsTimeoutMs);
                }
            }
            while (!iRv && !_isSignaled);
        // } else {
        //    iRv = 0;
        // }
        CxTracer() << xTRACE_VAR(iRv);

        // adjust signaled member
        switch (iRv) {
            case 0:
                if (_isAutoReset) {
                    _isSignaled = false;
                }

                osRes = osSignaled;
                break;
            case ETIMEDOUT:
                osRes = osTimeout;

                if (_isAutoReset) {
                    _isSignaled = false;
                } else {
                    osRes = _initState ? osSignaled : osTimeout;
                    _isSignaled = _initState;
                }
                break;
        }

    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif

    xTEST_MSG_EQ(true, osSignaled == osRes || osTimeout == osRes, CxLastError::format(osRes));

    return osRes;
}
//------------------------------------------------------------------------------
bool_t
CxEvent::isSignaled()
{
    // n/a

    bool_t bRv = false;

#if xOS_ENV_WIN
    DWORD dwRv = ::WaitForSingleObject(handle().get(), 0UL);
    // n/a

    bRv = (_event.isValid() && osSignaled == dwRv);
#else
    bRv = _isSignaled;
#endif

    return bRv;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
