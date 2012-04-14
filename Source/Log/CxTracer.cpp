/**
 * \file   CxTracer.cpp
 * \brief  tracer
 */


#include <xLib/Log/CxTracer.h>


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*virtual*/
CxTracer::~CxTracer() {
#if xOS_ENV_WIN
    (void)::OutputDebugString((_m_ossStream.str() + CxConst::xNL).c_str());
#elif xOS_ENV_UNIX
    xNA;
#endif

    std::tcout << _m_ossStream.str() << std::endl;
}
//---------------------------------------------------------------------------
/*static*/
CxTracer
CxTracer::Write() {
    return CxTracer();
}
//---------------------------------------------------------------------------
/*static*/
bool
CxTracer::bTrace(
    const tchar_t *pcszFormat, ...
)
{
    std::tstring_t sRes;

    va_list palArgs;
    xVA_START(palArgs, pcszFormat);
    sRes = CxString::sFormatV(pcszFormat, palArgs);
    xVA_END(palArgs);

#if xOS_ENV_WIN
    (void)::OutputDebugString((sRes + CxConst::xNL).c_str());
#elif xOS_ENV_UNIX
    xNA;
#endif

    std::tcout << sRes << std::endl;

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxTracer::CxTracer() {

}
//---------------------------------------------------------------------------
