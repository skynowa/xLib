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
    xTEST_CASE(CxFileTemp::all, cullCaseLoops)
    {
        CxFileTemp ftFileTemp(true);
        CxFile     fJobber;

        ftFileTemp.vCreate(CxPath::sExe(), sTempDirPath() + CxConst::xSLASH + xT("Temp"), &fJobber);
        #if 0
            xTRACEV(xT("\tsTemp: %s"), fJobber.sGetPath().c_str());
        #endif

        m_llRv = fJobber.llSize();
        xTEST_EQ(0LL, m_llRv);

        fJobber.vWriteLine(xT("qwertyuiop"));

        m_bRv = fJobber.bIsEmpty();
        xTEST_EQ(false, m_bRv);

        fJobber.vClear();
        fJobber.vClose();
    }
}
//---------------------------------------------------------------------------
