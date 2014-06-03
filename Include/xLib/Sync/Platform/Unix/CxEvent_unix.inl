/**
 * \file  CxEvent.h
 * \brief event (using between threads)
 */


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxEvent::_dectruct_impl()
{
    int_t iRv = - 1;

    iRv = ::pthread_cond_destroy(&_cond);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    iRv = ::pthread_mutex_destroy(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
}
//-------------------------------------------------------------------------------------------------
inline const CxEvent::handle_t &
CxEvent::_handle_impl() const
{
    return _cond;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxEvent::_create_impl()
{

    int_t iRv = - 1;

    iRv = ::pthread_mutex_init(&_mutex, xPTR_NULL);   // mutex not recursive
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    iRv = ::pthread_cond_init(&_cond, xPTR_NULL);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxEvent::_set_impl()
{
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

}
//-------------------------------------------------------------------------------------------------
inline void_t
CxEvent::_reset_impl()
{
    int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    {
        _isSignaled = false;
    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
}
//-------------------------------------------------------------------------------------------------
inline CxEvent::ExObjectState
CxEvent::_wait_impl(
    culong_t &a_timeoutMs /* = xTIMEOUT_INFINITE */  ///< in milliseconds
)
{
    ExObjectState osRv = osFailed;

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

    return osRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxEvent::_isSignaled_impl() const
{
    // n/a

    return _isSignaled;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
