/**
 * \file   Test_Blowfish.cpp
 * \brief
 */


#include <Test/Crypt/Test_Blowfish.h>

#include <xLib/Core/Const.h>
#include <xLib/Crypt/Crc32.h>
#include <xLib/IO/File.h>


#if xHAVE_OPENSSL_CRYPTO

//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Blowfish::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("encryptCfb64", a_caseLoops)
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
            std::ustring_t encrypted;
            std::ustring_t decrypted;

            blowfish.setKey(key);
            blowfish.encryptCfb64(plain[i], &encrypted, Blowfish::cmEncrypt);
            blowfish.encryptCfb64(encrypted, &decrypted, Blowfish::cmDecrypt);

            xTEST_EQ(plain[i], decrypted);
            xTEST_EQ(Crc32().calc(&(plain[i]).at(0), plain[i].size()),
                Crc32().calc(&decrypted.at(0), decrypted.size()));
        }
    }

    xTEST_CASE("encryptFileCfb64", a_caseLoops)
    {
        Blowfish blowfish;
        std::tstring_t key           = xT("888888888A");
        std::tstring_t filePlain     = tempDirPath() + Const::slash() + xT("Blowfish.txt");
        std::tstring_t fileEncrypted = tempDirPath() + Const::slash() + xT("Blowfish_Encrypted.txt");
        std::tstring_t fileDecrypted = tempDirPath() + Const::slash() + xT("Blowfish_Decrypted.txt");

        // prepare
        {
            File::textWrite(filePlain, xT("text_text"), File::omWrite);
        }

        // test
        blowfish.setKey(key);
        blowfish.encryptFileCfb64(filePlain, fileEncrypted, Blowfish::cmEncrypt);
        blowfish.encryptFileCfb64(fileEncrypted, fileDecrypted, Blowfish::cmDecrypt);

        {
            File fileIn;
            fileIn.create(filePlain, File::omBinRead);

            File fileOut;
            fileOut.create(fileDecrypted, File::omBinRead);

            xTEST_EQ(fileIn.size(), fileOut.size());
            xTEST_EQ(Crc32().calcFile(filePlain), Crc32().calcFile(fileDecrypted));
        }
    }
}
//-------------------------------------------------------------------------------------------------

#endif // xHAVE_OPENSSL_CRYPTO
