/**
 * \file  CxThreadStorage.cpp
 * \brief thread local storage
 */


#include <xLib/Sync/CxThreadStorage.h>

#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTracer.h>

xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxThreadStorage::CxThreadStorage() :
#if xOS_ENV_WIN
    _index(TLS_OUT_OF_INDEXES)
#else
    _index(static_cast<pthread_key_t>( -1 ))
#endif
{
    _construct();
}
//------------------------------------------------------------------------------
/* virtual */
xINLINE_HO
CxThreadStorage::~CxThreadStorage()
{
    _destruct();
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxThreadStorage::isSet() const
{
    void_t *pvRv = NULL;

#if xOS_ENV_WIN
    pvRv = ::TlsGetValue(_index);
    xCHECK_RET(NULL == pvRv, false);
#else
    pvRv = ::pthread_getspecific(_index);
    xCHECK_RET(NULL == pvRv, false);
#endif

    return true;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t *
CxThreadStorage::value() const
{
    void_t *pvRv = NULL;

#if xOS_ENV_WIN
    xTEST_DIFF(TLS_OUT_OF_INDEXES, _index);

    pvRv = ::TlsGetValue(_index);
    xTEST_EQ(true, (NULL != pvRv) && (ERROR_SUCCESS == CxLastError::get()));
#else
    xTEST_EQ(true, 0 < _index);

    pvRv = ::pthread_getspecific(_index);
    xTEST_PTR(pvRv);
#endif

    return pvRv;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxThreadStorage::setValue(
    void_t *a_value
) const
{
    xTEST_PTR(a_value);

#if xOS_ENV_WIN
    xTEST_DIFF(TLS_OUT_OF_INDEXES, _index);

    BOOL blRes = ::TlsSetValue(_index, a_value);
    xTEST_DIFF(FALSE, blRes);
#else
    xTEST_EQ(true, 0 < _index);

    int_t iRv = ::pthread_setspecific(_index, a_value);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxThreadStorage::_construct()
{
    index_t indRes = (index_t)- 1;

#if xOS_ENV_WIN
    xTEST_EQ(TLS_OUT_OF_INDEXES, _index);

    indRes = ::TlsAlloc();
    xTEST_DIFF(TLS_OUT_OF_INDEXES, indRes);
#else
    xTEST_EQ(static_cast<pthread_key_t>( - 1 ), _index);

    int_t iRv = ::pthread_key_create(&indRes, NULL);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif

    _index = indRes;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxThreadStorage::_destruct()
{
#if xOS_ENV_WIN
    xTEST_DIFF(TLS_OUT_OF_INDEXES, _index);

    BOOL blRes = ::TlsFree(_index);
    xTEST_DIFF(FALSE, blRes);

    _index = TLS_OUT_OF_INDEXES;
#else
    xTEST_EQ(true, 0 < _index);

    int_t iRv = ::pthread_key_delete(_index);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    _index = static_cast<pthread_key_t>( -1 );
#endif
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
