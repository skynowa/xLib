/**
 * \file   Trace.cpp
 * \brief  tracer
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Trace.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/Format.h>

#if   xENV_WIN
    #include "Platform/Win/Trace_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Trace_unix.inl"

    #if   xENV_LINUX

    #elif xENV_BSD

    #elif xENV_APPLE

    #endif
#endif


xNAMESPACE_BEGIN2(xl, log)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
Trace::~Trace()
{
    write(xT("%s"), _oss.str().c_str());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE void_t
Trace::write(
    cptr_ctchar_t a_format, ...
) const
{
    xCHECK_DO(!isEnabled(),          return);
    xCHECK_DO(a_format == xPTR_NULL, return);

    std::tstring_t msg;

    va_list args;
    xVA_START(args, a_format);
    msg = FormatC::strV(a_format, args);
    xVA_END(args);

    write(lvPlain, xT("%s"), msg.c_str());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE void_t
Trace::write(
    cExLevel      &a_level,
    cptr_ctchar_t  a_format, ...
) const
{
    xCHECK_DO(!isEnabled(), return);

    std::tstring_t msg;
    {
        va_list args;
        xVA_START(args, a_format);
        msg = FormatC::strV(a_format, args);
        xVA_END(args);

        if (a_level != lvPlain) {
            msg = _levelString(a_level) + xT(": ") + msg;
        }
    }

    _write_impl(msg);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, log)
