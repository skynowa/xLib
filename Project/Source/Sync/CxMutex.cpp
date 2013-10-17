/**
 * \file  CxMutex.cpp
 * \brief critical section (using between threads)
 */


#include <xLib/Sync/CxMutex.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxMutex::CxMutex() :
    _handle()
{
}
//------------------------------------------------------------------------------
/* virtual */
CxMutex::~CxMutex()
{
#if xOS_ENV_WIN
    bool_t bRv = false;

    try {
        (void_t)::DeleteCriticalSection(&_handle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST_EQ(true, bRv);
#else
    int_t iRv = ::pthread_mutex_destroy(&_handle);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
void_t
CxMutex::create()
{
#if xOS_ENV_WIN
    bool_t bRv = false;

    try {
        (void_t)::InitializeCriticalSection(&_handle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST_EQ(true, bRv);
#else
    int_t iRv = - 1;

    pthread_mutexattr_t maAttr;    // n/a {{0}}

    iRv = ::pthread_mutexattr_init(&maAttr);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    iRv = ::pthread_mutexattr_setpshared(&maAttr, PTHREAD_PROCESS_PRIVATE);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    // TODO: create - PTHREAD_MUTEX_RECURSIVE
#if 1
    iRv = ::pthread_mutexattr_settype(&maAttr, PTHREAD_MUTEX_RECURSIVE);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif

    {
        iRv = ::pthread_mutex_init(&_handle, &maAttr);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    }

    iRv = ::pthread_mutexattr_destroy(&maAttr);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
const CxMutex::handle_t &
CxMutex::handle() const
{
    return _handle;
}
//------------------------------------------------------------------------------
void_t
CxMutex::lock()
{
#if xOS_ENV_WIN
    bool_t bRv = false;

    try {
        (void_t)::EnterCriticalSection(&_handle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST_EQ(true, bRv);
#else
    int_t iRv = ::pthread_mutex_lock(&_handle);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
bool_t
CxMutex::tryLock()
{
#if xOS_ENV_WIN
    BOOL blRes = ::TryEnterCriticalSection(&_handle);
    xCHECK_RET(FALSE == blRes, false);
#else
    int_t iRv = ::pthread_mutex_trylock(&_handle);
    xCHECK_RET(0 != iRv, false);
#endif

    return true;
}
//------------------------------------------------------------------------------
void_t
CxMutex::unlock()
{
#if xOS_ENV_WIN
    bool_t bRv = false;

    try {
        (void_t)::LeaveCriticalSection(&_handle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST_EQ(true, bRv);
#else
    int_t iRv = ::pthread_mutex_unlock(&_handle);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
