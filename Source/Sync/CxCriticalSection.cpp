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
#if defined(xOS_WIN)
    _m_CS    ()
#elif defined(xOS_LINUX)
    _m_mMutex()
#endif
{
#if defined(xOS_WIN)
    BOOL bRes = FALSE;

    try {
        (VOID)::InitializeCriticalSection(&_m_CS);

        bRes = TRUE;
    } catch (...) {
        bRes = FALSE;
    }

    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
#elif defined(xOS_LINUX)
    INT iRes = - 1;

    pthread_mutexattr_t maAttr;

    iRes = pthread_mutexattr_init(&maAttr);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);

    iRes = pthread_mutexattr_settype(&maAttr, PTHREAD_MUTEX_RECURSIVE);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);

    {
        iRes = pthread_mutex_init(&_m_mMutex, &maAttr);
        /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);
    }

    iRes = pthread_mutexattr_destroy(&maAttr);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);
#endif
}
//---------------------------------------------------------------------------
CxCriticalSection::CxCriticalSection(
    const ULONG culSpinCount
)
{
    /*DEBUG*///ulSpinCount - n/a

#if defined(xOS_WIN)
    BOOL bRes = ::InitializeCriticalSectionAndSpinCount(&_m_CS, culSpinCount /*0x00000400*/);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
#elif defined(xOS_LINUX)
    INT iRes = - 1;

    pthread_mutexattr_t maAttr;

    iRes = pthread_mutexattr_init(&maAttr);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);

    iRes = pthread_mutexattr_settype(&maAttr, PTHREAD_MUTEX_RECURSIVE);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);

    {
        iRes = pthread_mutex_init(&_m_mMutex, &maAttr);
        /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);
    }

    iRes = pthread_mutexattr_destroy(&maAttr);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);

    //TODO: culSpinCount
#endif
}
//---------------------------------------------------------------------------
CxCriticalSection::~CxCriticalSection() {
#if defined(xOS_WIN)
    BOOL bRes = FALSE;

    try {
        (VOID)::DeleteCriticalSection(&_m_CS);

        bRes = TRUE;
    } catch (...) {
        bRes = FALSE;
    }

    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
#elif defined(xOS_LINUX)
    INT iRes = pthread_mutex_destroy(&_m_mMutex);
	/*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);
#endif
}
//---------------------------------------------------------------------------
const CxCriticalSection::TxHandle &
CxCriticalSection::hGet() const {
    /*DEBUG*/

#if defined(xOS_WIN)
    return _m_CS;
#elif defined(xOS_LINUX)
    return _m_mMutex;
#endif
}
//---------------------------------------------------------------------------
BOOL
CxCriticalSection::bEnter() {
#if defined(xOS_WIN)
    BOOL bRes = FALSE;

    try {
        (VOID)::EnterCriticalSection(&_m_CS);

        bRes = TRUE;
    } catch (...) {
        bRes = FALSE;
    }

    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    INT iRes = pthread_mutex_lock(&_m_mMutex);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxCriticalSection::bTryEnter() {
#if defined(xOS_WIN)
    BOOL bRes = ::TryEnterCriticalSection(&_m_CS);
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    INT iRes = pthread_mutex_trylock(&_m_mMutex);
    xCHECK_RET(0 != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxCriticalSection::bLeave() {
#if defined(xOS_WIN)
    BOOL bRes = FALSE;

    try {
        (VOID)::LeaveCriticalSection(&_m_CS);

        bRes = TRUE;
    } catch (...) {
        bRes = FALSE;
    }

    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    INT iRes = pthread_mutex_unlock(&_m_mMutex);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
ULONG
CxCriticalSection::ulSetSpinCount(
    const ULONG culSpinCount
)
{
    /*DEBUG*/// ulSpinCount - n/a

#if defined(xOS_WIN)
    return ::SetCriticalSectionSpinCount(&_m_CS, culSpinCount);
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    //TODO: ulSetSpinCount

    return 0UL;
#endif
}
//---------------------------------------------------------------------------
