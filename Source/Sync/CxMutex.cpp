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
    HANDLE hRes = ::CreateMutex(NULL, FALSE, CxMacros::pcszAsCString(csName));
    /*DEBUG*/xASSERT_RET(NULL != hRes, false);

    _m_hHandle.bSet(hRes);
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
    DWORD ulRes = ::WaitForSingleObject(_m_hHandle.hGet(), culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0  == ulRes, false);
    /*DEBUG*/xASSERT_RET(WAIT_ABANDONED != ulRes, false);
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
