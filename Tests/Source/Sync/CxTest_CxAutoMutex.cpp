/**
 * \file   CxTest_CxAutoMutex.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxAutoMutex.h>

#include <xLib/Sync/CxMutex.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxAutoMutex::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxAutoMutex::CxAutoMutex", a_caseLoops)
    {
        size_t  uiCounter = 0;
        CxMutex mtMutex;

        {
            CxAutoMutex amtAutoMutex(&mtMutex);

            for (size_t i = 0; i < 10; ++ i) {
                ++ uiCounter;
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------
