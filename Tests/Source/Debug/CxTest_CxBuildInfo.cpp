/**
 * \file   CxTest_CxBuildInfo.cpp
 * \brief  test CxBuildInfo
 */


#include <Test/Debug/CxTest_CxBuildInfo.h>


//---------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxBuildInfo::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxBuildInfo::isRelease", a_caseLoops)
    {
        CxBuildInfo info;

        m_bRv = info.isRelease();
        #if defined(NDEBUG)
            xTEST_EQ(true, m_bRv);
        #else
            xTEST_EQ(false, m_bRv);
        #endif

        #if xBUILD_DEBUG
            xTEST_EQ(m_bRv, false);
        #else
            xTEST_EQ(m_bRv, true);
        #endif
    }

    xTEST_CASE("CxBuildInfo::datetime", a_caseLoops)
    {
        CxBuildInfo info;

        m_sRv = info.datetime();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("CxBuildInfo::langStandart", a_caseLoops)
    {
        CxBuildInfo info;

        m_sRv = info.langStandart();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("CxBuildInfo::osEnvironment", a_caseLoops)
    {
        CxBuildInfo info;

        m_sRv = info.osEnvironment();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("CxBuildInfo::os", a_caseLoops)
    {
        CxBuildInfo info;

        m_sRv = info.os();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("CxBuildInfo::arch", a_caseLoops)
    {
        CxBuildInfo info;

        m_sRv = info.arch();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("CxBuildInfo::compiler", a_caseLoops)
    {
        CxBuildInfo info;

        m_sRv = info.compiler();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("CxBuildInfo::isUnicodeEncoding", a_caseLoops)
    {
        CxBuildInfo info;

        m_bRv = info.isUnicodeEncoding();
        #if xUNICODE
            xTEST_EQ(m_bRv, true);
        #else
            xTEST_EQ(m_bRv, false);
        #endif
    }

    xTEST_CASE("CxBuildInfo::stdLibC", a_caseLoops)
    {
        CxBuildInfo info;

        m_sRv = info.stdLibC();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("CxBuildInfo::stdLibCpp", a_caseLoops)
    {
        CxBuildInfo info;

        m_sRv = info.stdLibCpp();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("CxBuildInfo::xlibVersion", a_caseLoops)
    {
        CxBuildInfo info;

        m_sRv = info.xlibVersion();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("CxBuildInfo::binaryType", a_caseLoops)
    {
        CxBuildInfo info;

        m_sRv = info.binaryType();
        xTEST_EQ(m_sRv, std::tstring_t( xT("Executable binary") ));
    }
}
//---------------------------------------------------------------------------
