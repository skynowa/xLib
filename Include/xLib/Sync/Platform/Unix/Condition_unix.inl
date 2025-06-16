/**
 * \file   Condition.inl
 * \brief  condition variable
 */


namespace xl::sync
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Condition::_dtor_impl()
{
    int_t iRv = - 1;

    iRv = ::pthread_cond_destroy(&_handle);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));

    iRv = ::pthread_mutex_destroy(&_mutex);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
}
//-------------------------------------------------------------------------------------------------
const pthread_mutex_t &
Condition::mutex() const
{
    return _mutex;
}
//-------------------------------------------------------------------------------------------------
const pthread_cond_t &
Condition::handle() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
void_t
Condition::_create_impl()
{
    int_t iRv = - 1;

    iRv = ::pthread_mutex_init(&_mutex, nullptr); // mutex not recursive
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));

    iRv = ::pthread_cond_init(&_handle, nullptr);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
}
//-------------------------------------------------------------------------------------------------
void_t
Condition::_wait_impl(
    culong_t &a_timeoutMs
)
{
    int_t iRv = - 1;

    // wait until condition thread returns control
    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));

    for ( ; ; ) {
        if (a_timeoutMs == xTIMEOUT_INFINITE) {
            iRv = ::pthread_cond_wait(&_handle, &_mutex);
        } else {
            timespec timeoutMs {};
            timeval  timeNow   {};

            iRv = ::gettimeofday(&timeNow, nullptr);
            xTEST_DIFF(iRv, - 1);

            timeoutMs.tv_sec  = timeNow.tv_sec + static_cast<time_t>(a_timeoutMs) / 1000;
            timeoutMs.tv_nsec = timeNow.tv_usec * 1000 + (static_cast<time_t>(a_timeoutMs) % 1000) * 1000000;

            // handle overflow
            if (timeoutMs.tv_nsec >= 1000000000) {
            	LogCoutWarning() << xT("xLib: Condition::vWait - handle overflow");

                ++ timeoutMs.tv_sec;
                timeoutMs.tv_nsec -= 1000000000;
            }

            iRv = ::pthread_cond_timedwait(&_handle, &_mutex, &timeoutMs);
        }

        xCHECK_DO(iRv, break);
    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
}
//-------------------------------------------------------------------------------------------------
void_t
Condition::_signal_impl()
{
    int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));

    {
        iRv = ::pthread_cond_signal(&_handle);
        xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
}
//-------------------------------------------------------------------------------------------------
void_t
Condition::_broadcast_impl()
{
     int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));

    {
        iRv = ::pthread_cond_broadcast(&_handle);
        xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
}
//-------------------------------------------------------------------------------------------------

} // namespace
