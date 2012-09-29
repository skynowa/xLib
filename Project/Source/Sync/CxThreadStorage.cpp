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
#if   xOS_ENV_WIN
    _m_indIndex(TLS_OUT_OF_INDEXES)
#elif xOS_ENV_UNIX
    _m_indIndex(static_cast<pthread_key_t>( -1 ))
#endif
{
    (void)_bAlloc();
}
//---------------------------------------------------------------------------
/* virtual */
CxThreadStorage::~CxThreadStorage() {
    (void)_bFree();
}
//---------------------------------------------------------------------------
bool
CxThreadStorage::bIsSet() const {
    void *pvRv = NULL;

#if   xOS_ENV_WIN
    pvRv = ::TlsGetValue(_m_indIndex);
    xCHECK_RET(NULL == pvRv, false);
#elif xOS_ENV_UNIX
    pvRv = ::pthread_getspecific(_m_indIndex);
    xCHECK_RET(NULL == pvRv, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
void *
CxThreadStorage::pvGetValue() const {
    void *pvRv = NULL;

#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES != _m_indIndex, NULL);

    pvRv = ::TlsGetValue(_m_indIndex);
    /*DEBUG*/xASSERT_RET((NULL != pvRv) && (ERROR_SUCCESS == CxLastError::ulGet()), NULL);
#elif xOS_ENV_UNIX
    /*DEBUG*/xASSERT_RET(0 <= _m_indIndex, NULL);

    pvRv = ::pthread_getspecific(_m_indIndex);
    /*DEBUG*/xASSERT_RET(NULL != pvRv, NULL);
#endif

    return pvRv;
}
//---------------------------------------------------------------------------
bool
CxThreadStorage::bSetValue(
    void *a_pvValue
) const
{
    /*DEBUG*/xASSERT_RET(NULL != a_pvValue, false);

#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES != _m_indIndex, false);

    BOOL blRes = ::TlsSetValue(_m_indIndex, a_pvValue);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    /*DEBUG*/xASSERT_RET(0 <= _m_indIndex, false);

    int iRv = ::pthread_setspecific(_m_indIndex, a_pvValue);
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
CxThreadStorage::_bAlloc() {
    index_t indRes = (index_t)- 1;

#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES == _m_indIndex, false);

    indRes = ::TlsAlloc();
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES != indRes, false);
#elif xOS_ENV_UNIX
    /*DEBUG*/xASSERT_RET(static_cast<pthread_key_t>( -1 ) == _m_indIndex, false);

    int iRv = ::pthread_key_create(&indRes, NULL);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), false);
#endif

    _m_indIndex = indRes;

    return true;
}
//---------------------------------------------------------------------------
bool
CxThreadStorage::_bFree() {
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES != _m_indIndex, false);

    BOOL blRes = ::TlsFree(_m_indIndex);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    _m_indIndex = TLS_OUT_OF_INDEXES;
#elif xOS_ENV_UNIX
    /*DEBUG*/xASSERT_RET(0 <= _m_indIndex, false);

    int iRv = ::pthread_key_delete(_m_indIndex);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), false);

    _m_indIndex = static_cast<pthread_key_t>( -1 );
#endif

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
