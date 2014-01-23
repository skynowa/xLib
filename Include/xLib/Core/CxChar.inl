/**
 * \file  CxChar.cpp
 * \brief character
 */


#include <xLib/Core/CxUtils.h>


xNAMESPACE2_BEGIN(xlib, core)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxChar::CxChar(
    ctchar_t          &a_ch,
    const std::locale &a_locale /*  = std::locale() */
) :
    _ch    (a_ch),
    _locale(a_locale)
{
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxChar::isAlphaNum() const
{
    return xINT_TO_BOOL( xTISALNUM(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxChar::isAlpha() const
{
    return xINT_TO_BOOL( xTISALPHA(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxChar::isControl() const
{
    return xINT_TO_BOOL( xTISCNTRL(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxChar::isDigitDec() const
{
    return xINT_TO_BOOL( xTISDIGIT(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxChar::isDigitHex() const
{
    return xINT_TO_BOOL( xTISXDIGIT(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxChar::isGraph() const
{
    return xINT_TO_BOOL( xTISGRAPH(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxChar::isPrint() const
{
    return xINT_TO_BOOL( xTISPRINT(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxChar::isPunct() const
{
    return xINT_TO_BOOL( xTISPUNCT(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxChar::isSpace() const
{
    return xINT_TO_BOOL( xTISSPACE(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxChar::isLower() const
{
    return xINT_TO_BOOL( xTISLOWER(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxChar::isUpper() const
{
    return xINT_TO_BOOL( xTISUPPER(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
inline tchar_t
CxChar::toLower() const
{
    return static_cast<tchar_t>( xTTOLOWER(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------
inline tchar_t
CxChar::toUpper() const
{
    return static_cast<tchar_t>( xTTOUPPER(_ch, _locale) );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, core)
