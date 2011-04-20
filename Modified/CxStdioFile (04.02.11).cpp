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


#include <xLib/Fso/CxStdioFile.h>

#include <xLib/Fso/CxPath.h>

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
*	public: ������
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxStdioFile (constructor)
CxStdioFile::CxStdioFile() :
    _m_bRes     (FALSE),
    _m_pFile    (NULL),
    _m_sFilePath()
{
	////BOOL bRes = FALSE;
	////
	////bRes = CxLocale::bSetDefault();
	////xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
//TODO: + ~CxStdioFile (destructor)
CxStdioFile::~CxStdioFile() { 
	xCHECK_DO(NULL == _m_pFile, return);

	_m_bRes = bClose();
	/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);	
}
//---------------------------------------------------------------------------
//TODO: + operator FILE* ()
CxStdioFile::operator FILE * () {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, NULL);     
	
	return _m_pFile;
}
//---------------------------------------------------------------------------
//TODO: + pGet (��������� ���������)
FILE *
CxStdioFile::pGet() {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, NULL);      

	return _m_pFile;
}
//---------------------------------------------------------------------------
//TODO: + bOpen (open)
BOOL
CxStdioFile::bOpen(const tString &csFilePath, const tString &omMode) {
	/*DEBUG*/xASSERT_RET(NULL  == _m_pFile,           FALSE);
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE); 
	/*DEBUG*/xASSERT_RET(false == omMode.empty(),     FALSE); 
	
	_m_pFile = _tfopen(csFilePath.c_str(), omMode.c_str());
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE); 

	_m_sFilePath = csFilePath; 

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bReopen (Reopen stream with different file or mode)
BOOL
CxStdioFile::bReopen(const tString &csFilePath, const tString &csMode) {
	/*DEBUG*/xASSERT_RET(NULL  != _m_pFile,           FALSE);
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE); 
	/*DEBUG*/xASSERT_RET(false == csMode.empty(),     FALSE); 

	_m_pFile = _tfreopen(csFilePath.c_str(), csMode.c_str(), _m_pFile);
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);   

	_m_sFilePath = csFilePath; 

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + sGetPath (file path)
tString
CxStdioFile::sGetPath() {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), tString()); 

	return _m_sFilePath;
}
//---------------------------------------------------------------------------


/****************************************************************************
* public: read / write
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + uiRead (Read block of data from stream)
std::size_t
CxStdioFile::uiRead(LPVOID pvBuff, std::size_t uiCount) {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, 0); 
	/*DEBUG*/xASSERT_RET(NULL != pvBuff,   0); 
	
	std::size_t uiRes = 0;

	uiRes = fread(pvBuff, /*sizeof(TCHAR)*/1, uiCount, _m_pFile);          
	/*DEBUG*/xASSERT_RET(uiCount >= uiRes, 0); 
	
	return uiRes;
}
//---------------------------------------------------------------------------
//TODO: - uiWrite (Write block of data to stream)
std::size_t
CxStdioFile::uiWrite(const LPVOID pcvBuf, std::size_t uiCount) {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, 0);
	/*DEBUG*/xASSERT_RET(NULL != pcvBuf,   0); 

	std::size_t uiRes = 0;

	uiRes = fwrite(pcvBuf, /*sizeof(TCHAR)*/1, uiCount, _m_pFile);
	/*DEBUG*/xASSERT_RET(uiCount == uiRes, 0); 

	return uiRes;
}
//---------------------------------------------------------------------------
//TODO: - bReadAll (������ ���� ���� �������)
BOOL
CxStdioFile::bReadAll(LPVOID pvBuff, std::size_t uiBuffSize, std::size_t uiBlockSize) {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile,    FALSE); 
	/*DEBUG*/xASSERT_RET(NULL != pvBuff,      FALSE); 
	/*DEBUG*/xASSERT_RET(0    != uiBlockSize, FALSE); 

	xNOT_IMPLEMENTED_RET(FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bWriteAll (����� ���� ���� �������)
BOOL
CxStdioFile::bWriteAll(const LPVOID pcvBuf, std::size_t uiBuffSize, std::size_t uiBlockSize) {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile,    FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pcvBuf,      FALSE); 
	/*DEBUG*/xASSERT_RET(0    != uiBlockSize, FALSE); 

    xNOT_IMPLEMENTED_RET(FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bReadAll (read all file by blocks)
BOOL
CxStdioFile::bReadAll(uString *psBuff, std::size_t uiBlockSize) {
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
		uiRes = fread(&(*psBuff).at(0) + i, sizeof(UCHAR)/*1*/, uiBlockSize, _m_pFile);
		/*DEBUG*/xASSERT_RET(uiBlockSize >= uiRes, FALSE); 
    }

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bWriteAll (write all string by blocks)
BOOL
CxStdioFile::bWriteAll(const uString &csBuff, std::size_t uiBlockSize) {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile,    FALSE); 
	/*DEBUG*///csBuff - n/a
	/*DEBUG*/xASSERT_RET(0    <  uiBlockSize, FALSE); 

	std::size_t uiRes = 0;

	for (std::size_t i = 0; i < csBuff.size(); i += uiBlockSize) {
		//������� ������
		if (uiBlockSize > (csBuff.size() - i)) {
			uiBlockSize = csBuff.size() - i;
		}

		uiRes = fwrite(&csBuff.at(0) + i, sizeof(UCHAR)/*1*/, uiBlockSize, _m_pFile);
		/*DEBUG*/xASSERT_RET(uiBlockSize == uiRes, FALSE); 
    }

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bReadLine (Reads data from the file to pszStr till '\n' is encountered)
BOOL
CxStdioFile::bReadLine(LPTSTR pszStr, std::size_t uiMaxCount) {		//TODO: overflow
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pszStr,   FALSE); 

	LPTSTR pszRes = NULL;
	
	pszRes = _fgetts(pszStr, uiMaxCount, _m_pFile);
	/*DEBUG*/xASSERT_RET(NULL != pszRes, FALSE); 

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bWriteLine (Writes csStr and then writes '\n' to the file)
BOOL
CxStdioFile::bWriteLine(const tString &csStr) {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

	std::size_t uiSize = csStr.size() + CxConst::xEOL.size();
	std::size_t uiRes  = uiWrite(static_cast<LPVOID>(&(csStr + CxConst::xEOL).at(0)), uiSize);
	xCHECK_RET(uiRes < uiSize, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bWriteChar (Write character to stream)
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
//TODO: + cReadChar (Get character from stream)
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
//TODO: + bUngetChar (Unget character from stream)
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
//TODO: + bWriteString (Write string to stream)
BOOL
CxStdioFile::bWriteString(const tString &csStr) {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);

	INT iRes = etError;

	iRes = _fputts(csStr.c_str(), _m_pFile);
	/*DEBUG*/xASSERT_RET(iRes != etError, FALSE);
	/*DEBUG*/xASSERT_RET(EOF < iRes,      FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bReadFile (read in std::vector)
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
			pvecsVector->push_back(CxString::sRemoveEOL(sLine));	
			sLine.clear();		
		}
	}

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bWriteFile (write std::vector in file)
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
//TODO: + bSetMode (Sets the file translation mode)
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
//TODO: + bSetPosition (REFilePosition stream position indicator)
BOOL
CxStdioFile::bSetPosition(LONG lOffset, EPointerPosition fpPos/* = fpBegin*/) {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);
    
	INT iRet = ppError;

	iRet = fseek(_m_pFile, lOffset, fpPos);
	/*DEBUG*/xASSERT_RET(0 == iRet, FALSE); 
	
	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + liGetPosition (Get current position in stream)
LONG
CxStdioFile::liGetPosition() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);
    
	LONG liRes = ppError;

	liRes = ftell(_m_pFile);
	/*DEBUG*/xASSERT_RET(ppError != liRes, ppError); 
		
	return liRes;
}
//---------------------------------------------------------------------------
//TODO: + liGetSize (file size)
//NOTE: https://www.securecoding.cert.org/confluence/display/seccode/FIO19-C.+Do+not+use+fseek()+and+ftell()+to+compute+the+size+of+a+file
LONG
CxStdioFile::liGetSize() {
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
//TODO: + bChsize(Changes the file size)
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
//TODO: + bLocking (Locks or unlocks bytes of a file)
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
//TODO: + bFlush (Flush stream)
BOOL
CxStdioFile::bFlush() {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);  

	INT iRes = etError;	

	iRes = fflush(_m_pFile);
	/*DEBUG*/xASSERT_RET(0 == iRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bClose (Close file)
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
//TODO: - bIsFile (check for file)
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
//TODO: + bIsExists (check for existence)
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
//TODO: + bAccess (Determine file-access permission)
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
//TODO: + bChmod (Change the file-permission settings)
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
//TODO: + bDelete (delete)
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
//TODO: + bUnlink (Delete a file)
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
//TODO: + bRename (rename)
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
//TODO: + bCopy (copy)
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
//TODO: + bMove (move)
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
//TODO: + sCreateTempFileName (Generate temporary filename)
/*static*/
tString
CxStdioFile::sCreateTempFileName() {
	TCHAR  szBuff[L_tmpnam] = {0};
	TCHAR *pszRes           = NULL;

	pszRes = _ttmpnam(szBuff);
	/*DEBUG*/xASSERT_RET(NULL != pszRes, tString()); 

	return tString(szBuff);  
}
//---------------------------------------------------------------------------
//TODO: - ulLines (���-�� ����� � �����)
/*static*/
ULONGLONG
CxStdioFile::ullLines(const tString &csFilePath) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    0);
	/*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), 0);

	//-------------------------------------
	//������������� ��������� ������
	////BOOL bRes = CxLocale::bSetDefault();
	/////*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
	
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
*	public: character input/output
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + cGetCharFromStdin (Get character from stdin)
/*static*/
TCHAR
CxStdioFile::cGetCharFromStdin() {
	INT iRes = etError;
	
	iRes = _gettchar();
	/*DEBUG*/xASSERT_RET(etError != iRes, static_cast<TCHAR>(etError));
	
	return (TCHAR)iRes;
}
//---------------------------------------------------------------------------
//TODO: + sGetStringFromStdin (Get string from stdin)
/*static*/
tString
CxStdioFile::sGetStringFromStdin(LPTSTR pszBuff) {
	LPTSTR pszRes = NULL;

	pszRes = _getts(pszBuff);
	/*DEBUG*/xASSERT_RET(NULL != pszRes, tString());


	////fgets( buff, 100, stdin );   // safe

	return tString(pszRes);
}
//---------------------------------------------------------------------------
//TODO: + bWriteCharToStdout (Write character to stdout)
/*static*/
BOOL
CxStdioFile::bWriteCharToStdout(TCHAR cChar) {
    INT iRes = etError;

    iRes = _puttchar(static_cast<INT>(cChar));
    /*DEBUG*/xASSERT_RET(etError                 != iRes, FALSE);
    /*DEBUG*/xASSERT_RET(static_cast<INT>(cChar) == iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bWriteStringToStdout (Write string to stdout)
/*static*/
BOOL
CxStdioFile::bWriteStringToStdout(const tString &csStr) {
    INT iRes = etError;

    iRes = _putts(csStr.c_str());
    /*DEBUG*/xASSERT_RET(etError < iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + iFprintfV (Write formatted variable argument list to stream)
INT
CxStdioFile::iFprintfV(LPCTSTR pcszFormat, va_list arg) {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile,   etError);
    /*DEBUG*/xASSERT_RET(NULL != pcszFormat, etError);
    /*DEBUG*/xASSERT_RET(NULL != arg,        etError);

    INT iRes = etError;

    iRes = _vftprintf(_m_pFile, pcszFormat, arg);
    /*DEBUG*/xASSERT_RET(etError < iRes, etError);

    return iRes;
}
//---------------------------------------------------------------------------
//TODO: + iPrintfV (Print formatted variable argument list to stdout)
INT
CxStdioFile::iPrintfV(LPCTSTR pcszFormat, va_list arg) {
    /*DEBUG*/xASSERT_RET(NULL != pcszFormat, etError);
    /*DEBUG*/xASSERT_RET(NULL != arg,        etError);

    INT iRes = etError;

    iRes = _vtprintf(pcszFormat, arg);
    /*DEBUG*/xASSERT_RET(etError < iRes, etError);

    return iRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public: Formatted input/output 
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + iFprintf(Write formatted output to stream)
INT
CxStdioFile::iFprintf(LPCTSTR pcszFormat, ...) {
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
//TODO: + iPrintf (Print formatted data to stdout)
INT
CxStdioFile::iPrintf(LPCTSTR pcszFormat, ...) {
	/*DEBUG*/xASSERT_RET(NULL != pcszFormat, etError); 
	
	INT iRes = etError;
	
	va_list args = NULL;
	va_start(args, pcszFormat);

	iRes = _vtprintf(pcszFormat, args);
	/*DEBUG*/xASSERT_RET(etError < iRes, etError);
	
	va_end(args);

	return iRes;
}
//---------------------------------------------------------------------------
//TODO: + bFlushAllOutput (Flushes all streams opened for output)
/*static*/
BOOL
CxStdioFile::bFlushAllOutput() {
    INT iRes = etError;

    iRes = fflush(NULL);
    /*DEBUG*/xASSERT_RET(0 == iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + iFlushAll (returns the number of open streams (input and output))
/*static*/
INT
CxStdioFile::iFlushAll() {
    INT iRes = etError;

#if defined(xOS_WIN)
    iRes = _flushall();
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    xNOT_IMPLEMENTED_RET(etError);
#endif

    return iRes;
}
//--------------------------------------------------------------------------


/****************************************************************************
*	public: Error-handling:
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + bClearErr (Clear error indicators)
BOOL
CxStdioFile::bClearErr() {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);
    
    clearerr(_m_pFile);
    /*DEBUG*/// n/a
    
    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bIsEof (Check End-of-File indicator)
BOOL
CxStdioFile::bIsEof() {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);
 
	INT iRes = feof(_m_pFile);
	/*DEBUG*/// n/a

    return static_cast<BOOL>(iRes);
	/*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: + bIsError (Check error indicator)
BOOL
CxStdioFile::bIsError() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFile, FALSE);
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>(ferror(_m_pFile));
    /*DEBUG*/// n/a
    
    return TRUE;
}		
//---------------------------------------------------------------------------
//TODO: + bPrintError (Print error message)
BOOL
CxStdioFile::bPrintError(const tString &csStr) {
    _tperror(csStr.c_str());
    /*DEBUG*/// n/a
    
    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public: ������ / ������ �����
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

	bRes = sfFile.bOpen(csFilePath, CxStdioFile::CxOpenMode::omRead);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	iRes = sfFile.liGetSize();
	/*DEBUG*/xASSERT_RET(0 <= iRes, FALSE);

	return iRes; 
}
//--------------------------------------------------------------------------
//TODO: - bReadFileEx
/*static*/
BOOL
CxStdioFile::bReadFileEx(const tString &csFilePath, std::vector<tString> *pvecsFile) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    FALSE);
	/*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), FALSE);
	/*DEBUG*/xASSERT_RET(NULL  != pvecsFile,             FALSE);

	//-------------------------------------
	//������������� ��������� ������
	////BOOL bRes = CxLocale::bSetDefault();
	////xASSERT_RET(FALSE != bRes, FALSE);
	
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

	//-------------------------------------
	//������������� ��������� ������
	////BOOL bRes = CxLocale::bSetDefault();
	////xASSERT_RET(FALSE != bRes, FALSE);

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

	//-------------------------------------
	//������������� ��������� ������
	////bRes = CxLocale::bSetDefault();
	/////*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
	
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

	//-------------------------------------
	//������������� ��������� ������
	////BOOL bRes = CxLocale::bSetDefault();
	////xASSERT_RET(FALSE != bRes, FALSE);
	
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

	bRes = sfFile.bOpen(csFilePath, CxStdioFile::CxOpenMode::omBinRead);
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

	bRes = sfFile.bOpen(csFilePath, CxStdioFile::CxOpenMode::omBinWrite);
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
//TODO: + _iGetHandle (Gets the file descriptor associated with a stream)
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
