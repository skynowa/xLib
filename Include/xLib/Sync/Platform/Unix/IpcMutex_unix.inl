/**
 * \file  IpcMutex.inl
 * \brief mutex
 */


// lib: -lrt


xNAMESPACE_BEGIN2(xl, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
IpcMutex::_create_impl(
    std::ctstring_t &a_name
)
{
    std::ctstring_t unixName    = Const::unixSlash() + a_name;
    const mode_t    modeDefault = S_IRWXU | S_IRGRP |  S_IXGRP | S_IROTH | S_IXOTH;

    handle_t hRv = ::sem_open(xT2A(unixName).c_str(), O_CREAT | O_RDWR, modeDefault, 1U);
    xTEST_DIFF(hRv, static_cast<handle_t>( SEM_FAILED ));

    _handle = hRv;
    _name   = unixName;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
IpcMutex::_open_impl(
    std::ctstring_t &a_name
)
{
    std::ctstring_t unixName    = Const::unixSlash() + a_name;
    const mode_t    modeDefault = S_IRWXU | S_IRGRP |  S_IXGRP | S_IROTH | S_IXOTH;

    handle_t hRv = ::sem_open(xT2A(unixName).c_str(), O_RDWR, modeDefault, 1U);
    xTEST_DIFF(hRv, static_cast<handle_t>( SEM_FAILED ));

    _handle = hRv;
    _name   = unixName;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
IpcMutex::_lock_impl(
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

        (void_t)_Functor::timespecAddMsec(&timeoutMsec, static_cast<long>(a_timeoutMsec));
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
xINLINE void_t
IpcMutex::_unlock_impl() const
{
    int_t iRv = ::sem_post(_handle);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
