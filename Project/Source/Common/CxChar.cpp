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
    const tchar_t a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISALNUM(a_cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsAlpha(
    const tchar_t a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISALPHA(a_cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsControl(
    const tchar_t a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISCNTRL(a_cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsDigitDec(
    const tchar_t a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISDIGIT(a_cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsDigitHex(
    const tchar_t a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISXDIGIT(a_cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsGraph(
    const tchar_t a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISGRAPH(a_cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsPrint(
    const tchar_t a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISPRINT(a_cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsPunct(
    const tchar_t a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISPUNCT(a_cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsSpace(
    const tchar_t a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISSPACE(a_cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsLower(
    const tchar_t a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISLOWER(a_cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsUpper(
    const tchar_t a_cchChar
)
{
    return xINT_TO_BOOL( ::xTISUPPER(a_cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
tchar_t
CxChar::chToLower(
    const tchar_t a_cchChar
)
{
    return xTTOLOWER(a_cchChar);
}
//---------------------------------------------------------------------------
/*static*/
tchar_t
CxChar::chToUpper(
    const tchar_t a_cchChar
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
/*virtual*/
CxChar::~CxChar() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
