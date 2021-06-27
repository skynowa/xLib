/**
 * \file   Test_Blowfish.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Blowfish)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Blowfish::unit()
{
    xTEST_CASE("encryptCfb64")
    {
        std::ustring_t plain[] = {
            std::ustring_t(1,  'a'),
            std::ustring_t(2,  'b'),
            std::ustring_t(3,  'c'),
            std::ustring_t(8,  'd'),
            std::ustring_t(11, 'e'),
            std::ustring_t(12, 'f'),
            std::ustring_t(16, 'j'),
            std::ustring_t(17, 'h'),
            std::ustring_t(28, 'i'),
            std::ustring_t(32, 'j'),
            std::ustring_t(51, 'k')
        };

        for (size_t i = 0; i < xARRAY_SIZE(plain); i ++) {
            Blowfish blowfish;

            std::tstring_t key = xT("8888r88888");
            blowfish.setKey(key);

            std::ustring_t encrypted;
            blowfish.encryptCfb64(Blowfish::Mode::Encrypt, plain[i], &encrypted);

            std::ustring_t decrypted;
            blowfish.encryptCfb64(Blowfish::Mode::Decrypt, encrypted, &decrypted);

            xTEST_EQ(plain[i], decrypted);
            xTEST_EQ(Crc32().calc(&(plain[i]).at(0), plain[i].size()),
                Crc32().calc(&decrypted.at(0), decrypted.size()));
        }
    }

    xTEST_CASE("encryptFileCfb64")
    {
        Blowfish blowfish;
        std::tstring_t key           = xT("888888888A");
        std::tstring_t filePlain     = getData().tempDirPath + Const::slash() + xT("Blowfish.txt");
        std::tstring_t fileEncrypted = getData().tempDirPath + Const::slash() + xT("Blowfish_Encrypted.txt");
        std::tstring_t fileDecrypted = getData().tempDirPath + Const::slash() + xT("Blowfish_Decrypted.txt");

        // prepare
        {
            File(filePlain).textWrite(xT("text_text"), FileIO::OpenMode::Write);
        }

        // test
        blowfish.setKey(key);
        blowfish.encryptFileCfb64(Blowfish::Mode::Encrypt, filePlain, fileEncrypted);
        blowfish.encryptFileCfb64(Blowfish::Mode::Decrypt, fileEncrypted, fileDecrypted);

        {
            FileIO fileIn(filePlain);
            fileIn.open(FileIO::OpenMode::BinReadOnly);

            FileIO fileOut(fileDecrypted);
            fileOut.open(FileIO::OpenMode::BinReadOnly);

            xTEST_EQ(fileIn.size(), fileOut.size());
            xTEST_EQ(Crc32().calcFile(filePlain), Crc32().calcFile(fileDecrypted));
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------

