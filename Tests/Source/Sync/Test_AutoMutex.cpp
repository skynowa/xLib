/**
 * \file   Test_AutoMutex.cpp
 * \brief
 */


#include <Test/Sync/Test_AutoMutex.h>

#include <xLib/Sync/Mutex.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_AutoMutex)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_AutoMutex::unit()
{
    xTEST_CASE("AutoMutex")
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

    return true;
}
//-------------------------------------------------------------------------------------------------
