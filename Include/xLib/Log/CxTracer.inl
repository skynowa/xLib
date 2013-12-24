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

    write(xT("%s"), _oss.str().c_str() );
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline void_t
CxTracer::write(
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(a_format == NULL, return);

    va_list args;
    xVA_START(args, a_format);
    write(lvUnknown, a_format, args);
    xVA_END(args);
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

    std::tstring_t msg;
    {
        va_list args;
        xVA_START(args, a_format);
        msg = CxString::formatV(a_format, args);
        xVA_END(args);

        msg = _levelToString(a_level) + xT(": ") + msg;
    }

    // write
    {
    #if xOS_ENV_WIN
        (void_t)::OutputDebugString( msg.c_str() );
    #endif

        std::tcout << msg;
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
