/**
 * \file   CxTest_CxHandleT.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxHandleT.h>

#include <xLib/Sync/CxCurrentProcess.h>


//---------------------------------------------------------------------------
CxTest_CxHandleT::CxTest_CxHandleT() {

}
//---------------------------------------------------------------------------
CxTest_CxHandleT::~CxTest_CxHandleT() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxHandleT::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxHandleT::CxHandleT", cullCaseLoops)
    {
        CxHandle objNullHandle;
        xTEST_EQ(false, objNullHandle.isValid());

        CxHandleInvalid objInvalidHandle;
        xTEST_EQ(false, objInvalidHandle.isValid());
    }

    xTEST_CASE("CxHandleT::CxHandleT(const HANDLE &chHandle)", cullCaseLoops)
    {
        CxHandle hHandle( CxCurrentProcess::hHandle() );

        m_bRv = hHandle.isValid();
        xTEST_EQ(true, m_bRv);

        m_hRv = hHandle.detach();
        xTEST_EQ(false, hHandle.isValid());
    }

    xTEST_CASE("CxHandleT::CxHandleT(const CxHandleT &chHandle)", cullCaseLoops)
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

    xTEST_CASE("CxHandleT::operator = (const native_handle_t &chHandle)", cullCaseLoops)
    {
        CxHandle hHandle;

        hHandle = CxCurrentProcess::hHandle();

        m_hRv = hHandle.detach();
        xTEST_EQ(false, hHandle.isValid());
    }

    xTEST_CASE("CxHandleT::operator = (const CxHandleT &chHandle)", cullCaseLoops)
    {
        CxHandle hHandle1;
        xTEST_EQ(false, hHandle1.isValid());

        CxHandle hHandle2;
        xTEST_EQ(false, hHandle2.isValid());

        hHandle1 = hHandle2;
        xTEST_EQ(false, hHandle1.isValid());
        xTEST_EQ(false, hHandle2.isValid());
    }

    xTEST_CASE("CxHandleT::get set", cullCaseLoops)
    {
        CxHandle hHandle;

        m_hRv = hHandle.get();
        xTEST_EQ(false, hHandle.isValid());

        hHandle.set(native_handle_t());

        m_hRv = hHandle.get();
        xTEST_EQ(true, native_handle_t() == m_hRv);

        hHandle.set(CxCurrentProcess::hHandle());

        m_hRv = hHandle.get();
        xTEST_EQ(CxCurrentProcess::hHandle(), m_hRv);

        m_hRv = hHandle.detach();
        xTEST_EQ(false, hHandle.isValid());
    }

    xTEST_CASE("CxHandleT::duplicate", cullCaseLoops)
    {
        CxHandle hHandle;

        m_hRv = hHandle.duplicate();
        xTEST_EQ(false, hHandle.isValid());
    }

    xTEST_CASE("CxHandleT::isValid", cullCaseLoops)
    {
        CxHandle hHandle;

        m_bRv = hHandle.isValid();
        xTEST_EQ(false, m_bRv);

        hHandle.set(CxCurrentProcess::hHandle());

        m_hRv = hHandle.detach();
        xTEST_EQ(false, hHandle.isValid());
    }

    xTEST_CASE("CxHandleT::attach", cullCaseLoops)
    {
        CxHandle hHandle;

        hHandle.attach(CxCurrentProcess::hHandle());
    }

    xTEST_CASE("CxHandleT::detach", cullCaseLoops)
    {
        CxHandle hHandle;

        m_hRv = hHandle.detach();
        xTEST_EQ(false, hHandle.isValid());
    }

    xTEST_CASE("CxHandleT::close", cullCaseLoops)
    {
        CxHandle hHandle;

        hHandle.close();

        m_bRv = hHandle.isValid();
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxHandleT::setInfo", cullCaseLoops)
    {
        // TEST: CxHandleT::setInfo

    #if   xOS_ENV_WIN
        #if xTODO
            CxHandle hHandle;

            hHandle = CxCurrentProcess::hHandle();
            xTEST_EQ(true, hHandle.isValid());

            hHandle.setInfo(HANDLE_FLAG_INHERIT, 0);

            m_ulRv = hHandle.info();
            xTEST_EQ((ulong_t)HANDLE_FLAG_INHERIT, m_ulRv);
        #endif
    #elif xOS_ENV_UNIX

    #endif
    }

    xTEST_CASE("CxHandleT::info", cullCaseLoops)
    {
        // TEST: CxHandleT::info

    #if   xOS_ENV_WIN
        #if xTODO
            CxHandle hHandle;

            hHandle = CxCurrentProcess::hHandle();
            xTEST_EQ(true, hHandle.isValid());

            hHandle.setInfo(HANDLE_FLAG_PROTECT_FROM_CLOSE, 0);

            m_ulRv = hHandle.info();
            xTEST_EQ((ulong_t)HANDLE_FLAG_PROTECT_FROM_CLOSE, m_ulRv);
        #endif
    #elif xOS_ENV_UNIX

    #endif
    }
}
//---------------------------------------------------------------------------

