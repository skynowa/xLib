/**
 * \file   Trace.cpp
 * \brief  tracer
 */


#if !xOPTION_HEADER_ONLY
    #include "Trace.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>

#if   xENV_WIN
    #include "Platform/Win/Trace_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/Trace_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/Trace_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/Trace_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, log)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
inline
Trace::~Trace()
{
    write(xT("%s"), _oss.str().c_str());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline void_t
Trace::write(
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(!isEnabled(),          return);
    xCHECK_DO(a_format == xPTR_NULL, return);

    std::tstring_t msg;

    va_list args;
    xVA_START(args, a_format);
    msg = String::formatV(a_format, args);
    xVA_END(args);

    write(lvPlain, xT("%s"), msg.c_str());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline void_t
Trace::write(
    cExLevel &a_level,
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(!isEnabled(), return);

    std::tstring_t msg;
    {
        va_list args;
        xVA_START(args, a_format);
        msg = String::formatV(a_format, args);
        xVA_END(args);

        if (a_level != lvPlain) {
            msg = _levelString(a_level) + xT(": ") + msg;
        }
    }

    _write_impl(msg);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, log)
