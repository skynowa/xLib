/**
 * \file   Test_Crc32.cpp
 * \brief
 */


#include <Test/Crypt/Test_Crc32.h>

#include <xLib/Core/Const.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Crc32)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Crc32::unit()
{
    std::ctstring_t filePath = tempDirPath()  + Const::slash() + xT("Crc32.txt");

    // Prepare
    {
        File file;

        file.create(filePath, File::omCreateReadWrite);
        file.resize(1337LL);
    }

    xTEST_CASE("calcFile, calc, formatHex")
    {
        Crc32 crc32;

        m_ulRv = crc32.calcFile(filePath);
        xTEST_EQ(432847819UL, m_ulRv);

        m_sRv = crc32.formatHex();
        xTEST_EQ(m_sRv, std::tstring_t(xT("19CCBBCB")));
    }
}
//-------------------------------------------------------------------------------------------------
