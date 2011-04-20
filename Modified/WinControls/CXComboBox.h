/****************************************************************************
*	CXComboBox
*
*****************************************************************************/


#ifndef CXComboBox_H
#define CXComboBox_H
//---------------------------------------------------------------------------
#include "CXSubclassWnd.h"
//---------------------------------------------------------------------------
class CXComboBox: public CXSubclassWnd {
	public:
		       CXComboBox    ();
		BOOL   Create        (HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles);
		////void (*OnChange) (WORD ControlId, WORD Message, HWND hWnd);	//?????

		LRESULT AddString    (LPARAM lString);
		LRESULT ResetContent ();
		LRESULT SetCurSel    (WPARAM wIndex);
		BOOL    bLoadFromFile(const std::string &csFilePath, int iItemIndex = - 1);  
};
//---------------------------------------------------------------------------
#endif
