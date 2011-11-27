/**
 * \file   CxTest_CxEvent.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxEvent.h>


//---------------------------------------------------------------------------
CxTest_CxEvent::CxTest_CxEvent() {

}
//---------------------------------------------------------------------------
CxTest_CxEvent::~CxTest_CxEvent() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxEvent::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //-------------------------------------
    //hGet
    {
        CxEvent objEvent(true, true);

        #if xOS_ENV_WIN
            xTEST_EQ(true, objEvent.hGet().bIsValid())
        #elif xOS_ENV_UNIX
            //TODO: hRes
        #endif
    }

    //-------------------------------------
    //bIsSignaled
    {
        {
            CxEvent objEvent(true, true);

            m_bRes = objEvent.bIsSignaled();
            xTEST_EQ(true, m_bRes);
        }

        {
            CxEvent objEvent(true, false);

            m_bRes = objEvent.bIsSignaled();
            xTEST_EQ(false, m_bRes);
        }
    }

    //-------------------------------------
    //bSet
    {
        const size_t cuiSpinCount = 3;


        CxEvent objEvent(true, true);

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            m_bRes = objEvent.bReset();
            xTEST_EQ(true, m_bRes);

            m_bRes = objEvent.bIsSignaled();
            xTEST_EQ(false, m_bRes);
        }

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            m_bRes = objEvent.bSet();
            xTEST_EQ(true, m_bRes);

            m_bRes = objEvent.bIsSignaled();
            xTEST_EQ(true, m_bRes);
        }
    }

    //-------------------------------------
    //bReset
    {
        const size_t cuiSpinCount = 3;


        CxEvent objEvent(true, true);

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            m_bRes = objEvent.bSet();
            xTEST_EQ(true, m_bRes);

            m_bRes = objEvent.bIsSignaled();
            xTEST_EQ(true, m_bRes);
        }

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            m_bRes = objEvent.bReset();
            xTEST_EQ(true, m_bRes);

            m_bRes = objEvent.bIsSignaled();
            xTEST_EQ(false, m_bRes);
        }
    }

    //-------------------------------------
    //bWait
    {
        {
            const bool cbIsAutoReset  = false;
            const bool cbInitialState = false;


            CxEvent objEvent(cbIsAutoReset, cbInitialState);

            m_bRes = objEvent.bIsSignaled();
            xTEST_EQ(cbInitialState, m_bRes);

            CxEvent::EObjectState osRes = objEvent.osWait(5);
            xTEST_EQ((ulong_t)CxEvent::osTimeout, (ulong_t)osRes);

            m_bRes = objEvent.bIsSignaled();
            xTEST_EQ(cbInitialState, m_bRes);
        }

        {
            const bool cbIsAutoReset  = true;
            const bool cbInitialState = true;


            CxEvent objEvent(cbIsAutoReset, cbInitialState);

            m_bRes = objEvent.bIsSignaled();
            xTEST_EQ(cbInitialState, m_bRes);

            CxEvent::EObjectState osRes = objEvent.osWait(5);

            //BUG: objEvent.osWait(5);
        #if xTODO
            xTEST_EQ((ulong_t)CxEvent::osSignaled, (ulong_t)osRes);   //LINUX   - osSignaled
                                                                  //Windows - osTimeout
        #endif
            m_bRes = objEvent.bIsSignaled();
            xTEST_EQ(false, m_bRes);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
