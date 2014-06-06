/**
 * \file  CxFile.h
 * \brief file
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, filesystem)

class CxFileType;

class CxFile
    /// file
{
public:
    enum ExOpenMode
        /// open mode
    {
        omUnknown,             ///< unknown
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

#if xENV_WIN
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
        #if   xENV_WIN
            lmLock    = LK_NBLCK,
            lmTryLock = LK_LOCK,
            lmUnlock  = LK_UNLCK
        #elif xENV_UNIX
            lmLock    = F_LOCK,
            lmTlock   = F_TLOCK,
            lmTryLock = F_TEST,
            lmUnlock  = F_ULOCK
        #endif
    };

    enum ExPermissionMode
        /// permission mode
    {
        #if xENV_WIN
            pmRead             = _S_IREAD,
            pmWrite            = _S_IWRITE,
            pmReadWrite        = (_S_IREAD | _S_IWRITE)
        #else
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
                   CxFile();
        ///< constructor
    virtual       ~CxFile();
        ///< destructor

    // open, get
    void_t         create(std::ctstring_t &filePath, const ExOpenMode &mode, cbool_t &isUseBuffering);
        ///< open
    void_t         reopen(std::ctstring_t &filePath, const ExOpenMode &mode, cbool_t &isUseBuffering);
        ///< reopen with different file or mode
    std::FILE     *get() const xWARN_UNUSED_RV;
        ///< get handle
    std::ctstring_t & path() const xWARN_UNUSED_RV;
        ///< get file path
    void_t         attach(std::FILE *file);
        ///< attach to stream
    std::FILE *    detach() xWARN_UNUSED_RV;
        ///< detach from stream

    // read, write
    size_t         read(void_t *buff, std::csize_t &count) const xWARN_UNUSED_RV;
        ///< read block of data
    size_t         write(cvoid_t *buff, std::csize_t &count) const xWARN_UNUSED_RV;
        ///< write block of data
    void_t         read(std::ustring_t *buff) const;
        ///< read to std::ustring_t
    void_t         write(std::custring_t &buff) const;
        ///< write from std::ustring_t
    void_t         read(std::tstring_t *buff) const;
        ///< read to std::tstring_t
    int_t          write(ctchar_t *format, ...) const xWARN_UNUSED_RV;
        ///< write formatted output to stream
    int_t          writeV(ctchar_t *format, va_list arg) const xWARN_UNUSED_RV;
        ///< write formatted variable argument list to stream
    void_t         readLine(std::tstring_t *str, std::csize_t &maxCount) const;
        ///< read string to newline or to the end of file
    void_t         writeLine(std::ctstring_t &str) const;
        ///< write string and end of line
    tchar_t        readChar() const xWARN_UNUSED_RV;
        ///< get character
    void_t         writeChar(ctchar_t &ch) const;
        ///< write character
    void_t         ungetChar(ctchar_t &ch) const;
        ///< unget character from stream
    void_t         clear() const;
        ///< clear

    // times

    // other
    void_t         locking(const ExLockingMode &mode, clong_t &bytes);
        ///< locks or unlocks bytes of a file
    void_t         setPosition(clong_t &offset, const ExPointerPosition &pos) const;
        ///< set stream position indicator
    long_t         position() const xWARN_UNUSED_RV;
        ///< get current position in stream
    void_t         setVBuff(char *buff, const ExBufferingMode &mode, std::csize_t &size) const;
        ///< change stream buffering

#if xENV_WIN
    void_t         setMode(const ExTranslationMode &mode) const;
        ///< sets the file translation mode
#endif

    longlong_t     size() const xWARN_UNUSED_RV;
        ///< get file size
    void_t         resize(clonglong_t &size) const;
        ///< changes the file size

    // error handling
    bool_t         isValid() const xWARN_UNUSED_RV;
        ///< validating handle
    bool_t         isOpen() const xWARN_UNUSED_RV;
        ///< is open
    bool_t         isEmpty() const xWARN_UNUSED_RV;
        ///< is empty
    bool_t         isEof() const xWARN_UNUSED_RV;
        ///< check end of file indicator
    bool_t         isError() const xWARN_UNUSED_RV;
        ///< check error indicator
    void_t         errorClear() const;
        ///< clear error indicators

    // closing
    void_t         flush() const;
        ///< flush
    void_t         close();
        ///< close

    // static
    static
    bool_t         isFile(std::ctstring_t &filePath) xWARN_UNUSED_RV;
        ///< check for file
    static
    bool_t         isExists(std::ctstring_t &filePath) xWARN_UNUSED_RV;
        ///< check for existence
    static
    std::tstring_t isExistsEx(std::ctstring_t &filePath) xWARN_UNUSED_RV;
        ///< check for existence, if exists - generate new file name (file path), which not exists
    static
    void_t         access(std::ctstring_t &filePath, const ExAccessMode &mode);
        ///< determine file-access permission
    static
    void_t         chmod(std::ctstring_t &filePath, const ExPermissionMode &mode);
        ///< change the file-permission settings
    static
    void_t         clear(std::ctstring_t &filePath);
        ///< clear content
    static
    void_t         remove(std::ctstring_t &filePath);
        ///< deleting
    static
    void_t         tryRemove(std::ctstring_t &filePath, std::csize_t &attempts,
                       culong_t &timeoutMsec);
        ///< try deleting, max 100 attempts
    static
    void_t         wipe(std::ctstring_t &filePath, std::csize_t &passes);
        ///< wipe
    static
    void_t         unlink(std::ctstring_t &filePath);
        ///< deleting
    static
    void_t         rename(std::ctstring_t &filePathOld,  std::ctstring_t &filePathNew);
        ///< renaming
    static
    void_t         move(std::ctstring_t &filePath, std::ctstring_t &dirPath);
        ///< move
    static
    void_t         copy(std::ctstring_t &filePathFrom, std::ctstring_t &filePathTo,
                       cbool_t &isFailIfExists) /* throw(CxException) */;
        ///< copy
    static
    longlong_t     size(std::ctstring_t &filePath) xWARN_UNUSED_RV;
        ///< get size
    static
    ulonglong_t    lines(std::ctstring_t &filePath) xWARN_UNUSED_RV;
        ///< get number of lines
    static
    void_t         time(std::ctstring_t &filePath, time_t *create, time_t *access, time_t *modified);
        ///< get time
    static
    void_t         setTime(std::ctstring_t &filePath, const time_t &create, const time_t &access,
                       const time_t &modified);
        ///< set time

    // text
    static
    void_t         textRead(std::ctstring_t &filePath, std::tstring_t *content);
        ///< read to std::tstring_t
    static
    void_t         textWrite(std::ctstring_t &filePath, std::ctstring_t &content,
                       const ExOpenMode &mode);
        ///< write std::tstring_t
    static
    void_t         textRead(std::ctstring_t &filePath, std::vec_tstring_t *content);
        ///< read to std::vector
    static
    void_t         textWrite(std::ctstring_t &filePath, std::cvec_tstring_t &content,
                       const ExOpenMode &mode);
        ///< write std::vector
    static
    void_t         textRead(std::ctstring_t &filePath, std::ctstring_t &separator,
                       std::map_tstring_t *content);
        ///< read text to std::map
    static
    void_t         textWrite(std::ctstring_t &filePath, std::ctstring_t &separator,
                       std::cmap_tstring_t &content, const ExOpenMode &mode);
        ///< write text from std::map

    // binary
    static
    void_t         binRead(std::ctstring_t &filePath, std::ustring_t *content);
        ///< read binary data
    static
    void_t         binWrite(std::ctstring_t &filePath, std::custring_t &content);
        ///< write binary data

private:
    friend class   CxFileTemp;  ///< temporary file

    std::FILE     *_handle;     ///< file handle
    std::tstring_t _filePath;   ///< file path

    static
    int_t          _nativeHandle(std::FILE *file) xWARN_UNUSED_RV;
        ///< gets the file descriptor associated with a stream
    static
    std::FILE     *_stdHandle(int_t fileHandle, const ExOpenMode &mode) xWARN_UNUSED_RV;
        ///< get stream by handle
    static
    std::tstring_t _openMode(const ExOpenMode &mode) xWARN_UNUSED_RV;
        ///< get open mode as string, by default use "r"

    xNO_COPY_ASSIGN(CxFile)

xPLATFORM:
    static
    bool_t         _isFile_impl(const CxFileType &type) xWARN_UNUSED_RV;
    static
    void_t         _time_impl(std::ctstring_t &filePath, time_t *create, time_t *access,
                       time_t *modified);
    static
    void_t         _setTime_impl(std::ctstring_t &filePath, const time_t &create,
                       const time_t &access, const time_t &modified);
};

xNAMESPACE_END2(xlib, filesystem)
//-------------------------------------------------------------------------------------------------
#include "CxFile.inl"
