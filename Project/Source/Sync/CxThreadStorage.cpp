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
    _vAlloc();
}
//---------------------------------------------------------------------------
/* virtual */
CxThreadStorage::~CxThreadStorage() {
    _vFree();
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
CxThreadStorage::pvValue() const {
    void *pvRv = NULL;

#if   xOS_ENV_WIN
    /*DEBUG*/xTEST_DIFF(TLS_OUT_OF_INDEXES, _m_indIndex);

    pvRv = ::TlsGetValue(_m_indIndex);
    /*DEBUG*/xTEST_EQ(true, (NULL != pvRv) && (ERROR_SUCCESS == CxLastError::ulGet()));
#elif xOS_ENV_UNIX
    /*DEBUG*/xTEST_EQ(true, 0 < _m_indIndex);

    pvRv = ::pthread_getspecific(_m_indIndex);
    /*DEBUG*/xTEST_PTR(pvRv);
#endif

    return pvRv;
}
//---------------------------------------------------------------------------
void
CxThreadStorage::vSetValue(
    void *a_pvValue
) const
{
    /*DEBUG*/xTEST_PTR(a_pvValue);

#if   xOS_ENV_WIN
    /*DEBUG*/xTEST_DIFF(TLS_OUT_OF_INDEXES, _m_indIndex);

    BOOL blRes = ::TlsSetValue(_m_indIndex, a_pvValue);
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    /*DEBUG*/xTEST_EQ(true, 0 < _m_indIndex);

    int iRv = ::pthread_setspecific(_m_indIndex, a_pvValue);
    /*DEBUG*/xTEST_MSG_EQ(0, iRv, CxLastError::sFormat(iRv));
#endif
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxThreadStorage::_vAlloc() {
    index_t indRes = (index_t)- 1;

#if   xOS_ENV_WIN
    /*DEBUG*/xTEST_EQ(TLS_OUT_OF_INDEXES, _m_indIndex);

    indRes = ::TlsAlloc();
    /*DEBUG*/xTEST_DIFF(TLS_OUT_OF_INDEXES, indRes);
#elif xOS_ENV_UNIX
    /*DEBUG*/xTEST_EQ(static_cast<pthread_key_t>( - 1 ), _m_indIndex);

    int iRv = ::pthread_key_create(&indRes, NULL);
    /*DEBUG*/xTEST_MSG_EQ(0, iRv, CxLastError::sFormat(iRv));
#endif

    _m_indIndex = indRes;
}
//---------------------------------------------------------------------------
void
CxThreadStorage::_vFree() {
#if   xOS_ENV_WIN
    /*DEBUG*/xTEST_DIFF(TLS_OUT_OF_INDEXES, _m_indIndex);

    BOOL blRes = ::TlsFree(_m_indIndex);
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);

    _m_indIndex = TLS_OUT_OF_INDEXES;
#elif xOS_ENV_UNIX
    /*DEBUG*/xTEST_EQ(true, 0 < _m_indIndex);

    int iRv = ::pthread_key_delete(_m_indIndex);
    /*DEBUG*/xTEST_MSG_EQ(0, iRv, CxLastError::sFormat(iRv));

    _m_indIndex = static_cast<pthread_key_t>( -1 );
#endif
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
