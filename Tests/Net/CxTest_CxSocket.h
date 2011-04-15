/****************************************************************************
* Class name:  CxTest_CxSocket
* Description: test CxSocket 
* File name:   CxTest_CxSocket.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxTest_CxSocketH
#define CxTest_CxSocketH
//---------------------------------------------------------------------------
#include <xLib/Net/CxSocket.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_CxSocket : public CxTest {
	public:
		CxTest_CxSocket();
	   ~CxTest_CxSocket();

	   /*virtual*/ BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxSocket (comment)
CxTest_CxSocket::CxTest_CxSocket() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxSocket (comment)
CxTest_CxSocket::~CxTest_CxSocket() {
	//code
}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL CxTest_CxSocket::bUnit() {
	/*DEBUG*/

	return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxSocketH
