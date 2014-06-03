/**
 * \file  CxIpcMutex.inl
 * \brief mutex
 */


// lib: -lrt


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcMutex::_create_impl(
    std::ctstring_t &a_name
)
{
    std::tstring_t unixName = CxConst::unixSlash() + a_name;

    handle_t handle = ::sem_open(unixName.c_str(), O_CREAT | O_RDWR, 0777, 1U);
    xTEST_DIFF(handle, SEM_FAILED);

    _handle = handle;
    _name   = unixName;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcMutex::_open_impl(
    std::ctstring_t &a_name
)
{
    std::ctstring_t unixName = CxConst::unixSlash() + a_name;

    handle_t handle = ::sem_open(unixName.c_str(), O_RDWR, 0777, 1U);
    xTEST_DIFF(handle, SEM_FAILED);

    _handle = handle;
    _name   = unixName;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcMutex::_lock_impl(
    culong_t &a_timeoutMsec
) const
{
    struct _Functor
    {
        static void_t
        timespecAddMsec(
            timespec *a_ts,
            long      a_ms
        )
        {
            long_t sec = 0L;

            sec  = a_ms / 1000;
            a_ms = a_ms - sec * 1000;

            // perform the addition
            a_ts->tv_nsec += a_ms * 1000000;

            // adjust the time
            a_ts->tv_sec += a_ts->tv_nsec / 1000000000 + sec;
            a_ts->tv_nsec = a_ts->tv_nsec % 1000000000;
        }
    };


    int_t    iRv         = - 1;
    timespec timeoutMsec = {0, 0};

    // add msec to timespec
    {
        iRv = ::clock_gettime(CLOCK_REALTIME, &timeoutMsec);
        xTEST_DIFF(iRv, - 1);

        (void_t)_Functor::timespecAddMsec(&timeoutMsec, a_timeoutMsec);
    }

    while ((iRv = ::sem_timedwait(_handle, &timeoutMsec)) == - 1 && (errno == EINTR)) {
        // Restart if interrupted by handler
        continue;
    }

    if (iRv == - 1) {
        if (errno == ETIMEDOUT) {
            // timeout
            xTEST_FAIL;
        } else {
            xTEST_FAIL;
        }
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcMutex::_unlock_impl() const
{
    int_t iRv = ::sem_post(_handle);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
