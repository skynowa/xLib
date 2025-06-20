/**
 * \file  Mutex.inl
 * \brief mutex
 */


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Mutex::_dtor_impl()
{
    int_t iRv = ::pthread_mutex_destroy(&_handle);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
}
//-------------------------------------------------------------------------------------------------
void_t
Mutex::_create_impl()
{
    int_t iRv = - 1;

    pthread_mutexattr_t attr;    // n/a {{0}}

    iRv = ::pthread_mutexattr_init(&attr);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));

    iRv = ::pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_PRIVATE);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));

    // TODO: [skynowa] Mutex::create() - Unix - PTHREAD_MUTEX_RECURSIVE
#if 1
    iRv = ::pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
#endif

    {
        iRv = ::pthread_mutex_init(&_handle, &attr);
        xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
    }

    iRv = ::pthread_mutexattr_destroy(&attr);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
}
//-------------------------------------------------------------------------------------------------
void_t
Mutex::_lock_impl()
{
    int_t iRv = ::pthread_mutex_lock(&_handle);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
}
//-------------------------------------------------------------------------------------------------
bool_t
Mutex::_tryLock_impl()
{
    int_t iRv = ::pthread_mutex_trylock(&_handle);
    xCHECK_RET(iRv != 0, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
Mutex::_unlock_impl()
{
    int_t iRv = ::pthread_mutex_unlock(&_handle);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
}
//-------------------------------------------------------------------------------------------------

} // namespace
