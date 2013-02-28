/**
 * \file   CxTest_CxSleeper.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxSleeper.h>


//------------------------------------------------------------------------------
CxTest_CxSleeper::CxTest_CxSleeper() {

}
//------------------------------------------------------------------------------
CxTest_CxSleeper::~CxTest_CxSleeper() {

}
//------------------------------------------------------------------------------
/* virtual */
void
CxTest_CxSleeper::unit(
    culonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxSleeper::isSleeping", cullCaseLoops)
    {
        CxSleeper objSleeper;

        m_bRv = objSleeper.isSleeping();
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxSleeper::sleep", cullCaseLoops)
    {
        CxSleeper objSleeper;

        for (size_t i = 0; i < 3; ++ i) {
            m_bRv = objSleeper.isSleeping();
            xTEST_EQ(false, m_bRv);

            objSleeper.sleep(5);

            m_bRv = objSleeper.isSleeping();
            xTEST_EQ(false, m_bRv);

            m_bRv = objSleeper.isSleeping();
            xTEST_EQ(false, m_bRv);
        }
    }

    xTEST_CASE("CxSleeper::wakeUp", cullCaseLoops)
    {
        // TEST: CxSleeper::vWakeUp
        #if xTODO
            CxSleeper objSleeper;

            objSleeper.wakeUp();
        #endif
    }
}
//------------------------------------------------------------------------------
