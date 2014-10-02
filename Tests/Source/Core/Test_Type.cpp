/**
 * \file   Test_Type.cpp
 * \brief
 */


#include <Test/Core/Test_Type.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Type::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("Type::name", a_caseLoops)
    {
        std::tstring_t sObject;

        m_sRv = Type::name(sObject);
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("Type::rawName", a_caseLoops)
    {
        std::tstring_t sObject;

        m_sRv = Type::rawName(sObject);
        xTEST_EQ(false, m_sRv.empty())
    }

    xTEST_CASE("Type::isEquals", a_caseLoops)
    {
        std::string  sObject1;
        std::wstring wsObject2;

        m_bRv = Type::isEquals(sObject1, wsObject2);
        xTEST_EQ(m_bRv, false);
    }
}
//-------------------------------------------------------------------------------------------------
