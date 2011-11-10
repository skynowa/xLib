/**
 * \file   CxTest_CxType.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxType.h>


//---------------------------------------------------------------------------
CxTest_CxType::CxTest_CxType() {

}
//---------------------------------------------------------------------------
CxTest_CxType::~CxTest_CxType() {

}
//---------------------------------------------------------------------------
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
        std::string_t sObject;

        m_sRes = CxType::sGetName(sObject);
        xTEST_EQ(false, m_sRes.empty());
    }

    //-------------------------------------
    //sGetRawName
    xTEST_BLOCK(cullBlockLoops)
    {
        std::string_t sObject;

        m_sRes = CxType::sGetRawName(sObject);
        xTEST_EQ(false, m_sRes.empty())
    }

    //-------------------------------------
    //bIsEquals
    xTEST_BLOCK(cullBlockLoops)
    {
         std::string  sObject1;
        std::wstring sObject2;

        m_bRes = CxType::bIsEquals(sObject1, sObject2);
        xTEST_EQ(FALSE, m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
