/**
 * \file  Char.inl
 * \brief character
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Char.h"
#endif

#include <xLib/Core/Utils.h>


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Char::Char(
    ctchar_t      &a_ch,
    const xLOCALE &a_locale /*  = std::locale() */
) :
    _ch    (a_ch),
    _locale(a_locale)
{
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isAlphaNum() const
{
    return static_cast<bool_t>( xTISALNUM(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isAlpha() const
{
    return static_cast<bool_t>( xTISALPHA(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isControl() const
{
    return static_cast<bool_t>( xTISCNTRL(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isDigitDec() const
{
    return static_cast<bool_t>( xTISDIGIT(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isDigitHex() const
{
    return static_cast<bool_t>( xTISXDIGIT(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isGraph() const
{
    return static_cast<bool_t>( xTISGRAPH(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isPrint() const
{
    return static_cast<bool_t>( xTISPRINT(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isPunct() const
{
    return static_cast<bool_t>( xTISPUNCT(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isSpace() const
{
    return static_cast<bool_t>( xTISSPACE(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isLower() const
{
    return static_cast<bool_t>( xTISLOWER(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isUpper() const
{
    return static_cast<bool_t>( xTISUPPER(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE tchar_t
Char::toLower() const
{
    return static_cast<tchar_t>( xTTOLOWER(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE tchar_t
Char::toUpper() const
{
    return static_cast<tchar_t>( xTTOUPPER(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
