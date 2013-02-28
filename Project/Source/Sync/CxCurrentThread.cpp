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
/* static */
bool_t
CxCurrentThread::isCurrent(
    const CxThread::id_t &a_culId
)
{
    bool_t bRv = false;

#if   xOS_ENV_WIN
    bRv = (id() == a_culId);
#elif xOS_ENV_UNIX
    //TODO: If either thread1 or thread2 are not valid thread IDs, the behavior is undefined
    bRv = ::pthread_equal(id(), a_culId);
#endif

    return bRv;
}
//------------------------------------------------------------------------------
/* static */
CxThread::id_t
CxCurrentThread::id() {
    // n/a

    CxThread::id_t ulRv = 0UL;

#if   xOS_ENV_WIN
    ulRv = ::GetCurrentThreadId();
    xTEST_LESS(0UL, ulRv);
#elif xOS_ENV_UNIX
    ulRv = ::pthread_self();
    xTEST_EQ(true, 0UL < ulRv);
#endif

    return ulRv;
}
//------------------------------------------------------------------------------
/* static */
CxThread::handle_t
CxCurrentThread::handle() {
    // n/a

    CxThread::handle_t hRv;

#if   xOS_ENV_WIN
    hRv = ::GetCurrentThread();
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
#elif xOS_ENV_UNIX
    hRv = ::pthread_self();
    xTEST_EQ(true, 0 < hRv);
#endif

    return hRv;
}
//------------------------------------------------------------------------------
/* static */
void
CxCurrentThread::yield() {
    // n/a

#if   xOS_ENV_WIN
    (void)::SwitchToThread();
#elif xOS_ENV_UNIX
    int_t iRv = ::sched_yield();
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
/* static */
void
CxCurrentThread::sleep(
    culong_t &a_culMsec
) {
    // n/a

#if   xOS_ENV_WIN
    (void)::Sleep(a_culMsec);
#elif xOS_ENV_UNIX
    timespec tsSleep  = {0};
    timespec tsRemain = {0};

    tsSleep.tv_sec  = a_culMsec / 1000;
    tsSleep.tv_nsec = (a_culMsec % 1000) * (1000 * 1000);

    xFOREVER {
        int_t iRv = ::nanosleep(&tsSleep, &tsRemain);
        // n/a
        xCHECK_DO(!(- 1 == iRv && EINTR == CxLastError::get()), break);

        tsSleep = tsRemain;
    }
#endif
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxCurrentThread::CxCurrentThread() {

}
//------------------------------------------------------------------------------
/* virtual */
CxCurrentThread::~CxCurrentThread() {

}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
