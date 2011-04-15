/****************************************************************************
* Class name:  CxTest_CxComPort
* Description: test CxComPort
* File name:   CxTest_CxComPort.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxTest_CxComPortH
#define CxTest_CxComPortH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/Win/CxComPort.h>
//---------------------------------------------------------------------------
class CxTest_CxComPort : public CxTest {
	public:
		CxTest_CxComPort();
	   ~CxTest_CxComPort();

	   /*virtual*/ BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxComPort (comment)
CxTest_CxComPort::CxTest_CxComPort() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxComPort (comment)
CxTest_CxComPort::~CxTest_CxComPort() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL CxTest_CxComPort::bUnit() {
	/*DEBUG*/

	//////-------------------------------------
	//////[FUNCTION_NAME]
	////{
	////	tString sTestData[][2] = {
	////		{_T("TEST_STRING_1"),		 _T("MUST_BE_1")},
	////		{_T("TEST_STRING_2"),		 _T("MUST_BE_2")},
	////		{_T("TEST_STRING_3"),		 _T("MUST_BE_3")},
	////		{_T("TEST_STRING_4"),		 _T("MUST_BE_4")}
	////	};

	////	for (std::size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
	////		////tString sStr1 = [FUNCTION_NAME](sTestData[i][0]);
	////		////tString sStr2 = [FUNCTION_NAME](sTestData[i][1]);
	////		////XASSERT(sStr1 == sStr2);

	////		////tString sStr3 = [FUNCTION_NAME](sTestData[i][0]);
	////		////tString sStr4 = sTestData[i][1];
	////		////XASSERT(sStr3 == sStr4);
	////	}
	////}

	return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxComPortH

