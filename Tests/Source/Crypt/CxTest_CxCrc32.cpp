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
/* virtual */
bool
CxTest_CxCrc32::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    /*DEBUG*/

    const std::tstring_t csFilePath = sGetTempDirPath()  + CxConst::xSLASH + xT("Test.txt");;

    //-------------------------------------
    //Prepare
    {
        CxFile flFile;

        m_bRv = flFile.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = flFile.bResize(1337LL);
        xTEST_EQ(true, m_bRv);
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
        m_ulRv = CxCrc32::ulCalcFile(csFilePath);
        xTEST_LESS(0UL, m_ulRv);
        //xTRACE(m_ulRv);

        m_sRv = CxCrc32::sFormatHex(m_ulRv);
        xTEST_EQ(false, m_sRv.empty());
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
        m_ulRv = CxCrc32::ulCalcFileFast(csFilePath);
        xTEST_LESS(0UL, m_ulRv);
        //xTRACE(m_ulRv);

        m_sRv = CxCrc32::sFormatHex(m_ulRv);
        xTEST_EQ(false, m_sRv.empty());
    }

    return true;
}
//---------------------------------------------------------------------------
