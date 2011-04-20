/****************************************************************************
*	CXEdit
*
*****************************************************************************/


#include <Xlib/WinControls/CXRichEdit.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXRichEdit::CXRichEdit() {
	_m_hmRichEdtDll = ::LoadLibrary("RICHED32.DLL");
	
	_m_sClassName = RICHEDIT_CLASS;
	_m_iLeft      = 0;
	_m_iTop       = 0;
	_m_iWidth     = 100;
	_m_iHeight    = 20;
}
//---------------------------------------------------------------------------
CXRichEdit::~CXRichEdit() {
    ::FreeLibrary(_m_hmRichEdtDll);
}
//---------------------------------------------------------------------------
BOOL CXRichEdit::Create(HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles) {
	_m_hWnd = ::CreateWindowEx(
					dwExStyles, 
					_m_sClassName.c_str(),	
					_m_sText.c_str(),					
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | dwStyles,		
					_m_iLeft,							
					_m_iTop,							
					_m_iWidth,							
					_m_iHeight,							
					hParent,							
					(HMENU)hmnuID,							
					(HINSTANCE)::GetWindowLong(hParent, GWL_HINSTANCE), 
					this);
					
	//m_hRichEdt = ::CreateWindowEx(0x00000000, "RICHEDIT", "", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_WANTRETURN | ES_READONLY, iRichEdtShift, 16, 400, 180, hMainWnd, (HMENU)m_IDC_redtMsg, ::GetModuleHandle(NULL)/*instance*/, NULL); 

	if (NULL == _m_hWnd) {
		return FALSE;
	} 

	SetDefaultFont();
	Subclass();
	
	return TRUE;
}
//---------------------------------------------------------------------------
BOOL CXRichEdit::CanUndo() const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (BOOL)::SendMessage(_m_hWnd, EM_CANUNDO, 0, 0L);
}
//---------------------------------------------------------------------------
INT CXRichEdit::GetLineCount() const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (INT)::SendMessage(_m_hWnd, EM_GETLINECOUNT, 0, 0L);
}
//---------------------------------------------------------------------------
BOOL CXRichEdit::GetModify() const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (BOOL)::SendMessage(_m_hWnd, EM_GETMODIFY, 0, 0L);
}
//---------------------------------------------------------------------------
VOID CXRichEdit::SetModify(BOOL bModified) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	::SendMessage(_m_hWnd, EM_SETMODIFY, bModified, 0L);
}
//---------------------------------------------------------------------------
VOID CXRichEdit::GetRect(LPRECT lpRect) const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	::SendMessage(_m_hWnd, EM_GETRECT, 0, (LPARAM)lpRect);
}
//---------------------------------------------------------------------------
POINT CXRichEdit::GetCharPos(LONG lChar) const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	POINT pt;
	::SendMessage(_m_hWnd, EM_POSFROMCHAR, (WPARAM) &pt, (LPARAM)lChar);
    
	return pt;
}
//---------------------------------------------------------------------------
UINT CXRichEdit::SetOptions(WORD wOp, DWORD dwFlags) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (UINT)::SendMessage(_m_hWnd, EM_SETOPTIONS, (WPARAM)wOp, (LPARAM)dwFlags);
}
//---------------------------------------------------------------------------
// NOTE: first word in lpszBuffer must contain the size of the buffer!
INT CXRichEdit::GetLine(INT nIndex, LPSTR lpszBuffer) const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (INT)::SendMessage(_m_hWnd, EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
}
//---------------------------------------------------------------------------
INT CXRichEdit::GetLine(INT nIndex, LPSTR lpszBuffer, INT nMaxLength) const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	*(LPINT)lpszBuffer = nMaxLength;

	return (INT)::SendMessage(_m_hWnd, EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
}
//---------------------------------------------------------------------------
BOOL CXRichEdit::CanPaste(UINT nFormat) const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (BOOL)::SendMessage(_m_hWnd, EM_CANPASTE, nFormat, 0L);
}
//---------------------------------------------------------------------------
VOID CXRichEdit::GetSel(LONG &nStartChar, LONG &nEndChar) const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	CHARRANGE cr = {0};
	::SendMessage(_m_hWnd, EM_EXGETSEL, 0, (LPARAM) &cr);
	nStartChar = cr.cpMin;
	nEndChar = cr.cpMax;
}
//---------------------------------------------------------------------------
VOID CXRichEdit::GetSel(CHARRANGE &cr) const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	::SendMessage(_m_hWnd, EM_EXGETSEL, 0, (LPARAM) &cr);
}
//---------------------------------------------------------------------------
VOID CXRichEdit::LimitText(LONG nChars) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	::SendMessage(_m_hWnd, EM_EXLIMITTEXT, 0, nChars);
}
//---------------------------------------------------------------------------
LONG CXRichEdit::LineFromChar(LONG nIndex) const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (LONG)::SendMessage(_m_hWnd, EM_EXLINEFROMCHAR, 0, nIndex);
}
//---------------------------------------------------------------------------
INT CXRichEdit::SetSel(LONG nStartChar, LONG nEndChar) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	CHARRANGE cr = {0};
	cr.cpMin = nStartChar;
	cr.cpMax = nEndChar;
    
	return (INT)::SendMessage(_m_hWnd, EM_EXSETSEL, 0, (LPARAM) &cr);
}
//---------------------------------------------------------------------------
INT CXRichEdit::SetSel(CHARRANGE &cr) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
	return (INT)::SendMessage(_m_hWnd, EM_EXSETSEL, 0, (LPARAM) &cr);
}
//---------------------------------------------------------------------------
DWORD CXRichEdit::GetDefaultCharFormat(CHARFORMAT &cf) const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	cf.cbSize = sizeof(CHARFORMAT);
    
	return (DWORD)::SendMessage(_m_hWnd, EM_GETCHARFORMAT, 0, (LPARAM) &cf);
}
//---------------------------------------------------------------------------
DWORD CXRichEdit::GetSelectionCharFormat(CHARFORMAT &cf) const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	cf.cbSize = sizeof(CHARFORMAT);
    
	return (DWORD)::SendMessage(_m_hWnd, EM_GETCHARFORMAT, 1, (LPARAM) &cf);
}
//---------------------------------------------------------------------------
LONG CXRichEdit::GetEventMask() const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (LONG)::SendMessage(_m_hWnd, EM_GETEVENTMASK, 0, 0L);
}
//---------------------------------------------------------------------------
LONG CXRichEdit::GetLimitText() const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (LONG)::SendMessage(_m_hWnd, EM_GETLIMITTEXT, 0, 0L);
}
//---------------------------------------------------------------------------
DWORD CXRichEdit::GetParaFormat(PARAFORMAT &pf) const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	pf.cbSize = sizeof(PARAFORMAT);
    
	return (DWORD)::SendMessage(_m_hWnd, EM_GETPARAFORMAT, 0, (LPARAM) &pf);
}
//---------------------------------------------------------------------------
//richedit EM_GETSELTEXT is ANSI
LONG CXRichEdit::GetSelText(LPSTR lpBuf) const {

	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (LONG)::SendMessage(_m_hWnd, EM_GETSELTEXT, 0, (LPARAM)lpBuf);
}
//---------------------------------------------------------------------------
WORD CXRichEdit::GetSelectionType() const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (WORD)::SendMessage(_m_hWnd, EM_SELECTIONTYPE, 0, 0L);
}
//---------------------------------------------------------------------------
COLORREF CXRichEdit::SetBackgroundColor(BOOL bSysColor, COLORREF cr) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (COLORREF)::SendMessage(_m_hWnd, EM_SETBKGNDCOLOR, bSysColor, cr);
}
//---------------------------------------------------------------------------
BOOL CXRichEdit::SetDefaultCharFormat(CHARFORMAT &cf) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	cf.cbSize = sizeof(CHARFORMAT);
    
	return (BOOL)::SendMessage(_m_hWnd, EM_SETCHARFORMAT, 0, (LPARAM) &cf);
}
//---------------------------------------------------------------------------
BOOL CXRichEdit::SetSelectionCharFormat(CHARFORMAT &cf) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	cf.cbSize = sizeof(CHARFORMAT);
    
	return (BOOL)::SendMessage(_m_hWnd, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM) &cf);
}
//---------------------------------------------------------------------------
BOOL CXRichEdit::SetWordCharFormat(CHARFORMAT &cf) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	cf.cbSize = sizeof(CHARFORMAT);
    
	return (BOOL)::SendMessage(_m_hWnd, EM_SETCHARFORMAT, SCF_SELECTION | SCF_WORD, (LPARAM) &cf);
}
//---------------------------------------------------------------------------
DWORD CXRichEdit::SetEventMask(DWORD dwEventMask) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (DWORD)::SendMessage(_m_hWnd, EM_SETEVENTMASK, 0, dwEventMask);
}
//---------------------------------------------------------------------------
BOOL CXRichEdit::SetParaFormat(PARAFORMAT &pf) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	pf.cbSize = sizeof(PARAFORMAT);
    
	return (BOOL)::SendMessage(_m_hWnd, EM_SETPARAFORMAT, 0, (LPARAM) &pf);
}
//---------------------------------------------------------------------------
BOOL CXRichEdit::SetTargetDevice(HDC hDC, LONG lLineWidth) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (BOOL)::SendMessage(_m_hWnd, EM_SETTARGETDEVICE, (WPARAM)hDC, lLineWidth);
}
//---------------------------------------------------------------------------
LONG CXRichEdit::GetTextLength() const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (LONG)::SendMessage(_m_hWnd, WM_GETTEXTLENGTH, 0, 0L);
}
//---------------------------------------------------------------------------
BOOL CXRichEdit::SetReadOnly(BOOL bReadOnly) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (BOOL)::SendMessage(_m_hWnd, EM_SETREADONLY, bReadOnly, 0L);
}
//---------------------------------------------------------------------------
INT CXRichEdit::GetFirstVisibleLine() const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (INT)::SendMessage(_m_hWnd, EM_GETFIRSTVISIBLELINE, 0, 0L);
}
//---------------------------------------------------------------------------
// Operations
VOID CXRichEdit::EmptyUndoBuffer() {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	::SendMessage(_m_hWnd, EM_EMPTYUNDOBUFFER, 0, 0L);
}
//---------------------------------------------------------------------------
INT CXRichEdit::LineIndex(INT nLine) const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (INT)::SendMessage(_m_hWnd, EM_LINEINDEX, nLine, 0L);
}
//---------------------------------------------------------------------------
INT CXRichEdit::LineLength(INT nLine) const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (INT)::SendMessage(_m_hWnd, EM_LINELENGTH, nLine, 0L);
}
//---------------------------------------------------------------------------
BOOL CXRichEdit::LineScroll(INT nLines, INT nChars) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (BOOL)::SendMessage(_m_hWnd, EM_LINESCROLL, nChars, nLines);
}
//---------------------------------------------------------------------------
VOID CXRichEdit::ReplaceSel(LPCSTR lpszNewText, BOOL bCanUndo) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	::SendMessage(_m_hWnd, EM_REPLACESEL, (WPARAM)bCanUndo, (LPARAM)lpszNewText);
}
//---------------------------------------------------------------------------
VOID CXRichEdit::SetRect(LPCRECT lpRect) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	::SendMessage(_m_hWnd, EM_SETRECT, 0, (LPARAM)lpRect);
}
//---------------------------------------------------------------------------
BOOL CXRichEdit::DisplayBand(LPRECT pDisplayRect) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (BOOL)::SendMessage(_m_hWnd, EM_DISPLAYBAND, 0, (LPARAM)pDisplayRect);
}
//---------------------------------------------------------------------------
LONG CXRichEdit::FindText(DWORD dwFlags, FINDTEXTEX *pFindText) const {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (LONG)::SendMessage(_m_hWnd, EM_FINDTEXTEX, dwFlags, (LPARAM)pFindText);
}
//---------------------------------------------------------------------------
LONG CXRichEdit::FormatRange(FORMATRANGE *pfr, BOOL bDisplay) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (LONG)::SendMessage(_m_hWnd, EM_FORMATRANGE, (WPARAM)bDisplay, (LPARAM)pfr);
}
//---------------------------------------------------------------------------
VOID CXRichEdit::HideSelection(BOOL bHide, BOOL bPerm) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	::SendMessage(_m_hWnd, EM_HIDESELECTION, bHide, bPerm);
}
//---------------------------------------------------------------------------
VOID CXRichEdit::PasteSpecial(UINT nClipFormat, DWORD dvAspect, HMETAFILE hMF) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	REPASTESPECIAL reps = {0};
	reps.dwAspect = dvAspect;
	reps.dwParam = (DWORD)hMF;
	::SendMessage(_m_hWnd, EM_PASTESPECIAL, nClipFormat, (LPARAM) &reps);
}
//---------------------------------------------------------------------------
VOID CXRichEdit::RequestResize() {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	::SendMessage(_m_hWnd, EM_REQUESTRESIZE, 0, 0L);
}
//---------------------------------------------------------------------------
LONG CXRichEdit::StreamIn(INT nFormat, EDITSTREAM &es) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (LONG)::SendMessage(_m_hWnd, EM_STREAMIN, nFormat, (LPARAM) &es);
}
//---------------------------------------------------------------------------
LONG CXRichEdit::StreamOut(INT nFormat, EDITSTREAM &es) {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (LONG)::SendMessage(_m_hWnd, EM_STREAMOUT, nFormat, (LPARAM) &es);
}
//---------------------------------------------------------------------------
// Additional operations
VOID CXRichEdit::ScrollCaret() {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	::SendMessage(_m_hWnd, EM_SCROLLCARET, 0, 0L);
}
//---------------------------------------------------------------------------
INT CXRichEdit::InsertText(LONG nInsertAfterChar, LPCSTR lpstrText, BOOL bCanUndo) {
	INT nRet = SetSel(nInsertAfterChar, nInsertAfterChar);
	ReplaceSel(lpstrText, bCanUndo);
    
	return nRet;
}
//---------------------------------------------------------------------------
INT CXRichEdit::AppendText(LPCSTR lpstrText, BOOL bCanUndo) {
	return InsertText(::GetWindowTextLength(_m_hWnd), lpstrText, bCanUndo);
}
//---------------------------------------------------------------------------
// Clipboard operations
BOOL CXRichEdit::Undo() {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	return (BOOL)::SendMessage(_m_hWnd, EM_UNDO, 0, 0L);
}
//---------------------------------------------------------------------------
VOID CXRichEdit::Clear() {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	::SendMessage(_m_hWnd, WM_CLEAR, 0, 0L);
}
//---------------------------------------------------------------------------
VOID CXRichEdit::Copy() {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	::SendMessage(_m_hWnd, WM_COPY, 0, 0L);
}
//---------------------------------------------------------------------------
VOID CXRichEdit::Cut() {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	::SendMessage(_m_hWnd, WM_CUT, 0, 0L);
}
//---------------------------------------------------------------------------
VOID CXRichEdit::Paste() {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));
    
	::SendMessage(_m_hWnd, WM_PASTE, 0, 0L);
}
//---------------------------------------------------------------------------