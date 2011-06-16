/****************************************************************************
* Class name:  CxTest_CxCompletionPort
* Description: test CxCompletionPort
* File name:   CxTest_CxCompletionPort.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxCompletionPortH
#define CxTest_CxCompletionPortH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxCompletionPort.h>
//---------------------------------------------------------------------------
class CxTest_CxCompletionPort :
    public CxTest
{
	public:
		CxTest_CxCompletionPort();
		virtual     ~CxTest_CxCompletionPort();

		virtual     BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


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
BOOL CxTest_CxCompletionPort::bUnit() {
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
#endif //CxTest_CxCompletionPortH

