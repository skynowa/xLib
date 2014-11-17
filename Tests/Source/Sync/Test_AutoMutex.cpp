/**
 * \file   Test_AutoMutex.cpp
 * \brief
 */


#include <Test/Sync/Test_AutoMutex.h>

#include <xLib/Sync/Mutex.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_AutoMutex::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("AutoMutex", a_caseLoops)
    {
        size_t  uiCounter = 0;
        Mutex mtMutex;

        {
            AutoMutex amtAutoMutex(&mtMutex);

            for (size_t i = 0; i < 10; ++ i) {
                ++ uiCounter;
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------
