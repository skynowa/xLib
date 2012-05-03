/**
 * \file   CxTest_CxBlowfish.cpp
 * \brief
 */


#include <Test/Crypt/CxTest_CxBlowfish.h>

#include <xLib/Filesystem/CxFile.h>


//---------------------------------------------------------------------------
CxTest_CxBlowfish::CxTest_CxBlowfish() {

}
//---------------------------------------------------------------------------
CxTest_CxBlowfish::~CxTest_CxBlowfish() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxBlowfish::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //-------------------------------------
    //bEncryptCfb64
    xTEST_CASE(cullCaseLoops)
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

            m_bRes = BF.bSetKey(sKey);
            xTEST_EQ(true, m_bRes);

            m_bRes = BF.bEncryptCfb64(usPlain[i], &sEncrypted, CxBlowfish::cmEncrypt);
            xTEST_EQ(true, m_bRes);

            m_bRes = BF.bEncryptCfb64(sEncrypted, &sDecrypted, CxBlowfish::cmDecrypt);
            xTEST_EQ(true, m_bRes);

            xASSERT(usPlain[i] == sDecrypted);
        }
    }

    //-------------------------------------
    //bEncryptFileCfb64
    xTEST_CASE(cullCaseLoops)
    {
        CxBlowfish BF;
        std::tstring_t sKey           = xT("888888888");
        std::tstring_t sFilePlain     = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.Plain.txt");
        std::tstring_t sFileEncrypted = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.Encrypted.txt");
        std::tstring_t sFileDecrypted = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.FileDecrypted.txt");

        //prepare
        {
            m_bRes = CxFile::bTextWrite(sFilePlain, xT("text_text"));
            xTEST_EQ(true, m_bRes);
        }

        //test
        m_bRes = BF.bSetKey(sKey);
        xTEST_EQ(true, m_bRes);

        m_bRes = BF.bEncryptFileCfb64(sFilePlain, sFileEncrypted, CxBlowfish::cmEncrypt);
        xTEST_EQ(true, m_bRes);

        m_bRes = BF.bEncryptFileCfb64(sFileEncrypted, sFileDecrypted, CxBlowfish::cmDecrypt);
        xTEST_EQ(true, m_bRes);
    }

    return true;
}
//---------------------------------------------------------------------------
