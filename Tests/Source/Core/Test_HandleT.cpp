/**
 * \file   Test_HandleT.cpp
 * \brief
 */


#include <Test/Core/Test_HandleT.h>

#include <xLib/Sync/Process.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_HandleT::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("HandleT", a_caseLoops)
    {
        Handle objNullHandle;
        xTEST_EQ(false, objNullHandle.isValid());

        HandleInvalid objInvalidHandle;
        xTEST_EQ(false, objInvalidHandle.isValid());
    }

    xTEST_CASE("HandleT(const HANDLE &chHandle)", a_caseLoops)
    {
        Handle handle( Process::currentHandle() );

        m_bRv = handle.isValid();
        xTEST_EQ(m_bRv, true);

        m_hRv = handle.detach();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("HandleT(const HandleT &chHandle)", a_caseLoops)
    {
        Handle hHandle1;
        xTEST_EQ(false, hHandle1.isValid());

        Handle hHandle2( hHandle1 );
        xTEST_EQ(false, hHandle2.isValid());

        m_hRv = hHandle1.detach();
        xTEST_EQ(false, hHandle1.isValid());

        m_hRv = hHandle2.detach();
        xTEST_EQ(false, hHandle2.isValid());
    }

    xTEST_CASE("operator = (cnative_handle_t &chHandle)", a_caseLoops)
    {
        Handle handle;

        handle = Process::currentHandle();

        m_hRv = handle.detach();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("operator = (const HandleT &chHandle)", a_caseLoops)
    {
        Handle hHandle1;
        xTEST_EQ(false, hHandle1.isValid());

        Handle hHandle2;
        xTEST_EQ(false, hHandle2.isValid());

        hHandle1 = hHandle2;
        xTEST_EQ(false, hHandle1.isValid());
        xTEST_EQ(false, hHandle2.isValid());
    }

    xTEST_CASE("get set", a_caseLoops)
    {
        Handle handle;

        m_hRv = handle.get();
        xTEST_EQ(false, handle.isValid());

        handle.set(native_handle_t());

        m_hRv = handle.get();
        xTEST_EQ(true, native_handle_t() == m_hRv);

        handle.set(Process::currentHandle());

        m_hRv = handle.get();
        xTEST_EQ(Process::currentHandle(), m_hRv);

        m_hRv = handle.detach();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("duplicate", a_caseLoops)
    {
        Handle handle;

        m_hRv = handle.duplicate();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("isValid", a_caseLoops)
    {
        Handle handle;

        m_bRv = handle.isValid();
        xTEST_EQ(m_bRv, false);

        handle.set(Process::currentHandle());

        m_hRv = handle.detach();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("attach", a_caseLoops)
    {
        Handle handle;

        handle.attach(Process::currentHandle());
    }

    xTEST_CASE("detach", a_caseLoops)
    {
        Handle handle;

        m_hRv = handle.detach();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("close", a_caseLoops)
    {
        Handle handle;

        handle.close();

        m_bRv = handle.isValid();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("setInfo", a_caseLoops)
    {
        // TEST: HandleT::setInfo

    #if   xENV_WIN
        Handle handle;

        handle = Process::currentHandle();
        xTEST_EQ(true, handle.isValid());

        handle.setInfo(HANDLE_FLAG_INHERIT, 0);

        m_ulRv = handle.info();
        xTEST_EQ((ulong_t)HANDLE_FLAG_INHERIT, m_ulRv);
    #elif xENV_UNIX

    #endif
    }

    xTEST_CASE("info", a_caseLoops)
    {
        // TEST: HandleT::info

    #if   xENV_WIN
        Handle handle;

        handle = Process::currentHandle();
        xTEST_EQ(true, handle.isValid());

        handle.setInfo(HANDLE_FLAG_PROTECT_FROM_CLOSE, 0);

        m_ulRv = handle.info();
        xTEST_EQ((ulong_t)HANDLE_FLAG_PROTECT_FROM_CLOSE, m_ulRv);
    #elif xENV_UNIX

    #endif
    }
}
//-------------------------------------------------------------------------------------------------
