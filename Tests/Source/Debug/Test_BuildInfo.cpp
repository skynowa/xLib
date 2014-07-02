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
    xTEST_CASE("BuildInfo::isRelease", a_caseLoops)
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

    xTEST_CASE("BuildInfo::datetime", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.datetime();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("BuildInfo::langStandart", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.langStandart();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("BuildInfo::osEnvironment", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.osEnvironment();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("BuildInfo::os", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.os();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("BuildInfo::arch", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.arch();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("BuildInfo::bitsArch", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.bitsArch();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("BuildInfo::compiler", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.compiler();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("BuildInfo::isUnicodeEncoding", a_caseLoops)
    {
        BuildInfo info;

        m_bRv = info.isUnicodeEncoding();
        #if xUNICODE
            xTEST_EQ(m_bRv, true);
        #else
            xTEST_EQ(m_bRv, false);
        #endif
    }

    xTEST_CASE("BuildInfo::stdLibC", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.stdLibC();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("BuildInfo::stdLibCpp", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.stdLibCpp();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("BuildInfo::xlibVersion", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.xlibVersion();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("BuildInfo::binaryType", a_caseLoops)
    {
        BuildInfo info;

        m_sRv = info.binaryType();
        xTEST_EQ(m_sRv, std::tstring_t( xT("Executable binary") ));
    }
}
//---------------------------------------------------------------------------
