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
    // hGet
    {
        CxEvent objEvent(true, true);

        #if   xOS_ENV_WIN
            xTEST_EQ(true, objEvent.hGet().bIsValid())
        #elif xOS_ENV_UNIX
            // TODO: hRv
        #endif
    }

    //-------------------------------------
    // bIsSignaled
    {
        {
            CxEvent objEvent(true, true);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(true, m_bRv);
        }

        {
            CxEvent objEvent(true, false);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(false, m_bRv);
        }
    }

    //-------------------------------------
    // bSet
    {
        const size_t cuiSpinCount = 3;


        CxEvent objEvent(true, true);

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            m_bRv = objEvent.bReset();
            xTEST_EQ(true, m_bRv);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(false, m_bRv);
        }

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            m_bRv = objEvent.bSet();
            xTEST_EQ(true, m_bRv);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(true, m_bRv);
        }
    }

    //-------------------------------------
    // bReset
    {
        const size_t cuiSpinCount = 3;


        CxEvent objEvent(true, true);

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            m_bRv = objEvent.bSet();
            xTEST_EQ(true, m_bRv);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(true, m_bRv);
        }

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            m_bRv = objEvent.bReset();
            xTEST_EQ(true, m_bRv);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(false, m_bRv);
        }
    }

    //-------------------------------------
    // bWait
    {
        {
            const bool cbIsAutoReset  = false;
            const bool cbInitialState = false;


            CxEvent objEvent(cbIsAutoReset, cbInitialState);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            CxEvent::ExObjectState osRes = objEvent.osWait(5);
            xTEST_EQ((ulong_t)CxEvent::osTimeout, (ulong_t)osRes);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(cbInitialState, m_bRv);
        }

        {
            const bool cbIsAutoReset  = true;
            const bool cbInitialState = true;


            CxEvent objEvent(cbIsAutoReset, cbInitialState);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            CxEvent::ExObjectState osRes = objEvent.osWait(50);  //BUG: objEvent.osWait(5);
            xTEST_EQ(CxEvent::osTimeout, osRes);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(false, m_bRv);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
