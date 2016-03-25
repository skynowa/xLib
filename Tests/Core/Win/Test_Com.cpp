/**
 * \file   Test_Com.cpp
 * \brief
 */


#include "Test_Com.h"

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Com)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Com::unit()
{
#if xENV_WIN
    xTEST_CASE("Com")
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
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
