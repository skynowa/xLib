/**
 * \file   CxTest_CxFileTemp.cpp
 * \brief  test CxFileTemp
 */


#include <Test/Filesystem/CxTest_CxFileTemp.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxPath.h>


//---------------------------------------------------------------------------
CxTest_CxFileTemp::CxTest_CxFileTemp() {

}
//---------------------------------------------------------------------------
CxTest_CxFileTemp::~CxTest_CxFileTemp() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxFileTemp::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxFileTemp::all", cullCaseLoops)
    {
        CxFileTemp ftFileTemp(true);
        CxFile     fJobber;

        ftFileTemp.create(CxPath::exe(), sTempDirPath() + CxConst::xSLASH + xT("Temp"), &fJobber);
        #if 0
            xTRACEV(xT("\tsTemp: %s"), fJobber.path().c_str());
        #endif

        m_llRv = fJobber.size();
        xTEST_EQ(0LL, m_llRv);

        fJobber.writeLine(xT("qwertyuiop"));

        m_bRv = fJobber.isEmpty();
        xTEST_EQ(false, m_bRv);

        fJobber.clear();
        fJobber.close();
    }
}
//---------------------------------------------------------------------------
