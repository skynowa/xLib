/**
 * \file   CxTest_CxEvent.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxEvent.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxEvent::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxEvent::handle", a_cullCaseLoops)
    {
        CxEvent objEvent(true, true);

        objEvent.create();

        #if   xOS_ENV_WIN
            xTEST_EQ(true, objEvent.handle().isValid())
        #elif xOS_ENV_UNIX
            // TODO: hRv
        #endif
    }

    xTEST_CASE("CxEvent::isSignaled", a_cullCaseLoops)
    {
        {
            CxEvent objEvent(true, true);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(true, m_bRv);
        }

        {
            CxEvent objEvent(true, false);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(false, m_bRv);
        }
    }

    xTEST_CASE("CxEvent::set", a_cullCaseLoops)
    {
        std::csize_t cuiSpinCount = 3;


        CxEvent objEvent(true, true);

        objEvent.create();

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            objEvent.reset();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(false, m_bRv);
        }

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            objEvent.set();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(true, m_bRv);
        }
    }

    xTEST_CASE("CxEvent::reset", a_cullCaseLoops)
    {
        std::csize_t cuiSpinCount = 3;


        CxEvent objEvent(true, true);

        objEvent.create();

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            objEvent.set();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(true, m_bRv);
        }

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            objEvent.reset();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(false, m_bRv);
        }
    }

    xTEST_CASE("CxEvent::wait", a_cullCaseLoops)
    {
        {
            cbool_t cbIsAutoReset  = false;
            cbool_t cbInitialState = false;


            CxEvent objEvent(cbIsAutoReset, cbInitialState);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            CxEvent::ExObjectState osRes = objEvent.wait(5);
            xTEST_EQ(CxEvent::osTimeout, osRes);

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(cbInitialState, m_bRv);
        }

        {
            cbool_t cbIsAutoReset  = true;
            cbool_t cbInitialState = true;


            CxEvent objEvent(cbIsAutoReset, cbInitialState);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            CxEvent::ExObjectState osRes = objEvent.wait(10);
            xTEST_EQ(CxEvent::osTimeout, osRes);

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(false, m_bRv);
        }

        {
            cbool_t cbIsAutoReset  = true;
            cbool_t cbInitialState = false;

            CxEvent objEvent(cbIsAutoReset, cbInitialState);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            CxEvent::ExObjectState osRes = objEvent.wait(10);
            xTEST_EQ(CxEvent::osTimeout, osRes);

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(false, m_bRv);
        }

        {
            cbool_t cbIsAutoReset  = false;
            cbool_t cbInitialState = true;

            CxEvent objEvent(cbIsAutoReset, cbInitialState);

            objEvent.create();

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(cbInitialState, m_bRv);

            CxEvent::ExObjectState osRes = objEvent.wait(10);
            xTEST_EQ(CxEvent::osSignaled, osRes);

            m_bRv = objEvent.isSignaled();
            xTEST_EQ(true, m_bRv);
        }

    }
}
//------------------------------------------------------------------------------
