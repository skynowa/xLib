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
		const data2_tstring_t data[]
		{
			{Format::str(xT("kernel32.{}"), Path::fileExt(Path::FileExt::Dll)), xT("Beep")}
		};
	#elif xENV_UNIX
		#if   xENV_LINUX
			const data2_tstring_t data[]
			{
				{Format::str(xT("libm.{}.6"), Path::fileExt(Path::FileExt::Dll)), xT("cos")}
			};
		#elif xENV_BSD
			// TEST: if -static Dll::load() don't load any 'so'-libraries
			return false;

			const data2_tstring_t data[]
			{
				{Format::str(xT("libm.{}.6"), Path::fileExt(Path::FileExt::Dll)), xT("cos")}
			};
		#elif xENV_APPLE
			const data2_tstring_t data[]
			{
				{Format::str(xT("libm.{}"), Path::fileExt(Path::FileExt::Dll)), xT("cos")}
			};
		#endif
	#endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            Dll dll(data[i].test);

            m_bRv = dll.get().isValid();
            xTEST(!m_bRv);

            // load
            dll.load();

            // isLoaded
            m_bRv = dll.get().isValid();
            xTEST(m_bRv);

            // isProcExists
            m_bRv = dll.isProcExists(data[i].expect);
            xTEST(m_bRv);

            // procAddress
        #if   xENV_WIN
            Dll::proc_address_t paRv = dll.procAddress(data[i].expect);
            xTEST_PTR(paRv);

            using ptr_dll_func_t = void_t (__stdcall *)(ulong_t, ulong_t);
            ptr_dll_func_t loadBeep = (ptr_dll_func_t)paRv;

            loadBeep(1, 1);
        #elif xENV_UNIX
            Dll::proc_address_t paRv = dll.procAddress(data[i].expect);
            xTEST_PTR(paRv);

            using ptr_dll_func_t = double (*)(double);
            ptr_dll_func_t cosine = (ptr_dll_func_t)paRv;

            const ddouble_t dRv( cosine(2.0) );
            xTEST_LESS(dRv, -0.4 /* -0.41614683654 */);
        #endif

            // isLoaded
            m_bRv = dll.get().isValid();
            xTEST(m_bRv);
        } // for (i)
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
