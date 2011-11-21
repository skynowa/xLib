/**
 * \file   CxTest_CxBlowfish.cpp
 * \brief
 */


#include <Test/Crypt/CxTest_CxBlowfish.h>


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
    const ULONGLONG cullBlockLoops
)
{
    //-------------------------------------
    //bEncryptCfb64
    xTEST_CASE(cullBlockLoops)
    {
        const std::ustring usPlain[] = {
            std::ustring(1,  'a'),
            std::ustring(2,  'b'),
            std::ustring(3,  'c'),
            std::ustring(8,  'd'),
            std::ustring(11, 'e'),
            std::ustring(12, 'f'),
            std::ustring(16, 'j'),
            std::ustring(17, 'h'),
            std::ustring(28, 'i'),
            std::ustring(32, 'j'),
            std::ustring(51, 'k')
        };

        for (size_t i = 0; i < xARRAY_SIZE(usPlain); i ++) {
            CxBlowfish BF;
            std::tstring sKey       = xT("888888888");
            std::ustring sEncrypted;
            std::ustring sDecrypted;

            m_bRes = BF.bSetKey(sKey);
            xTEST_DIFF(false, m_bRes);

            m_bRes = BF.bEncryptCfb64(usPlain[i], &sEncrypted, CxBlowfish::cmEncrypt);
            xTEST_DIFF(false, m_bRes);

            m_bRes = BF.bEncryptCfb64(sEncrypted, &sDecrypted, CxBlowfish::cmDecrypt);
            xTEST_DIFF(false, m_bRes);

            xASSERT(usPlain[i] == sDecrypted);
        }
    }

    //-------------------------------------
    //bEncryptFileCfb64
    xTEST_CASE(cullBlockLoops)
    {
        CxBlowfish BF;
        std::tstring sKey           = xT("888888888");
        std::tstring sFilePlain     = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.Plain.txt");
        std::tstring sFileEncrypted = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.Encrypted.txt");
        std::tstring sFileDecrypted = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.FileDecrypted.txt");

        //prepare
        {
            m_bRes = CxFile::bTextWrite(sFilePlain, xT("text_text"));
            xTEST_DIFF(false, m_bRes);
        }

        //test
        m_bRes = BF.bSetKey(sKey);
        xTEST_DIFF(false, m_bRes);

        m_bRes = BF.bEncryptFileCfb64(sFilePlain, sFileEncrypted, CxBlowfish::cmEncrypt);
        xTEST_DIFF(false, m_bRes);

        m_bRes = BF.bEncryptFileCfb64(sFileEncrypted, sFileDecrypted, CxBlowfish::cmDecrypt);
        xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bEncryptFileCfb64 (with stamp)
    xTEST_CASE(cullBlockLoops)
    {
        CxBlowfish BF;

        CxBlowfish::ECryptMode cmRes = CxBlowfish::cmUnknown;
        std::tstring sKey           = xT("888888888");
        std::tstring sStamp         = xT("stamp");
        std::ustring usStamp        = xS2US(sStamp);
        std::tstring sFilePlain     = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.Plain.txt");
        std::tstring sFileEncrypted = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.Encrypted.txt");
        std::tstring sFileDecrypted = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.FileDecrypted.txt");

        m_bRes = BF.bSetKey(sKey);
        xTEST_DIFF(false, m_bRes);

        cmRes = BF.cmGetFileCryptStatus(sFilePlain, usStamp);
        xTEST_EQ(CxBlowfish::cmDecrypt, cmRes);

    #if xTODO
        m_bRes = BF.bEncryptFileCfb64(sFilePlain,     sFileEncrypted, usStamp);
        xTEST_DIFF(false, m_bRes);

        m_bRes = BF.bEncryptFileCfb64(sFileEncrypted, sFileDecrypted, usStamp);
        xTEST_DIFF(false, m_bRes);
    #endif
    }


    return true;
}
//---------------------------------------------------------------------------
