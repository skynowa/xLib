/**
 * \file  IpcSemaphore.inl
 * \brief semaphore
 */


// lib: -lrt

namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::_ctor_impl()
{
    // sem_init
}
//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::_dtor_impl()
{
    int_t iRv = ::sem_close(_handle);  _handle = nullptr;
    xTEST_DIFF(iRv, - 1);

    // sem_destroy
    // sem_unlink
}
//-------------------------------------------------------------------------------------------------
long_t
IpcSemaphore::_valueMax_impl() const
{
    long_t liRv {};

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
void_t
IpcSemaphore::_create_impl(
    clong_t          a_initialValue,
    std::ctstring_t &a_name
)
{
    std::ctstring_t unixName    = Const::unixSlash() + a_name;
    const mode_t    modeDefault = S_IRWXU | S_IRGRP |  S_IXGRP | S_IROTH | S_IXOTH;

    handle_t hRv = ::sem_open(xT2A(unixName).c_str(), O_CREAT | O_RDWR, modeDefault, a_initialValue);
    xTEST(hRv != static_cast<handle_t>(SEM_FAILED));

    _handle = hRv;
    _name   = unixName;
}
//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::_open_impl(
    std::ctstring_t &a_name
)
{
    std::ctstring_t unixName    = Const::unixSlash() + a_name;
    const mode_t    modeDefault = S_IRWXU | S_IRGRP |  S_IXGRP | S_IROTH | S_IXOTH;

    handle_t hRv = ::sem_open(xT2A(unixName).c_str(), O_RDWR, modeDefault, 0U);
    xTEST(hRv != static_cast<handle_t>(SEM_FAILED));

    _handle = hRv;
    _name   = unixName;
}
//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::_post_impl() const
{
    int_t iRv = ::sem_post(_handle);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::_wait_impl(
    culong_t a_timeoutMsec
) const
{
    int_t iRv {- 1};

    // add msec to timespec
    timespec ts {};
    {
        iRv = ::clock_gettime(CLOCK_REALTIME, &ts);
        xTEST_DIFF(iRv, - 1);

		auto timespecAddMsec = [] (long_t a_ms, timespec *a_ts) -> void_t
		{
			long_t sec {};

			sec  = a_ms / 1000;
			a_ms = a_ms - sec * 1000;

			// perform the addition
			a_ts->tv_nsec += a_ms * 1000000;

			// adjust the time
			a_ts->tv_sec += a_ts->tv_nsec / 1000000000 + sec;
			a_ts->tv_nsec = a_ts->tv_nsec % 1000000000;
		};

        timespecAddMsec(static_cast<long_t>(a_timeoutMsec), &ts);
    }

    // wait
    int_t _nativeError {};
	{
	    for ( ; ; ) {
			iRv = ::sem_timedwait(_handle, &ts);
			_nativeError = errno;

			if (iRv == - 1 && _nativeError == EINTR) {
				LogCout() << xT("Restart if interrupted by handler");
				continue;
			}

			break;
		}
	}

    if (iRv == - 1) {
        if (_nativeError == ETIMEDOUT) {
            xTEST(false && "Timed out");
        } else {
            xTEST(false && "Error");
        }

        return;
    }
}
//-------------------------------------------------------------------------------------------------
long_t
IpcSemaphore::_value_impl() const
{
    long_t liRv {- 1L};

    int_t _value {- 1};
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
bool_t
IpcSemaphore::_isValid_impl() const
{
    return (_handle != nullptr);
}
//-------------------------------------------------------------------------------------------------

} // namespace
