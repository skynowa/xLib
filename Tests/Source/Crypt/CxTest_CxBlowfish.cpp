/**
 * \file   CxTest_CxBlowfish.cpp
 * \brief
 */


#include <Test/Crypt/CxTest_CxBlowfish.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Filesystem/CxFile.h>


#if xHAVE_OPENSSL_CRYPTO

//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxBlowfish::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxBlowfish::encryptCfb64", a_caseLoops)
    {
        std::custring_t plain[] = {
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
            CxBlowfish blowfish;
            std::tstring_t key = xT("8888r88888");
            std::ustring_t encrypted;
            std::ustring_t decrypted;

            blowfish.setKey(key);
            blowfish.encryptCfb64(plain[i], &encrypted, CxBlowfish::cmEncrypt);
            blowfish.encryptCfb64(encrypted, &decrypted, CxBlowfish::cmDecrypt);

            xTEST_EQ(true, plain[i] == decrypted);
        }
    }

    xTEST_CASE("CxBlowfish::encryptFileCfb64", a_caseLoops)
    {
        CxBlowfish blowfish;
        std::tstring_t key           = xT("888888888A");
        std::tstring_t filePlain     = tempDirPath() + CxConst::slash() + xT("CxBlowfish.txt");
        std::tstring_t fileEncrypted = tempDirPath() + CxConst::slash() + xT("CxBlowfish_Encrypted.txt");
        std::tstring_t fileDecrypted = tempDirPath() + CxConst::slash() + xT("CxBlowfish_Decrypted.txt");

        // prepare
        {
            CxFile::textWrite(filePlain, xT("text_text"), CxFile::omWrite);
        }

        // test
        blowfish.setKey(key);
        blowfish.encryptFileCfb64(filePlain, fileEncrypted, CxBlowfish::cmEncrypt);
        blowfish.encryptFileCfb64(fileEncrypted, fileDecrypted, CxBlowfish::cmDecrypt);
    }
}
//-------------------------------------------------------------------------------------------------

#endif // xHAVE_OPENSSL_CRYPTO
