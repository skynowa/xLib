/****************************************************************************
*	CXSubclassWnd
*
*****************************************************************************/


//---------------------------------------------------------------------------
#ifndef CSUBCLASSEDWINDOW_H
#define CSUBCLASSEDWINDOW_H
//---------------------------------------------------------------------------
#include "CXWnd.h"
//---------------------------------------------------------------------------
class CXSubclassWnd: public CXWnd {
	public:
		                        CXSubclassWnd ();
		BOOL                    bCreate       (HWND hParent, HMENU hmnuID, ULONG ulStyles, ULONG ulExStyles);

	protected:
		WNDPROC                 _m_wpOrigWndProc;

		static LRESULT CALLBACK BaseWindowProc(HWND hWnd, UINT uiMessage, WPARAM wParam, LPARAM lParam, PBOOL pbProcessed);
		LRESULT                 WindowProc    (HWND hWnd, UINT uiMessage, WPARAM wParam, LPARAM lParam, PBOOL pbProcessed);
		VOID                    Subclass      ();
};
//---------------------------------------------------------------------------
#endif
