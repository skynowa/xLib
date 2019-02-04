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
enum class TestType
{
	Unknown = 0,
	First   = 1,
	Second  = 2,
	Third   = 3,
	Last    = Third + 1
};
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Enum::unit()
{
    xTEST_CASE("toString")
    {
        m_sRv = Enum<TestType>::toString(TestType::First);
        xTEST_EQ(m_sRv, std::tstring_t(xT("1")));
    }

    xTEST_CASE("fromString")
    {
        auto arv = Enum<TestType>::fromString(xT("2"));
        xTEST_EQ((int)arv, (int)TestType::Second);
    }

    xTEST_CASE("inc/dec")
    {
        TestType eRv = TestType::Unknown;

        eRv = Enum<TestType>::inc(eRv);
        xTEST_EQ((int)eRv, (int)TestType::First);

        eRv = Enum<TestType>::dec(eRv);
        xTEST_EQ((int)eRv, (int)TestType::Unknown);
    }

    xTEST_CASE("operator <<")
    {
    #if 0
        const size_t enumSize = 5;
        const EnumArray<TestType, enumSize> enums;

        std::stringstream ss;
        for (size_t i = 0; i < enums.size(); ++ i) {
            ss << enums[i];
        }
        xTEST_EQ(ss.str(), std::tstring_t(xT("01234")));

        std::stringstream ssC11;
        for (auto &it_enum : enums) {
            ssC11 << it_enum;
        }
        xTEST_EQ(ssC11.str(), std::tstring_t(xT("01234")));
    #endif
    }

    /**************************************************************************************************
    *   Operators
    *
    **************************************************************************************************/

    enum class Type
    {
        Zero  = 0,
        One   = 1,
        Two   = 2,
        Three = 3
    };

    xTEST_CASE("Operators::operator ++")
    {
        Type t {Type::Zero};
        ++ t;
        xTEST_EQ((int_t)t, (int_t)Type::One);
    }

    xTEST_CASE("Operators::operator --")
    {
        Type t {Type::Three};
        -- t;
        xTEST_EQ((int_t)t, (int_t)Type::Two);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
