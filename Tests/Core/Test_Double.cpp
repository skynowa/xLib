/**
 * \file  Test_Double.cpp
 * \brief test Double
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
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

	xTEST_CASE("operator ==, !=")
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

		for (const auto &it_data : data) {
			const ddouble_t f(it_data.test1);

			// ==
			m_bRv = (f == it_data.test2);
			xTEST(m_bRv == it_data.expect);

			// !=
			m_bRv = (f != it_data.test2);
			xTEST(m_bRv != it_data.expect);

			m_bRv = (ddouble_t::isEqual(it_data.test1, it_data.test2));
			xTEST(m_bRv == it_data.expect);
		}
	}

	xTEST_CASE("operator <, >")
	{
		const Data3<double_t, double_t, bool_t> data[]
		{
			{10.5,   11.0,   true},
			{10.0,   10.0,   false},
			{10.4,   10.0,   false},
			{0.0,    0.0,    false},
			{-10.4, -10.0,   true},
			{-10.4, -10.4,   false},
			{-10.5, -11.0,   false},
			{-10.6, -11.0,   false},
			{994.11, 995.07, true},
			{84.71,  84.71,  false}
		};

		for (const auto &it_data : data) {
			const ddouble_t f(it_data.test1);

			// <
			m_bRv = (f < it_data.test2);
			xTEST(m_bRv == it_data.expect);

			// >
			m_bRv = (f >= it_data.test2);
			xTEST(m_bRv != it_data.expect);
		}
	}

	xTEST_CASE("operator <=, >=")
	{
		const Data3<double_t, double_t, bool_t> data[]
		{
			{10.5,   11.0,   true},
			{10.0,   10.0,   true},
			{10.4,   10.0,   false},
			{0.0,    0.0,    true},
			{-10.4, -10.0,   true},
			{-10.4, -10.4,   true},
			{-10.5, -11.0,   false},
			{-10.6, -11.0,   false},
			{994.11, 995.07, true},
			{84.71,  84.71,  true}
		};

		for (const auto &it_data : data) {
		  const ddouble_t f(it_data.test1);

		  // <=
		  m_bRv = (f <= it_data.test2);
		  xTEST(m_bRv == it_data.expect);

		  // >=
		  m_bRv = (f > it_data.test2);
		  xTEST(m_bRv != it_data.expect);
		}
	}

	xTEST_CASE("operator = ")
	{
		cdouble_t test {7.0};

		ddouble_t value(test);

		ddouble_t d;
		d = value;
		xTEST(d == test);

		d = std::move(value);
		xTEST(d == test);
	}

	xTEST_CASE("isEqual")
	{
		cdouble_t data[][3]
		{
			{10.5,   11.0, 0.0},
			{10.0,   10.0, 1.0},
			{10.4,   10.0, 0.0},
			{0.0,    0.0,  1.0},
			{-10.4, -10.0, 0.0},
			{-10.4, -10.4, 1.0},
			{-10.5, -11.0, 0.0},
			{-10.6, -11.0, 0.0}
		};

		for (const auto &it_data : data) {
			const auto bRv = static_cast<bool_t>( it_data[2] );
			m_bRv = ddouble_t::isEqual(it_data[0], it_data[1]);
			xTEST_EQ(m_bRv, bRv);
		}
	}

	xTEST_CASE("get")
	{
		ddouble_t d(11.55);
		xTEST(ddouble_t(d.get()) == 11.55);
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
