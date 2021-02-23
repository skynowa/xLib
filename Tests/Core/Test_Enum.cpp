/**
 * \file   Test_Enum.cpp
 * \brief  test Enum
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
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
    xTEST_CASE("ctor")
    {
        std::ctstring_t str(xT("2"));

        Enum<TestType> e(str);
        m_sRv = e.str();
        xTEST_EQ(m_sRv, str);
    }

    xTEST_CASE("str")
    {
        m_sRv = Enum(TestType::First).str();
        xTEST_EQ(m_sRv, std::tstring_t(xT("1")));
    }

    xTEST_CASE("value")
    {
        m_ullRv = Enum(TestType::Last).value();
        xTEST_EQ(m_ullRv, 4ULL);
    }

    xTEST_CASE("name")
    {
        m_sRv = Enum(TestType::Third).name();
        xTEST_EQ(m_sRv, std::tstring_t(xT("Third")));
    }

    xTEST_CASE("inc/dec")
    {
        TestType eRv {0};

        eRv = Enum(eRv).inc().get();
        xTEST_EQ((int)eRv, (int)TestType::First);

        eRv = Enum(eRv).dec().get();
        xTEST_EQ((int)eRv, (int)TestType::Unknown);
    }

    xTEST_CASE("operator <<")
    {
    #if 0
        const size_t enumSize = 5;
        const EnumArray<TestType, enumSize> enums;

        std::stringstream ss;
        for (const auto &it_enum : enums) {
            ss << it_enum;
        }
        xTEST_EQ(ss.str(), std::tstring_t(xT("01234")));
    #else
        /// std::tcout << TestType::First << std::endl;
        /// OStream() << TestType::First << std::endl;

        /// Enum(TestType::First).print(std::cout); std::cout << std::endl;

        /// Cout xCout;
        /// Enum(TestType::Second).print(xCout); Cout() << std::endl;
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
