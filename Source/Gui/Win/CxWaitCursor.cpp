/****************************************************************************
* Class name:  CxWaitCursor
* Description: wait cursor
* File name:   CxWaitCursor.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.06.2009 19:08:17
*
*****************************************************************************/



#include <xLib/Gui/CxWaitCursor.h>

//---------------------------------------------------------------------------
//DONE: CxWaitCursor (Set the cursor remembering the old cursor)
CxWaitCursor::CxWaitCursor() :
	_m_hCursor(NULL)
{
	HCURSOR hRes = NULL;

	hRes = ::LoadCursor(NULL, IDC_WAIT);
	/*DEBUG*/xASSERT_DO(NULL != hRes, return);
	
	_m_hCursor = ::SetCursor(hRes);
	/*DEBUG*///not need
}
//---------------------------------------------------------------------------
//DONE: ~CxWaitCursor (Restore cursor when it was valid. If it was not set the arrow cursor)
CxWaitCursor::~CxWaitCursor() {
	HCURSOR hRes = NULL;

	hRes = ::LoadCursor(NULL, IDC_ARROW);
	/*DEBUG*/xASSERT_DO(NULL != hRes, return);

	::SetCursor(_m_hCursor ? _m_hCursor : hRes);
	/*DEBUG*///not need
}
//---------------------------------------------------------------------------
//DONE: bRestore (Restore the wait cursor)
BOOL CxWaitCursor::bRestore() {
	HCURSOR hRes = NULL;

	hRes = ::LoadCursor(NULL, IDC_WAIT);
	/*DEBUG*/xASSERT_DO(NULL != hRes, FALSE);

	::SetCursor(hRes);
	/*DEBUG*///not need

	return TRUE;
}
//---------------------------------------------------------------------------