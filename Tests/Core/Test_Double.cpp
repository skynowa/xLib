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
		ddouble_t d;
		xTEST_EQ(d, 0.0);
		xTEST(d.isNull());
	}

	xTEST_CASE("Double(const T)")
	{
		ddouble_t f(5.75);
		xTEST_EQ(f, 5.75);
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
			xTEST_EQ(m_bRv, it_data.expect);

			// !=
			m_bRv = (f != it_data.test2);
			xTEST_DIFF(m_bRv, it_data.expect);

			m_bRv = (ddouble_t::isEqual(it_data.test1, it_data.test2));
			xTEST_EQ(m_bRv, it_data.expect);
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
			xTEST_EQ(m_bRv, it_data.expect);

			// >
			m_bRv = (f >= it_data.test2);
			xTEST_DIFF(m_bRv, it_data.expect);
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
			xTEST_EQ(m_bRv, it_data.expect);

			// >=
			m_bRv = (f > it_data.test2);
			xTEST_DIFF(m_bRv, it_data.expect);
		}
	}

	xTEST_CASE("operator = ")
	{
		cdouble_t test {7.0};

		ddouble_t value(test);

		ddouble_t d;
		d = value;
		xTEST_EQ(d, test);

		d = std::move(value);
		xTEST_EQ(d, test);

		d = 0.0;
		xTEST(d.isNull());
	}

	xTEST_CASE("operator = (const T )")
	{
		cdouble_t test {7.0};

		ddouble_t value;
		value = test;
		xTEST_EQ(value, test);
	}

	xTEST_CASE("isEqual")
	{
		// #1
		{
			struct Data
			{
				double value1;
				double value2;
				bool   expected;
			};

			const Data data[]
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
				m_bRv = ddouble_t::isEqual(it_data.value1, it_data.value2);
				xTEST_EQ(m_bRv, it_data.expected);
			}
		}

		// #2
		{
			const double dRv1 = 112.57 / 67.54;
			const double dRv2 = (double)11257 / 6754;
			xTEST(ddouble_t::isEqual(dRv1, dRv2));
		}
	}

	xTEST_CASE("get")
	{
		ddouble_t d(11.55);
		xTEST_EQ(ddouble_t(d.get()), 11.55);
	}

	/// [TEST] Determines

	xTEST_CASE("isNull")
	{
		ddouble_t d(0.0);
		xTEST(d.isNull());

		ddouble_t d2(0.000001);
		xTEST(!d2.isNull());
	}

	xTEST_CASE("safeDiv")
	{
		ddouble_t d(10.0);

		ddouble_t dRv( d.safeDiv(0.0) );
		xTEST(dRv.isNull());
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
