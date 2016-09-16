/**
 * \file   Test_FileTemp.cpp
 * \brief  test FileTemp
 */


#include "Test_FileTemp.h"
#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xlib;

xTEST_CLASS(Test_FileTemp)
xTEST_UNIT(Test_FileTemp)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_FileTemp::unit()
{
    xTEST_CASE("all")
    {
        FileTemp fileTemp(true);
        File     fileJobber;

        fileTemp.create(Path::exe(), data.tempDirPath + Const::slash() + xT("Temp"), &fileJobber);
        xTEST_EQ(fileJobber.isEmpty(), true);

        fileJobber.writeLine(xT("qwertyuiop"));
        xTEST_EQ(fileJobber.isEmpty(), false);

        fileJobber.clear();
        fileJobber.close();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
