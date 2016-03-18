/**
 * \file   Test_Dll.cpp
 * \brief
 */


#include <Test/IO/Test_Dll.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Dll)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Dll::unit(
    culonglong_t &a_caseLoops
)
{
    // TEST: Test_Dll()

    xTEST_CASE("Dll", a_caseLoops)
    {
        #if   xENV_WIN
            const data2_tstring_t data[] = {
                {xT("kernel32.dll"), xT("Beep")}
            };
        #elif xENV_UNIX
            #if xOS_FREEBSD
                // TEST: if -static Dll::load() don't load any 'so'-libraries
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
            Dll dll;

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
        #if   xENV_WIN
            Dll::proc_address_t paRv = dll.procAddress(data[i].expect);
            xTEST_PTR(paRv);

            typedef void_t (__stdcall *ptr_dll_func_t)(ulong_t, ulong_t);
            ptr_dll_func_t loadBeep = (ptr_dll_func_t)paRv;

            loadBeep(1, 1);
        #elif xENV_UNIX
            Dll::proc_address_t paRv = dll.procAddress(data[i].expect);
            xTEST_PTR(paRv);

            typedef double (*ptr_dll_func_t)(double);
            ptr_dll_func_t cosine = (ptr_dll_func_t)paRv;

            double dRv = cosine(2.0);
            xUNUSED(dRv);
            // TEST: Test_Dll::unit() - procAddress
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
