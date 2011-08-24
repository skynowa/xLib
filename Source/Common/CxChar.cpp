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
CxChar::CxChar() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*virtual*/
CxChar::~CxChar() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
