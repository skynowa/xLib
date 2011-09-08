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
CxTest_CxHttpClient::CxTest_CxHttpClient() {

}
//---------------------------------------------------------------------------
CxTest_CxHttpClient::~CxTest_CxHttpClient() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxHttpClient::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    xTEST_BLOCK(cullBlockLoops)
    {
        CxHttpClient hcHttpClient;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
