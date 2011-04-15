/****************************************************************************
*	uTest_CxProgressBar.cpp
*
*****************************************************************************/


#include "CWndMain.h"

//---------------------------------------------------------------------------
//TODO: - bTest_CxProgressBar ()
BOOL CWndMain::bTest_CxProgressBar(CxProgressBar &xObj, INT iID, CxWindow *pwndParent) {
	/*DEBUG*/// cpbPB - n/a
	/*DEBUG*/xASSERT_RET(0    < iID,         FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

	//CxProgressBar::bCreateRes
	{
		_m_bRes = xObj.bCreateRes(iID, pwndParent);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxProgressBar::bSetViewStyle
	{
		//Syntax:	BOOL bSetViewStyle(EViewStyle vsViewStyle);	

		_m_bRes = xObj.bSetViewStyle(CxProgressBar::vsVertical);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		_m_bRes = xObj.bSetViewStyle(CxProgressBar::vsDefault);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		_m_bRes = xObj.bSetViewStyle(CxProgressBar::vsSmooth);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxProgressBar::uiGetPos
	{
		#if (xWINVER >= xWIN32_2K)
		//Syntax:	UINT uiGetPos();
		_m_uiRes = xObj.uiGetPos();
		/*DEBUG*/xASSERT(0 == _m_uiRes);
		#endif //xWIN32_2K
	}
	
	//CxProgressBar::bSetPos
	{
		#if (xWINVER >= xWIN32_2K)
		//Syntax:	BOOL bSetPos(UINT uiPos);
		_m_bRes = xObj.bSetPos(60);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		_m_uiRes = xObj.uiGetPos();
		/*DEBUG*/xASSERT(60 == _m_uiRes);
		#endif //xWIN32_2K
	}

	//CxProgressBar::bSetDeltaPos
	{
		#if (xWINVER >= xWIN32_2K) 
		//Syntax:	BOOL bSetDeltaPos(INT iDelta);
		_m_bRes = xObj.bSetDeltaPos(30);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		_m_uiRes = xObj.uiGetPos();
		/*DEBUG*/xASSERT(90 == _m_uiRes);
		#endif //xWIN32_2K
	}
	
	//CxProgressBar::stGetState
	{
		#if (xWINVER >= xWIN32_VISTA)
		//Syntax:	EState stGetState();
		CxProgressBar::EState stRes = xObj.stGetState();
		/*DEBUG*/xASSERT(CxProgressBar::stPaused == stRes);
		#endif //xWIN32_VISTA
	}
	
	//CxProgressBar::bSetState
	{
		#if (xWINVER >= xWIN32_VISTA)
		//Syntax:	BOOL bSetState(EState stState);
		_m_bRes = xObj.bSetState(CxProgressBar::stNormal);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		CxProgressBar::EState stRes = xObj.stGetState();
		/*DEBUG*/xASSERT(CxProgressBar::stNormal == stRes);
		#endif //xWIN32_VISTA
	}
	
	//CxProgressBar::crGetBarColor
	{
		#if (xWINVER >= xWIN32_VISTA)  
		//Syntax:	COLORREF crGetBarColor();
		_m_crRes = xObj.crGetBarColor();
		/*DEBUG*/xASSERT(CLR_DEFAULT == _m_crRes);
		#endif //xWIN32_VISTA
	}
	
	//CxProgressBar::bSetBarColor
	{
		#if (xWINVER >= xWIN32_2K)
		//Syntax:	BOOL bSetBarColor(COLORREF crColor /* = CLR_DEFAULT*/);
		_m_bRes = xObj.bSetBarColor(RGB(0, 0, 255));
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		////_m_crRes = xObj.crGetBarColor();
		/////*DEBUG*/xASSERT(RGB(0, 0, 255) == _m_crRes);
		#endif //xWIN32_2K
	}

	//CxProgressBar::crGetBkColor
	{
		#if (xWINVER >= xWIN32_VISTA)  
		//Syntax:	COLORREF crGetBkColor();
		_m_crRes = xObj.crGetBkColor();
		/*DEBUG*/xASSERT(CLR_DEFAULT == _m_crRes);
		#endif //xWIN32_VISTA
	}

	//CxProgressBar::bSetBkColor
	{
		#if (xWINVER >= xWIN32_2K)
		//Syntax:	BOOL bSetBkColor(COLORREF crColor /*= CLR_DEFAULT*/);
		_m_bRes = xObj.bSetBkColor(RGB(255, 0, 0));
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		////_m_crRes = xObj.crGetBkColor();
		/////*DEBUG*/xASSERT(RGB(255, 0, 0) == _m_crRes);
		#endif //xWIN32_2K
	}

	//CxProgressBar::bGetRange
	{
		#if (xWINVER >= xWIN32_2K)
		//Syntax:	BOOL bGetRange(INT *piMin, INT *piMax);
		INT iMin = - 1;
		INT iMax = - 1;
		
		_m_bRes = xObj.bGetRange(&iMin, &iMax);
		/*DEBUG*/xASSERT(0   == iMin);
		/*DEBUG*/xASSERT(100 == iMax);
		#endif //xWIN32_2K
	}

	//CxProgressBar::bSetRange
	{
		#if (xWINVER >= xWIN32_2K)
		//Syntax:	BOOL bSetRange(USHORT usMin, USHORT usMax);
		_m_bRes = xObj.bSetRange(20, 40);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		INT iMin = - 1;
		INT iMax = - 1;

		_m_bRes = xObj.bGetRange(&iMin, &iMax);
		/*DEBUG*/xASSERT(20   == iMin);
		/*DEBUG*/xASSERT(40 == iMax);
		#endif //xWIN32_2K
	}
	
	//CxProgressBar::bSetRange32
	{
		#if (xWINVER >= xWIN32_2K)
		//Syntax:	BOOL bSetRange32(INT iMin, INT iMax);
		_m_bRes = xObj.bSetRange32(10, 90);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		INT iMin = - 1;
		INT iMax = - 1;

		_m_bRes = xObj.bGetRange(&iMin, &iMax);
		/*DEBUG*/xASSERT(10   == iMin);
		/*DEBUG*/xASSERT(90 == iMax);
		#endif //xWIN32_2K
	}
	
	//CxProgressBar::uiGetStep
	{
		#if (xWINVER >= xWIN32_VISTA)
		//Syntax:	UINT uiGetStep();
		_m_uiRes = xObj.uiGetStep();
		/*DEBUG*/xASSERT(1 == _m_uiRes);
		#endif //xWIN32_VISTA
	}

	//CxProgressBar::bSetStep
	{
		#if (xWINVER >= xWIN32_2K)
		//Syntax:	BOOL bSetStep(UINT uiStep);
		_m_bRes = xObj.bSetStep(12);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		////_m_uiRes = xObj.uiGetStep();
		/////*DEBUG*/xASSERT(12 == _m_uiRes);
		#endif //xWIN32_2K
	}

	//CxProgressBar::bStepIt
	{
		#if (xWINVER >= xWIN32_2K)
		//Syntax:	BOOL bStepIt();
		_m_bRes = xObj.bStepIt();
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_2K
	}

	//CxProgressBar::bSetMarquee
	{
		/*
		Note  
			Comctl32.dll version 6 is not redistributable but it is included in Windows XP or later. 
			To use Comctl32.dll version 6, specify it in a manifest. 
			For more information on manifests, see Enabling Visual Styles.
		*/

		////#if (xWINVER >= xWIN32_S03)
		//////Syntax:	BOOL bSetMarquee(BOOL bIsOn, ULONG ulMilliSeconds);

		////_m_bRes = xObj.bSetViewStyle(CxProgressBar::vsMarquee);
		/////*DEBUG*/xASSERT(FALSE != _m_bRes);

		////_m_bRes = xObj.bSetMarquee(TRUE, 1000);
		/////*DEBUG*/xASSERT(FALSE != _m_bRes);
		////#endif //xWIN32_S03
	}
	
	return TRUE;
}
//---------------------------------------------------------------------------