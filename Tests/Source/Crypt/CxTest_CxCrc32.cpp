/**
 * \file   CxTest_CxCrc32.cpp
 * \brief
 */


#include <Test/Crypt/CxTest_CxCrc32.h>

#include <xLib/Common/CxConst.h>


//------------------------------------------------------------------------------
CxTest_CxCrc32::CxTest_CxCrc32() {

}
//------------------------------------------------------------------------------
CxTest_CxCrc32::~CxTest_CxCrc32() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxCrc32::unit(
    culonglong_t &cullCaseLoops
)
{
    std::ctstring_t csFilePath = tempDirPath()  + CxConst::xSLASH + xT("Test.txt");;

    //-------------------------------------
    // Prepare
    {
        CxFile flFile;

        flFile.create(csFilePath, CxFile::omCreateReadWrite, true);
        flFile.resize(1337LL);
    }

    xTEST_CASE("CxCrc32::calc", cullCaseLoops)
    {

    }

    xTEST_CASE("CxCrc32::calcFile formatHex", cullCaseLoops)
    {
        m_ulRv = CxCrc32::calcFile(csFilePath);
        xTEST_LESS(0UL, m_ulRv);
        //xTRACE(m_ulRv);

        m_sRv = CxCrc32::formatHex(m_ulRv);
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxCrc32::calcFast", cullCaseLoops)
    {

    }

    xTEST_CASE("CxCrc32::calcFileFast formatHex", cullCaseLoops)
    {
        m_ulRv = CxCrc32::calcFileFast(csFilePath);
        xTEST_LESS(0UL, m_ulRv);
        //xTRACE(m_ulRv);

        m_sRv = CxCrc32::formatHex(m_ulRv);
        xTEST_EQ(false, m_sRv.empty());
    }
}
//------------------------------------------------------------------------------
