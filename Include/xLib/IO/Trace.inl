/**
 * \file   Trace.inl
 * \brief  tracer
 */


#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>


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
template<class T>
inline Trace &
Trace::operator << (const T &valueT)
{
    _oss << valueT;
    return *this;
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

    // write
    {
    #if xENV_WIN
        (void_t)::OutputDebugString( msg.c_str() );
    #endif

        std::tcout << msg << std::endl;
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, log)
