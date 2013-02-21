/**
 * \file   CxTest_CxAutoMutex.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxAutoMutex.h>

#include <xLib/Sync/CxMutex.h>


//------------------------------------------------------------------------------
CxTest_CxAutoMutex::CxTest_CxAutoMutex() {

}
//------------------------------------------------------------------------------
CxTest_CxAutoMutex::~CxTest_CxAutoMutex() {

}
//------------------------------------------------------------------------------
/* virtual */
void
CxTest_CxAutoMutex::unit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxAutoMutex::CxAutoMutex", cullCaseLoops)
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
//------------------------------------------------------------------------------
