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
    return xINT_TO_BOOL( std::xTISALNUM(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isAlpha(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( std::xTISALPHA(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isControl(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( std::xTISCNTRL(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isDigitDec(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( std::xTISDIGIT(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isDigitHex(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( std::xTISXDIGIT(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isGraph(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( std::xTISGRAPH(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isPrint(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( std::xTISPRINT(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isPunct(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( std::xTISPUNCT(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isSpace(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( std::xTISSPACE(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isLower(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( std::xTISLOWER(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxChar::isUpper(
    ctchar_t &a_ch
)
{
    return xINT_TO_BOOL( std::xTISUPPER(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline tchar_t
CxChar::toLower(
    ctchar_t &a_ch
)
{
    return static_cast<tchar_t>( std::xTTOLOWER(a_ch) );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline tchar_t
CxChar::toUpper(
    ctchar_t &a_ch
)
{
    return static_cast<tchar_t>( std::xTTOUPPER(a_ch) );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
