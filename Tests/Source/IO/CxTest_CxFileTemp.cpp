/**
 * \file   CxTest_CxFileTemp.cpp
 * \brief  test CxFileTemp
 */


#include <Test/IO/CxTest_CxFileTemp.h>

#include <xLib/Core/CxConst.h>
#include <xLib/IO/CxFile.h>
#include <xLib/IO/CxPath.h>


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
