/****************************************************************************
* Class name:  CxException
* Description: exception
* File name:   CxException.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     1 лют. 2011 11:13:48
*
*****************************************************************************/


#include <xLib/Common/CxException.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxException
CxException::CxException() :
    _m_sMsg()
{
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: ~CxException
/*virtual*/
CxException::~CxException() throw() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*virtual*/
const char*
CxException::what() const throw() {

    return _m_sMsg.c_str();
}
//---------------------------------------------------------------------------
//DONE: sGetClassName ()
tString
CxException::sGetClassName() const throw() {
    /*DEBUG*/

    return typeid(*this).name();
}
//---------------------------------------------------------------------------
//DONE: sGetWhat ()
const tString &
CxException::sGetWhat() const throw() {
    /*DEBUG*/

    return _m_sMsg;
}
//---------------------------------------------------------------------------

