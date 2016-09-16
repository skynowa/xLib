/**
 * \file   Test_Type.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xlib;

xTEST_CLASS(Test_Type)
xTEST_UNIT(Test_Type)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Type::unit()
{
    xTEST_CASE("name")
    {
        std::tstring_t sObject;

        m_sRv = Type::name(sObject);
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("rawName")
    {
        std::tstring_t sObject;

        m_sRv = Type::rawName(sObject);
        xTEST_EQ(false, m_sRv.empty())
    }

    xTEST_CASE("isEquals")
    {
        std::string  sObject1;
        std::wstring wsObject2;

        m_bRv = Type::isEquals(sObject1, wsObject2);
        xTEST_EQ(m_bRv, false);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
