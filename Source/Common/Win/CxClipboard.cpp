/****************************************************************************
* Class name:  CxClipboard
* Description: ����� ������
* File name:   CxClipboard.cpp
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     12.07.2010 12:43:35
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Common/Win/CxClipboard.h>


/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxClipboard (comment)
CxClipboard::CxClipboard() :
	_m_bRes     (FALSE),
	_m_hObject  (NULL),
	_m_hWndOwner(NULL)
{
}
//---------------------------------------------------------------------------
//TODO: + ~CxClipboard (comment)
CxClipboard::~CxClipboard() {
	/*DEBUG*///
}
//---------------------------------------------------------------------------
//TODO: + bSetOwner ()
BOOL 
CxClipboard::bSetOwner(HWND hWndOwner) {
	/*DEBUG*///

	_m_hWndOwner = hWndOwner;	

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bOpen ()
BOOL 
CxClipboard::bOpen() {
	/*DEBUG*///

	_m_bRes = ::OpenClipboard(_m_hWndOwner);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bClose ()
BOOL 
CxClipboard::bClose() {
	/*DEBUG*///

	_m_bRes = ::CloseClipboard();
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bGetData ()
BOOL 
CxClipboard::bGetData(EFormat fmFormat) {
	/*DEBUG*///

	_m_hObject = ::GetClipboardData(static_cast<UINT>(fmFormat));
	/*DEBUG*/xASSERT_RET(NULL != _m_hObject, FALSE); 

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bSetData ()
BOOL 
CxClipboard::bSetData(EFormat fmFormat, HANDLE hData) {
	/*DEBUG*///

	_m_hObject = ::SetClipboardData(static_cast<UINT>(fmFormat), hData);
	/*DEBUG*/xASSERT_RET(NULL != _m_hObject, FALSE); 

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bGetText ()
BOOL 
CxClipboard::bGetText(tString *psText) {
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

	uiDataSize = uiDataSize / sizeof(tString::value_type) - 1;	//'\0' - �� �����

	(*psText).assign(static_cast<LPCTSTR>(pvData), uiDataSize);	

	_m_bRes = ::GlobalUnlock(_m_hObject);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

	_m_bRes = bClose();
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bSetText ()
BOOL 
CxClipboard::bSetText(const tString csText) {
	/*DEBUG*/

	_m_bRes = bClear();
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	_m_bRes = bOpen();
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);  

	////_m_bRes = ::EmptyClipboard();
	/////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

	const SIZE_T cuiBytes = (csText.size() + 1 ) * sizeof(tString::value_type);	//'\0' - �����
	
	_m_hObject = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, cuiBytes);
	/*DEBUG*/xASSERT_RET(NULL != _m_hObject, FALSE); 

	LPVOID pvData = ::GlobalLock(_m_hObject);
	/*DEBUG*/xASSERT_RET(NULL != pvData, FALSE);

	::CopyMemory(pvData, csText.data(), cuiBytes);	//'\0' - �� ����� ????
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
//TODO: + bClear ()
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
//TODO: - bIsHasFormat ()
BOOL CxClipboard::bIsHasFormat(EFormat fmFormat) {
	/*DEBUG*///

	_m_bRes = ::IsClipboardFormatAvailable(static_cast<UINT>(fmFormat));
	/*DEBUG*/// n/a

	return _m_bRes;
}
//---------------------------------------------------------------------------
//TODO: - bRegisterFormat ()
BOOL 
CxClipboard::bRegisterFormat(const tString csText, EFormat *pfmFormat) {
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
