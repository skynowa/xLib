/****************************************************************************
*	CXProgressBar
*
*****************************************************************************/


#ifndef CXProgressBar_H
#define CXProgressBar_H
//---------------------------------------------------------------------------
#include "CXSubclassWnd.h"
//---------------------------------------------------------------------------
class CXProgressBar: public CXSubclassWnd {
	public:
		         CXProgressBar();
		BOOL     Create       (HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles);

		INT      SetRange     (INT nMin, INT nMax);
		INT      SetRange32   (INT nMin, INT nMax);
		void     GetRange     (PPBRANGE pPBRange);
		INT      GetRangeLimit(BOOL bLimit);
		INT      GetMaxValue  ();
		INT      GetMinValue  ();
		INT      SetPos       (INT nPos);
		INT      GetPos       ();
		INT      DeltaPos	  (INT nDelta);
		INT      SetStep      (INT nStep);		
		INT      StepIt       ();
		COLORREF SetBarColour (COLORREF clrBar);
		COLORREF SetBkColour  (COLORREF clrBk);

/*
		BOOL SetText(LPCTSTR strMessage);
		BOOL SetSize(INT nSize);

*/
};
//---------------------------------------------------------------------------
#endif