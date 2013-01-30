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
        #if   xOS_ENV_WIN
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
        #if   xOS_ENV_WIN
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

    // constructors, destructor
                           CxFile       ();
        ///< constructor
    virtual               ~CxFile       ();
        ///< destructor

    // open, get
    void                   create       (const std::tstring_t &csFilePath, const ExOpenMode &omMode, const bool &cbIsUseBuffering);
        ///< open
    void                   reopen       (const std::tstring_t &csFilePath, const ExOpenMode &omMode, const bool &cbIsUseBuffering);
        ///< reopen with different file or mode
    std::FILE             *get          () const;
        ///< get handle
    const std::tstring_t & path         () const;
        ///< get file path
    void                   attach       (std::FILE *pflFile);
        ///< attach to stream
    std::FILE *            detach       ();
        ///< detach from stream

    // read, write
    size_t                 read         (void *pvBuff,        const size_t &cuiCount) const;
        ///< read block of data
    size_t                 write        (const void *pcvBuff, const size_t &cuiCount) const;
        ///< write block of data
    void                   read         (std::ustring_t *psBuff) const;
        ///< read to std::ustring_t
    void                   write        (const std::ustring_t &csBuff) const;
        ///< write from std::ustring_t
    void                   read         (std::tstring_t *psBuff) const;
        ///< read to std::tstring_t
    int                    write        (const tchar_t *pcszFormat, ...) const;
        ///< write formatted output to stream
    int                    writeV       (const tchar_t *pcszFormat, va_list arg) const;
        ///< write formatted variable argument list to stream
    void                   readLine     (std::tstring_t *psStr, const size_t &cuiMaxCount) const;
        ///< read string to newline or to the end of file
    void                   writeLine    (const std::tstring_t &csStr) const;
        ///< write string and end of line
    tchar_t                readChar     () const;
        ///< get character
    void                   writeChar    (const tchar_t &ccChar) const;
        ///< write character
    void                   ungetChar    (const tchar_t &ccChar) const;
        ///< unget character from stream
    void                   clear        () const;
        ///< clear

    // times

    // other
    void                   locking      (const ExLockingMode &clmMode, const long_t &cliBytes);
        ///< locks or unlocks bytes of a file
    void                   setPosition  (const long_t &clOffset, const ExPointerPosition &cppPos) const;
        ///< set stream position indicator
    long_t                 position     () const;
        ///< get current position in stream
    void                   setVBuff     (char *pszBuff, const ExBufferingMode &cbmMode, const size_t &cuiSize) const;
        ///< change stream buffering

#if xOS_ENV_WIN
    void                   setMode      (const ExTranslationMode &tmMode) const;
        ///< sets the file translation mode
#endif

    longlong_t             size         () const;
        ///< get file size
    void                   resize       (const longlong_t &cllSize) const;
        ///< changes the file size

    // error handling
    bool                   isValid      () const;
        ///< validating handle
    bool                   isOpen       () const;
        ///< is open
    bool                   isEmpty      () const;
        ///< is empty
    bool                   isEof        () const;
        ///< check end of file indicator
    bool                   isError      () const;
        ///< check error indicator
    void                   errorClear   () const;
        ///< clear error indicators

    // closing
    void                   flush        () const;
        ///< flush
    void                   close        ();
        ///< close

    // static
    static bool            isFile       (const std::tstring_t &csFilePath);
        ///< check for file
    static bool            isExists     (const std::tstring_t &csFilePath);
        ///< check for existence
    static std::tstring_t  isExistsEx   (const std::tstring_t &csFilePath);
        ///< check for existence, if exists - generate new file name (file path), which not exists
    static void            access       (const std::tstring_t &csFilePath, const ExAccessMode &camMode);
        ///< determine file-access permission
    static void            chmod        (const std::tstring_t &csFilePath, const ExPermissionMode &cpmMode);
        ///< change the file-permission settings
    static void            clear        (const std::tstring_t &csFilePath);
        ///< clear content
    static void            remove       (const std::tstring_t &csFilePath);
        ///< deleting
    static void            tryRemove    (const std::tstring_t &csFilePath, const size_t &cuiAttempts, const ulong_t &culTimeoutMsec);
        ///< try deleting, max 100 attempts
    static void            wipe         (const std::tstring_t &csFilePath, const size_t &cuiPasses);
        ///< wipe
    static void            unlink       (const std::tstring_t &csFilePath);
        ///< deleting
    static void            rename       (const std::tstring_t &csOldFilePath,  const std::tstring_t &csNewFilePath);
        ///< renaming
    static void            move         (const std::tstring_t &csFilePath,     const std::tstring_t &csDirPath);
        ///< move
    static void            copy         (const std::tstring_t &csFilePathFrom, const std::tstring_t &csFilePathTo, const bool &cbFailIfExists);
        ///< copy
    static longlong_t      size         (const std::tstring_t &csFilePath);
        ///< get size
    static ulonglong_t     lines        (const std::tstring_t &csFilePath);
        ///< get number of lines
    static void            time         (const std::tstring_t &csFilePath, time_t *ptmCreate, time_t *ptmAccess, time_t *ptmModified);
        ///< get time
    static void            setTime      (const std::tstring_t &csFilePath, const time_t &ctmCreate, const time_t &ctmAccess, const time_t &ctmModified);
        ///< set time

    // text
    static void            textRead     (const std::tstring_t &csFilePath, std::tstring_t *psContent);
        ///< read to std::tstring_t
    static void            textWrite    (const std::tstring_t &csFilePath, const std::tstring_t &csContent);
        ///< write std::tstring_t
    static void            textRead     (const std::tstring_t &csFilePath, std::vec_tstring_t *pvsContent);
        ///< read to std::vector
    static void            textWrite    (const std::tstring_t &csFilePath, const std::vec_tstring_t &cvsContent);
        ///< write std::vector
    static void            textRead     (const std::tstring_t &csFilePath, const std::tstring_t &csSeparator, std::map_tstring_t *pmsContent);
        ///< read text to std::map
    static void            textWrite    (const std::tstring_t &csFilePath, const std::tstring_t &csSeparator, const std::map_tstring_t &cmsContent);
        ///< write text from std::map

    // binary
    static void            binRead      (const std::tstring_t &csFilePath, std::ustring_t *pusContent);
        ///< read binary data
    static void            binWrite     (const std::tstring_t &csFilePath, const std::ustring_t &cusContent);
        ///< write binary data

private:
    friend class           CxFileTemp;    ///< temporary file

    std::FILE             *_m_pFile;      ///< file handle
    std::tstring_t         _m_sFilePath;  ///< file path

    static int             _nativeHandle(std::FILE *pfFile);
        ///< gets the file descriptor associated with a stream
    static std::FILE *     _stdHandle   (int iFileHandle, const ExOpenMode &omMode);
        ///< get stream by handle
    static std::tstring_t  _openMode    (const ExOpenMode &comMode);
        ///< get open mode as string, by default use "r"
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif  // xLib_Filesystem_CxFileH
