/**
 * \file   CxTest_CxCrc32.cpp
 * \brief
 */


#include <Test/Crypt/CxTest_CxCrc32.h>

#include <xLib/Core/CxConst.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxCrc32::unit(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t csFilePath = tempDirPath()  + CxConst::slash() + xT("Test.txt");;

    //-------------------------------------
    // Prepare
    {
        CxFile flFile;

        flFile.create(csFilePath, CxFile::omCreateReadWrite, true);
        flFile.resize(1337LL);
    }

    xTEST_CASE("CxCrc32::calc", a_caseLoops)
    {

    }

    xTEST_CASE("CxCrc32::calcFile formatHex", a_caseLoops)
    {
        m_ulRv = CxCrc32::calcFile(csFilePath);
        xTEST_LESS(0UL, m_ulRv);
        //xTRACE(m_ulRv);

        m_sRv = CxCrc32::formatHex(m_ulRv);
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxCrc32::calcFast", a_caseLoops)
    {

    }

    xTEST_CASE("CxCrc32::calcFileFast formatHex", a_caseLoops)
    {
        m_ulRv = CxCrc32::calcFileFast(csFilePath);
        xTEST_LESS(0UL, m_ulRv);
        //xTRACE(m_ulRv);

        m_sRv = CxCrc32::formatHex(m_ulRv);
        xTEST_EQ(false, m_sRv.empty());
    }
}
//------------------------------------------------------------------------------
