/**
 * \file  CxCriticalSection.cpp
 * \brief critical section (using between threads)
 */


#include <xLib/Sync/CxCriticalSection.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCriticalSection::CxCriticalSection() :
    _m_hHandle()
{
#if defined(xOS_ENV_WIN)
    BOOL bRes = FALSE;

    try {
        (void)::InitializeCriticalSection(&_m_hHandle);

        bRes = TRUE;
    } catch (...) {
        bRes = FALSE;
    }

    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
#elif defined(xOS_ENV_UNIX)
    int iRes = - 1;

    pthread_mutexattr_t maAttr;	// n/a {{0}}

    iRes = pthread_mutexattr_init(&maAttr);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);

    iRes = pthread_mutexattr_settype(&maAttr, PTHREAD_MUTEX_RECURSIVE);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);

    {
        iRes = pthread_mutex_init(&_m_hHandle, &maAttr);
        /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);
    }

    iRes = pthread_mutexattr_destroy(&maAttr);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);
#endif
}
//---------------------------------------------------------------------------
/*virtual*/
CxCriticalSection::~CxCriticalSection() {
#if defined(xOS_ENV_WIN)
    BOOL bRes = FALSE;

    try {
        (void)::DeleteCriticalSection(&_m_hHandle);

        bRes = TRUE;
    } catch (...) {
        bRes = FALSE;
    }

    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
#elif defined(xOS_ENV_UNIX)
    int iRes = pthread_mutex_destroy(&_m_hHandle);
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
BOOL
CxCriticalSection::bLock() {
#if defined(xOS_ENV_WIN)
    BOOL bRes = FALSE;

    try {
        (void)::EnterCriticalSection(&_m_hHandle);

        bRes = TRUE;
    } catch (...) {
        bRes = FALSE;
    }

    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    int iRes = pthread_mutex_lock(&_m_hHandle);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxCriticalSection::bTryLock() {
#if defined(xOS_ENV_WIN)
    BOOL bRes = ::TryEnterCriticalSection(&_m_hHandle);
    xCHECK_RET(FALSE == bRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    int iRes = pthread_mutex_trylock(&_m_hHandle);
    xCHECK_RET(0 != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxCriticalSection::bUnlock() {
#if defined(xOS_ENV_WIN)
    BOOL bRes = FALSE;

    try {
        (void)::LeaveCriticalSection(&_m_hHandle);

        bRes = TRUE;
    } catch (...) {
        bRes = FALSE;
    }

    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    int iRes = pthread_mutex_unlock(&_m_hHandle);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
