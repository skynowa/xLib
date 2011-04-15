/****************************************************************************
* Class name:  CxTest_CxDebugger
* Description: test CxDebugger
* File name:   CxTest_CxDebugger.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxTest_CxDebuggerH
#define CxTest_CxDebuggerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Debug/CxDebugger.h>
//---------------------------------------------------------------------------
class CxTest_CxDebugger : public CxTest {
	public:
		CxTest_CxDebugger();
	   ~CxTest_CxDebugger();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxDebugger (constructor)
CxTest_CxDebugger::CxTest_CxDebugger() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxDebugger (destructor)
CxTest_CxDebugger::~CxTest_CxDebugger() {

}
//----------------------------------------------------------------------------------------------------
BOOL bAssert() {
    xASSERT(FALSE);

    return TRUE;
}
//----------------------------------------------------------------------------------------------------
BOOL bAssert_Msg() {
    xASSERT_MSG(FALSE, xT("simple note"));

    return TRUE;
}
//----------------------------------------------------------------------------------------------------
BOOL bAssert_Do() {
    xASSERT_DO(FALSE, tcout << xT("simple job") << tendl);

    return TRUE;
}
//----------------------------------------------------------------------------------------------------
BOOL bAssert_Ret() {
    xASSERT_RET(FALSE, FALSE);

    return TRUE;
}
//----------------------------------------------------------------------------------------------------
BOOL bAssert_Msg_Ret() {
    xASSERT_MSG_RET(FALSE, xT("simple note"), FALSE);

    return TRUE;
}
//----------------------------------------------------------------------------------------------------
BOOL bNotImplemented() {
    xNOT_IMPLEMENTED_RET(FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxDebugger::bUnit() {
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
    for (int  i = 0;  i < 10; ++ i) {
        CxDebugger::bTrace(xT("CxDebugger: %i"), i);
    }

    //--------------------------------------------------
    //xNOT_IMPLEMENTED_RET
    {
        bNotImplemented();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxDebuggerH



 	//-------------------------------------
	//xASSERT(exp)     
	//xASSERT(FALSE);

	////-------------------------------------
	////XASSERT_EX(exp, comment)   
	//xASSERT_MSG(FALSE, xT("Simple xASSERT_EX comment"));


	////-------------------------------------
	////xASSERT_RET(exp, return_exp) 
	//xASSERT_RET(TRUE, FALSE);

	////-------------------------------------
	////XASSERT_EX_RET(exp, comment, return_exp)
	//xASSERT_MSG_RET(TRUE, xT("Simple xASSERT_EX_RET comment"), FALSE);

	////-------------------------------------
	////xASSERT_DO(exp, do_instructions) 
	//INT iCount_AssertDo = 0;
	//for (iCount_AssertDo = 0; iCount_AssertDo < 100; iCount_AssertDo ++) {
	//	xASSERT_DO(iCount_AssertDo < 50, break);
	//}

	////-------------------------------------
	////xCHECK_RET(exp, return_exp)  
	//xCHECK_RET(FALSE, FALSE);

	////-------------------------------------
	////xCHECK_DO(exp, do_instructions)   
	//INT iCount_CheckDo = 0;
	//for (iCount_CheckDo = 0; iCount_CheckDo < 100; iCount_CheckDo ++) {
	//	xCHECK_DO(iCount_CheckDo > 40, break);
	//}
