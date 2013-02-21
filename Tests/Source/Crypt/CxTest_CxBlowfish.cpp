/**
 * \file   CxTest_CxBlowfish.cpp
 * \brief
 */


#include <Test/Crypt/CxTest_CxBlowfish.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Filesystem/CxFile.h>


//------------------------------------------------------------------------------
CxTest_CxBlowfish::CxTest_CxBlowfish() {

}
//------------------------------------------------------------------------------
CxTest_CxBlowfish::~CxTest_CxBlowfish() {

}
//------------------------------------------------------------------------------
/* virtual */
void
CxTest_CxBlowfish::unit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxBlowfish::encryptCfb64", cullCaseLoops)
    {
        const std::ustring_t usPlain[] = {
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

        for (size_t i = 0; i < xARRAY_SIZE(usPlain); i ++) {
            CxBlowfish BF;
            std::tstring_t sKey       = xT("888888888");
            std::ustring_t sEncrypted;
            std::ustring_t sDecrypted;

            BF.setKey(sKey);
            BF.encryptCfb64(usPlain[i], &sEncrypted, CxBlowfish::cmEncrypt);
            BF.encryptCfb64(sEncrypted, &sDecrypted, CxBlowfish::cmDecrypt);

            xTEST_EQ(true, usPlain[i] == sDecrypted);
        }
    }

    xTEST_CASE("CxBlowfish::encryptFileCfb64", cullCaseLoops)
    {
        CxBlowfish BF;
        std::tstring_t sKey           = xT("888888888");
        std::tstring_t sFilePlain     = tempDirPath() + CxConst::xSLASH + xT("Test.Plain.txt");
        std::tstring_t sFileEncrypted = tempDirPath() + CxConst::xSLASH + xT("Test.Encrypted.txt");
        std::tstring_t sFileDecrypted = tempDirPath() + CxConst::xSLASH + xT("Test.FileDecrypted.txt");

        //prepare
        {
            CxFile::textWrite(sFilePlain, xT("text_text"));
        }

        //test
        BF.setKey(sKey);
        BF.encryptFileCfb64(sFilePlain, sFileEncrypted, CxBlowfish::cmEncrypt);
        BF.encryptFileCfb64(sFileEncrypted, sFileDecrypted, CxBlowfish::cmDecrypt);
    }
}
//------------------------------------------------------------------------------
