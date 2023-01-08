/**
 * \file   Test_Libs.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Libs)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Libs::unit()
{
	info::Libs sysInfo;

#if xENV_UNIX
    xTEST_CASE("glibcVersion")
    {
        m_sRv = sysInfo.glibcVersion();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("pthreadVersion")
    {
        m_sRv = sysInfo.pthreadVersion();
        xTEST(!m_sRv.empty());
    }
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
