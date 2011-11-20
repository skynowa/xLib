/**
 * \file  CxClipboard.cpp
 * \brief clipboard
 */


#include <xLib/Common/Win/CxClipboard.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

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
bool
CxClipboard::bSetOwner(
    const HWND chWndOwner
)
{
    /*DEBUG*///

    _m_hWndOwner = chWndOwner;

    return true;
}
//---------------------------------------------------------------------------
bool
CxClipboard::bOpen() {
    /*DEBUG*///

    BOOL bRes = ::OpenClipboard(_m_hWndOwner);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxClipboard::bClose() {
    /*DEBUG*///

    BOOL bRes = ::CloseClipboard();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxClipboard::bGetData(
    const EFormat cfmFormat
)
{
    /*DEBUG*///

    _m_hObject = ::GetClipboardData(static_cast<UINT>( cfmFormat ));
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxClipboard::bSetData(
    const EFormat cfmFormat,
    const HANDLE  chData
)
{
    /*DEBUG*///

    _m_hObject = ::SetClipboardData(static_cast<UINT>( cfmFormat ), chData);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxClipboard::bGetText(
    std::tstring *psText
)
{
    /*DEBUG*/xASSERT_RET(NULL != psText, false);

    bool bRes = bOpen();
    /*DEBUG*/xASSERT_RET(false != bRes, false);

#if xUNICODE
    bRes = bGetData(fmUnicodeText);
#else
    bRes = bGetData(fmText);
#endif
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    LPVOID pvData = ::GlobalLock(_m_hObject);
    /*DEBUG*/xASSERT_RET(NULL != pvData, false);

    //TODO: resize() ???
    SIZE_T uiDataSize = ::GlobalSize(_m_hObject);
    /*DEBUG*/xASSERT_RET(0 != uiDataSize, false);

    uiDataSize = uiDataSize / sizeof(std::tstring::value_type) - 1;    //'\0'

    (*psText).assign(static_cast<LPCTSTR>( pvData ), uiDataSize);

    BOOL blRes = ::GlobalUnlock(_m_hObject);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    bRes = bClose();
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxClipboard::bSetText(
    const std::tstring &csText
)
{
    /*DEBUG*/

    bool bRes = bClear();
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    bRes = bOpen();
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    ////bRes = ::EmptyClipboard();
    /////*DEBUG*/xASSERT_RET(false != bRes, false);

    const SIZE_T cuiBytes = (csText.size() + 1 ) * sizeof(std::tstring::value_type);    //'\0'

    _m_hObject = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, cuiBytes);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject, false);

    LPVOID pvData = ::GlobalLock(_m_hObject);
    /*DEBUG*/xASSERT_RET(NULL != pvData, false);

    ::CopyMemory(pvData, csText.data(), cuiBytes);    //'\0'
    /*DEBUG*/// n/a

    BOOL blRes = ::GlobalUnlock(_m_hObject);
    /*DEBUG*/xASSERT_RET((FALSE == blRes) && (NO_ERROR == CxLastError::ulGet()), false);

#if xUNICODE
    bRes = bSetData(fmUnicodeText, _m_hObject);
#else
    bRes = bSetData(fmText,        _m_hObject);
#endif
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    bRes = bClose();
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxClipboard::bClear() {
    /*DEBUG*///

    bool bRes = bOpen();
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    BOOL blRes = ::EmptyClipboard();
    /*DEBUG*/xASSERT(FALSE != blRes);

    bRes = bClose();
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool 
CxClipboard::bIsHasFormat(
    const EFormat cfmFormat
)
{
    /*DEBUG*///

    BOOL bRes = ::IsClipboardFormatAvailable(static_cast<UINT>( cfmFormat ));
    /*DEBUG*/// n/a

    return !!bRes;
}
//---------------------------------------------------------------------------
bool
CxClipboard::bRegisterFormat(
    const std::tstring &csText,
    EFormat            *pfmFormat
)
{
    /*DEBUG*/// csText
    /*DEBUG*/xASSERT_RET(NULL != pfmFormat, false);

    UINT uiRes = ::RegisterClipboardFormat(csText.c_str());
    /*DEBUG*/xASSERT_RET(0 != uiRes, false);

    *pfmFormat = static_cast<EFormat>( uiRes );

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
