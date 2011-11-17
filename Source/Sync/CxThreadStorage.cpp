/**
 * \file  CxThreadStorage.cpp
 * \brief thread local storage
 */


#include <xLib/Sync/CxThreadStorage.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxThreadStorage::CxThreadStorage() :
#if xOS_ENV_WIN
    _m_indIndex(TLS_OUT_OF_INDEXES)
#elif xOS_ENV_UNIX
    _m_indIndex(static_cast<pthread_key_t>( -1 ))
#endif
{
    (void)_bAlloc();
}
//---------------------------------------------------------------------------
/*virtual*/
CxThreadStorage::~CxThreadStorage() {
    (void)_bFree();
}
//---------------------------------------------------------------------------
BOOL
CxThreadStorage::bIsSet() const {
    void *pvRes = NULL;

#if xOS_ENV_WIN
    pvRes = ::TlsGetValue(_m_indIndex);
    xCHECK_RET(NULL == pvRes, FALSE);
#elif xOS_ENV_UNIX
    pvRes = ::pthread_getspecific(_m_indIndex);
    xCHECK_RET(NULL == pvRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
void *
CxThreadStorage::pvGetValue() const {
    void *pvRes = NULL;

#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES != _m_indIndex, NULL);

    pvRes = ::TlsGetValue(_m_indIndex);
    /*DEBUG*/xASSERT_RET((NULL != pvRes) && (ERROR_SUCCESS == CxLastError::ulGet()), NULL);
#elif xOS_ENV_UNIX
    /*DEBUG*/xASSERT_RET(0 <= _m_indIndex, NULL);

    pvRes = ::pthread_getspecific(_m_indIndex);
    /*DEBUG*/xASSERT_RET(NULL != pvRes, NULL);
#endif

    return pvRes;
}
//---------------------------------------------------------------------------
BOOL
CxThreadStorage::bSetValue(
    void *pvValue
) const
{
    /*DEBUG*/xASSERT_RET(NULL != pvValue, FALSE);

#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES != _m_indIndex, FALSE);

    BOOL bRes = ::TlsSetValue(_m_indIndex, pvValue);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif xOS_ENV_UNIX
    /*DEBUG*/xASSERT_RET(0 <= _m_indIndex, FALSE);

    int iRes = ::pthread_setspecific(_m_indIndex, pvValue);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxThreadStorage::_bAlloc() {
    TxIndex indRes = (TxIndex)- 1;

#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES == _m_indIndex, FALSE);

    indRes = ::TlsAlloc();
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES != indRes, FALSE);
#elif xOS_ENV_UNIX
    /*DEBUG*/xASSERT_RET(static_cast<pthread_key_t>( -1 ) == _m_indIndex, FALSE);

    int iRes = ::pthread_key_create(&indRes, NULL);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);
#endif

    _m_indIndex = indRes;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxThreadStorage::_bFree() {
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES != _m_indIndex, FALSE);

    BOOL bRes = ::TlsFree(_m_indIndex);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    _m_indIndex = TLS_OUT_OF_INDEXES;
#elif xOS_ENV_UNIX
    /*DEBUG*/xASSERT_RET(0 <= _m_indIndex, FALSE);

    int iRes = ::pthread_key_delete(_m_indIndex);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);

    _m_indIndex = static_cast<pthread_key_t>( -1 );
#endif

    return TRUE;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
