/****************************************************************************
*	bTest_CxGroupBox.cpp
*
*****************************************************************************/


#include "CWndMain.h"

//---------------------------------------------------------------------------
//TODO: bTest_CxGroupBox ()
BOOL CWndMain::bTest_CxGroupBox(CxGroupBox &xObj, INT iID, CxWindow *pwndParent) {
	/*DEBUG*/// cpbPB - n/a
	/*DEBUG*/xASSERT_RET(0    < iID,         FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

	//CxProgressBar::
	{
		_m_bRes = xObj.bCreateRes(iID, pwndParent);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}


	return TRUE;
}
//---------------------------------------------------------------------------