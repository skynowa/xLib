/****************************************************************************
*	CXComboBox
*
*****************************************************************************/


#include <Xlib/WinControls/CXComboBox.h>
#include <fstream>
////#include <Xlib/CXFsoString.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXComboBox::CXComboBox() {
	_m_sClassName = "COMBOBOX";
	_m_iLeft      = 0;
	_m_iTop		  = 0;
	_m_iWidth     = 130;
	_m_iHeight    = 20 * 20;
}
//---------------------------------------------------------------------------
BOOL CXComboBox::Create(HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles) {
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

	if (NULL == _m_hWnd) {
		return FALSE;
	} 

	SetDefaultFont();
	Subclass();

	return TRUE;
}
//---------------------------------------------------------------------------
LRESULT CXComboBox::AddString(LPARAM lString) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(CB_ADDSTRING, 0, lString);
}
//---------------------------------------------------------------------------
LRESULT CXComboBox::ResetContent() {
    /*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(CB_RESETCONTENT, 0, 0);
}
//---------------------------------------------------------------------------
LRESULT CXComboBox::SetCurSel(WPARAM wIndex) {
    /*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(CB_SETCURSEL, wIndex, 0);
}
//---------------------------------------------------------------------------
BOOL CXComboBox::bLoadFromFile(const std::string &csFilePath, int iItemIndex) {    //overflow!!!
	/*DEBUG*/XASSERT(bIsWindow());
	/*DEBUG*/////XASSERT_RET(TRUE == bFileExists(csFilePath), FALSE);

	BOOL bRes = FALSE;

	try {
		ResetContent();

		//прочитать файл построчно
		std::ifstream ifsStream(csFilePath.c_str(), std::ios::in);
		const ULONG   culLineSize             = MAX_PATH;
		CHAR          szLine[culLineSize + 1] = {0};	
		
		while ((!ifsStream.eof()) && (!ifsStream.fail())) {
			ifsStream.getline(szLine, culLineSize);					//overflow!!!
			if (0 != ::lstrlen(szLine)) {
				szLine[::lstrlen(szLine)] = '\0';		//удаляем "\r\n"	
			}			

			AddString((LPARAM)szLine);
		}
		ifsStream.close();

		SetCurSel(iItemIndex);

		bRes = TRUE;
	} catch (...) {
		bRes = FALSE;
	}

	return bRes;
}
//---------------------------------------------------------------------------