/**
 * \file  CxTraceLog.cpp
 * \brief tracing
 */


#include <xLib/Log/CxTraceLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxTraceLog::CxTraceLog(
    const bool cbIsUseTimeStr
) :
    _m_bIsEnable    (true),
    _m_bIsUseTimeStr(cbIsUseTimeStr)
{
}
//---------------------------------------------------------------------------
CxTraceLog::~CxTraceLog() {

}
//---------------------------------------------------------------------------
bool
CxTraceLog::bSetEnabled(
    const bool cbFlag
)
{
    /*DEBUG*/// cbFlag - n/a

    _m_bIsEnable = cbFlag;

    return true;
}
//---------------------------------------------------------------------------
bool
CxTraceLog::bWrite(
    const tchar_t *pcszFormat, ...
)
{
    /*DEBUG*/xASSERT_RET(NULL != pcszFormat, false);

    xCHECK_RET(false == _m_bIsEnable, true);

    //-------------------------------------
    //time
    std::tstring_t sTime;

    if (true == _m_bIsUseTimeStr) {
        sTime = xT("[") + CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime) + xT("] ");
    } else {
        sTime = xT("");
    }

    //-------------------------------------
    //comment
    std::tstring_t sParam;
    va_list      palArgs;

    xVA_START(palArgs, pcszFormat);
    sParam = CxString::sFormatV(pcszFormat, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    //tracing
#if xOS_ENV_WIN
    ::OutputDebugString((sTime + sParam + CxConst::xNL).c_str());
    /*DEBUG*/// n/a
#elif xOS_ENV_UNIX
    std::tcout << sTime << sParam << std::endl;
#endif

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
