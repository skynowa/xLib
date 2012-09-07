/**
 * \file  CxMutex.cpp
 * \brief critical section (using between threads)
 */


#include <xLib/Sync/CxMutex.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxMutex::CxMutex() :
    _m_hHandle()
{
    ///*DEBUG*/xASSERT_DO(false == _bIsValid(), return);
}
//---------------------------------------------------------------------------
/*virtual*/
CxMutex::~CxMutex() {
    ///*DEBUG*/xASSERT_DO(true == _bIsValid(), return);
xASSERT(false);
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
bool
CxMutex::bCreate() {
    ///*DEBUG*/xASSERT_RET(false == _bIsValid(), false);

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
const CxMutex::handle_t &
CxMutex::hGet() const {
    ///*DEBUG*/xASSERT(true == _bIsValid());

    return _m_hHandle;
}
//---------------------------------------------------------------------------
bool
CxMutex::bLock() {
    ///*DEBUG*/xASSERT_RET(true == _bIsValid(), false);

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
CxMutex::bTryLock() {
    ///*DEBUG*/xASSERT_RET(true == _bIsValid(), false);

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
CxMutex::bUnlock() {
    ///*DEBUG*/xASSERT_RET(true == _bIsValid(), false);

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


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxMutex::_bIsValid() const {
#if xTODO
    #if xOS_ENV_WIN
        return (NULL != _m_hHandle.OwningThread);
    #elif xOS_ENV_UNIX
        return (0 < _m_hHandle.__owner);
    #endif
#endif

    return false;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
