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
    // Prepare
    {
        CxFile flFile;

        flFile.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        flFile.vResize(1337LL);
    }

    xTEST_CASE(CxCrc32::ulCalc, cullCaseLoops)
    {

    }

    xTEST_CASE(CxCrc32::ulCalcFile sFormatHex, cullCaseLoops)
    {
        m_ulRv = CxCrc32::ulCalcFile(csFilePath);
        xTEST_LESS(0UL, m_ulRv);
        //xTRACE(m_ulRv);

        m_sRv = CxCrc32::sFormatHex(m_ulRv);
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE(CxCrc32::ulCalcFast, cullCaseLoops)
    {

    }

    xTEST_CASE(CxCrc32::ulCalcFileFast sFormatHex, cullCaseLoops)
    {
        m_ulRv = CxCrc32::ulCalcFileFast(csFilePath);
        xTEST_LESS(0UL, m_ulRv);
        //xTRACE(m_ulRv);

        m_sRv = CxCrc32::sFormatHex(m_ulRv);
        xTEST_EQ(false, m_sRv.empty());
    }
}
//---------------------------------------------------------------------------
