/****************************************************************************
* Class name:  CxTest_CxGdiplus
* Description: test CxGdiplus
* File name:   CxTest_CxGdiplus.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxTest_CxGdiplusH
#define CxTest_CxGdiplusH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Gui/Win/GDI+/CxGdiplus.h>
//---------------------------------------------------------------------------
class CxTest_CxGdiplus : public CxTest {
	public:
		CxTest_CxGdiplus();
	   ~CxTest_CxGdiplus();

	   /*virtual*/ BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxGdiplusH


/****************************************************************************
* Class name:  CxTest_CxGdiplus
* Description: test CxGdiplus
* File name:   CxTest_CxGdiplus.cpp
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxTest_CxGdiplus (comment)
CxTest_CxGdiplus::CxTest_CxGdiplus() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxGdiplus (comment)
CxTest_CxGdiplus::~CxTest_CxGdiplus() {
	//code
}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL CxTest_CxGdiplus::bUnit() {
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

