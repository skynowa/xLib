/****************************************************************************
* Class name:  CxTest_CxHandleT
* Description: test CxHandle
* File name:   CxTest_CxHandleT.h
* Compilers:   Visual C++ 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <Test/Common/CxTest_CxHandleT.h>

#include <xLib/Sync/CxProcess.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxHandleT
CxTest_CxHandleT::CxTest_CxHandleT() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxHandleT
CxTest_CxHandleT::~CxTest_CxHandleT() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxHandleT::bUnit() {
#if defined(xOS_WIN)
    //-------------------------------------
    //CxHandleT
    CxHandleT<hvNull> objHandle;

    //-------------------------------------
    //CxHandleT(const HANDLE chHandle)
    {
        m_bRes = objHandle.bIsValid();
        xASSERT(FALSE == m_bRes);

        m_bRes = objHandle.bSet( CxHandle::hGetCurrentProcess() );
        xASSERT(FALSE != m_bRes);

        m_bRes = objHandle.bIsValid();
        xASSERT(FALSE                          != m_bRes);
        xASSERT(CxHandle::hGetCurrentProcess() == objHandle.hGet());
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
        xASSERT(CxHandle::hGetCurrentProcess() == m_hRes);

        HANDLE chHandle;

        m_bRes = objHandle.bSet(NULL);
        xASSERT(FALSE != m_bRes);

        m_hRes = objHandle.hGet();
        xASSERT(NULL == m_hRes);

        m_bRes = objHandle.bSet(CxHandle::hGetCurrentProcess());
        xASSERT(FALSE != m_bRes);

        m_hRes = objHandle.hGet();
        xASSERT(CxHandle::hGetCurrentProcess() == m_hRes);
    }

    //-------------------------------------
    //bIsValid
    {
        m_bRes = objHandle.bIsValid();
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bSetInformation
    {
        #if xTEMP_DISABLED
            m_bRes = objHandle.bSetInformation(7, HANDLE_FLAG_INHERIT);
            xASSERT(FALSE != m_bRes);
        #endif
    }

    //-------------------------------------
    //ulGetInformation
    {
        #if xTODO
            m_ulRes = objHandle.ulGetInformation();
            xASSERT(HANDLE_FLAG_INHERIT == m_ulRes);
        #endif
    }

    //-------------------------------------
    //bSetFlagInherit
    {
        #if xTEMP_DISABLED
            m_bRes = objHandle.bSetFlagInherit(TRUE);
            xASSERT(FALSE != m_bRes);
        #endif
    }

    //-------------------------------------
    //bIsFlagInherit
    {
        #if xTEMP_DISABLED
            m_bRes = objHandle.bIsFlagInherit();
            xASSERT(FALSE != m_bRes);
        #endif
    }

    //-------------------------------------
    //bSetFlagProtectFromClose
    {
        #if xTODO
            m_bRes = objHandle.bSetFlagProtectFromClose(FALSE);
            xASSERT(FALSE != m_bRes);
        #endif
    }

    //-------------------------------------
    //bIsFlagProtectFromClose
    {
        #if xTODO
            m_bRes = objHandle.bIsFlagProtectFromClose();
            xASSERT(FALSE == m_bRes);
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
            xASSERT(FALSE != m_bRes);
        #endif
    }

    //-------------------------------------
    //bClose
    {
        #if xTODO
            m_bRes = objHandle.bClose();
            xASSERT(FALSE != m_bRes);
        #endif
    }

    //-------------------------------------
    //bIsValid
    {
        m_bRes = CxHandleT<hvNull>::bIsValid(CxHandle::hGetCurrentProcess());
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bIsValid
    {
        m_bRes = CxHandleT<hvInvalid>::bIsValid(CxHandle::hGetCurrentProcess());
        xASSERT(FALSE == m_bRes);
    }

    //detach handle
    m_bRes = objHandle.bSet(NULL);
    xASSERT(FALSE != m_bRes);
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------

