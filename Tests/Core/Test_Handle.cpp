/**
 * \file   Test_Handle.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Handle)
xTEST_UNIT(Test_Handle)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Handle::unit()
{
    xTEST_CASE("Handle")
    {
        HandleNative objNullHandle;
        xTEST(!objNullHandle.isValid());

        HandleNativeInvalid objInvalidHandle;
        xTEST(!objInvalidHandle.isValid());

        HandleStdFile objStdHandle;
        xTEST(!objStdHandle.isValid());
    }

    xTEST_CASE("Handle(const HANDLE &chHandle)")
    {
        HandleNative handle( Process::currentHandle() );

        m_bRv = handle.isValid();
        xTEST(m_bRv);

        m_hRv = handle.detach();
        xTEST(!handle.isValid());
    }

    xTEST_CASE("Handle(const Handle &chHandle)")
    {
        HandleNative hHandle1;
        xTEST(!hHandle1.isValid());

        HandleNative hHandle2( hHandle1 );
        xTEST(!hHandle2.isValid());

        m_hRv = hHandle1.detach();
        xTEST(!hHandle1.isValid());

        m_hRv = hHandle2.detach();
        xTEST(!hHandle2.isValid());
    }

    xTEST_CASE("operator = (const native_handle_t &chHandle)")
    {
        HandleNative handle;

        handle = Process::currentHandle();

        m_hRv = handle.detach();
        xTEST(!handle.isValid());
    }

    xTEST_CASE("operator = (const Handle &chHandle)")
    {
        HandleNative hHandle1;
        xTEST(!hHandle1.isValid());

        HandleNative hHandle2;
        xTEST(!hHandle2.isValid());

        hHandle1 = hHandle2;
        xTEST(!hHandle1.isValid());
        xTEST(!hHandle2.isValid());
    }

    xTEST_CASE("get set")
    {
        HandleNative handle;

        m_hRv = handle.get();
        xTEST(!handle.isValid());

        handle.set(native_handle_t());

        m_hRv = handle.get();
        xTEST(native_handle_t() == m_hRv);

        handle.set(Process::currentHandle());

        m_hRv = handle.get();
        xTEST_EQ(Process::currentHandle(), m_hRv);

        m_hRv = handle.detach();
        xTEST(!handle.isValid());
    }

    xTEST_CASE("clone")
    {
        HandleNative handle;

        m_hRv = handle.clone();
        xTEST(!handle.isValid());
    }

    xTEST_CASE("isValid")
    {
        HandleNative handle;

        m_bRv = handle.isValid();
        xTEST(!m_bRv);

        handle.set(Process::currentHandle());

        m_hRv = handle.detach();
        xTEST(!handle.isValid());
    }

    xTEST_CASE("attach")
    {
        HandleNative handle;

        handle.attach(Process::currentHandle());
    }

    xTEST_CASE("detach")
    {
        HandleNative handle;

        m_hRv = handle.detach();
        xTEST(!handle.isValid());
    }

    xTEST_CASE("close")
    {
        HandleNative handle;

        handle.close();

        m_bRv = handle.isValid();
        xTEST(!m_bRv);
    }

    xTEST_CASE("setInfo")
    {
        // TEST: Handle::setInfo

    #if   xENV_WIN
        HandleNative handle;

        handle = Process::currentHandle();
        xTEST(handle.isValid());

        handle.setInfo(HANDLE_FLAG_INHERIT, 0);

        m_ulRv = handle.info();
        xTEST_EQ((ulong_t)HANDLE_FLAG_INHERIT, m_ulRv);
    #elif xENV_UNIX

    #endif
    }

    xTEST_CASE("info")
    {
        // TEST: Handle::info

    #if   xENV_WIN
        HandleNative handle;

        handle = Process::currentHandle();
        xTEST(handle.isValid());

        handle.setInfo(HANDLE_FLAG_PROTECT_FROM_CLOSE, 0);

        m_ulRv = handle.info();
        xTEST_EQ((ulong_t)HANDLE_FLAG_PROTECT_FROM_CLOSE, m_ulRv);
    #elif xENV_UNIX

    #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
