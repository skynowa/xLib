/**
 * \file  CxFile.h
 * \brief file
 */


#ifndef xLib_Filesystem_CxFileH
#define xLib_Filesystem_CxFileH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
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
    virtual              ~CxFile       ();
        ///< destructor

    // open, get
    void_t                create       (std::ctstring_t &csFilePath, const ExOpenMode &omMode, cbool_t &cbIsUseBuffering);
        ///< open
    void_t                reopen       (std::ctstring_t &csFilePath, const ExOpenMode &omMode, cbool_t &cbIsUseBuffering);
        ///< reopen with different file or mode
    std::FILE            *get          () const xWARN_UNUSED_RV;
        ///< get handle
    std::ctstring_t &     path         () const xWARN_UNUSED_RV;
        ///< get file path
    void_t                attach       (std::FILE *pflFile);
        ///< attach to stream
    std::FILE *           detach       () xWARN_UNUSED_RV;
        ///< detach from stream

    // read, write
    size_t                read         (void_t *pvBuff,        std::csize_t &cuiCount) const xWARN_UNUSED_RV;
        ///< read block of data
    size_t                write        (cvoid_t *pcvBuff, std::csize_t &cuiCount) const xWARN_UNUSED_RV;
        ///< write block of data
    void_t                read         (std::ustring_t *psBuff) const;
        ///< read to std::ustring_t
    void_t                write        (std::custring_t &csBuff) const;
        ///< write from std::ustring_t
    void_t                read         (std::tstring_t *psBuff) const;
        ///< read to std::tstring_t
    int_t                 write        (ctchar_t *pcszFormat, ...) const xWARN_UNUSED_RV;
        ///< write formatted output to stream
    int_t                 writeV       (ctchar_t *pcszFormat, va_list arg) const xWARN_UNUSED_RV;
        ///< write formatted variable argument list to stream
    void_t                readLine     (std::tstring_t *psStr, std::csize_t &cuiMaxCount) const;
        ///< read string to newline or to the end of file
    void_t                writeLine    (std::ctstring_t &csStr) const;
        ///< write string and end of line
    tchar_t               readChar     () const xWARN_UNUSED_RV;
        ///< get character
    void_t                writeChar    (ctchar_t &ccChar) const;
        ///< write character
    void_t                ungetChar    (ctchar_t &ccChar) const;
        ///< unget character from stream
    void_t                clear        () const;
        ///< clear

    // times

    // other
    void_t                locking      (const ExLockingMode &clmMode, clong_t &cliBytes);
        ///< locks or unlocks bytes of a file
    void_t                setPosition  (clong_t &clOffset, const ExPointerPosition &cppPos) const;
        ///< set stream position indicator
    long_t                position     () const xWARN_UNUSED_RV;
        ///< get current position in stream
    void_t                setVBuff     (char *pszBuff, const ExBufferingMode &cbmMode, std::csize_t &cuiSize) const;
        ///< change stream buffering

#if xOS_ENV_WIN
    void_t                setMode      (const ExTranslationMode &tmMode) const;
        ///< sets the file translation mode
#endif

    longlong_t            size         () const xWARN_UNUSED_RV;
        ///< get file size
    void_t                resize       (clonglong_t &cllSize) const;
        ///< changes the file size

    // error handling
    bool_t                isValid      () const xWARN_UNUSED_RV;
        ///< validating handle
    bool_t                isOpen       () const xWARN_UNUSED_RV;
        ///< is open
    bool_t                isEmpty      () const xWARN_UNUSED_RV;
        ///< is empty
    bool_t                isEof        () const xWARN_UNUSED_RV;
        ///< check end of file indicator
    bool_t                isError      () const xWARN_UNUSED_RV;
        ///< check error indicator
    void_t                errorClear   () const;
        ///< clear error indicators

    // closing
    void_t                flush        () const;
        ///< flush
    void_t                close        ();
        ///< close

    // static
    static bool_t         isFile       (std::ctstring_t &csFilePath) xWARN_UNUSED_RV;
        ///< check for file
    static bool_t         isExists     (std::ctstring_t &csFilePath) xWARN_UNUSED_RV;
        ///< check for existence
    static std::tstring_t isExistsEx   (std::ctstring_t &csFilePath) xWARN_UNUSED_RV;
        ///< check for existence, if exists - generate new file name (file path), which not exists
    static void_t         access       (std::ctstring_t &csFilePath, const ExAccessMode &camMode);
        ///< determine file-access permission
    static void_t         chmod        (std::ctstring_t &csFilePath, const ExPermissionMode &cpmMode);
        ///< change the file-permission settings
    static void_t         clear        (std::ctstring_t &csFilePath);
        ///< clear content
    static void_t         remove       (std::ctstring_t &csFilePath);
        ///< deleting
    static void_t         tryRemove    (std::ctstring_t &csFilePath, std::csize_t &cuiAttempts, culong_t &culTimeoutMsec);
        ///< try deleting, max 100 attempts
    static void_t         wipe         (std::ctstring_t &csFilePath, std::csize_t &cuiPasses);
        ///< wipe
    static void_t         unlink       (std::ctstring_t &csFilePath);
        ///< deleting
    static void_t         rename       (std::ctstring_t &csOldFilePath,  std::ctstring_t &csNewFilePath);
        ///< renaming
    static void_t         move         (std::ctstring_t &csFilePath,     std::ctstring_t &csDirPath);
        ///< move
    static void_t         copy         (std::ctstring_t &csFilePathFrom, std::ctstring_t &csFilePathTo, cbool_t &cbFailIfExists);
        ///< copy
    static longlong_t     size         (std::ctstring_t &csFilePath) xWARN_UNUSED_RV;
        ///< get size
    static ulonglong_t    lines        (std::ctstring_t &csFilePath) xWARN_UNUSED_RV;
        ///< get number of lines
    static void_t         time         (std::ctstring_t &csFilePath, time_t *ptmCreate, time_t *ptmAccess, time_t *ptmModified);
        ///< get time
    static void_t         setTime      (std::ctstring_t &csFilePath, const time_t &ctmCreate, const time_t &ctmAccess, const time_t &ctmModified);
        ///< set time

    // text
    static void_t         textRead     (std::ctstring_t &csFilePath, std::tstring_t *psContent);
        ///< read to std::tstring_t
    static void_t         textWrite    (std::ctstring_t &csFilePath, std::ctstring_t &csContent);
        ///< write std::tstring_t
    static void_t         textRead     (std::ctstring_t &csFilePath, std::vec_tstring_t *pvsContent);
        ///< read to std::vector
    static void_t         textWrite    (std::ctstring_t &csFilePath, std::cvec_tstring_t &cvsContent);
        ///< write std::vector
    static void_t         textRead     (std::ctstring_t &csFilePath, std::ctstring_t &csSeparator, std::map_tstring_t *pmsContent);
        ///< read text to std::map
    static void_t         textWrite    (std::ctstring_t &csFilePath, std::ctstring_t &csSeparator, std::cmap_tstring_t &cmsContent);
        ///< write text from std::map

    // binary
    static void_t         binRead      (std::ctstring_t &csFilePath, std::ustring_t *pusContent);
        ///< read binary data
    static void_t         binWrite     (std::ctstring_t &csFilePath, std::custring_t &cusContent);
        ///< write binary data

private:
    friend class          CxFileTemp;    ///< temporary file

    std::FILE            *_m_pFile;      ///< file handle
    std::tstring_t        _m_sFilePath;  ///< file path

    static int_t          _nativeHandle(std::FILE *pfFile) xWARN_UNUSED_RV;
        ///< gets the file descriptor associated with a stream
    static std::FILE     *_stdHandle   (int_t iFileHandle, const ExOpenMode &omMode) xWARN_UNUSED_RV;
        ///< get stream by handle
    static std::tstring_t _openMode    (const ExOpenMode &comMode) xWARN_UNUSED_RV;
        ///< get open mode as string, by default use "r"
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif  // xLib_Filesystem_CxFileH
