/**
 * \file   Test_PathDll.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_PathDll)
xTEST_UNIT(Test_PathDll)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_PathDll::unit()
{
    xTEST_CASE("ctor")
    {
        m_sRv = PathDll().str();
    #if (cmOPTION_PROJECT_LIB_SHARE || cmOPTION_PROJECT_LIB_MODULE)
        xTEST(FileInfo(m_sRv).isExists());
    #else
        xTEST_NA(m_sRv);
    #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
