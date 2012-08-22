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
/*virtual*/
bool
CxTest_CxSleeper::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    //bIsSleeping
    xTEST_CASE(cullCaseLoops)
    {
        CxSleeper objSleeper;

        m_bRv = objSleeper.bIsSleeping();
        xTEST_EQ(false, m_bRv);
    }

    //--------------------------------------------------
    //bSleep
    xTEST_CASE(cullCaseLoops)
    {
        CxSleeper objSleeper;

        for (size_t i = 0; i < 3; ++ i) {
            m_bRv = objSleeper.bIsSleeping();
            xTEST_EQ(false, m_bRv);

            m_bRv = objSleeper.bSleep(5);
            xTEST_EQ(true, m_bRv);

            m_bRv = objSleeper.bIsSleeping();
            xTEST_EQ(false, m_bRv);

            m_bRv = objSleeper.bIsSleeping();
            xTEST_EQ(false, m_bRv);
        }
    }

    //--------------------------------------------------
    //bWakeUp
    xTEST_CASE(cullCaseLoops)
    {
        #if xTODO
            CxSleeper objSleeper;

            m_bRv = objSleeper.bWakeUp();
            xTEST_EQ(true, m_bRv);
        #endif
    }

    return true;
}
//---------------------------------------------------------------------------
