/**
 * \file   CxTest_CxFileTemp.cpp
 * \brief  test CxFileTemp
 */


#include <Test/Filesystem/CxTest_CxFileTemp.h>

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
bool
CxTest_CxFileTemp::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //-------------------------------------
    //sTempCreate, bTempClose
    xTEST_CASE(cullCaseLoops)
    {
        CxFileTemp ftFileTemp(true);
        CxFile     fJobber;

        m_bRv = ftFileTemp.bCreate(CxPath::sGetExe(), sGetTempDirPath() + CxConst::xSLASH + xT("Temp"), &fJobber);
        #if 0
            xTRACEV(xT("\tsTemp: %s"), fJobber.sGetPath().c_str());
        #endif

        m_llRv = fJobber.llGetSize();
        xTEST_EQ(0LL, m_llRv);

        m_bRv = fJobber.bWriteLine(xT("qwertyuiop"));
        xTEST_EQ(true, m_bRv);

        m_bRv = fJobber.bIsEmpty();
        xTEST_EQ(false, m_bRv);

        m_bRv = fJobber.bClear();
        xTEST_EQ(true, m_bRv);

        m_bRv = fJobber.bClose();
        xTEST_EQ(true, m_bRv);
    }

    return true;
}
//---------------------------------------------------------------------------
