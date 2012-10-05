/**
 * \file   CxTest_CxCrc32.cpp
 * \brief
 */


#include <Test/Crypt/CxTest_CxCrc32.h>

#include <xLib/Common/CxConst.h>


//---------------------------------------------------------------------------
CxTest_CxCrc32::CxTest_CxCrc32() {

}
//---------------------------------------------------------------------------
CxTest_CxCrc32::~CxTest_CxCrc32() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxCrc32::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    /*DEBUG*/

    const std::tstring_t csFilePath = sGetTempDirPath()  + CxConst::xSLASH + xT("Test.txt");;

    //-------------------------------------
    //Prepare
    {
        CxFile flFile;

        flFile.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        flFile.vResize(1337LL);
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
}
//---------------------------------------------------------------------------
