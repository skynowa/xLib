/**
 * \file   Test_Path.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_PathExe)
xTEST_UNIT(Test_PathExe)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_PathExe::unit()
{
    xTEST_CASE("ctor")
    {
        m_sRv = PathExe().str();
        xTEST(FileInfo(m_sRv).isExists());
    }

    xTEST_CASE("dir")
    {
        m_sRv = PathExe().dir();
        xTEST(Dir(m_sRv).isExists());
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
