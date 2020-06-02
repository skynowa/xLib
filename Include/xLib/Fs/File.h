/**
 * \file  File.h
 * \brief file
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

class FileType;

class File
    /// file
{
public:
    enum class OpenMode
        /// open mode
    {
        Unknown,            ///< unknown
        Read,               ///< "r"
        Write,              ///< "w"
        Append,             ///< "a"
        OpenReadWrite,      ///< "r+"
        CreateReadWrite,    ///< "w+"
        OpenReadAppend,     ///< "a+"

        BinRead,            ///< "rb"
        BinWrite,           ///< "wb"
        BinAppend,          ///< "ab"
        BinOpenReadWrite,   ///< "rb+"
        BinCreateReadWrite, ///< "wb+"
        BinOpenReadAppend   ///< "ab+"
    };
    xUSING_CONST(OpenMode);

#if xENV_WIN
    enum TranslationMode
        /// translation mode
    {
        Text   = O_TEXT,
        Binary = O_BINARY
    };
    xUSING_CONST(TranslationMode);
#endif

    enum class AccessMode
        /// access mode
    {
        Existence = 0,
        Write     = 2,
        Read      = 4,
        ReadWrite = 6
    };
    xUSING_CONST(AccessMode);

    enum class PointerPosition
        /// pointer position
    {
        Error = - 1L,
        Begin = SEEK_SET,
        Curr  = SEEK_CUR,
        End   = SEEK_END
    };
    xUSING_CONST(PointerPosition);

    enum class BufferingMode
        /// buffering mode
    {
        No   = _IONBF,
        Line = _IOLBF,
        Full = _IOFBF
    };
    xUSING_CONST(BufferingMode);

    enum class LockingMode
        /// locking mode
    {
    #if   xENV_WIN
        Lock    = LK_NBLCK,
        TryLock = LK_LOCK,
        Unlock  = LK_UNLCK
    #elif xENV_UNIX
        Lock    = F_LOCK,
        TryLock = F_TEST,
        Unlock  = F_ULOCK
    #endif
    };
    xUSING_CONST(LockingMode);

    enum class PermissionMode
        /// permission mode
    {
    #if xENV_WIN
        Read             = _S_IREAD,
        Write            = _S_IWRITE,
        ReadWrite        = (_S_IREAD | _S_IWRITE)
    #else
        Read             = S_IRUSR,
        Write            = S_IWUSR,
        ReadWrite        = (S_IRUSR | S_IWUSR),

        SetUserId        = S_ISUID,
        SetGroupId       = S_ISGID,
        StickyBit        = S_ISVTX,

        ExecSearch       = S_IXUSR,

        GroupRead        = S_IRGRP,
        GroupWrite       = S_IWGRP,
        GroupExecSearch  = S_IXGRP,

        OthersRead       = S_IROTH,
        OthersWrite      = S_IWOTH,
        OthersExecSearch = S_IXOTH
    #endif
    };
    xUSING_CONST(PermissionMode);

    // constructors, destructor
    explicit       File(cbool_t isUseBuffering = true);
        ///< constructor
    virtual       ~File();
        ///< destructor

    // open, get
    void_t         create(std::ctstring_t &filePath, cOpenMode mode);
        ///< open
    void_t         reopen(std::ctstring_t &filePath, cOpenMode mode);
        ///< reopen with different file or mode
    HandleStdFile &get() xWARN_UNUSED_RV;
        ///< get handle
    int_t          getNative() const xWARN_UNUSED_RV;
        ///< get native file descriptor associated with a stream
    std::tstring_t path() const xWARN_UNUSED_RV;
        ///< get file path
    void_t         attach(const HandleStdFile &handle, std::ctstring_t &filePath);
        ///< attach to stream
    HandleStdFile &detach() xWARN_UNUSED_RV;
        ///< detach from stream

    // read, write
    size_t         read(void_t *buff, std::csize_t count) const xWARN_UNUSED_RV;
        ///< read block of data
    size_t         write(cptr_cvoid_t, std::csize_t count) const xWARN_UNUSED_RV;
        ///< write block of data
    void_t         read(std::ustring_t *buff) const;
        ///< read to std::ustring_t
    void_t         write(std::custring_t &buff) const;
        ///< write from std::ustring_t
    void_t         read(std::tstring_t *buff) const;
        ///< read to std::tstring_t
    int_t          write(cptr_ctchar_t format, ...) const xWARN_UNUSED_RV;
        ///< write formatted output to stream
    int_t          writeV(cptr_ctchar_t format, va_list arg) const xWARN_UNUSED_RV;
        ///< write formatted variable argument list to stream
    void_t         readLine(std::tstring_t *str, std::csize_t maxCount) const;
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
    void_t         locking(cLockingMode mode, clong_t &bytes);
        ///< locks or unlocks bytes of a file
    void_t         setPosition(clong_t &offset, cPointerPosition &pos) const;
        ///< set stream position indicator
    long_t         position() const xWARN_UNUSED_RV;
        ///< get current position in stream
    void_t         setVBuff(char *buff, cBufferingMode mode, std::csize_t size) const;
        ///< change stream buffering

#if xENV_WIN
    void_t         setMode(cTranslationMode mode) const;
        ///< sets the file translation mode
#endif

    longlong_t     size() const xWARN_UNUSED_RV;
        ///< get file size
    void_t         resize(clonglong_t &size) const;
        ///< changes the file size

    // error handling
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
    void_t         access(std::ctstring_t &filePath, cAccessMode mode);
        ///< determine file-access permission
    static
    void_t         chmod(std::ctstring_t &filePath, cPermissionMode mode);
        ///< change the file-permission settings

    static
    void_t         clear(std::ctstring_t &filePath);
        ///< clear content
    static
    void_t         remove(std::ctstring_t &filePath);
        ///< deleting
    static
    void_t         tryRemove(std::ctstring_t &filePath, std::csize_t attempts, culong_t timeoutMsec);
        ///< try deleting, max 100 attempts
    static
    void_t         wipe(std::ctstring_t &filePath, std::csize_t passes);
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
                       cbool_t &isFailIfExists) /* throw(Exception) */;
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
    void_t         textWrite(std::ctstring_t &filePath, std::ctstring_t &content, cOpenMode mode);
        ///< write std::tstring_t
    static
    void_t         textRead(std::ctstring_t &filePath, std::vec_tstring_t *content);
        ///< read to std::vector
    static
    void_t         textWrite(std::ctstring_t &filePath, std::cvec_tstring_t &content,
                        cOpenMode mode);
        ///< write std::vector
    // TODO: std::map_tstring_t -> std::multimap
    static
    void_t         textRead(std::ctstring_t &filePath, std::ctstring_t &separator,
                       std::map_tstring_t *content);
        ///< read text to std::map
    // TODO: std::map_tstring_t -> std::multimap
    static
    void_t         textWrite(std::ctstring_t &filePath, std::ctstring_t &separator,
                       std::cmap_tstring_t &content, cOpenMode mode);
        ///< write text from std::map

    // binary
    static
    void_t         binRead(std::ctstring_t &filePath, std::ustring_t *content);
        ///< read binary data
    static
    void_t         binWrite(std::ctstring_t &filePath, std::custring_t &content);
        ///< write binary data

private:
    HandleStdFile  _handle;            ///< file handle
    std::tstring_t _filePath;          ///< file path
    cbool_t        _isUseBuffering {}; ///< is use buffering

    static
    int_t          _nativeHandle(std::FILE *file) xWARN_UNUSED_RV;
        ///< gets the file descriptor associated with a stream
    static
    std::FILE*     _stdHandle(int_t fileHandle, cOpenMode mode) xWARN_UNUSED_RV;
        ///< get stream by handle
    static
    std::tstring_t _openMode(cOpenMode mode) xWARN_UNUSED_RV;
        ///< get open mode as string, by default use "r"

    xNO_COPY_ASSIGN(File)

    friend class   FileTemp;  ///< temporary file

xPLATFORM_IMPL:
    static
    bool_t _isFile_impl(const FileType &type) xWARN_UNUSED_RV;
    static
    void_t _time_impl(std::ctstring_t &filePath, time_t *create, time_t *access, time_t *modified);
    static
    void_t _setTime_impl(std::ctstring_t &filePath, const time_t &create, const time_t &access,
				const time_t &modified);
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
