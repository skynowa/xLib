/****************************************************************************
* Class name:  CxFont
* Description: רנטפע
* File name:   CxFont.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     09.03.2010 10:36:56
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Gui_CxFontH
#define xLib_Gui_CxFontH
//---------------------------------------------------------------------------
#include <xLib/xCommon.h>
//---------------------------------------------------------------------------
class CxFont : public CxNonCopyable {
	public:
		CxFont();
	   ~CxFont();
	   
		BOOL  bCreate       (INT iHeight, INT iWidth, INT iEscapement, INT iOrientation, INT iWeight, ULONG ulItalic, ULONG ulUnderline, ULONG ulStrikeOut, ULONG ulCharSet, ULONG ulOutputPrecision, ULONG ulClipPrecision, ULONG ulQuality, ULONG ulPitchAndFamily, LPCTSTR pcszFace);
		BOOL  bCreateDefault();
		HFONT hGet          (HWND hWnd);
		BOOL  bSet          (HWND hWnd);
		BOOL  bDelete       ();
		
	private:
		BOOL  _m_bRes;
		HFONT _m_hFont;
};
//---------------------------------------------------------------------------
#endif	//xLib_Gui_CxFontH