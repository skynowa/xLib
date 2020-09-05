/**
 * \file  Test_DirTemp.cpp
 * \brief test DirTemp
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_DirTemp)
xTEST_UNIT(Test_DirTemp)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_DirTemp::unit()
{
    xTEST_CASE("DirTemp")
    {
		cbool_t isAutoDelete {false};
		DirTemp dirTemp( Path::exeDir() + Const::slash() + getData().name, isAutoDelete);
		dirTemp.create();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
