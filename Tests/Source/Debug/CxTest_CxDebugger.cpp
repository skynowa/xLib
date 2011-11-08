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
CxTest_CxDebugger::CxTest_CxDebugger() {

}
//---------------------------------------------------------------------------
CxTest_CxDebugger::~CxTest_CxDebugger() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxDebugger::bUnit(
    const ULONGLONG cullBlockLoops
)
{

    //-------------------------------------
    //bGetEnabled, bGetEnabled
    xTEST_BLOCK(cullBlockLoops)
    {
        const BOOL cbTrue  = TRUE;
        const BOOL cbFalse = FALSE;

        m_bRes = CxDebugger::bGetEnabled();
        xASSERT_EQ(cbTrue, m_bRes);

        m_bRes = CxDebugger::bSetEnabled(cbFalse);
        xASSERT_DIFF(FALSE, m_bRes);

        m_bRes = CxDebugger::bGetEnabled();
        xASSERT_EQ(cbFalse, m_bRes);

        m_bRes = CxDebugger::bSetEnabled(cbTrue);
        xASSERT_DIFF(FALSE, m_bRes);

        m_bRes = CxDebugger::bGetEnabled();
        xASSERT_EQ(cbTrue, m_bRes);
    }

    //-------------------------------------
    //bIsPresent
    xTEST_BLOCK(cullBlockLoops)
    {
        //TODO: bIsPresent
    }

    //-------------------------------------
    //bBreak
    xTEST_BLOCK(cullBlockLoops)
    {
        //TODO: bBreak
    }

    //-------------------------------------
    //bSetLogPath, sGetLogPath
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring csFilePath = xT("");

        m_sRes = CxDebugger::sGetLogPath();
        xASSERT_EQ(true, m_sRes.empty());

        m_bRes = CxDebugger::bSetLogPath(csFilePath);
        xASSERT_DIFF(FALSE, m_bRes);

        m_sRes = CxDebugger::sGetLogPath();
        xASSERT_EQ(csFilePath, m_sRes);

        m_bRes = CxDebugger::bSetLogPath(xT(""));
        xASSERT_DIFF(FALSE, m_bRes);

        m_sRes = CxDebugger::sGetLogPath();
        xASSERT_EQ(true, m_sRes.empty());
    }

    //-------------------------------------
    //bReportMake
    xTEST_BLOCK(cullBlockLoops)
    {
        const CxReport::EType crtType[] = {
            CxReport::rtMsgboxPlain,
            CxReport::rtMsgboxFormated,
            CxReport::rtStdoutPlain,
            CxReport::rtStdoutHtml,
            CxReport::rtLoggingPlain,
            CxReport::rtLoggingHtml
        };

        for (size_t i = 0; i < xARRAY_SIZE(crtType); ++ i) {
	        CxReport rpReport(crtType[i], xT("expr"), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT("test"));

	        //m_bRes = CxDebugger::bReportMake(rpReport);
            //xASSERT_DIFF(FALSE, m_bRes);
        }
    }

    //-------------------------------------
    //bTrace
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEST_IGNORE
            CxDebugger::bTrace(xT("\tCxDebugger: trace data %")xPR_SIZET, CxRandom::liGetIntEx(0, 10000));
            xASSERT_DIFF(FALSE, m_bRes);
        #endif
    }

    //-------------------------------------
    //bTrace
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEST_IGNORE || 0
            CxDebugger::bTrace(xT("\tCxDebugger: trace data %s"), CxRandom::sGetString( CxRandom::liGetIntEx(0, 20) ).c_str());
        #endif

        xASSERT_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bBeep
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxDebugger::bBeep();
        xASSERT_DIFF(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //xNOT_IMPLEMENTED_RET
    xTEST_BLOCK(cullBlockLoops)
    {
        //TODO: xNOT_IMPLEMENTED_RET
    }

    //--------------------------------------------------
    //xASSERT
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sVar1 = xT("xxx");
        std::tstring sVar2 = xT("xxx");
        xASSERT(sVar1 == sVar2);
    }

    //--------------------------------------------------
    //xASSERT_RET
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sVar1 = xT("xxx");
        std::tstring sVar2 = xT("xxx");
        xASSERT_RET(sVar1 == sVar2, FALSE);
    }

    //--------------------------------------------------
    //xASSERT_DO
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sVar1 = xT("xxx");
        std::tstring sVar2 = xT("xxx");
        xASSERT_DO(sVar1 == sVar2, sVar1.clear());
    }

    //--------------------------------------------------
    //xASSERT_MSG
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sVar1 = xT("xxx");
        std::tstring sVar2 = xT("xxx");
        xASSERT_MSG(sVar1 == sVar2, xT("Simple message"));
    }

    //--------------------------------------------------
    //xASSERT_MSG_RET
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sVar1 = xT("xxx");
        std::tstring sVar2 = xT("xxx");
        xASSERT_MSG_RET(sVar1 == sVar2, xT("Simple message"), FALSE);
    }

    //--------------------------------------------------
    //xASSERT_MSG_DO
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sVar1 = xT("xxx");
        std::tstring sVar2 = xT("xxx");
        xASSERT_MSG_DO(sVar1 == sVar2, xT("Simple message"), sVar1.swap(sVar2));
    }

    //--------------------------------------------------
    //like xASSERT_EQ macroses

    //with INT
    {
        xTEST_BLOCK(cullBlockLoops)
	    {
		    INT iVar1 = 1;
		    INT iVar2 = 1;
		    xASSERT_EQ(iVar1, iVar2);
	    }

        xTEST_BLOCK(cullBlockLoops)
	    {
		    INT iVar1 = 0;
		    INT iVar2 = 1;
		    xASSERT_DIFF(iVar1, iVar2);
	    }

        xTEST_BLOCK(cullBlockLoops)
	    {
		    INT iVar1 = 1;
		    INT iVar2 = 122;
		    xASSERT_LESS(iVar1, iVar2);
	    }

        xTEST_BLOCK(cullBlockLoops)
	    {
		    INT iVar1 = 110;
		    INT iVar2 = 10;
		    xASSERT_GREATER(iVar1, iVar2);
	    }

        xTEST_BLOCK(cullBlockLoops)
	    {
		    INT iVar1 = 50;
		    INT iVar2 = 122;
		    xASSERT_LESS_EQ(iVar1, iVar2);

            INT iVar3 = 200;
		    INT iVar4 = 200;
		    xASSERT_LESS_EQ(iVar3, iVar4);
	    }

        xTEST_BLOCK(cullBlockLoops)
	    {
		    INT iVar1 = 500;
		    INT iVar2 = 147;
		    xASSERT_GREATER_EQ(iVar1, iVar2);

            INT iVar3 = 77777;
		    INT iVar4 = 77777;
		    xASSERT_GREATER_EQ(iVar3, iVar4);
	    }
    }

    //--------------------------------------------------
    //like xASSERT_EQ macroses

    //with std::tstring
    {
        xTEST_BLOCK(cullBlockLoops)
	    {
		    std::tstring sVar1 = xT("aaa");
		    std::tstring sVar2 = xT("aaa");
		    xASSERT_EQ(sVar1, sVar2);
	    }

        xTEST_BLOCK(cullBlockLoops)
	    {
		    std::tstring sVar1 = xT("bbb");
		    std::tstring sVar2 = xT("BBB");
		    xASSERT_DIFF(sVar1, sVar2);
	    }

        xTEST_BLOCK(cullBlockLoops)
	    {
		    std::tstring sVar1 = xT("aaa");
		    std::tstring sVar2 = xT("ccc");
		    xASSERT_LESS(sVar1, sVar2);
	    }

        xTEST_BLOCK(cullBlockLoops)
	    {
		    std::tstring sVar1 = xT("bbb");
		    std::tstring sVar2 = xT("aaa");
		    xASSERT_GREATER(sVar1, sVar2);
	    }

        xTEST_BLOCK(cullBlockLoops)
	    {
		    std::tstring sVar1 = xT("aaa");
		    std::tstring sVar2 = xT("aaa");
		    xASSERT_LESS_EQ(sVar1, sVar2);

            std::tstring sVar3 = xT("aaa");
		    std::tstring sVar4 = xT("ggg");
		    xASSERT_LESS_EQ(sVar3, sVar4);
	    }

        xTEST_BLOCK(cullBlockLoops)
	    {
		    std::tstring sVar1 = xT("aaa");
		    std::tstring sVar2 = xT("aaa");
		    xASSERT_GREATER_EQ(sVar1, sVar2);

            std::tstring sVar3 = xT("hhhh");
		    std::tstring sVar4 = xT("aaa");
		    xASSERT_GREATER_EQ(sVar3, sVar4);
	    }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
