/**
 * \file  CxWndLog.cpp
 * \brief windows logging
 */


#include <xLib/Log/Win/CxWndLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>

#if xOS_ENV_WIN
    #include <xLib/Sync/CxAutoCriticalSection.h>
#elif xOS_ENV_UNIX

#endif


#if xOS_ENV_WIN

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
CxWndLog::~CxWndLog() {

}
//---------------------------------------------------------------------------
BOOL
CxWndLog::bWrite(
    const HWND chWnd,
    LPCTSTR    pcszFormat, ...
)
{
    /*DEBUG*/xASSERT_RET(NULL != chWnd,      FALSE);
    /*DEBUG*/xASSERT_RET(NULL != pcszFormat, FALSE);

    //-------------------------------------
    //time
    std::string_t sTime;
    sTime = CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime);

    //-------------------------------------
    //comment
    std::string_t sParam;
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
                    /*DEBUG*/xASSERT_RET(FALSE, FALSE);
                }
                break;
        }
    #endif

    return TRUE;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
