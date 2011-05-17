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
    const INT ciChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( isalnum(ciChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bIsAlpha (Check if character is alphabetic)
/*static*/
BOOL
CxChar::bIsAlpha(
    const INT ciChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( iswalpha(ciChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bIsControl (Check if character is a control character)
/*static*/
BOOL
CxChar::bIsControl(
    const INT ciChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( iscntrl(ciChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bIsDigitDec (Check if character is decimal digit)
/*static*/
BOOL
CxChar::bIsDigitDec(
    const INT ciChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( isdigit(ciChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bIsDigitHex (Check if character is hexadecimal digit)
/*static*/
BOOL
CxChar::bIsDigitHex(
    const INT ciChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( isxdigit(ciChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bIsGraph (Check if character has graphical representation)
/*static*/
BOOL
CxChar::bIsGraph(
    const INT ciChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( isgraph(ciChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bIsPrint (Check if character is printable)
/*static*/
BOOL
CxChar::bIsPrint(
    const INT ciChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( isprint(ciChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bIsPunct (Check if character is a punctuation character)
/*static*/
BOOL
CxChar::bIsPunct(
    const INT ciChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( ispunct(ciChar) );
}
//---------------------------------------------------------------------------
//DONE: bIsSpace (Check if character is a white-space)
/*static*/
BOOL
CxChar::bIsSpace(
    const INT ciChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( isspace(ciChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bIsLower (Check if character is lowercase letter)
/*static*/
BOOL
CxChar::bIsLower(
    const INT ciChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( islower(ciChar) );
}
//---------------------------------------------------------------------------
//DONE: bIsUpper (Check if character is uppercase letter)
/*static*/
BOOL
CxChar::bIsUpper(
    const INT ciChar
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( isupper(ciChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: chToLower (Convert uppercase letter to lowercase)
/*static*/
TCHAR
CxChar::chToLower(
    const INT ciChar
)
{
    /*DEBUG*/// n/a

    //TODO: unicode
    return tolower(ciChar);
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: chToUpper (Convert lowercase letter to uppercase)
/*static*/
TCHAR
CxChar::chToUpper(
    const INT ciChar
)
{
    /*DEBUG*/// n/a

    //TODO: unicode
    return toupper(ciChar);
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxChar (constructor)
CxChar::CxChar() :
    _m_bRes(FALSE)
{
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: ~CxChar (destructor)
/*virtual*/
CxChar::~CxChar() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
