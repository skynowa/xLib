/****************************************************************************
* Class name:  CxStdioFile
* Description: file
* File name:   CxStdioFile.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     21.05.2009 17:46:38
*
*****************************************************************************/


#include <xLib/Filesystem/CxStdioFile.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Common/CxDateTime.h>

#if defined(xOS_WIN)
    #include <xLib/Common/CxLocale.h>
    #include <xLib/Filesystem/Win/CxFileAttribute.h>
#endif


/****************************************************************************
*    public: constructors, destructor
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxStdioFile (constructor)
CxStdioFile::CxStdioFile() :
    _m_bRes     (FALSE),
    _m_pFile    (NULL),
    _m_sFilePath()
{
}
//---------------------------------------------------------------------------
//DONE: ~CxStdioFile (destructor)
CxStdioFile::~CxStdioFile() {
    /*DEBUG*/// n/a

    _m_bRes = bClose();
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------

/****************************************************************************
*    public: open, get
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bIsValid (validating handle)
BOOL
CxStdioFile::bIsValid() const {
    /*DEBUG*/

    return static_cast<BOOL>( NULL != _m_pFile );
}
//---------------------------------------------------------------------------
//DONE: bOpen (open)
BOOL
CxStdioFile::bOpen(const tString &csFilePath, const EOpenMode omMode) {
    /*DEBUG*/xASSERT_RET(FALSE == bIsValid(),                       FALSE);
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != CxPath::bIsValidName(csFilePath), FALSE);
    /*DEBUG*/// comMode - n/a

    FILE *pFile = _tfopen(csFilePath.c_str(), _sGetOpenMode(omMode).c_str());
    /*DEBUG*/xASSERT_RET(NULL != pFile, FALSE);

    _m_pFile     = pFile;
    _m_sFilePath = csFilePath;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bReopen (reopen with different file or mode)
BOOL
CxStdioFile::bReopen(const tString &csFilePath, const EOpenMode omMode) {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),                       FALSE);
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != CxPath::bIsValidName(csFilePath), FALSE);
    /*DEBUG*/// omMode - n/a

    FILE *pFile = _tfreopen(csFilePath.c_str(), _sGetOpenMode(omMode).c_str(), _m_pFile);
    /*DEBUG*/xASSERT_RET(NULL != pFile, FALSE);

    _m_pFile     = pFile;
    _m_sFilePath = csFilePath;

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bAttach (attach to stream)
BOOL
CxStdioFile::bAttach(FILE *pflFile) {
    /*DEBUG*/// _m_pFile - n/a
    /*DEBUG*/// pflFile  - n/a

    xCHECK_DO(TRUE == bIsValid(), bClose());

    _m_pFile     = pflFile;
    _m_sFilePath = CxConst::xSTR_EMPTY;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: pGet (get handle)
FILE *
CxStdioFile::pGet() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), NULL);

    return _m_pFile;
}
//---------------------------------------------------------------------------
//DONE: sGetPath (get file path)
tString
CxStdioFile::sGetPath() const {
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), tString());

    return _m_sFilePath;
}
//---------------------------------------------------------------------------

/****************************************************************************
* public: read / write
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: uiRead (read block of data)
size_t
CxStdioFile::uiRead(LPVOID pvBuff, const size_t cuiCount) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0);
    /*DEBUG*/xASSERT_RET(NULL != pvBuff,      0);

    size_t uiRes = 0;

    uiRes = fread(pvBuff, 1, cuiCount, pGet());
    /*DEBUG*/xASSERT_RET(cuiCount >= uiRes, uiRes);

    return uiRes;
}
//---------------------------------------------------------------------------
//DONE: uiWrite (write block of data)
size_t
CxStdioFile::uiWrite(const LPVOID pcvBuff, const size_t cuiCount) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0);
    /*DEBUG*/xASSERT_RET(NULL  != pcvBuff,    0);

    size_t uiRes = 0;

    uiRes = fwrite(pcvBuff, 1, cuiCount, pGet());
    /*DEBUG*/xASSERT_RET(cuiCount == uiRes, uiRes);

    return uiRes;
}
//---------------------------------------------------------------------------
//DONE: bRead (read to uString)
BOOL
CxStdioFile::bRead(uString *psBuff) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL != psBuff,      FALSE);

    size_t uiRes      = 0;
    LONG   liFileSize = 0;

    liFileSize = liGetSize();
    /*DEBUG*/xASSERT_RET(ppError != liFileSize, FALSE);

    (*psBuff).clear();
    (*psBuff).resize(liFileSize);
    xCHECK_RET(0 == liFileSize, TRUE);

    uiRes = fread(&(*psBuff).at(0), sizeof(uString::value_type), (*psBuff).size(), pGet());
    /*DEBUG*/xASSERT_RET((*psBuff).size() == uiRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWrite (write from uString)
BOOL
CxStdioFile::bWrite(const uString &csBuff) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*///csBuff - n/a

    size_t uiRes = 0;

    uiRes = fwrite(&csBuff.at(0), sizeof(uString::value_type), csBuff.size(), pGet());
    /*DEBUG*/xASSERT_RET(csBuff.size() == uiRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: iWrite(Write formatted output to stream)
INT
CxStdioFile::iWrite(LPCTSTR pcszFormat, ...) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), etError);
    /*DEBUG*/xASSERT_RET(NULL  != pcszFormat, etError);

    INT iRes = etError;

    va_list args = NULL;
    va_start(args, pcszFormat);

    iRes = _vftprintf(pGet(), pcszFormat, args);
    /*DEBUG*/xASSERT_RET(etError < iRes, etError);

    va_end(args);

    return iRes;
}
//---------------------------------------------------------------------------
//DONE: iWriteV (Write formatted variable argument list to stream)
INT
CxStdioFile::iWriteV(LPCTSTR pcszFormat, va_list arg) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), etError);
    /*DEBUG*/xASSERT_RET(NULL  != pcszFormat, etError);
    /*DEBUG*/xASSERT_RET(NULL  != arg,        etError);

    INT iRes = etError;

    iRes = _vftprintf(pGet(), pcszFormat, arg);
    /*DEBUG*/xASSERT_RET(etError < iRes, etError);

    return iRes;
}
//---------------------------------------------------------------------------
//DONE: bReadLine (read string to newline or to the end of file)
BOOL
CxStdioFile::bReadLine(tString *psStr, const size_t cuiMaxCount) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != psStr,      FALSE);
    /*DEBUG*/xASSERT_RET(0     < cuiMaxCount, FALSE);

    LPTSTR pszRes = NULL;

    #if xTEMP_DISABLED
        if ((*psStr).size() != cuiMaxCount) {
            (*psStr).resize(cuiMaxCount);
        }
        std::fill((*psStr).begin(), (*psStr).end(), tString::value_type());
    #endif

    (*psStr).clear();
    (*psStr).resize(cuiMaxCount + 1);   //+ 1 for 0

    pszRes = _fgetts(&(*psStr).at(0), (*psStr).size(), pGet());
    /*DEBUG*/xASSERT_RET(NULL != pszRes, FALSE);

    (*psStr).erase( (*psStr).end() - 1 );   //erase last char - 0

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWriteLine (writes string and '\n')
BOOL
CxStdioFile::bWriteLine(const tString &csStr) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    tString sLine;

    sLine.assign(csStr);
    sLine.append(CxConst::xEOL);

    size_t uiRes  = uiWrite(&sLine.at(0), sLine.size());
    /*DEBUG*/xASSERT_RET(uiRes == sLine.size(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWriteString (write string)
BOOL
CxStdioFile::bWriteString(const tString &csStr) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    INT iRes = etError;

    iRes = _fputts(csStr.c_str(), pGet());
    /*DEBUG*/xASSERT_RET(iRes != etError, FALSE);
    /*DEBUG*/xASSERT_RET(EOF < iRes,      FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: cReadChar (get character)
TCHAR
CxStdioFile::cReadChar() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    INT iRes = etError;

    iRes = _gettc(pGet());
    /*DEBUG*/// n/a xASSERT_RET(iRes != etError, (TCHAR)etError);
    /*DEBUG*/// n/a xASSERT_RET(EOF < iRes,      (TCHAR)etError);

    return static_cast<TCHAR>(iRes);
}
//---------------------------------------------------------------------------
//TODO: bWriteChar (write character)
BOOL
CxStdioFile::bWriteChar(TCHAR cChar) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    INT iRes = etError;

    iRes = _fputtc(static_cast<INT>(cChar), pGet());
    /*DEBUG*/xASSERT_RET(static_cast<INT>(cChar) != etError, FALSE);
    /*DEBUG*/xASSERT_RET(static_cast<INT>(cChar) == iRes,    FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bUngetChar (Unget character from stream)
BOOL
CxStdioFile::bUngetChar(TCHAR cChar) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    INT iRes = etError;

    iRes = _ungettc(cChar, pGet());
    /*DEBUG*/xASSERT_RET(iRes  != etError,                  FALSE);
    /*DEBUG*/xASSERT_RET(cChar == static_cast<TCHAR>(iRes), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DINE: bClear (clear)
BOOL
CxStdioFile::bClear() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    return bResize(0L);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: other
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bLocking (Locks or unlocks bytes of a file)
BOOL
CxStdioFile::bLocking(const ELockingMode clmMode, LONG liBytes) {
    INT iRes = etError;

#if defined(xOS_WIN)
    iRes = _locking(_iGetHandle(), clmMode, liBytes);
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
#elif defined(xOS_LINUX)
    iRes = lockf(_iGetHandle(), clmMode, static_cast<off_t>( liBytes ));
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSetPosition (REFilePosition stream position indicator)
BOOL
CxStdioFile::bSetPosition(LONG lOffset, const EPointerPosition cppPos) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    INT iRet = ppError;

    iRet = fseek(pGet(), lOffset, cppPos);
    /*DEBUG*/xASSERT_RET(0 == iRet, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: liGetPosition (Get current position in stream)
LONG
CxStdioFile::liGetPosition() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    LONG liRes = ppError;

    liRes = ftell(pGet());
    /*DEBUG*/xASSERT_RET(ppError != liRes, ppError);

    return liRes;
}
//---------------------------------------------------------------------------
//TODO: bSetVBuff (Change stream buffering)
BOOL
CxStdioFile::bSetVBuff(LPSTR pszBuff, const EBufferingMode cbmMode, size_t uiSize) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),               FALSE);
    /*DEBUG*/// pszBuff - n/a
    /////*DEBUG*/xASSERT_RET(2 < uiSize && uiSize < INT_MAX, FALSE);

    INT iRes = etError;

    iRes = setvbuf(pGet(), pszBuff, cbmMode, uiSize);
    /*DEBUG*/xASSERT_RET(0 == iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bSetMode (Sets the file translation mode)
#if defined(xOS_WIN)
BOOL
CxStdioFile::bSetMode(ETranslationMode ctmMode) const {
    INT iRes = etError;

    #if defined(xCOMPILER_MINGW32) || defined(xCOMPILER_MS)
        iRes = setmode(_iGetHandle(), ctmMode);
        /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
    #elif defined(xCOMPILER_CODEGEAR)
        iRes = _setmode(_iGetHandle(), ctmMode);
        /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
    #endif

    return TRUE;
}
#elif defined(xOS_LINUX)
    //TODO: bSetMode
#endif
//---------------------------------------------------------------------------
//DONE: liGetSize (get file size)
//NOTE: https://www.securecoding.cert.org/confluence/display/seccode/FIO19-C.+Do+not+use+fseek()+and+ftell()+to+compute+the+size+of+a+file
LONG
CxStdioFile::liGetSize() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    LONG liStreamSize    = ppError;
    LONG liCurrStreamPos = ppError;

    //Get current position
    liCurrStreamPos = liGetPosition();

    //seek to the end of file
    xCHECK_RET(FALSE == bSetPosition(0, ppEnd), ppError);

    liStreamSize = liGetPosition();

    //Get back to the stored position
    xCHECK_RET(FALSE == bSetPosition(liCurrStreamPos, ppBegin), ppError);

    return liStreamSize;
}
//---------------------------------------------------------------------------
//DONE: bResize(changes the file size)
BOOL
CxStdioFile::bResize(const LONG cliSize) const {
    /*DEBUG*/// n/a

    INT iRes = etError;

#if defined(xOS_WIN)
    #if defined(xCOMPILER_MINGW32) || defined(xCOMPILER_MS)
        iRes = chsize(_iGetHandle(), cliSize);
        /*DEBUG*/xASSERT_RET(iRes != etError, FALSE);
    #elif defined(xCOMPILER_CODEGEAR)
        iRes = _chsize(_iGetHandle(), cliSize);
        /*DEBUG*/xASSERT_RET(iRes != etError, FALSE);
    #endif
#elif defined(xOS_LINUX)
    iRes = ftruncate(_iGetHandle(), static_cast<off_t>( cliSize ));
    /*DEBUG*/xASSERT_RET(iRes != etError, FALSE);
#endif

    /*DEBUG*/xASSERT_RET(cliSize == liGetSize(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------

/****************************************************************************
*    public: error handling
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bIsEof (check end of file indicator)
BOOL
CxStdioFile::bIsEof() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    _m_bRes = static_cast<BOOL>( feof(pGet()) );
    /*DEBUG*/// n/a

    return _m_bRes;
}
//---------------------------------------------------------------------------
//DONE: bIsError (check error indicator)
BOOL
CxStdioFile::bIsError() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    _m_bRes = static_cast<BOOL>( ferror(pGet()) );
    /*DEBUG*/// n/a

    return _m_bRes;
}
//---------------------------------------------------------------------------
//DONE: bErrorClear (clear error indicators)
BOOL
CxStdioFile::bErrorClear() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    clearerr(pGet());
    /*DEBUG*/// n/a

    return TRUE;
}
//---------------------------------------------------------------------------

/****************************************************************************
*    public: closing
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bFlush (flush)
BOOL
CxStdioFile::bFlush() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    INT iRes = etError;

    iRes = fflush(pGet());
    /*DEBUG*/xASSERT_RET(0 == iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClose (close)
BOOL
CxStdioFile::bClose() {
    /*DEBUG*/// _m_pFile - n/a

    if (FALSE != bIsValid()) {
        INT iRes = etError;

        iRes = fclose(pGet());
        /*DEBUG*/xASSERT_RET(0 == iRes, FALSE);
    }

    _m_pFile = NULL;

    return TRUE;
}
//---------------------------------------------------------------------------

/****************************************************************************
*    public, static
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bIsFile (check for file)
/*static*/
BOOL
CxStdioFile::bIsFile(const tString &csFilePath) {
    /*DEBUG*/// csFilePath - n/a

    BOOL bRes = FALSE;

#if defined(xOS_WIN)
    //TODO: bIsFile
    ////bRes = CxFileAttribute::bIsExists(csFilePath, /*! CxFileAttribute::faDirectory*/);
    ////xCHECK_RET(FALSE == bRes, FALSE);

    DWORD dwAttr = ::GetFileAttributes(csFilePath.c_str());

    bRes = (dwAttr != INVALID_FILE_ATTRIBUTES) &&
           !(dwAttr & (FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_DEVICE | FILE_ATTRIBUTE_OFFLINE | FILE_ATTRIBUTE_REPARSE_POINT));
    xCHECK_RET(FALSE == bRes, FALSE);
#elif defined(xOS_LINUX)
    struct stat stInfo = {0};

    INT iRes = stat/*lstat*/(csFilePath.c_str(), &stInfo);
    xCHECK_RET(- 1 == iRes, FALSE);

    bRes = static_cast<BOOL>( S_ISREG(stInfo.st_mode) );
    xCHECK_RET(FALSE == bRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bIsExists (check for existence)
/*static*/
BOOL
CxStdioFile::bIsExists(const tString &csFilePath) {
    /*DEBUG*/// csFilePath - n/a
    xCHECK_RET(FALSE == bIsFile(csFilePath), FALSE);

    INT iRes       = etError;
    INT iLastError = 0;

    iRes       = _taccess(csFilePath.c_str(), amExistence);
    iLastError = errno;
    xCHECK_RET((etError == iRes) && (ENOENT == iLastError), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bAccess (determine file-access permission)
/*static*/
BOOL
CxStdioFile::bAccess(const tString &csFilePath, const EAccessMode camMode) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*///iMode

    INT iRes = etError;

    iRes = _taccess(csFilePath.c_str(), camMode);
    /*DEBUG*/xASSERT_RET(iRes != etError, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bChmod (change the file-permission settings)
/*static*/
BOOL
CxStdioFile::bChmod(const tString &csFilePath, const EPermissionMode cpmMode) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*///iMode

    INT iRes = etError;

#if defined(xOS_WIN)
    iRes = _tchmod(csFilePath.c_str(), cpmMode);
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
#elif defined(xOS_LINUX)
    iRes = chmod(csFilePath.c_str(), static_cast<mode_t>(cpmMode));
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bDelete (deleting)
/*static*/
BOOL
CxStdioFile::bDelete(const tString &csFilePath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    BOOL bRes = FALSE;
    INT  iRes = etError;

    bRes = bChmod(csFilePath, pmWrite);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    iRes = _tremove(csFilePath.c_str());
    /*DEBUG*/xASSERT_RET(0 == iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bWipe (wipe)
/*static*/
BOOL
CxStdioFile::bWipe(const tString &csFilePath, const size_t cuiPasses) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cuiPasses - n/a

    BOOL bRes = FALSE;

    {
        CxStdioFile sfFile;
        LONG        liSize = 0;

        //--------------------------------------------------
        //TODO: remove all file attributes


        //--------------------------------------------------
        //open
        bRes = sfFile.bOpen(csFilePath, CxStdioFile::omBinWrite);
        xASSERT(FALSE != bRes);

        liSize = sfFile.liGetSize();
        if (0L < liSize) {
            //--------------------------------------------------
            //fill by 0x55, 0xAA, random char
            for (size_t i = 0; i < cuiPasses; ++ i) {
                xRANDOMIZE();

                const UCHAR chRand  = static_cast<UCHAR>(xRANDOM(255) + 1);
                const UCHAR chChar1 = 0x55;
                const UCHAR chChar2 = 0xAA;

                //chRand
                {
                    bRes = sfFile.bSetPosition(0, ppBegin);
                    xASSERT(FALSE != bRes);

                    for (LONG i = 0; i < liSize; ++ i) {
                        size_t uiRes = fwrite(&chRand, 1, sizeof(chRand), sfFile.pGet());
                        /*DEBUG*/xASSERT_RET(sizeof(chRand) == uiRes, FALSE);
                    }
                }

                //chChar1
                {
                    bRes = sfFile.bSetPosition(0, ppBegin);
                    xASSERT(FALSE != bRes);

                    for (LONG i = 0; i < liSize; ++ i) {
                        size_t uiRes = fwrite(&chChar1, 1, sizeof(chChar1), sfFile.pGet());
                        /*DEBUG*/xASSERT_RET(sizeof(chChar1) == uiRes, FALSE);
                    }
                }

                //chChar2
                {
                    bRes = sfFile.bSetPosition(0, ppBegin);
                    xASSERT(FALSE != bRes);

                    for (LONG i = 0; i < liSize; ++ i) {
                        size_t uiRes = fwrite(&chChar2, 1, sizeof(chChar2), sfFile.pGet());
                        /*DEBUG*/xASSERT_RET(sizeof(chChar2) == uiRes, FALSE);
                    }
                }
            }

            //--------------------------------------------------
            //truncate
            bRes = sfFile.bFlush();
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

            bRes = sfFile.bResize(0L);
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
        }

        //--------------------------------------------------
        //TODO: random filetime
    }

    //--------------------------------------------------
    //random file name
    tString sRndFileName;
    tString sRndFilePath;

    sRndFileName = CxString::lexical_cast( CxDateTime().dtGetCurrent().ullToMilliseconds() );
    std::random_shuffle(sRndFileName.begin(), sRndFileName.end());

    sRndFilePath = CxPath::sGetDir(csFilePath) + CxConst::xSLASH + sRndFileName;

    bRes = bRename(csFilePath, sRndFilePath);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //--------------------------------------------------
    //delete
    bRes = bDelete(sRndFilePath);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bUnlink (deleting)
/*static*/
BOOL
CxStdioFile::bUnlink(const tString &csFilePath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    INT iRes = etError;

    iRes = _tunlink(csFilePath.c_str());
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);

    return FALSE;
}
//---------------------------------------------------------------------------
//DONE: bRename (renaming)
/*static*/
BOOL
CxStdioFile::bRename(const tString &csOldFilePath, const tString &csNewFilePath) {
    /*DEBUG*/xASSERT_RET(false == csOldFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csNewFilePath.empty(), FALSE);

    INT iRes = etError;

    iRes = _trename(csOldFilePath.c_str(), csNewFilePath.c_str());
    /*DEBUG*/xASSERT_RET(0 == iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bMove (move)
/*static*/
BOOL
CxStdioFile::bMove(const tString &csFilePath, const tString &csDirPath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(),  FALSE);

    BOOL bRes = FALSE;

    bRes = bRename(csFilePath, csDirPath + CxConst::xSLASH + CxPath::sGetFullName(csFilePath));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bCopy (copy)
/*static*/
BOOL
CxStdioFile::bCopy(const tString &csFilePathFrom, const tString &csFilePathTo, BOOL bFailIfExists) {
    /*DEBUG*/xASSERT_RET(false == csFilePathFrom.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csFilePathTo.empty(),   FALSE);

    BOOL bRes      = FALSE;
    BOOL bIsCopyOk = TRUE;

    //--------------------------------------------------
    //fail if exists
    xCHECK_RET(TRUE == bFailIfExists && TRUE == CxStdioFile::bIsExists(csFilePathTo), FALSE);

    {
        //--------------------------------------------------
        //open files
        CxStdioFile sfFrom;

        bRes = sfFrom.bOpen(csFilePathFrom, omBinRead);
        xCHECK_RET(FALSE == bRes, FALSE);

        CxStdioFile sfTo;

        bRes = sfTo.bOpen(csFilePathTo, omBinWrite);
        xCHECK_RET(FALSE == bRes, FALSE);

        //--------------------------------------------------
        //copy files
        const size_t cuiBuffSize         = 1024;
        UCHAR        ucBuff[cuiBuffSize] = {0};

        for ( ; ; ) {
            const size_t uiReaded  = sfFrom.uiRead(ucBuff, cuiBuffSize);
            xCHECK_DO(0 >= uiReaded, break);

            const size_t uiWritten = sfTo.uiWrite(ucBuff, uiReaded);
            xCHECK_DO(uiReaded != uiWritten, bIsCopyOk = FALSE; break);
        }
    }

    //--------------------------------------------------
    //if copy fail - delete out file
    xCHECK_DO(bIsCopyOk == FALSE, CxStdioFile::bDelete(csFilePathTo); return FALSE);

    //--------------------------------------------------
    //test for size, maybe CRC
    xCHECK_DO(CxStdioFile::liGetSize(csFilePathFrom) != CxStdioFile::liGetSize(csFilePathTo), CxStdioFile::bDelete(csFilePathTo); return FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sCreateTemp (create temporary file)
/*static*/
tString
CxStdioFile::sCreateTemp(const tString &csFilePath, const tString &csDirPath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(),  tString());

    tString sRes;
    BOOL    bRes = FALSE;

    bRes = CxDir::bCreateForce(csDirPath);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, tString());

#if defined(xOS_WIN)
    TCHAR  szRes[L_tmpnam] = {0};
    TCHAR *pszRes          = NULL;

    pszRes = _ttmpnam(szRes);
    /*DEBUG*/xASSERT_RET(NULL != pszRes, tString());

    sRes.assign(szRes);
#elif defined(xOS_LINUX)
    const tString csTemplate = xT("XXXXXX");

    sRes = CxPath::sSlashAppend(csDirPath) + CxPath::sGetFullName(csFilePath) + csTemplate;

    INT iFile = - 1;

    iFile = _tmkstemp(&sRes.at(0));
    /*DEBUG*/xASSERT_RET(- 1 != iFile, tString());
#endif

    return sRes;
}
//--------------------------------------------------------------------------
//DONE: liGetSize (size)
/*static*/
LONG
CxStdioFile::liGetSize(const tString &csFilePath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    - 1L);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), - 1L);

    LONG        liRes = 0L;
    BOOL        bRes  = FALSE;
    CxStdioFile sfFile;

    bRes = sfFile.bOpen(csFilePath, omRead);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, - 1L);

    liRes = sfFile.liGetSize();
    /*DEBUG*/xASSERT_RET(0 <= liRes, - 1L);

    return liRes;
}
//---------------------------------------------------------------------------
//DONE: ullGetLines (get number of lines)
/*static*/
ULONGLONG
CxStdioFile::ullGetLines(const tString &csFilePath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    0LL);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), 0LL);

    ULONGLONG ullRes = 0LL;
    TCHAR     cChar;
    tifstream ifsStream(csFilePath.c_str(), std::ios::in);

    xCHECK_RET(!ifsStream || ifsStream.fail() || !ifsStream.good() || !ifsStream.is_open() || ifsStream.eof(), 0LL);

    for (ullRes = 0LL; ifsStream.get(cChar); ) {
        xCHECK_DO(xT('\n') == cChar, ++ ullRes);
    }

    return ullRes;
}
//--------------------------------------------------------------------------
//TODO: - bTextRead ()
/*static*/
BOOL
CxStdioFile::bTextRead(const tString &csFilePath, tString *psStr) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != psStr,              FALSE);

    tifstream ifsStream(csFilePath.c_str());
    /*DEBUG*/xASSERT_RET(ifsStream,           FALSE);
    /*DEBUG*/xASSERT_RET(!ifsStream.fail(),   FALSE);
    /*DEBUG*/xASSERT_RET(ifsStream.good(),    FALSE);
    /*DEBUG*/xASSERT_RET(ifsStream.is_open(), FALSE);
    /*DEBUG*/xASSERT_RET(!ifsStream.eof(),    FALSE);

    tString sLine;

    (*psStr).clear();
    for (; !ifsStream.eof(); ) {
        std::getline(ifsStream, sLine);
        (*psStr).append(sLine);
        (*psStr).append(CxConst::xEOL);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bTextWrite ()
/*static*/
BOOL
CxStdioFile::bTextWrite(const tString &csFilePath, const tString &csStr) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// csStr - n/a

    BOOL        bRes = FALSE;
    CxStdioFile sfFile;
    size_t      uiWriteLen = - 1;

    bRes = sfFile.bOpen(csFilePath, CxStdioFile::omWrite);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    uiWriteLen = sfFile.uiWrite((LPVOID)&csStr.at(0), csStr.size());
    /*DEBUG*/xASSERT_RET(csStr.size() == uiWriteLen, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bTextRead
/*static*/
BOOL
CxStdioFile::bTextRead(const tString &csFilePath, std::vector<tString> *pvecsContent) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pvecsContent,          FALSE);

    tifstream ifsStream(csFilePath.c_str());
    /*DEBUG*/xASSERT_RET(ifsStream,           FALSE);
    /*DEBUG*/xASSERT_RET(!ifsStream.fail(),   FALSE);
    /*DEBUG*/xASSERT_RET(ifsStream.good(),    FALSE);
    /*DEBUG*/xASSERT_RET(ifsStream.is_open(), FALSE);
    /*DEBUG*/xASSERT_RET(!ifsStream.eof(),    FALSE);

    tString sLine;

    (*pvecsContent).clear();
    for (size_t i = 0; !ifsStream.eof();  ++ i) {
        std::getline(ifsStream, sLine);
        (*pvecsContent).push_back(sLine);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bTextWrite (write std::vector in file)
/*static*/
BOOL
CxStdioFile::bTextWrite(const tString &csFilePath, const std::vector<tString> &cvecsContent) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cvecsFileContent - n/a

    BOOL bRes = FALSE;

    CxStdioFile stdFile;

    bRes = stdFile.bOpen(csFilePath, CxStdioFile::omBinWrite);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    std::vector<tString>::const_iterator it;
    for (it = cvecsContent.begin(); it < cvecsContent.end(); ++ it) {
        bRes = stdFile.bWriteLine(*it);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    return TRUE;
}
//--------------------------------------------------------------------------
//TODO: bTextRead (Name1=Value1\r\r\nName2=Value2\r\n...)
/*static*/
BOOL
CxStdioFile::bTextRead(const tString &csFilePath, const tString &csDelimiter, std::map<tString, tString> *pmapsFile) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pmapsFile,             FALSE);

    BOOL bRes = FALSE;

    tifstream ifsStream(csFilePath.c_str());
    /*DEBUG*/xASSERT_RET(ifsStream,           FALSE);
    /*DEBUG*/xASSERT_RET(!ifsStream.fail(),   FALSE);
    /*DEBUG*/xASSERT_RET(ifsStream.good(),    FALSE);
    /*DEBUG*/xASSERT_RET(ifsStream.is_open(), FALSE);
    /*DEBUG*/xASSERT_RET(!ifsStream.eof(),    FALSE);

    tString              sStr;
    std::vector<tString> vecsLine;

    (*pmapsFile).clear();
    for (size_t i = 0; !ifsStream.eof();  ++ i) {
        std::getline(ifsStream, sStr);

        bRes = CxString::bSplit(sStr, csDelimiter, &vecsLine);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        (*pmapsFile).insert( std::pair<tString, tString>(vecsLine.at(0), vecsLine.at(1)) );
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bBinRead (read binary data)
/*static*/
BOOL
CxStdioFile::bBinRead(const tString &csFilePath, uString *pusStr) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pusStr,             FALSE);

    BOOL        bRes       = FALSE;
    CxStdioFile sfFile;
    LONG        liFileSize = - 1;
    size_t      uiReadLen  = 0;

    (*pusStr).clear();

    bRes = sfFile.bOpen(csFilePath, omBinRead);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    liFileSize = sfFile.liGetSize();
    /*DEBUG*/xASSERT_RET(- 1 < liFileSize, FALSE);

    (*pusStr).resize(liFileSize);
    xCHECK_RET(0 == liFileSize, TRUE);

    uiReadLen = sfFile.uiRead(&(*pusStr).at(0), (*pusStr).size());
    /*DEBUG*/xASSERT_RET(static_cast<size_t>( liFileSize ) == uiReadLen, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bBinWrite (write binary data)
/*static*/
BOOL
CxStdioFile::bBinWrite(const tString &csFilePath, const uString &cusStr) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cusStr - n/a

    BOOL        bRes       = FALSE;
    CxStdioFile sfFile;
    size_t      uiWriteLen = 0;

    bRes = sfFile.bOpen(csFilePath, omBinWrite);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    uiWriteLen = sfFile.uiWrite((LPVOID)&cusStr.at(0), cusStr.size());
    /*DEBUG*/xASSERT_RET(cusStr.size() == uiWriteLen, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _iGetHandle (Gets the file descriptor associated with a stream)
INT
CxStdioFile::_iGetHandle() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), etError);

    INT iRes = etError;

    iRes = fileno/*_fileno*/(pGet());
    /*DEBUG*/xASSERT_RET(etError != iRes, etError);

    return iRes;
}
//---------------------------------------------------------------------------
//DONE: _sGetOpenMode (get open mode as string, by default use "r")
/*static*/
tString
CxStdioFile::_sGetOpenMode(const EOpenMode omMode) {
    /*DEBUG*/

    tString sRes;

    switch (omMode) {
        case omRead:                { sRes.assign( xT("r")   ); }   break;
        case omWrite:               { sRes.assign( xT("w")   ); }   break;
        case omAppend:              { sRes.assign( xT("a")   ); }   break;
        case omOpenReadWrite:       { sRes.assign( xT("r+")  ); }   break;
        case omCreateReadWrite:     { sRes.assign( xT("w+")  ); }   break;
        case omOpenReadAppend:      { sRes.assign( xT("a+")  ); }   break;

        case omBinRead:             { sRes.assign( xT("rb")  ); }   break;
        case omBinWrite:            { sRes.assign( xT("wb")  ); }   break;
        case omBinAppend:           { sRes.assign( xT("ab")  ); }   break;
        case omBinOpenReadWrite:    { sRes.assign( xT("rb+") ); }   break;
        case omBinCreateReadWrite:  { sRes.assign( xT("wb+") ); }   break;
        case omBinOpenReadAppend:   { sRes.assign( xT("ab+") ); }   break;

        default:                    { sRes.assign( xT("r")   ); }	break;
    }

    return sRes;
}
//---------------------------------------------------------------------------



/*
ofstream fout;
fout.open("D:\\vec.txt");
copy(vec.begin(), vec.end(), ostream_iterator<int>(fout," "));
fout.close();
*/

/*
int main(int argc, char* argv[])
{
if (argc < 2) { help(argv[0]); return 1; }
std::vector<std::string> file;
std::string line;
file.clear();
std::ifstream infile (argv[1], std::ios_base::in);
while (getline(infile, line, '\n'))
{
file.push_back (line);
}

std::cout << "Read " << file.size() << " lines.\n";

return 0;
}
*/
