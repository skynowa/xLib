/****************************************************************************
* Class name:  CxTest_CxHttpClient
* Description: test CxHttpClient
* File name:   CxTest_CxHttpClient.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxHttpClientH
#define CxTest_CxHttpClientH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxHttpClient.h>
//---------------------------------------------------------------------------
class CxTest_CxHttpClient : public CxTest {
	public:
		CxTest_CxHttpClient();
		virtual     ~CxTest_CxHttpClient();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: CxTest_CxHttpClient (constructor)
CxTest_CxHttpClient::CxTest_CxHttpClient() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//TODO: ~CxTest_CxHttpClient (destructor)
CxTest_CxHttpClient::~CxTest_CxHttpClient() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxHttpClient::bUnit() {
    CxHttpClient hcHttpClient;



    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxHttpClientH

