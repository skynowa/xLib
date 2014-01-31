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

    }

    xTEST_CASE("CxBuildInfo::langStandart", a_caseLoops)
    {

    }

    xTEST_CASE("CxBuildInfo::os", a_caseLoops)
    {

    }

    xTEST_CASE("CxBuildInfo::arch", a_caseLoops)
    {

    }

    xTEST_CASE("CxBuildInfo::compiler", a_caseLoops)
    {

    }

    xTEST_CASE("CxBuildInfo::isUnicodeEncoding", a_caseLoops)
    {

    }

    xTEST_CASE("CxBuildInfo::stdLibC", a_caseLoops)
    {

    }

    xTEST_CASE("CxBuildInfo::stdLibCpp", a_caseLoops)
    {

    }

    xTEST_CASE("CxBuildInfo::xlibVersion", a_caseLoops)
    {

    }

    xTEST_CASE("CxBuildInfo::binaryType", a_caseLoops)
    {

    }
}
//---------------------------------------------------------------------------
