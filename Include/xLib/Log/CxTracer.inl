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

    _write( _oss.str() );
}
//-------------------------------------------------------------------------------------------------
/* virtual */
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

    _write(sRv);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline void_t
CxTracer::write(
    cExLevel &a_level,
    ctchar_t *a_format, ...
) const
{
    xUNUSED(a_level);
    xUNUSED(a_format);

    std::ctstring_t format = _levelToString(a_level) + xT(": ") + a_format;

    va_list args;
    xVA_START(args, a_format);
    _write(format.c_str(), args);
    xVA_END(args);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxTracer::_write(
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
