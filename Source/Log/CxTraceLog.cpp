/**
 * \file  CxTraceLog.cpp
 * \brief tracing
 */


#include <xLib/Log/CxTraceLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxTraceLog::CxTraceLog(
	const BOOL cbIsUseTimeStr
) :
    _m_bIsEnable    (TRUE),
    _m_bIsUseTimeStr(cbIsUseTimeStr)
{
}
//---------------------------------------------------------------------------
CxTraceLog::~CxTraceLog() {

}
//---------------------------------------------------------------------------
BOOL
CxTraceLog::bSetEnabled(
    const BOOL cbFlag
)
{
    /*DEBUG*/// cbFlag - n/a

    _m_bIsEnable = cbFlag;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxTraceLog::bWrite(
    LPCTSTR pcszFormat, ...
)
{
    /*DEBUG*/xASSERT_RET(NULL != pcszFormat, FALSE);

    xCHECK_RET(FALSE == _m_bIsEnable, TRUE);

    //-------------------------------------
    //time
    std::tstring sTime;

    if (TRUE == _m_bIsUseTimeStr) {
        sTime = xT("[") + CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime) + xT("] ");
    } else {
        sTime = xT("");
    }

    //-------------------------------------
    //comment
    std::tstring sParam;
    va_list      palArgs;

    xVA_START(palArgs, pcszFormat);
    sParam = CxString::sFormatV(pcszFormat, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    //tracing
#if defined(xOS_WIN)
    ::OutputDebugString((sTime + sParam + CxConst::xNL).c_str());
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    std::tcout << sTime << sParam << std::endl;
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
