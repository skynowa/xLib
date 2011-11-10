/**
 * \file   CxTest_CxHandleT.cpp
 * \brief
 */


#include <Test/Common/Win/CxTest_CxHandleT.h>

#include <xLib/Sync/CxProcess.h>


//---------------------------------------------------------------------------
CxTest_CxHandleT::CxTest_CxHandleT() {

}
//---------------------------------------------------------------------------
CxTest_CxHandleT::~CxTest_CxHandleT() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxHandleT::bUnit(
    const ULONGLONG cullBlockLoops
)
{
#if defined(xOS_ENV_WIN)
    //-------------------------------------
    //CxHandleT
    CxHandleT<hvNull> objHandle;

    //-------------------------------------
    //CxHandleT(const HANDLE chHandle)
    {
        m_bRes = objHandle.bIsValid();
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = objHandle.bSet( CxHandle::hGetCurrentProcess() );
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = objHandle.bIsValid();
        xTEST_DIFF(FALSE, m_bRes);
        xTEST_EQ(CxHandle::hGetCurrentProcess(), objHandle.hGet());
    }

    //-------------------------------------
    //CxHandleT(const CxHandleT &chHandle)
    {
        #if xTODO
            CxHandle objHandle2(objHandle.m_hHandle);
        #endif
    }

    //-------------------------------------
    //CxHandleT
    {
        #if xTODO
            CxHandle objHandle1(objHandle);
        #endif
    }

    //-------------------------------------
    //operator HANDLE
    {
        #if xTODO
            operator HANDLE         () const;
        #endif
    }

    //-------------------------------------
    //hGet, bSet
    {
        m_hRes = objHandle.hGet();
        xTEST_EQ(CxHandle::hGetCurrentProcess(), m_hRes);

        m_bRes = objHandle.bSet(NULL);
        xTEST_DIFF(FALSE, m_bRes);

        m_hRes = objHandle.hGet();
        xASSERT(NULL == m_hRes);

        m_bRes = objHandle.bSet(CxHandle::hGetCurrentProcess());
        xTEST_DIFF(FALSE, m_bRes);

        m_hRes = objHandle.hGet();
        xTEST_EQ(CxHandle::hGetCurrentProcess(), m_hRes);
    }

    //-------------------------------------
    //bIsValid
    {
        m_bRes = objHandle.bIsValid();
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bSetInformation
    {
        #if xTEMP_DISABLED
            m_bRes = objHandle.bSetInformation(7, HANDLE_FLAG_INHERIT);
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //-------------------------------------
    //ulGetInformation
    {
        #if xTODO
            m_ulRes = objHandle.ulGetInformation();
            xTEST_EQ(HANDLE_FLAG_INHERIT, m_ulRes);
        #endif
    }

    //-------------------------------------
    //bSetFlagInherit
    {
        #if xTEMP_DISABLED
            m_bRes = objHandle.bSetFlagInherit(TRUE);
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //-------------------------------------
    //bIsFlagInherit
    {
        #if xTEMP_DISABLED
            m_bRes = objHandle.bIsFlagInherit();
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //-------------------------------------
    //bSetFlagProtectFromClose
    {
        #if xTODO
            m_bRes = objHandle.bSetFlagProtectFromClose(FALSE);
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //-------------------------------------
    //bIsFlagProtectFromClose
    {
        #if xTODO
            m_bRes = objHandle.bIsFlagProtectFromClose();
            xTEST_EQ(FALSE, m_bRes);
        #endif
    }

    //-------------------------------------
    //hDuplicate
    {
        #if xTODO
            m_hRes = objHandle.hDuplicate(CxHandle::hGetCurrentProcess(), 0, FALSE, 0);
            xASSERT(NULL != m_hRes);
        #endif
    }

    //-------------------------------------
    //hDetach
    {
        #if xTODO
            m_hRes = objHandle.hDetach();
            xASSERT(NULL != m_hRes);
        #endif
    }

    //-------------------------------------
    //bAttach
    {
        #if xTODO
            m_bRes = objHandle.bAttach(CxHandle::hGetCurrentProcess());
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //-------------------------------------
    //bClose
    {
        #if xTODO
            m_bRes = objHandle.bClose();
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //-------------------------------------
    //bIsValid
    {
        m_bRes = CxHandleT<hvNull>::bIsValid(CxHandle::hGetCurrentProcess());
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bIsValid
    {
        m_bRes = CxHandleT<hvInvalid>::bIsValid(CxHandle::hGetCurrentProcess());
        xTEST_EQ(FALSE, m_bRes);
    }

    //detach handle
    m_bRes = objHandle.bSet(NULL);
    xTEST_DIFF(FALSE, m_bRes);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------

