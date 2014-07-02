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
        FileTemp ftFileTemp(true);
        File     fJobber;

        ftFileTemp.create(Path::exe(), tempDirPath() + Const::slash() + xT("Temp"), &fJobber);
        #if 0
            xTRACEV(xT("\tsTemp: %s"), fJobber.path().c_str());
        #endif

        m_llRv = fJobber.size();
        xTEST_EQ(0LL, m_llRv);

        fJobber.writeLine(xT("qwertyuiop"));

        m_bRv = fJobber.isEmpty();
        xTEST_EQ(m_bRv, false);

        fJobber.clear();
        fJobber.close();
    }
}
//-------------------------------------------------------------------------------------------------
