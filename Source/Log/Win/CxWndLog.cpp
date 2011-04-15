/****************************************************************************
* Class name:  CxWndLog
* Description: ����������� � ����
* File name:   CxWndLog.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     01.06.2009 17:44:10
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Log/Win/CxWndLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Sync/CxAutoCriticalSection.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCriticalSection CxWndLog::_ms_csListBox;
//---------------------------------------------------------------------------
//TODO: + CxWndLog (constructor)
CxWndLog::CxWndLog(EWindowClass wcWC) :
	_m_eWC (wcWC)
{
	/*DEBUG*/xASSERT_DO(wcListBox == _m_eWC, return);
}
//---------------------------------------------------------------------------
//TODO: + ~CxWndLog (destructor)
CxWndLog::~CxWndLog() {

}
//---------------------------------------------------------------------------
//TODO: + bWrite (write)
BOOL
CxWndLog::bWrite(HWND hWnd, LPCTSTR pcszFormat, ...) {
	/*DEBUG*/xASSERT_RET(NULL != hWnd,       FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pcszFormat, FALSE);

	BOOL bRes = FALSE;

	//-------------------------------------
	//time
	tString sTime;
	sTime = CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime);

	//-------------------------------------
	//comment
	tString sParam;
	va_list palArgs = NULL;

	va_start(palArgs, pcszFormat);
	sParam = CxString::sFormatV(pcszFormat, palArgs);
	va_end(palArgs);	

	//-------------------------------------
	//choose window
//	switch(_m_eWC) {
//		case wcListBox: {
//				/*LOCK*/CxAutoCriticalSection SL(_ms_csListBox);
//
//				::SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)(CxString::sRemoveEOL(xT("[") + sTime + xT("] ") + xT(" ") + sParam)).c_str());
//				::SendMessage(hWnd, WM_VSCROLL, MAKEWORD(SB_LINEDOWN, 0), 0);
//			}
//			break;
//
//		default: {
//				/*DEBUG*/xASSERT_RET(FALSE, FALSE);
//			}
//			break;
//	}
	
	return TRUE;
}
//---------------------------------------------------------------------------
