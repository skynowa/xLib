/**
 * \file  CxStdioFile.h
 * \brief file
 */


#ifndef xLib_Filesystem_CxStdioFileH
#define xLib_Filesystem_CxStdioFileH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxStdioFile :
    public CxNonCopyable
    /// file
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
        BOOL             bOpen        (const std::tstring &csFilePath, const EOpenMode omMode, const BOOL cbIsUseBuffering);
            ///< open
        BOOL             bReopen      (const std::tstring &csFilePath, const EOpenMode omMode, const BOOL cbIsUseBuffering);
            ///< reopen with different file or mode
        BOOL             bOpen        (FILE *pflFile);
            ///< attach to stream
        FILE            *pGet         () const;
            ///< get handle
        std::tstring          sGetPath     () const;
            ///< get file path

        //read, write
        size_t           uiRead       (LPVOID pvBuff,        const size_t cuiCount) const;
            ///< read block of data
        size_t           uiWrite      (const LPVOID pcvBuff, const size_t cuiCount) const;
            ///< write block of data
        BOOL             bRead        (std::ustring *psBuff) const;
            ///< read to std::ustring
        BOOL             bWrite       (const std::ustring &csBuff) const;
            ///< write from std::ustring
        BOOL             bRead        (std::tstring *psBuff) const;
            ///< read to std::tstring
        INT              iWrite       (LPCTSTR pcszFormat, ...) const;
            ///< write formatted output to stream
        INT              iWriteV      (LPCTSTR pcszFormat, va_list arg) const;
            ///< write formatted variable argument list to stream
        BOOL             bReadLine    (std::tstring *psStr, const size_t cuiMaxCount) const;
            ///< read string to newline or to the end of file
        BOOL             bWriteLine   (const std::tstring &csStr) const;
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
        static BOOL      bIsFile      (const std::tstring &csFilePath);
            ///< check for file
        static BOOL      bIsExists    (const std::tstring &csFilePath);
            ///< check for existence
        static BOOL      bAccess      (const std::tstring &csFilePath, const EAccessMode camMode);
            ///< determine file-access permission
        static BOOL      bChmod       (const std::tstring &csFilePath, const EPermissionMode cpmMode);
            ///< change the file-permission settings
        static BOOL      bClear       (const std::tstring &csFilePath);
            ///< clear content
        static BOOL      bDelete      (const std::tstring &csFilePath);
            ///< deleting
        static BOOL      bTryDelete   (const std::tstring &csFilePath, const size_t cuiAttempts, const ULONG culTimeoutMsec);
            ///< try deleting, max 100 attempts
        static BOOL      bWipe        (const std::tstring &csFilePath, const size_t cuiPasses);
            ///< wipe
        static BOOL      bUnlink      (const std::tstring &csFilePath);
            ///< deleting
        static BOOL      bRename      (const std::tstring &csOldFilePath,  const std::tstring &csNewFilePath);
            ///< renaming
        static BOOL      bMove        (const std::tstring &csFilePath,     const std::tstring &csDirPath);
            ///< move
        static BOOL      bCopy        (const std::tstring &csFilePathFrom, const std::tstring &csFilePathTo, const BOOL cbFailIfExists);
            ///< copy
        static LONG      liGetSize    (const std::tstring &csFilePath);
            ///< get size
        static ULONGLONG ullGetLines  (const std::tstring &csFilePath);
            ///< get number of lines
        static BOOL      bGetTime     (const std::tstring &csFilePath, time_t *ptmCreate, time_t *ptmAccess, time_t *ptmModified);
            ///< get time
        static BOOL      bSetTime     (const std::tstring &csFilePath, const time_t &ctmCreate, const time_t &ctmAccess, const time_t &ctmModified);
            ///< set time

        //temporary
        static std::tstring   sTempCreate  (const std::tstring &csFilePath, const std::tstring &csDirPath, FILE **pfFileHandle);
            ///< create temporary file, open it
        static BOOL      bTempClose   (FILE **pfFileHandle);
            ///< close temporary file

        //text
        static BOOL      bTextRead    (const std::tstring &csFilePath, std::tstring *psContent);
            ///< read to std::tstring
        static BOOL      bTextWrite   (const std::tstring &csFilePath, const std::tstring &csContent);
            ///< write std::tstring
        static BOOL      bTextRead    (const std::tstring &csFilePath, std::vector<std::tstring> *pvsContent);
            ///< read to std::vector
        static BOOL      bTextWrite   (const std::tstring &csFilePath, const std::vector<std::tstring> &cvsContent);
            ///< write std::vector
        static BOOL      bTextRead    (const std::tstring &csFilePath, const std::tstring &csSeparator, std::map<std::tstring, std::tstring> *pmsContent);
            ///< read text to std::map
        static BOOL      bTextWrite   (const std::tstring &csFilePath, const std::tstring &csSeparator, const std::map<std::tstring, std::tstring> &cmsContent);
            ///< write text from std::map

        //binary
        static BOOL      bBinRead     (const std::tstring &csFilePath, std::ustring *pusContent);
            ///< read binary data
        static BOOL      bBinWrite    (const std::tstring &csFilePath, const std::ustring &cusContent);
            ///< write binary data

        //other
        static std::tstring   sBackup      (const std::tstring &csFilePath, const std::tstring &csDestDirPath, const BOOL cbMakeDaily /*,INT bBackupLimit*/);
            ///< backup

    private:
        mutable BOOL     _m_bRes;
            ///< for private using
        FILE            *_m_pFile;
            ///< file handle
        std::tstring          _m_sFilePath;
            ///< file path

        static INT       _iGetHandle  (FILE *pfFile);
            ///< gets the file descriptor associated with a stream
        static FILE *    _pfGetHandle (INT iFileHandle, const EOpenMode omMode);
            ///< get stream by handle
        static std::tstring   _sGetOpenMode(const EOpenMode comMode);
            ///< get open mode as string, by default use "r"
};
//---------------------------------------------------------------------------
#endif  //xLib_Filesystem_CxStdioFileH
