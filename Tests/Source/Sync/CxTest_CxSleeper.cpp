/**
 * \file   CxTest_CxSleeper.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxSleeper.h>


//---------------------------------------------------------------------------
CxTest_CxSleeper::CxTest_CxSleeper() {

}
//---------------------------------------------------------------------------
CxTest_CxSleeper::~CxTest_CxSleeper() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxSleeper::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxSleeper::bIsSleeping", cullCaseLoops)
    {
        CxSleeper objSleeper;

        m_bRv = objSleeper.bIsSleeping();
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxSleeper::vSleep", cullCaseLoops)
    {
        CxSleeper objSleeper;

        for (size_t i = 0; i < 3; ++ i) {
            m_bRv = objSleeper.bIsSleeping();
            xTEST_EQ(false, m_bRv);

            objSleeper.vSleep(5);

            m_bRv = objSleeper.bIsSleeping();
            xTEST_EQ(false, m_bRv);

            m_bRv = objSleeper.bIsSleeping();
            xTEST_EQ(false, m_bRv);
        }
    }

    xTEST_CASE("CxSleeper::vWakeUp", cullCaseLoops)
    {
        // TEST: CxSleeper::vWakeUp
        #if xTODO
            CxSleeper objSleeper;

            objSleeper.vWakeUp();
        #endif
    }
}
//---------------------------------------------------------------------------
