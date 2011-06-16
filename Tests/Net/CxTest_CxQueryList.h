/****************************************************************************
* Class name:  CxTest_CxQueryList
* Description: test CxQueryList
* File name:   CxTest_CxQueryList.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxQueryListH
#define CxTest_CxQueryListH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxQueryList.h>
//---------------------------------------------------------------------------
class CxTest_CxQueryList :
    public CxTest
{
	public:
		CxTest_CxQueryList();
		virtual     ~CxTest_CxQueryList();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxQueryList (constructor)
CxTest_CxQueryList::CxTest_CxQueryList() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxQueryList (destructor)
CxTest_CxQueryList::~CxTest_CxQueryList() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxQueryList::bUnit() {
	std::string sQueryStr = "-----------------------------7d89c2f80530\nContent-Disposition: form-data; name=\"inpLogin\"\n\nAlca\n-----------------------------7d89c2f80530\nContent-Disposition: form-data; name=\"inpPin\"\n\n1111\n-----------------------------7d89c2f80530\nContent-Disposition: form-data; name=\"inpId\"\n\n%235%119%89%85%119%74%188%59\n-----------------------------7d89c2f80530\nContent-Disposition: form-data; name=\"inpServId\"\n\nxxx\n-----------------------------7d89c2f80530\nContent-Disposition: form-data; name=\"btnSubmit\"\n\nÂîéòè\n-----------------------------7d89c2f80530--\nck;\usr\local\php5;d:\_";


	CxQueryList qlQL(sQueryStr);
	MessageBox(0, qlQL.sGetParamByName("inpLogin").c_str(),  "", MB_OK);
	MessageBox(0, qlQL.sGetParamByName("inpPin").c_str(),    "", MB_OK);
	MessageBox(0, qlQL.sGetParamByName("inpId").c_str(),     "", MB_OK);
	MessageBox(0, qlQL.sGetParamByName("inpServId").c_str(), "", MB_OK);
	MessageBox(0, qlQL.sGetParamByName("btnSubmit").c_str(), "", MB_OK);

	std::size_t uiLen = qlQL.uiGetCountParam();

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxQueryListH

