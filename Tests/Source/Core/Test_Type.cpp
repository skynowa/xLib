/**
 * \file   Test_Type.cpp
 * \brief
 */


#include <Test/Core/Test_Type.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Type)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Type::unit(
    std::csize_t &a_caseLoops
)
{
    xTEST_CASE("name", a_caseLoops)
    {
        std::tstring_t sObject;

        m_sRv = Type::name(sObject);
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("rawName", a_caseLoops)
    {
        std::tstring_t sObject;

        m_sRv = Type::rawName(sObject);
        xTEST_EQ(false, m_sRv.empty())
    }

    xTEST_CASE("isEquals", a_caseLoops)
    {
        std::string  sObject1;
        std::wstring wsObject2;

        m_bRv = Type::isEquals(sObject1, wsObject2);
        xTEST_EQ(m_bRv, false);
    }
}
//-------------------------------------------------------------------------------------------------
