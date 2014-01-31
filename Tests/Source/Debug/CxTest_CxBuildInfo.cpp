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
    xTEST_CASE("CxBuildInfo::isDebugBuild", a_caseLoops)
    {
        CxBuildInfo info;

        m_bRv = info.isDebugBuild();
        #if defined(NDEBUG)
            xTEST_EQ(false, m_bRv);
        #else
            xTEST_EQ(true, m_bRv);
        #endif

        #if xBUILD_DEBUG
            xTEST_EQ(m_bRv, true);
        #else
            xTEST_EQ(m_bRv, false);
        #endif
    }
}
//---------------------------------------------------------------------------
