/**
 * \file   CxCurrentThread.cpp
 * \brief
 */


#include <xLib/Sync/CxCurrentThread.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
bool
CxCurrentThread::bIsCurrent(
    const CxThread::id_t &a_culId
)
{
    /*DEBUG*/

    bool bRv = false;

#if   xOS_ENV_WIN
    bRv = (ulGetId() == a_culId);
#elif xOS_ENV_UNIX
    //TODO: If either thread1 or thread2 are not valid thread IDs, the behavior is undefined
    bRv = ::pthread_equal(ulGetId(), a_culId);
#endif

    return bRv;
}
//---------------------------------------------------------------------------
/* static */
CxThread::id_t
CxCurrentThread::ulGetId() {
    /*DEBUG*/// n/a

    CxThread::id_t ulRv = 0UL;

#if   xOS_ENV_WIN
    ulRv = ::GetCurrentThreadId();
    /*DEBUG*/xTEST_LESS(0UL, ulRv);
#elif xOS_ENV_UNIX
    ulRv = ::pthread_self();
    /*DEBUG*/xASSERT_RET(0UL < ulRv, 0UL);
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/* static */
CxThread::handle_t
CxCurrentThread::hGetHandle() {
    /*DEBUG*/// n/a

    CxThread::handle_t hRv;

#if   xOS_ENV_WIN
    hRv = ::GetCurrentThread();
    /*DEBUG*/xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
#elif xOS_ENV_UNIX
    hRv = ::pthread_self();
    /*DEBUG*/xASSERT_RET(0 < hRv, 0);
#endif

    return hRv;
}
//---------------------------------------------------------------------------
/* static */
bool
CxCurrentThread::bYield() {
    /*DEBUG*/// n/a

#if   xOS_ENV_WIN
    (void)::SwitchToThread();
#elif xOS_ENV_UNIX
    int iRv = ::sched_yield();
    /*DEBUG*/xASSERT_MSG_RET(- 1 != iRv, CxLastError::sFormat(iRv), false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxCurrentThread::bSleep(
    const ulong_t a_culMsec
) {
    /*DEBUG*/// n/a

#if   xOS_ENV_WIN
    (void)::Sleep(a_culMsec);
#elif xOS_ENV_UNIX
    timespec tsSleep  = {0};
    timespec tsRemain = {0};

    tsSleep.tv_sec  = a_culMsec / 1000;
    tsSleep.tv_nsec = (a_culMsec % 1000) * (1000 * 1000);

    for ( ; ; ) {
        int iRv = ::nanosleep(&tsSleep, &tsRemain);
        /*DEBUG*/// n/a
        xCHECK_DO(!(- 1 == iRv && EINTR == CxLastError::ulGet()), break);

        tsSleep = tsRemain;
    }
#endif

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCurrentThread::CxCurrentThread() {

}
//---------------------------------------------------------------------------
/* virtual */
CxCurrentThread::~CxCurrentThread() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
