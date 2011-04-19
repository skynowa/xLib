/****************************************************************************
* Class name:  CxException
* Description: exception
* File name:   CxException.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     1 лют. 2011 11:13:48
*
*****************************************************************************/


#include <xLib/Common/CxException.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxException (constructor)
CxException::CxException() :
    _m_sMsg()
{
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: ~CxException (destructor)
/*virtual*/
CxException::~CxException() throw() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: what (message)
/*virtual*/
const char *
CxException::what() const throw() {
    /*DEBUG*/// n/a

    return std::string(_m_sMsg.begin(), _m_sMsg.end()).c_str();
}
//---------------------------------------------------------------------------
