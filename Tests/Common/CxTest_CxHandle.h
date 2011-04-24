/****************************************************************************
* Class name:  CxTest_CxHandleT
* Description: test CxHandle
* File name:   CxTest_CxHandleT.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxHandleT_CxHandleH
#define CxHandleT_CxHandleH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/Win/CxHandle.h>
#include <xLib/Sync/CxProcess.h>
//---------------------------------------------------------------------------
class CxTest_CxHandleT : public CxTest {
    public:
        CxTest_CxHandleT();
        virtual     ~CxTest_CxHandleT();

        virtual BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxHandleT (constructor)
CxTest_CxHandleT::CxTest_CxHandleT() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxHandleT (destructor)
CxTest_CxHandleT::~CxTest_CxHandleT() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxHandleT::bUnit() {
    CxHandle objHandle;

    //objHandle = CxHandle::hGetCurrentProcess();
    objHandle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, CxProcess::ulGetCurrId());

    {
        ///CxHandle objHandle2(objHandle.m_hHandle);
    }
    {
        ///CxHandle objHandle1(objHandle);
    }


    ////operator HANDLE         () const;

    m_bRes = objHandle.bIsValid();
    xASSERT(FALSE != m_bRes);


    m_bRes = objHandle.bSetInformation(7, HANDLE_FLAG_INHERIT);
    xASSERT(FALSE != m_bRes);

    m_ulRes = objHandle.ulGetInformation();
    xASSERT(HANDLE_FLAG_INHERIT == m_ulRes);



    m_bRes = objHandle.bSetFlagInherit(TRUE);
    xASSERT(FALSE != m_bRes);

    m_bRes = objHandle.bIsFlagInherit();
    xASSERT(FALSE != m_bRes);



    m_bRes = objHandle.bSetFlagProtectFromClose(FALSE);
    xASSERT(FALSE != m_bRes);

    m_bRes = objHandle.bIsFlagProtectFromClose();
    xASSERT(FALSE == m_bRes);



    m_hRes = objHandle.hDuplicate(CxHandle::hGetCurrentProcess(), 0, FALSE, 0);
    xASSERT(NULL != m_hRes);

    ////////m_hRes = objHandle.hDetach();
    ////////xASSERT(NULL != m_hRes);

    ////////m_bRes = objHandle.bAttach(CxHandle::hGetCurrentProcess());
    ////////xASSERT(FALSE != m_bRes);

    m_bRes = objHandle.bClose();
    xASSERT(FALSE != m_bRes);


    //-------------------------------------
    //static
    m_bRes = CxHandle::bIsValid(CxHandle::hGetCurrentProcess());
    xASSERT(FALSE != m_bRes);

    ////TODO: m_bRes = CxHandle::bIsValid(CxHandle::hGetCurrentProcess()); //INVALID_HANDLE_VALUE
    xASSERT(FALSE == m_bRes);

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxHandleT_CxHandleH

