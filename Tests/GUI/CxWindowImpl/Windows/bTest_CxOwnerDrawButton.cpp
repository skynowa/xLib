/****************************************************************************
*	bTest_CxOwnerDrawButton.cpp
*
*****************************************************************************/


#include "CWndMain.h"

//---------------------------------------------------------------------------
//TODO: bTest_CxOwnerDrawButton ()
BOOL CWndMain::bTest_CxOwnerDrawButton(CxOwnerDrawButton &xObj, INT iID, CxWindow *pwndParent) {
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