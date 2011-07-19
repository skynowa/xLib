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
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxBlowfish
CxTest_CxBlowfish::~CxTest_CxBlowfish() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxBlowfish::bUnit() {
	//-------------------------------------
	//bEncryptCfb64
	{
		const uString usPlain[] = {
			uString(1,  'a'),
			uString(2,  'b'),
			uString(3,  'c'),
			uString(8,  'd'),
			uString(11, 'e'),
			uString(12, 'f'),
			uString(16, 'j'),
			uString(17, 'h'),
			uString(28, 'i'),
			uString(32, 'j'),
			uString(51, 'k')
		};

		for (size_t i = 0; i < xARRAY_SIZE(usPlain); i ++) {
			CxBlowfish BF;
			tString sKey       = xT("888888888");
			uString sEncrypted;
			uString sDecrypted;

			m_bRes = BF.bSetKey(sKey);
			xASSERT(FALSE != m_bRes);

			m_bRes = BF.bEncryptCfb64(usPlain[i], &sEncrypted, CxBlowfish::cmEncrypt);
			xASSERT(FALSE != m_bRes);

			m_bRes = BF.bEncryptCfb64(sEncrypted, &sDecrypted, CxBlowfish::cmDecrypt);
			xASSERT(FALSE != m_bRes);

			xASSERT(usPlain[i] == sDecrypted);
		}
	}

	//-------------------------------------
	//bEncryptFileCfb64
	{
		CxBlowfish BF;
		tString sKey           = xT("888888888");
		tString sFilePlain     = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.Plain.txt");
		tString sFileEncrypted = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.Encrypted.txt");
		tString sFileDecrypted = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.FileDecrypted.txt");

		m_bRes = BF.bSetKey(sKey);
		xASSERT(FALSE != m_bRes);

		m_bRes = BF.bEncryptFileCfb64(sFilePlain, sFileEncrypted, CxBlowfish::cmEncrypt);
		xASSERT(FALSE != m_bRes);

		m_bRes = BF.bEncryptFileCfb64(sFileEncrypted, sFileDecrypted, CxBlowfish::cmDecrypt);
		xASSERT(FALSE != m_bRes);
	}

	//-------------------------------------
	//bEncryptFileCfb64 (with stamp)
	{
		CxBlowfish BF;

		CxBlowfish::ECryptMode cmRes = CxBlowfish::cmUnknown;
		tString sKey           = xT("888888888");
		tString sStamp         = xT("stamp");
		uString usStamp        = xS2US(sStamp);
		tString sFilePlain     = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.Plain.txt");
		tString sFileEncrypted = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.Encrypted.txt");
		tString sFileDecrypted = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.FileDecrypted.txt");

		m_bRes = BF.bSetKey(sKey);
		xASSERT(FALSE != m_bRes);

		cmRes = BF.cmGetFileCryptStatus(sFilePlain, usStamp);
		xASSERT(CxBlowfish::cmDecrypt == cmRes);

//		m_bRes = BF.bEncryptFileCfb64(sFilePlain,     sFileEncrypted, usStamp);
//		xASSERT(FALSE != m_bRes);
//
//		m_bRes = BF.bEncryptFileCfb64(sFileEncrypted, sFileDecrypted, usStamp);
//		xASSERT(FALSE != m_bRes);
	}


    return TRUE;
}
//---------------------------------------------------------------------------
