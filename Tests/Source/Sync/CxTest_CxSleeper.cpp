/****************************************************************************
* Class name:  CxTest_CxSleeper
* Description: test CxSleeper
* File name:   CxTest_CxSleeper.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Sync/CxTest_CxSleeper.h>


//---------------------------------------------------------------------------
CxTest_CxSleeper::CxTest_CxSleeper() {

}
//---------------------------------------------------------------------------
CxTest_CxSleeper::~CxTest_CxSleeper() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
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
        xTEST_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bSleep
    xTEST_BLOCK(cullBlockLoops)
    {
        CxSleeper objSleeper;

        for (size_t i = 0; i < 3; ++ i) {
            m_bRes = objSleeper.bIsSleeping();
            xTEST_EQ(FALSE, m_bRes);

            m_bRes = objSleeper.bSleep(5);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = objSleeper.bIsSleeping();
            xTEST_EQ(FALSE, m_bRes);

            m_bRes = objSleeper.bIsSleeping();
            xTEST_EQ(FALSE, m_bRes);
        }
    }

    //--------------------------------------------------
    //bWakeUp
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            CxSleeper objSleeper;

            m_bRes = objSleeper.bWakeUp();
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    return TRUE;
}
//---------------------------------------------------------------------------
