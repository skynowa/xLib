/**
 * \file   Test_BuildInfo.cpp
 * \brief  test BuildInfo
 */


#include <Test/Debug/Test_BuildInfo.h>


//---------------------------------------------------------------------------
/* virtual */
void_t
Test_BuildInfo::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("isRelease", a_caseLoops)
    {
        BuildInfo info;

        m_bRv = info.isRelease();
        #if defined(NDEBUG)
            xTEST_EQ(m_bRv, true);
        #else
            xTEST_EQ(m_bRv, false);
        #endif

        #if xBUILD_DEBUG
            xTEST_EQ(m_bRv, false);
        #else
            xTEST_EQ(m_bRv, true);
        #endif
    }

    xTEST_CASE("datetime", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.datetime();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("langStandart", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.langStandart();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("osEnvironment", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.osEnvironment();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("os", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.os();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("arch", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.arch();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("bitsArch", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.bitsArch();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("compiler", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.compiler();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("isUnicodeEncoding", a_caseLoops)
    {
        BuildInfo info;

        m_bRv = info.isUnicodeEncoding();
        #if xUNICODE
            xTEST_EQ(m_bRv, true);
        #else
            xTEST_EQ(m_bRv, false);
        #endif
    }

    xTEST_CASE("stdLibC", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.stdLibC();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("stdLibCpp", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.stdLibCpp();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("qt", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.qt();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("xlibVersion", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.xlibVersion();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("binaryType", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.binaryType();
        xTEST_EQ(m_sRv, std::tstring_t( xT("Executable binary") ));
    }
}
//---------------------------------------------------------------------------
