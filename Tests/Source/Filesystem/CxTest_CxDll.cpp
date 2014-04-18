/**
 * \file   CxTest_CxDll.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxDll.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxDll::unit(
    culonglong_t &a_caseLoops
)
{
    // TEST: CxTest_CxDll()

    xTEST_CASE("CxDll::CxDll", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            const data2_tstring_t data[] = {
                {xT("kernel32.dll"), xT("Beep")}
            };
        #elif xOS_ENV_UNIX
            #if xOS_FREEBSD
                // TEST: if -static CxDll::load() don't load any 'so'-libraries
                return;

                const data2_tstring_t data[] = {
                    {xT("libm.so"), xT("cos")}
                };
            #else
                const data2_tstring_t data[] = {
                    {xT("libm.so"), xT("cos")}
                };
            #endif
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            CxDll dll;

            m_bRv = dll.isLoaded();
            xTEST_EQ(m_bRv, false);

            // load
            dll.load(data[i].test);

            // isLoaded
            m_bRv = dll.isLoaded();
            xTEST_EQ(m_bRv, true);

            // isProcExists
            m_bRv = dll.isProcExists(data[i].expect);
            xTEST_EQ(m_bRv, true);

            // procAddress
        #if   xOS_ENV_WIN
            CxDll::proc_address_t paRv = dll.procAddress(data[i].expect);
            xTEST_PTR(paRv);

            typedef void_t (__stdcall *ptr_dll_func_t)(ulong_t, ulong_t);
            ptr_dll_func_t loadBeep = (ptr_dll_func_t)paRv;

            loadBeep(1, 1);
        #elif xOS_ENV_UNIX
            CxDll::proc_address_t paRv = dll.procAddress(data[i].expect);
            xTEST_PTR(paRv);

            typedef double (*ptr_dll_func_t)(double);
            ptr_dll_func_t cosine = (ptr_dll_func_t)paRv;

            double dRv = cosine(2.0);
            xUNUSED(dRv);
            // TEST: CxTest_CxDll::unit() - procAddress
            // xTEST_EQ(-0.416147, m_dRv);
            // xTRACEV(xT("\tpCosine(2.0): %f"), dRv);
        #endif

            // isLoaded
            m_bRv = dll.isLoaded();
            xTEST_EQ(m_bRv, true);
        } //for
    }
}
//-------------------------------------------------------------------------------------------------
