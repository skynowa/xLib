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
    _oss()
{
}
//------------------------------------------------------------------------------
/* virtual */
CxTracer::~CxTracer()
{
    write(_oss.str());
}
//------------------------------------------------------------------------------
/* static */
void_t
CxTracer::write(
    ctchar_t *a_format, ...
)
{
    xCHECK_DO(a_format == NULL, return);

    std::tstring_t sRv;

    va_list palArgs;
    xVA_START(palArgs, a_format);
    sRv = CxString::formatV(a_format, palArgs);
    xVA_END(palArgs);

    write(sRv);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxTracer::write(
    std::ctstring_t &a_msg
)
{
#if xOS_ENV_WIN
    (void_t)::OutputDebugString((a_msg + CxConst::xNL).c_str());
#endif

    std::tcout << a_msg << std::endl;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
