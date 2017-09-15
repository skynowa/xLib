/**
 * \file   Test_Enum.cpp
 * \brief  test Enum
 */


#include <xLib/xLib.h>
#include <initializer_list>


//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Enum)
xTEST_UNIT(Test_Enum)
//-------------------------------------------------------------------------------------------------
enum TestType
{
	ttUnknown = 0,
	ttFirst   = 1,
	ttSecond  = 2,
	ttThird   = 3,
	ttLast    = ttThird + 1
};
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Enum::unit()
{
    xTEST_CASE("Enum::Enum")
    {
        const size_t enumSize = 5;

        const Enum<TestType, enumSize> enumeration;
        xTEST_EQ(enumeration.size(), enumSize);
    }

    const Enum<TestType, 5> enumeration(
        {
            TestType::ttUnknown,
            TestType::ttFirst,
            TestType::ttSecond,
            TestType::ttThird,
            TestType::ttLast
        });

    xTEST_CASE("Enum::toString")
    {
        m_sRv = Enum<TestType, 5>::toString(TestType::ttFirst);
        xTEST_EQ(m_sRv, std::tstring_t(xT("1")));
    }

    xTEST_CASE("Enum::fromString")
    {
        TestType ttRv = Enum<TestType, 5>::fromString(xT("2"));
        xTEST_EQ(ttRv, TestType::ttSecond);
    }

    xTEST_CASE("Enum::asString")
    {
        m_sRv = Enum<TestType, 5>::asString(TestType::ttThird);
        xTEST_EQ(m_sRv, std::tstring_t(xT("ttThird")));
    }

    xTEST_CASE("Enum::isValid")
    {
        m_bRv = enumeration.isValid(0);
        xTEST_EQ(m_bRv, true);

        m_bRv = enumeration.isValid(10);
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("Enum::inc/dec")
    {
        TestType eRv = TestType::ttUnknown;

        eRv = Enum<TestType>::inc(eRv);
        xTEST_EQ(eRv, TestType::ttFirst);

        eRv = Enum<TestType>::dec(eRv);
        xTEST_EQ(eRv, TestType::ttUnknown);
    }

    xTEST_CASE("Enum::operator <<")
    {
        std::stringstream ss;
        for (size_t i = 0; i < enumeration.size(); ++ i) {
            ss << enumeration[i];
        }
        xTEST_EQ(ss.str(), std::tstring_t(xT("01234")));

        std::stringstream ssC11;
        for (auto &it_enum : enumeration) {
            ssC11 << it_enum;
        }
        xTEST_EQ(ssC11.str(), std::tstring_t(xT("01234")));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
