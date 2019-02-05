/**
 * \file   Test_EnumArray.cpp
 * \brief  test EnumArray
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_EnumArray)
xTEST_UNIT(Test_EnumArray)
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
Test_EnumArray::unit()
{
    const EnumArray<TestType, 5> enums(
        {
            TestType::Unknown,
            TestType::First,
            TestType::Second,
            TestType::Third,
            TestType::Last
        }
    );

    xTEST_CASE("isValid")
    {
        m_bRv = enums.isValid(0);
        xTEST(m_bRv);

        m_bRv = enums.isValid(10);
        xTEST(!m_bRv);
    }

    xTEST_CASE("operator <<")
    {
        std::tstringstream_t ss;
        ss << enums;
        xTEST_EQ(ss.str(), std::tstring_t(xT("0,1,2,3,4")));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
