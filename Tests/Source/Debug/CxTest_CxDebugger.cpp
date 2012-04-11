/**
 * \file   CxTest_CxDebugger.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxDebugger.h>


//---------------------------------------------------------------------------
CxTest_CxDebugger::CxTest_CxDebugger() {

}
//---------------------------------------------------------------------------
CxTest_CxDebugger::~CxTest_CxDebugger() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxDebugger::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    // operator <<
    xTEST_CASE(cullCaseLoops)
    {
//        CxDebugger() << xT("\tTest_vars: ")
//                     << 777  << xT(";")
//                     << 5.0f << xT(";")
//                     << std::vector<std::tstring_t>() << xT(";");
        CxDebugger() << 777;
    }

    //-------------------------------------
    //bGetEnabled, bGetEnabled
    xTEST_CASE(cullCaseLoops)
    {
        const bool cbTrue  = true;
        const bool cbFalse = false;

        CxDebugger dbgDebugger;

        m_bRes = dbgDebugger.bGetEnabled();
        xTEST_EQ(cbTrue, m_bRes);

        m_bRes = dbgDebugger.bSetEnabled(cbFalse);
        xTEST_EQ(true, m_bRes);

        m_bRes = dbgDebugger.bGetEnabled();
        xTEST_EQ(cbFalse, m_bRes);

        m_bRes = dbgDebugger.bSetEnabled(cbTrue);
        xTEST_EQ(true, m_bRes);

        m_bRes = dbgDebugger.bGetEnabled();
        xTEST_EQ(cbTrue, m_bRes);
    }

    //-------------------------------------
    //bIsPresent
    xTEST_CASE(cullCaseLoops)
    {   
        CxDebugger dbgDebugger;

        m_bRes = dbgDebugger.bIsPresent();
    }

    //-------------------------------------
    //bIsDebugBuild
    xTEST_CASE(cullCaseLoops)
    {
        CxDebugger dbgDebugger;

        m_bRes = dbgDebugger.bIsDebugBuild();
        #if defined(NDEBUG)
            xTEST_EQ(false, m_bRes);
        #else
            xTEST_EQ(true, m_bRes);
        #endif
    }

    //-------------------------------------
    //bBreak
    xTEST_CASE(cullCaseLoops)
    {
        CxDebugger dbgDebugger;

        #if xTEST_IGNORE
            m_bRes = dbgDebugger.bBreak();
            xTEST_EQ(true, m_bRes);
        #endif
    }

    //-------------------------------------
    //bSetLogPath, sGetLogPath
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csFilePath = xT("");

        CxDebugger dbgDebugger;

        m_sRes = dbgDebugger.sGetLogPath();
        xTEST_EQ(true, m_sRes.empty());

        m_bRes = dbgDebugger.bSetLogPath(csFilePath);
        xTEST_EQ(true, m_bRes);

        m_sRes = dbgDebugger.sGetLogPath();
        xTEST_EQ(csFilePath, m_sRes);

        m_bRes = dbgDebugger.bSetLogPath(xT(""));
        xTEST_EQ(true, m_bRes);

        m_sRes = dbgDebugger.sGetLogPath();
        xTEST_EQ(true, m_sRes.empty());
    }

    //-------------------------------------
    //bReportMake
    xTEST_CASE(cullCaseLoops)
    {
        const CxErrorReport::EType crtType[] = {
            CxErrorReport::rtMsgboxPlain,
            CxErrorReport::rtMsgboxFormated,
            CxErrorReport::rtStdoutPlain,
            CxErrorReport::rtStdoutHtml,
            CxErrorReport::rtLoggingPlain,
            CxErrorReport::rtLoggingHtml
        };

        for (size_t i = 0; i < xARRAY_SIZE(crtType); ++ i) {
            CxErrorReport rpReport(crtType[i], xT("expr"), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT("test"));

            CxDebugger dbgDebugger;

            //m_bRes = dbgDebugger.bReportMake(rpReport);
            //xTEST_EQ(true, m_bRes);
        }
    }

    //-------------------------------------
    //bTrace
    xTEST_CASE(cullCaseLoops)
    {
        #if xTEST_IGNORE
            CxDebugger::bTrace(xT("\tCxDebugger: trace data %")xPR_SIZET, CxRandom::liGetIntEx(0, 10000));
            xTEST_EQ(true, m_bRes);
        #endif
    }

    //-------------------------------------
    //bTrace
    xTEST_CASE(cullCaseLoops)
    {
        #if xTEST_IGNORE || 0
            CxDebugger::bTrace(xT("\tCxDebugger: trace data %s"), CxRandom::sGetString( CxRandom::liGetIntEx(0, 20) ).c_str());
        #endif

        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //bBeep
    xTEST_CASE(cullCaseLoops)
    {
        CxDebugger dbgDebugger;

        m_bRes = dbgDebugger.bBeep();
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //xNOT_IMPLEMENTED_RET
    xTEST_CASE(cullCaseLoops)
    {
        //TODO: xNOT_IMPLEMENTED_RET
    }

    //--------------------------------------------------
    //xASSERT
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sVar1 = xT("xxx");
        std::tstring_t sVar2 = xT("xxx");
        xASSERT(sVar1 == sVar2);
    }

    //--------------------------------------------------
    //xASSERT_RET
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sVar1 = xT("xxx");
        std::tstring_t sVar2 = xT("xxx");
        xASSERT_RET(sVar1 == sVar2, false);
    }

    //--------------------------------------------------
    //xASSERT_DO
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sVar1 = xT("xxx");
        std::tstring_t sVar2 = xT("xxx");
        xASSERT_DO(sVar1 == sVar2, sVar1.clear());
    }

    //--------------------------------------------------
    //xASSERT_MSG
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sVar1 = xT("xxx");
        std::tstring_t sVar2 = xT("xxx");
        xASSERT_MSG(sVar1 == sVar2, xT("Simple message"));
    }

    //--------------------------------------------------
    //xASSERT_MSG_RET
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sVar1 = xT("xxx");
        std::tstring_t sVar2 = xT("xxx");
        xASSERT_MSG_RET(sVar1 == sVar2, xT("Simple message"), false);
    }

    //--------------------------------------------------
    //xASSERT_MSG_DO
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sVar1 = xT("xxx");
        std::tstring_t sVar2 = xT("xxx");
        xASSERT_MSG_DO(sVar1 == sVar2, xT("Simple message"), sVar1.swap(sVar2));
    }

    //--------------------------------------------------
    //like xTEST_EQ macroses

    //with int
    {
        xTEST_CASE(cullCaseLoops)
        {
            int iVar1 = 1;
            int iVar2 = 1;
            xTEST_EQ(iVar1, iVar2);
        }

        xTEST_CASE(cullCaseLoops)
        {
            int iVar1 = 0;
            int iVar2 = 1;
            xTEST_DIFF(iVar1, iVar2);
        }

        xTEST_CASE(cullCaseLoops)
        {
            int iVar1 = 1;
            int iVar2 = 122;
            xTEST_LESS(iVar1, iVar2);
        }

        xTEST_CASE(cullCaseLoops)
        {
            int iVar1 = 110;
            int iVar2 = 10;
            xTEST_GREATER(iVar1, iVar2);
        }

        xTEST_CASE(cullCaseLoops)
        {
            int iVar1 = 50;
            int iVar2 = 122;
            xTEST_LESS_EQ(iVar1, iVar2);

            int iVar3 = 200;
            int iVar4 = 200;
            xTEST_LESS_EQ(iVar3, iVar4);
        }

        xTEST_CASE(cullCaseLoops)
        {
            int iVar1 = 500;
            int iVar2 = 147;
            xTEST_GREATER_EQ(iVar1, iVar2);

            int iVar3 = 77777;
            int iVar4 = 77777;
            xTEST_GREATER_EQ(iVar3, iVar4);
        }
    }

    //--------------------------------------------------
    //like xTEST_EQ macroses

    //with std::tstring_t
    {
        xTEST_CASE(cullCaseLoops)
        {
            std::tstring_t sVar1 = xT("aaa");
            std::tstring_t sVar2 = xT("aaa");
            xTEST_EQ(sVar1, sVar2);
        }

        xTEST_CASE(cullCaseLoops)
        {
            std::tstring_t sVar1 = xT("bbb");
            std::tstring_t sVar2 = xT("BBB");
            xTEST_DIFF(sVar1, sVar2);
        }

        xTEST_CASE(cullCaseLoops)
        {
            std::tstring_t sVar1 = xT("aaa");
            std::tstring_t sVar2 = xT("ccc");
            xTEST_LESS(sVar1, sVar2);
        }

        xTEST_CASE(cullCaseLoops)
        {
            std::tstring_t sVar1 = xT("bbb");
            std::tstring_t sVar2 = xT("aaa");
            xTEST_GREATER(sVar1, sVar2);
        }

        xTEST_CASE(cullCaseLoops)
        {
            std::tstring_t sVar1 = xT("aaa");
            std::tstring_t sVar2 = xT("aaa");
            xTEST_LESS_EQ(sVar1, sVar2);

            std::tstring_t sVar3 = xT("aaa");
            std::tstring_t sVar4 = xT("ggg");
            xTEST_LESS_EQ(sVar3, sVar4);
        }

        xTEST_CASE(cullCaseLoops)
        {
            std::tstring_t sVar1 = xT("aaa");
            std::tstring_t sVar2 = xT("aaa");
            xTEST_GREATER_EQ(sVar1, sVar2);

            std::tstring_t sVar3 = xT("hhhh");
            std::tstring_t sVar4 = xT("aaa");
            xTEST_GREATER_EQ(sVar3, sVar4);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
