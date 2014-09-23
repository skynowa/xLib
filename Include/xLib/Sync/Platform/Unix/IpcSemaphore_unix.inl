/**
 * \file  IpcSemaphore.inl
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
IpcSemaphore::_construct_impl()
{
    // sem_init
}
//-------------------------------------------------------------------------------------------------
inline void_t
IpcSemaphore::_destruct_impl()
{
    int_t iRv = ::sem_close(_handle);  _handle = xPTR_NULL;
    xTEST_DIFF(iRv, - 1);

    // sem_destroy
    // sem_unlink
}
//-------------------------------------------------------------------------------------------------
inline long_t
IpcSemaphore::_valueMax_impl() const
{
    long_t liRv = 0;

#if   defined(SEM_VALUE_MAX)
    liRv = SEM_VALUE_MAX;
#elif defined(_SC_SEM_VALUE_MAX)
    liRv = ::sysconf(_SC_SEM_VALUE_MAX);
    xTEST_DIFF(liRv, - 1L);
#else
    #pragma message("xLib: IpcSemaphore::_valueMax_impl() - n/a")
    liRv = 0L;
#endif

    return liRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
IpcSemaphore::_create_impl(
    clong_t         &a_initialValue,
    std::ctstring_t &a_name
)
{
    std::ctstring_t unixName    = Const::unixSlash() + a_name;
    const mode_t    modeDefault = S_IRWXU | S_IRGRP |  S_IXGRP | S_IROTH | S_IXOTH;

    handle_t hRv = ::sem_open(unixName.c_str(), O_CREAT | O_RDWR, modeDefault, a_initialValue);
    xTEST_DIFF(hRv, static_cast<handle_t>( SEM_FAILED ));

    _handle = hRv;
    _name   = unixName;
}
//-------------------------------------------------------------------------------------------------
inline void_t
IpcSemaphore::_open_impl(
    std::ctstring_t &a_name
)
{
    std::ctstring_t unixName    = Const::unixSlash() + a_name;
    const mode_t    modeDefault = S_IRWXU | S_IRGRP |  S_IXGRP | S_IROTH | S_IXOTH;

    handle_t hRv = ::sem_open(unixName.c_str(), O_RDWR, modeDefault, 0U);
    xTEST_DIFF(hRv, static_cast<handle_t>( SEM_FAILED ));

    _handle = hRv;
    _name   = unixName;
}
//-------------------------------------------------------------------------------------------------
inline void_t
IpcSemaphore::_post_impl() const
{
    int_t iRv = ::sem_post(_handle);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
inline void_t
IpcSemaphore::_wait_impl(
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
    int_t nativeError = 0;

    for ( ; ; ) {
        iRv       = ::sem_timedwait(_handle, &tmsTimeout);
        nativeError = errno;

        xCHECK_DO(! (iRv == - 1 && nativeError == EINTR), break);
    }
#endif

    if (iRv == - 1) {
        if (ETIMEDOUT == nativeError) {
            // timeout
            xTEST_FAIL;
        } else {
            xTEST_FAIL;
        }
    }
}
//-------------------------------------------------------------------------------------------------
inline long_t
IpcSemaphore::_value_impl() const
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
IpcSemaphore::_isValid_impl() const
{
    return (_handle != xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
