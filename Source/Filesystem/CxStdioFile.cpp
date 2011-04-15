/****************************************************************************
* Class name:  CxStdioFile
* Description: file
* File name:   CxStdioFile.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     21.05.2009 17:46:38
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Filesystem/CxStdioFile.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>

#if defined(xOS_WIN)
    #include <xLib/Common/CxLocale.h>
#endif


/****************************************************************************
*	public: static
*
*****************************************************************************/

const tString CxStdioFile::CxOpenMode::omRead               = xT("r");
const tString CxStdioFile::CxOpenMode::omWrite              = xT("w");
const tString CxStdioFile::CxOpenMode::omAppend             = xT("a");
const tString CxStdioFile::CxOpenMode::omOpenReadWrite      = xT("r+");
const tString CxStdioFile::CxOpenMode::omCreateReadWrite    = xT("w+");
const tString CxStdioFile::CxOpenMode::omOpenReadAppend	    = xT("a+");

const tString CxStdioFile::CxOpenMode::omBinRead            = xT("rb");
const tString CxStdioFile::CxOpenMode::omBinWrite           = xT("wb");
const tString CxStdioFile::CxOpenMode::omBinAppend          = xT("ab");
const tString CxStdioFile::CxOpenMode::omBinOpenReadWrite   = xT("rb+");
const tString CxStdioFile::CxOpenMode::omBinCreateReadWrite = xT("wb+");
const tString CxStdioFile::CxOpenMode::omBinOpenReadAppend  = xT("ab+");


/****************************************************************************
*	public: constructors, destructor
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
	xCHECK_DO(NULL == _m_pFile, return);

	_m_bRes = bClose();
	/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public: open, get
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: bOpen (open)
BOOL
CxStdioFile::bOpen(FILE *pflFile) {
    /*DEBUG*/xASSERT_RET(NULL  == _m_pFile, FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pflFile,  FALSE);

    _m_pFile = pflFile;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bOpen (open)
BOOL
CxStdioFile::bOpen(const tString &csFilePath, const tString &omMode) {
	/*DEBUG*/xASSERT_RET(NULL  == _m_pFile,                         FALSE);
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(),               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != CxPath::bIsValidName(csFilePath), FALSE);
	/*DEBUG*/xASSERT_RET(false == omMode.empty(),                   FALSE);

	_m_pFile = _tfopen(csFilePath.c_str(), omMode.c_str());
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

	_m_sFilePath = csFilePath;

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bReopen (reopen with different file or mode)
BOOL
CxStdioFile::bReopen(const tString &csFilePath, const tString &csMode) {
	/*DEBUG*/xASSERT_RET(NULL  != _m_pFile,                         FALSE);
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(),               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != CxPath::bIsValidName(csFilePath), FALSE);
	/*DEBUG*/xASSERT_RET(false == csMode.empty(),                   FALSE);

	_m_pFile = _tfreopen(csFilePath.c_str(), csMode.c_str(), _m_pFile);
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

	_m_sFilePath = csFilePath;

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: pGet (get handle)
FILE *
CxStdioFile::pGet() const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile, NULL);

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
std::size_t
CxStdioFile::uiRead(LPVOID pvBuff, std::size_t uiCount) const {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, 0);
	/*DEBUG*/xASSERT_RET(NULL != pvBuff,   0);

	std::size_t uiRes = 0;

	uiRes = fread(pvBuff, 1, uiCount, _m_pFile);
	/*DEBUG*/xASSERT_RET(uiCount >= uiRes, 0);

	return uiRes;
}
//---------------------------------------------------------------------------
//DONE: uiWrite (write block of data)
std::size_t
CxStdioFile::uiWrite(const LPVOID pcvBuf, std::size_t uiCount) const {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, 0);
	/*DEBUG*/xASSERT_RET(NULL != pcvBuf,   0);

	std::size_t uiRes = 0;

	uiRes = fwrite(pcvBuf, 1, uiCount, _m_pFile);
	/*DEBUG*/xASSERT_RET(uiCount == uiRes, 0);

	return uiRes;
}
//---------------------------------------------------------------------------
//TODO: bReadAll (read block of data)
BOOL
CxStdioFile::bReadAll(LPVOID pvBuff, std::size_t uiBuffSize, std::size_t uiBlockSize) const {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile,    FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pvBuff,      FALSE);
	/*DEBUG*/xASSERT_RET(0    != uiBlockSize, FALSE);


	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bWriteAll (write block of data)
BOOL
CxStdioFile::bWriteAll(const LPVOID pcvBuf, std::size_t uiBuffSize, std::size_t uiBlockSize) const {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile,    FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pcvBuf,      FALSE);
	/*DEBUG*/xASSERT_RET(0    != uiBlockSize, FALSE);


	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bReadAll (read all file by blocks)
BOOL
CxStdioFile::bReadAll(uString *psBuff, std::size_t uiBlockSize) const {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile,    FALSE);
	/*DEBUG*/xASSERT_RET(NULL != psBuff,      FALSE);
	/*DEBUG*/xASSERT_RET(0    <  uiBlockSize, FALSE);

	std::size_t uiRes      = 0;
	LONG        liFileSize = 0;

	liFileSize = liGetSize();
	/*DEBUG*/xASSERT_RET(ppError != liFileSize, FALSE);

	(*psBuff).clear();
	(*psBuff).resize(liFileSize);

	for (LONG i = 0; i < liFileSize; i += uiBlockSize) {
		uiRes = fread(&(*psBuff).at(0) + i, sizeof(UCHAR), uiBlockSize, _m_pFile);
		/*DEBUG*/xASSERT_RET(uiBlockSize >= uiRes, FALSE);
    }

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWriteAll (write all string by blocks)
BOOL
CxStdioFile::bWriteAll(const uString &csBuff, std::size_t uiBlockSize) const {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile,    FALSE);
	/*DEBUG*///csBuff - n/a
	/*DEBUG*/xASSERT_RET(0    <  uiBlockSize, FALSE);

	std::size_t uiRes = 0;

	for (std::size_t i = 0; i < csBuff.size(); i += uiBlockSize) {
		if (uiBlockSize > (csBuff.size() - i)) {
			uiBlockSize = csBuff.size() - i;
		}

		uiRes = fwrite(&csBuff.at(0) + i, sizeof(UCHAR), uiBlockSize, _m_pFile);
		/*DEBUG*/xASSERT_RET(uiBlockSize == uiRes, FALSE);
    }

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bReadAll (read all file by blocks)
BOOL
CxStdioFile::bReadAll(tString *psBuff, std::size_t uiBlockSize) const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != psBuff,      FALSE);
    /*DEBUG*/xASSERT_RET(0    <  uiBlockSize, FALSE);

    std::size_t uiRes      = 0;
    LONG        liFileSize = 0;

    liFileSize = liGetSize();
    /*DEBUG*/xASSERT_RET(ppError != liFileSize, FALSE);
    /*DEBUG*/xASSERT_RET(NULL != psBuff,      FALSE);
    /*DEBUG*/xASSERT_RET(0 < psBuff->size(),      FALSE);

    (*psBuff).clear();
    (*psBuff).resize(liFileSize);

    for (LONG i = 0; i < liFileSize; i += uiBlockSize) {
        uiRes = fread(&(*psBuff).at(0) + i, sizeof(CHAR), uiBlockSize, _m_pFile);
        /*DEBUG*/xASSERT_RET(uiBlockSize >= uiRes, FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWriteAll (write all string by blocks)
BOOL
CxStdioFile::bWriteAll(const tString &csBuff, std::size_t uiBlockSize) const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile,    FALSE);
    /*DEBUG*///csBuff - n/a
    /*DEBUG*/xASSERT_RET(0    <  uiBlockSize, FALSE);

    std::size_t uiRes = 0;

    for (std::size_t i = 0; i < csBuff.size(); i += uiBlockSize) {
        if (uiBlockSize > (csBuff.size() - i)) {
            uiBlockSize = csBuff.size() - i;
        }

        uiRes = fwrite(&csBuff.at(0) + i, sizeof(CHAR), uiBlockSize, _m_pFile);
        /*DEBUG*/xASSERT_RET(uiBlockSize == uiRes, FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bReadLine (read string to newline or to the end of file)
BOOL
CxStdioFile::bReadLine(LPTSTR pszStr, std::size_t uiMaxCount) const {		//TODO: overflow
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pszStr,   FALSE);

    LPTSTR pszRes = NULL;

    pszRes = _fgetts(pszStr, uiMaxCount, _m_pFile);
    /*DEBUG*/xASSERT_RET(NULL != pszRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWriteLine (writes string and '\n')
BOOL
CxStdioFile::bWriteLine(const tString &csStr) const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

    tString sLine;

    sLine.assign(csStr);
    sLine.append(CxConst::xEOL);

    std::size_t uiRes  = uiWrite(&sLine.at(0), sLine.size());
    /*DEBUG*/xASSERT_RET(uiRes == sLine.size(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWriteString (write string)
BOOL
CxStdioFile::bWriteString(const tString &csStr) const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

    INT iRes = etError;

    iRes = _fputts(csStr.c_str(), _m_pFile);
    /*DEBUG*/xASSERT_RET(iRes != etError, FALSE);
    /*DEBUG*/xASSERT_RET(EOF < iRes,      FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: cReadChar (get character)
TCHAR
CxStdioFile::cReadChar() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

    INT iRes = etError;

    iRes = _gettc(_m_pFile);
    /*DEBUG*/// n/a xASSERT_RET(iRes != etError, (TCHAR)etError);
    /*DEBUG*/// n/a xASSERT_RET(EOF < iRes,      (TCHAR)etError);

    return static_cast<TCHAR>(iRes);
}
//---------------------------------------------------------------------------
//TODO: bWriteChar (write character)
BOOL
CxStdioFile::bWriteChar(TCHAR cChar) {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

	INT iRes = etError;

	iRes = _fputtc(static_cast<INT>(cChar), _m_pFile);
	/*DEBUG*/xASSERT_RET(static_cast<INT>(cChar) != etError, FALSE);
	/*DEBUG*/xASSERT_RET(static_cast<INT>(cChar) == iRes,    FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bUngetChar (Unget character from stream)
BOOL
CxStdioFile::bUngetChar(TCHAR cChar) {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

	INT iRes = etError;

	iRes = _ungettc(cChar, _m_pFile);
	/*DEBUG*/xASSERT_RET(iRes  != etError,                  FALSE);
	/*DEBUG*/xASSERT_RET(cChar == static_cast<TCHAR>(iRes), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*   public: Formatted input/output
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: iFprintf(Write formatted output to stream)
INT
CxStdioFile::iFprintf(LPCTSTR pcszFormat, ...) const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile,   etError);
    /*DEBUG*/xASSERT_RET(NULL != pcszFormat, etError);

    INT iRes = etError;

    va_list args = NULL;
    va_start(args, pcszFormat);

    iRes = _vftprintf(_m_pFile, pcszFormat, args);
    /*DEBUG*/xASSERT_RET(etError < iRes, etError);

    va_end(args);

    return iRes;
}
//---------------------------------------------------------------------------
//DONE: iFprintfV (Write formatted variable argument list to stream)
INT
CxStdioFile::iFprintfV(LPCTSTR pcszFormat, va_list arg) const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile,   etError);
    /*DEBUG*/xASSERT_RET(NULL != pcszFormat, etError);
    /*DEBUG*/xASSERT_RET(NULL != arg,        etError);

    INT iRes = etError;

    iRes = _vftprintf(_m_pFile, pcszFormat, arg);
    /*DEBUG*/xASSERT_RET(etError < iRes, etError);

    return iRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public: ...
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bSetVBuff (Change stream buffering)
BOOL
CxStdioFile::bSetVBuff(LPSTR pszBuff, EBufferingMode bmMode, std::size_t uiSize) {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile,               FALSE);
    /*DEBUG*/// pszBuff - n/a
    /////*DEBUG*/xASSERT_RET(2 < uiSize && uiSize < INT_MAX, FALSE);

    INT iRes = etError;

	iRes = setvbuf(_m_pFile, pszBuff, bmMode, uiSize);
	/*DEBUG*/xASSERT_RET(0 == iRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bSetMode (Sets the file translation mode)
//////BOOL
//CxStdioFile::bSetMode(ETranslationMode tmMode) {
//	INT iRes = etError;
//
//	iRes = /*BC++_setmode*/setmode(_iGetHandle(), tmMode);
//	/*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
//
//	return TRUE;
//////}
//---------------------------------------------------------------------------
//DONE: bSetPosition (REFilePosition stream position indicator)
BOOL
CxStdioFile::bSetPosition(LONG lOffset, EPointerPosition fpPos/* = fpBegin*/) const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

	INT iRet = ppError;

	iRet = fseek(_m_pFile, lOffset, fpPos);
	/*DEBUG*/xASSERT_RET(0 == iRet, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: liGetPosition (Get current position in stream)
LONG
CxStdioFile::liGetPosition() const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

	LONG liRes = ppError;

	liRes = ftell(_m_pFile);
	/*DEBUG*/xASSERT_RET(ppError != liRes, ppError);

	return liRes;
}
//---------------------------------------------------------------------------
//DONE: liGetSize (get file size)
//NOTE: https://www.securecoding.cert.org/confluence/display/seccode/FIO19-C.+Do+not+use+fseek()+and+ftell()+to+compute+the+size+of+a+file
LONG
CxStdioFile::liGetSize() const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

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
//TODO: bChsize(Changes the file size)
////BOOL
//CxStdioFile::bChsize(LONG liSize) {
//	/*DEBUG*/// n/a
//
//	INT iRes = etError;
//
//	iRes = /*BC++ _chsize*/chsize(_iGetHandle(), liSize);
//	/*DEBUG*/xASSERT_RET(iRes != etError, FALSE);
//
//	return TRUE;
////}
//---------------------------------------------------------------------------
//TODO: bLocking (Locks or unlocks bytes of a file)
////BOOL
//CxStdioFile::bLocking(ELockingMode lmMode, LONG liBytes) {
//	INT iRes = etError;
//
////	iRes = _locking(_iGetHandle(), lmMode, liBytes);           CG2010
////	/*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
//
//	return FALSE;
////}
//---------------------------------------------------------------------------


/****************************************************************************
*	closing
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bFlush (flush)
BOOL
CxStdioFile::bFlush() const {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

	INT iRes = etError;

	iRes = fflush(_m_pFile);
	/*DEBUG*/xASSERT_RET(0 == iRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClose (close)
BOOL
CxStdioFile::bClose() {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

	INT iRes = etError;

	iRes = fclose(_m_pFile);
	/*DEBUG*/xASSERT_RET(0 == iRes, FALSE);

	_m_pFile = NULL;

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public, static
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bIsFile (check for file)
/*static*/
BOOL
CxStdioFile::bIsFile(const tString &csFilePath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    BOOL bRes = FALSE;

#if defined(xOS_WIN)
    //TODO: xOS_WIN
    ////bRes = CxFileAttribute::bIsExists(csFilePath, /*! CxFileAttribute::faDirectory*/);
    ////xCHECK_RET(FALSE == bRes, FALSE);

    DWORD dw = ::GetFileAttributes(csFilePath.c_str());
    return dw != INVALID_FILE_ATTRIBUTES && !(dw & (FILE_ATTRIBUTE_DIRECTORY |
                                                    FILE_ATTRIBUTE_DEVICE |
                                                    FILE_ATTRIBUTE_OFFLINE |
                                                    FILE_ATTRIBUTE_REPARSE_POINT));
#elif defined(xOS_LINUX)
    struct stat stInfo = {0};

    INT iRes = stat/*lstat*/(csFilePath.c_str(), &stInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);

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
CxStdioFile::bAccess(const tString &csFilePath, EAccessMode amMode) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
	/*DEBUG*///iMode

	INT iRes = etError;

	iRes = _taccess(csFilePath.c_str(), amMode);
	/*DEBUG*/xASSERT_RET(iRes != etError, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bChmod (change the file-permission settings)
/*static*/
BOOL
CxStdioFile::bChmod(const tString &csFilePath, EPermissionMode pmMode) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
	/*DEBUG*///iMode

	INT iRes = etError;

#if defined(xOS_WIN)
    iRes = _tchmod(csFilePath.c_str(), pmMode);
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
#elif defined(xOS_LINUX)
    iRes = chmod(csFilePath.c_str(), static_cast<mode_t>(pmMode));
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

	INT iRes = etError;

	iRes = bChmod(csFilePath.c_str(), pmWrite);
	/*DEBUG*/xASSERT_RET(FALSE != iRes, FALSE);

	iRes = _tremove(csFilePath.c_str());
	/*DEBUG*/xASSERT_RET(0 == iRes, FALSE);

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
//TODO: bCopy (coping)
//TODO: - FilePath -> DirPath
/*static*/
BOOL
CxStdioFile::bCopy(const tString &csFromFilePath, const tString &csToFilePath) {
	/*DEBUG*/xASSERT_RET(false == csFromFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csToFilePath.empty(),   FALSE);

	BOOL        bRes     = FALSE;
	std::size_t uiReaded = 0;
	std::size_t uiWrited = 0;
	uString     sBuff;

	CxStdioFile stdfFile;

	//-------------------------------------
	//read from source
	bRes = stdfFile.bOpen(csFromFilePath.c_str(), CxOpenMode::omBinRead);
	xCHECK_RET(FALSE == bRes, FALSE);

	sBuff.resize(stdfFile.liGetSize());

	uiReaded = stdfFile.uiRead(&sBuff.at(0), sBuff.size());
	xCHECK_RET(sBuff.size() != uiReaded, FALSE);

	bRes = stdfFile.bClose();
	xCHECK_RET(FALSE == bRes, FALSE);

	//-------------------------------------
	//write to destination
	bRes = stdfFile.bOpen(csToFilePath.c_str(), CxOpenMode::omBinWrite);
	xCHECK_RET(FALSE == bRes, FALSE);

	uiWrited = stdfFile.uiWrite(&sBuff[0], sBuff.size());
	if (sBuff.size() != uiWrited) {
		//coping faile - delete out-file
		stdfFile.bClose();
		CxStdioFile::bDelete(csToFilePath);

		return FALSE;
	}

	return TRUE;
}
/*
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void pHelp(char *me) {
  fprintf(stdout, "Usage: %s <srcfile> <destfile>\n", me);
  exit(0);
}

int main(int argc, char *argv[]) {
  int inF, ouF;
  char line[512];
  int bytes;

  if(argc < 3)
    pHelp(argv[0]);

  if((inF = open(argv[1], O_RDONLY)) == -1) {
    perror("open");
    exit(-1);
  }

  if((ouF = open(argv[2], O_WRONLY | O_CREAT)) == -1) {
    perror("open");
    exit(-1);
  }

  while ((bytes = read(inF, line, sizeof(line))) > 0) {
    write(ouF, line, bytes);
  }

  close(inF);
  close(ouF);
}
*/


/*
#include <fstream>
#include <string>
#include <stdexcept>

void copy_file(const std::string& src, const std::string& dst) {
   std::ifstream in(src.c_str(), std::ios::binary);
   if ( !in ) {
      throw std::runtime_error("can`t open file: " + src);
   }
   std::ofstream out(dst.c_str(), std::ios::binary|std::ios::trunc);
   if ( !out ) {
      throw std::runtime_error("can`t create file: " + dst);
   }
   out << in.rdbuf();
}
*/


/*
int main(int argc, const char** argv)  {
   try {
      copy_file("infile.dat", "outfile.dat");
   } catch (const std::exception& e) {
      std::cout << e.what() << std::endl;
   }

   return 0;
}
*/
//---------------------------------------------------------------------------
//DONE: bMove (movement)
/*static*/
BOOL
CxStdioFile::bMove(const tString &csFilePath, const tString &csDirPath) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csDirPath.empty(),  FALSE);

	BOOL bRes = FALSE;

	tString sFileName = CxPath::sGetFullName(csFilePath);

	bRes = bRename(csFilePath, csDirPath + CxConst::xSLASH + sFileName);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sCreateTemp (create temporary file)
/*static*/
tString
CxStdioFile::sCreateTemp(const tString &csFilePath, const tString &csDirPath) {
    /*DEBUG*/

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
//---------------------------------------------------------------------------
//TODO: - ulLines (get number of lines)
/*static*/
ULONGLONG
CxStdioFile::ullLines(const tString &csFilePath) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    0);
	/*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), 0);

	ULONGLONG ullLines = 0;

	tifstream ifsStream(csFilePath.c_str(), std::ios::in);
	xCHECK_RET(!ifsStream || ifsStream.fail() || !ifsStream.good() || !ifsStream.is_open() || ifsStream.eof(), 0);

	TCHAR cChar = xT('\0');
	while (ifsStream.get(cChar)) {
		xCHECK_DO(xT('\n') == cChar, ++ ullLines);
	}
	++ ullLines;

	ifsStream.close();

	return ullLines;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public: Error-handling:
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bIsEof (check end of file indicator)
BOOL
CxStdioFile::bIsEof() const {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

	BOOL bRes = FALSE;

	bRes = static_cast<BOOL>( feof(_m_pFile) );
	/*DEBUG*/// n/a

    return bRes;
}
//---------------------------------------------------------------------------
//TODO: bIsError (check error indicator)
BOOL
CxStdioFile::bIsError() const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

    BOOL bRes = FALSE;

    bRes = static_cast<BOOL>( ferror(_m_pFile) );
    /*DEBUG*/// n/a

    return bRes;
}
//---------------------------------------------------------------------------
//DONE: bClearErr (clear error indicators)
BOOL
CxStdioFile::bClearErr() const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

    clearerr(_m_pFile);
    /*DEBUG*/// n/a

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public, static
*
*****************************************************************************/

//--------------------------------------------------------------------------
//TODO: - liGetSize
/*static*/
LONG
CxStdioFile::liGetSize(const tString &csFilePath) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    - 1);
	/*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), - 1);

	LONG        iRes = 0;
	BOOL        bRes = FALSE;
	CxStdioFile sfFile;

	bRes = sfFile.bOpen(csFilePath, CxOpenMode::omRead);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	iRes = sfFile.liGetSize();
	/*DEBUG*/xASSERT_RET(0 <= iRes, FALSE);

	return iRes;
}
//---------------------------------------------------------------------------
//DONE: bReadFile (read in std::vector)
/*static*/
BOOL
CxStdioFile::bReadFile(const tString &csFilePath, std::vector<tString> *pvecsVector) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pvecsVector,        FALSE);

    BOOL bRes = FALSE;
    INT  iRes = etError;

    CxStdioFile stdFile;

    bRes = stdFile.bOpen(csFilePath.c_str(), xT("rb"));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    tString sLine;

    pvecsVector->clear();
    for ( ;; ) {
        bRes = stdFile.bIsEof();
        xCHECK_DO(TRUE == bRes, break);

        iRes = static_cast<INT>(stdFile.cReadChar());
        if ((INT)etError == iRes) {
            //�������� ��������� ������ (� ��� ��� EOL)
            pvecsVector->push_back(sLine);
            sLine.clear();

            break;
        }

        sLine.append( 1, static_cast<TCHAR>(iRes) );
        if (CxConst::xNL.at(0) == static_cast<TCHAR>(iRes)) {
            pvecsVector->push_back( CxString::sTrimRightChars(sLine, CxConst::xEOL) );
            sLine.clear();
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWriteFile (write std::vector in file)
/*static*/
BOOL
CxStdioFile::bWriteFile(const tString &csFilePath, const std::vector<tString> *pcvecsVector) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pcvecsVector,       FALSE);

    BOOL bRes = FALSE;

    CxStdioFile stdFile;

    bRes = stdFile.bOpen(csFilePath.c_str(), xT("wb"));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    std::vector<tString>::const_iterator it;
    for (it = pcvecsVector->begin(); it < pcvecsVector->end(); it ++) {
        std::size_t uiRes   = 0;
        tString     sLine   = *it + CxConst::xEOL;
        std::size_t uiCount = sLine.size();

        uiRes = stdFile.uiWrite(static_cast<LPVOID>(&sLine.at(0)), uiCount);
        xCHECK_RET(uiCount != uiRes, FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bReadFileEx
/*static*/
BOOL
CxStdioFile::bReadFileEx(const tString &csFilePath, std::vector<tString> *pvecsFile) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    FALSE);
	/*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), FALSE);
	/*DEBUG*/xASSERT_RET(NULL  != pvecsFile,             FALSE);

	tifstream ifsStream(csFilePath.c_str());
	/*DEBUG*/xASSERT_RET(ifsStream,           FALSE);
	/*DEBUG*/xASSERT_RET(!ifsStream.fail(),   FALSE);
	/*DEBUG*/xASSERT_RET(ifsStream.good(),    FALSE);
	/*DEBUG*/xASSERT_RET(ifsStream.is_open(), FALSE);
	/*DEBUG*/xASSERT_RET(!ifsStream.eof(),    FALSE);
	tString sStr;

	(*pvecsFile).clear();
	for (size_t i = 0; !ifsStream.eof();  ++ i) {
		std::getline(ifsStream, sStr);
		(*pvecsFile).push_back(sStr);
	}

	return TRUE;
}
//--------------------------------------------------------------------------
//TODO: - bReadFile
/*static*/
BOOL
CxStdioFile::bReadFile(const tString &csFilePath, std::vector<TCHAR> *pvecchFile) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    FALSE);
	/*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), FALSE);
	/*DEBUG*/xASSERT_RET(NULL  != pvecchFile,            FALSE);

	tifstream ifsStream(csFilePath.c_str(), std::ios::in | std::ios::binary);
	/*DEBUG*/xASSERT_RET(ifsStream,           FALSE);
	/*DEBUG*/xASSERT_RET(!ifsStream.fail(),   FALSE);
	/*DEBUG*/xASSERT_RET(ifsStream.good(),    FALSE);
	/*DEBUG*/xASSERT_RET(ifsStream.is_open(), FALSE);
	/*DEBUG*/xASSERT_RET(!ifsStream.eof(),    FALSE);

	/*std::size_t*/std::size_t uiSize = 0;

	if (ifsStream.seekg(0, std::ios::end)) {
		uiSize = static_cast<std::size_t>(ifsStream.tellg());	//FIX_ME: ����
	}

	if (uiSize && ifsStream.seekg(0, std::ios::beg)) {
		(*pvecchFile).resize(uiSize);
		ifsStream.read(&(*pvecchFile)[0], uiSize);
	}

	return TRUE;
}
//--------------------------------------------------------------------------
//TODO: - bReadFile (���������� ����� Name1=Value1\r\r\nName2=Value2\r\n...)
/*static*/
BOOL
CxStdioFile::bReadFile(const tString &csFilePath, const tString &csDelimiter, std::map<tString, tString> *pmapsFile) {
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

		(*pmapsFile)[vecsLine.at(0)] = vecsLine.at(1);
	}

	return TRUE;
}
//--------------------------------------------------------------------------
//TODO: - bReadFile (Writes csStr and then writes '\n' to the file)
/*static*/
BOOL
CxStdioFile::bReadFile(const tString &csFilePath,  tString *psStr) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(NULL  != psStr,              FALSE);

	tifstream ifsStream(csFilePath.c_str());
	/*DEBUG*/xASSERT_RET(ifsStream,           FALSE);
	/*DEBUG*/xASSERT_RET(!ifsStream.fail(),   FALSE);
	/*DEBUG*/xASSERT_RET(ifsStream.good(),    FALSE);
	/*DEBUG*/xASSERT_RET(ifsStream.is_open(), FALSE);
	/*DEBUG*/xASSERT_RET(!ifsStream.eof(),    FALSE);

	tString sTemp;

	(*psStr).clear();
	for (; !ifsStream.eof(); ) {
		std::getline(ifsStream, sTemp);
		(*psStr).append(sTemp);
		(*psStr).append(CxConst::xEOL);
	}

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bReadFile ()
/*static*/
BOOL
CxStdioFile::bReadFile(const tString &csFilePath, uString *pusStr) {
	/*DEBUG*/

	BOOL        bRes       = FALSE;
	CxStdioFile sfFile;
	LONG        liFileSize = - 1;
	size_t      uiReadLen  = - 1;

	(*pusStr).clear();

	bRes = sfFile.bOpen(csFilePath, CxOpenMode::omBinRead);
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
//TODO: - bWriteFile ()
/*static*/
BOOL
CxStdioFile::bWriteFile(const tString &csFilePath, const uString &cusStr) {
	/*DEBUG*/

	BOOL        bRes       = FALSE;
	CxStdioFile sfFile;
	size_t      uiWriteLen = - 1;

	bRes = sfFile.bOpen(csFilePath, CxOpenMode::omBinWrite);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	uiWriteLen = sfFile.uiWrite((LPVOID)&cusStr.at(0), cusStr.size());
	/*DEBUG*/xASSERT_RET(cusStr.size() == uiWriteLen, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: _iGetHandle (Gets the file descriptor associated with a stream)
INT
CxStdioFile::_iGetHandle() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile, etError);

    INT iRes = etError;

	iRes = fileno/*_fileno*/(_m_pFile);
	/*DEBUG*/xASSERT_RET(etError != iRes, etError);

	return iRes;
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
