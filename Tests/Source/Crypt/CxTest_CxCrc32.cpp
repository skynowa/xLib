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
    std::ctstring_t filePath = tempDirPath()  + CxConst::slash() + xT("Test.txt");

    // Prepare
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);
        file.resize(1337LL);
    }

    xTEST_CASE("CxCrc32::calcFile calc formatHex", a_caseLoops)
    {
        m_ulRv = CxCrc32::calcFile(filePath);
        xTEST_LESS(0UL, m_ulRv);
        //xTRACE(m_ulRv);

        m_sRv = CxCrc32::formatHex(m_ulRv);
        xTEST_EQ(false, m_sRv.empty());
    }
}
//-------------------------------------------------------------------------------------------------
