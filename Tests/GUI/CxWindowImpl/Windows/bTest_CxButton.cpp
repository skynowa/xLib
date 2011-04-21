/****************************************************************************
*	bTest_CxButton.cpp
*
*****************************************************************************/


#include "CWndMain.h"

//---------------------------------------------------------------------------
//TODO: - bTest_CxButton ()
BOOL CWndMain::bTest_CxButton(CxButton &xObj, INT iID, CxWindow *pwndParent) {
	/*DEBUG*/// cpbPB - n/a
	/*DEBUG*/xASSERT_RET(0    < iID,         FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

	//CxProgressBar::
	{
		_m_bRes = xObj.bCreateRes(iID, pwndParent);  
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//сообщения CxButtonBase
	{
		_m_bRes = xObj.bSetViewStyle(CxButton::vsText);  
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		_m_bRes = xObj.bSetText(xT("xxxxxxxxxxxxxxx"));
		/*DEBUG*/xASSERT(FALSE != _m_bRes);	


		//_m_bRes = xObj.bSetAlignment(CxButtonBase::taRight);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		//_m_bRes = xObj.bSetNotify(TRUE);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		//_m_bRes = xObj.bSetFlat(TRUE);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		_m_bRes = xObj.bSetMultiLine(TRUE);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		////_m_bRes = xObj.bClick();
		/////*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxButton::vsText
	{
		_m_bRes = xObj.bSetViewStyle(CxButton::vsText);  
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		_m_bRes = xObj.bSetText(xT("xxxx"));
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxButton::vsIcon (icon)
	{
		_m_bRes = xObj.bSetViewStyle(CxButton::vsIcon);  
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		HICON hIcon = ::LoadIcon(NULL, IDI_ERROR);
		/*DEBUG*/xASSERT(NULL != hIcon);

		_m_bRes = xObj.bSetImage(CxButton::itIcon, hIcon);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxButton::vsIcon (cursor)
	{
		_m_bRes = xObj.bSetViewStyle(CxButton::vsIcon);  
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		HICON hCursor = ::LoadCursor(NULL, IDC_APPSTARTING);
		/*DEBUG*/xASSERT(NULL != hCursor);

		_m_bRes = xObj.bSetImage(CxButton::itIcon, hCursor);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxButton::vsBitmap
	//{
	//	_m_bRes = xObj.bSetViewStyle(CxButton::vsBitmap);  
	//	/*DEBUG*/xASSERT(FALSE != _m_bRes); 

	//	HBITMAP hBitmap = ::LoadBitmap(NULL, MAKEINTRESOURCE(OBM_CHECK));
	//	/*DEBUG*/xASSERT(NULL != hBitmap);

	//	_m_bRes = xObj.bSetImage(CxButton::itBitmap, hBitmap);
	//	/*DEBUG*/xASSERT(FALSE != _m_bRes);
	//}

	//обработчики событий
	{
		xObj.vSet_OnClick    ( xCLOSURE(this, &CWndMain::vBtnButton1_OnClick)     );  
		xObj.vSet_OnDbClick  ( xCLOSURE(this, &CWndMain::vBtnButton1_OnDbClick)   );  
		xObj.vSet_OnKillFocus( xCLOSURE(this, &CWndMain::vBtnButton1_OnKillFocus) );  
		xObj.vSet_OnSetFocus ( xCLOSURE(this, &CWndMain::vBtnButton1_OnSetFocus)  ); 
	} 


	return TRUE;
}
//---------------------------------------------------------------------------