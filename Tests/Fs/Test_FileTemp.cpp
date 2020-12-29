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
        std::ctstring_t filePath = Path::exe().str();

    	FileIO fileWorker(filePath);

        FileTemp fileTemp(filePath, getData().tempDirPath, true);
        fileTemp.create(&fileWorker);
        xTEST(FileInfo(fileWorker).isEmpty());

        fileWorker.writeLine(xT("qwertyuiop"));
        fileWorker.flush();
        xTEST(!FileInfo(fileWorker).isEmpty());

        fileWorker.clear();
        fileWorker.close();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
