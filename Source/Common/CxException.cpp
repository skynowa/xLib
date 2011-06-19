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

	std::string sRes = xTS2S(_m_sMsg);

	return sRes.c_str();
}
//---------------------------------------------------------------------------
//DONE: sGetClassName ()
tString
CxException::sGetClassName() const throw() {
    /*DEBUG*/

	std::string sRes = typeid(*this).name();

	return xS2TS(sRes);
}
//---------------------------------------------------------------------------
//DONE: sGetWhat ()
const tString &
CxException::sGetWhat() const throw() {
    /*DEBUG*/

    return _m_sMsg;
}
//---------------------------------------------------------------------------

