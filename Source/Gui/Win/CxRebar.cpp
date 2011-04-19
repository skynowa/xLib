/****************************************************************************
* Class name:  CxRebar
* Description: работа с ребаром
* File name:   CxRebar.сзз
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     24.07.2009 11:20:41
*
*****************************************************************************/



#include <xLib/Gui/CxRebar.h>

//---------------------------------------------------------------------------
CxRebar::CxRebar() : 
	CxWindow()
{
	_m_bIsControl     = TRUE;
}
//---------------------------------------------------------------------------
CxRebar::~CxRebar() {

}
//---------------------------------------------------------------------------
HWND CxRebar::Create(HWND hwndOwner, AlignFlags afFlag) {
	REBARINFO     rbi;
	INITCOMMONCONTROLSEX icex;
	HINSTANCE g_hinst=GetModuleHandle(NULL);
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC   = ICC_COOL_CLASSES|ICC_BAR_CLASSES;
	::InitCommonControlsEx(&icex);



	_m_hWnd = ::CreateWindowEx(0,
		REBARCLASSNAME,
		NULL,
		WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|
		WS_CLIPCHILDREN|RBS_VARHEIGHT|
		CCS_NODIVIDER|
		afFlag ,
		0,0,0,50,
		hwndOwner,
		NULL,
		g_hinst,
		NULL);
	if(!_m_hWnd)
		return NULL;
	rbi.cbSize = sizeof(REBARINFO);  
	rbi.fMask  = 0;
	rbi.himl   = (HIMAGELIST)NULL;
	if(!SendMessage(_m_hWnd, RB_SETBARINFO, 0, (LPARAM)&rbi))
		return NULL;
	return (_m_hWnd);
}
//---------------------------------------------------------------------------
VOID CxRebar::InsertBand(HWND hClientWnd,TCHAR* szName) {
	REBARBANDINFO rbBand;
	rbBand.cbSize = sizeof(REBARBANDINFO);  // Required
	rbBand.fMask  =  RBBIM_TEXT | RBBIM_BACKGROUND | 
		RBBIM_STYLE | RBBIM_CHILD  | RBBIM_CHILDSIZE | 
		RBBIM_IMAGE|RBBIM_SIZE;
	rbBand.fStyle =RBBS_BREAK|RBBS_CHILDEDGE | RBBS_FIXEDBMP/*RBBS_CHILDEDGE|
															RBBS_USECHEVRON| RBBS_GRIPPERALWAYS|RBBS_VARIABLEHEIGHT*/;
	rbBand.hbmBack = 0;//LoadBitmap(GetModuleHandle(NULL),MAKEINTRESOURCE(IDB_BITMAP_BG));   
	RECT rect;
	GetClientRect(hClientWnd,&rect);
	//		rbBand.clrBack=RGB(212,208,200);
	//		rbBand.clrFore=0xFF0000;
	rbBand.lpText     = szName;
	rbBand.cch		  = ::lstrlen(szName);
	rbBand.hwndChild  = hClientWnd;
	//		rbBand.cxMinChild = rect.right-rect.left;
	//		rbBand.cyMinChild = rect.bottom-rect.top;
	rbBand.cyMinChild = 100;
	rbBand.cxMinChild = 100;//rect.bottom-rect.top;
	rbBand.cx         = 35;//rect.right-rect.left;
	SendMessage(_m_hWnd, RB_INSERTBAND, (WPARAM)-1, (LPARAM)&rbBand);
}
//---------------------------------------------------------------------------
BOOL CxRebar::DeleteBand(int numBand) {
	return (0!=SendMessage(_m_hWnd,(UINT) RB_DELETEBAND,WPARAM(numBand),0)); 
}
//---------------------------------------------------------------------------
VOID CxRebar::AutoSize()	{
	SendMessage((HWND) _m_hWnd,      
		(UINT) RB_SHOWBAND,    
		(WPARAM) 0,
		(LPARAM) TRUE);  
}
//---------------------------------------------------------------------------