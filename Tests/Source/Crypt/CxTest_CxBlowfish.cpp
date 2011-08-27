/****************************************************************************
* Class name:  CxTest_CxBlowfish
* Description: test CxBlowfish
* File name:   CxTest_CxBlowfish.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Crypt/CxTest_CxBlowfish.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxBlowfish
CxTest_CxBlowfish::CxTest_CxBlowfish() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxBlowfish
CxTest_CxBlowfish::~CxTest_CxBlowfish() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxBlowfish::bUnit(
    const ULONGLONG cullBlockLoops
)
{
	//-------------------------------------
	//bEncryptCfb64
    xTEST_BLOCK(cullBlockLoops)
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
			xASSERT_NOT_EQ(FALSE, m_bRes);

			m_bRes = BF.bEncryptCfb64(usPlain[i], &sEncrypted, CxBlowfish::cmEncrypt);
			xASSERT_NOT_EQ(FALSE, m_bRes);

			m_bRes = BF.bEncryptCfb64(sEncrypted, &sDecrypted, CxBlowfish::cmDecrypt);
			xASSERT_NOT_EQ(FALSE, m_bRes);

			xASSERT(usPlain[i] == sDecrypted);
		}
	}

	//-------------------------------------
	//bEncryptFileCfb64
    xTEST_BLOCK(cullBlockLoops)
	{
		CxBlowfish BF;
		std::tstring sKey           = xT("888888888");
		std::tstring sFilePlain     = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.Plain.txt");
		std::tstring sFileEncrypted = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.Encrypted.txt");
		std::tstring sFileDecrypted = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.FileDecrypted.txt");

		//prepare
        {
            m_bRes = CxFile::bTextWrite(sFilePlain, xT("text_text"));
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

		//test
		m_bRes = BF.bSetKey(sKey);
		xASSERT_NOT_EQ(FALSE, m_bRes);

		m_bRes = BF.bEncryptFileCfb64(sFilePlain, sFileEncrypted, CxBlowfish::cmEncrypt);
		xASSERT_NOT_EQ(FALSE, m_bRes);

		m_bRes = BF.bEncryptFileCfb64(sFileEncrypted, sFileDecrypted, CxBlowfish::cmDecrypt);
		xASSERT_NOT_EQ(FALSE, m_bRes);
	}

	//-------------------------------------
	//bEncryptFileCfb64 (with stamp)
    xTEST_BLOCK(cullBlockLoops)
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
		xASSERT_NOT_EQ(FALSE, m_bRes);

		cmRes = BF.cmGetFileCryptStatus(sFilePlain, usStamp);
		xASSERT_EQ(CxBlowfish::cmDecrypt, cmRes);

//		m_bRes = BF.bEncryptFileCfb64(sFilePlain,     sFileEncrypted, usStamp);
//		xASSERT_NOT_EQ(FALSE, m_bRes);
//
//		m_bRes = BF.bEncryptFileCfb64(sFileEncrypted, sFileDecrypted, usStamp);
//		xASSERT_NOT_EQ(FALSE, m_bRes);
	}


    return TRUE;
}
//---------------------------------------------------------------------------
