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
#if xOS_ENV_WIN

#elif xOS_ENV_UNIX

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
    /////*DEBUG*/xASSERT_RET(false == _m_hHandle.bIsValid(), false);
    /*DEBUG*///csName - n/a

#if xOS_ENV_WIN
    const tchar_t *pcszName = (true == csName.empty()) ? (NULL) : (csName.c_str());

    HANDLE hRv = ::CreateMutex(NULL, FALSE, pcszName);
    /*DEBUG*/xASSERT_RET(NULL != hRv, false);

    _m_hHandle.bSet(hRv);
#elif xOS_ENV_UNIX

#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxMutex::bLock(
    const ulong_t culTimeout
) const
{
    /////*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(), false);
    /*DEBUG*///culTimeout - n/a

#if xOS_ENV_WIN
    DWORD ulRv = ::WaitForSingleObject(_m_hHandle.hGet(), culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0  == ulRv, false);
    /*DEBUG*/xASSERT_RET(WAIT_ABANDONED != ulRv, false);
#elif xOS_ENV_UNIX

#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxMutex::bUnlock() const {
    /////*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(), false);

#if xOS_ENV_WIN
    BOOL blRes = ::ReleaseMutex(_m_hHandle.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX

#endif

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
