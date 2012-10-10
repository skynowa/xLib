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
    xTEST_CASE(CxHandleT::CxHandleT, cullCaseLoops)
    {
        CxHandle objNullHandle;
        xTEST_EQ(false, objNullHandle.bIsValid());

        CxFileHandle objInvalidHandle;
        xTEST_EQ(false, objInvalidHandle.bIsValid());
    }

    xTEST_CASE(CxHandleT::CxHandleT(const HANDLE &chHandle), cullCaseLoops)
    {
        CxHandle hHandle( CxCurrentProcess::hHandle() );

        m_bRv = hHandle.bIsValid();
        xTEST_EQ(true, m_bRv);

        m_hRv = hHandle.hDetach();
        xTEST_EQ(false, hHandle.bIsValid());
    }

    xTEST_CASE(CxHandleT::CxHandleT(const CxHandleT &chHandle), cullCaseLoops)
    {
        CxHandle hHandle1;
        xTEST_EQ(false, hHandle1.bIsValid());

        CxHandle hHandle2( hHandle1 );
        xTEST_EQ(false, hHandle2.bIsValid());

        m_hRv = hHandle1.hDetach();
        xTEST_EQ(false, hHandle1.bIsValid());

        m_hRv = hHandle2.hDetach();
        xTEST_EQ(false, hHandle2.bIsValid());
    }

    xTEST_CASE(CxHandleT::operator = (const native_handle_t &chHandle), cullCaseLoops)
    {
        CxHandle hHandle;

        hHandle = CxCurrentProcess::hHandle();

        m_hRv = hHandle.hDetach();
        xTEST_EQ(false, hHandle.bIsValid());
    }

    xTEST_CASE(CxHandleT::operator = (const CxHandleT &chHandle), cullCaseLoops)
    {
        CxHandle hHandle1;
        xTEST_EQ(false, hHandle1.bIsValid());

        CxHandle hHandle2;
        xTEST_EQ(false, hHandle2.bIsValid());

        hHandle1 = hHandle2;
        xTEST_EQ(false, hHandle1.bIsValid());
        xTEST_EQ(false, hHandle2.bIsValid());
    }

    xTEST_CASE(CxHandleT::hGet vSet, cullCaseLoops)
    {
        CxHandle hHandle;

        m_hRv = hHandle.hGet();
        xTEST_EQ(false, hHandle.bIsValid());

        hHandle.vSet(native_handle_t());

        m_hRv = hHandle.hGet();
        xTEST_EQ(true, native_handle_t() == m_hRv);

        hHandle.vSet(CxCurrentProcess::hHandle());

        m_hRv = hHandle.hGet();
        xTEST_EQ(CxCurrentProcess::hHandle(), m_hRv);

        m_hRv = hHandle.hDetach();
        xTEST_EQ(false, hHandle.bIsValid());
    }

    xTEST_CASE(CxHandleT::hDuplicate, cullCaseLoops)
    {
        CxHandle hHandle;

        m_hRv = hHandle.hDuplicate();
        xTEST_EQ(false, hHandle.bIsValid());
    }

    xTEST_CASE(CxHandleT::bIsValid, cullCaseLoops)
    {
        CxHandle hHandle;

        m_bRv = hHandle.bIsValid();
        xTEST_EQ(false, m_bRv);

        hHandle.vSet(CxCurrentProcess::hHandle());

        m_hRv = hHandle.hDetach();
        xTEST_EQ(false, hHandle.bIsValid());
    }

    xTEST_CASE(CxHandleT::vAttach, cullCaseLoops)
    {
        CxHandle hHandle;

        hHandle.vAttach(CxCurrentProcess::hHandle());
    }

    xTEST_CASE(CxHandleT::hDetach, cullCaseLoops)
    {
        CxHandle hHandle;

        m_hRv = hHandle.hDetach();
        xTEST_EQ(false, hHandle.bIsValid());
    }

    xTEST_CASE(CxHandleT::vClose, cullCaseLoops)
    {
        CxHandle hHandle;

        hHandle.vClose();

        m_bRv = hHandle.bIsValid();
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE(CxHandleT::vSetInfo, cullCaseLoops)
    {
    #if   xOS_ENV_WIN
        #if xTODO
            CxHandle hHandle;

            hHandle = CxCurrentProcess::hGetHandle();
            xTEST_EQ(true, hHandle.bIsValid());

            hHandle.vSetInfo(HANDLE_FLAG_INHERIT, 0);

            m_ulRv = hHandle.ulGetInfo();
            xTEST_EQ((ulong_t)HANDLE_FLAG_INHERIT, m_ulRv);
        #endif
    #elif xOS_ENV_UNIX

    #endif
    }

    xTEST_CASE(CxHandleT::ulGetInfo, cullCaseLoops)
    {
    #if   xOS_ENV_WIN
        #if xTODO
            CxHandle hHandle;

            hHandle = CxCurrentProcess::hGetHandle();
            xTEST_EQ(true, hHandle.bIsValid());

            hHandle.vSetInfo(HANDLE_FLAG_PROTECT_FROM_CLOSE, 0);

            m_ulRv = hHandle.ulGetInfo();
            xTEST_EQ((ulong_t)HANDLE_FLAG_PROTECT_FROM_CLOSE, m_ulRv);
        #endif
    #elif xOS_ENV_UNIX

    #endif
    }
}
//---------------------------------------------------------------------------

