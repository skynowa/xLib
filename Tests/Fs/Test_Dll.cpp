/**
 * \file  Test_Dll.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Dll)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Dll::unit()
{
	xTEST_CASE("sample")
	{
	#if xENV_WIN
		// TEST
	#elif xENV_UNIX
		Dll dll(xT("libm.so.6"));
		dll.load();
		xTEST(dll.isOk());

		auto func = dll.symbol<xFUNC_PTR(double, double x)>(xT("cos"));

		const FDouble dRv( func(2 * M_PI) );
		xTEST_EQ(dRv, 1.0);
	#endif
	}

	const data2_tstring_t datas[]
	{
	#if   xENV_WIN
		{Format::str(xT("kernel32.{}"), Path::fileExt(Path::FileExt::Dll)), xT("Beep")}
	#elif xENV_UNIX
		#if   xENV_LINUX
			{Format::str(xT("libm.{}.6"), Path::fileExt(Path::FileExt::Dll)), xT("cos")}
		#elif xENV_BSD
			// TEST: if -static Dll::load() don't load any 'so'-libraries
			static_assert(false);

			{Format::str(xT("libm.{}.6"), Path::fileExt(Path::FileExt::Dll)), xT("cos")}
		#elif xENV_APPLE
			{Format::str(xT("libm.{}"), Path::fileExt(Path::FileExt::Dll)), xT("cos")}
		#endif
	#endif
	};

	for (const auto &it_data : datas) {
		const auto &dllPath  = it_data.test;
		const auto &funcName = it_data.expect;

		Dll dll(dllPath);

		xTEST_CASE("ctor")
		{
			m_bRv = dll.isOk();
			xTEST(!m_bRv);
		}

		xTEST_CASE("load")
		{
			dll.load();
			xTEST(dll.isOk());
			xTEST(!!dll.isOk());
			xTEST(static_cast<bool_t>(dll));

			if (!dll) {
				xTEST(false);
			}
		}

		xTEST_CASE("isOk")
		{
			m_bRv = dll.isOk();
			xTEST(m_bRv);
			xTEST(!!dll.isOk());

			if (!dll) {
				xTEST(false);
			}
		}

		xTEST_CASE("symbol")
		{
		#if   xENV_WIN
			using func_t = xFUNC_PTR(void_t, ulong_t, ulong_t);
			auto func = dll.symbol<func_t>(funcName);

			func(1, 1);
		#elif xENV_UNIX
			using func_t = xFUNC_PTR(double, double x);
			auto func = dll.symbol<func_t>(funcName);

			const FDouble dRv( func(2 * M_PI) );
			xTEST_EQ(dRv, 1.0);
		#endif
		}

		xTEST_CASE("isOk")
		{
			m_bRv = dll.isOk();
			xTEST(m_bRv);
		}
	} // for (datas)

    return true;
}
//-------------------------------------------------------------------------------------------------
