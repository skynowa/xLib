/****************************************************************************
* Class name:  CxComboBox
* Description: работа с выпадающем списком
* File name:   CxComboBox.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     24.07.2009 17:01:13
*
*****************************************************************************/



#include <xLib/Gui/CxComboBox.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxComboBox
CxComboBox::CxComboBox() {
	LOG();
	
	//-------------------------------------
	//переопределяем параметры окна
	_m_sClassName     = xCXCOMBOBOX_CONTROL_CLASS;
	_m_ulStyle        = xCXCOMBOBOX_DEFAULT_WINDOW_STYLE;
	_m_ulStyleEx      = xCXCOMBOBOX_DEFAULT_WINDOW_STYLE_EX;

	_m_iLeft          = 0;
	_m_iTop           = 0;
	_m_iWidth         = xCXCOMBOBOX_DEFAULT_WIDTH;
	_m_iHeight        = xCXCOMBOBOX_DEFAULT_HEIGHT;

	_m_bIsControl     = TRUE;

	//-------------------------------------
	//внутр
}
//---------------------------------------------------------------------------
//DONE: ~CxComboBox
CxComboBox::~CxComboBox() {
	LOG();
}
//---------------------------------------------------------------------------
//DONE: bCreateRes
BOOL CxComboBox::bCreateRes(INT iID, CxWindow *pwndParent) {
	/*DEBUG*/xASSERT_RET(0 < iID,            FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

	_m_bRes = CxWindow::bCreate(iID, pwndParent, _m_sClassName, CxResources::sGetText(iID), 
							    CxResources::iGetLeft  (iID), CxResources::iGetTop     (iID), 
							    CxResources::iGetWidth (iID), CxResources::iGetHeight  (iID), 
							    CxResources::ulGetStyle(iID), CxResources::ulGetStyleEx(iID),
							    this);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public: сообщения
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - iFindStringExact (inds the first string in a combo box list that exactly matches the specified string, except that the search is not case sensitive)
#if (xWINVER >= xWIN32_95)
INT CxComboBox::iFindStringExact(INT iIndexStart, LPCTSTR pcszFind) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);
	/*DEBUG*///iIndexStart
	/*DEBUG*///pcszFind

	INT iRes = CB_ERR;

	iRes = static_cast<INT>( ComboBox_FindStringExact(_m_hWnd, iIndexStart, pcszFind) );
	/*DEBUG*/xASSERT_RET(CB_ERR != iRes, CB_ERR);

	return iRes;
}
#endif //xWIN32_95
//---------------------------------------------------------------------------
//TODO: - bGetCount (Gets the number of items in the list box of a combo box)
#if (xWINVER >= xWIN32_31)
BOOL CxComboBox::bGetCount() {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

	static_cast<BOOL>( ComboBox_GetCount(_m_hWnd) );
	/*DEBUG*/// n/a

	return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bGetCueBannerText (Gets the cue banner text displayed in the edit control of a combo box)
#if (xWINVER >= xWIN32_VISTA)
BOOL CxComboBox::bGetCueBannerText(LPWSTR pwszText, INT iTextSize) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*///pwszText
	/*DEBUG*///iTextSize

	BOOL bRes = FALSE;

	bRes = static_cast<BOOL>( ComboBox_GetCueBannerText(_m_hWnd, pwszText, iTextSize) );
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return bRes;
}
#endif //xWIN32_VISTA
//---------------------------------------------------------------------------
//TODO: - iGetCurSel (Gets the index of the currently selected item in a combo box)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iGetCurSel() {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);

	INT iRes = CB_ERR;

	iRes = static_cast<INT>( ComboBox_GetCurSel(_m_hWnd) );
	/*DEBUG*/xASSERT_RET(CB_ERR != iRes, CB_ERR);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bGetDroppedControlRect  (Retrieves the screen coordinates of a combo box in its dropped-down state)
#if (xWINVER >= xWIN32_31)
BOOL CxComboBox::bGetDroppedControlRect (RECT *prcRect) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*///prcRect

	static_cast<VOID>( ComboBox_GetDroppedControlRect (_m_hWnd, prcRect) );
	/*DEBUG*/// n/a

	return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iGetDroppedState (Ascertains whether the drop list in a combo box control is visible)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iGetDroppedState() {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

	INT iRes = FALSE;

	iRes = static_cast<INT>( ComboBox_GetDroppedState(_m_hWnd) );
	/*DEBUG*/xASSERT_RET(FALSE != iRes, FALSE);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - uiGetExtendedUI (Ascertains whether a combo box is using the default user interface (UI) or the extended UI)
#if (xWINVER >= xWIN32_31)
UINT CxComboBox::uiGetExtendedUI() {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

	UINT uiRes = FALSE;

	uiRes = static_cast<UINT>( ComboBox_GetExtendedUI(_m_hWnd) );
	/*DEBUG*/xASSERT_RET(FALSE != uiRes, FALSE);

	return uiRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - lpGetItemData (Gets the application-defined value associated with the specified list item in a combo box)
#if (xWINVER >= xWIN32_31)
LRESULT CxComboBox::lpGetItemData(INT iIndex) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);
	/*DEBUG*///iIndex

	LRESULT lpRes = CB_ERR;

	lpRes = static_cast<LRESULT>( ComboBox_GetItemData(_m_hWnd, iIndex) );
	/*DEBUG*/xASSERT_RET(CB_ERR != lpRes, CB_ERR);

	return lpRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bGetItemHeight (Retrieves the height of list items in a combo box)
#if (xWINVER >= xWIN32_95)
BOOL CxComboBox::bGetItemHeight() {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

	static_cast<BOOL>( ComboBox_GetItemHeight(_m_hWnd) );
	/*DEBUG*/// n/a

	return TRUE;
}
#endif //xWIN32_95
//---------------------------------------------------------------------------
//TODO: - iGetLBText (Gets a string from a list in a combo box)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iGetLBText(INT iIndex, LPCTSTR pcszText) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);
	/*DEBUG*///iIndex
	/*DEBUG*///pcszText

	INT iRes = CB_ERR;

	iRes = static_cast<INT>( ComboBox_GetLBText(_m_hWnd, iIndex, pcszText) );
	/*DEBUG*/xASSERT_RET(CB_ERR != iRes, CB_ERR);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bGetLBTextLen (Gets the length of a string in the list in a combo box)
#if (xWINVER >= xWIN32_31)
BOOL CxComboBox::bGetLBTextLen(INT iIndex) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*///iIndex

	static_cast<BOOL>( ComboBox_GetLBTextLen(_m_hWnd, iIndex) );
	/*DEBUG*/// n/a

	return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bGetMinVisible (Gets the minimum number of visible items in the drop-down list of a combo box)
#if (xWINVER >= xWIN32_XP)
BOOL CxComboBox::bGetMinVisible() {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

	static_cast<BOOL>( ComboBox_GetMinVisible(_m_hWnd) );
	/*DEBUG*/// n/a

	return TRUE;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - bGetText  (Retrieves the text from a combo box control)
#if (xWINVER >= xWIN32_31)
BOOL CxComboBox::bGetText (LPTSTR pszText, INT iTextSize) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*///pszText
	/*DEBUG*///iTextSize

	static_cast<BOOL>( ComboBox_GetText (_m_hWnd, pszText, iTextSize) );
	/*DEBUG*/// n/a

	return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bGetTextLength (Gets the number of characters in the text of a combo box)
#if (xWINVER >= xWIN32_31)
BOOL CxComboBox::bGetTextLength() {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

	static_cast<BOOL>( ComboBox_GetTextLength(_m_hWnd) );
	/*DEBUG*/// n/a

	return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iInsertItemData (Inserts item data in a list in a combo box at the specified location)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iInsertItemData(INT iIndex, LPARAM lpData) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);
	/*DEBUG*///iIndex
	/*DEBUG*///lpData

	INT iRes = CB_ERR;

	iRes = static_cast<INT>( ComboBox_InsertItemData(_m_hWnd, iIndex, lpData) );
	/*DEBUG*/xASSERT_RET(CB_ERR != iRes, CB_ERR);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iInsertString (Adds a string to a list in a combo box at the specified location)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iInsertString(INT iIndex, LPCSTR pcszText) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);
	/*DEBUG*///iIndex
	/*DEBUG*///pcszText

	INT iRes = CB_ERR;

	iRes = static_cast<INT>( ComboBox_InsertString(_m_hWnd, iIndex, pcszText) );
	/*DEBUG*/xASSERT_RET(CB_ERR != iRes, CB_ERR);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bLimitText (Limits the length of the text the user may type into the edit control of a combo box)
#if (xWINVER >= xWIN32_31)
BOOL CxComboBox::bLimitText(INT iTextSize) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*///iTextSize

	static_cast<BOOL>( ComboBox_LimitText(_m_hWnd, iTextSize) );
	/*DEBUG*/// n/a

	return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iResetContent (Removes all items from the list box and edit control of a combo box)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iResetContent() {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, - 1);

	INT iRes = - 1;

	iRes = static_cast<INT>( ComboBox_ResetContent(_m_hWnd) );
	/*DEBUG*/xASSERT_RET(CB_OKAY == iRes, - 1);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iSelectItemData (Searches a list in a combo box for an item that has the specified item data)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iSelectItemData(INT iIndexStart, LPARAM lpData) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);
	/*DEBUG*///iIndexStart
	/*DEBUG*///lpData

	INT iRes = CB_ERR;

	iRes = static_cast<INT>( ComboBox_SelectItemData(_m_hWnd, iIndexStart, lpData) );
	/*DEBUG*/xASSERT_RET(CB_ERR != iRes, CB_ERR);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iSelectString (Searches a list in a combo box for an item that begins with the characters in a specified string)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iSelectString(INT iIndexStart, LPCTSTR pcszFind) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);
	/*DEBUG*///iIndexStart
	/*DEBUG*///pcszFind

	INT iRes = CB_ERR;

	iRes = static_cast<INT>( ComboBox_SelectString(_m_hWnd, iIndexStart, pcszFind) );
	/*DEBUG*/xASSERT_RET(CB_ERR != iRes, CB_ERR);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetCueBannerText  (Sets the cue banner text that is displayed for the edit control of a combo box)
#if (xWINVER >= xWIN32_VISTA)
BOOL CxComboBox::bSetCueBannerText (LPCWSTR pcwszText) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*///pcwszText

	BOOL bRes = FALSE;

	bRes = static_cast<BOOL>( ComboBox_SetCueBannerText (_m_hWnd, pcwszText) );
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return bRes;
}
#endif //xWIN32_VISTA
//---------------------------------------------------------------------------
//TODO: - iSetCurSel (Sets the currently selected item in a combo box)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iSetCurSel(INT iIndex) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);
	/*DEBUG*///iIndex

	INT iRes = CB_ERR;

	iRes = static_cast<INT>( ComboBox_SetCurSel(_m_hWnd, iIndex) );
	/*DEBUG*/xASSERT_RET(CB_ERR != iRes, CB_ERR);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iSetExtendedUI  (Selects either the default user interface (UI) or the extended UI for a combo box that has the CBS_DROPDOWN or CBS_DROPDOWNLIST style)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iSetExtendedUI (UINT uiFlags) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);
	/*DEBUG*///uiFlags

	INT iRes = CB_ERR;

	iRes = static_cast<INT>( ComboBox_SetExtendedUI (_m_hWnd, uiFlags) );
	/*DEBUG*/xASSERT_RET(CB_ERR != iRes, CB_ERR);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iSetItemData (Sets the application-defined value associated with the specified list item in a combo box)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iSetItemData(INT iIndex, LPARAM lpData) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);
	/*DEBUG*///iIndex
	/*DEBUG*///lpData

	INT iRes = CB_ERR;

	iRes = static_cast<INT>( ComboBox_SetItemData(_m_hWnd, iIndex, lpData) );
	/*DEBUG*/xASSERT_RET(CB_ERR != iRes, CB_ERR);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iSetItemHeight (Sets the height of list items or the selection field in a combo box)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iSetItemHeight(INT iIndex, INT iHeight) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);
	/*DEBUG*///iIndex
	/*DEBUG*///iHeight

	INT iRes = CB_ERR;

	iRes = static_cast<INT>( ComboBox_SetItemHeight(_m_hWnd, iIndex, iHeight) );
	/*DEBUG*/xASSERT_RET(CB_ERR != iRes, CB_ERR);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetMinVisible (Sets the minimum number of visible items in the drop-down list of a combo box)
#if (xWINVER >= xWIN32_XP)
BOOL CxComboBox::bSetMinVisible(INT iNum) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*///iNum

	BOOL bRes = FALSE;

	bRes = static_cast<BOOL>( ComboBox_SetMinVisible(_m_hWnd, iNum) );
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return bRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - iSetText (Sets the text of a combo box)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iSetText(LPTSTR pszText) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*///pszText

	INT iRes = FALSE;

	iRes = static_cast<INT>( ComboBox_SetText(_m_hWnd, pszText) );
	/*DEBUG*/xASSERT_RET(FALSE != iRes, FALSE);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bShowDropdown (Shows or hides the list in a combo box)
#if (xWINVER >= xWIN32_31)
BOOL CxComboBox::bShowDropdown(BOOL bFlag) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*///bFlag

	BOOL bRes = FALSE;

	bRes = static_cast<BOOL>( ComboBox_ShowDropdown(_m_hWnd, bFlag) );
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iAddItemData (Adds item data to the list in a combo box at the specified location)
#if (xWINVER >= xWIN32_95)
INT CxComboBox::iAddItemData(LPARAM lpData) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);
	/*DEBUG*///lpData

	INT iRes = NULL;

	iRes = static_cast<INT>( ComboBox_AddItemData(_m_hWnd, lpData) );
	/*DEBUG*/xASSERT_RET(NULL != iRes, NULL);

	return iRes;
}
#endif //xWIN32_95
//---------------------------------------------------------------------------
//TODO: - iAddString (Adds a string to a list in a combo box)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iAddString(LPCSTR pcszText) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);
	/*DEBUG*///pcszText

	INT iRes = CB_ERR;

	iRes = static_cast<INT>( ComboBox_AddString(_m_hWnd, pcszText) );
	/*DEBUG*/xASSERT_RET(CB_ERR != iRes, CB_ERR);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iDeleteString (Deletes the item at the specified location in a list in a combo box)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iDeleteString(INT iIndex) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);
	/*DEBUG*///iIndex

	INT iRes = CB_ERR;

	iRes = static_cast<INT>( ComboBox_DeleteString(_m_hWnd, iIndex) );
	/*DEBUG*/xASSERT_RET(CB_ERR != iRes, CB_ERR);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iDir (Adds names to the list displayed by a combo box)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iDir(UINT uiAttr, LPCTSTR pcszFileSpec) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);
	/*DEBUG*///uiAttr
	/*DEBUG*///pcszFileSpec

	INT iRes = CB_ERR;

	iRes = static_cast<INT>( ComboBox_Dir(_m_hWnd, uiAttr, pcszFileSpec) );
	/*DEBUG*/xASSERT_RET(CB_ERR != iRes, CB_ERR);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bEnable (Enables or disables a combo box control)
#if (xWINVER >= xWIN32_31)
BOOL CxComboBox::bEnable(BOOL bFlag) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*///bFlag

	static_cast<BOOL>( ComboBox_Enable(_m_hWnd, bFlag) );
	/*DEBUG*/// n/a

	return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iFindItemData (Finds the first item in a combo box list that has the specified item data)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iFindItemData(INT iIndexStart, LPARAM lpData) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);
	/*DEBUG*///iIndexStart
	/*DEBUG*///lpData

	INT iRes = CB_ERR;

	iRes = static_cast<INT>( ComboBox_FindItemData(_m_hWnd, iIndexStart, lpData) );
	/*DEBUG*/xASSERT_RET(CB_ERR != iRes, CB_ERR);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iFindString (Finds the first string in a combo box list that begins with the specified string)
#if (xWINVER >= xWIN32_31)
INT CxComboBox::iFindString(INT iIndexStart, LPCTSTR pcszFind) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, CB_ERR);
	/*DEBUG*///iIndexStart
	/*DEBUG*///pcszFind

	INT iRes = CB_ERR;

	iRes = static_cast<INT>( ComboBox_FindString(_m_hWnd, iIndexStart, pcszFind) );
	/*DEBUG*/xASSERT_RET(CB_ERR != iRes, CB_ERR);

	return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------


//////---------------------------------------------------------------------------
////BOOL CxComboBox::bAddString(const tString &csItem) {
////	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////	BOOL bRes = FALSE;
////
////	bRes = (BOOL)pSendMessage(CB_ADDSTRING, 0, (LPARAM)csItem.c_str());
////	/*DEBUG*///??? xASSERT_RET(FALSE != bRes, FALSE);
////
////	return TRUE;
////}
//////---------------------------------------------------------------------------
////BOOL CxComboBox::bResetContent() {
////	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////	BOOL bRes = FALSE;
////
////	bRes = (BOOL)pSendMessage(CB_RESETCONTENT, 0, 0);
////	/*DEBUG*///??? xASSERT_RET(FALSE != bRes, FALSE);
////
////	return TRUE;
////}
//////---------------------------------------------------------------------------
////BOOL CxComboBox::bSetCurSel(WPARAM wIndex) {
////	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////	BOOL bRes = FALSE;
////
////	bRes = (BOOL)pSendMessage(CB_SETCURSEL, wIndex, 0);
////	/*DEBUG*///??? xASSERT_RET(FALSE != bRes, FALSE);
////	
////	return TRUE;
////}
//////---------------------------------------------------------------------------
////BOOL CxComboBox::bLoadFromFile(const tString &csFilePath, int iItemIndex) {    //overflow!!!
////	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////	/*DEBUG*/////xASSERT_RET(TRUE == bFileExists(csFilePath), FALSE);
////
////	BOOL bRes = FALSE;
////
////	try {
////		bResetContent();      
////
////		//прочитать файл построчно
////		tifstream   ifsStream(csFilePath.c_str(), std::ios::in);
////		const ULONG culLineSize             = MAX_PATH;
////		TCHAR       szLine[culLineSize + 1] = {0};	
////		
////		while ((!ifsStream.eof()) && (!ifsStream.fail())) {
////			ifsStream.getline(szLine, culLineSize);					//overflow!!!
////			if (0 != ::lstrlen(szLine)) {
////				szLine[::lstrlen(szLine)] = _T('\0');		//удаляем "\r\n"	
////			}			
////
////			bAddString(szLine);
////		}
////		ifsStream.close();
////
////		bSetCurSel(iItemIndex);
////
////		bRes = TRUE;
////	} catch (...) {
////		bRes = FALSE;
////	}
////
////	return bRes;
////}
//////---------------------------------------------------------------------------