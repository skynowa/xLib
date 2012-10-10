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
/* virtual */
void
CxTest_CxEvent::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE(CxEvent::hGet, cullCaseLoops)
    {
        CxEvent objEvent(true, true);

        #if   xOS_ENV_WIN
            xTEST_EQ(true, objEvent.hHandle().bIsValid())
        #elif xOS_ENV_UNIX
            // TODO: hRv
        #endif
    }

    xTEST_CASE(CxEvent::bIsSignaled, cullCaseLoops)
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

    xTEST_CASE(CxEvent::vSet, cullCaseLoops)
    {
        const size_t cuiSpinCount = 3;


        CxEvent objEvent(true, true);

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            objEvent.vReset();

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(false, m_bRv);
        }

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            objEvent.vSet();

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(true, m_bRv);
        }
    }

    xTEST_CASE(CxEvent::vReset, cullCaseLoops)
    {
        const size_t cuiSpinCount = 3;


        CxEvent objEvent(true, true);

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            objEvent.vSet();

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(true, m_bRv);
        }

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            objEvent.vReset();

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(false, m_bRv);
        }
    }

    xTEST_CASE(CxEvent::vWait, cullCaseLoops)
    {
        {
            const bool cbIsAutoReset  = false;
            const bool cbInitialState = false;


            CxEvent objEvent(cbIsAutoReset, cbInitialState);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            CxEvent::ExObjectState osRes = objEvent.osWait(5);
            xTEST_EQ(CxEvent::osTimeout, osRes);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(cbInitialState, m_bRv);
        }

        {
            const bool cbIsAutoReset  = true;
            const bool cbInitialState = true;


            CxEvent objEvent(cbIsAutoReset, cbInitialState);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            CxEvent::ExObjectState osRes = objEvent.osWait(10);
            xTEST_EQ(CxEvent::osTimeout, osRes);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(false, m_bRv);
        }

        {
            const bool cbIsAutoReset  = true;
            const bool cbInitialState = false;

            CxEvent objEvent(cbIsAutoReset, cbInitialState);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            CxEvent::ExObjectState osRes = objEvent.osWait(10);
            xTEST_EQ(CxEvent::osTimeout, osRes);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(false, m_bRv);
        }

        {
            const bool cbIsAutoReset  = false;
            const bool cbInitialState = true;

            CxEvent objEvent(cbIsAutoReset, cbInitialState);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            CxEvent::ExObjectState osRes = objEvent.osWait(10);
            xTEST_EQ(CxEvent::osSignaled, osRes);

            m_bRv = objEvent.bIsSignaled();
            xTEST_EQ(true, m_bRv);
        }

    }
}
//---------------------------------------------------------------------------
