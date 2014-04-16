/**
 * \file   CxCondition.inl
 * \brief  condition variable
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTrace.h>


/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxCondition::CxCondition()
#if !xOS_ENV_WIN
    :
    _mutex (),
    _handle()
#endif
{
}
//-------------------------------------------------------------------------------------------------
/*virtual*/
inline
CxCondition::~CxCondition()
{
#if   xOS_ENV_WIN

#elif xOS_ENV_UNIX
    int_t iRv = - 1;

    iRv = ::pthread_cond_destroy(&_handle);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    iRv = ::pthread_mutex_destroy(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_UNIX

inline const pthread_mutex_t &
CxCondition::mutex() const
{
    return _mutex;
}

#endif
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_UNIX

inline const pthread_cond_t &
CxCondition::handle() const
{
    return _handle;
}

#endif
//-------------------------------------------------------------------------------------------------
inline void_t
CxCondition::create()
{
#if   xOS_ENV_WIN

#elif xOS_ENV_UNIX
    int_t iRv = - 1;

    iRv = ::pthread_mutex_init(&_mutex, xPTR_NULL); // mutex not recursive
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    iRv = ::pthread_cond_init(&_handle, xPTR_NULL);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCondition::wait(
    culong_t &a_timeoutMs
)
{
#if   xOS_ENV_WIN

#elif xOS_ENV_UNIX
    int_t iRv = - 1;

    // wait until condition thread returns control
    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    {
        for ( ; ; ) {
            if (a_timeoutMs == xTIMEOUT_INFINITE) {
                iRv = ::pthread_cond_wait(&_handle, &_mutex);
            } else {
                timespec timeoutMs = {0, 0};
                timeval  timeNow   = {0, 0};

                iRv = ::gettimeofday(&timeNow, xPTR_NULL);
                xTEST_DIFF(iRv, - 1);

                timeoutMs.tv_sec  = timeNow.tv_sec + a_timeoutMs / 1000;
                timeoutMs.tv_nsec = timeNow.tv_usec * 1000 + (a_timeoutMs % 1000) * 1000000;

                // handle overflow
                if (timeoutMs.tv_nsec >= 1000000000) {
                    CxTrace() << xT("xLib: CxCondition::vWait - handle overflow");

                    ++ timeoutMs.tv_sec;
                    timeoutMs.tv_nsec -= 1000000000;
                }

                iRv = ::pthread_cond_timedwait(&_handle, &_mutex, &timeoutMs);
            }

            xCHECK_DO(iRv, break);
        }
    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCondition::signal()
{
#if   xOS_ENV_WIN

#elif xOS_ENV_UNIX
    int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    {
        iRv = ::pthread_cond_signal(&_handle);
        xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCondition::broadcast()
{
#if   xOS_ENV_WIN

#elif xOS_ENV_UNIX
     int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    {
        iRv = ::pthread_cond_broadcast(&_handle);
        xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------
