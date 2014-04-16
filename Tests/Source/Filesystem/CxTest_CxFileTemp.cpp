/**
 * \file   CxTest_CxFileTemp.cpp
 * \brief  test CxFileTemp
 */


#include <Test/Filesystem/CxTest_CxFileTemp.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxPath.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxFileTemp::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxFileTemp::all", a_caseLoops)
    {
        CxFileTemp ftFileTemp(true);
        CxFile     fJobber;

        ftFileTemp.create(CxPath::exe(), tempDirPath() + CxConst::slash() + xT("Temp"), &fJobber);
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
