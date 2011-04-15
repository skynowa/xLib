/****************************************************************************
* Class name:  CxWaitCursor
* Description: wait cursor
* File name:   CxWaitCursor.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.06.2009 19:08:17
* Version:     1.0.0.0 Debug
*
*****************************************************************************/



#include <xLib/Gui/CxWaitCursor.h>

//---------------------------------------------------------------------------
//TODO: + CxWaitCursor (Set the cursor remembering the old cursor)
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
//TODO: + ~CxWaitCursor (Restore cursor when it was valid. If it was not set the arrow cursor)
CxWaitCursor::~CxWaitCursor() {
	HCURSOR hRes = NULL;

	hRes = ::LoadCursor(NULL, IDC_ARROW);
	/*DEBUG*/xASSERT_DO(NULL != hRes, return);

	::SetCursor(_m_hCursor ? _m_hCursor : hRes);
	/*DEBUG*///not need
}
//---------------------------------------------------------------------------
//TODO: + bRestore (Restore the wait cursor)
BOOL CxWaitCursor::bRestore() {
	HCURSOR hRes = NULL;

	hRes = ::LoadCursor(NULL, IDC_WAIT);
	/*DEBUG*/xASSERT_DO(NULL != hRes, FALSE);

	::SetCursor(hRes);
	/*DEBUG*///not need

	return TRUE;
}
//---------------------------------------------------------------------------