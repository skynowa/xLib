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
    //-------------------------------------
    //CxHandleT()
    xTEST_CASE(cullCaseLoops)
    {
        CxHandle objNullHandle;
        xTEST_EQ(false, objNullHandle.bIsValid());

        CxFileHandle objInvalidHandle;
        xTEST_EQ(false, objInvalidHandle.bIsValid());
    }

    //-------------------------------------
    //CxHandleT(const HANDLE chHandle)
    xTEST_CASE(cullCaseLoops)
    {
        CxHandle hHandle( CxCurrentProcess::hGetHandle() );

        m_bRv = hHandle.bIsValid();
        xTEST_EQ(true, m_bRv);

        m_hRv = hHandle.hDetach();
        xTEST_EQ(false, hHandle.bIsValid());
    }

    //-------------------------------------
    //CxHandleT(const CxHandleT &chHandle)
    xTEST_CASE(cullCaseLoops)
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

    //--------------------------------------------------
    //operator = (const native_handle_t chHandle)
    xTEST_CASE(cullCaseLoops)
    {
        CxHandle hHandle;

        hHandle = CxCurrentProcess::hGetHandle();

        m_hRv = hHandle.hDetach();
        xTEST_EQ(false, hHandle.bIsValid());
    }

    //--------------------------------------------------
    //operator = (const CxHandleT &chHandle)
    xTEST_CASE(cullCaseLoops)
    {
        CxHandle hHandle1;
        xTEST_EQ(false, hHandle1.bIsValid());

        CxHandle hHandle2;
        xTEST_EQ(false, hHandle2.bIsValid());

        hHandle1 = hHandle2;
        xTEST_EQ(false, hHandle1.bIsValid());
        xTEST_EQ(false, hHandle2.bIsValid());
    }

    //-------------------------------------
    //hGet, bSet
    xTEST_CASE(cullCaseLoops)
    {
        CxHandle hHandle;

        m_hRv = hHandle.hGet();
        xTEST_EQ(false, hHandle.bIsValid());

        hHandle.vSet(native_handle_t());

        m_hRv = hHandle.hGet();
        xTEST_EQ(true, native_handle_t() == m_hRv);

        hHandle.vSet(CxCurrentProcess::hGetHandle());

        m_hRv = hHandle.hGet();
        xTEST_EQ(CxCurrentProcess::hGetHandle(), m_hRv);

        m_hRv = hHandle.hDetach();
        xTEST_EQ(false, hHandle.bIsValid());
    }

     //-------------------------------------
    //hDuplicate
    xTEST_CASE(cullCaseLoops)
    {
        CxHandle hHandle;

        m_hRv = hHandle.hDuplicate();
        xTEST_EQ(false, hHandle.bIsValid());
    }

    //-------------------------------------
    //bIsValid
    xTEST_CASE(cullCaseLoops)
    {
        CxHandle hHandle;

        m_bRv = hHandle.bIsValid();
        xTEST_EQ(false, m_bRv);

        hHandle.vSet(CxCurrentProcess::hGetHandle());

        m_hRv = hHandle.hDetach();
        xTEST_EQ(false, hHandle.bIsValid());
    }

    //-------------------------------------
    //bAttach
    xTEST_CASE(cullCaseLoops)
    {
        CxHandle hHandle;

        hHandle.vAttach(CxCurrentProcess::hGetHandle());
    }

    //-------------------------------------
    //hDetach
    xTEST_CASE(cullCaseLoops)
    {
        CxHandle hHandle;

        m_hRv = hHandle.hDetach();
        xTEST_EQ(false, hHandle.bIsValid());
    }

    //-------------------------------------
    //bClose
    xTEST_CASE(cullCaseLoops)
    {
        CxHandle hHandle;

        hHandle.vClose();

        m_bRv = hHandle.bIsValid();
        xTEST_EQ(false, m_bRv);
    }

    //-------------------------------------
    //bSetInfo
    xTEST_CASE(cullCaseLoops)
    {
    #if   xOS_ENV_WIN
        #if xTODO
            CxHandle hHandle;

            hHandle = CxCurrentProcess::hGetHandle();
            xTEST_EQ(true, hHandle.bIsValid());

            m_bRv = hHandle.bSetInfo(HANDLE_FLAG_INHERIT, 0);
            xTEST_EQ(true, m_bRv);

            m_ulRv = hHandle.ulGetInfo();
            xTEST_EQ((ulong_t)HANDLE_FLAG_INHERIT, m_ulRv);
        #endif
    #elif xOS_ENV_UNIX

    #endif
    }

    //-------------------------------------
    //ulGetInfo
    xTEST_CASE(cullCaseLoops)
    {
    #if   xOS_ENV_WIN
        #if xTODO
            CxHandle hHandle;

            hHandle = CxCurrentProcess::hGetHandle();
            xTEST_EQ(true, hHandle.bIsValid());

            m_bRv = hHandle.bSetInfo(HANDLE_FLAG_PROTECT_FROM_CLOSE, 0);
            xTEST_EQ(true, m_bRv);

            m_ulRv = hHandle.ulGetInfo();
            xTEST_EQ((ulong_t)HANDLE_FLAG_PROTECT_FROM_CLOSE, m_ulRv);
        #endif
    #elif xOS_ENV_UNIX

    #endif
    }
}
//---------------------------------------------------------------------------

