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
    _m_hHandle()
{

}
//------------------------------------------------------------------------------
/* virtual */
CxMutex::~CxMutex() {
#if   xOS_ENV_WIN
    bool_t bRv = false;

    try {
        (void_t)::DeleteCriticalSection(&_m_hHandle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST_EQ(true, bRv);
#elif xOS_ENV_UNIX
    int_t iRv = ::pthread_mutex_destroy(&_m_hHandle);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
void_t
CxMutex::create() {
#if   xOS_ENV_WIN
    bool_t bRv = false;

    try {
        (void_t)::InitializeCriticalSection(&_m_hHandle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST_EQ(true, bRv);
#elif xOS_ENV_UNIX
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
        iRv = ::pthread_mutex_init(&_m_hHandle, &maAttr);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    }

    iRv = ::pthread_mutexattr_destroy(&maAttr);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
const CxMutex::handle_t &
CxMutex::handle() const {
    return _m_hHandle;
}
//------------------------------------------------------------------------------
void_t
CxMutex::lock() {
#if   xOS_ENV_WIN
    bool_t bRv = false;

    try {
        (void_t)::EnterCriticalSection(&_m_hHandle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST_EQ(true, bRv);
#elif xOS_ENV_UNIX
    int_t iRv = ::pthread_mutex_lock(&_m_hHandle);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
bool_t
CxMutex::tryLock() {
#if   xOS_ENV_WIN
    BOOL blRes = ::TryEnterCriticalSection(&_m_hHandle);
    xCHECK_RET(FALSE == blRes, false);
#elif xOS_ENV_UNIX
    int_t iRv = ::pthread_mutex_trylock(&_m_hHandle);
    xCHECK_RET(0 != iRv, false);
#endif

    return true;
}
//------------------------------------------------------------------------------
void_t
CxMutex::unlock() {
#if   xOS_ENV_WIN
    bool_t bRv = false;

    try {
        (void_t)::LeaveCriticalSection(&_m_hHandle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST_EQ(true, bRv);
#elif xOS_ENV_UNIX
    int_t iRv = ::pthread_mutex_unlock(&_m_hHandle);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
