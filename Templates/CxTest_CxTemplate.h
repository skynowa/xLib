/****************************************************************************
* Class name:  CxTest_CxTemplate
* Description: test CxTemplate
* File name:   CxTemplate.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     
*
*****************************************************************************/


#ifndef CxTest_CxTemplateH
#define CxTest_CxTemplateH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//#include <xLib/CxTemplate.h>
//---------------------------------------------------------------------------
class CxTest_CxTemplate : 
    public CxTest 
{
	public:
		         CxTest_CxTemplate();
	    virtual ~CxTest_CxTemplate();

	    virtual  BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxTemplate
CxTest_CxTemplate::CxTest_CxTemplate() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxTemplate
CxTest_CxTemplate::~CxTest_CxTemplate() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxTemplate::bUnit() {


    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxTemplateH
