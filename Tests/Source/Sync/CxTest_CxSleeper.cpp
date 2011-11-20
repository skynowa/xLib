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
    const ULONGLONG cullBlockLoops
)
{
    //--------------------------------------------------
    //bIsSleeping
    xTEST_BLOCK(cullBlockLoops)
    {
        CxSleeper objSleeper;

        m_bRes = objSleeper.bIsSleeping();
        xTEST_EQ(false, m_bRes);
    }

    //--------------------------------------------------
    //bSleep
    xTEST_BLOCK(cullBlockLoops)
    {
        CxSleeper objSleeper;

        for (size_t i = 0; i < 3; ++ i) {
            m_bRes = objSleeper.bIsSleeping();
            xTEST_EQ(false, m_bRes);

            m_bRes = objSleeper.bSleep(5);
            xTEST_DIFF(false, m_bRes);

            m_bRes = objSleeper.bIsSleeping();
            xTEST_EQ(false, m_bRes);

            m_bRes = objSleeper.bIsSleeping();
            xTEST_EQ(false, m_bRes);
        }
    }

    //--------------------------------------------------
    //bWakeUp
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            CxSleeper objSleeper;

            m_bRes = objSleeper.bWakeUp();
            xTEST_DIFF(false, m_bRes);
        #endif
    }

    return true;
}
//---------------------------------------------------------------------------
