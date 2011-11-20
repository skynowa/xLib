/**
 * \file   CxTest_CxHttpClient.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxHttpClient.h>


//---------------------------------------------------------------------------
CxTest_CxHttpClient::CxTest_CxHttpClient() {

}
//---------------------------------------------------------------------------
CxTest_CxHttpClient::~CxTest_CxHttpClient() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxHttpClient::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    xTEST_BLOCK(cullBlockLoops)
    {
        CxHttpClient hcHttpClient;
    }

    return true;
}
//---------------------------------------------------------------------------
