/****************************************************************************
* Class name:  CxException
* Description: exception
* File name:   CxException.h
* Compilers:   Visual C++ 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     1 лют. 2011 11:13:48
* Version:     1.0.0.0 Debug
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
