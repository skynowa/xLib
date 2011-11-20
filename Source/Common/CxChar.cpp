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
/*static*/
bool
CxChar::bIsAlphaNum(
    const tchar cchChar
)
{
    return xINT_AS_BOOL( std::xTISALNUM(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsAlpha(
    const tchar cchChar
)
{
    return xINT_AS_BOOL( ::xTISALPHA(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsControl(
    const tchar cchChar
)
{
    return xINT_AS_BOOL( std::xTISCNTRL(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsDigitDec(
    const tchar cchChar
)
{
    return xINT_AS_BOOL( std::xTISDIGIT(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsDigitHex(
    const tchar cchChar
)
{
    return xINT_AS_BOOL( std::xTISXDIGIT(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsGraph(
    const tchar cchChar
)
{
    return xINT_AS_BOOL( std::xTISGRAPH(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsPrint(
    const tchar cchChar
)
{
    return xINT_AS_BOOL( std::xTISPRINT(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsPunct(
    const tchar cchChar
)
{
    return xINT_AS_BOOL( std::xTISPUNCT(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsSpace(
    const tchar cchChar
)
{
    return xINT_AS_BOOL( std::xTISSPACE(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsLower(
    const tchar cchChar
)
{
    return xINT_AS_BOOL( std::xTISLOWER(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsUpper(
    const tchar cchChar
)
{
    return xINT_AS_BOOL( std::xTISUPPER(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
tchar
CxChar::chToLower(
    const tchar cchChar
)
{
    return xTTOLOWER(cchChar);
}
//---------------------------------------------------------------------------
/*static*/
tchar
CxChar::chToUpper(
    const tchar cchChar
)
{
    return xTTOUPPER(cchChar);
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
/*virtual*/
CxChar::~CxChar() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
