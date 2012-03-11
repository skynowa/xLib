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
    const tchar_t cchChar
)
{
    return xINT_TO_BOOL( ::xTISALNUM(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsAlpha(
    const tchar_t cchChar
)
{
    return xINT_TO_BOOL( ::xTISALPHA(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsControl(
    const tchar_t cchChar
)
{
    return xINT_TO_BOOL( ::xTISCNTRL(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsDigitDec(
    const tchar_t cchChar
)
{
    return xINT_TO_BOOL( ::xTISDIGIT(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsDigitHex(
    const tchar_t cchChar
)
{
    return xINT_TO_BOOL( ::xTISXDIGIT(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsGraph(
    const tchar_t cchChar
)
{
    return xINT_TO_BOOL( ::xTISGRAPH(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsPrint(
    const tchar_t cchChar
)
{
    return xINT_TO_BOOL( ::xTISPRINT(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsPunct(
    const tchar_t cchChar
)
{
    return xINT_TO_BOOL( ::xTISPUNCT(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsSpace(
    const tchar_t cchChar
)
{
    return xINT_TO_BOOL( ::xTISSPACE(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsLower(
    const tchar_t cchChar
)
{
    return xINT_TO_BOOL( ::xTISLOWER(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
bool
CxChar::bIsUpper(
    const tchar_t cchChar
)
{
    return xINT_TO_BOOL( ::xTISUPPER(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
tchar_t
CxChar::chToLower(
    const tchar_t cchChar
)
{
    return xTTOLOWER(cchChar);
}
//---------------------------------------------------------------------------
/*static*/
tchar_t
CxChar::chToUpper(
    const tchar_t cchChar
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
