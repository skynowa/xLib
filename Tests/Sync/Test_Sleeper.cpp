/**
 * \file   Test_Sleeper.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Sleeper)
xTEST_UNIT(Test_Sleeper)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Sleeper::unit()
{
    xTEST_CASE("isSleeping")
    {
        Sleeper objSleeper;

        m_bRv = objSleeper.isSleeping();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("sleep")
    {
        Sleeper objSleeper;

        for (size_t i = 0; i < 3; ++ i) {
            m_bRv = objSleeper.isSleeping();
            xTEST_EQ(m_bRv, false);

            objSleeper.sleep(5);

            m_bRv = objSleeper.isSleeping();
            xTEST_EQ(m_bRv, false);

            m_bRv = objSleeper.isSleeping();
            xTEST_EQ(m_bRv, false);
        }
    }

    xTEST_CASE("wakeUp")
    {
        // TEST: Sleeper::wakeUp()
        #if xTODO
            Sleeper objSleeper;

            objSleeper.wakeUp();
        #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
