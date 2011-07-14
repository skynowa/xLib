/****************************************************************************
* Class name:  CxTest_CxHttpClient
* Description: test CxHttpClient
* File name:   CxTest_CxHttpClient.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Net/CxTest_CxHttpClient.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxHttpClient (constructor)
CxTest_CxHttpClient::CxTest_CxHttpClient() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxHttpClient (destructor)
CxTest_CxHttpClient::~CxTest_CxHttpClient() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxHttpClient::bUnit() {
    CxHttpClient hcHttpClient;



    return TRUE;
}
//---------------------------------------------------------------------------
