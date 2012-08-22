/**
 * \file  CxCriticalSection.cpp
 * \brief critical section (using between threads)
 */


#include <xLib/Sync/CxCriticalSection.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCriticalSection::CxCriticalSection() :
    _m_hHandle()
{

}
//---------------------------------------------------------------------------
bool
CxCriticalSection::bCreate() {
    /*DEBUG*/

#if xOS_ENV_WIN
    bool bRv = false;

    try {
        (void)::InitializeCriticalSection(&_m_hHandle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    /*DEBUG*/xASSERT_RET(true == bRv, false);
#elif xOS_ENV_UNIX
    int iRv = - 1;

    pthread_mutexattr_t maAttr;    // n/a {{0}}

    iRv = ::pthread_mutexattr_init(&maAttr);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), false);

    iRv = ::pthread_mutexattr_setpshared(&maAttr, PTHREAD_PROCESS_PRIVATE);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), false);

    iRv = ::pthread_mutexattr_settype(&maAttr, PTHREAD_MUTEX_RECURSIVE);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), false);

    {
        iRv = ::pthread_mutex_init(&_m_hHandle, &maAttr);
        /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), false);
    }

    iRv = ::pthread_mutexattr_destroy(&maAttr);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/*virtual*/
CxCriticalSection::~CxCriticalSection() {
#if xOS_ENV_WIN
    bool bRv = false;

    try {
        (void)::DeleteCriticalSection(&_m_hHandle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    /*DEBUG*/xASSERT_DO(true == bRv, return);
#elif xOS_ENV_UNIX
    int iRv = ::pthread_mutex_destroy(&_m_hHandle);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRv, CxLastError::sFormat(iRv), return);
#endif
}
//---------------------------------------------------------------------------
const CxCriticalSection::TxHandle &
CxCriticalSection::hGet() const {
    /*DEBUG*/

    return _m_hHandle;
}
//---------------------------------------------------------------------------
bool
CxCriticalSection::bLock() {
#if xOS_ENV_WIN
    bool bRv = false;

    try {
        (void)::EnterCriticalSection(&_m_hHandle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    /*DEBUG*/xASSERT_RET(true == bRv, false);
#elif xOS_ENV_UNIX
    int iRv = ::pthread_mutex_lock(&_m_hHandle);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxCriticalSection::bTryLock() {
#if xOS_ENV_WIN
    BOOL blRes = ::TryEnterCriticalSection(&_m_hHandle);
    xCHECK_RET(FALSE == blRes, false);
#elif xOS_ENV_UNIX
    int iRv = ::pthread_mutex_trylock(&_m_hHandle);
    xCHECK_RET(0 != iRv, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxCriticalSection::bUnlock() {
#if xOS_ENV_WIN
    bool bRv = false;

    try {
        (void)::LeaveCriticalSection(&_m_hHandle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    /*DEBUG*/xASSERT_RET(true == bRv, false);
#elif xOS_ENV_UNIX
    int iRv = ::pthread_mutex_unlock(&_m_hHandle);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), false);
#endif

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
