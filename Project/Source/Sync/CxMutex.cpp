/**
 * \file  CxMutex.cpp
 * \brief critical section (using between threads)
 */


#include <xLib/Sync/CxMutex.h>

#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTracer.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE_HO
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
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
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

    pthread_mutexattr_t attr;    // n/a {{0}}

    iRv = ::pthread_mutexattr_init(&attr);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    iRv = ::pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_PRIVATE);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    // TODO: create - PTHREAD_MUTEX_RECURSIVE
#if 1
    iRv = ::pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif

    {
        iRv = ::pthread_mutex_init(&_handle, &attr);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    }

    iRv = ::pthread_mutexattr_destroy(&attr);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO const CxMutex::handle_t &
CxMutex::handle() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
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
//-------------------------------------------------------------------------------------------------
xINLINE_HO bool_t
CxMutex::tryLock()
{
#if xOS_ENV_WIN
    BOOL blRv = ::TryEnterCriticalSection(&_handle);
    xCHECK_RET(FALSE == blRv, false);
#else
    int_t iRv = ::pthread_mutex_trylock(&_handle);
    xCHECK_RET(0 != iRv, false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
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
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
