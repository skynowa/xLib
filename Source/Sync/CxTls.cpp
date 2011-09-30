/**
 * \file  CxTls.cpp
 * \brief thread local storage
 */


#include <xLib/Sync/CxTls.h>


#if defined(xOS_ENV_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxTls
CxTls::CxTls() :
    _m_ulIndex(TLS_OUT_OF_INDEXES)
{

}
//---------------------------------------------------------------------------
//TODO: ~CxTls
CxTls::~CxTls() {

}
//---------------------------------------------------------------------------
//DONE: bAlloc (Allocates a thread local storage (TLS) index)
BOOL
CxTls::bAlloc() {
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES == _m_ulIndex, FALSE);

    ULONG ulRes = TLS_OUT_OF_INDEXES;

    ulRes = ::TlsAlloc();
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES != ulRes, FALSE);

    _m_ulIndex = ulRes;

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bFree (Releases a thread local storage (TLS) index, making it available for reuse)
BOOL
CxTls::bFree() {
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES != _m_ulIndex, FALSE);

    BOOL bRes = FALSE;

    bRes = ::TlsFree(_m_ulIndex);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: pGetValue (Retrieves the value in the calling thread's thread local storage (TLS) slot for the specified TLS index)
VOID *
CxTls::pvGetValue() {
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES != _m_ulIndex, FALSE);

    VOID *pvRes = NULL;

    pvRes = ::TlsGetValue(_m_ulIndex);
    /*DEBUG*/xASSERT_RET(FALSE      != pvRes, FALSE);
    /*DEBUG*/////xASSERT_RET(_m_ulIndex == pvRes, FALSE);

    return pvRes;
}
//---------------------------------------------------------------------------
//TODO: bSetValue (Stores a value in the calling thread's thread local storage (TLS) slot for the specified TLS index)
BOOL
CxTls::bSetValue(
    VOID *pvValue
)
{
    /*DEBUG*/xASSERT_RET(TLS_OUT_OF_INDEXES != _m_ulIndex, FALSE);
    /*DEBUG*/xASSERT_RET(NULL               != pvValue,    FALSE);

    BOOL bRes = FALSE;

    bRes = ::TlsSetValue(_m_ulIndex, pvValue);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
#elif defined(xOS_ENV_UNIX)

#endif
