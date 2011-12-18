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
/*virtual*/
bool
CxTest_CxHandleT::bUnit(
    const ulonglong_t cullCaseLoops
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

        m_bRes = hHandle.bIsValid();
        xTEST_EQ(true, m_bRes);

        m_hRes = hHandle.hDetach();
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

        m_hRes = hHandle1.hDetach();
        xTEST_EQ(false, hHandle1.bIsValid());

        m_hRes = hHandle2.hDetach();
        xTEST_EQ(false, hHandle2.bIsValid());
    }

    //--------------------------------------------------
    //operator = (const TxHandle chHandle)
    xTEST_CASE(cullCaseLoops)
    {
	    CxHandle hHandle;

        hHandle = CxCurrentProcess::hGetHandle();

        m_hRes = hHandle.hDetach();
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

        m_hRes = hHandle.hGet();
        xTEST_EQ(false, hHandle.bIsValid());

        m_bRes = hHandle.bSet(NULL);
        xTEST_EQ(true, m_bRes);

        m_hRes = hHandle.hGet();
        xASSERT(NULL == m_hRes);

        m_bRes = hHandle.bSet(CxCurrentProcess::hGetHandle());
        xTEST_EQ(true, m_bRes);

        m_hRes = hHandle.hGet();
        xTEST_EQ(CxCurrentProcess::hGetHandle(), m_hRes);

        m_hRes = hHandle.hDetach();
        xTEST_EQ(false, hHandle.bIsValid());
    }

     //-------------------------------------
    //hDuplicate
    xTEST_CASE(cullCaseLoops)
    {
        CxHandle hHandle;

        m_hRes = hHandle.hDuplicate();
        xTEST_EQ(false, hHandle.bIsValid());
    }

    //-------------------------------------
    //bIsValid
    xTEST_CASE(cullCaseLoops)
    {
        CxHandle hHandle;

        m_bRes = hHandle.bIsValid();
        xTEST_EQ(false, m_bRes);

        m_bRes = hHandle.bSet(CxCurrentProcess::hGetHandle());
        xTEST_EQ(true, m_bRes);

        m_hRes = hHandle.hDetach();
        xTEST_EQ(false, hHandle.bIsValid());
    }

    //-------------------------------------
    //bAttach
    xTEST_CASE(cullCaseLoops)
    {
        CxHandle hHandle;

        m_bRes = hHandle.bAttach(CxCurrentProcess::hGetHandle());
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //hDetach
    xTEST_CASE(cullCaseLoops)
    {
        CxHandle hHandle;

        m_hRes = hHandle.hDetach();
        xTEST_EQ(false, hHandle.bIsValid());
    }

    //-------------------------------------
    //bClose
    xTEST_CASE(cullCaseLoops)
    {
        CxHandle hHandle;

        m_bRes = hHandle.bClose();
        xTEST_EQ(true, m_bRes);

        m_bRes = hHandle.bIsValid();
        xTEST_EQ(false, m_bRes);
    }

    //-------------------------------------
    //bSetInformation
    xTEST_CASE(cullCaseLoops)
    {
    #if defined(xOS_ENV_WIN)
        #if xTODO
            CxHandle hHandle;

            hHandle = CxCurrentProcess::hGetHandle();
            xTEST_EQ(true, hHandle.bIsValid());

            m_bRes = hHandle.bSetInformation(HANDLE_FLAG_INHERIT, 0);
            xTEST_EQ(true, m_bRes);

            m_ulRes = hHandle.ulGetInformation();
            xTEST_EQ((ulong_t)HANDLE_FLAG_INHERIT, m_ulRes);
        #endif
    #elif defined(xOS_ENV_UNIX)

    #endif
    }

    //-------------------------------------
    //ulGetInformation
    xTEST_CASE(cullCaseLoops)
    {
    #if defined(xOS_ENV_WIN)
        #if xTODO
            CxHandle hHandle;

            hHandle = CxCurrentProcess::hGetHandle();
            xTEST_EQ(true, hHandle.bIsValid());
        
            m_bRes = hHandle.bSetInformation(HANDLE_FLAG_PROTECT_FROM_CLOSE, 0);
            xTEST_EQ(true, m_bRes);

            m_ulRes = hHandle.ulGetInformation();
            xTEST_EQ((ulong_t)HANDLE_FLAG_PROTECT_FROM_CLOSE, m_ulRes);
        #endif
    #elif defined(xOS_ENV_UNIX)

    #endif
    }

    return true;
}
//---------------------------------------------------------------------------

