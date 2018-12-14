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

    xTEST_CASE("operator =")
    {
		ddouble_t d(7.0);
		xTEST(d.isEqual(7.0));
    }

    xTEST_CASE("isEqual")
    {
    	ddouble_t d(1.0);
        xTEST(d.isEqual(1.0));
    }

    xTEST_CASE("isAlmostEqual")
    {
    	ddouble_t d(1.0);
    	xTEST(d.isAlmostEqual(1.0));
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
