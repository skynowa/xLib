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
//TODO: bIsAlphaNum (Check if character is alphanumeric)
/*static*/
BOOL
CxChar::bIsAlphaNum(INT iChar) {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( isalnum(iChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: bIsAlpha (Check if character is alphabetic)
/*static*/
BOOL
CxChar::bIsAlpha(INT iChar) {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( iswalpha(iChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: bIsControl (Check if character is a control character)
/*static*/
BOOL
CxChar::bIsControl(INT iChar) {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( iscntrl(iChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: bIsDigitDec (Check if character is decimal digit)
/*static*/
BOOL
CxChar::bIsDigitDec(INT iChar) {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( isdigit(iChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: bIsDigitHex (Check if character is hexadecimal digit)
/*static*/
BOOL
CxChar::bIsDigitHex(INT iChar) {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( isxdigit(iChar) );
    /*DEBUG*/// n/a

}
//---------------------------------------------------------------------------
//TODO: bIsGraph (Check if character has graphical representation)
/*static*/
BOOL
CxChar::bIsGraph(INT iChar) {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( isgraph(iChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: bIsPrint (Check if character is printable)
/*static*/
BOOL
CxChar::bIsPrint(INT iChar) {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( isprint(iChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: bIsPunct (Check if character is a punctuation character)
/*static*/
BOOL
CxChar::bIsPunct(INT iChar) {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( ispunct(iChar) );
}
//---------------------------------------------------------------------------
//TODO: bIsSpace (Check if character is a white-space)
/*static*/
BOOL
CxChar::bIsSpace(INT iChar) {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( isspace(iChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: bIsLower (Check if character is lowercase letter)
/*static*/
BOOL
CxChar::bIsLower(INT iChar) {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( islower(iChar) );
}
//---------------------------------------------------------------------------
//TODO: bIsUpper (Check if character is uppercase letter)
/*static*/
BOOL
CxChar::bIsUpper(INT iChar) {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( isupper(iChar) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: chToLower (Convert uppercase letter to lowercase)
/*static*/
CHAR
CxChar::chToLower(INT iChar) {
    /*DEBUG*/// n/a

    //TODO: unicode
    return tolower(iChar);
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: chToUpper (Convert lowercase letter to uppercase)
/*static*/
CHAR
CxChar::chToUpper(INT iChar) {
    /*DEBUG*/// n/a

    //TODO: unicode
    return toupper(iChar);
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxChar (comment)
/*virtual*/
CxChar::CxChar() :
    _m_bRes(FALSE)
{
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: ~CxChar (comment)
CxChar::~CxChar() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
