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
		dfloat_t f(1.0);
		xUNUSED(f);

		ddouble_t d(1.0);
		xUNUSED(d);

		dlongdouble_t l(1.0);
		xUNUSED(l);
    }

    xTEST_CASE("operators")
    {
		ddouble_t d(7.0);
		xTEST(d.isEqual(7.0));

		// TODO: tests
    }

    xTEST_CASE("isEqual")
    {
		const Data3<float_t, float_t, bool_t> data[]
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
			dfloat_t f(it_data.test1);

			m_bRv = f.isEqual(it_data.test2);
			xTEST(m_bRv == it_data.expect);
		}
    }

    xTEST_CASE("isNull")
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
