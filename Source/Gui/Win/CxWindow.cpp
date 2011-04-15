/****************************************************************************
* Class name:  CxWindow
* Description: Класс root для всех дочерних окон 
* File name:   CxWindow.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     31.08.2009 16:44:56
* Version:     1.0.0.0 Debug
*
*****************************************************************************/



#include <xLib/Gui/CxWindow.h>

#include <xLib/GUI/CxWindowImpl.h>

//---------------------------------------------------------------------------
CxTraceLog CxWindow::_m_tlLog(FALSE);           
//---------------------------------------------------------------------------


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxWindow
CxWindow::CxWindow() :
	m_fnFont     (),
	m_stStyle    (),
	_m_hWnd      (NULL),
	_m_iID       (0),
	_m_sClassName(),
	_m_hParentWnd(NULL),		
	_m_sText     (),
	_m_iLeft     (CW_USEDEFAULT),
	_m_iTop      (CW_USEDEFAULT),
	_m_iWidth    (0),
	_m_iHeight   (0),
	_m_ulStyle   (0),
	_m_ulStyleEx (0),
	////_m_iMenu (0),
	_m_pwndParent(NULL),
	_m_bIsControl(FALSE),
	_m_bRes      (FALSE)
{
	LOG();
}
//---------------------------------------------------------------------------
//TODO: + ~CxWindow
CxWindow::~CxWindow() {
	LOG();
}
//---------------------------------------------------------------------------
//TODO: + lpProcessMsg
/*virtual*/
LRESULT CxWindow::lpProcessMsg(UINT uiMsg, WPARAM wParam, LPARAM lParam) {	
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), NULL);

	return ::DefWindowProc(_m_hWnd, uiMsg, wParam, lParam);
}
//---------------------------------------------------------------------------
//TODO: + bIsWindow
BOOL CxWindow::bIsWindow() const {
	/*DEBUG*///not need

	return (NULL != _m_hWnd) && (INVALID_HANDLE_VALUE != _m_hWnd) && (FALSE != ::IsWindow(_m_hWnd));
}
//---------------------------------------------------------------------------
//TODO: + hGetHandle
HWND CxWindow::hGetHandle() const { 
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), NULL);

	return _m_hWnd; 
}
//---------------------------------------------------------------------------
//TODO: + hSetHandle
BOOL CxWindow::bSetHandle(HWND hWnd) {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);

	_m_hWnd = hWnd;

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + iGetID
INT CxWindow::iGetID() const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), 0);
	/*DEBUG*/xASSERT_RET(0     <  _m_iID,      0);

	return _m_iID;
}
//---------------------------------------------------------------------------
//TODO: + bSetID
BOOL CxWindow::bSetID(INT iID) {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);
	/*DEBUG*/xASSERT_RET(0     <  iID,         FALSE);

	liSetWindowLong(GWL_ID, iID);
	
	_m_iID = iID;

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + sGetClassName
tString CxWindow::sGetClassName() const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), tString());

	return _m_sClassName;
}
//---------------------------------------------------------------------------
//TODO: + bSetClassName 
BOOL CxWindow::bSetClassName(const tString &csClassName) {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(),         FALSE);
	/*DEBUG*/xASSERT_RET(FALSE != csClassName.empty(), FALSE);

	_m_sClassName = csClassName;

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + sGetText
tString CxWindow::sGetText() const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), tString());

	tString sRes;

	const INT ciTextSize = ::GetWindowTextLength(_m_hWnd);
	if (ciTextSize > 0) {
		sRes.resize(ciTextSize + 1);

		::GetWindowText(_m_hWnd, &sRes[0], ciTextSize + 1);
		/*DEBUG*/

		sRes.resize(ciTextSize);
	}
	/*DEBUG*/xASSERT_RET(_m_sText == sRes, tString());

	return sRes;
}
//---------------------------------------------------------------------------
//TODO: + bSetText
BOOL CxWindow::bSetText(const tString &csText) {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);
	/*DEBUG*///csText - n/a

	_m_bRes = ::SetWindowText(_m_hWnd, csText.c_str());
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
	
	_m_sText = csText;

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bCreate
BOOL CxWindow::bCreate(INT iID, HWND hParent, const tString &csClassName, const tString &csText, 
					   INT iLeft, INT iTop, INT iWidth, INT iHeight, ULONG ulStyle, ULONG ulStyleEx, LPVOID lpParam)
{
	/*DEBUG*/xASSERT_RET(FALSE == bIsWindow(),         FALSE);
	/*DEBUG*/xASSERT_RET(0     <  iID,                 FALSE);
	/*DEBUG*/// hParent - n/a
	/*DEBUG*/xASSERT_RET(false == csClassName.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(0     <= iLeft,               FALSE);
	/*DEBUG*/xASSERT_RET(0     <= iTop,                FALSE);
	/*DEBUG*/xASSERT_RET(0     <= iWidth,              FALSE);
	/*DEBUG*/xASSERT_RET(0     <= iHeight,             FALSE);

	HWND hWnd = NULL;

	hWnd = ::CreateWindowEx(_m_ulStyleEx | ulStyleEx, 
							csClassName.c_str(), 
							csText.c_str(), 
							_m_ulStyle | ulStyle, 
							iLeft, iTop, iWidth, iHeight, 
							hParent, 
							(tString::npos != csClassName.find(xCXWINDOW_CONTROL_CLASS)) ? static_cast<HMENU>(NULL) : reinterpret_cast<HMENU>(iID),	/*окно - NULL, контрол - iID*/ 
							CxApplication::hGetInstance(), 
							lpParam);
	/*DEBUG*/xASSERT_RET(NULL != hWnd, FALSE);
	/*DEBUG*/xCHECK_DO(FALSE == _m_bIsControl, xASSERT_RET(::GetDlgCtrlID(hWnd) == 0,   FALSE));	//окно
	/*DEBUG*/xCHECK_DO(TRUE  == _m_bIsControl, xASSERT_RET(::GetDlgCtrlID(hWnd) == iID, FALSE));	//контрол

	//-------------------------------------
	//переопределяем поля класса
	_m_hWnd       = hWnd;
	_m_iID        = iID;
	_m_sClassName = _m_sClassName;
	_m_hParentWnd =	hParent;	
	_m_sText      = csText;
	_m_iLeft      = iLeft;
	_m_iTop       = iTop;
	_m_iWidth     = iWidth; 
	_m_iHeight    = iHeight;
	_m_ulStyle    = _m_ulStyle   | ulStyle;
	_m_ulStyleEx  = _m_ulStyleEx | ulStyleEx;    
	////_m_iMenu  = iMenu;
	
	//-------------------------------------
	//дефолтный шрифт
	_m_bRes = m_fnFont.bCreateDefault();
	xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_bRes = m_fnFont.bSet( hGetHandle() );
	xASSERT_RET(FALSE != _m_bRes, FALSE);
	
	//-------------------------------------
	//стиль
	m_stStyle.bSetOwner(_m_hWnd);   //!!!!!!!!!!!!!!!!!!!!!

	return TRUE; 
}
//---------------------------------------------------------------------------
//TODO: + bCreate
BOOL CxWindow::bCreate(INT iID, CxWindow *pwndParent, const tString &csClassName, const tString &csText, 
					   INT iLeft, INT iTop, INT iWidth, INT iHeight, ULONG ulStyle, ULONG ulStyleEx, LPVOID lpParam)
{
	/*DEBUG*/
	
	HWND hParent = (NULL == pwndParent) ? NULL : pwndParent->hGetHandle();
	
	_m_bRes = CxWindow::bCreate(iID, hParent, csClassName, csText, iLeft, iTop, iWidth, iHeight, ulStyle, ulStyleEx, lpParam);
						 
	xCHECK_RET(NULL == pwndParent, TRUE);

	//-------------------------------------
	//добавление дочернего окна в контеймер
	CxWindowImpl *pParent = reinterpret_cast<CxWindowImpl *>(pwndParent);
	/*DEBUG*/xASSERT_RET(NULL != pParent, FALSE);

	pParent->m_vecpContainer.bAdd(this);
	
	//-------------------------------------
	//переопределяем поля класса
	_m_pwndParent = pwndParent;
							 
	return TRUE; 
}
//---------------------------------------------------------------------------
//TODO: + bShow
BOOL CxWindow::bShow(INT iCmdShow) const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);
	/*DEBUG*///not need

	INT  iRes = - 1;

	iRes = ::ShowWindow(_m_hWnd, iCmdShow);
	/*DEBUG*/// n/a

	_m_bRes = bUpdate();
	xCHECK_RET(FALSE == _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bUpdate
BOOL CxWindow::bUpdate() const  {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);

	_m_bRes = ::UpdateWindow(_m_hWnd);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO + bMove
BOOL CxWindow::bMove(INT iLeft, INT iTop, INT iWidth, INT iHeight) {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);

	_m_bRes = ::MoveWindow(_m_hWnd, iLeft , iTop , iWidth , iHeight, TRUE);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	//-------------------------------------
	//переопределяем поля класса
	_m_iLeft      = iLeft;
	_m_iTop       = iTop;
	_m_iWidth     = iWidth; 
	_m_iHeight    = iHeight;

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO + bMoveCenter
BOOL CxWindow::bMoveCenter(HWND hParentWnd) {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);

	RECT rcDlg     = {0};
	RECT rcWnd     = {0};
	RECT rcDesktop = {0};
	INT  iLeft     = 0;
	INT  iTop      = 0;
	INT  iWidth    = 0;
	INT  iHeight   = 0;

	::GetWindowRect(_m_hWnd,    &rcDlg);
	::GetWindowRect(hParentWnd, &rcWnd);

	iWidth  = rcDlg.right  - rcDlg.left;
	iHeight = rcDlg.bottom - rcDlg.top;

	_m_bRes = ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDesktop, 0);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	iLeft = rcWnd.left + ((rcWnd.right - rcWnd.left - iWidth) / 2);

	if (iLeft < 0) {
	    iLeft = 0;
	} else {
		if (iLeft + iWidth > (rcDesktop.right - rcDesktop.left)) {
			iLeft = rcDesktop.right - rcDesktop.left - iWidth;
		}
	}

	iTop = rcWnd.top + ((rcWnd.bottom - rcWnd.top - iHeight) / 2);

	if (iTop < 0) {
		iTop = 0;
	} else {
		if (iTop + iHeight > (rcDesktop.bottom - rcDesktop.top)) {
			iTop = rcDesktop.bottom - rcDesktop.top - iHeight;
		}
	}

	_m_bRes = bSetPos(iLeft, iTop, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
	/*DEBUG*/xCHECK_RET(FALSE == _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bSetPos
BOOL CxWindow::bSetPos(INT iLeft, INT iTop, INT iWidth, INT iHeight, UINT uiFlags) {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);

	_m_bRes = ::SetWindowPos(_m_hWnd, NULL, iLeft, iTop, iWidth, iHeight, uiFlags);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;	
}
//---------------------------------------------------------------------------
//TODO: + bEnable
BOOL CxWindow::bEnable(BOOL bFlag) const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);

	_m_bRes = ::EnableWindow(_m_hWnd, bFlag);
	/*DEBUG*/// n/a

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bSetActive
BOOL CxWindow::bSetActive() const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);

	HWND hWnd = ::SetActiveWindow(_m_hWnd);
	/*DEBUG*/xASSERT_RET(NULL != hWnd, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bSetRedraw
BOOL CxWindow::bSetRedraw(BOOL bFlag) const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);

	SetWindowRedraw(_m_hWnd, bFlag);
	/*DEBUG*/// n/a

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bInvalidateRect ()
BOOL CxWindow::bInvalidateRect(const RECT *prcRect, BOOL bErase) const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);

	_m_bRes = ::InvalidateRect(_m_hWnd, prcRect, bErase);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bDestroy
BOOL CxWindow::bDestroy() const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);

	_m_bRes = ::DestroyWindow(_m_hWnd);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bClose
BOOL CxWindow::bClose() {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);

	return bPostMessage(WM_CLOSE, NULL, NULL);
}
//---------------------------------------------------------------------------


/****************************************************************************
*	посылка сообщений
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - pSendMessage
LRESULT CxWindow::pSendMessage(UINT uiMsg, WPARAM wParam, LPARAM lParam) const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), NULL);

	LRESULT lpRes = ::SendMessage(_m_hWnd, uiMsg, wParam, lParam);
	/*DEBUG*///not need

	return lpRes;
}
//---------------------------------------------------------------------------
//TODO: + bPostMessage
BOOL CxWindow::bPostMessage(UINT uiMsg, WPARAM wParam, LPARAM lParam) const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);

	_m_bRes = ::PostMessage(_m_hWnd, uiMsg, wParam, lParam);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	Остальные
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + liGetWindowLong
LONG CxWindow::liGetWindowLong(INT iIndex) {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), 0);

	LONG liRes = ::GetWindowLong(_m_hWnd, iIndex);
	/*DEBUG*/xASSERT_RET(0 != liRes, 0);

	return liRes;
}
//---------------------------------------------------------------------------
//TODO: + liSetWindowLong
LONG CxWindow::liSetWindowLong(INT iIndex, LONG liNewLong) {
	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), 0);

	LONG liRes = ::SetWindowLong(_m_hWnd, iIndex, liNewLong);
	/*DEBUG*/xASSERT_RET(0 != liRes, 0);

	return liRes; 
}
//---------------------------------------------------------------------------







/****************************************************************************
*	protected
*
*****************************************************************************/

/*
LRESULT CALLBACK Window::MsgRouter(HWND hwnd, UINT message,	WPARAM wparam, LPARAM lparam) {
	Window *wnd = 0;

	if (WM_NCCREATE == message)  {
		//retrieve Window instance from window creation data and associate
		wnd = reinterpret_cast<Window *>((LPCREATESTRUCT)lparam)->lpCreateParams;
		::SetWindowLong(hwnd, GWL_USERDATA, reinterpret_cast<long>(wnd));

		//save window handle
		wnd->SetHWND(hwnd);
	} else {
		//retrieve associated Window instance
		wnd = reinterpret_cast<Window *>(::GetWindowLong(hwnd, GWL_USERDATA));
	}

	//call the windows message handler
	wnd->WndProc(message, wparam, lparam);
}
*/
//---------------------------------------------------------------------------
//TODO: + _s_pWndProc
/*static*/
LRESULT CxWindow::_s_pWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) {
	/*DEBUG*/xASSERT_RET((NULL != hWnd) && (INVALID_HANDLE_VALUE != hWnd) && (FALSE != ::IsWindow(hWnd)), NULL);
	/*DEBUG*/xASSERT_RET(0     != uiMsg, NULL);
	/*DEBUG*///wParam - n/a
	/*DEBUG*///lParam - n/a

	BOOL      bRes     = FALSE;
	CxWindow *pwndThis = NULL;

	switch (uiMsg) {
		////case WM_INITDIALOG:
		////	{
		////		::SetWindowLong(hWnd, GWL_USERDATA, (LONG)lParam);
		////		pWnd = (CxWindow *)lParam;										//получим указатель на класс
		////		/*DEBUG*/xASSERT(NULL != pWnd);
		////		pWnd->_m_hWnd = hWnd;
		////	}
		////	break;

		case WM_NCCREATE:
			{
				LONG liNewLong = 0;

				liNewLong = reinterpret_cast<LONG>  ( ( reinterpret_cast<LPCREATESTRUCT>(lParam) )->lpCreateParams ); 
				/*DEBUG*/xASSERT_RET(0 != liNewLong, NULL);
				
				::SetWindowLong(hWnd, GWL_USERDATA, liNewLong);
				/*DEBUG*///xASSERT(0 != liRes);

				//retrieve Window instance from window creation data and associate
				pwndThis  = static_cast<CxWindow *>( ( reinterpret_cast<LPCREATESTRUCT>(lParam) )->lpCreateParams );
				/*DEBUG*/xASSERT_RET(NULL != pwndThis, NULL);

				//--bRes = pwndThis->bSetHandle(hWnd);
				/*DEBUG*///--xASSERT_RET(FALSE != bRes, NULL);
				/*DEBUG*/xASSERT_RET((NULL != hWnd) && (INVALID_HANDLE_VALUE != hWnd) && (FALSE != ::IsWindow(hWnd)), NULL);
				pwndThis->_m_hWnd = hWnd;
			}
			break;

		default:
			{
				//retrieve associated Window instance
				pwndThis = reinterpret_cast<CxWindow *>( ::GetWindowLong(hWnd, GWL_USERDATA) ); 
				/*DEBUG*/// n/a
			}
			break;
	}

	if (NULL != pwndThis) {
		return pwndThis->lpProcessMsg(uiMsg, wParam, lParam);
	}

	return NULL;
	//return ::DefWindowProc(_m_hWnd, uiMsg, wParam, lParam);
}
//---------------------------------------------------------------------------
//TODO: + _bInitCommonControls
/*static*/
BOOL CxWindow::_bInitCommonControls(ULONG ulFlags) {
	/*DEBUG*/

	INITCOMMONCONTROLSEX iccx = {0};
	iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccx.dwICC  = ulFlags;

	BOOL bRes = FALSE;

	bRes = ::InitCommonControlsEx(&iccx);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + _bRegisterClassEx
/*static*/
BOOL CxWindow::_bRegisterClass(const WNDCLASSEX *cpwcWndClassEx) {		
	/*DEBUG*/xASSERT_RET(NULL != cpwcWndClassEx, FALSE);

	BOOL bRes = FALSE;

	bRes = ::RegisterClassEx(cpwcWndClassEx);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + _bRegisterClassEx
/*static*/
BOOL CxWindow::_bUnregisterClass(const tString &csClassName) {		
	/*DEBUG*///xASSERT_RET(false != csClassName.empty(), FALSE);

	BOOL bRes = FALSE;

	bRes = ::UnregisterClass(csClassName.c_str(), CxApplication::hGetInstance());
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------