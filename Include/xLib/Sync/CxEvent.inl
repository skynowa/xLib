/**
 * \file  CxEvent.h
 * \brief event (using between threads)
 */


#include <xLib/Log/CxTrace.h>


xNAMESPACE2_BEGIN(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxEvent::CxEvent(
    cbool_t &a_isAutoReset,    ///< is auto reset
    cbool_t &a_isSignaled      ///< is signaled (false - wait, lock)
) :
#if   xOS_ENV_WIN
    _event      (),
#elif xOS_ENV_UNIX
    _mutex      (),
    _cond       (),
    _isSignaled (a_isSignaled),
#endif
    _isAutoReset(a_isAutoReset),
    _initState  (a_isSignaled)
{
}
//-------------------------------------------------------------------------------------------------
inline
CxEvent::~CxEvent()
{
#if   xOS_ENV_WIN
    xNA;
#elif xOS_ENV_UNIX
    int_t iRv = - 1;

    iRv = ::pthread_cond_destroy(&_cond);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    iRv = ::pthread_mutex_destroy(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------
inline const CxEvent::handle_t &
CxEvent::handle() const
{
#if   xOS_ENV_WIN
    return _event;
#elif xOS_ENV_UNIX
    return _cond;
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxEvent::create()
{
#if   xOS_ENV_WIN
    xTEST_EQ(false, _event.isValid());

    HANDLE hRv = ::CreateEvent(xPTR_NULL, ! _isAutoReset, _initState, xPTR_NULL);
    xTEST_DIFF(hRv, static_cast<HANDLE>(xPTR_NULL));

    _event.set(hRv);
    // n/a
#elif xOS_ENV_UNIX
    int_t iRv = - 1;

    iRv = ::pthread_mutex_init(&_mutex, xPTR_NULL);   // mutex not recursive
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    iRv = ::pthread_cond_init(&_cond, xPTR_NULL);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------
// NOTE: unblock threads blocked on a condition variable
inline void_t
CxEvent::set()
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _event.isValid());

    BOOL blRv = ::SetEvent(handle().get());
    xTEST_DIFF(blRv, FALSE);
#elif xOS_ENV_UNIX
    int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    {
        if (_isAutoReset) {
            iRv = ::pthread_cond_signal(&_cond);
            xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
        } else {
            iRv = ::pthread_cond_broadcast(&_cond);
            xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
        }

        _isSignaled = true;
    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxEvent::reset()
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _event.isValid());

    BOOL blRv = ::ResetEvent(handle().get());
    xTEST_DIFF(blRv, FALSE);
#elif xOS_ENV_UNIX
    int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    {
        _isSignaled = false;
    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------
inline CxEvent::ExObjectState
CxEvent::wait(
    culong_t &a_timeoutMs /* = xTIMEOUT_INFINITE */  ///< in milliseconds
)
{
    // timeoutMs - n/a

    ExObjectState osRv = osFailed;

#if   xOS_ENV_WIN
    xTEST_EQ(true, _event.isValid());

    osRv = static_cast<ExObjectState>( ::WaitForSingleObject(handle().get(), a_timeoutMs) );
#elif xOS_ENV_UNIX
    int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    {
        // if (!_isSignaled) {
            timespec timeoutMsec = {0, 0};

            if (a_timeoutMs != xTIMEOUT_INFINITE) {
                timeval timeNow  = {0, 0};

                iRv = ::gettimeofday(&timeNow, xPTR_NULL);
                xTEST_DIFF(iRv, - 1);

                timeoutMsec.tv_sec  = timeNow.tv_sec + a_timeoutMs / 1000;
                timeoutMsec.tv_nsec = timeNow.tv_usec * 1000 + (a_timeoutMs % 1000) * 1000000;

                // handle overflow
                if (timeoutMsec.tv_nsec >= 1000000000) {
                    CxTrace() << xT("::: xLib: CxEvent::osWait - handle overflow :::");

                    ++ timeoutMsec.tv_sec;
                    timeoutMsec.tv_nsec -= 1000000000;
                }
            }

            // wait until condition thread returns control
            do {
                if (a_timeoutMs == xTIMEOUT_INFINITE) {
                    iRv = ::pthread_cond_wait     (&_cond, &_mutex);
                } else {
                    iRv = ::pthread_cond_timedwait(&_cond, &_mutex, &timeoutMsec);
                }
            }
            while (!iRv && !_isSignaled);
        // } else {
        //    iRv = 0;
        // }
        CxTrace() << xTRACE_VAR(iRv);

        // adjust signaled member
        switch (iRv) {
        case 0:
            if (_isAutoReset) {
                _isSignaled = false;
            }

            osRv = osSignaled;
            break;
        case ETIMEDOUT:
            osRv = osTimeout;

            if (_isAutoReset) {
                _isSignaled = false;
            } else {
                osRv = _initState ? osSignaled : osTimeout;
                _isSignaled = _initState;
            }
            break;
        }

    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
#endif

    xTEST_MSG_EQ((osRv == osSignaled) || (osRv == osTimeout), true, CxLastError::format(osRv));

    return osRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxEvent::isSignaled() const
{
    // n/a

    bool_t bRv = false;

#if   xOS_ENV_WIN
    DWORD dwRv = ::WaitForSingleObject(handle().get(), 0UL);
    // n/a

    bRv = (_event.isValid() && dwRv == osSignaled);
#elif xOS_ENV_UNIX
    bRv = _isSignaled;
#endif

    return bRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, sync)
