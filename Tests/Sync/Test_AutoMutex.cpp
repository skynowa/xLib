/**
 * \file   Test_AutoMutex.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_AutoMutex)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_AutoMutex::unit()
{
    xTEST_CASE("ctor")
    {
        size_t counter {};
        Mutex  mutex;

        {
            AutoMutex autoMutex(&mutex);

            for (size_t i = 0; i < 10; ++ i) {
                ++ counter;
            }
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
