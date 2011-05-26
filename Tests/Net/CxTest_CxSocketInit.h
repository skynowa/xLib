/****************************************************************************
* Class name:  CxTest_CxSocketInit
* Description: test CxSocketInit
* File name:   CxTest_CxSocketInit.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxSocketInitH
#define CxTest_CxSocketInitH
//---------------------------------------------------------------------------
#include <xLib/Net/CxSocketInit.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_CxSocketInit : public CxTest {
	public:
		CxTest_CxSocketInit();
		virtual     ~CxTest_CxSocketInit();

		virtual     BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxSocketInit (comment)
CxTest_CxSocketInit::CxTest_CxSocketInit() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxSocketInit (comment)
CxTest_CxSocketInit::~CxTest_CxSocketInit() {
	//code
}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL CxTest_CxSocketInit::bUnit() {
	/*DEBUG*/

	//-------------------------------------
	//CxSocketInit
	{
		CxSocketInit siInit10(1, 0);
		CxSocketInit siInit11(1, 1);
		CxSocketInit siInit20(2, 0);
		CxSocketInit siInit21(2, 1);
		CxSocketInit siInit22(2, 2);
	}



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
#endif //CxTest_CxSocketInitH

