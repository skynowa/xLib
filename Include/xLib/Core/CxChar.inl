/**
 * \file  CxChar.cpp
 * \brief character
 */


#include <xLib/Core/CxUtils.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isAlphaNum(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( xTISALNUM(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isAlpha(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( xTISALPHA(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isControl(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( xTISCNTRL(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isDigitDec(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( xTISDIGIT(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isDigitHex(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( xTISXDIGIT(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isGraph(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( xTISGRAPH(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isPrint(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( xTISPRINT(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isPunct(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( xTISPUNCT(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isSpace(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( xTISSPACE(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isLower(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( xTISLOWER(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isUpper(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( xTISUPPER(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline tchar_t
CxChar::toLower(
    ctchar_t &a_ch
)
{
    return static_cast<tchar_t>( xTTOLOWER(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline tchar_t
CxChar::toUpper(
    ctchar_t &a_ch
)
{
    return static_cast<tchar_t>( xTTOUPPER(a_ch) );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
