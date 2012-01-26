/**
 * \file   CxTest_CxCrc32.cpp
 * \brief
 */


#include <Test/Crypt/CxTest_CxCrc32.h>


//---------------------------------------------------------------------------
CxTest_CxCrc32::CxTest_CxCrc32() {

}
//---------------------------------------------------------------------------
CxTest_CxCrc32::~CxTest_CxCrc32() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxCrc32::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    /*DEBUG*/

    const std::tstring_t csFilePath = sGetWorkDirPath()  + CxConst::xSLASH + xT("Test.txt");;

    //-------------------------------------
    //Prepare
    {
        CxFile flFile;

        m_bRes = flFile.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = flFile.bResize(1337);
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //ulCalc
    xTEST_CASE(cullCaseLoops)
    {

    }

    //-------------------------------------
    //ulCalcFile, sFormatHex
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRes = CxCrc32::ulCalcFile(csFilePath);
        xTEST_LESS(0UL, m_ulRes);
        //xTRACE(m_ulRes);

        m_sRes = CxCrc32::sFormatHex(m_ulRes);
        xTEST_EQ(false, m_sRes.empty());
    }

    //-------------------------------------
    //ulCalcFast
    xTEST_CASE(cullCaseLoops)
    {

    }

    //------------------------------------
    //ulCalcFileFast, sFormatHex
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRes = CxCrc32::ulCalcFileFast(csFilePath);
        xTEST_LESS(0UL, m_ulRes);
        //xTRACE(m_ulRes);

        m_sRes = CxCrc32::sFormatHex(m_ulRes);
        xTEST_EQ(false, m_sRes.empty());
    }

    return true;
}
//---------------------------------------------------------------------------
