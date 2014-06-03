/**
 * \file  CxIpcSemaphore.inl
 * \brief semaphore
 */


// lib: -lrt


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::_construct_impl()
{
    // sem_init
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::_destruct_impl()
{
    int_t iRv = ::sem_close(_handle);  _handle = xPTR_NULL;
    xTEST_DIFF(iRv, - 1);

    // sem_destroy
    // sem_unlink
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::_create_impl(
    clong_t         &a_initialValue,
    std::ctstring_t &a_name
)
{
    std::tstring_t unixName = CxConst::unixSlash() + a_name;

    handle_t hRv = ::sem_open(unixName.c_str(), O_CREAT | O_RDWR, 0777, a_initialValue);
    xTEST_DIFF(hRv, SEM_FAILED);

    _handle = hRv;
    _name   = unixName;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::_open_impl(
    std::ctstring_t &a_name
)
{
    std::tstring_t unixName = CxConst::unixSlash() + a_name;

    handle_t hRv = ::sem_open(unixName.c_str(), O_RDWR, 0777, 0U);
    xTEST_DIFF(hRv, SEM_FAILED);

    _handle = hRv;
    _name   = unixName;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::_post_impl() const
{
    int_t iRv = ::sem_post(_handle);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::_wait_impl(
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


    int_t    iRv        = - 1;
    timespec tmsTimeout = {0, 0};

    // add msec to timespec
    {
        iRv = ::clock_gettime(CLOCK_REALTIME, &tmsTimeout);
        xTEST_DIFF(iRv, - 1);

        (void_t)_Functor::timespecAddMsec(&tmsTimeout, a_timeoutMsec);
    }

#if 0
    while ((iRv = ::sem_timedwait(_handle, &tmsTimeout)) == - 1 && (errno == EINTR)) {
        // Restart if interrupted by handler
        continue;
    }
#else
    int_t lastError = 0;

    for ( ; ; ) {
        iRv       = ::sem_timedwait(_handle, &tmsTimeout);
        lastError = errno;

        xCHECK_DO(! (iRv == - 1 && lastError == EINTR), break);
    }
#endif

    if (iRv == - 1) {
        if (ETIMEDOUT == lastError) {
            // timeout
            xTEST_FAIL;
        } else {
            xTEST_FAIL;
        }
    }
}
//-------------------------------------------------------------------------------------------------
inline long_t
CxIpcSemaphore::_value_impl() const
{
    long_t liRv = - 1L;

    int_t _value = - 1;
    int_t iRv = ::sem_getvalue(_handle, &_value);
    xTEST_DIFF(iRv, - 1);

    liRv = _value;

    return liRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxIpcSemaphore::_isValid_impl() const
{
    return (_handle != xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
