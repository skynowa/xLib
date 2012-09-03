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
    private CxNonCopyable
    /// file
{
    public:
        enum ExErrorType
            /// error type
        {
            etError = - 1
        };

        enum ExOpenMode
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
        enum ExTranslationMode
            /// translation mode
        {
            tmText   = O_TEXT,
            tmBinary = O_BINARY
        };
    #endif

        enum ExAccessMode
            /// access mode
        {
            amExistence = 0,
            amWrite     = 2,
            amRead      = 4,
            amReadWrite = 6
        };

        enum ExPointerPosition
            /// pointer position
        {
            ppError = - 1L,
            ppBegin = SEEK_SET,
            ppCurr  = SEEK_CUR,
            ppEnd   = SEEK_END
        };

        enum ExBufferingMode
            /// buffering mode
        {
            bmFull = _IOFBF,
            bmLine = _IOLBF,
            bmNo   = _IONBF
        };

        enum ExLockingMode
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

        enum ExPermissionMode
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

        virtual               ~CxFile       ();
            ///< destructor

        //open, get
        bool                   bCreate      (const std::tstring_t &csFilePath, const ExOpenMode omMode, const bool cbIsUseBuffering);
            ///< open
        bool                   bReopen      (const std::tstring_t &csFilePath, const ExOpenMode omMode, const bool cbIsUseBuffering);
            ///< reopen with different file or mode
        bool                   bAttach      (std::FILE *pflFile);
            ///< attach to stream
        std::FILE *            pDetach      ();
            ///< detach from stream
        std::FILE             *pGet         () const;
            ///< get handle
        std::tstring_t         sGetPath     () const;
            ///< get file path

        //read, write
        size_t                 uiRead       (void *pvBuff,        const size_t cuiCount) const;
            ///< read block of data
        size_t                 uiWrite      (const void *pcvBuff, const size_t cuiCount) const;
            ///< write block of data
        bool                   bRead        (std::ustring_t *psBuff) const;
            ///< read to std::ustring_t
        bool                   bWrite       (const std::ustring_t &csBuff) const;
            ///< write from std::ustring_t
        bool                   bRead        (std::tstring_t *psBuff) const;
            ///< read to std::tstring_t
        int                    iWrite       (const tchar_t *pcszFormat, ...) const;
            ///< write formatted output to stream
        int                    iWriteV      (const tchar_t *pcszFormat, va_list arg) const;
            ///< write formatted variable argument list to stream
        bool                   bReadLine    (std::tstring_t *psStr, const size_t cuiMaxCount) const;
            ///< read string to newline or to the end of file
        bool                   bWriteLine   (const std::tstring_t &csStr) const;
            ///< write string and end of line
        tchar_t                chReadChar   () const;
            ///< get character
        bool                   bWriteChar   (const tchar_t ccChar) const;
            ///< write character
        bool                   bUngetChar   (const tchar_t ccChar) const;
            ///< unget character from stream
        bool                   bClear       () const;
            ///< clear

        //times

        //other
        bool                   bLocking     (const ExLockingMode clmMode, const long_t cliBytes);
            ///< locks or unlocks bytes of a file
        bool                   bSetPosition (const long_t clOffset, const ExPointerPosition cppPos) const;
            ///< set stream position indicator
        long_t                 liGetPosition() const;
            ///< get current position in stream
        bool                   bSetVBuff    (char *pszBuff, const ExBufferingMode cbmMode, const size_t cuiSize) const;
            ///< change stream buffering

    #if xOS_ENV_WIN
        bool                   bSetMode     (const ExTranslationMode tmMode) const;
            ///< sets the file translation mode
    #endif

        longlong_t             llGetSize    () const;
            ///< get file size
        bool                   bResize      (const longlong_t cllSize) const;
            ///< changes the file size

        //error handling
        bool                   bIsValid     () const;
            ///< validating handle
        bool                   bIsOpen      () const;
            ///< is open
        bool                   bIsEmpty     () const;
            ///< is empty
        bool                   bIsEof       () const;
            ///< check end of file indicator
        bool                   bIsError     () const;
            ///< check error indicator
        bool                   bErrorClear  () const;
            ///< clear error indicators

        //closing
        bool                   bFlush       () const;
            ///< flush
        bool                   bClose       ();
            ///< close

        //static
        static bool            bIsFile      (const std::tstring_t &csFilePath);
            ///< check for file
        static bool            bIsExists    (const std::tstring_t &csFilePath);
            ///< check for existence
        static std::tstring_t  sIsExists    (const std::tstring_t &csFilePath);
            ///< check for existence, if exists - generate new file name (file path), which not exists
        static bool            bAccess      (const std::tstring_t &csFilePath, const ExAccessMode camMode);
            ///< determine file-access permission
        static bool            bChmod       (const std::tstring_t &csFilePath, const ExPermissionMode cpmMode);
            ///< change the file-permission settings
        static bool            bClear       (const std::tstring_t &csFilePath);
            ///< clear content
        static bool            bDelete      (const std::tstring_t &csFilePath);
            ///< deleting
        static bool            bTryDelete   (const std::tstring_t &csFilePath, const size_t cuiAttempts, const ulong_t culTimeoutMsec);
            ///< try deleting, max 100 attempts
        static bool            bWipe        (const std::tstring_t &csFilePath, const size_t cuiPasses);
            ///< wipe
        static bool            bUnlink      (const std::tstring_t &csFilePath);
            ///< deleting
        static bool            bRename      (const std::tstring_t &csOldFilePath,  const std::tstring_t &csNewFilePath);
            ///< renaming
        static bool            bMove        (const std::tstring_t &csFilePath,     const std::tstring_t &csDirPath);
            ///< move
        static bool            bCopy        (const std::tstring_t &csFilePathFrom, const std::tstring_t &csFilePathTo, const bool cbFailIfExists);
            ///< copy
        static longlong_t      llGetSize    (const std::tstring_t &csFilePath);
            ///< get size
        static ulonglong_t     ullGetLines  (const std::tstring_t &csFilePath);
            ///< get number of lines
        static bool            bGetTime     (const std::tstring_t &csFilePath, time_t *ptmCreate, time_t *ptmAccess, time_t *ptmModified);
            ///< get time
        static bool            bSetTime     (const std::tstring_t &csFilePath, const time_t &ctmCreate, const time_t &ctmAccess, const time_t &ctmModified);
            ///< set time

        //text
        static bool            bTextRead    (const std::tstring_t &csFilePath, std::tstring_t *psContent);
            ///< read to std::tstring_t
        static bool            bTextWrite   (const std::tstring_t &csFilePath, const std::tstring_t &csContent);
            ///< write std::tstring_t
        static bool            bTextRead    (const std::tstring_t &csFilePath, std::vec_tstring_t *pvsContent);
            ///< read to std::vector
        static bool            bTextWrite   (const std::tstring_t &csFilePath, const std::vec_tstring_t &cvsContent);
            ///< write std::vector
        static bool            bTextRead    (const std::tstring_t &csFilePath, const std::tstring_t &csSeparator, std::map_tstring_t *pmsContent);
            ///< read text to std::map
        static bool            bTextWrite   (const std::tstring_t &csFilePath, const std::tstring_t &csSeparator, const std::map_tstring_t &cmsContent);
            ///< write text from std::map

        //binary
        static bool            bBinRead     (const std::tstring_t &csFilePath, std::ustring_t *pusContent);
            ///< read binary data
        static bool            bBinWrite    (const std::tstring_t &csFilePath, const std::ustring_t &cusContent);
            ///< write binary data

    private:
        std::FILE             *_m_pFile;      ///< file handle
        std::tstring_t         _m_sFilePath;  ///< file path

        static int             _iGetHandle  (std::FILE *pfFile);
            ///< gets the file descriptor associated with a stream
        static std::FILE *     _pfGetHandle (int iFileHandle, const ExOpenMode omMode);
            ///< get stream by handle
        static std::tstring_t  _sGetOpenMode(const ExOpenMode comMode);
            ///< get open mode as string, by default use "r"

        friend class           CxFileTemp;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif  //xLib_Filesystem_CxFileH
