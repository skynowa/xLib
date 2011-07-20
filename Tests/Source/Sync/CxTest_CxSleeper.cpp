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
//DONE: CxTest_CxSleeper
CxTest_CxSleeper::CxTest_CxSleeper() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxSleeper
CxTest_CxSleeper::~CxTest_CxSleeper() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxSleeper::bUnit() {
#if defined(xOS_WIN)
    CxSleeper objSleeper;

    m_bRes = objSleeper.bIsSleeping();
    xASSERT(FALSE == m_bRes);

    for (size_t i = 0; i < 10; ++ i) {
        m_bRes = objSleeper.bSleep(10);
        xASSERT(FALSE != m_bRes);

        m_bRes = objSleeper.bIsSleeping();
        xASSERT(FALSE == m_bRes);

        m_bRes = objSleeper.bIsSleeping();
        xASSERT(FALSE == m_bRes);

        #if xTODO
            m_bRes = objSleeper.bWakeUp();
            //xASSERT(FALSE != m_bRes);
        #endif
    }
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
