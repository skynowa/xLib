/**********************************************************************
*	Класс CXTab (CXTab.h)
*
***********************************************************************/


#ifndef CXTabH
#define CXTabH       
//---------------------------------------------------------------------------
#include <windows.h>
#include "CXSubclassWnd.h"
//---------------------------------------------------------------------------
class CXTab : public CXSubclassWnd {
	public:
	                CXTab       ();
		            //~CXTab    ();
		BOOL        Create      (HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles);
		VOID        vInsertTab  (LPSTR lpCaption, INT iPos, INT iImage);
		VOID        vAddDlg     (HWND hPageDlg, INT iPos);
		BOOL        bShowTab    (INT iPos, BOOL bFlag);
		LRESULT     iGetCurrSel ();
		LRESULT     GetImageList();
		HIMAGELIST  SetImageList(HIMAGELIST lImageList);
};
//---------------------------------------------------------------------------
#endif