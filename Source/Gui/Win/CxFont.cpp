/****************************************************************************
* Class name:  CxFont
* Description: רנטפע
* File name:   CxFont.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     09.03.2010 10:36:56
*
*****************************************************************************/


#include <xLib/Gui/CxFont.h>

/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxFont
CxFont::CxFont() : 
	_m_hFont(NULL),
	_m_bRes (FALSE)
{
}
//---------------------------------------------------------------------------
//TODO: - ~CxFont
CxFont::~CxFont() {
	xCHECK_DO(NULL != _m_hFont, bDelete());
}
//---------------------------------------------------------------------------
//TODO: - bCreate (creates a logical font with the specified characteristics) 
BOOL CxFont::bCreate(				
				INT     iHeight,
				INT     iWidth,
				INT     iEscapement,
				INT     iOrientation,
				INT     iWeight,
				ULONG   ulItalic,
				ULONG   ulUnderline,
				ULONG   ulStrikeOut,
				ULONG   ulCharSet,
				ULONG   ulOutputPrecision,
				ULONG   ulClipPrecision,
				ULONG   ulQuality,
				ULONG   ulPitchAndFamily,
				LPCTSTR pcszFace) 
{
	/*DEBUG*/xASSERT_RET(NULL == _m_hFont, FALSE); 
	
	HFONT hFont = NULL;
	
	hFont = ::CreateFont(iHeight, iWidth, iEscapement, iOrientation, iWeight, 
	                     ulItalic, ulUnderline, ulStrikeOut, ulCharSet, 
						 ulOutputPrecision, ulClipPrecision, ulQuality, ulPitchAndFamily, pcszFace);
	/*DEBUG*/xASSERT_RET(NULL != hFont, FALSE);

	_m_hFont = hFont;

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bCreateDefault
BOOL CxFont::bCreateDefault() {
	/*DEBUG*/xASSERT_RET(NULL == _m_hFont, FALSE); 

	//_m_hFont = ::CreateFont(- 11, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, 
	//					      OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma");
	_m_bRes = bCreate(- 11, 0, 0, 0, 400, 0, 0, 0, 0xCC, 0, 0, 0, DEFAULT_PITCH, /*_T("Arial Black")*/_T("Tahoma"));
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: hGet
HFONT CxFont::hGet(HWND hWnd) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hFont, NULL);
	/*DEBUG*/xASSERT_RET(NULL != hWnd,     NULL); 

	HFONT hFont = NULL;

	hFont = reinterpret_cast<HFONT>( ::SendMessage(hWnd, WM_GETFONT, 0, 0) );
	/*DEBUG*/xASSERT_RET(NULL != hFont, NULL);	//NULL if the control is using the system font.

	return hFont;
}
//---------------------------------------------------------------------------
//DONE: bSet
BOOL CxFont::bSet(HWND hWnd) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hFont, FALSE);
	/*DEBUG*/xASSERT_RET(NULL != hWnd,     FALSE); 

	//TODO: reinterpret_cast
	_m_bRes = static_cast<BOOL>( ::SendMessage(hWnd, WM_SETFONT, reinterpret_cast<WPARAM>(_m_hFont), /*MAKELPARAM(TRUE, 0)*/TRUE) );	
	/*DEBUG*///not return a value

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bDelete
BOOL CxFont::bDelete() {
	/*DEBUG*/xASSERT_RET(NULL != _m_hFont, FALSE);

	_m_bRes = ::DeleteObject(_m_hFont);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Private methods                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
