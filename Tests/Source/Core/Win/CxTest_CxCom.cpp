/**
 * \file   CxTest_CxCom.cpp
 * \brief
 */


#include <Test/Core/Win/CxTest_CxCom.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxCom::unit(
    culonglong_t &a_cullCaseLoops
)
{
#if xOS_ENV_WIN

    xTEST_CASE("CxCom::CxCom", a_cullCaseLoops)
    {
        const COINIT ccmModel[] = {
            COINIT_APARTMENTTHREADED,
            COINIT_MULTITHREADED,
            COINIT_DISABLE_OLE1DDE,
            COINIT_SPEED_OVER_MEMORY
        };

        for (size_t i = 0; i < xARRAY_SIZE(ccmModel) - 1; ++ i) {
            CxCom cmCom1(ccmModel[i]);
            CxCom cmCom2(ccmModel[i]);
            CxCom cmCom3(ccmModel[i]);
        }
    }

#endif
}
//------------------------------------------------------------------------------
