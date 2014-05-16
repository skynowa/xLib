/**
 * \file  CxThreadStorage.inl
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
#if   xENV_WIN
    _index(TLS_OUT_OF_INDEXES)
#elif xENV_UNIX
    _index(static_cast<pthread_key_t>( - 1 ))
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

#if   xENV_WIN
    pvRv = ::TlsGetValue(_index);
    xCHECK_RET(pvRv == xPTR_NULL, false);
#elif xENV_UNIX
    pvRv = ::pthread_getspecific(_index);
    xCHECK_RET(pvRv == xPTR_NULL, false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t *
CxThreadStorage::value() const
{
    void_t *pvRv = xPTR_NULL;

#if   xENV_WIN
    xTEST_DIFF(TLS_OUT_OF_INDEXES, _index);

    pvRv = ::TlsGetValue(_index);
    xTEST_EQ((pvRv != xPTR_NULL) && (CxLastError::get() == ERROR_SUCCESS), true);
#elif xENV_UNIX
    xTEST_EQ(0 < _index, true);

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

#if   xENV_WIN
    xTEST_DIFF(_index, TLS_OUT_OF_INDEXES);

    BOOL blRv = ::TlsSetValue(_index, a_value);
    xTEST_DIFF(blRv, FALSE);
#elif xENV_UNIX
    xTEST_EQ(0 < _index, true);

    int_t iRv = ::pthread_setspecific(_index, a_value);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
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

#if   xENV_WIN
    xTEST_EQ(_index, TLS_OUT_OF_INDEXES);

    indRv = ::TlsAlloc();
    xTEST_DIFF(indRv, TLS_OUT_OF_INDEXES);
#elif xENV_UNIX
    xTEST_EQ(_index, static_cast<pthread_key_t>( - 1 ));

    int_t iRv = ::pthread_key_create(&indRv, xPTR_NULL);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
#endif

    _index = indRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThreadStorage::_destruct()
{
#if   xENV_WIN
    xTEST_DIFF(_index, TLS_OUT_OF_INDEXES);

    BOOL blRv = ::TlsFree(_index);
    xTEST_DIFF(blRv, FALSE);

    _index = TLS_OUT_OF_INDEXES;
#elif xENV_UNIX
    xTEST_EQ(0 < _index, true);

    int_t iRv = ::pthread_key_delete(_index);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    _index = static_cast<pthread_key_t>( -1 );
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, sync)
