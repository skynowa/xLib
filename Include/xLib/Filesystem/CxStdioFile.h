/****************************************************************************
 Class name:  CxStdioFile
 File name:   CxStdioFile.h
 Description: file
 Author:      skynowa
 E-mail:      skynowa@gmail.com
 Created:     21.05.2009 17:46:38

*****************************************************************************/


#ifndef xLib_Filesystem_CxStdioFileH
#define xLib_Filesystem_CxStdioFileH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
/// \file  CxStdioFile.h
/// \class CxStdioFile
/// \brief file implementation
class CxStdioFile :
    public CxNonCopyable
{
    public:
        /// error type
        enum EErrorType {
            etError = TEOF
        };

        /// open mode
        enum EOpenMode {
            omRead,                ///< "r"
            omWrite,               ///< "w"
            omAppend,              ///< "a"
            omOpenReadWrite,       ///< "r+"
            omCreateReadWrite,     ///< "w+"
            omOpenReadAppend,      ///< "a+"

            omBinRead,             ///< "rb"
            omBinWrite,            ///< "wb"
            omBinAppend,           ///< "ab"
            omBinOpenReadWrite,    ///< "rb+"
            omBinCreateReadWrite,  ///< "wb+"
            omBinOpenReadAppend    ///< "ab+"
        };

    #if defined(xOS_WIN)
        /// translation mode
        enum ETranslationMode {
            tmText   = O_TEXT,
            tmBinary = O_BINARY
        };
    #endif

        /// access mode
        enum EAccessMode {
            amExistence = 0,
            amWrite     = 2,
            amRead      = 4,
            amReadWrite = 6
        };

        /// pointer position
        enum EPointerPosition {
            ppBegin = SEEK_SET,
            ppCurr  = SEEK_CUR,
            ppEnd   = SEEK_END,
            ppError = - 1L
        };

        /// buffering mode
        enum EBufferingMode {
            bmFull = _IOFBF,
            bmLine = _IOLBF,
            bmNo   = _IONBF
        };

        /// locking mode
        enum ELockingMode {
            #if defined(xOS_WIN)
                lmLock    = LK_NBLCK,
                lmTryLock = LK_LOCK,
                lmUnlock  = LK_UNLCK
            #elif defined(xOS_LINUX)
                lmLock    = F_LOCK,
                lmTlock   = F_TLOCK,
                lmTryLock = F_TEST,
                lmUnlock  = F_ULOCK
            #endif
        };

        /// permission mode
        enum EPermissionMode {
            #if defined(xOS_WIN)
                pmRead             = _S_IREAD,
                pmWrite            = _S_IWRITE,
                pmReadWrite        = (_S_IREAD | _S_IWRITE)
            #elif defined(xOS_LINUX)
                pmSetUserId        = S_ISUID,
                pmSetGroupId       = S_ISGID,
                pmStickyBit        = S_ISVTX,

                pmRead             = S_IRUSR,
                pmWrite            = S_IWUSR,
                pmReadWrite        = (S_IRUSR | S_IWUSR),
                pmExecSearch       = S_IXUSR,

                pmGroupRead        = S_IRGRP,
                pmGroupWrite       = S_IWGRP,
                pmGroupExecSearch  = S_IXGRP,

                pmOthersRead       = S_IROTH,
                pmOthersWrite      = S_IWOTH,
                pmOthersExecSearch = S_IXOTH
            #endif
        };

        //constructors, destructor
                         CxStdioFile  ();
            ///< constructor

        virtual         ~CxStdioFile  ();
            ///< destructor

        //open, get
        BOOL             bOpen        (const tString &csFilePath, const EOpenMode omMode, const BOOL cbIsUseBuffering);
            ///< open
        BOOL             bReopen      (const tString &csFilePath, const EOpenMode omMode, const BOOL cbIsUseBuffering);
            ///< reopen with different file or mode
        BOOL             bOpen        (FILE *pflFile);
            ///< attach to stream
        FILE            *pGet         () const;
            ///< get handle
        tString          sGetPath     () const;
            ///< get file path

        //read, write
        size_t           uiRead       (LPVOID pvBuff,        const size_t cuiCount) const;
            ///< read block of data
        size_t           uiWrite      (const LPVOID pcvBuff, const size_t cuiCount) const;
            ///< write block of data
        BOOL             bRead        (uString *psBuff) const;
            ///< read to uString
        BOOL             bWrite       (const uString &csBuff) const;
            ///< write from uString
        BOOL             bRead        (tString *psBuff) const;
            ///< read to tString
        INT              iWrite       (LPCTSTR pcszFormat, ...) const;
            ///< write formatted output to stream
        INT              iWriteV      (LPCTSTR pcszFormat, va_list arg) const;
            ///< write formatted variable argument list to stream
        BOOL             bReadLine    (tString *psStr, const size_t cuiMaxCount) const;
            ///< read string to newline or to the end of file
        BOOL             bWriteLine   (const tString &csStr) const;
            ///< write string and end of line
        TCHAR            chReadChar   () const;
            ///< get character
        BOOL             bWriteChar   (const TCHAR ccChar) const;
            ///< write character
        BOOL             bUngetChar   (const TCHAR ccChar) const;
            ///< unget character from stream
        BOOL             bClear       () const;
            ///< clear

        //times

        //other
        BOOL             bLocking     (const ELockingMode clmMode, const LONG cliBytes);
            ///< locks or unlocks bytes of a file
        BOOL             bSetPosition (const LONG clOffset, const EPointerPosition cppPos) const;
            ///< set stream position indicator
        LONG             liGetPosition() const;
            ///< get current position in stream
        BOOL             bSetVBuff    (LPSTR pszBuff, const EBufferingMode cbmMode, const size_t cuiSize) const;
            ///< change stream buffering

    #if defined(xOS_WIN)
        BOOL             bSetMode     (const ETranslationMode tmMode) const;
            ///< sets the file translation mode
    #endif

        LONG             liGetSize    () const;
            ///< get file size
        BOOL             bResize      (const LONG cliSize) const;
            ///< changes the file size

        //error handling
        BOOL             bIsValid     () const;
            ///< validating handle
        BOOL             bIsOpen      () const;
            ///< is open
        BOOL             bIsEmpty     () const;
            ///< is empty
        BOOL             bIsEof       () const;
            ///< check end of file indicator
        BOOL             bIsError     () const;
            ///< check error indicator
        BOOL             bErrorClear  () const;
            ///< clear error indicators

        //closing
        BOOL             bFlush       () const;
            ///< flush
        BOOL             bClose       ();
            ///< close

        //static
        static BOOL      bIsFile      (const tString &csFilePath);
            ///< check for file
        static BOOL      bIsExists    (const tString &csFilePath);
            ///< check for existence
        static BOOL      bAccess      (const tString &csFilePath, const EAccessMode camMode);
            ///< determine file-access permission
        static BOOL      bChmod       (const tString &csFilePath, const EPermissionMode cpmMode);
            ///< change the file-permission settings
        static BOOL      bClear       (const tString &csFilePath);
            ///< clear content
        static BOOL      bDelete      (const tString &csFilePath);
            ///< deleting
        static BOOL      bTryDelete   (const tString &csFilePath, const size_t cuiAttempts, const ULONG culTimeoutMsec);
            ///< try deleting, max 100 attempts
        static BOOL      bWipe        (const tString &csFilePath, const size_t cuiPasses);
            ///< wipe
        static BOOL      bUnlink      (const tString &csFilePath);
            ///< deleting
        static BOOL      bRename      (const tString &csOldFilePath,  const tString &csNewFilePath);
            ///< renaming
        static BOOL      bMove        (const tString &csFilePath,     const tString &csDirPath);
            ///< move
        static BOOL      bCopy        (const tString &csFilePathFrom, const tString &csFilePathTo, const BOOL cbFailIfExists);
            ///< copy
        static LONG      liGetSize    (const tString &csFilePath);
            ///< get size
        static ULONGLONG ullGetLines  (const tString &csFilePath);
            ///< get number of lines
        static BOOL      bGetTime     (const tString &csFilePath, time_t *ptmCreate, time_t *ptmAccess, time_t *ptmModified);
            ///< get time
        static BOOL      bSetTime     (const tString &csFilePath, const time_t &ctmCreate, const time_t &ctmAccess, const time_t &ctmModified);
            ///< set time

        //temporary
        static tString   sTempCreate  (const tString &csFilePath, const tString &csDirPath, FILE **pfFileHandle);
            ///< create temporary file, open it
        static BOOL      bTempClose   (FILE **pfFileHandle);
            ///< close temporary file

        //text
        static BOOL      bTextRead    (const tString &csFilePath, tString *psContent);
            ///< read to tString
        static BOOL      bTextWrite   (const tString &csFilePath, const tString &csContent);
            ///< write tString
        static BOOL      bTextRead    (const tString &csFilePath, std::vector<tString> *pvsContent);
            ///< read to std::vector
        static BOOL      bTextWrite   (const tString &csFilePath, const std::vector<tString> &cvsContent);
            ///< write std::vector
        static BOOL      bTextRead    (const tString &csFilePath, const tString &csSeparator, std::map<tString, tString> *pmsContent);
            ///< read text to std::map
        static BOOL      bTextWrite   (const tString &csFilePath, const tString &csSeparator, const std::map<tString, tString> &cmsContent);
            ///< write text from std::map

        //binary
        static BOOL      bBinRead     (const tString &csFilePath, uString *pusContent);
            ///< read binary data
        static BOOL      bBinWrite    (const tString &csFilePath, const uString &cusContent);
            ///< write binary data

        //other
        static tString   sBackup      (const tString &csFilePath, const tString &csDestDirPath, const BOOL cbMakeDaily /*,INT bBackupLimit*/);
            ///< backup

    private:
        mutable BOOL     _m_bRes;
            ///< for private using
        FILE            *_m_pFile;
            ///< file handle
        tString          _m_sFilePath;
            ///< file path

        static INT       _iGetHandle  (FILE *pfFile);
            ///< gets the file descriptor associated with a stream
        static FILE *    _pfGetHandle (INT iFileHandle, const EOpenMode omMode);
            ///< get stream by handle
        static tString   _sGetOpenMode(const EOpenMode comMode);
            ///< get open mode as string, by default use "r"
};
//---------------------------------------------------------------------------
#endif  //xLib_Filesystem_CxStdioFileH
