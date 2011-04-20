/**********************************************************************
*	Класс CXTimer (CXTimer.h)
*
***********************************************************************/


#ifndef CXTimerH
#define CXTimerH       
//---------------------------------------------------------------------------
#include <windows.h>
#include "CXSubclassWnd.h"
//---------------------------------------------------------------------------
class CXTimer : public CXSubclassWnd {
	public:
	                CXTimer     ();
		            //~CXTimer  ();
		BOOL        Create      (HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles);
};
//---------------------------------------------------------------------------
#endif


/*

SetTimer
KillTimer

*/