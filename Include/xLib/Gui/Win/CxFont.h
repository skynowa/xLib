/**
 * \file  CxFont.h
 * \brief font
 */


#ifndef xLib_Gui_CxFontH
#define xLib_Gui_CxFontH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxFont :
    public CxNonCopyable
    /// font
{
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
#endif
//---------------------------------------------------------------------------
#endif    //xLib_Gui_CxFontH
