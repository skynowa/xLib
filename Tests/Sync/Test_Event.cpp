/**
 * \file   Test_Event.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Event)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Event::unit()
{
    xTEST_CASE("handle")
    {
        Event objEvent(true, true);
        objEvent.create();

        #if   xENV_WIN
            xTEST_DIFF(objEvent.handle(), xNATIVE_HANDLE_NULL);
        #elif xENV_UNIX
            // TEST: Test_Event() - hRv
        #endif
    }

    xTEST_CASE("isSignaled")
    {
        {
            Event objEvent(true, true);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST(m_bRv);
        }

        {
            Event objEvent(true, false);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST(!m_bRv);
        }
    }

    xTEST_CASE("set")
    {
        std::csize_t cuiSpinCount = 3;


        Event objEvent(true, true);

        objEvent.create();

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            objEvent.reset();

            m_bRv = objEvent.isSignaled();
            xTEST(!m_bRv);
        }

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            objEvent.set();

            m_bRv = objEvent.isSignaled();
            xTEST(m_bRv);
        }
    }

    xTEST_CASE("reset")
    {
        std::csize_t cuiSpinCount = 3;


        Event objEvent(true, true);

        objEvent.create();

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            objEvent.set();

            m_bRv = objEvent.isSignaled();
            xTEST(m_bRv);
        }

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            objEvent.reset();

            m_bRv = objEvent.isSignaled();
            xTEST(!m_bRv);
        }
    }

    xTEST_CASE("wait")
    {
        {
            cbool_t cbIsAutoReset  = false;
            cbool_t cbInitialState = false;


            Event objEvent(cbIsAutoReset, cbInitialState);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            Event::ObjectState osRes = objEvent.wait(5);
            xTEST_EQ((int)Event::ObjectState::osTimeout, (int)osRes);

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

            Event::ObjectState osRes = objEvent.wait(10);
            xTEST_EQ((int)Event::ObjectState::osTimeout, (int)osRes);

            m_bRv = objEvent.isSignaled();
            xTEST(!m_bRv);
        }

        {
            cbool_t cbIsAutoReset  = true;
            cbool_t cbInitialState = false;

            Event objEvent(cbIsAutoReset, cbInitialState);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            Event::ObjectState osRes = objEvent.wait(10);
            xTEST_EQ((int)Event::ObjectState::osTimeout, (int)osRes);

            m_bRv = objEvent.isSignaled();
            xTEST(!m_bRv);
        }

        {
            cbool_t cbIsAutoReset  = false;
            cbool_t cbInitialState = true;

            Event objEvent(cbIsAutoReset, cbInitialState);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            Event::ObjectState osRes = objEvent.wait(10);
            xTEST_EQ((int)Event::ObjectState::osSignaled, (int)osRes);

            m_bRv = objEvent.isSignaled();
            xTEST(m_bRv);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
