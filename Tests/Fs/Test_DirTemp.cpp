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
		std::tstring_t dirPath = Path::exeDir() + Const::slash() + getData().name;
		cbool_t        isRandomPostfix {true};
		cbool_t        isAutoDelete    {true};

		DirTemp dirTemp(dirPath, isRandomPostfix, isAutoDelete);
		dirTemp.create();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
