/**
 * \file  CxMutex.inl
 * \brief mutex
 */


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxMutex::_destruc_impl()
{
    int_t iRv = ::pthread_mutex_destroy(&_handle);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMutex::_create_impl()
{
    int_t iRv = - 1;

    pthread_mutexattr_t attr;    // n/a {{0}}

    iRv = ::pthread_mutexattr_init(&attr);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    iRv = ::pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_PRIVATE);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    // TODO: CxMutex::create() - Unix - PTHREAD_MUTEX_RECURSIVE
#if 1
    iRv = ::pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
#endif

    {
        iRv = ::pthread_mutex_init(&_handle, &attr);
        xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
    }

    iRv = ::pthread_mutexattr_destroy(&attr);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMutex::_lock_impl()
{
    int_t iRv = ::pthread_mutex_lock(&_handle);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxMutex::_tryLock_impl()
{
    int_t iRv = ::pthread_mutex_trylock(&_handle);
    xCHECK_RET(iRv != 0, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMutex::_unlock_impl()
{
    int_t iRv = ::pthread_mutex_unlock(&_handle);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
