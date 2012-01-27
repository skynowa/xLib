/**
 * \file  CxMutex.cpp
 * \brief mutex
 */


#include <xLib/Sync/CxMutex.h>

#include <xLib/Sync/CxCriticalSection.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxMutex::CxMutex() :
    _m_hHandle()
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxMutex::~CxMutex() {
#if defined(xOS_ENV_WIN)

#elif defined(xOS_ENV_UNIX)
    int iRes = ::pthread_mutex_destroy(&_m_hHandle);
    /*DEBUG*/xASSERT_MSG_DO(0 == iRes, CxLastError::sFormat(iRes), return);
#endif
}
//---------------------------------------------------------------------------
const CxMutex::TxHandle &
CxMutex::hGet() const {
    /*DEBUG*/

    return _m_hHandle;
}
//---------------------------------------------------------------------------
bool
CxMutex::bCreate(
    const std::tstring_t &csName
)
{
    /*DEBUG*/xASSERT_RET(false == _m_hHandle.bIsValid(), false);
    /*DEBUG*///csName       - n/a

#if defined(xOS_ENV_WIN)
    HANDLE hRes = NULL;

    hRes = ::CreateMutex(NULL, FALSE, CxMacros::pcszAsCString(csName));
    /*DEBUG*/xASSERT_RET(NULL != hRes, false);

    _m_hHandle.bSet(hRes);
#elif defined(xOS_ENV_UNIX)
    int iRes = - 1;

    pthread_mutexattr_t maAttr;    // n/a {{0}}

    iRes = ::pthread_mutexattr_init(&maAttr);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), false);

    //TODO: PTHREAD_PROCESS_PRIVATE or PTHREAD_PROCESS_SHARED
    iRes = ::pthread_mutexattr_setpshared(&maAttr, PTHREAD_PROCESS_PRIVATE);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), false);
    
    iRes = ::pthread_mutexattr_settype(&maAttr, PTHREAD_MUTEX_RECURSIVE);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), false);

    {
        iRes = ::pthread_mutex_init(&_m_hHandle, &maAttr);
        /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), false);
    }

    iRes = ::pthread_mutexattr_destroy(&maAttr);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxMutex::bLock(
    const ulong_t culTimeout
) const
{
    /*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(), false);
    /*DEBUG*///culTimeout - n/a

#if defined(xOS_ENV_WIN)
    DWORD ulRes = WAIT_FAILED;

    ulRes = ::WaitForSingleObject(_m_hHandle.hGet(), culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0  == ulRes, false);
    /*DEBUG*/xASSERT_RET(WAIT_ABANDONED != ulRes, false);
#elif defined(xOS_ENV_UNIX)
    int iRes = ::pthread_mutex_lock(&_m_hHandle);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxMutex::bUnlock() const {
    /*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(), false);

#if defined(xOS_ENV_WIN)
    BOOL bRes = ::ReleaseMutex(_m_hHandle.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, false);
#elif defined(xOS_ENV_UNIX)
    int iRes = ::pthread_mutex_unlock(&_m_hHandle);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), false);
#endif

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
