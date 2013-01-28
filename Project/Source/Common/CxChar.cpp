/**
 * \file  CxChar.cpp
 * \brief character
 */


#include <xLib/Common/CxChar.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
bool
CxChar::isAlphaNum(
    const tchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISALNUM(a_cchChar) );
}
//---------------------------------------------------------------------------
/* static */
bool
CxChar::isAlpha(
    const tchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISALPHA(a_cchChar) );
}
//---------------------------------------------------------------------------
/* static */
bool
CxChar::isControl(
    const tchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISCNTRL(a_cchChar) );
}
//---------------------------------------------------------------------------
/* static */
bool
CxChar::isDigitDec(
    const tchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISDIGIT(a_cchChar) );
}
//---------------------------------------------------------------------------
/* static */
bool
CxChar::isDigitHex(
    const tchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISXDIGIT(a_cchChar) );
}
//---------------------------------------------------------------------------
/* static */
bool
CxChar::isGraph(
    const tchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISGRAPH(a_cchChar) );
}
//---------------------------------------------------------------------------
/* static */
bool
CxChar::isPrint(
    const tchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISPRINT(a_cchChar) );
}
//---------------------------------------------------------------------------
/* static */
bool
CxChar::isPunct(
    const tchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISPUNCT(a_cchChar) );
}
//---------------------------------------------------------------------------
/* static */
bool
CxChar::isSpace(
    const tchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISSPACE(a_cchChar) );
}
//---------------------------------------------------------------------------
/* static */
bool
CxChar::isLower(
    const tchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISLOWER(a_cchChar) );
}
//---------------------------------------------------------------------------
/* static */
bool
CxChar::isUpper(
    const tchar_t &a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISUPPER(a_cchChar) );
}
//---------------------------------------------------------------------------
/* static */
tchar_t
CxChar::toLower(
    const tchar_t &a_cchChar
)
{
    return xTTOLOWER(a_cchChar);
}
//---------------------------------------------------------------------------
/* static */
tchar_t
CxChar::toUpper(
    const tchar_t &a_cchChar
)
{
    return xTTOUPPER(a_cchChar);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxChar::CxChar() {

}
//---------------------------------------------------------------------------
/* virtual */
CxChar::~CxChar() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
