/**
 * \file  CxMutex.inl
 * \brief mutex
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTrace.h>


xNAMESPACE2_BEGIN(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxMutex::~CxMutex()
{
#if   xENV_WIN
    bool_t bRv = false;

    try {
        (void_t)::DeleteCriticalSection(&_handle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST_EQ(bRv, true);
#elif xENV_UNIX
    int_t iRv = ::pthread_mutex_destroy(&_handle);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMutex::create()
{
#if   xENV_WIN
    bool_t bRv = false;

    try {
        (void_t)::InitializeCriticalSection(&_handle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST_EQ(bRv, true);
#elif xENV_UNIX
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
#endif
}
//-------------------------------------------------------------------------------------------------
inline const CxMutex::handle_t &
CxMutex::handle() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMutex::lock()
{
#if   xENV_WIN
    bool_t bRv = false;

    try {
        (void_t)::EnterCriticalSection(&_handle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST_EQ(bRv, true);
#elif xENV_UNIX
    int_t iRv = ::pthread_mutex_lock(&_handle);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxMutex::tryLock()
{
#if   xENV_WIN
    BOOL blRv = ::TryEnterCriticalSection(&_handle);
    xCHECK_RET(blRv == FALSE, false);
#elif xENV_UNIX
    int_t iRv = ::pthread_mutex_trylock(&_handle);
    xCHECK_RET(iRv != 0, false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMutex::unlock()
{
#if   xENV_WIN
    bool_t bRv = false;

    try {
        (void_t)::LeaveCriticalSection(&_handle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST_EQ(bRv, true);
#elif xENV_UNIX
    int_t iRv = ::pthread_mutex_unlock(&_handle);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, sync)
