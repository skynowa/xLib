/**
 * \file   CxCondition.cpp
 * \brief
 */


#include <xLib/Sync/CxCondition.h>


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

#elif xOS_ENV_UNIX
CxCondition::CxCondition() :
    _m_mutex (),
    _m_handle()
{
}
#endif
//---------------------------------------------------------------------------
/*virtual*/
CxCondition::~CxCondition() {
#if   xOS_ENV_WIN

#elif xOS_ENV_UNIX
    int iRv = - 1;

    iRv = ::pthread_cond_destroy(&_m_handle);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    iRv = ::pthread_mutex_destroy(&_m_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//---------------------------------------------------------------------------
#if xOS_ENV_UNIX

const pthread_mutex_t &
CxCondition::mutex() const {
    return _m_mutex;
}

#endif
//---------------------------------------------------------------------------
#if xOS_ENV_UNIX

const pthread_cond_t &
CxCondition::handle() const {
    return _m_handle;
}

#endif
//---------------------------------------------------------------------------
void
CxCondition::create() {
#if   xOS_ENV_WIN

#elif xOS_ENV_UNIX
    int iRv = - 1;

    iRv = ::pthread_mutex_init(&_m_mutex, NULL);    // mutex not recursive
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    iRv = ::pthread_cond_init(&_m_handle, NULL);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//---------------------------------------------------------------------------
void
CxCondition::wait(
    const ulong_t &a_culTimeoutMs
)
{
#if   xOS_ENV_WIN

#elif xOS_ENV_UNIX
    int iRv = - 1;

    // wait until condition thread returns control
    iRv = ::pthread_mutex_lock(&_m_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    {
        xFOREVER {
            if (xTIMEOUT_INFINITE == a_culTimeoutMs) {
                iRv = ::pthread_cond_wait(&_m_handle, &_m_mutex);
            } else {
                timespec tsTimeoutMs = {0};
                timeval  tvNow       = {0};

                iRv = ::gettimeofday(&tvNow, NULL);
                xTEST_DIFF(- 1, iRv);

                tsTimeoutMs.tv_sec  = tvNow.tv_sec + a_culTimeoutMs / 1000;
                tsTimeoutMs.tv_nsec = tvNow.tv_usec * 1000 + (a_culTimeoutMs % 1000) * 1000000;

                // handle overflow
                if (tsTimeoutMs.tv_nsec >= 1000000000) {
                    CxTracer() << xT("xLib: CxCondition::vWait - handle overflow");

                    ++ tsTimeoutMs.tv_sec;
                    tsTimeoutMs.tv_nsec -= 1000000000;
                }

                iRv = ::pthread_cond_timedwait(&_m_handle, &_m_mutex, &tsTimeoutMs);
            }

            xCHECK_DO(iRv, break);
        }
    }

    iRv = ::pthread_mutex_unlock(&_m_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//---------------------------------------------------------------------------
void
CxCondition::signal() {
#if   xOS_ENV_WIN

#elif xOS_ENV_UNIX
    int iRv = - 1;

    iRv = ::pthread_mutex_lock(&_m_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    {
        iRv = ::pthread_cond_signal(&_m_handle);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    }

    iRv = ::pthread_mutex_unlock(&_m_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//---------------------------------------------------------------------------
void
CxCondition::broadcast() {
#if   xOS_ENV_WIN

#elif xOS_ENV_UNIX
     int iRv = - 1;

    iRv = ::pthread_mutex_lock(&_m_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    {
        iRv = ::pthread_cond_broadcast(&_m_handle);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    }

    iRv = ::pthread_mutex_unlock(&_m_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//---------------------------------------------------------------------------
