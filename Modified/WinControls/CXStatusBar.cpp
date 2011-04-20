/****************************************************************************
*	CXStatusBar
*
*****************************************************************************/


#include <Xlib/WinControls/CXStatusBar.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXStatusBar::CXStatusBar() {
	_m_sClassName  = STATUSCLASSNAME;
	m_iDefaultSize = - 1;
}
//---------------------------------------------------------------------------
BOOL CXStatusBar::Create(HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles) {
	if (FALSE == bInitCommonControls(ICC_BAR_CLASSES)) {
		return FALSE;
	}

	_m_hWnd = ::CreateWindowEx(
						dwExStyles, 
						_m_sClassName.c_str(), 
						NULL, 
						WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | WS_CLIPSIBLINGS | CCS_BOTTOM | dwStyles,
						0, 
						0, 
						0, 
						0, 
						hParent,  
						(HMENU)hmnuID,	
						(HINSTANCE)::GetWindowLong(hParent, GWL_HINSTANCE), 
						NULL); 

	if (NULL == _m_hWnd) {
		return FALSE;
	}

	/*InitCommonControlsO;
	hStatusWindow = CreateStatusWindow(WS_CHILD ¦ WS_VISIBLE,"Menu sample", hWnd, wId);
	if(!hStatusWindow) {
		MessageBox(NULL, "Cannot create status window", "Error", MB_OK);
		retum 0;
	}*/

	SetDefaultFont();		//????
	Subclass();				//????

	return TRUE;
}
//---------------------------------------------------------------------------
void CXStatusBar::SetSimple(BOOL Simple) {
	/*DEBUG*/XASSERT(bIsWindow());

	SendMessage(SB_SIMPLE, (WPARAM)Simple, 0);
}
//---------------------------------------------------------------------------
INT CXStatusBar::Height() {
	RECT rect = GetRect();
	
	return rect.bottom - rect.top;
}
//---------------------------------------------------------------------------
BOOL CXStatusBar::SetMinHeight(INT iHeight) {
	/*DEBUG*/XASSERT(bIsWindow());

	return (BOOL)SendMessage(SB_SETMINHEIGHT, (WPARAM)iHeight, (LPARAM)0);
}
//---------------------------------------------------------------------------
BOOL CXStatusBar::SetIcon(INT nPart, HICON hIcon) {
	/*DEBUG*/XASSERT(bIsWindow());

	return (BOOL)SendMessage(SB_SETICON, (WPARAM)nPart, (LPARAM)hIcon);
}
//---------------------------------------------------------------------------
BOOL CXStatusBar::SetIcon(INT PartIndex, HINSTANCE hInstance, INT IdIcon) {
	HICON hIcon = (HICON)::LoadImage(hInstance, MAKEINTRESOURCE(IdIcon), IMAGE_ICON, 0, 0, LR_SHARED);

	return SetIcon(PartIndex, hIcon);
}
//---------------------------------------------------------------------------
BOOL CXStatusBar::SetText(INT PartIndex, const std::string &csPartText) {
	/*DEBUG*/XASSERT(bIsWindow());

	return (BOOL)SendMessage(SB_SETTEXT, PartIndex, (LPARAM)csPartText.c_str());
}
//---------------------------------------------------------------------------
BOOL CXStatusBar::SetSize(INT PartIndex, INT Size) {
	/*DEBUG*/XASSERT(bIsWindow());

	if (PartIndex >= m_iNumParts) {
		return FALSE;
	}
	m_iPartsWidths[PartIndex] = Size;

	return (BOOL)SendMessage(SB_SETPARTS, (WPARAM)m_iNumParts, (LPARAM)m_iPartsWidths);
}
//---------------------------------------------------------------------------
INT CXStatusBar::AddPart() {
	return AddPart(m_iDefaultSize);
}
//---------------------------------------------------------------------------
INT CXStatusBar::AddPart(const std::string &csPartText) {
	return AddPart(csPartText, m_iDefaultSize);
}
//---------------------------------------------------------------------------
INT CXStatusBar::AddPart(const std::string &csPartText, HICON hIcon) {
	return AddPart(csPartText, hIcon, m_iDefaultSize);
}
//---------------------------------------------------------------------------
INT CXStatusBar::AddPart(const std::string &csPartText, HINSTANCE hInstance, INT IdIcon) {
	HICON hIcon = (HICON)::LoadImage(hInstance, MAKEINTRESOURCE(IdIcon), IMAGE_ICON, 0, 0, LR_SHARED);
	
	return AddPart(csPartText, hIcon);
}
//---------------------------------------------------------------------------
INT CXStatusBar::AddPart(INT Size) {
	/*DEBUG*/XASSERT(bIsWindow());

	m_iPartsWidths[m_iNumParts] = 0;
	for (INT Cnt = 0; Cnt < m_iNumParts; Cnt ++) {
		m_iPartsWidths[m_iNumParts] += m_iPartsWidths[Cnt];
	}
	m_iPartsWidths[m_iNumParts] += Size;
	m_iNumParts ++;
	if (!SendMessage(SB_SETPARTS, (WPARAM)m_iNumParts, (LPARAM)m_iPartsWidths)) {
		return  - 1;
	}
	
	return m_iNumParts - 1;
}
//---------------------------------------------------------------------------
INT CXStatusBar::AddPart(const std::string &csPartText, INT Size) {
	INT Index = - 1;
	Index = AddPart(Size);
	if (Index < 0) {
		return Index;
	}
	SetText(m_iNumParts - 1, csPartText);
	
	return Index;
}
//---------------------------------------------------------------------------
INT CXStatusBar::AddPart(const std::string &csPartText, HICON hIcon, INT Size) {
	INT Index = - 1;
	Index = AddPart(Size);
	if (Index < 0) {
		return Index;
	}
	SetIcon(m_iNumParts - 1, hIcon);
	SetText(m_iNumParts - 1, csPartText);
	
	return Index;
}
//---------------------------------------------------------------------------
INT CXStatusBar::AddPart(const std::string &csPartText, HINSTANCE hInstance, INT IdIcon, INT Size) {
	HICON hIcon = (HICON)::LoadImage(hInstance, MAKEINTRESOURCE(IdIcon), IMAGE_ICON, 0, 0, LR_SHARED);

	return AddPart(csPartText, hIcon, Size);
}
//---------------------------------------------------------------------------
INT CXStatusBar::AddPart(HICON hIcon, INT Size) {
	INT Index = - 1;
	Index = AddPart(Size);
	if (Index < 0) {
		return Index;
	}
	SetIcon(m_iNumParts - 1, hIcon);

	return Index;
}
//---------------------------------------------------------------------------