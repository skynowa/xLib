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
BOOL
CxChar::bIsAlphaNum(
    const char_t cchChar
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
    const char_t cchChar
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
    const char_t cchChar
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
    const char_t cchChar
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
    const char_t cchChar
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
    const char_t cchChar
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
    const char_t cchChar
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
    const char_t cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( xTISPUNCT(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsSpace(
    const char_t cchChar
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
    const char_t cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( xTISLOWER(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsUpper(
    const char_t cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( xTISUPPER(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*static*/
char_t
CxChar::chToLower(
    const char_t cchChar
)
{
    /*DEBUG*/// n/a

    return xTTOLOWER(cchChar);
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*static*/
char_t
CxChar::chToUpper(
    const char_t cchChar
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

xNAMESPACE_END(NxLib)
