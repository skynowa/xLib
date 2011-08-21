/****************************************************************************
* Class name:  CxTest_CxFile
* Description: test CxFile
* File name:   CxTest_CxFile.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Filesystem/Win/CxTest_CxFile.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxFile
CxTest_CxFile::CxTest_CxFile() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxFile
CxTest_CxFile::~CxTest_CxFile() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxFile::bUnit(
    const ULONGLONG cullBlockLoops
)
{
#if defined(xOS_WIN)
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
    //????
    CxFile F;

    m_bRes = F.bCreate(csFilePath, CxFile::grRead | CxFile::grWrite,  CxFile::smRead | CxFile::smWrite, CxFile::cfCreateAlways, CxFileAttribute::faNormal); xASSERT_NOT_EQ(FALSE, m_bRes);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_bRes = F.bOpen(csFilePath, CxFile::grRead | CxFile::grWrite,  CxFile::smRead | CxFile::smWrite, CxFile::cfOpenExisting, CxFileAttribute::faNormal); xASSERT_NOT_EQ(FALSE, m_bRes);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_bRes = F.bIsOpen();
    xASSERT_NOT_EQ(FALSE, m_bRes);

    ////m_bRes = F.bAttach(hTest);
    ////xASSERT_NOT_EQ(FALSE, m_bRes);

    ////hRes = F.bDetach();
    ////xASSERT_NOT_EQ(FALSE, m_bRes);

    m_bRes = F.bWrite(csStr.c_str(), csStr.size());
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_bRes = F.bWrite(csStr.c_str(), csStr.size(), &ulWritten);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_bRes = F.bRead(&szInBuff[0], xARRAY_SIZE(szInBuff) - 1);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_bRes = F.bRead(&szInBuff[0], xARRAY_SIZE(szInBuff) - 1, &ulReaded);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_ulRes = F.ulSetPosition(10, CxFile::ppBegin);
    m_ulRes = F.ulGetPosition();
    m_bRes = F.bLock(10, 2);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_bRes = F.bUnlock(10, 2);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_llRes = F.llGetSize();
    xASSERT_NOT_EQ(0LL, m_llRes);

    ////	BOOL CxFile::bSetSize(ULONG ulSize) {

    m_ulRes = F.ulGetType();
    xASSERT_NOT_EQ((ULONG)CxFile::ftUnknown, (ULONG)m_ulRes);

    //--------------------------------------------------
    //bGetTime, bSetTime
    xTEST_BLOCK(cullBlockLoops)
    {
        const FILETIME ctmCreate   = {100000000};
        const FILETIME ctmAccess   = {200000000};
        const FILETIME ctmModified = {300000000};

        m_bRes = F.bSetTime(ctmCreate, ctmAccess, ctmModified);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        FILETIME tmCreate   = {0};
        FILETIME tmAccess   = {0};
        FILETIME tmModified = {0};

        m_bRes = F.bGetTime(&tmCreate, &tmAccess, &tmModified);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        xASSERT_EQ(ctmCreate.dwLowDateTime,    tmCreate.dwLowDateTime);
        xASSERT_EQ(ctmCreate.dwHighDateTime,   tmCreate.dwHighDateTime);
        xASSERT_EQ(ctmAccess.dwLowDateTime,    tmAccess.dwLowDateTime);
        xASSERT_EQ(ctmAccess.dwHighDateTime,   tmAccess.dwHighDateTime);
        xASSERT_EQ(ctmModified.dwLowDateTime,  tmModified.dwLowDateTime);
        xASSERT_EQ(ctmModified.dwHighDateTime, tmModified.dwHighDateTime);
    }

    m_bRes = F.bSetEof();
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_bRes = F.bFlush();
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_bRes = F.bClose();
    xASSERT_NOT_EQ(FALSE, m_bRes);


    /****************************************************************************
    *	static
    *
    *****************************************************************************/

    /*??????? ??? ?????*/
    m_bRes = F.bCreate(csFilePathSt, CxFile::grRead | CxFile::grWrite,  CxFile::smRead | CxFile::smWrite, CxFile::cfCreateAlways, CxFileAttribute::faNormal);
    m_bRes = F.bClose();

    //bIsExists
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFile::bIsExists(xT("C:"));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bIsExists(xT("C:\\Windows"));
        xASSERT_EQ(FALSE, m_bRes);

        ////m_bRes = CxFile::bIsExists(xT("C:\\pagefile.sys"));
        ////xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bIsExists(xT("C:\\{DB5B11E9-28B8-4336-A275-82A0259F48F9}"));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bIsExists(csFilePathSt);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //sIsExists
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxFile::sIsExists(csFilePathSt);
        xASSERT_EQ(sGetWorkDirPath() + xT("\\Test_Static (1).txt"), m_sRes);
    }

    m_bRes = CxFile::bMove(csFilePathSt, csNewFilePath); /*????, ???????*/
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_sRes = CxFile::sCreateTempName(xT("Prefix"));
    xASSERT_EQ(false, m_sRes.empty());

    m_bRes = CxFile::bCopy(csNewFilePath, csFilePathSt);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_bRes = CxFile::bCopy(csFilePathSt,  csNewFilePath, FALSE);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_bRes = CxFile::bReplace(csNewFilePath, csFilePathSt, csBakFilePath);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    ////m_bRes = CxFile::bCutFromEnd(csNewFilePath, 10);
    ////xASSERT_NOT_EQ(FALSE, m_bRes);

    ////m_bRes = CxFile::bCutFromEnd(FILE *pFile, ULONG ulDistanceToCut);
    ////xASSERT_NOT_EQ(FALSE, m_bRes);

    ////m_bRes = CxFile::bCheckSignature(TCHAR *pszBuff, TCHAR *pszSignature, INT iSignatureSize);
    ////xASSERT_NOT_EQ(FALSE, m_bRes);

    m_bRes = CxFile::bSetRandomDate(csNewFilePath);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    //////m_bRes = CxFile::bDelete(csNewFilePath);
    //////xASSERT_NOT_EQ(FALSE, m_bRes);

    m_bRes = CxFile::bWipe(csNewFilePath, 1);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    //-------------------------------------
    //????????
    /*??????? ??? ?????*/
    m_bRes = F.bCreate(csFilePathSt, CxFile::grRead | CxFile::grWrite,  CxFile::smRead | CxFile::smWrite, CxFile::cfCreateAlways, CxFileAttribute::faNormal);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_bRes = F.bClose();
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_ulRes = CxFileAttribute::atGet(csFilePathSt);
    xASSERT_NOT_EQ(0UL, m_ulRes);

    //bSetAttr
    m_bRes = CxFileAttribute::bSet(csFilePathSt, CxFileAttribute::faReadOnly);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_bRes = CxFileAttribute::bSet(csFilePathSt, CxFileAttribute::faNormal);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_bRes = CxFile::bSetAttrCompressed(csFilePathSt, TRUE);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    m_ullRes = CxFile::ullGetCompressedSize(csFilePathSt);
    xASSERT_NOT_EQ((ULONGLONG)INVALID_FILE_SIZE, m_ullRes);

    m_bRes = CxFile::bSetAttrUncompressed(csFilePathSt);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    //-------------------------------------
    //other
    //TODO: bBackupFile
    xTEST_BLOCK(cullBlockLoops)
    {
        CxDir::bCreateForce(csTmpDirPath);

        CxFile _F;

        m_bRes = _F.bCreate(csTmpDirPath + CxConst::xWIN_SLASH + xT("Test.txt"), CxFile::grRead | CxFile::grWrite,  CxFile::smRead | CxFile::smWrite, CxFile::cfCreateAlways, CxFileAttribute::faNormal);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //TODO: bCreateShortcut
    //TODO: bExec
#elif defined(xOS_LINUX)

#endif

	return TRUE;
}
//---------------------------------------------------------------------------
