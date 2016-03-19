/**
 * \file   Test_Sleeper.cpp
 * \brief
 */


#include <Test/Sync/Test_Sleeper.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Sleeper)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Sleeper::unit(
    std::csize_t &a_caseLoops
)
{
    xTEST_CASE("isSleeping", a_caseLoops)
    {
        Sleeper objSleeper;

        m_bRv = objSleeper.isSleeping();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("sleep", a_caseLoops)
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

    xTEST_CASE("wakeUp", a_caseLoops)
    {
        // TEST: Sleeper::wakeUp()
        #if xTODO
            Sleeper objSleeper;

            objSleeper.wakeUp();
        #endif
    }
}
//-------------------------------------------------------------------------------------------------
