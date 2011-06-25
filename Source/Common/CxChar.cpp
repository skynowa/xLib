/****************************************************************************
* Class name:  CxChar
* Description: character
* File name:   CxChar.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     11:01:2010 13:20:00
*
*****************************************************************************/


#include <xLib/Common/CxChar.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bIsAlphaNum (Check if character is alphanumeric)
/*static*/
BOOL
CxChar::bIsAlphaNum(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( _istalnum(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bIsAlpha (Check if character is alphabetic)
/*static*/
BOOL
CxChar::bIsAlpha(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( _istalpha(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bIsControl (Check if character is a control character)
/*static*/
BOOL
CxChar::bIsControl(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( _istcntrl(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bIsDigitDec (Check if character is decimal digit)
/*static*/
BOOL
CxChar::bIsDigitDec(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( _istdigit(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bIsDigitHex (Check if character is hexadecimal digit)
/*static*/
BOOL
CxChar::bIsDigitHex(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( _istxdigit(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bIsGraph (Check if character has graphical representation)
/*static*/
BOOL
CxChar::bIsGraph(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( _istgraph(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bIsPrint (Check if character is printable)
/*static*/
BOOL
CxChar::bIsPrint(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( _istprint(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bIsPunct (Check if character is a punctuation character)
/*static*/
BOOL
CxChar::bIsPunct(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( _istpunct(cchChar) );
}
//---------------------------------------------------------------------------
//DONE: bIsSpace (Check if character is a white-space)
/*static*/
BOOL
CxChar::bIsSpace(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( _istspace(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bIsLower (Check if character is lowercase letter)
/*static*/
BOOL
CxChar::bIsLower(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( _istlower(cchChar) );
}
//---------------------------------------------------------------------------
//DONE: bIsUpper (Check if character is uppercase letter)
/*static*/
BOOL
CxChar::bIsUpper(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( _istupper(cchChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: chToLower (Convert uppercase letter to lowercase)
/*static*/
TCHAR
CxChar::chToLower(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return _totlower(cchChar);
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: chToUpper (Convert lowercase letter to uppercase)
/*static*/
TCHAR
CxChar::chToUpper(
    const TCHAR cchChar
)
{
    /*DEBUG*/// n/a

    return _totupper(cchChar);
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxChar
CxChar::CxChar() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: ~CxChar
/*virtual*/
CxChar::~CxChar() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
