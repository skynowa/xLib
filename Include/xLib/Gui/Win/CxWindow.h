/****************************************************************************
* Class name:  CxWindow
* Description: Класс root для всех дочерних окон 
* File name:   CxWindow.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     31.08.2009 16:44:56
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Gui_CxWindowH
#define xLib_Gui_CxWindowH
//---------------------------------------------------------------------------
#include <xLib/xClosure.h>
#include <xLib/Gui/xCommon.h>
#include <xLib/Gui/xMessageMap.h>
#include <xLib/Gui/CxApplication.h>
#include <xLib/Gui/CxFont.h>
#include <xLib/Gui/CxStyle.h>
//---------------------------------------------------------------------------
class CxWindow : public CxNonCopyable {	
	public:
		CxFont            m_fnFont;			//шрифт
		CxStyle           m_stStyle;

		                  CxWindow           ();	
		virtual          ~CxWindow           () = 0;


		virtual LRESULT   lpProcessMsg       (UINT uiMsg, WPARAM wParam, LPARAM lParam); 

		BOOL              bIsWindow          () const;
		//CxWindow       *pGetParentWnd      () const;
		//BOOL            bSetParentWnd      ();

		//данные
		HWND              hGetHandle         () const;
		BOOL              bSetHandle         (HWND hWnd);
		INT               iGetID             () const;
		BOOL              bSetID             (INT iID);
		tString           sGetClassName      () const;
		BOOL              bSetClassName      (const tString &csClassName);
		//HWND            _m_hParentWnd;			//хэндл родительского окна		
		tString           sGetText           () const;
		BOOL              bSetText           (const tString &csText);
		//INT             _m_iLeft,  _m_iTop;		//координаты окна
		//INT             _m_iWidth, _m_iHeight;	//размеры окна

		//создание
		BOOL              bCreate            (INT iID, HWND hParent, const tString &csClassName, const tString &csText, 
										      INT iLeft, INT iTop, INT iWidth, INT iHeight, ULONG ulStyle, ULONG ulStyleEx, LPVOID lpParam);
		BOOL              bCreate            (INT iID, CxWindow *pwndParent, const tString &csClassName, const tString &csText, 
			                                  INT iLeft, INT iTop, INT iWidth, INT iHeight, ULONG ulStyle, ULONG ulStyleEx, LPVOID lpParam);										      
		BOOL              bCreateRes         (INT iID, HWND hParent);
		//BOOL            bCreateRes         (INT iID, CxWindow *pwndParent);

		//действия
		BOOL              bShow              (INT iCmdShow) const;
		BOOL              bUpdate            () const;
		BOOL              bMove              (INT iLeft, INT iTop, INT iWidth, INT iHeight);
		BOOL              bMoveCenter        (HWND hParentWnd);
		BOOL              bSetPos            (INT iLeft, INT iTop, INT iWidth, INT iHeight, UINT uiFlags);
		BOOL              bEnable            (BOOL bFlag) const;
		BOOL              bSetActive         () const; 
		BOOL              bSetRedraw         (BOOL bFlag) const; 
		BOOL              bInvalidateRect    (const RECT *prcRect, BOOL bErase) const;
		BOOL              bDestroy           () const;
		BOOL              bClose             ();

		//посылка сообщений
		LRESULT           pSendMessage       (UINT uiMsg, WPARAM wParam, LPARAM lParam) const;
		BOOL              bPostMessage       (UINT uiMsg, WPARAM wParam, LPARAM lParam) const;

		//остальное
		LONG              liGetWindowLong    (INT iIndex);
		LONG              liSetWindowLong    (INT iIndex, LONG liNewLong);

		virtual VOID      vOnClick           () {/*iMsgBox(_T(__FUNCTION__);*/}
		virtual VOID      vOnDbClick         () {/*iMsgBox(_T(__FUNCTION__);*/}
		virtual VOID      vOnKillFocus       () {/*iMsgBox(_T(__FUNCTION__);*/}
		virtual VOID      vOnSetFocus        () {/*iMsgBox(_T(__FUNCTION__);*/}

	protected:
		HWND              _m_hWnd;				//хэндл окна
		INT               _m_iID;				//идентификатор контрола    /*SHORT*/
		tString           _m_sClassName;		//класс окна, контрола
		HWND              _m_hParentWnd;		//хэндл родительского окна		
		tString           _m_sText;				//текст окна
		INT               _m_iLeft,  _m_iTop;	//координаты окна
		INT               _m_iWidth, _m_iHeight;//размеры окна
		ULONG             _m_ulStyle;			//стиль окна
		ULONG             _m_ulStyleEx;			//расширенный стиль окна
		////INT           _m_iMenu;				//меню

		CxWindow         *_m_pwndParent; 

		
		BOOL              _m_bIsControl;		//является ли окно контролом
		mutable BOOL      _m_bRes;
		static CxTraceLog _m_tlLog;				//лог
 
		static LRESULT    _s_pWndProc         (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);   //Функция окна
		static BOOL       _bInitCommonControls(ULONG ulFlags);  
		static BOOL       _bRegisterClass     (const WNDCLASSEX *cpwcWndClassEx);
		static BOOL       _bUnregisterClass   (const tString &csClassName);
		//Attach, Detach

	private:

};
//---------------------------------------------------------------------------
#endif	//xLib_Gui_CxWindowH



/*
GetDlgCtrlID
*/