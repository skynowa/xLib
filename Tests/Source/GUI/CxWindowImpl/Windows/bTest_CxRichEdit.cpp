/****************************************************************************
*	bTest_CxRichEdit.cpp
*
*****************************************************************************/


#include "CWndMain.h"

//---------------------------------------------------------------------------
//TODO: bTest_CxRichEdit ()
BOOL CWndMain::bTest_CxRichEdit(CxRichEdit &xObj, INT iID, CxWindow *pwndParent) {
	/*DEBUG*/// cpbPB - n/a
	/*DEBUG*/xASSERT_RET(0    < iID,         FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

	//CxRichEdit::bCreateRes
	{
		_m_bRes = xObj.bCreateRes(iID, pwndParent);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}





	return TRUE;
}
//---------------------------------------------------------------------------