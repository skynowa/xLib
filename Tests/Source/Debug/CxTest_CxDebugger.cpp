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
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxDebugger::bUnit() {

    //-------------------------------------
    //bGetEnabled, bGetEnabled
    {
        const BOOL cbTrue  = TRUE;
        const BOOL cbFalse = FALSE;

        m_bRes = CxDebugger::bGetEnabled();
        xASSERT(cbTrue == m_bRes);

        m_bRes = CxDebugger::bSetEnabled(cbFalse);
        xASSERT_EQUAL(TRUE, m_bRes);

        m_bRes = CxDebugger::bGetEnabled();
        xASSERT(cbFalse == m_bRes);

        m_bRes = CxDebugger::bSetEnabled(cbTrue);
        xASSERT_EQUAL(TRUE, m_bRes);

        m_bRes = CxDebugger::bGetEnabled();
        xASSERT(cbTrue == m_bRes);
    }

    //-------------------------------------
    //bIsPresent
    {
        //TODO: bIsPresent
    }

    //-------------------------------------
    //bBreak
    {
        //TODO: bBreak
    }

    //-------------------------------------
    //bSetLogPath, sGetLogPath
    {
        const tString csFilePath = xT("");

        m_sRes = CxDebugger::sGetLogPath();
        xASSERT(true == m_sRes.empty());

        m_bRes = CxDebugger::bSetLogPath(csFilePath);
        xASSERT_EQUAL(TRUE, m_bRes);

        m_sRes = CxDebugger::sGetLogPath();
        xASSERT(csFilePath == m_sRes);

        m_bRes = CxDebugger::bSetLogPath(xT(""));
        xASSERT_EQUAL(TRUE, m_bRes);

        m_sRes = CxDebugger::sGetLogPath();
        xASSERT(true == m_sRes.empty());
    }

    //-------------------------------------
    //bReportMake
    {
        const CxReport::EType crtType[] = {
            CxReport::rtMsgboxPlain,
            CxReport::rtMsgboxRtf,
            CxReport::rtStdoutPlain,
            CxReport::rtStdoutHtml,
            CxReport::rtLoggingPlain,
            CxReport::rtLoggingHtml
        };

        for (size_t i = 0; i < 100; ++ i) {
	        CxReport rpReport(crtType[i], xT("expr"), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));

	        ////m_bRes = CxDebugger::bReportMake(rpReport);
            ////xASSERT_EQUAL(TRUE, m_bRes);
        }
    }

    //-------------------------------------
    //bTrace
    {
        for (size_t i = 0;  i < 10; ++ i) {
            CxDebugger::bTrace(xT("\tCxDebugger: %")xPR_SIZET, i);
        }
    }

    //-------------------------------------
    //bTrace
    {
        for (size_t i = 0;  i < 10; ++ i) {
            CxDebugger::bTrace(xT("\t") + CxString::lexical_cast(i));
        }
    }

    //-------------------------------------
    //bBeep
    {
        m_bRes = CxDebugger::bBeep();
        xASSERT_EQUAL(TRUE, m_bRes);
    }

    //-------------------------------------
    //vStdVectorPrintT
    {
        m_vecsRes.push_back(xT("qqqq"));
        m_vecsRes.push_back(xT("wwww"));
        m_vecsRes.push_back(xT("eeee"));
        m_vecsRes.push_back(xT("rrrr"));
        m_vecsRes.push_back(xT("tttt"));

        ////CxDebugger::vStdVectorPrintT(m_vecsRes);
    }

    //-------------------------------------
    //vStdMapPrintT
    {
        m_msRes.insert( std::pair<tString, tString>(xT("Key0"), xT("Value0")) );
        m_msRes.insert( std::pair<tString, tString>(xT("Key1"), xT("Value1")) );
        m_msRes.insert( std::pair<tString, tString>(xT("Key2"), xT("Value2")) );
        m_msRes.insert( std::pair<tString, tString>(xT("Key3"), xT("Value3")) );
        m_msRes.insert( std::pair<tString, tString>(xT("Key4"), xT("Value4")) );

        ////CxDebugger::vStdMapPrintT(m_msRes);
    }

    //-------------------------------------
    //vStdMultiMapPrintT
    {
        m_mmsRes.insert( std::pair<tString, tString>(xT("Key0"), xT("Value0")) );
        m_mmsRes.insert( std::pair<tString, tString>(xT("Key1"), xT("Value1")) );
        m_mmsRes.insert( std::pair<tString, tString>(xT("Key2"), xT("Value2")) );
        m_mmsRes.insert( std::pair<tString, tString>(xT("Key0"), xT("Value0")) );
        m_mmsRes.insert( std::pair<tString, tString>(xT("Key1"), xT("Value1")) );

        ////CxDebugger::vStdMultiMapPrintT(m_mmsRes);
    }

    //--------------------------------------------------
    //xNOT_IMPLEMENTED_RET
    {
        //TODO: xNOT_IMPLEMENTED_RET
    }

    //--------------------------------------------------
    //xASSERT
    {
        tString sVar1 = xT("xxx");
        tString sVar2 = xT("xxx");
        xASSERT(sVar1 == sVar2);
    }

    //--------------------------------------------------
    //xASSERT_RET
    {
        tString sVar1 = xT("xxx");
        tString sVar2 = xT("xxx");
        xASSERT_RET(sVar1 == sVar2, FALSE);
    }

    //--------------------------------------------------
    //xASSERT_DO
    {
        tString sVar1 = xT("xxx");
        tString sVar2 = xT("xxx");
        xASSERT_DO(sVar1 == sVar2, sVar1.clear());
    }

    //--------------------------------------------------
    //xASSERT_MSG
    {
        tString sVar1 = xT("xxx");
        tString sVar2 = xT("xxx");
        xASSERT_MSG(sVar1 == sVar2, xT("Simple message"));
    }

    //--------------------------------------------------
    //xASSERT_MSG_RET
    {
        tString sVar1 = xT("xxx");
        tString sVar2 = xT("xxx");
        xASSERT_MSG_RET(sVar1 == sVar2, xT("Simple message"), FALSE);
    }

    //--------------------------------------------------
    //xASSERT_MSG_DO
    {
        tString sVar1 = xT("xxx");
        tString sVar2 = xT("xxx");
        xASSERT_MSG_DO(sVar1 == sVar2, xT("Simple message"), sVar1.swap(sVar2));
    }

    //--------------------------------------------------
    //like xASSERT_EQUAL macroses

    //with INT
    {
	    {
		    INT iVar1 = 1;
		    INT iVar2 = 1;
		    xASSERT_EQUAL(iVar1, iVar2);
	    }

	    {
		    INT iVar1 = 0;
		    INT iVar2 = 1;
		    xASSERT_NOT_EQUAL(iVar1, iVar2);
	    }

	    {
		    INT iVar1 = 1;
		    INT iVar2 = 122;
		    xASSERT_LESS(iVar1, iVar2);
	    }

	    {
		    INT iVar1 = 110;
		    INT iVar2 = 10;
		    xASSERT_GREATER(iVar1, iVar2);
	    }

	    {
		    INT iVar1 = 50;
		    INT iVar2 = 122;
		    xASSERT_LESS_EQUAL(iVar1, iVar2);

            INT iVar3 = 200;
		    INT iVar4 = 200;
		    xASSERT_LESS_EQUAL(iVar3, iVar4);
	    }

	    {
		    INT iVar1 = 500;
		    INT iVar2 = 147;
		    xASSERT_GREATER_EQUAL(iVar1, iVar2);

            INT iVar3 = 77777;
		    INT iVar4 = 77777;
		    xASSERT_GREATER_EQUAL(iVar3, iVar4);
	    }
    }

    //--------------------------------------------------
    //like xASSERT_EQUAL macroses

    //with tString
    {
	    {
		    tString sVar1 = xT("aaa");
		    tString sVar2 = xT("aaa");
		    xASSERT_EQUAL(sVar1, sVar2);
	    }

	    {
		    tString sVar1 = xT("bbb");
		    tString sVar2 = xT("BBB");
		    xASSERT_NOT_EQUAL(sVar1, sVar2);
	    }

	    {
		    tString sVar1 = xT("aaa");
		    tString sVar2 = xT("ccc");
		    xASSERT_LESS(sVar1, sVar2);
	    }

	    {
		    tString sVar1 = xT("bbb");
		    tString sVar2 = xT("aaa");
		    xASSERT_GREATER(sVar1, sVar2);
	    }

	    {
		    tString sVar1 = xT("aaa");
		    tString sVar2 = xT("aaa");
		    xASSERT_LESS_EQUAL(sVar1, sVar2);

            tString sVar3 = xT("aaa");
		    tString sVar4 = xT("ggg");
		    xASSERT_LESS_EQUAL(sVar3, sVar4);
	    }

	    {
		    tString sVar1 = xT("aaa");
		    tString sVar2 = xT("aaa");
		    xASSERT_GREATER_EQUAL(sVar1, sVar2);

            tString sVar3 = xT("hhhh");
		    tString sVar4 = xT("aaa");
		    xASSERT_GREATER_EQUAL(sVar3, sVar4);
	    }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
