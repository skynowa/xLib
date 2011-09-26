/**
 * \file  CxChar.cpp
 * \brief character
 */


#include <xLib/Common/CxChar.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsAlphaNum(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( xTISALNUM(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsAlpha(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( xTISALPHA(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsControl(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( xTISCNTRL(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsDigitDec(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( xTISDIGIT(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsDigitHex(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( xTISXDIGIT(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsGraph(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( xTISGRAPH(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsPrint(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( xTISPRINT(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsPunct(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( xTISPUNCT(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsSpace(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( xTISSPACE(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsLower(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( xTISLOWER(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsUpper(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( xTISUPPER(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*static*/
TCHAR
CxChar::chToLower(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return xTTOLOWER(cchChar);
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*static*/
TCHAR
CxChar::chToUpper(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return xTTOUPPER(cchChar);
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxChar::CxChar() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*virtual*/
CxChar::~CxChar() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
