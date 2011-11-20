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
/*static*/
bool
CxCurrentThread::bIsCurrent(
    const CxThread::TxId culId
)
{
    /*DEBUG*/

    bool bRes = false;

#if xOS_ENV_WIN
    bRes = static_cast<bool>( ulGetId() == culId );
#elif xOS_ENV_UNIX
    //TODO: If either thread1 or thread2 are not valid thread IDs, the behavior is undefined
    bRes = static_cast<bool>( ::pthread_equal(ulGetId(), culId) );
#endif

    return bRes;
}
//---------------------------------------------------------------------------
/*static*/
CxThread::TxId
CxCurrentThread::ulGetId() {
    /*DEBUG*/// n/a

    CxThread::TxId ulRes = 0UL;

#if xOS_ENV_WIN
    ulRes = ::GetCurrentThreadId();
    /*DEBUG*/xASSERT_RET(0UL < ulRes, 0UL);
#elif xOS_ENV_UNIX
    ulRes = ::pthread_self();
    /*DEBUG*/xASSERT_RET(0UL < ulRes, 0UL);
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
/*static*/
CxThread::TxHandle
CxCurrentThread::hGetHandle() {
    /*DEBUG*/// n/a

    CxThread::TxHandle hRes;

#if xOS_ENV_WIN
    hRes = ::GetCurrentThread();
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);
#elif xOS_ENV_UNIX
    hRes = ::pthread_self();
    /*DEBUG*/xASSERT_RET(0 < hRes, 0);
#endif

    return hRes;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxCurrentThread::bYield() {
    /*DEBUG*/// n/a

#if xOS_ENV_WIN
    (void)::SwitchToThread();
#elif xOS_ENV_UNIX
    int iRes = ::sched_yield();
    /*DEBUG*/xASSERT_MSG_RET(- 1 != iRes, CxLastError::sFormat(iRes), false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxCurrentThread::bSleep(
    const ULONG culMsec
) {
    /*DEBUG*/// n/a

#if xOS_ENV_WIN
    (void)::Sleep(culMsec);
#elif xOS_ENV_UNIX
    timespec tsSleep  = {0};
    timespec tsRemain = {0};

    tsSleep.tv_sec  = culMsec / 1000;
    tsSleep.tv_nsec = (culMsec % 1000) * (1000 * 1000);

    for ( ; ; ) {
        int iRes = ::nanosleep(&tsSleep, &tsRemain);
        /*DEBUG*/// n/a
        xCHECK_DO(!(- 1 == iRes && EINTR == CxLastError::ulGet()), break);

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
/*virtual*/
CxCurrentThread::~CxCurrentThread() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
