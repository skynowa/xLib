/**
 * \file   Test_Limits.cpp
 * \brief  test Limits
 */


#include <Test/Core/Test_Limits.h>

#include <xLib/IO/Path.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Limits)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Limits::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("xHOST_NAME_MAX_", a_caseLoops)
    {
        m_iRv = xHOST_NAME_MAX;
        xTEST_GR(m_iRv, 0);
    }

    xTEST_CASE("xUSER_NAME_MAX", a_caseLoops)
    {
        m_iRv = xUSER_NAME_MAX;
        xTEST_GR(m_iRv, 0);
    }

    xTEST_CASE("xPATH_MAX_", a_caseLoops)
    {
        m_stRv = xPATH_MAX;
        xTEST_GR(m_stRv, size_t(0));
    }

    xTEST_CASE("xNAME_MAX_", a_caseLoops)
    {
        m_stRv = xNAME_MAX;
        xTEST_GR(m_stRv, size_t(0));
    }

    xTEST_CASE("xLINE_MAX_", a_caseLoops)
    {
        m_stRv = xLINE_MAX;
        xTEST_GR(m_stRv, size_t(0));
    }

    xTEST_CASE("xENV_MAX_", a_caseLoops)
    {
        m_stRv = xENV_MAX;
        xTEST_GR(m_stRv, size_t(0));
    }

    xTEST_CASE("xFRAMES_MAX_", a_caseLoops)
    {
        m_ulRv = xSTACK_TRACE_FRAMES_MAX;
        xTEST_GR(m_ulRv, 0UL);
    }

    xTEST_CASE("xPAGE_SIZE_", a_caseLoops)
    {
        #if xENV_UNIX
            m_stRv = xPAGE_SIZE;
            xTEST_GR(m_stRv, size_t(0));
        #endif
    }

    xTEST_CASE("xTIMEOUT_INFINITE_", a_caseLoops)
    {
        m_ullRv = xTIMEOUT_INFINITE;
    }
}
//-------------------------------------------------------------------------------------------------
