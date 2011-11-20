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
#if xOS_ENV_WIN
    bool bRes = false;

    try {
        (void)::InitializeCriticalSection(&_m_hHandle);

        bRes = true;
    } catch (...) {
        bRes = false;
    }

    /*DEBUG*/xASSERT_DO(false != bRes, return);
#elif xOS_ENV_UNIX
    int iRes = - 1;

    pthread_mutexattr_t maAttr;    // n/a {{0}}

    iRes = ::pthread_mutexattr_init(&maAttr);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);

    iRes = ::pthread_mutexattr_settype(&maAttr, PTHREAD_MUTEX_RECURSIVE);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);

    {
        iRes = ::pthread_mutex_init(&_m_hHandle, &maAttr);
        /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);
    }

    iRes = ::pthread_mutexattr_destroy(&maAttr);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);
#endif
}
//---------------------------------------------------------------------------
/*virtual*/
CxCriticalSection::~CxCriticalSection() {
#if xOS_ENV_WIN
    bool bRes = false;

    try {
        (void)::DeleteCriticalSection(&_m_hHandle);

        bRes = true;
    } catch (...) {
        bRes = false;
    }

    /*DEBUG*/xASSERT_DO(false != bRes, return);
#elif xOS_ENV_UNIX
    int iRes = ::pthread_mutex_destroy(&_m_hHandle);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);
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
    bool bRes = false;

    try {
        (void)::EnterCriticalSection(&_m_hHandle);

        bRes = true;
    } catch (...) {
        bRes = false;
    }

    /*DEBUG*/xASSERT_RET(false != bRes, false);
#elif xOS_ENV_UNIX
    int iRes = ::pthread_mutex_lock(&_m_hHandle);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxCriticalSection::bTryLock() {
#if xOS_ENV_WIN
    BOOL bRes = ::TryEnterCriticalSection(&_m_hHandle);
    xCHECK_RET(FALSE == bRes, false);
#elif xOS_ENV_UNIX
    int iRes = ::pthread_mutex_trylock(&_m_hHandle);
    xCHECK_RET(0 != iRes, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxCriticalSection::bUnlock() {
#if xOS_ENV_WIN
    bool bRes = false;

    try {
        (void)::LeaveCriticalSection(&_m_hHandle);

        bRes = true;
    } catch (...) {
        bRes = false;
    }

    /*DEBUG*/xASSERT_RET(false != bRes, false);
#elif xOS_ENV_UNIX
    int iRes = ::pthread_mutex_unlock(&_m_hHandle);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), false);
#endif

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
