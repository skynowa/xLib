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

    return static_cast<BOOL>( std::xTISALNUM(cchChar) );
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

    return static_cast<BOOL>( ::xTISALPHA(cchChar) );
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

    return static_cast<BOOL>( std::xTISCNTRL(cchChar) );
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

    return static_cast<BOOL>( std::xTISDIGIT(cchChar) );
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

    return static_cast<BOOL>( std::xTISXDIGIT(cchChar) );
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

    return static_cast<BOOL>( std::xTISGRAPH(cchChar) );
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

    return static_cast<BOOL>( std::xTISPRINT(cchChar) );
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

    return static_cast<BOOL>( std::xTISPUNCT(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsSpace(
    const char_t cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( std::xTISSPACE(cchChar) );
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

    return static_cast<BOOL>( std::xTISLOWER(cchChar) );
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxChar::bIsUpper(
    const char_t cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( std::xTISUPPER(cchChar) );
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
