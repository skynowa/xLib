/**
 * \file   CxTest_CxDebugger.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxDebugger.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxDebugger::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxDebugger::isEnabled setEnabled", a_caseLoops)
    {
        cbool_t cbTrue  = true;
        cbool_t cbFalse = false;

        CxDebugger dbgDebugger;

        m_bRv = dbgDebugger.isEnabled();
        xTEST_EQ(cbTrue, m_bRv);

        dbgDebugger.setEnabled(cbFalse);

        m_bRv = dbgDebugger.isEnabled();
        xTEST_EQ(cbFalse, m_bRv);

        dbgDebugger.setEnabled(cbTrue);

        m_bRv = dbgDebugger.isEnabled();
        xTEST_EQ(cbTrue, m_bRv);
    }

    xTEST_CASE("CxDebugger::isActive", a_caseLoops)
    {
        CxDebugger dbgDebugger;

        m_bRv = dbgDebugger.isActive();
    }

    xTEST_CASE("CxDebugger::isDebugBuild", a_caseLoops)
    {
        CxDebugger dbgDebugger;

        m_bRv = dbgDebugger.isDebugBuild();
        #if defined(NDEBUG)
            xTEST_EQ(false, m_bRv);
        #else
            xTEST_EQ(true, m_bRv);
        #endif
    }

    xTEST_CASE("CxDebugger::breakPoint", a_caseLoops)
    {
        CxDebugger dbgDebugger;

        #if xTEST_IGNORE
            dbgDebugger.breakPoint();
        #endif
    }

    xTEST_CASE("CxDebugger::setLogPath logPath", a_caseLoops)
    {
        std::ctstring_t csFilePath;

        CxDebugger dbgDebugger;

        m_sRv = dbgDebugger.logPath();
        xTEST_EQ(true, m_sRv.empty());

        dbgDebugger.setLogPath(csFilePath);

        m_sRv = dbgDebugger.logPath();
        xTEST_EQ(csFilePath, m_sRv);

        dbgDebugger.setLogPath(xT(""));

        m_sRv = dbgDebugger.logPath();
        xTEST_EQ(true, m_sRv.empty());
    }

    xTEST_CASE("CxDebugger::reportMake", a_caseLoops)
    {
        const CxErrorReport::ExType crtType[] = {
            CxErrorReport::rtMsgbox,
            CxErrorReport::rtStdout,
            CxErrorReport::rtLog
        };

        for (size_t i = 0; i < xARRAY_SIZE(crtType); ++ i) {
            ulong_t lastError = CxLastError::get();

            ulong_t val1 = 10UL;
            ulong_t val2 = 20UL;

            CxErrorReport rpReport(crtType[i], xT("val1"), xT("val2"), val1, val2, xT("=="),
                lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(),
                xT(""));

            CxDebugger dbgDebugger;

            // m_bRv = dbgDebugger.reportMake(rpReport);
            // xTEST_EQ(true, m_bRv);
        }
    }
#if 0
    //--------------------------------------------------
    //like xTEST_EQ macroses

    //with int_t
    {
        xTEST_CASE("CxDebugger::xTEST_EQ_", a_caseLoops)
        {
            int_t iVar1 = 1;
            int_t iVar2 = 1;
            xTEST_EQ(iVar1, iVar2);
        }

        xTEST_CASE("CxDebugger::xTEST_DIFF_", a_caseLoops)
        {
            int_t iVar1 = 0;
            int_t iVar2 = 1;
            xTEST_DIFF(iVar1, iVar2);
        }

        xTEST_CASE("CxDebugger::xTEST_LESS_", a_caseLoops)
        {
            int_t iVar1 = 1;
            int_t iVar2 = 122;
            xTEST_LESS(iVar1, iVar2);
        }

        xTEST_CASE("CxDebugger::xTEST_GR_", a_caseLoops)
        {
            int_t iVar1 = 110;
            int_t iVar2 = 10;
            xTEST_GR(iVar1, iVar2);
        }

        xTEST_CASE("CxDebugger::xTEST_LESS_EQ_", a_caseLoops)
        {
            int_t iVar1 = 50;
            int_t iVar2 = 122;
            xTEST_LESS_EQ(iVar1, iVar2);

            int_t iVar3 = 200;
            int_t iVar4 = 200;
            xTEST_LESS_EQ(iVar3, iVar4);
        }

        xTEST_CASE("CxDebugger::xTEST_GR_EQ_", a_caseLoops)
        {
            int_t iVar1 = 500;
            int_t iVar2 = 147;
            xTEST_GR_EQ(iVar1, iVar2);

            int_t iVar3 = 77777;
            int_t iVar4 = 77777;
            xTEST_GR_EQ(iVar3, iVar4);
        }
    }

    //--------------------------------------------------
    //like xTEST_EQ macroses

    //with std::tstring_t
    {
        xTEST_CASE("CxDebugger::xTEST_EQ_", a_caseLoops)
        {
            std::tstring_t sVar1 = xT("aaa");
            std::tstring_t sVar2 = xT("aaa");
            xTEST_EQ(sVar1, sVar2);
        }

        xTEST_CASE("CxDebugger::xTEST_DIFF_", a_caseLoops)
        {
            std::tstring_t sVar1 = xT("bbb");
            std::tstring_t sVar2 = xT("BBB");
            xTEST_DIFF(sVar1, sVar2);
        }

        xTEST_CASE("CxDebugger::xTEST_LESS_", a_caseLoops)
        {
            std::tstring_t sVar1 = xT("aaa");
            std::tstring_t sVar2 = xT("ccc");
            xTEST_LESS(sVar1, sVar2);
        }

        xTEST_CASE("CxDebugger::xTEST_GR_", a_caseLoops)
        {
            std::tstring_t sVar1 = xT("bbb");
            std::tstring_t sVar2 = xT("aaa");
            xTEST_GR(sVar1, sVar2);
        }

        xTEST_CASE("CxDebugger::xTEST_LESS_EQ_", a_caseLoops)
        {
            std::tstring_t sVar1 = xT("aaa");
            std::tstring_t sVar2 = xT("aaa");
            xTEST_LESS_EQ(sVar1, sVar2);

            std::tstring_t sVar3 = xT("aaa");
            std::tstring_t sVar4 = xT("ggg");
            xTEST_LESS_EQ(sVar3, sVar4);
        }

        xTEST_CASE("CxDebugger::xTEST_GR_EQ_", a_caseLoops)
        {
            std::tstring_t sVar1 = xT("aaa");
            std::tstring_t sVar2 = xT("aaa");
            xTEST_GR_EQ(sVar1, sVar2);

            std::tstring_t sVar3 = xT("hhhh");
            std::tstring_t sVar4 = xT("aaa");
            xTEST_GR_EQ(sVar3, sVar4);
        }
    }
#endif
}
//------------------------------------------------------------------------------
