/**
 * \file  CxThreadStorage.cpp
 * \brief thread local storage
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTrace.h>


xNAMESPACE2_BEGIN(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxThreadStorage::CxThreadStorage() :
#if   xOS_ENV_WIN
    _index(TLS_OUT_OF_INDEXES)
#elif xOS_ENV_UNIX
    _index(static_cast<pthread_key_t>( -1 ))
#endif
{
    _construct();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxThreadStorage::~CxThreadStorage()
{
    _destruct();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThreadStorage::isSet() const
{
    void_t *pvRv = xPTR_NULL;

#if   xOS_ENV_WIN
    pvRv = ::TlsGetValue(_index);
    xCHECK_RET(xPTR_NULL == pvRv, false);
#elif xOS_ENV_UNIX
    pvRv = ::pthread_getspecific(_index);
    xCHECK_RET(xPTR_NULL == pvRv, false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t *
CxThreadStorage::value() const
{
    void_t *pvRv = xPTR_NULL;

#if   xOS_ENV_WIN
    xTEST_DIFF(TLS_OUT_OF_INDEXES, _index);

    pvRv = ::TlsGetValue(_index);
    xTEST_EQ(true, (xPTR_NULL != pvRv) && (ERROR_SUCCESS == CxLastError::get()));
#elif xOS_ENV_UNIX
    xTEST_EQ(true, 0 < _index);

    pvRv = ::pthread_getspecific(_index);
    xTEST_PTR(pvRv);
#endif

    return pvRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThreadStorage::setValue(
    void_t *a_value
) const
{
    xTEST_PTR(a_value);

#if   xOS_ENV_WIN
    xTEST_DIFF(TLS_OUT_OF_INDEXES, _index);

    BOOL blRv = ::TlsSetValue(_index, a_value);
    xTEST_DIFF(FALSE, blRv);
#elif xOS_ENV_UNIX
    xTEST_EQ(true, 0 < _index);

    int_t iRv = ::pthread_setspecific(_index, a_value);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxThreadStorage::_construct()
{
    index_t indRv = (index_t)- 1;

#if   xOS_ENV_WIN
    xTEST_EQ(TLS_OUT_OF_INDEXES, _index);

    indRv = ::TlsAlloc();
    xTEST_DIFF(TLS_OUT_OF_INDEXES, indRv);
#elif xOS_ENV_UNIX
    xTEST_EQ(static_cast<pthread_key_t>( - 1 ), _index);

    int_t iRv = ::pthread_key_create(&indRv, xPTR_NULL);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif

    _index = indRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThreadStorage::_destruct()
{
#if   xOS_ENV_WIN
    xTEST_DIFF(TLS_OUT_OF_INDEXES, _index);

    BOOL blRv = ::TlsFree(_index);
    xTEST_DIFF(FALSE, blRv);

    _index = TLS_OUT_OF_INDEXES;
#elif xOS_ENV_UNIX
    xTEST_EQ(true, 0 < _index);

    int_t iRv = ::pthread_key_delete(_index);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    _index = static_cast<pthread_key_t>( -1 );
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, sync)
