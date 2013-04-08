/**
 * \file  CxThreadStorage.cpp
 * \brief thread local storage
 */


#include <xLib/Sync/CxThreadStorage.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxThreadStorage::CxThreadStorage() :
#if xOS_ENV_WIN
    _m_indIndex(TLS_OUT_OF_INDEXES)
#else
    _m_indIndex(static_cast<pthread_key_t>( -1 ))
#endif
{
    _construct();
}
//------------------------------------------------------------------------------
/* virtual */
CxThreadStorage::~CxThreadStorage() {
    _destruct();
}
//------------------------------------------------------------------------------
bool_t
CxThreadStorage::isSet() const {
    void_t *pvRv = NULL;

#if xOS_ENV_WIN
    pvRv = ::TlsGetValue(_m_indIndex);
    xCHECK_RET(NULL == pvRv, false);
#else
    pvRv = ::pthread_getspecific(_m_indIndex);
    xCHECK_RET(NULL == pvRv, false);
#endif

    return true;
}
//------------------------------------------------------------------------------
void_t *
CxThreadStorage::value() const {
    void_t *pvRv = NULL;

#if xOS_ENV_WIN
    xTEST_DIFF(TLS_OUT_OF_INDEXES, _m_indIndex);

    pvRv = ::TlsGetValue(_m_indIndex);
    xTEST_EQ(true, (NULL != pvRv) && (ERROR_SUCCESS == CxLastError::get()));
#else
    xTEST_EQ(true, 0 < _m_indIndex);

    pvRv = ::pthread_getspecific(_m_indIndex);
    xTEST_PTR(pvRv);
#endif

    return pvRv;
}
//------------------------------------------------------------------------------
void_t
CxThreadStorage::setValue(
    void_t *a_pvValue
) const
{
    xTEST_PTR(a_pvValue);

#if xOS_ENV_WIN
    xTEST_DIFF(TLS_OUT_OF_INDEXES, _m_indIndex);

    BOOL blRes = ::TlsSetValue(_m_indIndex, a_pvValue);
    xTEST_DIFF(FALSE, blRes);
#else
    xTEST_EQ(true, 0 < _m_indIndex);

    int_t iRv = ::pthread_setspecific(_m_indIndex, a_pvValue);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void_t
CxThreadStorage::_construct() {
    index_t indRes = (index_t)- 1;

#if xOS_ENV_WIN
    xTEST_EQ(TLS_OUT_OF_INDEXES, _m_indIndex);

    indRes = ::TlsAlloc();
    xTEST_DIFF(TLS_OUT_OF_INDEXES, indRes);
#else
    xTEST_EQ(static_cast<pthread_key_t>( - 1 ), _m_indIndex);

    int_t iRv = ::pthread_key_create(&indRes, NULL);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif

    _m_indIndex = indRes;
}
//------------------------------------------------------------------------------
void_t
CxThreadStorage::_destruct() {
#if xOS_ENV_WIN
    xTEST_DIFF(TLS_OUT_OF_INDEXES, _m_indIndex);

    BOOL blRes = ::TlsFree(_m_indIndex);
    xTEST_DIFF(FALSE, blRes);

    _m_indIndex = TLS_OUT_OF_INDEXES;
#else
    xTEST_EQ(true, 0 < _m_indIndex);

    int_t iRv = ::pthread_key_delete(_m_indIndex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    _m_indIndex = static_cast<pthread_key_t>( -1 );
#endif
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
