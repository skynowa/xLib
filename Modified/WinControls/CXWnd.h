/****************************************************************************
*	CXWnd
*
*****************************************************************************/


#ifndef CXWnd_H
#define CXWnd_H
//---------------------------------------------------------------------------
#include <windows.h>
#include <commctrl.h>
#include <string>
//---------------------------------------------------------------------------
class CXWnd {
	public:
		                        CXWnd               ();
								//virtual ~WinRoot();
		INT                     iGetID              ();
		BOOL                    bSetText            (const std::string &csText);
		std::string             sGetText            ();
		INT                     GetWidth            ();
		INT                     GetHeight           ();
		INT                     GetLeft             ();
		INT                     GetTop              ();
		BOOL                    bSetSize            (INT iWidth, INT iHeight);
		BOOL                    bSetPos             (INT iLeft,  INT iTop);
		BOOL                    Align               (HWND hParent, HWND hChild);
		BOOL                    SetRedraw           (BOOL bRedraw);
		RECT                    GetRect             ();
		BOOL                    SetRect             (RECT rectRect);
		HWND                    GetHandle           ();
		HFONT                   GetFont             ();
		BOOL                    SetFont             (HFONT hFont);

		BOOL                    SetDefaultFont      ();
		LOGFONT                 GetLogicalFont      ();
		HWND                    SetFocus            ();
		HMENU                   GetMenu             ();
		BOOL                    SetMenu             (HMENU hValue);

		BOOL                    bDestroy            ();
		BOOL                    Close               ();
		BOOL                    Enable              (BOOL bEnabled);
		BOOL                    Invalidate          (BOOL bErase);
		BOOL                    Invalidate          (LPRECT prectRect, BOOL bErase);
		BOOL                    Validate            ();
		BOOL                    Validate            (LPRECT prectRect);
		VOID                    SetCursor           (HCURSOR hCursor);
		BOOL                    bShow               (INT iCmdShow);
		BOOL                    bUpdate             ();
		BOOL                    bMove               (int X, int Y, int nWidth, int nHeight, BOOL bRepaint);
		BOOL                    bSetWindowPos             (HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uiFlags);
		BOOL                    IsVisible           ();
	    BOOL                    bIsWindow           ();
static	BOOL                    bIsDialog           (HWND hWnd);
		LRESULT                 SendMessage         (UINT uiMsg, WPARAM wParam, LPARAM lParam);
		LRESULT                 PostMessage         (UINT uiMsg, WPARAM wParam, LPARAM lParam);

static  LONG_PTR                pliSetLongPtr       (HWND hWnd, INT iIndex, LONG_PTR pliNewLong);
static  LONG_PTR                pliGetLongPtr       (HWND hWnd, INT iIndex);
static  LONG                    liSetLong           (HWND hWnd, INT iIndex, LONG liNewLong);
static  LONG                    liGetLong           (HWND hWnd, INT iIndex);

		VOID                    (*OnDoubleClick)    ();
		VOID                    (*OnClose)          ();
		VOID                    (*OnDestroy)        ();
		VOID                    (*OnTimer)          (WPARAM wParam, LPARAM lParam);
		VOID                    (*OnResize)         (INT NewWidth, INT NewHeight, WPARAM SizeType);
		VOID                    (*OnResizing)       (WPARAM Edge, LPRECT DragRect);
		VOID                    (*OnContextMenu)    (HWND hWnd, INT X, INT Y);
		VOID                    (*OnNotify)         (WPARAM wParam, LPARAM lParam);
		VOID                    (*OnCreate)         (WPARAM wParam, LPARAM lParam);
		VOID                    (*OnCommand)        (WPARAM wParam, LPARAM lParam);
		VOID                    (*OnChar)           (WPARAM wParam, LPARAM lParam);
		VOID                    (*OnKeyDown)        (WPARAM wParam, LPARAM lParam);
		VOID                    (*OnKeyUp)          (WPARAM wParam, LPARAM lParam);
		VOID                    (*OnDeadChar)       (WPARAM wParam, LPARAM lParam);
		VOID                    (*OnMouseMove)      (WPARAM VKeys, INT x, INT y);
		VOID                    (*OnMouseLeftUp)    (WPARAM VKeys, INT x, INT y);

	protected:
		HWND                    _m_hWnd;
		HMENU                   _m_hMenu;
		std::string             _m_sText;
		std::string             _m_sClassName;
		INT                     _m_iWidth, _m_iHeight, _m_iLeft, _m_iTop;
		HFONT                   _m_DefaultFont;

		BOOL                    bInitCommonControls (ULONG ulFlags);
		static LRESULT CALLBACK BaseWindowProc      (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);	//This static method is called by Windows
		LRESULT                 WindowProc          (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, PBOOL pbProcessed);	//This method is called by StatiCXWndProc
		BOOL                    bOnMessage          (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, PBOOL pbProcessed);	//This method is called by WndProc

	private:
		HFONT                   hfCreateDefaultFont ();
};
//---------------------------------------------------------------------------
#endif


/*HWND GetDlgItem
(
HWND hDlg,	// дескриптор диалогового окна
int nIDDlgItem	// идентификатор элемента управления
);*/

/*
UINT GetDlgItemText
(
HWND hDlg,	// дескриптор диалогового окна
int nIDDlgItem,	// идентификатор элемента управления
LPTSTR lpString,	// адрес буфера для текста
int nMaxCount	// максимальная длина строки
);
*/