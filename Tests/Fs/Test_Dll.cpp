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
    xTEST_CASE("Dll")
    {
	#if   xENV_WIN
		const data2_tstring_t datas[]
		{
			{Format::str(xT("kernel32.{}"), Path::fileExt(Path::FileExt::Dll)), xT("Beep")}
		};
	#elif xENV_UNIX
		#if   xENV_LINUX
			const data2_tstring_t datas[]
			{
				{Format::str(xT("libm.{}.6"), Path::fileExt(Path::FileExt::Dll)), xT("cos")}
			};
		#elif xENV_BSD
			// TEST: if -static Dll::load() don't load any 'so'-libraries
			return false;

			const data2_tstring_t datas[]
			{
				{Format::str(xT("libm.{}.6"), Path::fileExt(Path::FileExt::Dll)), xT("cos")}
			};
		#elif xENV_APPLE
			const data2_tstring_t datas[]
			{
				{Format::str(xT("libm.{}"), Path::fileExt(Path::FileExt::Dll)), xT("cos")}
			};
		#endif
	#endif

        for (const auto &it_data : datas) {
            Dll dll(it_data.test);

            m_bRv = dll.get().isValid();
            xTEST(!m_bRv);

            // load
            dll.load();

            // isLoaded
            m_bRv = dll.get().isValid();
            xTEST(m_bRv);

            // isProcExists
            m_bRv = dll.isProcExists(it_data.expect);
            xTEST(m_bRv);

            // procAddress
            Dll::proc_address_t paRv = dll.procAddress(it_data.expect);
            xTEST_PTR(paRv);

        #if   xENV_WIN
            using ptr_dll_func_t = void_t (__stdcall *)(ulong_t, ulong_t);
            auto procBeep = reinterpret_cast<ptr_dll_func_t>(paRv);

            procBeep(1, 1);
        #elif xENV_UNIX
			#if 0
				using ptr_dll_func_t = double (*)(double);
				auto procCosine = reinterpret_cast<ptr_dll_func_t>(paRv);

				const FDouble dRv( procCosine(2.0) );
				xTEST_LESS(dRv, -0.4 /* -0.41614683654 */);
			#else
				using ptr_dll_func_t = double (*)(double);
				auto procCosine = dll.proc<ptr_dll_func_t>(it_data.expect);

				const FDouble dRv( procCosine(2.0) );
				xTEST_LESS(dRv, -0.4 /* -0.41614683654 */);
			#endif
        #endif

            // isLoaded
            m_bRv = dll.get().isValid();
            xTEST(m_bRv);
        } // for (datas)
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
