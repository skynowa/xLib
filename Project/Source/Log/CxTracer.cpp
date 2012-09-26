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
/* virtual */
CxTracer::~CxTracer() {
    vWrite(_m_ossStream.str());
}
//---------------------------------------------------------------------------
/* static */
void
CxTracer::vWrite(
    const tchar_t *a_pcszFormat, ...
)
{
    xCHECK_DO(a_pcszFormat == NULL, return);

    std::tstring_t sRv;

    va_list palArgs;
    xVA_START(palArgs, a_pcszFormat);
    sRv = CxString::sFormatV(a_pcszFormat, palArgs);
    xVA_END(palArgs);

    vWrite(sRv);
}
//---------------------------------------------------------------------------
/* static */
void
CxTracer::vWrite(
    const std::tstring_t &a_csMsg
)
{
#if   xOS_ENV_WIN
    (void)::OutputDebugString((a_csMsg + CxConst::xNL).c_str());
#elif xOS_ENV_UNIX
    xNA;
#endif

    std::tcout << a_csMsg << std::endl;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
