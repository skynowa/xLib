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

    return static_cast<BOOL>( xISTALNUM(cchChar) );
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

    return static_cast<BOOL>( xISTALPHA(cchChar) );
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

    return static_cast<BOOL>( xISTCNTRL(cchChar) );
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

    return static_cast<BOOL>( xISTDIGIT(cchChar) );
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

    return static_cast<BOOL>( xISTXDIGIT(cchChar) );
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

    return static_cast<BOOL>( xISTGRAPH(cchChar) );
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

    return static_cast<BOOL>( xISTPRINT(cchChar) );
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

    return static_cast<BOOL>( xISTPUNCT(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsSpace(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( xISTSPACE(cchChar) );
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

    return static_cast<BOOL>( xISTLOWER(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsUpper(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( xISTUPPER(cchChar) );
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

    return xTOTLOWER(cchChar);
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

    return xTOTUPPER(cchChar);
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
