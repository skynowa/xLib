/**
 * \file   CxTest_CxCrc32.cpp
 * \brief
 */


#include <Test/Crypt/CxTest_CxCrc32.h>

#include <xLib/Core/CxConst.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxCrc32::unit(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t filePath = tempDirPath()  + CxConst::slash() + xT("CxCrc32.txt");

    // Prepare
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);
        file.resize(1337LL);
    }

    xTEST_CASE("CxCrc32::calcFile calc formatHex", a_caseLoops)
    {
        CxCrc32 crc32;

        m_ulRv = crc32.calcFile(filePath);
        xTEST_EQ(432847819UL, m_ulRv);

        m_sRv = crc32.formatHex();
        xTEST_EQ(m_sRv, std::tstring_t(xT("19CCBBCB")));
    }
}
//-------------------------------------------------------------------------------------------------
