/**
 * \file   CxTest_CxFileTemp.cpp
 * \brief  test CxFileTemp
 */


#include <Test/Filesystem/CxTest_CxFileTemp.h>


//---------------------------------------------------------------------------
CxTest_CxFileTemp::CxTest_CxFileTemp() {

}
//---------------------------------------------------------------------------
CxTest_CxFileTemp::~CxTest_CxFileTemp() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxFileTemp::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //-------------------------------------
    //sTempCreate, bTempClose
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFileTemp ftFileTemp(TRUE);
        CxFile     fJobber;

        m_bRes = ftFileTemp.bCreate(CxPath::sGetExe(), sGetWorkDirPath() + CxConst::xSLASH + xT("Temp"), &fJobber);
        #if 0
            xTRACEV(xT("\tsTemp: %s"), fJobber.sGetPath().c_str());
        #endif

        m_liRes = fJobber.liGetSize();
        xTEST_EQ(0L, m_liRes);

        m_bRes = fJobber.bWriteLine(xT("qwertyuiop"));
        xTEST_EQ(TRUE, m_bRes);

        m_bRes = fJobber.bIsEmpty();
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = fJobber.bClear();
        xTEST_EQ(TRUE, m_bRes);

        m_bRes = fJobber.bClose();
        xTEST_EQ(TRUE, m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
