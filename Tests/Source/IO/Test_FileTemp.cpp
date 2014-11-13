/**
 * \file   Test_FileTemp.cpp
 * \brief  test FileTemp
 */


#include <Test/IO/Test_FileTemp.h>

#include <xLib/Core/Const.h>
#include <xLib/IO/File.h>
#include <xLib/IO/Path.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_FileTemp::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("FileTemp::all", a_caseLoops)
    {
        FileTemp fileTemp(true);
        File     fileJobber;

        fileTemp.create(Path::exe(), tempDirPath() + Const::slash() + xT("Temp"), &fileJobber);
        xTEST_EQ(fileJobber.isEmpty(), true);

        fileJobber.writeLine(xT("qwertyuiop"));
        xTEST_EQ(fileJobber.isEmpty(), false);

        fileJobber.clear();
        fileJobber.close();
    }
}
//-------------------------------------------------------------------------------------------------
