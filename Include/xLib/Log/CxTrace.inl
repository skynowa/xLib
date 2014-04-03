/**
 * \file   CxTrace.cpp
 * \brief  tracer
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>


xNAMESPACE2_BEGIN(xlib, log)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxTrace::~CxTrace()
{
    write(xT("%s"), _oss.str().c_str());
}
//-------------------------------------------------------------------------------------------------
template<class T>
inline CxTrace &
CxTrace::operator << (const T &valueT)
{
    _oss << valueT;
    return *this;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline void_t
CxTrace::write(
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(!isEnabled(),     return);
    xCHECK_DO(a_format == xPTR_NULL, return);

    std::tstring_t msg;

    va_list args;
    xVA_START(args, a_format);
    msg = CxString::formatV(a_format, args);
    xVA_END(args);

    write(lvPlain, xT("%s"), msg.c_str());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline void_t
CxTrace::write(
    cExLevel &a_level,
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(!isEnabled(), return);

    std::tstring_t msg;
    {
        va_list args;
        xVA_START(args, a_format);
        msg = CxString::formatV(a_format, args);
        xVA_END(args);

        if (a_level != lvPlain) {
            msg = _levelToString(a_level) + xT(": ") + msg;
        }
    }

    // write
    {
    #if xOS_ENV_WIN
        (void_t)::OutputDebugString( msg.c_str() );
    #endif

        std::tcout << msg << std::endl;
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, log)
