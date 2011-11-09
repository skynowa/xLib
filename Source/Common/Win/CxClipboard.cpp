/**
 * \file  CxClipboard.cpp
 * \brief clipboard
 */


#include <xLib/Common/Win/CxClipboard.h>


#if defined(xOS_ENV_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxClipboard::CxClipboard() :
    _m_hObject  (NULL),
    _m_hWndOwner(NULL)
{
}
//---------------------------------------------------------------------------
/*virtual*/
CxClipboard::~CxClipboard() {
    /*DEBUG*///
}
//---------------------------------------------------------------------------
BOOL
CxClipboard::bSetOwner(
    const HWND chWndOwner
)
{
    /*DEBUG*///

    _m_hWndOwner = chWndOwner;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxClipboard::bOpen() {
    /*DEBUG*///

    BOOL bRes = ::OpenClipboard(_m_hWndOwner);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxClipboard::bClose() {
    /*DEBUG*///

    BOOL bRes = ::CloseClipboard();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxClipboard::bGetData(
    const EFormat cfmFormat
)
{
    /*DEBUG*///

    _m_hObject = ::GetClipboardData(static_cast<UINT>( cfmFormat ));
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxClipboard::bSetData(
    const EFormat cfmFormat,
    const HANDLE  chData
)
{
    /*DEBUG*///

    _m_hObject = ::SetClipboardData(static_cast<UINT>( cfmFormat ), chData);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxClipboard::bGetText(
    std::string_t *psText
)
{
    /*DEBUG*/xASSERT_RET(NULL != psText, FALSE);

    BOOL bRes = bOpen();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

#if defined(xUNICODE)
    bRes = bGetData(fmUnicodeText);
#else
    bRes = bGetData(fmText);
#endif
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    LPVOID pvData = ::GlobalLock(_m_hObject);
    /*DEBUG*/xASSERT_RET(NULL != pvData, FALSE);

    //TODO: resize() ???
    SIZE_T uiDataSize = ::GlobalSize(_m_hObject);
    /*DEBUG*/xASSERT_RET(0 != uiDataSize, FALSE);

    uiDataSize = uiDataSize / sizeof(std::string_t::value_type) - 1;    //'\0'

    (*psText).assign(static_cast<LPCTSTR>( pvData ), uiDataSize);

    bRes = ::GlobalUnlock(_m_hObject);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = bClose();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxClipboard::bSetText(
    const std::string_t &csText
)
{
    /*DEBUG*/

    BOOL bRes = bClear();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = bOpen();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    ////bRes = ::EmptyClipboard();
    /////*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    const SIZE_T cuiBytes = (csText.size() + 1 ) * sizeof(std::string_t::value_type);    //'\0'

    _m_hObject = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, cuiBytes);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject, FALSE);

    LPVOID pvData = ::GlobalLock(_m_hObject);
    /*DEBUG*/xASSERT_RET(NULL != pvData, FALSE);

    ::CopyMemory(pvData, csText.data(), cuiBytes);    //'\0'
    /*DEBUG*/// n/a

    bRes = ::GlobalUnlock(_m_hObject);
    /*DEBUG*/xASSERT_RET((FALSE == bRes) && (NO_ERROR == CxLastError::ulGet()), FALSE);

#if defined(xUNICODE)
    bRes = bSetData(fmUnicodeText, _m_hObject);
#else
    bRes = bSetData(fmText,        _m_hObject);
#endif
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = bClose();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxClipboard::bClear() {
    /*DEBUG*///

    BOOL bRes = bOpen();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = ::EmptyClipboard();
    /*DEBUG*/xASSERT(FALSE != bRes);

    bRes = bClose();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL CxClipboard::bIsHasFormat(
    const EFormat cfmFormat
)
{
    /*DEBUG*///

    BOOL bRes = ::IsClipboardFormatAvailable(static_cast<UINT>( cfmFormat ));
    /*DEBUG*/// n/a

    return bRes;
}
//---------------------------------------------------------------------------
BOOL
CxClipboard::bRegisterFormat(
    const std::string_t &csText,
    EFormat            *pfmFormat
)
{
    /*DEBUG*/// csText
    /*DEBUG*/xASSERT_RET(NULL != pfmFormat, FALSE);

    UINT uiRes = ::RegisterClipboardFormat(csText.c_str());
    /*DEBUG*/xASSERT_RET(0 != uiRes, FALSE);

    *pfmFormat = static_cast<EFormat>( uiRes );

    return TRUE;
}
//---------------------------------------------------------------------------
#endif
