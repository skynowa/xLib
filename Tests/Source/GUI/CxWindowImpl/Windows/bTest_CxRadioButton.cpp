/****************************************************************************
*	bTest_CxRadioButton.cpp
*
*****************************************************************************/


#include "CWndMain.h"

//---------------------------------------------------------------------------
//TODO: bTest_CxRadioButton ()
BOOL CWndMain::bTest_CxRadioButton(CxRadioButton &xObj, INT iID, CxWindow *pwndParent) {
	/*DEBUG*/// cpbPB - n/a
	/*DEBUG*/xASSERT_RET(0    < iID,         FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

	//CxProgressBar::
	{
		_m_bRes = xObj.bCreateRes(IDC_rbtnRadioButton1, pwndParent);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}


	CxRadioButton::ECheckState bstRes = xObj.bstGetState(); 
	/*DEBUG*/xASSERT(CxRadioButton::csUnchecked == bstRes);

	_m_bRes = xObj.bSetState(CxRadioButton::csChecked);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);			//iMsgBox(xT("CxRadioButton::csChecked"));

	_m_bRes = xObj.bSetState(CxRadioButton::csUnchecked);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);		    //iMsgBox(xT("CxRadioButton::csUnchecked"));


	return TRUE;
}
//---------------------------------------------------------------------------