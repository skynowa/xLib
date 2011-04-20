/****************************************************************************
*	CXCheckBox
*
*****************************************************************************/


#ifndef CXRadioButton_H
#define CXRadioButton_H
//---------------------------------------------------------------------------
#include "CXSubclassWnd.h"
//---------------------------------------------------------------------------
class CXRadioButton: public CXSubclassWnd {
	public:
			 CXRadioButton();
		BOOL Create       (HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles);
		BOOL IsChecked    ();
		VOID Check        (BOOL bChecked);
};
//---------------------------------------------------------------------------
#endif