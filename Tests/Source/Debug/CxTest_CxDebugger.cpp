/****************************************************************************
* Class name:  CxTest_CxDebugger
* Description: test CxDebugger
* File name:   CxTest_CxDebugger.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Debug/CxTest_CxDebugger.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxDebugger
CxTest_CxDebugger::CxTest_CxDebugger() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxDebugger
CxTest_CxDebugger::~CxTest_CxDebugger() {

}
//----------------------------------------------------------------------------------------------------
BOOL 
bAssert() {
    xASSERT(FALSE);

    return TRUE;
}
//----------------------------------------------------------------------------------------------------
BOOL 
bAssert_Msg() {
    xASSERT_MSG(FALSE, xT("simple note"));

    return TRUE;
}
//----------------------------------------------------------------------------------------------------
BOOL 
bAssert_Do() {
    xASSERT_DO(FALSE, tcout << xT("simple job") << tendl);

    return TRUE;
}
//----------------------------------------------------------------------------------------------------
BOOL 
bAssert_Ret() {
    xASSERT_RET(FALSE, FALSE);

    return TRUE;
}
//----------------------------------------------------------------------------------------------------
BOOL 
bAssert_Msg_Ret() {
    xASSERT_MSG_RET(FALSE, xT("simple note"), FALSE);

    return TRUE;
}
//----------------------------------------------------------------------------------------------------
BOOL 
bNotImplemented() {
    xNOT_IMPLEMENTED_RET(FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxDebugger::bUnit() {
    //--------------------------------------------------
    //bBeep
    {
        m_bRes = CxDebugger::bBeep();
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //xASSERT
    {
        m_bRes = bAssert();
    }

    //--------------------------------------------------
    //xASSERT_MSG
    {
        m_bRes = bAssert_Msg();
    }

    //--------------------------------------------------
    //xASSERT_DO
    {
        m_bRes = bAssert_Do();
    }

    //--------------------------------------------------
    //xASSERT_RET
    {
        m_bRes = bAssert_Ret();
    }

    //--------------------------------------------------
    //xASSERT_MSG_RET
    {
        m_bRes = bAssert_Msg_Ret();
    }

    //--------------------------------------------------
    //bTrace
    for (size_t i = 0;  i < 10; ++ i) {
        CxDebugger::bTrace(xT("CxDebugger: %zu"), i);
    }

    //--------------------------------------------------
    //xNOT_IMPLEMENTED_RET
    {
        bNotImplemented();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
