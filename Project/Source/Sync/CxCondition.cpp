/**
 * \file   CxCondition.cpp
 * \brief
 */


#include <xLib/Sync/CxCondition.h>

#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTracer.h>


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxCondition::CxCondition()
#if !xOS_ENV_WIN
    :
    _mutex (),
    _handle()
#endif
{
}
//------------------------------------------------------------------------------
/*virtual*/
xINLINE_HO
CxCondition::~CxCondition()
{
#if xOS_ENV_WIN

#else
    int_t iRv = - 1;

    iRv = ::pthread_cond_destroy(&_handle);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    iRv = ::pthread_mutex_destroy(&_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
#if xOS_ENV_UNIX

xINLINE_HO const pthread_mutex_t &
CxCondition::mutex() const
{
    return _mutex;
}

#endif
//------------------------------------------------------------------------------
#if xOS_ENV_UNIX

xINLINE_HO const pthread_cond_t &
CxCondition::handle() const
{
    return _handle;
}

#endif
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxCondition::create()
{
#if xOS_ENV_WIN

#else
    int_t iRv = - 1;

    iRv = ::pthread_mutex_init(&_mutex, NULL);    // mutex not recursive
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    iRv = ::pthread_cond_init(&_handle, NULL);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxCondition::wait(
    culong_t &a_timeoutMs
)
{
#if xOS_ENV_WIN

#else
    int_t iRv = - 1;

    // wait until condition thread returns control
    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    {
        xFOREVER {
            if (xTIMEOUT_INFINITE == a_timeoutMs) {
                iRv = ::pthread_cond_wait(&_handle, &_mutex);
            } else {
                timespec tsTimeoutMs = {0};
                timeval  tvNow       = {0};

                iRv = ::gettimeofday(&tvNow, NULL);
                xTEST_DIFF(- 1, iRv);

                tsTimeoutMs.tv_sec  = tvNow.tv_sec + a_timeoutMs / 1000;
                tsTimeoutMs.tv_nsec = tvNow.tv_usec * 1000 + (a_timeoutMs % 1000) * 1000000;

                // handle overflow
                if (tsTimeoutMs.tv_nsec >= 1000000000) {
                    CxTracer() << xT("xLib: CxCondition::vWait - handle overflow");

                    ++ tsTimeoutMs.tv_sec;
                    tsTimeoutMs.tv_nsec -= 1000000000;
                }

                iRv = ::pthread_cond_timedwait(&_handle, &_mutex, &tsTimeoutMs);
            }

            xCHECK_DO(iRv, break);
        }
    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxCondition::signal()
{
#if xOS_ENV_WIN

#else
    int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    {
        iRv = ::pthread_cond_signal(&_handle);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxCondition::broadcast()
{
#if xOS_ENV_WIN

#else
     int_t iRv = - 1;

    iRv = ::pthread_mutex_lock(&_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    {
        iRv = ::pthread_cond_broadcast(&_handle);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    }

    iRv = ::pthread_mutex_unlock(&_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
