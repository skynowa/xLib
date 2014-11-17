/**
 * \file   Test_Com.cpp
 * \brief
 */


#include <Test/Core/Win/Test_Com.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Com::unit(
    culonglong_t &a_caseLoops
)
{
#if xENV_WIN
    xTEST_CASE("Com", a_caseLoops)
    {
        const COINIT model[] = {
            COINIT_APARTMENTTHREADED,
            COINIT_MULTITHREADED,
            COINIT_DISABLE_OLE1DDE,
            COINIT_SPEED_OVER_MEMORY
        };

        for (size_t i = 0; i < xARRAY_SIZE(model); ++ i) {
            Com com1(model[i]);
            Com com2(model[i]);
            Com com3(model[i]);
        }
    }
#else
    xUNUSED(a_caseLoops);
#endif
}
//-------------------------------------------------------------------------------------------------
