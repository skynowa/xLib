/**
 * \file   Test_HandleT.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_HandleT)
xTEST_UNIT(Test_HandleT)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_HandleT::unit()
{
    xTEST_CASE("HandleT")
    {
        HandleNull objNullHandle;
        xTEST_EQ(false, objNullHandle.isValid());

        HandleInvalid objInvalidHandle;
        xTEST_EQ(false, objInvalidHandle.isValid());
    }

    xTEST_CASE("HandleT(const HANDLE &chHandle)")
    {
        HandleNull handle( Process::currentHandle() );

        m_bRv = handle.isValid();
        xTEST_EQ(m_bRv, true);

        m_hRv = handle.detach();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("HandleT(const HandleT &chHandle)")
    {
        HandleNull hHandle1;
        xTEST_EQ(false, hHandle1.isValid());

        HandleNull hHandle2( hHandle1 );
        xTEST_EQ(false, hHandle2.isValid());

        m_hRv = hHandle1.detach();
        xTEST_EQ(false, hHandle1.isValid());

        m_hRv = hHandle2.detach();
        xTEST_EQ(false, hHandle2.isValid());
    }

    xTEST_CASE("operator = (const native_handle_t &chHandle)")
    {
        HandleNull handle;

        handle = Process::currentHandle();

        m_hRv = handle.detach();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("operator = (const HandleT &chHandle)")
    {
        HandleNull hHandle1;
        xTEST_EQ(false, hHandle1.isValid());

        HandleNull hHandle2;
        xTEST_EQ(false, hHandle2.isValid());

        hHandle1 = hHandle2;
        xTEST_EQ(false, hHandle1.isValid());
        xTEST_EQ(false, hHandle2.isValid());
    }

    xTEST_CASE("get set")
    {
        HandleNull handle;

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

    xTEST_CASE("dup")
    {
        HandleNull handle;

        m_hRv = handle.dup();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("isValid")
    {
        HandleNull handle;

        m_bRv = handle.isValid();
        xTEST_EQ(m_bRv, false);

        handle.set(Process::currentHandle());

        m_hRv = handle.detach();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("attach")
    {
        HandleNull handle;

        handle.attach(Process::currentHandle());
    }

    xTEST_CASE("detach")
    {
        HandleNull handle;

        m_hRv = handle.detach();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("close")
    {
        HandleNull handle;

        handle.close();

        m_bRv = handle.isValid();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("setInfo")
    {
        // TEST: HandleT::setInfo

    #if   xENV_WIN
        HandleNull handle;

        handle = Process::currentHandle();
        xTEST_EQ(true, handle.isValid());

        handle.setInfo(HANDLE_FLAG_INHERIT, 0);

        m_ulRv = handle.info();
        xTEST_EQ((ulong_t)HANDLE_FLAG_INHERIT, m_ulRv);
    #elif xENV_UNIX

    #endif
    }

    xTEST_CASE("info")
    {
        // TEST: HandleT::info

    #if   xENV_WIN
        HandleNull handle;

        handle = Process::currentHandle();
        xTEST_EQ(true, handle.isValid());

        handle.setInfo(HANDLE_FLAG_PROTECT_FROM_CLOSE, 0);

        m_ulRv = handle.info();
        xTEST_EQ((ulong_t)HANDLE_FLAG_PROTECT_FROM_CLOSE, m_ulRv);
    #elif xENV_UNIX

    #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
