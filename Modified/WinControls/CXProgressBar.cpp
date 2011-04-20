/****************************************************************************
*	CXProgressBar
*
*****************************************************************************/


#include <Xlib/WinControls/CXProgressBar.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXProgressBar::CXProgressBar() {
	_m_sClassName = PROGRESS_CLASS;	////"msctls_progress32";
	_m_iLeft      = 0;
	_m_iTop       = 0;
	_m_iWidth     = 50;
	_m_iHeight    = 50;
}
//---------------------------------------------------------------------------
BOOL CXProgressBar::Create(HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles) {
	if (FALSE == bInitCommonControls(ICC_PROGRESS_CLASS)) {
		return FALSE;
	}

	_m_hWnd = ::CreateWindowEx(
				dwExStyles, 
				_m_sClassName.c_str(),
				_m_sText.c_str(), 
				WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | dwStyles, 
				_m_iLeft, 
				_m_iTop, 
				_m_iWidth, 
				_m_iHeight, 
				hParent, 
				(HMENU)hmnuID,	 
				(HINSTANCE)::GetWindowLong(hParent, GWL_HINSTANCE), 
				this);

	if (_m_hWnd == NULL) {
		return FALSE;
	} 

	SetDefaultFont();
	Subclass();

	return TRUE;
}
//---------------------------------------------------------------------------
INT CXProgressBar::SetRange(INT nMin, INT nMax) {	 //диапазон изменения значений и начальное значение (в пределах от 0 до 65535).
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(PBM_SETRANGE, (WPARAM)0, (LPARAM)MAKELPARAM(nMin, nMax));
}
//---------------------------------------------------------------------------
INT CXProgressBar::SetRange32(INT nMin, INT nMax) {	 
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(PBM_SETRANGE32, (WPARAM)nMin, (LPARAM)nMax);
}
//---------------------------------------------------------------------------
void CXProgressBar::GetRange(PPBRANGE pPBRange) {
	/*DEBUG*/XASSERT(bIsWindow());

	SendMessage(PBM_GETRANGE, (WPARAM)TRUE, (LPARAM)pPBRange);
}
//---------------------------------------------------------------------------
INT CXProgressBar::GetRangeLimit(BOOL bLimit) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(PBM_GETRANGE, (WPARAM)bLimit, (LPARAM)NULL);
}
//---------------------------------------------------------------------------
INT CXProgressBar::GetMaxValue() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(PBM_GETRANGE, (WPARAM)0, (LPARAM)0);
}
//---------------------------------------------------------------------------
INT CXProgressBar::GetMinValue() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(PBM_GETRANGE, (WPARAM)1, (LPARAM)0);
}
//---------------------------------------------------------------------------
INT CXProgressBar::SetPos(INT nPos) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(PBM_SETPOS, nPos, 0);
}
//---------------------------------------------------------------------------
INT CXProgressBar::GetPos() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(PBM_GETPOS, (WPARAM)0, (LPARAM)0);
}
//---------------------------------------------------------------------------
INT CXProgressBar::DeltaPos(INT nDelta) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(PBM_DELTAPOS, nDelta, 0);
}
//---------------------------------------------------------------------------
INT CXProgressBar::SetStep(INT nStep) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(PBM_SETSTEP, (WPARAM)nStep, (LPARAM)0);
}
//---------------------------------------------------------------------------
INT CXProgressBar::StepIt() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(PBM_STEPIT, (WPARAM)0, (LPARAM)0);
}
//---------------------------------------------------------------------------
COLORREF CXProgressBar::SetBarColour(COLORREF clrBar) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(PBM_SETBARCOLOR , (WPARAM)0, (LPARAM)(COLORREF)clrBar);
}
//---------------------------------------------------------------------------
COLORREF CXProgressBar::SetBkColour(COLORREF clrBk) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(PBM_SETBKCOLOR, (WPARAM)0, (LPARAM)(COLORREF)clrBk);
}
//---------------------------------------------------------------------------