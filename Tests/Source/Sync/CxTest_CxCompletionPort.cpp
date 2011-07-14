/****************************************************************************
* Class name:  CxTest_CxCompletionPort
* Description: test CxCompletionPort
* File name:   CxTest_CxCompletionPort.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Sync/CxTest_CxCompletionPort.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxCompletionPort (comment)
CxTest_CxCompletionPort::CxTest_CxCompletionPort() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxCompletionPort (comment)
CxTest_CxCompletionPort::~CxTest_CxCompletionPort() {
	//code
}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxCompletionPort::bUnit() {
	/*DEBUG*/

	//////-------------------------------------
	//////[FUNCTION_NAME]
	////{
	////	tString sTestData[][2] = {
	////		{xT("TEST_STRING_1"),		 xT("MUST_BE_1")},
	////		{xT("TEST_STRING_2"),		 xT("MUST_BE_2")},
	////		{xT("TEST_STRING_3"),		 xT("MUST_BE_3")},
	////		{xT("TEST_STRING_4"),		 xT("MUST_BE_4")}
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
