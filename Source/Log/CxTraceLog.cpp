/****************************************************************************
* Class name:  CxTraceLog
* Description: tracing
* File name:   CxTraceLog.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.06.2009 17:45:21
*
*****************************************************************************/



#include <xLib/Log/CxTraceLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxTraceLog ()
CxTraceLog::CxTraceLog(BOOL bIsUseTimeStr) :
    _m_bIsEnable    (TRUE),
    _m_bIsUseTimeStr(bIsUseTimeStr)
{
}
//---------------------------------------------------------------------------
//DONE: ~CxTraceLog ()
CxTraceLog::~CxTraceLog() {

}
//---------------------------------------------------------------------------
//TODO: bSetEnabled ()
BOOL
CxTraceLog::bSetEnabled(BOOL bFlag) {
    /*DEBUG*/// bFlag - n/a

    _m_bIsEnable = bFlag;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWrite ()
BOOL
CxTraceLog::bWrite(LPCTSTR pcszFormat, ...) {
    /*DEBUG*/xASSERT_RET(NULL != pcszFormat, FALSE);

    xCHECK_RET(FALSE == _m_bIsEnable, TRUE);

    //-------------------------------------
    //time
    tString sTime;

    if (TRUE == _m_bIsUseTimeStr) {
        sTime = xT("[") + CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime) + xT("] ");
    } else {
        sTime = xT("");
    }

    //-------------------------------------
    //comment
    tString sParam;
    va_list palArgs;

    xVA_START(palArgs, pcszFormat);
    sParam = CxString::sFormatV(pcszFormat, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    //tracing
#if defined(xOS_WIN)
    ::OutputDebugString((sTime + sParam + CxConst::xNL).c_str());
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    tcout << (sTime + sParam + CxConst::xNL);   tcout.flush();
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
