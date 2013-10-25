/**
 * \file   CxCurrentThread.cpp
 * \brief
 */


#include <xLib/Sync/CxCurrentThread.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxCurrentThread::isCurrent(
    const CxThread::id_t &a_id
)
{
    bool_t bRv = false;

#if xOS_ENV_WIN
    bRv = (id() == a_id);
#else
    //TODO: If either thread1 or thread2 are not valid thread IDs, the behavior is undefined
    bRv = ::pthread_equal(id(), a_id);
#endif

    return bRv;
}
//------------------------------------------------------------------------------
xINLINE_HO CxThread::id_t
CxCurrentThread::id()
{
    // n/a

    CxThread::id_t ulRv = 0UL;

#if xOS_ENV_WIN
    ulRv = ::GetCurrentThreadId();
    xTEST_LESS(0UL, ulRv);
#else
    ulRv = ::pthread_self();
    xTEST_EQ(true, 0UL < ulRv);
#endif

    return ulRv;
}
//------------------------------------------------------------------------------
xINLINE_HO CxThread::handle_t
CxCurrentThread::handle()
{
    // n/a

    CxThread::handle_t hRv;

#if xOS_ENV_WIN
    hRv = ::GetCurrentThread();
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
#else
    hRv = ::pthread_self();
    xTEST_EQ(true, 0 < hRv);
#endif

    return hRv;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxCurrentThread::yield()
{
    // n/a

#if xOS_ENV_WIN
    (void_t)::SwitchToThread();
#else
    int_t iRv = ::sched_yield();
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxCurrentThread::sleep(
    culong_t &a_timeoutMs
)
{
    // n/a

#if xOS_ENV_WIN
    (void_t)::Sleep(a_timeoutMs);
#else
    timespec tsSleep  = {0};
    timespec tsRemain = {0};

    tsSleep.tv_sec  = a_timeoutMs / 1000;
    tsSleep.tv_nsec = (a_timeoutMs % 1000) * (1000 * 1000);

    xFOREVER {
        int_t iRv = ::nanosleep(&tsSleep, &tsRemain);
        // n/a
        xCHECK_DO(!(- 1 == iRv && EINTR == CxLastError::get()), break);

        tsSleep = tsRemain;
    }
#endif
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
