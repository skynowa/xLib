/**
 * \file   Test_Sleeper.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
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
        xTEST(!m_bRv);
    }

    xTEST_CASE("sleep")
    {
        Sleeper objSleeper;

        for (size_t i = 0; i < 3; ++ i) {
            m_bRv = objSleeper.isSleeping();
            xTEST(!m_bRv);

            objSleeper.sleep(5);

            m_bRv = objSleeper.isSleeping();
            xTEST(!m_bRv);

            m_bRv = objSleeper.isSleeping();
            xTEST(!m_bRv);
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
