/****************************************************************************
*	CXEdit
*
*****************************************************************************/


#ifndef CXRichEdit_H
#define CXRichEdit_H
//---------------------------------------------------------------------------
#include "CXSubclassWnd.h"
#include <richedit.h>
//---------------------------------------------------------------------------
class CXRichEdit: public CXSubclassWnd {
	public:
		         CXRichEdit              ();
		        ~CXRichEdit              ();
		BOOL     Create                  (HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles);
		
		BOOL     CanUndo                 () const;
		INT      GetLineCount            () const;
		BOOL     GetModify               () const;
		VOID     SetModify               (BOOL bModified = TRUE);
		VOID     GetRect                 (LPRECT lpRect) const;
		POINT    GetCharPos              (LONG lChar) const;
		UINT     SetOptions              (WORD wOp, DWORD dwFlags);
		INT      GetLine                 (INT nIndex, LPSTR lpszBuffer) const;
		INT      GetLine                 (INT nIndex, LPSTR lpszBuffer, INT nMaxLength) const;
		BOOL     CanPaste                (UINT nFormat = 0) const;
		VOID     GetSel                  (LONG &nStartChar, LONG &nEndChar) const;
		VOID     GetSel                  (CHARRANGE &cr) const;
		VOID     LimitText               (LONG nChars = 0);
		LONG     LineFromChar            (LONG nIndex) const;
		INT      SetSel                  (LONG nStartChar, LONG nEndChar);
		INT      SetSel                  (CHARRANGE &cr);
		DWORD    GetDefaultCharFormat    (CHARFORMAT &cf) const;
		DWORD    GetSelectionCharFormat  (CHARFORMAT &cf) const;
		LONG     GetEventMask            () const;
		LONG     GetLimitText            () const;
		DWORD    GetParaFormat           (PARAFORMAT &pf) const;
		LONG     GetSelText              (LPSTR lpBuf) const;
		WORD     GetSelectionType        () const;
		COLORREF SetBackgroundColor      (BOOL bSysColor, COLORREF cr);
		BOOL     SetDefaultCharFormat    (CHARFORMAT &cf);
		BOOL     SetSelectionCharFormat  (CHARFORMAT &cf);
		BOOL     SetWordCharFormat       (CHARFORMAT &cf);
		DWORD    SetEventMask            (DWORD dwEventMask);
		BOOL     SetParaFormat           (PARAFORMAT &pf);
		BOOL     SetTargetDevice         (HDC hDC, LONG lLineWidth);
		LONG     GetTextLength           () const;
		BOOL     SetReadOnly             (BOOL bReadOnly = TRUE);
		INT      GetFirstVisibleLine     () const;
		VOID     EmptyUndoBuffer         ();
		INT      LineIndex               (INT nLine =  - 1) const;
		INT      LineLength              (INT nLine =  - 1) const;
		BOOL     LineScroll              (INT nLines, INT nChars = 0);
		VOID     ReplaceSel              (LPCTSTR lpszNewText, BOOL bCanUndo = FALSE);
		VOID     SetRect                 (LPCRECT lpRect);
		BOOL     DisplayBand             (LPRECT pDisplayRect);
		LONG     FindText                (DWORD dwFlags, FINDTEXTEX *pFindText) const;
		LONG     FormatRange             (FORMATRANGE *pfr, BOOL bDisplay = TRUE);
		VOID     HideSelection           (BOOL bHide, BOOL bPerm);
		VOID     PasteSpecial            (UINT nClipFormat, DWORD dvAspect = 0, HMETAFILE hMF = 0);
		VOID     RequestResize           ();
		LONG     StreamIn                (INT nFormat, EDITSTREAM &es);
		LONG     StreamOut               (INT nFormat, EDITSTREAM &es);
		VOID     ScrollCaret             ();
		INT      InsertText              (LONG nInsertAfterChar, LPCTSTR lpstrText, BOOL bCanUndo = FALSE);
		INT      AppendText              (LPCTSTR lpstrText, BOOL bCanUndo = FALSE);
		BOOL     Undo                    ();
		VOID     Clear                   ();
		VOID     Copy                    ();
		VOID     Cut                     ();
		VOID     Paste                   ();
	
	private:
		HMODULE  _m_hmRichEdtDll;
};
//---------------------------------------------------------------------------
#endif