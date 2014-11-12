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
    #if 1
        Trace() << xT("\tsTemp: ") << fileJobber.path();
    #endif

        m_llRv = fileJobber.size();
        xTEST_EQ(m_llRv, 0LL);

        fileJobber.writeLine(xT("qwertyuiop"));

        m_bRv = fileJobber.isEmpty();
        xTEST_EQ(m_bRv, false);

        fileJobber.clear();
        fileJobber.close();
    }
}
//-------------------------------------------------------------------------------------------------
