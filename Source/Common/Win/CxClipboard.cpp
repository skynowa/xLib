/**
 * \file  CxClipboard.cpp
 * \brief clipboard
 */


#include <xLib/Common/Win/CxClipboard.h>


#if defined(xOS_WIN)
/****************************************************************************
*    Public methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxClipboard
CxClipboard::CxClipboard() :
    _m_bRes     (FALSE),
    _m_hObject  (NULL),
    _m_hWndOwner(NULL)
{
}
//---------------------------------------------------------------------------
//DONE: ~CxClipboard
/*virtual*/
CxClipboard::~CxClipboard() {
    /*DEBUG*///
}
//---------------------------------------------------------------------------
//DONE: bSetOwner ()
BOOL
CxClipboard::bSetOwner(HWND hWndOwner) {
    /*DEBUG*///

    _m_hWndOwner = hWndOwner;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bOpen ()
BOOL
CxClipboard::bOpen() {
    /*DEBUG*///

    _m_bRes = ::OpenClipboard(_m_hWndOwner);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClose ()
BOOL
CxClipboard::bClose() {
    /*DEBUG*///

    _m_bRes = ::CloseClipboard();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetData ()
BOOL
CxClipboard::bGetData(
    EFormat fmFormat
)
{
    /*DEBUG*///

    _m_hObject = ::GetClipboardData(static_cast<UINT>(fmFormat));
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSetData ()
BOOL
CxClipboard::bSetData(
    EFormat fmFormat, 
    HANDLE  hData
)
{
    /*DEBUG*///

    _m_hObject = ::SetClipboardData(static_cast<UINT>(fmFormat), hData);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetText ()
BOOL
CxClipboard::bGetText(
    std::tstring *psText
)
{
    /*DEBUG*/xASSERT_RET(NULL != psText, FALSE);

    _m_bRes = bOpen();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

#ifdef _UNICODE
    _m_bRes = bGetData(fmUnicodeText);
#else
    _m_bRes = bGetData(fmText);
#endif
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    LPVOID pvData = ::GlobalLock(_m_hObject);
    /*DEBUG*/xASSERT_RET(NULL != pvData, FALSE);

    //TODO: resize() ???
    SIZE_T uiDataSize = ::GlobalSize(_m_hObject);
    /*DEBUG*/xASSERT_RET(0 != uiDataSize, FALSE);

    uiDataSize = uiDataSize / sizeof(std::tstring::value_type) - 1;    //'\0' - �� �����

    (*psText).assign(static_cast<LPCTSTR>(pvData), uiDataSize);

    _m_bRes = ::GlobalUnlock(_m_hObject);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_bRes = bClose();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSetText ()
BOOL
CxClipboard::bSetText(
    const std::tstring csText
)
{
    /*DEBUG*/

    _m_bRes = bClear();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_bRes = bOpen();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    ////_m_bRes = ::EmptyClipboard();
    /////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    const SIZE_T cuiBytes = (csText.size() + 1 ) * sizeof(std::tstring::value_type);    //'\0' - �����

    _m_hObject = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, cuiBytes);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject, FALSE);

    LPVOID pvData = ::GlobalLock(_m_hObject);
    /*DEBUG*/xASSERT_RET(NULL != pvData, FALSE);

    ::CopyMemory(pvData, csText.data(), cuiBytes);    //'\0' - �� ����� ????
    /*DEBUG*/// n/a

    _m_bRes = ::GlobalUnlock(_m_hObject);
    /*DEBUG*/xASSERT_RET((FALSE == _m_bRes) && (NO_ERROR == ::GetLastError()), FALSE);

#ifdef _UNICODE
    _m_bRes = bSetData(fmUnicodeText, _m_hObject);
#else
    _m_bRes = bSetData(fmText,        _m_hObject);
#endif
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_bRes = bClose();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClear ()
BOOL
CxClipboard::bClear() {
    /*DEBUG*///

    _m_bRes = bOpen();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_bRes = ::EmptyClipboard();
    /*DEBUG*/xASSERT(FALSE != _m_bRes);

    _m_bRes = bClose();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bIsHasFormat ()
BOOL CxClipboard::bIsHasFormat(
    EFormat fmFormat
)
{
    /*DEBUG*///

    _m_bRes = ::IsClipboardFormatAvailable(static_cast<UINT>(fmFormat));
    /*DEBUG*/// n/a

    return _m_bRes;
}
//---------------------------------------------------------------------------
//TODO: bRegisterFormat ()
BOOL
CxClipboard::bRegisterFormat(
    const std::tstring  csText, 
    EFormat            *pfmFormat
)
{
    /*DEBUG*/// csText
    /*DEBUG*/xASSERT_RET(NULL != pfmFormat, FALSE);

    UINT uiRes = ::RegisterClipboardFormat(csText.c_str());
    /*DEBUG*/xASSERT_RET(0 != uiRes, FALSE);

    *pfmFormat = static_cast<EFormat>(uiRes);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
#elif defined(xOS_LINUX)

#endif
