/**
 * \file  CxChar.cpp
 * \brief character
 */


#include <xLib/Common/CxChar.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isAlphaNum(
    ctchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISALNUM(a_cchChar) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isAlpha(
    ctchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISALPHA(a_cchChar) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isControl(
    ctchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISCNTRL(a_cchChar) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isDigitDec(
    ctchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISDIGIT(a_cchChar) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isDigitHex(
    ctchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISXDIGIT(a_cchChar) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isGraph(
    ctchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISGRAPH(a_cchChar) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isPrint(
    ctchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISPRINT(a_cchChar) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isPunct(
    ctchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISPUNCT(a_cchChar) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isSpace(
    ctchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISSPACE(a_cchChar) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isLower(
    ctchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISLOWER(a_cchChar) );
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxChar::isUpper(
    ctchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISUPPER(a_cchChar) );
}
//------------------------------------------------------------------------------
/* static */
tchar_t
CxChar::toLower(
    ctchar_t &a_cchChar
)
{
    return xTTOLOWER(a_cchChar);
}
//------------------------------------------------------------------------------
/* static */
tchar_t
CxChar::toUpper(
    ctchar_t &a_cchChar
)
{
    return xTTOUPPER(a_cchChar);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxChar::CxChar() {

}
//------------------------------------------------------------------------------
/* virtual */
CxChar::~CxChar() {

}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
