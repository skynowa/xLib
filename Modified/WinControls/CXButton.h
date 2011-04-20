/****************************************************************************
*	CXButton
*
*****************************************************************************/


#ifndef CXButton_H
#define CXButton_H
//---------------------------------------------------------------------------
#include "CXSubclassWnd.h"
//---------------------------------------------------------------------------
class CXButton: public CXSubclassWnd {
	public:
		     CXButton  ();
		BOOL bCreate   (HWND hParent, HMENU hmnuID, ULONG ulStyles, ULONG ulExStyles);
		BOOL bCreateRes(HWND hParent, INT iResID);
		
		VOID (*OnCommand) (WPARAM wParam, LPARAM lParam);
};
//---------------------------------------------------------------------------
#endif