/**
 * \file   CxTracer.cpp
 * \brief  tracer
 */


#include <xLib/Log/CxTracer.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxTracer::CxTracer() :
    _m_ossStream()
{
}
//------------------------------------------------------------------------------
/* virtual */
CxTracer::~CxTracer() {
    write(_m_ossStream.str());
}
//------------------------------------------------------------------------------
/* static */
void_t
CxTracer::write(
    ctchar_t *a_pcszFormat, ...
)
{
    xCHECK_DO(a_pcszFormat == NULL, return);

    std::tstring_t sRv;

    va_list palArgs;
    xVA_START(palArgs, a_pcszFormat);
    sRv = CxString::formatV(a_pcszFormat, palArgs);
    xVA_END(palArgs);

    write(sRv);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxTracer::write(
    std::ctstring_t &a_csMsg
)
{
#if xOS_ENV_WIN
    (void_t)::OutputDebugString((a_csMsg + CxConst::xNL).c_str());
#endif

    std::tcout << a_csMsg << std::endl;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
