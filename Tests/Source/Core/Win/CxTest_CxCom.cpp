/**
 * \file   CxTest_CxCom.cpp
 * \brief
 */


#include <Test/Core/Win/CxTest_CxCom.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxCom::unit(
    culonglong_t &a_caseLoops
)
{
#if xOS_ENV_WIN
    xTEST_CASE("CxCom::CxCom", a_caseLoops)
    {
        const COINIT model[] = {
            COINIT_APARTMENTTHREADED,
            COINIT_MULTITHREADED,
            COINIT_DISABLE_OLE1DDE,
            COINIT_SPEED_OVER_MEMORY
        };

        for (size_t i = 0; i < xARRAY_SIZE(model) - 1; ++ i) {
            CxCom com1(model[i]);
            CxCom com2(model[i]);
            CxCom com3(model[i]);
        }
    }
#else
    xUNUSED(a_caseLoops);
#endif
}
//-------------------------------------------------------------------------------------------------
