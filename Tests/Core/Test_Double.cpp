/**
 * \file   Test_Double.cpp
 * \brief  test Double
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Double)
xTEST_UNIT(Test_Double)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Double::unit()
{
    xTEST_CASE("Double")
    {
		ddouble_t d(1.0);
		xTEST(d == 1.0);
    }

    xTEST_CASE("Double(const T)")
    {
		ddouble_t f = 5.75;
		xTEST(f == 5.75);
    }

    xTEST_CASE("operators")
    {
		ddouble_t d(7.0);
		xTEST(d == 7.0);

		// TODO: tests
    }

    xTEST_CASE("operator = ")
    {
		ddouble_t d;
		d = 7.0;
		xTEST(d == 7.0);
    }

    xTEST_CASE("operator ==")
    {
		const Data3<double_t, double_t, bool_t> data[]
		{
			{10.5,   11.0,   false},
			{10.0,   10.0,   true},
			{10.4,   10.0,   false},
			{0.0,    0.0,    true},
			{-10.4, -10.0,   false},
			{-10.4, -10.4,   true},
			{-10.5, -11.0,   false},
			{-10.6, -11.0,   false},
			{994.11, 995.07, false},
			{84.71,  84.71,  true}
		};

		for (auto &it_data : data) {
			ddouble_t f(it_data.test1);

			m_bRv = (f == it_data.test2);
			xTEST(m_bRv == it_data.expect);
		}
    }

    xTEST_CASE("get")
    {
    	ddouble_t d(11.55);
    	xTEST(ddouble_t(d.get()) == 11.55);
    }

    {
    	ddouble_t d(0.0);
    	xTEST(d.isNull());
    }

    xTEST_CASE("safeDiv")
    {
    	ddouble_t d(10.0);

    	ddouble_t dRv( d.safeDiv(0.0) );
    	xTEST(dRv.isNull());
    }

    xTEST_CASE("clear")
    {
		ddouble_t d(10.0);
		d.clear();

    	xTEST(d.isNull());
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
