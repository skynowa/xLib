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

#if 0

std::tostream_t &
operator << (std::tostream_t &out_os, const TestType a_value)
{
	out_os << static_cast<::ssize_t>(a_value);

	return out_os;
}

#endif
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
        const Enum<TestType> first(TestType::First);

        std::tstringstream_t ss;
        ss << first;
        xTEST_EQ(ss.str(), std::tstring_t(xT("First: 1")));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
