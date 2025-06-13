/**
 * \file  Event.h
 * \brief event (using between threads)
 */


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Event::_dectruct_impl()
{
    int_t iRv = - 1;

    iRv = ::pthread_cond_destroy(&_cond);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));

    iRv = ::pthread_mutex_destroy(&_mutex);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
}
//-------------------------------------------------------------------------------------------------
const Event::handle_t &
Event::_handle_impl() const
{
    return _cond;
}
//-------------------------------------------------------------------------------------------------
void_t
Event::_create_impl()
{

    int_t iRv = - 1;

    iRv = ::pthread_mutex_init(&_mutex, nullptr);   // mutex not recursive
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));

    iRv = ::pthread_cond_init(&_cond, nullptr);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
}
//-------------------------------------------------------------------------------------------------
void_t
Event::_set_impl()
{
    int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));

    {
        if (_isAutoReset) {
            iRv = ::pthread_cond_signal(&_cond);
            xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
        } else {
            iRv = ::pthread_cond_broadcast(&_cond);
            xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
        }

        _isSignaled = true;
    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));

}
//-------------------------------------------------------------------------------------------------
void_t
Event::_reset_impl()
{
    int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));

    {
        _isSignaled = false;
    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
}
//-------------------------------------------------------------------------------------------------
Event::ObjectState
Event::_wait_impl(
    culong_t &a_timeoutMs /* = xTIMEOUT_INFINITE */  ///< in milliseconds
)
{
    ObjectState osRv = ObjectState::osFailed;

    int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));

    {
        // if (!_isSignaled) {
            timespec timeoutMsec {};

            if (a_timeoutMs != xTIMEOUT_INFINITE) {
                timeval timeNow  = {0, 0};

                iRv = ::gettimeofday(&timeNow, nullptr);
                xTEST_DIFF(iRv, - 1);

                timeoutMsec.tv_sec  = timeNow.tv_sec + static_cast<time_t>(a_timeoutMs) / 1000;
                timeoutMsec.tv_nsec = timeNow.tv_usec * 1000 + (static_cast<time_t>(a_timeoutMs) % 1000) * 1000000;

                // handle overflow
                if (timeoutMsec.tv_nsec >= 1000000000) {
                	LogCoutWarning() << xT("::: xLib: Event::osWait - handle overflow :::");

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
        LogCout() << xTRACE_VAR(iRv);

        // adjust signaled member
        switch (iRv) {
        case 0:
            if (_isAutoReset) {
                _isSignaled = false;
            }

            osRv = ObjectState::osSignaled;
            break;
        case ETIMEDOUT:
            osRv = ObjectState::osTimeout;

            if (_isAutoReset) {
                _isSignaled = false;
            } else {
                osRv = _initState ? ObjectState::osSignaled : ObjectState::osTimeout;
                _isSignaled = _initState;
            }
            break;
        }

    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));

    return osRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Event::_isSignaled_impl() const
{
    // n/a

    return _isSignaled;
}
//-------------------------------------------------------------------------------------------------

} // namespace
