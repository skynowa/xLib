/**
 * \file   CxTest_CxAutoReset.cpp
 * \brief  test CxAutoReset
 */


#include <Test/Core/CxTest_CxAutoReset.h>


//---------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxAutoReset::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxAutoReset::CxAutoReset", a_caseLoops)
    {
    #if xTODO
        // TODO: CxTest_CxAutoReset
        bool data[] = {true, false, true};

        for (auto &it : data) {
            const bool origin = it;

            {
                CxAutoReset<bool> reseter(&it, false);
                xTEST_EQ(it, origin);
            }

            xTEST_EQ(it, false);
        }

        for (auto &it : data) {
            const bool origin = it;

            {
                CxAutoReset<bool> reseter(&it, true);
                xTEST_EQ(it, origin);
            }

            xTEST_EQ(it, true);
        }
    #endif
    }
}
//---------------------------------------------------------------------------
