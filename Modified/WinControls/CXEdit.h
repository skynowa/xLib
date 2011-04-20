/****************************************************************************
*	CXEdit
*
*****************************************************************************/


#ifndef CXEdit_H
#define CXEdit_H
//---------------------------------------------------------------------------
#include "CXSubclassWnd.h"
//---------------------------------------------------------------------------
class CXEdit: public CXSubclassWnd {
	public:
		        CXEdit   ();
		BOOL    Create   (HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles);
		LRESULT LimitText(UINT uiSize);
};
//---------------------------------------------------------------------------
#endif
