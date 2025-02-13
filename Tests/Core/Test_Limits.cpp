/**
 * \file   Test_Limits.cpp
 * \brief  test Limits
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Limits)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Limits::unit()
{
    xTEST_CASE("xHOST_NAME_MAX_")
    {
        m_iRv = xHOST_NAME_MAX;
        xTEST_GR(m_iRv, 0);
    }

    xTEST_CASE("xUSER_NAME_MAX")
    {
        m_iRv = xUSER_NAME_MAX;
        xTEST_GR(m_iRv, 0);
    }

    xTEST_CASE("xLINE_MAX_")
    {
        m_stRv = xLINE_MAX;
        xTEST_GR(m_stRv, size_t(0));
    }

    xTEST_CASE("xPAGE_SIZE_")
    {
        #if xENV_UNIX
            m_stRv = xPAGE_SIZE;
            xTEST_GR(m_stRv, size_t(0));
        #endif
    }

    xTEST_CASE("xTIMEOUT_INFINITE_")
    {
        m_ullRv = xTIMEOUT_INFINITE;
    }

    xTEST_CASE("xCUSTOM_SEMAPHORE_VALUE_MAX_WIN")
    {
        m_ullRv = xCUSTOM_SEMAPHORE_VALUE_MAX_WIN;
    }

    xTEST_CASE("xCUSTOM_SYSCONF_SC_GETPW_R_SIZE_MAX_UNIX")
    {
        m_ullRv = xCUSTOM_SYSCONF_SC_GETPW_R_SIZE_MAX_UNIX;
    }

    xTEST_CASE("xTHREAD_NAME_LENGTH_MAX")
    {
        m_ullRv = xTHREAD_NAME_LENGTH_MAX;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
