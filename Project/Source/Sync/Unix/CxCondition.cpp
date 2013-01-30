/**
 * \file   CxCondition.cpp
 * \brief
 */


#include <xLib/Sync/Unix/CxCondition.h>


#if xOS_ENV_UNIX

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCondition::CxCondition() :
    _m_mutex (),
    _m_handle()
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxCondition::~CxCondition() {
    int iRv = - 1;

    iRv = ::pthread_cond_destroy(&_m_handle);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    iRv = ::pthread_mutex_destroy(&_m_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
}
//---------------------------------------------------------------------------
const pthread_mutex_t &
CxCondition::hMutex() const {
    return _m_mutex;
}
//---------------------------------------------------------------------------
const pthread_cond_t &
CxCondition::hHandle() const {
    return _m_handle;
}
//---------------------------------------------------------------------------
void
CxCondition::create() {
    int iRv = - 1;

    iRv = ::pthread_mutex_init(&_m_mutex, NULL);    // mutex not recursive
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    iRv = ::pthread_cond_init(&_m_handle, NULL);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
}
//---------------------------------------------------------------------------
void
CxCondition::vWait(
    const ulong_t &a_culTimeoutMs
)
{
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

}
//---------------------------------------------------------------------------
void
CxCondition::vSignal() {
    int iRv = - 1;

    iRv = ::pthread_mutex_lock(&_m_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    {
        iRv = ::pthread_cond_signal(&_m_handle);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    }

    iRv = ::pthread_mutex_unlock(&_m_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
}
//---------------------------------------------------------------------------
void
CxCondition::vBroadcast() {
    int iRv = - 1;

    iRv = ::pthread_mutex_lock(&_m_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    {
        iRv = ::pthread_cond_broadcast(&_m_handle);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    }

    iRv = ::pthread_mutex_unlock(&_m_mutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
}
//---------------------------------------------------------------------------

#endif // xOS_ENV_UNIX
