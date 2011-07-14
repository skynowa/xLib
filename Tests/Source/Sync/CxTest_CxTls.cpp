/****************************************************************************
* Class name:  CxTest_CxTls
* Description: test CxTls
* File name:   CxTest_CxTls.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Sync/CxTest_CxTls.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxTls (constructor)
CxTest_CxTls::CxTest_CxTls() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxTls (destructor)
CxTest_CxTls::~CxTest_CxTls() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxTls::bUnit() {
	//-------------------------------------
	//[FUNCTION_NAME]
	{
        #if xTODO
            CxTls objTls;
        #endif

		tString sTestData[][2] = {
				{xT("TEST_STRING_1"),		 xT("MUST_BE_1")},
				{xT("TEST_STRING_2"),		 xT("MUST_BE_2")},
				{xT("TEST_STRING_3"),		 xT("MUST_BE_3")},
				{xT("TEST_STRING_4"),		 xT("MUST_BE_4")}
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
