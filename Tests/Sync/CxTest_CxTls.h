/****************************************************************************
* Class name:  CxTest_CxTls
* Description: test CxTls
* File name:   CxTest_CxTls.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxTlsH
#define CxTest_CxTlsH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxTls.h>
//---------------------------------------------------------------------------
class CxTest_CxTls :
    public CxTest
{
	public:
		CxTest_CxTls();
		virtual     ~CxTest_CxTls();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxTls (constructor)
CxTest_CxTls::CxTest_CxTls() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxTls (destructor)
CxTest_CxTls::~CxTest_CxTls() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxTls::bUnit() {
	//-------------------------------------
	//[FUNCTION_NAME]
	{
		CxTls objTls;



		tString sTestData[][2] = {
				{_T("TEST_STRING_1"),		 _T("MUST_BE_1")},
				{_T("TEST_STRING_2"),		 _T("MUST_BE_2")},
				{_T("TEST_STRING_3"),		 _T("MUST_BE_3")},
				{_T("TEST_STRING_4"),		 _T("MUST_BE_4")}
		};

		for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
			////tString sStr1 = [FUNCTION_NAME](sTestData[i][0]);
			////tString sStr2 = [FUNCTION_NAME](sTestData[i][1]);
			////xASSERT(sStr1 == sStr2);

			////tString sStr3 = [FUNCTION_NAME](sTestData[i][0]);
			////tString sStr4 = sTestData[i][1];
			////xASSERT(sStr3 == sStr4);
		}
	}

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxTlsH

