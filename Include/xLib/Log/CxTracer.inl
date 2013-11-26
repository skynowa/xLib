/**
 * \file   CxTracer.cpp
 * \brief  tracer
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxTracer::~CxTracer()
{
    _oss << CxConst::nl();

    write( _oss.str() );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxTracer::write(
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(a_format == NULL, return);

    std::tstring_t sRv;

    va_list args;
    xVA_START(args, a_format);
    sRv = CxString::formatV(a_format, args);
    xVA_END(args);

    write(sRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxTracer::write(
    std::ctstring_t &a_msg
) const
{
#if xOS_ENV_WIN
    (void_t)::OutputDebugString( a_msg.c_str() );
#endif

    std::tcout << a_msg;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
