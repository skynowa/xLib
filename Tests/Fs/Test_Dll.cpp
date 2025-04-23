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
		const auto &dllName  = it_data.test;
		const auto &funcName = it_data.expect;

		Dll dll(dllName);

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
			using func_t = void_t (__stdcall *)(ulong_t, ulong_t);
			auto func = dll.symbol<func_t>(funcName);

			func(1, 1);
		#elif xENV_UNIX
			#if 0
				using func_t = double (*)(double);
				auto func = dll.symbol<func_t>(funcName);

				const FDouble dRv( func(2 * M_PI) );
				xTEST_EQ(dRv, 1.0);
			#else
				auto func = dll.symbol<double, double>(funcName);

				const FDouble dRv( func(2 * M_PI) );
				xTEST_EQ(dRv, 1.0);
			#endif
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
