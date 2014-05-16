/**
 * \file   CxTest_xLimits.cpp
 * \brief  test xLimits
 */


#include <Test/Core/CxTest_xLimits.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_xLimits::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("xDefines::xHOST_NAME_MAX_", a_caseLoops)
    {
        m_iRv = xHOST_NAME_MAX;
        xTEST_GR(m_iRv, 0);
    }

    xTEST_CASE("xDefines::xUSER_NAME_MAX", a_caseLoops)
    {
        m_iRv = xUSER_NAME_MAX;
        xTEST_GR(m_iRv, 0);
    }

    xTEST_CASE("xDefines::xPATH_MAX_", a_caseLoops)
    {
        m_stRv = xPATH_MAX;
        xTEST_GR(m_stRv, size_t(0));
    }

    xTEST_CASE("xDefines::xNAME_MAX_", a_caseLoops)
    {
        m_stRv = xNAME_MAX;
        xTEST_GR(m_stRv, size_t(0));
    }

    xTEST_CASE("xDefines::xLINE_MAX_", a_caseLoops)
    {
        m_stRv = xLINE_MAX;
        xTEST_GR(m_stRv, size_t(0));
    }

    xTEST_CASE("xDefines::xENV_MAX_", a_caseLoops)
    {
        m_stRv = xENV_MAX;
        xTEST_GR(m_stRv, size_t(0));
    }

    xTEST_CASE("xDefines::xFRAMES_MAX_", a_caseLoops)
    {
        m_ulRv = xSTACK_TRACE_FRAMES_MAX;
        xTEST_GR(m_ulRv, 0UL);
    }

    xTEST_CASE("xDefines::xSEMAPHORE_VALUE_MAX_", a_caseLoops)
    {
        m_liRv = xSEMAPHORE_VALUE_MAX;
        xTEST_GR(m_liRv, 0L);
    }

    xTEST_CASE("xDefines::xPAGE_SIZE_", a_caseLoops)
    {
        #if xENV_UNIX
            m_stRv = xPAGE_SIZE;
            xTEST_GR(m_stRv, size_t(0));
        #endif
    }

    xTEST_CASE("xDefines::xTIMEOUT_INFINITE_", a_caseLoops)
    {
        m_ullRv = xTIMEOUT_INFINITE;
    }
}
//-------------------------------------------------------------------------------------------------
