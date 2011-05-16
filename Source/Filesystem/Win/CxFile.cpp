/****************************************************************************
* Class name:  CxFile
* Description: file
* File name:   CxFile.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     03.06.2009 16:30:15
*
*****************************************************************************/


#include <xLib/Filesystem/Win/CxFile.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/Win/CxDrive.h>
#include <xLib/Filesystem/CxDir.h>

#if defined(xOS_WIN)
    #include <fstream>
    #include <io.h>
    #include <share.h>
    #include <fcntl.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <shlobj.h>
    #include <WinIoCtl.h>
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
BOOL CxFile::_ms_bRes = FALSE;
//---------------------------------------------------------------------------
//TODO: CxFile
CxFile::CxFile() :
    m_hHandle(),
    _m_bRes  (FALSE)
{
}
//---------------------------------------------------------------------------
//TODO: ~CxFile
/*virtual*/
CxFile::~CxFile() {
    /*DEBUG*/// m_hHandle - n/a
}
//---------------------------------------------------------------------------
//TODO: bCreate
BOOL
CxFile::bCreate(const tString &csFilePath, ULONG ulAccess, ULONG ulShareMode, ULONG ulFlags, CxFileAttribute::EAttribute atAttributes) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    return bOpen(csFilePath, ulAccess, ulShareMode, ulFlags, atAttributes);
}
//---------------------------------------------------------------------------
//TODO: bTryOpen
BOOL
CxFile::bTryOpen(const tString &csFilePath, ULONG ulAccess, ULONG ulShareMode, ULONG ulFlags, CxFileAttribute::EAttribute atAttributes) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    m_hHandle = ::CreateFile(csFilePath.c_str(), ulAccess, ulShareMode, NULL, ulFlags, static_cast<ULONG>(atAttributes), NULL);
    xCHECK_RET(FALSE == m_hHandle.bIsValid(), FALSE);

    _m_bRes = bClose();
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bOpen
BOOL
CxFile::bOpen(const tString &csFilePath, ULONG ulAccess, ULONG ulShareMode, ULONG ulFlags, CxFileAttribute::EAttribute atAttributes) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    _m_bRes = bClose();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    m_hHandle = ::CreateFile(csFilePath.c_str(), ulAccess, ulShareMode, NULL, ulFlags, static_cast<ULONG>(atAttributes), NULL);
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bClose
BOOL
CxFile::bClose() {
    /*DEBUG*/// m_hHandle - n/a

    _m_bRes = m_hHandle.bClose();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bIsOpen
BOOL
CxFile::bIsOpen() {
    /*DEBUG*/// n/a

    return m_hHandle.bIsValid();
}
//---------------------------------------------------------------------------
//TODO: bIsEmpty
BOOL
CxFile::bIsEmpty() {
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), FALSE);

    return 0 == llGetSize();
}
//---------------------------------------------------------------------------
//TODO: bRead
BOOL
CxFile::bRead(LPVOID pvBuff, ULONG ulCount) {
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(),     FALSE);
    /*DEBUG*/xASSERT_RET(pvBuff   != NULL,                  FALSE);
    /*DEBUG*/xASSERT_RET(!::IsBadWritePtr(pvBuff, ulCount), FALSE);

    //avoid Win32 "null-read"
    xCHECK_RET(0 == ulCount, TRUE);

    ULONG ulBytesRead = 0;

    _m_bRes = ::ReadFile(m_hHandle, pvBuff, ulCount, &ulBytesRead, NULL);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bRead
BOOL
CxFile::bRead(LPVOID pvBuf, ULONG ulCount, LPDWORD pulRead) {
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL                 != pvBuf,    FALSE);
    /*DEBUG*/xASSERT_RET(!::IsBadWritePtr(pvBuf, ulCount), FALSE);
    /*DEBUG*/xASSERT_RET(NULL                 != pulRead,  FALSE);

    //avoid Win32 "null-read"
    xCHECK_RET(0 == ulCount, TRUE);

    *pulRead = 0;

    _m_bRes = ::ReadFile(m_hHandle, pvBuf, ulCount, pulRead, NULL);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bWrite
BOOL
CxFile::bWrite(LPCVOID pvBuf, ULONG ulCount) {
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(),    FALSE);
    /*DEBUG*/xASSERT_RET(NULL                 != pvBuf,   FALSE);
    /*DEBUG*/xASSERT_RET(!::IsBadReadPtr(pvBuf, ulCount), FALSE);

    //avoid Win32 "null-write"
    xCHECK_RET(0 == ulCount, TRUE);

    ULONG ulBytesWritten = 0;

    _m_bRes = ::WriteFile(m_hHandle, pvBuf, ulCount, &ulBytesWritten, NULL);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bWrite
BOOL
CxFile::bWrite(LPCVOID pvBuf, ULONG ulCount, LPDWORD pulWritten) {
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(),      FALSE);
    /*DEBUG*/xASSERT_RET(NULL                 != pvBuf,      FALSE);
    /*DEBUG*/xASSERT_RET(!::IsBadReadPtr(pvBuf, ulCount),    FALSE);
    /*DEBUG*/xASSERT_RET(NULL                 != pulWritten, FALSE);

    //avoid Win32 "null-write"
    xCHECK_RET(0 == ulCount, TRUE);

    *pulWritten = 0;

    _m_bRes = ::WriteFile(m_hHandle, pvBuf, ulCount, pulWritten, NULL);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: ulSetPosition
ULONG
CxFile::ulSetPosition(LONG liOff, EPointerPosition fpPos) {
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), INVALID_SET_FILE_POINTER);

    ULONG ulRes = INVALID_SET_FILE_POINTER;

    ulRes = ::SetFilePointer(m_hHandle, liOff, NULL, static_cast<ULONG>(fpPos));
    /*DEBUG*/xASSERT_RET(INVALID_SET_FILE_POINTER != ulRes, INVALID_SET_FILE_POINTER);

    return ulRes;
}
//---------------------------------------------------------------------------
//TODO: ulGetPosition
ULONG
CxFile::ulGetPosition() {
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), INVALID_SET_FILE_POINTER);

    return ulSetPosition(0, ppCurr);
}
//---------------------------------------------------------------------------
//TODO: bLock
BOOL
CxFile::bLock(ULONG ulOffset, ULONG ulSize) {
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), FALSE);

    _m_bRes = ::LockFile(m_hHandle, ulOffset, 0, ulSize, 0);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bUnlock
BOOL
CxFile::bUnlock(ULONG ulOffset, ULONG ulSize) {
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), FALSE);

    _m_bRes = ::UnlockFile(m_hHandle, ulOffset, 0, ulSize, 0);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bSetEof
BOOL
CxFile::bSetEof() {
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), FALSE);

    _m_bRes = ::SetEndOfFile(m_hHandle);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bFlush
BOOL
CxFile::bFlush() {
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), FALSE);

    _m_bRes = ::FlushFileBuffers(m_hHandle);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: llGetSize
LONGLONG
CxFile::llGetSize() {
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), 0);

    LARGE_INTEGER llRes;

    _m_bRes = ::GetFileSizeEx(m_hHandle, &llRes);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return llRes.QuadPart;
}
//---------------------------------------------------------------------------
//TODO: bSetSize
BOOL
CxFile::bSetSize(ULONG ulSize) {
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), 0);

    ulSetPosition(ulSize, ppBegin);
    /*DEBUG*/

    _m_bRes = bSetEof();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: ulGetType
ULONG/*EFileType*/
CxFile::ulGetType() {
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), FALSE);

    ULONG ulRes = (ULONG)ftUnknown;

    ulRes = ::GetFileType(m_hHandle);
    /*DEBUG*/xASSERT_RET((ULONG)ftUnknown != ulRes, (ULONG)ftUnknown);

    return ulRes;
}
//---------------------------------------------------------------------------
//TODO: bGetTime
BOOL
CxFile::bGetTime(FILETIME *pftCreate, FILETIME *pftAccess, FILETIME *pftModified) {
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), FALSE);

    _m_bRes = ::GetFileTime(m_hHandle, pftCreate, pftAccess, pftModified);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bSetTime
BOOL
CxFile::bSetTime(FILETIME *pftCreate, FILETIME *pftAccess, FILETIME *pftModified) {
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), FALSE);

    _m_bRes = ::SetFileTime(m_hHandle, pftCreate, pftAccess, pftModified);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------



/****************************************************************************
*    Static
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: bIsExists
/*static*/
BOOL
CxFile::bIsExists(const tString &csFilePath) {
    ///////////*DEBUG*/xASSERT_RET(!::IsBadStringPtr(csFilePath.c_str(), MAX_PATH), FALSE);
    //////////
    //////////ULONG ulErrMode = ::SetErrorMode(SEM_FAILCRITICALERRORS);
    //////////ULONG ulAttribs = ::GetFileAttributes(csFilePath.c_str());
    //////////::SetErrorMode(ulErrMode);
    //////////
    //////////return (ulAttribs != (ULONG) -1) && (ulAttribs & FILE_ATTRIBUTE_DIRECTORY) == 0;

    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    CxFileAttribute::EAttribute atAttr = CxFileAttribute::faInvalid;

    atAttr = CxFileAttribute::atGet(csFilePath.c_str());

    //��� �� ���� � �� ����� � �� ...
    xCHECK_RET(CxFileAttribute::faInvalid == atAttr, FALSE);

    //��� �����
    xCHECK_RET(atAttr & CxFileAttribute::faDirectory, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: sIsExists
/*static*/
tString
CxFile::sIsExists(const tString &csFilePath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());

    tString sRes;
    sRes.assign(csFilePath);

    //--static INT s_iFileExistsIndex = 0;
    tString    sFileDir           = CxPath::sGetDir(sRes);
    tString    sFileName          = CxPath::sGetName(sRes);
    tString    sFileExt           = CxPath::sGetExt(sRes);

    for (INT s_iFileExistsIndex = 1; TRUE == bIsExists(sRes); ++ s_iFileExistsIndex) {
        sRes = sFileDir                                   + CxConst::xSLASH     +
               sFileName                                  + xT(" (")                +
               CxString::lexical_cast(s_iFileExistsIndex) + xT(")") + CxConst::xDOT +
               sFileExt;
    }

    //--s_iFileExistsIndex = 0;

    return sRes;
}
//---------------------------------------------------------------------------
//TODO: tpGetTypeEx
/*static*/
CxFile::ETypeEx
CxFile::tpGetTypeEx(const tString &csFilePath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), fteUnknown);

    ETypeEx ftRes = fteUnknown;

    if (TRUE == CxFile::bIsExists(csFilePath)) {
        ftRes = fteFile;
    }
    else if (TRUE == CxDir::bIsExists(csFilePath)) {
        ftRes = fteDir;
    }
    else {
        ftRes = fteUnknown;
    }

    return ftRes;
}
//---------------------------------------------------------------------------
//TODO: llGetSize
/*static*/
LONGLONG
CxFile::llGetSize(const tString &csFilePath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), 0);

    LONGLONG llRes = 0;
    BOOL     bRes  = FALSE;

    CxFile flFile;

    bRes = flFile.bOpen(csFilePath, CxFile::grRead, CxFile::smDenyAll, CxFile::cfOpenExisting, CxFileAttribute::faNormal);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, 0);

    llRes = flFile.llGetSize();
    /*DEBUG*/// n/a

    bRes = flFile.bClose();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, 0);

    return llRes;
}
//---------------------------------------------------------------------------
//TODO: bDelete
/*static*/
BOOL
CxFile::bDelete(const tString &csFilePath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    BOOL bRes = FALSE;

    bRes = bIsExists(csFilePath);
    xCHECK_RET(FALSE == bRes, TRUE);

    bRes = CxFileAttribute::bSet(csFilePath, CxFileAttribute::faNormal);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = ::DeleteFile(csFilePath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: FIXME - bMove
/*static*/
BOOL
CxFile::bMove(const tString &csFilePathIn, const tString &csFilePathOut) {
    /*DEBUG*/xASSERT_RET(false == csFilePathIn.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePathIn), FALSE);
    /*DEBUG*/xASSERT_RET(false == csFilePathOut.empty(),   FALSE);

    BOOL bRes = FALSE;

    //-------------------------------------
    //������� ������� "������ ������"
    bRes = CxFileAttribute::bSet(csFilePathIn, CxFileAttribute::faNormal);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);


    if (TRUE == bIsExists(csFilePathOut)) {
        bRes = CxFileAttribute::bSet(csFilePathOut, CxFileAttribute::faNormal);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    //-------------------------------------
    //����������
    bRes = ::MoveFile(csFilePathIn.c_str(), csFilePathOut.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
//TODO: sCreateTempName
/*static*/
tString
CxFile::sCreateTempName(const tString &csExt) {    //csDirPath - ��� �����
    /*DEBUG*/TCHAR szFatalChars[] = {xT('\\'), xT('/'), xT(':'), xT('*'), xT('<'), xT('>'), xT('|'), xT('?'), xT('"'), xT('\t'), xT('\n'), xT('\r')};
    /*DEBUG*/for (size_t i = 0; i < xARRAY_SIZE(szFatalChars); ++ i) {
    /*DEBUG*/    xASSERT_RET(tString::npos == csExt.find(szFatalChars[i]), tString());
    /*DEBUG*/}

    tString sRes;

    if (true == csExt.empty()) {
        sRes = CxString::sCreateGuid();
    } else {
        sRes = CxString::sCreateGuid() + CxConst::xDOT + csExt;
    }

    return sRes;
}
//--------------------------------------------------------------------------
//TODO: bCopy
/*static*/
BOOL
CxFile::bCopy(const tString &csFilePathFrom, const tString &csFilePathTo) {
    /*DEBUG*/xASSERT_RET(false == csFilePathFrom.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePathFrom), FALSE);
    /*DEBUG*/xASSERT_RET(false == csFilePathTo.empty(),      FALSE);

    std::ifstream ifsStream(csFilePathFrom.c_str());
    if (!ifsStream || ifsStream.fail() || !ifsStream.good() || !ifsStream.is_open() || ifsStream.eof()) {
        return FALSE;
    }
    std::ofstream ofsStream(csFilePathTo.c_str());
    if (!ofsStream || ofsStream.fail() || !ofsStream.good() || !ofsStream.is_open() || ofsStream.eof()) {
        return FALSE;
    }

    ofsStream << ifsStream.rdbuf();
    ofsStream.close();

    return TRUE;
}
//--------------------------------------------------------------------------
//TODO: bCopy
/*static*/
BOOL
CxFile::bCopy(const tString &csFilePathFrom, const tString &csFilePathTo, BOOL bFailIfExists) {
    /*DEBUG*/xASSERT_RET(false == csFilePathFrom.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePathFrom), FALSE);
    /*DEBUG*/xASSERT_RET(false == csFilePathTo.empty(),      FALSE);

    BOOL bRes = FALSE;

    bRes = ::CopyFile(csFilePathFrom.c_str(), csFilePathTo.c_str(), bFailIfExists);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bReplace
/*static*/
BOOL
CxFile::bReplace(const tString &csOldFileName, const tString &csNewFilePath, const tString &csBackupFilePath) {
    /*DEBUG*/xASSERT_RET(false == csOldFileName.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csOldFileName), FALSE);
    /*DEBUG*/xASSERT_RET(false == csNewFilePath.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csNewFilePath), FALSE);
    /*DEBUG*/xASSERT_RET(false == csBackupFilePath.empty(), FALSE);

    BOOL bRes = FALSE;

    bRes = ::ReplaceFile(csOldFileName.c_str(), csNewFilePath.c_str(), csBackupFilePath.c_str(), REPLACEFILE_WRITE_THROUGH/* | REPLACEFILE_IGNORE_MERGE_ERRORS*/, (LPVOID)NULL, (LPVOID)NULL);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
//TODO: bWipe
/*static*/
BOOL
CxFile::bWipe(const tString &csFilePath, UINT uiPasses) {
    /*DEBUG*/// csFilePath - n/a
    /*DEBUG*/// iPasses    - n/a

    xCHECK_RET(FALSE == bIsExists(csFilePath), TRUE);

    //-------------------------------------
    //����������
    BOOL           bRes                = FALSE;
    ULONG          ulFilePointer       = INVALID_SET_FILE_POINTER;
    const LONGLONG cllClusterSize      = 32 * 1024;
    LONGLONG       llFileSize          = 0;
    const LONG     cliBuffSize            = 32 * 1024;
    UCHAR          ucBuff[cliBuffSize] = {0};
    tString        sFilePathOut;

    //-------------------------------------
    //��������, ���������, �������� �����
    {
        CxFile flFile;

        //-------------------------------------
        //�������� ������� "������ ������"
        bRes = CxFileAttribute::bSet(csFilePath, CxFileAttribute::faNormal);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        //-------------------------------------
        //�������� ������� ������
        bRes = bSetAttrCompressed(csFilePath, FALSE);
        /*DEBUG*/////xASSERT_RET(FALSE != bRes, FALSE);
        /*DEBUG*/xASSERT(FALSE != bRes);

        //-------------------------------------
        //����� ��������� ������ � ����, ������� �� 32kb, �������-�� ���
        {
            bRes = flFile.bOpen(csFilePath, CxFile::grAll, CxFile::smRead | CxFile::smWrite, CxFile::cfOpenExisting, CxFileAttribute::faNormal);
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

            //��������� ������� ����� � ����������� ������� ������ ��� �����
            llFileSize = flFile.llGetSize();
            llFileSize += (cllClusterSize - (llFileSize % cllClusterSize));

            for (UINT p = 0; p < uiPasses; ++ p) {
                xRANDOMIZE();

                for (LONG i = 0; i < llFileSize; i += cliBuffSize) {
                    //���������� ������ ��������� �������
                    for (LONGLONG j = 0; j < cliBuffSize; ++ j) {
                        ucBuff[j] = static_cast<UCHAR>(xRANDOM(255) + 1);
                    }

                    //������ ������ � ����
                    bRes = flFile.bWrite(ucBuff, cliBuffSize);
                    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
                }

                bRes = flFile.bFlush();
                /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

                ulFilePointer = flFile.ulSetPosition(0, ppBegin);
                /*DEBUG*/xASSERT_RET(INVALID_SET_FILE_POINTER != ulFilePointer, FALSE);
            }
        }

        //-------------------------------------
        //random filedate (���� ��������/�����������/���������� ��������� � ������ ��������)
        {
            //-------------------------------------
            //���� ��������
            FILETIME ftCreationTime = {0};
            xRANDOMIZE();
            ftCreationTime.dwHighDateTime = rand();
            xRANDOMIZE();
            ftCreationTime.dwLowDateTime  = rand();

            //-------------------------------------
            //���� ���������� �������
            FILETIME ftLastAccessTime = {0};
            xRANDOMIZE();
            ftLastAccessTime.dwHighDateTime = rand();
            xRANDOMIZE();
            ftLastAccessTime.dwLowDateTime  = rand();

            //-------------------------------------
            //���� ���������� ���������
            FILETIME ftLastWriteTime = {0};
            xRANDOMIZE();
            ftLastWriteTime.dwHighDateTime = rand();
            xRANDOMIZE();
            ftLastWriteTime.dwLowDateTime  = rand();

            //-------------------------------------
            //������ ��������
            bRes = flFile.bSetTime(&ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
        }

        //-------------------------------------
        //truncate to zero
        {
            ulFilePointer = flFile.ulSetPosition(0, ppBegin);
            /*DEBUG*/xASSERT_RET(INVALID_SET_FILE_POINTER != ulFilePointer, FALSE);

            bRes = flFile.bSetEof();
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
        }
    }

    //-------------------------------------
    //random file name (����� ����������� ��������� ��� ����� ����� ��� MAX_PATH)
    {
        tString sRandomFileName;
        sRandomFileName = CxString::sCreateGuid();
        sRandomFileName.resize( CxPath::sGetFullName(csFilePath).size() );

        sFilePathOut = CxPath::sGetDir(csFilePath) + CxConst::xSLASH + sRandomFileName;

        bRes = CxFile::bMove(csFilePath, sFilePathOut);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    //-------------------------------------
    //delete file
    {
        bRes = CxFile::bDelete(sFilePathOut);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    return TRUE;
}
//--------------------------------------------------------------------------
//TODO: bSetRandomDate
/*static*/
BOOL
CxFile::bSetRandomDate(const tString &csFilePath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), FALSE);

    //////////CxHandle<INVALID_HANDLE_VALUE> hFile;

    //////////hFile = ::CreateFile(csFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS, NULL);
    ///////////*DEBUG*/xASSERT_RET(FALSE != hFile.bIsValid(), FALSE);

    ////////////-------------------------------------
    ////////////���� ��������
    //////////FILETIME ftCreationTime = {0};
    //////////xRANDOMIZE();
    //////////ftCreationTime.dwHighDateTime = rand();
    //////////xRANDOMIZE();
    //////////ftCreationTime.dwLowDateTime  = rand();

    ////////////-------------------------------------
    ////////////���� ���������� �������
    //////////FILETIME ftLastAccessTime = {0};
    //////////xRANDOMIZE();
    //////////ftLastAccessTime.dwHighDateTime = rand();
    //////////xRANDOMIZE();
    //////////ftLastAccessTime.dwLowDateTime  = rand();

    ////////////-------------------------------------
    ////////////���� ���������� ���������
    //////////FILETIME ftLastWriteTime = {0};
    //////////xRANDOMIZE();
    //////////ftLastWriteTime.dwHighDateTime = rand();
    //////////xRANDOMIZE();
    //////////ftLastWriteTime.dwLowDateTime  = rand();

    ////////////-------------------------------------
    ////////////������ ��������
    //////////BOOL bRes = ::SetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
    ///////////*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
//TODO: ullGetCompressedSize
/*static*/
ULONGLONG
CxFile::ullGetCompressedSize(const tString &csFilePath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    ULONG ulLowPart  = 0;
    ULONG ulHighPart = 0;

    ulLowPart = ::GetCompressedFileSize(csFilePath.c_str(), &ulHighPart);
    if (INVALID_FILE_SIZE == ulLowPart) {
        /*DEBUG*/xASSERT_RET(NO_ERROR == ::GetLastError(), INVALID_FILE_SIZE);
    }

    return ((ULONGLONG)(ulHighPart) << 32) | ulLowPart;
}
//--------------------------------------------------------------------------


/****************************************************************************
* ��������
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: bSetAttrUncompressed
/*static*/
BOOL
CxFile::bSetAttrUncompressed(const tString &csFilePath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    BOOL bRes = FALSE;

    CxFileAttribute::EAttribute atFileAttr = CxFileAttribute::faInvalid;

    //������ �������� �����
    atFileAttr = CxFileAttribute::atGet(csFilePath);
    /*DEBUG*/xASSERT_RET(CxFileAttribute::faInvalid != atFileAttr, FALSE);

    //������ �������� "������"
    bRes = CxFileAttribute::bSet(csFilePath, static_cast<CxFileAttribute::EAttribute>( atFileAttr | CxFileAttribute::faCompressed) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bSetAttrCompressed
/*static*/
BOOL
CxFile::bSetAttrCompressed(const tString &csFilePath, BOOL bIsCompress) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// bIsCompress - n/a

    xCHECK_RET(CxFileAttribute::atGet(csFilePath) & CxFileAttribute::faCompressed, TRUE);

    BOOL   bRes            = FALSE;
    SHORT  siCompression   = COMPRESSION_FORMAT_NONE;
    ULONG  ulBytesReturned = 0;
    CxFile fFile;

    bRes = fFile.bCreate(csFilePath, grRead | grWrite, 0, cfOpenExisting, CxFileAttribute::faNormal);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    (TRUE == bIsCompress) ? (siCompression = COMPRESSION_FORMAT_DEFAULT) : (siCompression = COMPRESSION_FORMAT_NONE);

    bRes = ::DeviceIoControl(fFile.m_hHandle, FSCTL_SET_COMPRESSION, &siCompression, sizeof(SHORT), NULL, 0, &ulBytesReturned, NULL);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------





//--------------------------------------------------------------------------
/*static*/
bool
CxFile::bWriteText(const tString &csFilePath, const tString &csText) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);

    bool bRes = false;

    HANDLE hFile = ::CreateFile(csFilePath.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hFile, false);

    DWORD dwWrittenBytes = 0;
    BOOL bWriteRes = ::WriteFile(hFile, csText.c_str(), (DWORD)csText.size(), &dwWrittenBytes, NULL);
    if (FALSE == bWriteRes) {
        return false;
    }

    if (csText.size() != dwWrittenBytes) {
        bRes = false;
    } else {
        bRes = true;
    }

    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hFile, false);
    if (NULL != hFile) {
        ::CloseHandle(hFile); hFile = NULL;
    }

    return bRes;
}
//--------------------------------------------------------------------------
/*static*/
tString
CxFile::sReadText(const tString &csFilePath) {    ///char -> BYTE
    /*
    tString xstr;
    std::ifstream xfile("inputfile.txt", std::ios::binary);

    //������ ������ �����, � �������� ������ � ������
    xfile.seekg( 0, std::ios_base::end );
    xstr.resize( xfile.tellg() );
    xfile.seekg( 0, std::ios_base::beg );

    //�������� ������
    xfile.read( (void*)xstr.data(), xstr.size() );
    */

    /*
    std::ifstream iFile("inputfile.txt");
    tString mystr(std::istreambuf_iterator<char>(iFile), std::istreambuf_iterator<char>());
    */

    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), xT(""));
    /*DEBUG*/xASSERT_RET(TRUE == CxFile::bIsExists(csFilePath), xT(""));

    HANDLE hFile = ::CreateFile(csFilePath.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, NULL);
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hFile, xT(""));

    //-------------------------------------
    //�������� ������ �����
    DWORD dwFileSize = ::GetFileSize(hFile, NULL);
    if (0xFFFFFFFF == dwFileSize || 0 == dwFileSize) {
        /*DEBUG*/xASSERT_RET(NULL != hFile, xT(""));
        if (NULL != hFile) {
            ::CloseHandle(hFile);     hFile = NULL;
        }

        return xT("");
    }

    //-------------------------------------
    //������ ����
    tString  sRes = xT("");
    ULONG        dwRealyRead = 0;
    TCHAR        *pBuff       = new TCHAR[dwFileSize + 1];
    if (NULL == pBuff) {
        ::CloseHandle(hFile);

        return xT("");
    }
    if (FALSE == ::ReadFile(hFile, pBuff, dwFileSize, &dwRealyRead, NULL)) {
        delete [] pBuff;
        ::CloseHandle(hFile);

        return xT("");
    }
    if (dwFileSize != dwRealyRead) {
        delete [] pBuff;
        ::CloseHandle(hFile);

        return xT("");
    }

    //-------------------------------------
    //������ � tString
    sRes = tString(pBuff, dwFileSize);

    //-------------------------------------
    //��������� ���� � ������� �����3
    /*DEBUG*/xASSERT_RET(NULL != pBuff, xT(""));
    if (NULL != pBuff) {
        delete [] pBuff;    pBuff = NULL;
    }

    /*DEBUG*/xASSERT_RET(NULL != hFile, xT(""));
    if (NULL != hFile) {
        ::CloseHandle(hFile);     hFile = NULL;
    }

    return sRes;
}
//--------------------------------------------------------------------------



/****************************************************************************
*    other
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: bBackup
/*static*/
BOOL
CxFile::bBackup(const tString &csFilePath, const tString &csDestDirPath, BOOL bMakeDaily) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(false == csDestDirPath.empty(), FALSE);

    BOOL bRes = FALSE;

    bRes = CxFile::bIsExists(csFilePath);
    xCHECK_RET(FALSE == bRes, FALSE);

    bRes = CxDir::bIsExists(csDestDirPath);
    xCHECK_DO(FALSE == bRes, CxDir::bCreateForce(csDestDirPath));

    //-------------------------------------
    //format file full name
    CxDateTime dtDT;

    tString sBackupFilePath =
        CxPath::sSlashAppend(csDestDirPath) +
        CxPath::sGetFullName(csFilePath)    +
        xT(".bak [") + CxString::sReplaceAll((TRUE == bMakeDaily) ? (dtDT.dtGetCurrent().sFormat(CxDateTime::ftDate)) : (dtDT.dtGetCurrent().sFormat(CxDateTime::ftDateTime)), xT(":"), xT("-")) + xT("]");

    bRes = CxFile::bIsExists(sBackupFilePath);
    xCHECK_RET(TRUE == bRes, TRUE);

    //-------------------------------------
    //check for enough space
    ULONGLONG ullTotalFreeBytes = 0;
    bRes = CxDrive::bGetFreeSpace(CxPath::sGetDrive(csDestDirPath), NULL, NULL, &ullTotalFreeBytes);

    xCHECK_DO((ULONGLONG)CxFile::llGetSize(csFilePath) > ullTotalFreeBytes, CxMsgBoxT::iShow(xT("Not enough free space"), xT("File backup"), MB_OK); return TRUE);

    //-------------------------------------
    //copy
    bRes = bCopy(csFilePath, sBackupFilePath, TRUE);
    xCHECK_RET(FALSE == bRes, FALSE);

    //-------------------------------------
    //check for a valid backup
    xCHECK_RET(FALSE                 != bIsExists(sBackupFilePath), FALSE);
    xCHECK_RET(liGetSize(csFilePath) == liGetSize(sBackupFilePath), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bExec
/*static*/
BOOL
CxFile::bExec(const tString &csFilePath, const tString &csParams) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// csParams - n/a

    BOOL bRes = FALSE;

    //-------------------------------------
    //�����, ���� ��� ����
    tString sCmdLine;

    bRes = CxDir::bIsExists(csFilePath);
    if (FALSE != bRes) {
        //�����
        sCmdLine =  xT("explorer.exe /e, ") + csFilePath;
    } else {
        //���� ���� �� ����������
        bRes = CxFile::bIsExists(csFilePath);
        xASSERT_RET(FALSE != bRes, FALSE);
        xCHECK_RET(FALSE == bRes, FALSE);

        if (xT("cpl") == CxPath::sGetExt(csFilePath)) {
            //�������
            sCmdLine = xT("control.exe ") + csFilePath;
        } else {
            //exe-����
            sCmdLine = csFilePath;
        }
    }

    //���������� ����������
    xCHECK_DO(false == csParams.empty(), sCmdLine += xT(" ") + csParams);

    //-------------------------------------
    //������� �� ������
    STARTUPINFO         si = {0};   si.cb = sizeof(si);
    PROCESS_INFORMATION pi = {0};

    bRes = ::CreateProcess(NULL, &sCmdLine.at(0), NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    ::CloseHandle(pi.hThread);
    ::CloseHandle(pi.hProcess);

    return TRUE;
}
//---------------------------------------------------------------------------
