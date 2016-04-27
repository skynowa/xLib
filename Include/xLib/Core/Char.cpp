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
    return xINT_TO_BOOL( xTISALNUM(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isAlpha() const
{
    return xINT_TO_BOOL( xTISALPHA(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isControl() const
{
    return xINT_TO_BOOL( xTISCNTRL(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isDigitDec() const
{
    return xINT_TO_BOOL( xTISDIGIT(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isDigitHex() const
{
    return xINT_TO_BOOL( xTISXDIGIT(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isGraph() const
{
    return xINT_TO_BOOL( xTISGRAPH(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isPrint() const
{
    return xINT_TO_BOOL( xTISPRINT(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isPunct() const
{
    return xINT_TO_BOOL( xTISPUNCT(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isSpace() const
{
    return xINT_TO_BOOL( xTISSPACE(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isLower() const
{
    return xINT_TO_BOOL( xTISLOWER(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Char::isUpper() const
{
    return xINT_TO_BOOL( xTISUPPER(_ch, _locale) );
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
