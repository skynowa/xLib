/**
 * \file  CxFile.h
 * \brief file
 */


#ifndef xLib_Filesystem_CxFileH
#define xLib_Filesystem_CxFileH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxFile :
    public CxNonCopyable
    /// file
{
    public:


        enum EOpenMode
            /// open mode
        {
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

    #if xOS_ENV_WIN
        enum ETranslationMode
            /// translation mode
        {
            tmText   = O_TEXT,
            tmBinary = O_BINARY
        };
    #endif

        enum EAccessMode
            /// access mode
        {
            amExistence = 0,
            amWrite     = 2,
            amRead      = 4,
            amReadWrite = 6
        };

        enum EPointerPosition
            /// pointer position
        {
            ppError = - 1L,
            ppBegin = SEEK_SET,
            ppCurr  = SEEK_CUR,
            ppEnd   = SEEK_END
        };

        enum EBufferingMode
            /// buffering mode
        {
            bmFull = _IOFBF,
            bmLine = _IOLBF,
            bmNo   = _IONBF
        };

        enum ELockingMode
            /// locking mode
        {
            #if xOS_ENV_WIN
                lmLock    = LK_NBLCK,
                lmTryLock = LK_LOCK,
                lmUnlock  = LK_UNLCK
            #elif xOS_ENV_UNIX
                lmLock    = F_LOCK,
                lmTlock   = F_TLOCK,
                lmTryLock = F_TEST,
                lmUnlock  = F_ULOCK
            #endif
        };

        enum EPermissionMode
            /// permission mode
        {
            #if xOS_ENV_WIN
                pmRead             = _S_IREAD,
                pmWrite            = _S_IWRITE,
                pmReadWrite        = (_S_IREAD | _S_IWRITE)
            #elif xOS_ENV_UNIX
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
                             CxFile       ();
            ///< constructor

        virtual             ~CxFile       ();
            ///< destructor

        //open, get
        bool                 bCreate      (const std::tstring &csFilePath, const EOpenMode omMode, const bool cbIsUseBuffering);
            ///< open
        bool                 bReopen      (const std::tstring &csFilePath, const EOpenMode omMode, const bool cbIsUseBuffering);
            ///< reopen with different file or mode
        bool                 bAttach      (std::FILE *pflFile);
            ///< attach to stream
        std::FILE *          pDetach      ();
            ///< detach from stream
        std::FILE           *pGet         () const;
            ///< get handle
        std::tstring        sGetPath     () const;
            ///< get file path

        //read, write
        size_t               uiRead       (void *pvBuff,        const size_t cuiCount) const;
            ///< read block of data
        size_t               uiWrite      (const void *pcvBuff, const size_t cuiCount) const;
            ///< write block of data
        bool                 bRead        (std::ustring *psBuff) const;
            ///< read to std::ustring
        bool                 bWrite       (const std::ustring &csBuff) const;
            ///< write from std::ustring
        bool                 bRead        (std::tstring *psBuff) const;
            ///< read to std::tstring
        int                  iWrite       (const tchar *pcszFormat, ...) const;
            ///< write formatted output to stream
        int                  iWriteV      (const tchar *pcszFormat, va_list arg) const;
            ///< write formatted variable argument list to stream
        bool                 bReadLine    (std::tstring *psStr, const size_t cuiMaxCount) const;
            ///< read string to newline or to the end of file
        bool                 bWriteLine   (const std::tstring &csStr) const;
            ///< write string and end of line
        tchar                chReadChar   () const;
            ///< get character
        bool                 bWriteChar   (const tchar ccChar) const;
            ///< write character
        bool                 bUngetChar   (const tchar ccChar) const;
            ///< unget character from stream
        bool                 bClear       () const;
            ///< clear

        //times

        //other
        bool                 bLocking     (const ELockingMode clmMode, const LONG cliBytes);
            ///< locks or unlocks bytes of a file
        bool                 bSetPosition (const LONG clOffset, const EPointerPosition cppPos) const;
            ///< set stream position indicator
        LONG                 liGetPosition() const;
            ///< get current position in stream
        bool                 bSetVBuff    (char *pszBuff, const EBufferingMode cbmMode, const size_t cuiSize) const;
            ///< change stream buffering

    #if xOS_ENV_WIN
        bool                 bSetMode     (const ETranslationMode tmMode) const;
            ///< sets the file translation mode
    #endif

        LONG                 liGetSize    () const;
            ///< get file size
        bool                 bResize      (const LONG cliSize) const;
            ///< changes the file size

        //error handling
        bool                 bIsValid     () const;
            ///< validating handle
        bool                 bIsOpen      () const;
            ///< is open
        bool                 bIsEmpty     () const;
            ///< is empty
        bool                 bIsEof       () const;
            ///< check end of file indicator
        bool                 bIsError     () const;
            ///< check error indicator
        bool                 bErrorClear  () const;
            ///< clear error indicators

        //closing
        bool                 bFlush       () const;
            ///< flush
        bool                 bClose       ();
            ///< close

        //static
        static bool          bIsFile      (const std::tstring &csFilePath);
            ///< check for file
        static bool          bIsExists    (const std::tstring &csFilePath);
            ///< check for existence
        static std::tstring  sIsExists    (const std::tstring &csFilePath);
            ///< check for existence, if exists - generate new file name (file path), which not exists
        static bool          bAccess      (const std::tstring &csFilePath, const EAccessMode camMode);
            ///< determine file-access permission
        static bool          bChmod       (const std::tstring &csFilePath, const EPermissionMode cpmMode);
            ///< change the file-permission settings
        static bool          bClear       (const std::tstring &csFilePath);
            ///< clear content
        static bool          bDelete      (const std::tstring &csFilePath);
            ///< deleting
        static bool          bTryDelete   (const std::tstring &csFilePath, const size_t cuiAttempts, const ULONG culTimeoutMsec);
            ///< try deleting, max 100 attempts
        static bool          bWipe        (const std::tstring &csFilePath, const size_t cuiPasses);
            ///< wipe
        static bool          bUnlink      (const std::tstring &csFilePath);
            ///< deleting
        static bool          bRename      (const std::tstring &csOldFilePath,  const std::tstring &csNewFilePath);
            ///< renaming
        static bool          bMove        (const std::tstring &csFilePath,     const std::tstring &csDirPath);
            ///< move
        static bool          bCopy        (const std::tstring &csFilePathFrom, const std::tstring &csFilePathTo, const bool cbFailIfExists);
            ///< copy
        static LONG          liGetSize    (const std::tstring &csFilePath);
            ///< get size
        static ULONGLONG     ullGetLines  (const std::tstring &csFilePath);
            ///< get number of lines
        static bool          bGetTime     (const std::tstring &csFilePath, time_t *ptmCreate, time_t *ptmAccess, time_t *ptmModified);
            ///< get time
        static bool          bSetTime     (const std::tstring &csFilePath, const time_t &ctmCreate, const time_t &ctmAccess, const time_t &ctmModified);
            ///< set time

        //text
        static bool          bTextRead    (const std::tstring &csFilePath, std::tstring *psContent);
            ///< read to std::tstring
        static bool          bTextWrite   (const std::tstring &csFilePath, const std::tstring &csContent);
            ///< write std::tstring
        static bool          bTextRead    (const std::tstring &csFilePath, std::vector<std::tstring> *pvsContent);
            ///< read to std::vector
        static bool          bTextWrite   (const std::tstring &csFilePath, const std::vector<std::tstring> &cvsContent);
            ///< write std::vector
        static bool          bTextRead    (const std::tstring &csFilePath, const std::tstring &csSeparator, std::map<std::tstring, std::tstring> *pmsContent);
            ///< read text to std::map
        static bool          bTextWrite   (const std::tstring &csFilePath, const std::tstring &csSeparator, const std::map<std::tstring, std::tstring> &cmsContent);
            ///< write text from std::map

        //binary
        static bool          bBinRead     (const std::tstring &csFilePath, std::ustring *pusContent);
            ///< read binary data
        static bool          bBinWrite    (const std::tstring &csFilePath, const std::ustring &cusContent);
            ///< write binary data

    private:
            enum EErrorType
            /// error type
        {
            etError = - 1
        };

        std::FILE            *_m_pFile;      ///< file handle
        std::tstring         _m_sFilePath;  ///< file path

        static int           _iGetHandle  (std::FILE *pfFile);
            ///< gets the file descriptor associated with a stream
        static std::FILE *   _pfGetHandle (int iFileHandle, const EOpenMode omMode);
            ///< get stream by handle
        static std::tstring  _sGetOpenMode(const EOpenMode comMode);
            ///< get open mode as string, by default use "r"
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif  //xLib_Filesystem_CxFileH


#if xTODO
    int64_t
    CxFile::getSize(const String &path) {
        int64_t size = -1;

    #ifdef CCXX_OS_WINDOWS

        struct _stati64 stbuf;
        if (::_stati64(removeTrailingSeparators(path).c_str(), &stbuf) == 0)
            size = stbuf.st_size;
    #else
        struct stat stbuf;
        if (::stat(path.c_str(), &stbuf) == 0)
            size = stbuf.st_size;
    #endif

        return size;
    }
#endif
