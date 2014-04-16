/**
 * \file   CxTest_CxSleeper.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxSleeper.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxSleeper::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxSleeper::isSleeping", a_caseLoops)
    {
        CxSleeper objSleeper;

        m_bRv = objSleeper.isSleeping();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("CxSleeper::sleep", a_caseLoops)
    {
        CxSleeper objSleeper;

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

    xTEST_CASE("CxSleeper::wakeUp", a_caseLoops)
    {
        // TEST: CxSleeper::wakeUp()
        #if xTODO
            CxSleeper objSleeper;

            objSleeper.wakeUp();
        #endif
    }
}
//-------------------------------------------------------------------------------------------------
