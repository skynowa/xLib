/**
 * \file   Test_Event.cpp
 * \brief
 */


#include <Test/Sync/Test_Event.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Event)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Event::unit(
    std::csize_t &a_caseLoops
)
{
    xTEST_CASE("handle", a_caseLoops)
    {
        Event objEvent(true, true);

        objEvent.create();

        #if   xENV_WIN
            xTEST_EQ(true, objEvent.handle().isValid())
        #elif xENV_UNIX
            // TEST: Test_Event() - hRv
        #endif
    }

    xTEST_CASE("isSignaled", a_caseLoops)
    {
        {
            Event objEvent(true, true);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(m_bRv, true);
        }

        {
            Event objEvent(true, false);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(m_bRv, false);
        }
    }

    xTEST_CASE("set", a_caseLoops)
    {
        std::csize_t cuiSpinCount = 3;


        Event objEvent(true, true);

        objEvent.create();

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            objEvent.reset();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(m_bRv, false);
        }

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            objEvent.set();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(m_bRv, true);
        }
    }

    xTEST_CASE("reset", a_caseLoops)
    {
        std::csize_t cuiSpinCount = 3;


        Event objEvent(true, true);

        objEvent.create();

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            objEvent.set();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(m_bRv, true);
        }

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            objEvent.reset();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(m_bRv, false);
        }
    }

    xTEST_CASE("wait", a_caseLoops)
    {
        {
            cbool_t cbIsAutoReset  = false;
            cbool_t cbInitialState = false;


            Event objEvent(cbIsAutoReset, cbInitialState);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            Event::ExObjectState osRes = objEvent.wait(5);
            xTEST_EQ(Event::osTimeout, osRes);

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(cbInitialState, m_bRv);
        }

        {
            cbool_t cbIsAutoReset  = true;
            cbool_t cbInitialState = true;


            Event objEvent(cbIsAutoReset, cbInitialState);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            Event::ExObjectState osRes = objEvent.wait(10);
            xTEST_EQ(Event::osTimeout, osRes);

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(m_bRv, false);
        }

        {
            cbool_t cbIsAutoReset  = true;
            cbool_t cbInitialState = false;

            Event objEvent(cbIsAutoReset, cbInitialState);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            Event::ExObjectState osRes = objEvent.wait(10);
            xTEST_EQ(Event::osTimeout, osRes);

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(m_bRv, false);
        }

        {
            cbool_t cbIsAutoReset  = false;
            cbool_t cbInitialState = true;

            Event objEvent(cbIsAutoReset, cbInitialState);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            Event::ExObjectState osRes = objEvent.wait(10);
            xTEST_EQ(Event::osSignaled, osRes);

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(m_bRv, true);
        }

    }
}
//-------------------------------------------------------------------------------------------------
