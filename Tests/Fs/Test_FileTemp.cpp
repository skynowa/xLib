/**
 * \file   Test_FileTemp.cpp
 * \brief  test FileTemp
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_FileTemp)
xTEST_UNIT(Test_FileTemp)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_FileTemp::unit()
{
    xTEST_CASE("all")
    {
        FileIO fileJobber;

        FileTemp fileTemp(true);
        fileTemp.create(Path::exe(), getData().tempDirPath, &fileJobber);
        xTEST(FileInfo(fileJobber).isEmpty());

        fileJobber.writeLine(xT("qwertyuiop"));
        fileJobber.flush();
        xTEST(!FileInfo(fileJobber).isEmpty());

        fileJobber.clear();
        fileJobber.close();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
