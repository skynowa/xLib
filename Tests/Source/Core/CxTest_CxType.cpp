/**
 * \file   CxTest_CxType.cpp
 * \brief
 */


#include <Test/Core/CxTest_CxType.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxType::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxType::name", a_cullCaseLoops)
    {
        std::tstring_t sObject;

        m_sRv = CxType::name(sObject);
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxType::rawName", a_cullCaseLoops)
    {
        std::tstring_t sObject;

        m_sRv = CxType::rawName(sObject);
        xTEST_EQ(false, m_sRv.empty())
    }

    xTEST_CASE("CxType::isEquals", a_cullCaseLoops)
    {
        std::string  sObject1;
        std::wstring wsObject2;

        m_bRv = CxType::isEquals(sObject1, wsObject2);
        xTEST_EQ(false, m_bRv);
    }
}
//------------------------------------------------------------------------------
