/**
 * \file   CxTest_CxFileTemp.cpp
 * \brief  test CxFileTemp
 */


#include <Test/Filesystem/CxTest_CxFileTemp.h>

#include <xLib/Filesystem/CxPath.h>


//---------------------------------------------------------------------------
CxTest_CxFileTemp::CxTest_CxFileTemp() {

}
//---------------------------------------------------------------------------
CxTest_CxFileTemp::~CxTest_CxFileTemp() {

}
//---------------------------------------------------------------------------
/*virtual*/
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

        m_bRes = ftFileTemp.bCreate(CxPath::sGetExe(), sGetWorkDirPath() + CxConst::xSLASH + xT("Temp"), &fJobber);
        #if 0
            xTRACEV(xT("\tsTemp: %s"), fJobber.sGetPath().c_str());
        #endif

        m_llRes = fJobber.llGetSize();
        xTEST_EQ(0LL, m_llRes);

        m_bRes = fJobber.bWriteLine(xT("qwertyuiop"));
        xTEST_EQ(true, m_bRes);

        m_bRes = fJobber.bIsEmpty();
        xTEST_EQ(false, m_bRes);

        m_bRes = fJobber.bClear();
        xTEST_EQ(true, m_bRes);

        m_bRes = fJobber.bClose();
        xTEST_EQ(true, m_bRes);
    }

    return true;
}
//---------------------------------------------------------------------------
