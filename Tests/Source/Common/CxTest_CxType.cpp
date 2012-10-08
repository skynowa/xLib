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
/* virtual */
void
CxTest_CxType::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE(CxType::sGetName, cullCaseLoops)
    {
        std::tstring_t sObject;

        m_sRv = CxType::sGetName(sObject);
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE(CxType::sGetRawName, cullCaseLoops)
    {
        std::tstring_t sObject;

        m_sRv = CxType::sGetRawName(sObject);
        xTEST_EQ(false, m_sRv.empty())
    }

    xTEST_CASE(CxType::bIsEquals, cullCaseLoops)
    {
        std::string  sObject1;
        std::wstring sObject2;

        m_bRv = CxType::bIsEquals(sObject1, sObject2);
        xTEST_EQ(false, m_bRv);
    }
}
//---------------------------------------------------------------------------
