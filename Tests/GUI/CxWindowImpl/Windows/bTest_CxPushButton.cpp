/****************************************************************************
*	bTest_CxPushButton.cpp
*
*****************************************************************************/


#include "CWndMain.h"

//---------------------------------------------------------------------------
//TODO: - bTest_CxPushButton ()
BOOL CWndMain::bTest_CxPushButton(CxPushButton &xObj, INT iID, CxWindow *pwndParent) {
	/*DEBUG*/// cpbPB - n/a
	/*DEBUG*/xASSERT_RET(0    < iID,         FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

	//CxProgressBar::
	{
		_m_bRes = xObj.bCreateRes(iID, this);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxPushButton::vsText
	{
		_m_bRes = xObj.bSetViewStyle(CxPushButton::vsText);  
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		_m_bRes = xObj.bSetText(xT("xxxx"));
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxPushButton::vsIcon (icon)
	{
		_m_bRes = xObj.bSetViewStyle(CxPushButton::vsIcon);  
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		HICON hIcon = ::LoadIcon(NULL, IDI_ERROR);
		/*DEBUG*/xASSERT(NULL != hIcon);

		_m_bRes = xObj.bSetImage(CxPushButton::itIcon, hIcon);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxPushButton::vsIcon (cursor)
	{
		_m_bRes = xObj.bSetViewStyle(CxPushButton::vsIcon);  
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		HICON hCursor = ::LoadCursor(NULL, IDC_APPSTARTING);
		/*DEBUG*/xASSERT(NULL != hCursor);

		_m_bRes = xObj.bSetImage(CxPushButton::itIcon, hCursor);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxPushButton::vsBitmap
	{
		_m_bRes = xObj.bSetViewStyle(CxPushButton::vsBitmap);  
		/*DEBUG*/xASSERT(FALSE != _m_bRes); 

		HBITMAP hBitmap = (HBITMAP)::LoadImage(NULL, xT("Bitmap1.bmp"), IMAGE_BITMAP, 48, 48, LR_LOADFROMFILE);	//::LoadBitmap(NULL, MAKEINTRESOURCE(OBM_CHECK));
		/*DEBUG*/xASSERT(NULL != hBitmap);

		_m_bRes = xObj.bSetImage(CxPushButton::itBitmap, hBitmap);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxPushButton::csGetState, CxPushButton::bSetState
	{
		CxPushButton::ECheckState csRes = CxPushButton::csUknown;

		csRes = xObj.csGetState(); 
		/*DEBUG*/xASSERT(CxPushButton::csUnchecked == csRes);

		_m_bRes = xObj.bSetState(CxPushButton::csChecked);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);			//iMsgBox(xT("CxRadioButton::csChecked"));

		csRes = xObj.csGetState(); 
		/*DEBUG*/xASSERT(CxPushButton::csChecked == csRes);

		_m_bRes = xObj.bSetState(CxPushButton::csUnchecked);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);		    //iMsgBox(xT("CxRadioButton::csUnchecked"));

		csRes = xObj.csGetState(); 
		/*DEBUG*/xASSERT(CxPushButton::csUnchecked == csRes);
	}


	return TRUE;
}
//---------------------------------------------------------------------------