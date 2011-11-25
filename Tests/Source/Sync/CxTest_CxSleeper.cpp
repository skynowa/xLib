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
    const ulonglong_t cullBlockLoops
)
{
    //--------------------------------------------------
    //bIsSleeping
    xTEST_CASE(cullBlockLoops)
    {
        CxSleeper objSleeper;

        m_bRes = objSleeper.bIsSleeping();
        xTEST_EQ(false, m_bRes);
    }

    //--------------------------------------------------
    //bSleep
    xTEST_CASE(cullBlockLoops)
    {
        CxSleeper objSleeper;

        for (size_t i = 0; i < 3; ++ i) {
            m_bRes = objSleeper.bIsSleeping();
            xTEST_EQ(false, m_bRes);

            m_bRes = objSleeper.bSleep(5);
            xTEST_EQ(true, m_bRes);

            m_bRes = objSleeper.bIsSleeping();
            xTEST_EQ(false, m_bRes);

            m_bRes = objSleeper.bIsSleeping();
            xTEST_EQ(false, m_bRes);
        }
    }

    //--------------------------------------------------
    //bWakeUp
    xTEST_CASE(cullBlockLoops)
    {
        #if xTODO
            CxSleeper objSleeper;

            m_bRes = objSleeper.bWakeUp();
            xTEST_EQ(true, m_bRes);
        #endif
    }

    return true;
}
//---------------------------------------------------------------------------
