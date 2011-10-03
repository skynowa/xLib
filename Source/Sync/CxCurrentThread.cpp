/**
 * \file   CxCurrentThread.cpp
 * \brief
 */


#include <xLib/Sync/CxCurrentThread.h>


/****************************************************************************
*   public
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
/*static*/
CxThread::TxId
CxCurrentThread::ulGetId() {
    /*DEBUG*/// n/a

    CxThread::TxId ulRes = 0UL;

#if defined(xOS_ENV_WIN)
    ulRes = ::GetCurrentThreadId();
    /*DEBUG*/xASSERT_RET(0UL < ulRes, 0UL);
#elif defined(xOS_ENV_UNIX)
    ulRes = pthread_self();
    /*DEBUG*/xASSERT_RET(0UL < ulRes, 0UL);
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxCurrentThread::bIsCurrent(
    const CxThread::TxId culId
)
{
    /*DEBUG*/

    BOOL bRes = FALSE;

#if defined(xOS_ENV_WIN)
    bRes = static_cast<BOOL>( ulGetId() == culId );
#elif defined(xOS_ENV_UNIX)
    //TODO: If either thread1 or thread2 are not valid thread IDs, the behavior is undefined
    bRes = static_cast<BOOL>( pthread_equal(ulGetId(), culId) );
#endif

    return bRes;
}
//---------------------------------------------------------------------------
/*static*/
CxThread::TxHandle
CxCurrentThread::hGetHandle() {
    /*DEBUG*/// n/a

    CxThread::TxHandle hRes;

#if defined(xOS_ENV_WIN)
    hRes = ::GetCurrentThread();
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);
#elif defined(xOS_ENV_UNIX)
    hRes = pthread_self();
    /*DEBUG*/xASSERT_RET(0 < hRes, 0);
#endif

    return hRes;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxCurrentThread::bYield() {
    /*DEBUG*/// n/a

#if defined(xOS_ENV_WIN)
    (VOID)::SwitchToThread();
#elif defined(xOS_ENV_UNIX)
    INT iRes = sched_yield();
    /*DEBUG*/xASSERT_MSG_RET(- 1 != iRes, CxLastError::sFormat(iRes), FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxCurrentThread::bSleep(
    const ULONG culMsec
) {
    /*DEBUG*/// n/a

#if defined(xOS_ENV_WIN)
    (VOID)::Sleep(culMsec);
#elif defined(xOS_ENV_UNIX)
    timespec tsSleep  = {0};
    timespec tsRemain = {0};

    tsSleep.tv_sec  = culMsec / 1000;
    tsSleep.tv_nsec = (culMsec % 1000) * (1000 * 1000);

    for ( ; ; ) {
        INT iRes = nanosleep(&tsSleep, &tsRemain);
        /*DEBUG*/// n/a
        xCHECK_DO(!(- 1 == iRes && EINTR == CxLastError::ulGet()), break);

        tsSleep = tsRemain;
    }
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
