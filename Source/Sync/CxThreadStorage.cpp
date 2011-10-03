/**
 * \file  CxThreadStorage.cpp
 * \brief thread local storage
 */


#include <xLib/Sync/CxThreadStorage.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxThreadStorage::CxThreadStorage() :
#if defined(xOS_ENV_WIN)
    _m_indIndex(TLS_OUT_OF_INDEXES)
#elif defined(xOS_ENV_UNIX)
    _m_indIndex(static_cast<pthread_key_t>( -1 ))
#endif
{
    (VOID)_bAlloc();
}
//---------------------------------------------------------------------------
/*virtual*/
CxThreadStorage::~CxThreadStorage() {
    (VOID)_bFree();
}
//---------------------------------------------------------------------------
VOID *
CxThreadStorage::pvGetValue() const {
    VOID *pvRes = NULL;

#if defined(xOS_ENV_WIN)
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES != _m_indIndex, NULL);

    pvRes = ::TlsGetValue(_m_indIndex);
    /*DEBUG*/xASSERT_RET(NULL != pvRes, NULL);
#elif defined(xOS_ENV_UNIX)
    /*DEBUG*/xASSERT_RET(0 <= _m_indIndex, NULL);

    pvRes = pthread_getspecific(_m_indIndex);
    /*DEBUG*/xASSERT_RET(NULL != pvRes, NULL);
#endif

    return pvRes;
}
//---------------------------------------------------------------------------
BOOL
CxThreadStorage::bSetValue(
    VOID *pvValue
) const
{
    /*DEBUG*/xASSERT_RET(NULL != pvValue, FALSE);

#if defined(xOS_ENV_WIN)
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES != _m_indIndex, FALSE);

    BOOL bRes = ::TlsSetValue(_m_indIndex, pvValue);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    /*DEBUG*/xASSERT_RET(0 <= _m_indIndex, FALSE);

    INT iRes = pthread_setspecific(_m_indIndex, pvValue);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	private
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxThreadStorage::_bAlloc() {
    TxIndex indRes = (TxIndex)- 1;

#if defined(xOS_ENV_WIN)
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES == _m_indIndex, FALSE);

    indRes = ::TlsAlloc();
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES != indRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    /*DEBUG*/xASSERT_RET(static_cast<pthread_key_t>( -1 ) == _m_indIndex, FALSE);

    INT iRes = pthread_key_create(&indRes, NULL);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);
#endif

    _m_indIndex = indRes;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxThreadStorage::_bFree() {
#if defined(xOS_ENV_WIN)
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES != _m_indIndex, FALSE);

    BOOL bRes = ::TlsFree(_m_indIndex);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    _m_indIndex = TLS_OUT_OF_INDEXES;
#elif defined(xOS_ENV_UNIX)
    /*DEBUG*/xASSERT_RET(0 <= _m_indIndex, FALSE);

    INT iRes = pthread_key_delete(_m_indIndex);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);

    _m_indIndex = static_cast<pthread_key_t>( -1 );
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
