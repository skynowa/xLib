/****************************************************************************
* Class name:  CxWndLog
* Description: windows logging
* File name:   CxWndLog.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.06.2009 17:44:10
*
*****************************************************************************/


#include <xLib/Log/Win/CxWndLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>

#if defined(xOS_WIN)
    #include <xLib/Sync/CxAutoCriticalSection.h>
#elif defined(xOS_LINUX)

#endif


#if defined(xOS_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCriticalSection CxWndLog::_ms_csListBox;
//---------------------------------------------------------------------------
//DONE: CxWndLog
CxWndLog::CxWndLog(EWindowClass wcWC) :
    _m_eWC (wcWC)
{
    /*DEBUG*/xASSERT_DO(wcListBox == _m_eWC, return);
}
//---------------------------------------------------------------------------
//DONE: ~CxWndLog
CxWndLog::~CxWndLog() {

}
//---------------------------------------------------------------------------
//DONE: bWrite (write)
BOOL
CxWndLog::bWrite(HWND hWnd, LPCTSTR pcszFormat, ...) {
    /*DEBUG*/xASSERT_RET(NULL != hWnd,       FALSE);
    /*DEBUG*/xASSERT_RET(NULL != pcszFormat, FALSE);

    //-------------------------------------
    //time
    tString sTime;
    sTime = CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime);

    //-------------------------------------
    //comment
    tString sParam;
    va_list palArgs = NULL;

    xVA_START(palArgs, pcszFormat);
    sParam = CxString::sFormatV(pcszFormat, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    //choose window
//    switch(_m_eWC) {
//        case wcListBox: {
//                /*LOCK*/CxAutoCriticalSection SL(_ms_csListBox);
//
//                ::SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)(CxString::sRemoveEOL(xT("[") + sTime + xT("] ") + xT(" ") + sParam)).c_str());
//                ::SendMessage(hWnd, WM_VSCROLL, MAKEWORD(SB_LINEDOWN, 0), 0);
//            }
//            break;
//
//        default: {
//                /*DEBUG*/xASSERT_RET(FALSE, FALSE);
//            }
//            break;
//    }

    return TRUE;
}
//---------------------------------------------------------------------------
#elif defined(xOS_LINUX)

#endif
