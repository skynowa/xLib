/****************************************************************************
* Class name:  CxTest_CxType
* Description: test CxType
* File name:   CxType.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     30.07.2011
*
*****************************************************************************/


#include <Test/Common/CxTest_CxType.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxType
CxTest_CxType::CxTest_CxType() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxType
CxTest_CxType::~CxTest_CxType() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxType::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //-------------------------------------
    //sGetName
    xTEST_BLOCK(cullBlockLoops)
    {
        tString sObject;

	    m_sRes = CxType::sGetName(sObject);
        xASSERT_EQUAL(false, m_sRes.empty());
    }

    //-------------------------------------
    //sGetRawName
    xTEST_BLOCK(cullBlockLoops)
    {
	    tString sObject;

        m_sRes = CxType::sGetRawName(sObject);
        xASSERT_EQUAL(false, m_sRes.empty())
    }

    //-------------------------------------
    //bIsEquals
    xTEST_BLOCK(cullBlockLoops)
    {
 	    std::string  sObject1;
        std::wstring sObject2;

	    m_bRes = CxType::bIsEquals(sObject1, sObject2);
        xASSERT_EQUAL(FALSE, m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
