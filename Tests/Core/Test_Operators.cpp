/**
 * \file   Test_Operators.cpp
 * \brief  test Operators
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Operators)
xTEST_UNIT(Test_Operators)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Operators::unit()
{
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
