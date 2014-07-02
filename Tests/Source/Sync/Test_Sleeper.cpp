/**
 * \file   Test_Sleeper.cpp
 * \brief
 */


#include <Test/Sync/Test_Sleeper.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Sleeper::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("Sleeper::isSleeping", a_caseLoops)
    {
        Sleeper objSleeper;

        m_bRv = objSleeper.isSleeping();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("Sleeper::sleep", a_caseLoops)
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

    xTEST_CASE("Sleeper::wakeUp", a_caseLoops)
    {
        // TEST: Sleeper::wakeUp()
        #if xTODO
            Sleeper objSleeper;

            objSleeper.wakeUp();
        #endif
    }
}
//-------------------------------------------------------------------------------------------------
