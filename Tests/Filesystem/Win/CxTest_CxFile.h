/****************************************************************************
* Class name:  CxTest_CxFile
* Description: test CxFile
* File name:   CxTest_CxFile.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxFileH
#define CxTest_CxFileH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/Win/CxFile.h>
//---------------------------------------------------------------------------
class CxTest_CxFile : public CxTest {
	public:
		CxTest_CxFile();
		virtual     ~CxTest_CxFile();

		virtual     BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxFile (comment)
CxTest_CxFile::CxTest_CxFile() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxFile (comment)
CxTest_CxFile::~CxTest_CxFile() {

}
//---------------------------------------------------------------------------
//TODO: + bUnit ()
/*virtual*/
BOOL CxTest_CxFile::bUnit() {
	ULONG         ulWritten     = 0;
	ULONG         ulReaded      = 0;
	const tString csStr         = xT("fcbujdfvugbxcjbfgicfkh");
	TCHAR         szInBuff[256] = {0};
	const tString csFilePath    = sGetWorkDirPath() + xT("\\Test.txt");
	const tString csNewFilePath = sGetWorkDirPath() + xT("\\New.Test.txt");
	const tString csBakFilePath = sGetWorkDirPath() + xT("\\Test_Static.txt.bak");
	const tString csFilePathSt  = sGetWorkDirPath() + xT("\\Test_Static.txt");
	const tString csTmpDirPath  = sGetWorkDirPath() + xT("\\Test");


	//-------------------------------------
	//??????
	////_tsystem(tString(xT("del ") + csFilePath    + xT("/f")).c_str());
	////_tsystem(tString(xT("del ") + csNewFilePath + xT("/f")).c_str());
	////_tsystem(tString(xT("del ") + csBakFilePath + xT("/f")).c_str());
	////_tsystem(tString(xT("del ") + csFilePathSt  + xT("/f")).c_str());

	//-------------------------------------
	//????
	CxFile F;

	m_bRes = F.bCreate(csFilePath, CxFile::grRead | CxFile::grWrite,  CxFile::smRead | CxFile::smWrite, CxFile::cfCreateAlways, CxFileAttribute::faNormal); xASSERT(FALSE != m_bRes);
	xASSERT(FALSE != m_bRes);

	m_bRes = F.bOpen(csFilePath, CxFile::grRead | CxFile::grWrite,  CxFile::smRead | CxFile::smWrite, CxFile::cfOpenExisting, CxFileAttribute::faNormal); xASSERT(FALSE != m_bRes);
	xASSERT(FALSE != m_bRes);

	m_bRes = F.bIsOpen();
	xASSERT(FALSE != m_bRes);

	////m_bRes = F.bAttach(hTest);
	////xASSERT(FALSE != m_bRes);

	////hRes = F.bDetach();
	////xASSERT(FALSE != m_bRes);

	m_bRes = F.bWrite(csStr.c_str(), csStr.size());
	xASSERT(FALSE != m_bRes);

	m_bRes = F.bWrite(csStr.c_str(), csStr.size(), &ulWritten);
	xASSERT(FALSE != m_bRes);

	m_bRes = F.bRead(&szInBuff[0], xARRAY_SIZE(szInBuff) - 1);
	xASSERT(FALSE != m_bRes);

	m_bRes = F.bRead(&szInBuff[0], xARRAY_SIZE(szInBuff) - 1, &ulReaded);
	xASSERT(FALSE != m_bRes);

	m_ulRes = F.ulSetPosition(10, CxFile::ppBegin);
	m_ulRes = F.ulGetPosition();
	m_bRes = F.bLock(10, 2);
	xASSERT(FALSE != m_bRes);

	m_bRes = F.bUnlock(10, 2);
	xASSERT(FALSE != m_bRes);

	m_llRes = F.llGetSize();
	xASSERT(FALSE != m_llRes);

	////	BOOL CxFile::bSetSize(ULONG ulSize) {

	m_ulRes = F.ulGetType();
	xASSERT(CxFile::ftUnknown != m_ulRes);
	
	//--------------------------------------------------
    //bGetTime, bSetTime
    {
        const FILETIME ctmCreate   = {100000000};
        const FILETIME ctmAccess   = {200000000};
        const FILETIME ctmModified = {300000000};

        m_bRes = F.bSetTime(ctmCreate, ctmAccess, ctmModified);
        xASSERT(FALSE != m_bRes);

        FILETIME tmCreate   = {0};
        FILETIME tmAccess   = {0};
        FILETIME tmModified = {0};

        m_bRes = F.bGetTime(&tmCreate, &tmAccess, &tmModified);
        xASSERT(FALSE       != m_bRes);
        
        xASSERT(ctmCreate.dwLowDateTime    == tmCreate.dwLowDateTime);
        xASSERT(ctmCreate.dwHighDateTime   == tmCreate.dwHighDateTime);
        xASSERT(ctmAccess.dwLowDateTime    == tmAccess.dwLowDateTime);
        xASSERT(ctmAccess.dwHighDateTime   == tmAccess.dwHighDateTime);
        xASSERT(ctmModified.dwLowDateTime  == tmModified.dwLowDateTime);
        xASSERT(ctmModified.dwHighDateTime == tmModified.dwHighDateTime);
    }

	m_bRes = F.bSetEof();
	xASSERT(FALSE != m_bRes);

	m_bRes = F.bFlush();
	xASSERT(FALSE != m_bRes);

	m_bRes = F.bClose();
	xASSERT(FALSE != m_bRes);


	/****************************************************************************
	*	static
	*
	*****************************************************************************/

	/*??????? ??? ?????*/
	m_bRes = F.bCreate(csFilePathSt, CxFile::grRead | CxFile::grWrite,  CxFile::smRead | CxFile::smWrite, CxFile::cfCreateAlways, CxFileAttribute::faNormal);
	m_bRes = F.bClose();

	//bIsExists
	{
		m_bRes = CxFile::bIsExists(xT("C:"));
		xASSERT(FALSE == m_bRes);

		m_bRes = CxFile::bIsExists(xT("C:\\Windows"));
		xASSERT(FALSE == m_bRes);

		////m_bRes = CxFile::bIsExists(xT("C:\\pagefile.sys"));
		////xASSERT(FALSE != m_bRes);

		m_bRes = CxFile::bIsExists(xT("C:\\{DB5B11E9-28B8-4336-A275-82A0259F48F9}"));
		xASSERT(FALSE == m_bRes);

		m_bRes = CxFile::bIsExists(csFilePathSt);
		xASSERT(FALSE != m_bRes);
	}

	//sIsExists
	{
		m_sRes = CxFile::sIsExists(csFilePathSt);
		xASSERT(sGetWorkDirPath() + xT("\\Test_Static (1).txt") == m_sRes);
	}

	m_bRes = CxFile::bMove(csFilePathSt, csNewFilePath); /*????, ???????*/
	xASSERT(FALSE != m_bRes);

	m_sRes = CxFile::sCreateTempName(xT("Prefix"));
	xASSERT(false == m_sRes.empty());

	m_bRes = CxFile::bCopy(csNewFilePath, csFilePathSt);
	xASSERT(FALSE != m_bRes);

	m_bRes = CxFile::bCopy(csFilePathSt,  csNewFilePath, FALSE);
	xASSERT(FALSE != m_bRes);

	m_bRes = CxFile::bReplace(csNewFilePath, csFilePathSt, csBakFilePath);
	xASSERT(FALSE != m_bRes);

	////m_bRes = CxFile::bCutFromEnd(csNewFilePath, 10);
	////xASSERT(FALSE != m_bRes);

	////m_bRes = CxFile::bCutFromEnd(FILE *pFile, ULONG ulDistanceToCut);
	////xASSERT(FALSE != m_bRes);

	////m_bRes = CxFile::bCheckSignature(TCHAR *pszBuff, TCHAR *pszSignature, INT iSignatureSize);
	////xASSERT(FALSE != m_bRes);

	m_bRes = CxFile::bSetRandomDate(csNewFilePath);
	xASSERT(FALSE != m_bRes);

	//////m_bRes = CxFile::bDelete(csNewFilePath);
	//////xASSERT(FALSE != m_bRes);

	m_bRes = CxFile::bWipe(csNewFilePath, 1);
	xASSERT(FALSE != m_bRes);

	//-------------------------------------
	//????????
	/*??????? ??? ?????*/
	m_bRes = F.bCreate(csFilePathSt, CxFile::grRead | CxFile::grWrite,  CxFile::smRead | CxFile::smWrite, CxFile::cfCreateAlways, CxFileAttribute::faNormal);
	xASSERT(FALSE != m_bRes);

	m_bRes = F.bClose();
	xASSERT(FALSE != m_bRes);

	m_ulRes = CxFileAttribute::atGet(csFilePathSt);
	xASSERT(0 != m_ulRes);

	//bSetAttr
	m_bRes = CxFileAttribute::bSet(csFilePathSt, CxFileAttribute::faReadOnly);
	xASSERT(FALSE != m_bRes);

	m_bRes = CxFileAttribute::bSet(csFilePathSt, CxFileAttribute::faNormal);
	xASSERT(FALSE != m_bRes);

	m_bRes = CxFile::bSetAttrCompressed(csFilePathSt, TRUE);
	xASSERT(FALSE != m_bRes);

	m_ullRes = CxFile::ullGetCompressedSize(csFilePathSt);
	xASSERT(INVALID_FILE_SIZE != m_ullRes);

	m_bRes = CxFile::bSetAttrUncompressed(csFilePathSt);
	xASSERT(FALSE != m_bRes);

	//-------------------------------------
	//other
	//TODO: bBackupFile
	{
		CxDir::bCreateForce(csTmpDirPath);

		CxFile F;

		m_bRes = F.bCreate(csTmpDirPath + CxConst::xWIN_SLASH + xT("Test.txt"), CxFile::grRead | CxFile::grWrite,  CxFile::smRead | CxFile::smWrite, CxFile::cfCreateAlways, CxFileAttribute::faNormal);
		xASSERT(FALSE != m_bRes);
	}

	//TODO: bCreateShortcut
	//TODO: bExec

	//-------------------------------------
	//??????
	////_tsystem(tString(xT("del ") + csFilePath    + xT("/F")).c_str());
	////_tsystem(tString(xT("del ") + csNewFilePath + xT("/F")).c_str());
	////_tsystem(tString(xT("del ") + csBakFilePath + xT("/F")).c_str());
	////_tsystem(tString(xT("del ") + csFilePathSt  + xT("/F")).c_str());

	return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxFileH
