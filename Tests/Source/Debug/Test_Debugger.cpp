/**
 * \file   Test_Debugger.cpp
 * \brief
 */


#include <Test/Debug/Test_Debugger.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Debugger::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("isEnabled, setEnabled", a_caseLoops)
    {
        cbool_t cbTrue  = true;
        cbool_t cbFalse = false;

        Debugger debugger;

        m_bRv = debugger.isEnabled();
        xTEST_EQ(cbTrue, m_bRv);

        debugger.setEnabled(cbFalse);

        m_bRv = debugger.isEnabled();
        xTEST_EQ(cbFalse, m_bRv);

        debugger.setEnabled(cbTrue);

        m_bRv = debugger.isEnabled();
        xTEST_EQ(cbTrue, m_bRv);
    }

    xTEST_CASE("isActive", a_caseLoops)
    {
        Debugger debugger;

        m_bRv = debugger.isActive();
    }

    xTEST_CASE("coreDumpsEnable", a_caseLoops)
    {
        Debugger debugger;

        debugger.coreDumpsEnable(false);
        debugger.coreDumpsEnable(true);
    }

    xTEST_CASE("breakPoint", a_caseLoops)
    {
        Debugger debugger;

        #if xTEST_IGNORE
            debugger.breakPoint();
        #endif
    }

    xTEST_CASE("setLogPath, logPath", a_caseLoops)
    {
        std::ctstring_t filePath;

        Debugger debugger;

        m_sRv = debugger.logPath();
        xTEST_EQ(true, m_sRv.empty());

        debugger.setLogPath(filePath);

        m_sRv = debugger.logPath();
        xTEST_EQ(filePath, m_sRv);

        debugger.setLogPath(xT(""));

        m_sRv = debugger.logPath();
        xTEST_EQ(true, m_sRv.empty());
    }

    xTEST_CASE("reportMake", a_caseLoops)
    {
        const ErrorReport::ExType type[] = {
            ErrorReport::rtMsgbox,
            ErrorReport::rtStdout,
            ErrorReport::rtLog
        };

        for (size_t i = 0; i < xARRAY_SIZE(type); ++ i) {
            ulong_t nativeError = NativeError::get();

            ulong_t val1 = 10UL;
            ulong_t val2 = 20UL;

            ErrorReport report(type[i], xT("val1"), xT("val2"), val1, val2, xT("=="),
                nativeError, xFILE, xLINE, xFUNCTION, StackTrace().toString(), xT(""));

            Debugger debugger;
            debugger.setEnabled(false);
            debugger.reportMake(report);
        }
    }

#if 0
    //--------------------------------------------------
    // like xTEST_EQ macroses

    // with int_t
    {
        xTEST_CASE("xTEST_EQ_", a_caseLoops)
        {
            int_t iVar1 = 1;
            int_t iVar2 = 1;
            xTEST_EQ(iVar1, iVar2);
        }

        xTEST_CASE("xTEST_DIFF_", a_caseLoops)
        {
            int_t iVar1 = 0;
            int_t iVar2 = 1;
            xTEST_DIFF(iVar1, iVar2);
        }

        xTEST_CASE("xTEST_LESS_", a_caseLoops)
        {
            int_t iVar1 = 1;
            int_t iVar2 = 122;
            xTEST_LESS(iVar1, iVar2);
        }

        xTEST_CASE("xTEST_GR_", a_caseLoops)
        {
            int_t iVar1 = 110;
            int_t iVar2 = 10;
            xTEST_GR(iVar1, iVar2);
        }

        xTEST_CASE("xTEST_LESS_EQ_", a_caseLoops)
        {
            int_t iVar1 = 50;
            int_t iVar2 = 122;
            xTEST_LESS_EQ(iVar1, iVar2);

            int_t iVar3 = 200;
            int_t iVar4 = 200;
            xTEST_LESS_EQ(iVar3, iVar4);
        }

        xTEST_CASE("xTEST_GR_EQ_", a_caseLoops)
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
    // like xTEST_EQ macroses

    // with std::tstring_t
    {
        xTEST_CASE("xTEST_EQ_", a_caseLoops)
        {
            std::tstring_t sVar1 = xT("aaa");
            std::tstring_t sVar2 = xT("aaa");
            xTEST_EQ(sVar1, sVar2);
        }

        xTEST_CASE("xTEST_DIFF_", a_caseLoops)
        {
            std::tstring_t sVar1 = xT("bbb");
            std::tstring_t sVar2 = xT("BBB");
            xTEST_DIFF(sVar1, sVar2);
        }

        xTEST_CASE("xTEST_LESS_", a_caseLoops)
        {
            std::tstring_t sVar1 = xT("aaa");
            std::tstring_t sVar2 = xT("ccc");
            xTEST_LESS(sVar1, sVar2);
        }

        xTEST_CASE("xTEST_GR_", a_caseLoops)
        {
            std::tstring_t sVar1 = xT("bbb");
            std::tstring_t sVar2 = xT("aaa");
            xTEST_GR(sVar1, sVar2);
        }

        xTEST_CASE("xTEST_LESS_EQ_", a_caseLoops)
        {
            std::tstring_t sVar1 = xT("aaa");
            std::tstring_t sVar2 = xT("aaa");
            xTEST_LESS_EQ(sVar1, sVar2);

            std::tstring_t sVar3 = xT("aaa");
            std::tstring_t sVar4 = xT("ggg");
            xTEST_LESS_EQ(sVar3, sVar4);
        }

        xTEST_CASE("xTEST_GR_EQ_", a_caseLoops)
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
//-------------------------------------------------------------------------------------------------
