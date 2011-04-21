/****************************************************************************
*	bTest_CxCheckBox.cpp
*
*****************************************************************************/


#include "CWndMain.h"

//---------------------------------------------------------------------------
//TODO: - bTest_CxCheckBox ()
BOOL CWndMain::bTest_CxCheckBox(CxCheckBox &xObj, INT iID, CxWindow *pwndParent) {
	/*DEBUG*/// cpbPB - n/a
	/*DEBUG*/xASSERT_RET(0    < iID,         FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

	//CxProgressBar::
	{
		_m_bRes = xObj.bCreateRes(IDC_chkCheckBox1, pwndParent);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}


	CxCheckBox::ECheckState csRes = xObj.csGetState();
	/*DEBUG*/xASSERT(CxCheckBox::csUnchecked == csRes);

	///////*/*DEBUG*/xASSERT(TRUE  == bIsStyleExists(BS_AUTOCHECKBOX));
	///////*DEBUG*/xASSERT(FALSE == bIsStyleExists(BS_AUTO3STATE));*/

	_m_bRes = xObj.bSetAllowGrayed(TRUE); 
	/*DEBUG*/xASSERT(FALSE != _m_bRes);

	///////*/*DEBUG*/xASSERT(FALSE == bIsStyleExists(BS_AUTOCHECKBOX));
	///////*DEBUG*/xASSERT(TRUE  == bIsStyleExists(BS_AUTO3STATE));*/

	_m_bRes = xObj.bSetState(CxCheckBox::csChecked);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);			//iMsgBox(xT("CxCheckBox::csChecked"));
	_m_bRes = xObj.bSetState(CxCheckBox::csGrayed);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);		    //iMsgBox(xT("CxCheckBox::csGrayed"));
	_m_bRes = xObj.bSetState(CxCheckBox::csUnchecked);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);		    //iMsgBox(xT("CxCheckBox::csUnchecked"));

	return TRUE;
}
//---------------------------------------------------------------------------