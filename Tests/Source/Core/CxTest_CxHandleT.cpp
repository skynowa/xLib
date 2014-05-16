/**
 * \file   CxTest_CxHandleT.cpp
 * \brief
 */


#include <Test/Core/CxTest_CxHandleT.h>

#include <xLib/Sync/CxProcess.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxHandleT::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxHandleT::CxHandleT", a_caseLoops)
    {
        CxHandle objNullHandle;
        xTEST_EQ(false, objNullHandle.isValid());

        CxHandleInvalid objInvalidHandle;
        xTEST_EQ(false, objInvalidHandle.isValid());
    }

    xTEST_CASE("CxHandleT::CxHandleT(const HANDLE &chHandle)", a_caseLoops)
    {
        CxHandle handle( CxProcess::currentHandle() );

        m_bRv = handle.isValid();
        xTEST_EQ(m_bRv, true);

        m_hRv = handle.detach();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("CxHandleT::CxHandleT(const CxHandleT &chHandle)", a_caseLoops)
    {
        CxHandle hHandle1;
        xTEST_EQ(false, hHandle1.isValid());

        CxHandle hHandle2( hHandle1 );
        xTEST_EQ(false, hHandle2.isValid());

        m_hRv = hHandle1.detach();
        xTEST_EQ(false, hHandle1.isValid());

        m_hRv = hHandle2.detach();
        xTEST_EQ(false, hHandle2.isValid());
    }

    xTEST_CASE("CxHandleT::operator = (cnative_handle_t &chHandle)", a_caseLoops)
    {
        CxHandle handle;

        handle = CxProcess::currentHandle();

        m_hRv = handle.detach();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("CxHandleT::operator = (const CxHandleT &chHandle)", a_caseLoops)
    {
        CxHandle hHandle1;
        xTEST_EQ(false, hHandle1.isValid());

        CxHandle hHandle2;
        xTEST_EQ(false, hHandle2.isValid());

        hHandle1 = hHandle2;
        xTEST_EQ(false, hHandle1.isValid());
        xTEST_EQ(false, hHandle2.isValid());
    }

    xTEST_CASE("CxHandleT::get set", a_caseLoops)
    {
        CxHandle handle;

        m_hRv = handle.get();
        xTEST_EQ(false, handle.isValid());

        handle.set(native_handle_t());

        m_hRv = handle.get();
        xTEST_EQ(true, native_handle_t() == m_hRv);

        handle.set(CxProcess::currentHandle());

        m_hRv = handle.get();
        xTEST_EQ(CxProcess::currentHandle(), m_hRv);

        m_hRv = handle.detach();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("CxHandleT::duplicate", a_caseLoops)
    {
        CxHandle handle;

        m_hRv = handle.duplicate();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("CxHandleT::isValid", a_caseLoops)
    {
        CxHandle handle;

        m_bRv = handle.isValid();
        xTEST_EQ(m_bRv, false);

        handle.set(CxProcess::currentHandle());

        m_hRv = handle.detach();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("CxHandleT::attach", a_caseLoops)
    {
        CxHandle handle;

        handle.attach(CxProcess::currentHandle());
    }

    xTEST_CASE("CxHandleT::detach", a_caseLoops)
    {
        CxHandle handle;

        m_hRv = handle.detach();
        xTEST_EQ(false, handle.isValid());
    }

    xTEST_CASE("CxHandleT::close", a_caseLoops)
    {
        CxHandle handle;

        handle.close();

        m_bRv = handle.isValid();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("CxHandleT::setInfo", a_caseLoops)
    {
        // TEST: CxHandleT::setInfo

    #if   xENV_WIN
        CxHandle handle;

        handle = CxProcess::currentHandle();
        xTEST_EQ(true, handle.isValid());

        handle.setInfo(HANDLE_FLAG_INHERIT, 0);

        m_ulRv = handle.info();
        xTEST_EQ((ulong_t)HANDLE_FLAG_INHERIT, m_ulRv);
    #elif xENV_UNIX

    #endif
    }

    xTEST_CASE("CxHandleT::info", a_caseLoops)
    {
        // TEST: CxHandleT::info

    #if   xENV_WIN
        CxHandle handle;

        handle = CxProcess::currentHandle();
        xTEST_EQ(true, handle.isValid());

        handle.setInfo(HANDLE_FLAG_PROTECT_FROM_CLOSE, 0);

        m_ulRv = handle.info();
        xTEST_EQ((ulong_t)HANDLE_FLAG_PROTECT_FROM_CLOSE, m_ulRv);
    #elif xENV_UNIX

    #endif
    }
}
//-------------------------------------------------------------------------------------------------
