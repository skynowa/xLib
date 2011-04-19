/****************************************************************************
* Class name:  CxEdit
* Description: текстовое поле
* File name:   CxEdit.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     23.07.2009 13:11:14
*
*****************************************************************************/


#ifndef XLib_Gui_CxEditH
#define XLib_Gui_CxEditH
//---------------------------------------------------------------------------
#include <xLib/Gui/CxWindow.h>
//---------------------------------------------------------------------------
class CxEdit : public CxWindow {
	public:
		//-------------------------------------
		//константы

		        CxEdit    ();
		       ~CxEdit    ();
                       
		BOOL    bCreateRes(INT iID, CxWindow *pwndParent);

		//-------------------------------------
		//сообщения
		#if (xWINVER >= xWIN32_31)
			BOOL              bCanUndo                ();
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bEmptyUndoBuffer        ();
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bEnable                 (BOOL bFlag);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bFormatLines            (BOOL bIsAddEOL);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_XP)
			BOOL              bGetCueBannerText       (LPCWSTR pcwczText, LONG liTextSize);
		#endif //xWIN32_XP
		#if (xWINVER >= xWIN32_31)
			INT               iGetFirstVisibleLine    ();
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			HLOCAL            hGetHandle              ();
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			INT               iGetLine                (INT iLine, LPTSTR pszText, INT iTextSize);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			INT               iGetLineCount           ();
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bGetModify              ();
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bGetPasswordChar        ();
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bGetRect                (RECT *prcRect);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			ULONG             ulGetSel                ();
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			INT               iGetText                (LPTSTR pszText, INT iTextSize);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			INT               iGetTextLength          ();
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			EDITWORDBREAKPROC procGetWordBreakProc    ();
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_XP)
			BOOL              bHideBalloonTip         ();
		#endif //xWIN32_XP
		#if (xWINVER >= xWIN32_31)
			BOOL              bLimitText              (INT iMaxTextSize);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			INT               iLineFromChar           (INT iChar);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			INT               iLineIndex              (INT iLineIndex);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			INT               iLineLength             (INT iLineIndex);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bReplaceSel             (LPCTSTR pcszNewText);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bScroll                 (INT iVert, INT iHorz);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bScrollCaret            ();
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_XP)
			BOOL              bSetCueBannerText       (LPCWSTR pcwszText);
		#endif //xWIN32_XP
		#if (xWINVER >= xWIN32_VISTA)
			BOOL              bSetCueBannerTextFocused(LPCWSTR pcwszText, BOOL bDrawFocused);
		#endif //xWIN32_VISTA
		#if (xWINVER >= xWIN32_31)
			BOOL              bSetHandle              (HLOCAL hHandle);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bSetModify              (BOOL bFlag);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bSetPasswordChar        (UINT uiChar);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bSetReadOnly            (BOOL bFlag);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bSetRect                (RECT *prcRect);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bSetRectNoPaint         (RECT *prcRect);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bSetSel                 (INT iStartPos, INT iEndPos);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bSetTabStops            (INT iTabs, INT *puiTabs);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			INT               iSetText                (LPTSTR pszText);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_31)
			BOOL              bSetWordBreakProc       (EDITWORDBREAKPROC pfnWordBreak);
		#endif //xWIN32_31
		#if (xWINVER >= xWIN32_XP)
			BOOL              bShowBalloonTip         (EDITBALLOONTIP *pEditBalloonTip);
		#endif //xWIN32_XP
		#if (xWINVER >= xWIN32_31)
			BOOL              bUndo                   ();
		#endif //xWIN32_31

		//-------------------------------------
		//события

};
//---------------------------------------------------------------------------
#endif	//XLib_Gui_CxEditH