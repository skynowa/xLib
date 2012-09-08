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
    vWrite(_m_ossStream.str());
}
//---------------------------------------------------------------------------
/*static*/
void
CxTracer::vWrite(
    const tchar_t *pcszFormat, ...
)
{
    xCHECK_DO(pcszFormat == NULL, return);

    std::tstring_t sRv;

    va_list palArgs;
    xVA_START(palArgs, pcszFormat);
    sRv = CxString::sFormatV(pcszFormat, palArgs);
    xVA_END(palArgs);

    vWrite(sRv);
}
//---------------------------------------------------------------------------
/*static*/
void
CxTracer::vWrite(
    const std::tstring_t &csMsg
)
{
#if   xOS_ENV_WIN
    (void)::OutputDebugString((csMsg + CxConst::xNL).c_str());
#elif xOS_ENV_UNIX
    xNA;
#endif

    std::tcout << csMsg << std::endl;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
