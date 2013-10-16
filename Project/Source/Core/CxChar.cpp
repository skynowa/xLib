/**
 * \file  CxChar.cpp
 * \brief character
 */


#include <xLib/Core/CxChar.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isAlphaNum(
    ctchar_t &a_character
)
{
    return xINT_TO_BOOL( ::xTISALNUM(a_character) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isAlpha(
    ctchar_t &a_character
)
{
    return xINT_TO_BOOL( ::xTISALPHA(a_character) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isControl(
    ctchar_t &a_character
)
{
    return xINT_TO_BOOL( ::xTISCNTRL(a_character) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isDigitDec(
    ctchar_t &a_character
)
{
    return xINT_TO_BOOL( ::xTISDIGIT(a_character) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isDigitHex(
    ctchar_t &a_character
)
{
    return xINT_TO_BOOL( ::xTISXDIGIT(a_character) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isGraph(
    ctchar_t &a_character
)
{
    return xINT_TO_BOOL( ::xTISGRAPH(a_character) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isPrint(
    ctchar_t &a_character
)
{
    return xINT_TO_BOOL( ::xTISPRINT(a_character) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isPunct(
    ctchar_t &a_character
)
{
    return xINT_TO_BOOL( ::xTISPUNCT(a_character) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isSpace(
    ctchar_t &a_character
)
{
    return xINT_TO_BOOL( ::xTISSPACE(a_character) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isLower(
    ctchar_t &a_character
)
{
    return xINT_TO_BOOL( ::xTISLOWER(a_character) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isUpper(
    ctchar_t &a_character
)
{
    return xINT_TO_BOOL( ::xTISUPPER(a_character) );
}
//------------------------------------------------------------------------------
/* static */
tchar_t
CxChar::toLower(
    ctchar_t &a_character
)
{
    return xTTOLOWER(a_character);
}
//------------------------------------------------------------------------------
/* static */
tchar_t
CxChar::toUpper(
    ctchar_t &a_character
)
{
    return xTTOUPPER(a_character);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxChar::CxChar()
{
}
//------------------------------------------------------------------------------
/* virtual */
CxChar::~CxChar()
{
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
