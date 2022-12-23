/**
 * \file  IpcSemaphore.inl
 * \brief semaphore
 */


// lib: -lrt

#ifdef __APPLE__

typedef struct
{
    pthread_mutex_t count_lock;
    pthread_cond_t  count_bump;
    unsigned count;
}
bosal_sem_t;

int sem_init(sem_t *psem, int flags, unsigned count)
{
    bosal_sem_t *pnewsem;
    int result;

    pnewsem = (bosal_sem_t *)malloc(sizeof(bosal_sem_t));
    if (! pnewsem)
    {
        return -1;
    }
    result = pthread_mutex_init(&pnewsem->count_lock, NULL);
    if (result)
    {
        free(pnewsem);
        return result;
    }
    result = pthread_cond_init(&pnewsem->count_bump, NULL);
    if (result)
    {
        pthread_mutex_destroy(&pnewsem->count_lock);
        free(pnewsem);
        return result;
    }
    pnewsem->count = count;
    *psem = (sem_t)pnewsem;
    return 0;
}

int sem_destroy(sem_t *psem)
{
    bosal_sem_t *poldsem;

    if (! psem)
    {
        return EINVAL;
    }
    poldsem = (bosal_sem_t *)*psem;

    pthread_mutex_destroy(&poldsem->count_lock);
    pthread_cond_destroy(&poldsem->count_bump);
    free(poldsem);
    return 0;
}

int sem_post(sem_t *psem)
{
     bosal_sem_t *pxsem;
    int result, xresult;

    if (! psem)
    {
        return EINVAL;
    }
    pxsem = (bosal_sem_t *)*psem;

    result = pthread_mutex_lock(&pxsem->count_lock);
    if (result)
    {
        return result;
    }
    pxsem->count = pxsem->count + 1;

    xresult = pthread_cond_signal(&pxsem->count_bump);

    result = pthread_mutex_unlock(&pxsem->count_lock);
    if (result)
    {
        return result;
    }
    if (xresult)
    {
        errno = xresult;
        return -1;
    }
}

int sem_trywait(sem_t *psem)
{
    bosal_sem_t *pxsem;
    int result, xresult;

    if (! psem)
    {
        return EINVAL;
    }
    pxsem = (bosal_sem_t *)*psem;

    result = pthread_mutex_lock(&pxsem->count_lock);
    if (result)
    {
        return result;
    }
    xresult = 0;

    if (pxsem->count > 0)
    {
        pxsem->count--;
    }
    else
    {
        xresult = EAGAIN;
    }
    result = pthread_mutex_unlock(&pxsem->count_lock);
    if (result)
    {
        return result;
    }
    if (xresult)
    {
        errno = xresult;
        return -1;
    }
    return 0;
}

int sem_wait(sem_t *psem)
{
    bosal_sem_t *pxsem;
    int result, xresult;

    if (! psem)
    {
        return EINVAL;
    }
    pxsem = (bosal_sem_t *)*psem;

    result = pthread_mutex_lock(&pxsem->count_lock);
    if (result)
    {
        return result;
    }
    xresult = 0;

    if (pxsem->count == 0)
    {
        xresult = pthread_cond_wait(&pxsem->count_bump, &pxsem->count_lock);
    }
    if (! xresult)
    {
        if (pxsem->count > 0)
        {
            pxsem->count--;
        }
    }
    result = pthread_mutex_unlock(&pxsem->count_lock);
    if (result)
    {
        return result;
    }
    if (xresult)
    {
        errno = xresult;
        return -1;
    }
    return 0;
}

int sem_timedwait(sem_t *psem, const struct timespec *abstim)
{
    bosal_sem_t *pxsem;
    int result, xresult;

    if (! psem)
    {
        return EINVAL;
    }
    pxsem = (bosal_sem_t *)*psem;

    result = pthread_mutex_lock(&pxsem->count_lock);
    if (result)
    {
        return result;
    }
    xresult = 0;

    if (pxsem->count == 0)
    {
        xresult = pthread_cond_timedwait(&pxsem->count_bump, &pxsem->count_lock, abstim);
    }
    if (! xresult)
    {
        if (pxsem->count > 0)
        {
            pxsem->count--;
        }
    }
    result = pthread_mutex_unlock(&pxsem->count_lock);
    if (result)
    {
        return result;
    }
    if (xresult)
    {
        errno = xresult;
        return -1;
    }
    return 0;
}

#endif


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::_construct_impl()
{
    // sem_init
}
//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::_destruct_impl()
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
				Cout() << xT("Restart if interrupted by handler");
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
