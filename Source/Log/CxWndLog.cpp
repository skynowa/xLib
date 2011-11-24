/**
 * \file  CxWndLog.cpp
 * \brief windows logging
 */


#include <xLib/Log/CxWndLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Sync/CxAutoCriticalSection.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxCriticalSection -> Mutex
CxCriticalSection CxWndLog::_ms_csListBox;
//---------------------------------------------------------------------------
/*explicit*/
CxWndLog::CxWndLog(
    const EWindowClass cwcWC
) :
    _m_eWC (cwcWC)
{
    /*DEBUG*/xASSERT_DO(wcListBox == _m_eWC, return);
}
//---------------------------------------------------------------------------
/*virtual*/
CxWndLog::~CxWndLog() {

}
//---------------------------------------------------------------------------
bool
CxWndLog::bWrite(
    const TxHandle  chWnd,
    const tchar_t  *pcszFormat, ...
)
{
    /*DEBUG*/xASSERT_RET(NULL != chWnd,      false);
    /*DEBUG*/xASSERT_RET(NULL != pcszFormat, false);

    //-------------------------------------
    //time
    std::tstring_t sTime;
    sTime = CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime);

    //-------------------------------------
    //comment
    std::tstring_t sParam;
    va_list palArgs = NULL;

    xVA_START(palArgs, pcszFormat);
    sParam = CxString::sFormatV(pcszFormat, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    //choose window
    #if xTODO
        switch(_m_eWC) {
            case wcListBox: {
                    /*LOCK*/CxAutoCriticalSection SL(_ms_csListBox);

                    ::SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)(CxString::sRemoveEOL(xT("[") + sTime + xT("] ") + xT(" ") + sParam)).c_str());
                    ::SendMessage(hWnd, WM_VSCROLL, MAKEWORD(SB_LINEDOWN, 0), 0);
                }
                break;

            default: {
                    /*DEBUG*/xASSERT_RET(false, false);
                }
                break;
        }
    #endif

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
