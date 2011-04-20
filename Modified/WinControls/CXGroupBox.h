/****************************************************************************
*	CXGroupBox
*
*****************************************************************************/


#ifndef CXGroupBox_H
#define CXGroupBox_H
//---------------------------------------------------------------------------
#include "CXSubclassWnd.h"
//---------------------------------------------------------------------------
class CXGroupBox: public CXSubclassWnd {
	public:
		     CXGroupBox();
		BOOL Create    (HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles);
};
//---------------------------------------------------------------------------
#endif