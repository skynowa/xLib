/**
 * \file  Test_Float.cpp
 * \brief test Float
 */


#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Float)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Float::unit()
{
	xTEST_CASE("Float")
	{
		FDouble d;
		xTEST_EQ(d, 0.0);
		xTEST(d.isNull());
	}

	xTEST_CASE("Float(const T)")
	{
		FDouble f(5.75);
		xTEST_EQ(f, 5.75);

		FDouble f2( static_cast<int_t>(7) );
		xTEST_EQ(f2, 7.0);
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
			const FDouble f(it_data.test1);

			// ==
			m_bRv = (f == it_data.test2);
			xTEST_EQ(m_bRv, it_data.expect);

			// !=
			m_bRv = (f != it_data.test2);
			xTEST_DIFF(m_bRv, it_data.expect);

			m_bRv = (FDouble::isEqual(it_data.test1, it_data.test2));
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
			const FDouble f(it_data.test1);

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
			const FDouble f(it_data.test1);

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

		FDouble value(test);

		FDouble d;
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

		FDouble value;
		value = test;
		xTEST_EQ(value, test);
	}

	xTEST_CASE("isEqual")
	{
		// #1
		{
			struct Data
			{
				double_t value1;
				double_t value2;
				bool_t   expected;
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
				m_bRv = FDouble::isEqual(it_data.value1, it_data.value2);
				xTEST_EQ(m_bRv, it_data.expected);
			}
		}

		// #2
		{
			cdouble_t dRv1 = 112.57 / 67.54;
			cdouble_t dRv2 = (double_t)11257 / 6754;
			xTEST(FDouble::isEqual(dRv1, dRv2));
		}
	}

	xTEST_CASE("get")
	{
		FDouble d(11.55);
		xTEST_EQ(FDouble(d.get()), 11.55);
	}

	xTEST_CASE("operators +-*/")
	{
		FDouble dRv;

		// +
		dRv = 0.5xd + 1.5xd;
		xTEST_EQ(dRv, 2.0);

		dRv = 5xd + 1xd;
		xTEST_EQ(dRv, 6.0);

		// -
		dRv = 0.5xd - 1.5xd;
		xTEST_EQ(dRv, -1.0);

		dRv = 5xd - 1xd;
		xTEST_EQ(dRv, 4.0);

		// *
		dRv = 0.5xd * 0.5xd;
		xTEST_EQ(dRv, 0.25);

		dRv = 5xd * 5xd;
		xTEST_EQ(dRv, 25.0);

		// /
		dRv = 0.25xd / 0.5xd;
		xTEST_EQ(dRv, 0.5);

		dRv = 25xd / 5xd;
		xTEST_EQ(dRv, 5.0);
	}

	/// [TEST] Determines

	xTEST_CASE("isNull")
	{
		FDouble d(0.0);
		xTEST(d.isNull());

		FDouble d2(0.000001);
		xTEST(!d2.isNull());
	}

	xTEST_CASE("safeDiv")
	{
		FDouble d(10.0);

		FDouble dRv( d.safeDiv(0.0) );
		xTEST(dRv.isNull());
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
