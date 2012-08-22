/**
 * \file   CxTracer.cpp
 * \brief  tracer
 */


#include <xLib/Log/CxTracer.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxTracer::CxTracer() :
    _m_ossStream()
{

}
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
bool
CxTracer::bWrite(
    const tchar_t *pcszFormat, ...
)
{
    std::tstring_t sRv;

    va_list palArgs;
    xVA_START(palArgs, pcszFormat);
    sRv = CxString::sFormatV(pcszFormat, palArgs);
    xVA_END(palArgs);

#if xOS_ENV_WIN
    (void)::OutputDebugString((sRv + CxConst::xNL).c_str());
#elif xOS_ENV_UNIX
    xNA;
#endif

    std::tcout << sRv << std::endl;

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxTracer::bWrite(
    const std::tstring_t &csMsg
)
{
    return bWrite(xT("%s"), csMsg.c_str());
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
