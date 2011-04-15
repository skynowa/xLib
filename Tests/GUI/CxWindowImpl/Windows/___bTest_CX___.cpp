/****************************************************************************
*	bTest_CXClass.cpp
*
*****************************************************************************/


#include "CWndMain.h"

//---------------------------------------------------------------------------
//TODO: - bTest_CXClass ()
BOOL CWndMain::bTest_CXClass(CXClass &xObj, INT iID, CXWindow *pwndParent) {
	/*DEBUG*/// cpbPB - n/a
	/*DEBUG*/xASSERT_RET(0    < iID,         FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

	//CXProgressBar::
	{
		_m_bRes = xObj.bCreateRes(iID, pwndParent);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}


	return TRUE;
}
//---------------------------------------------------------------------------