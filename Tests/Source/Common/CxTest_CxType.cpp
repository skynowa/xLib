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
bool
CxTest_CxType::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //-------------------------------------
    //sGetName
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sObject;

        m_sRv = CxType::sGetName(sObject);
        xTEST_EQ(false, m_sRv.empty());
    }

    //-------------------------------------
    //sGetRawName
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sObject;

        m_sRv = CxType::sGetRawName(sObject);
        xTEST_EQ(false, m_sRv.empty())
    }

    //-------------------------------------
    //bIsEquals
    xTEST_CASE(cullCaseLoops)
    {
         std::string  sObject1;
        std::wstring sObject2;

        m_bRv = CxType::bIsEquals(sObject1, sObject2);
        xTEST_EQ(false, m_bRv);
    }

    return true;
}
//---------------------------------------------------------------------------
