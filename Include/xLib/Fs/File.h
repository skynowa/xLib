/**
 * \file  File.h
 * \brief file
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

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

///@name ctors, dtor
///@{
    explicit File();
    virtual ~File();

    xNO_COPY_ASSIGN(File)
///@}

    // open, get
    void_t         create(std::ctstring_t &filePath, cOpenMode mode, cbool_t isBuffering = true);
        ///< open
    void_t         reopen(std::ctstring_t &filePath, cOpenMode mode, cbool_t isBuffering = true);
        ///< reopen with different file or mode
    HandleStdFile &get();
        ///< get handle
    int_t          getNative() const;
        ///< get native file descriptor associated with a stream
    std::tstring_t path() const;
        ///< get file path
    void_t         attach(const HandleStdFile &handle, std::ctstring_t &filePath);
        ///< attach to stream
    HandleStdFile &detach();
        ///< detach from stream

    // read, write
    size_t         read(void_t *buff, std::csize_t count) const;
        ///< read block of data
    size_t         write(cptr_cvoid_t, std::csize_t count) const;
        ///< write block of data
    void_t         read(std::ustring_t *buff) const;
        ///< read to std::ustring_t
    void_t         write(std::custring_t &buff) const;
        ///< write from std::ustring_t
    void_t         read(std::tstring_t *buff) const;
        ///< read to std::tstring_t
    int_t          write(cptr_ctchar_t format, ...) const;
        ///< write formatted output to stream
    int_t          writeV(cptr_ctchar_t format, va_list arg) const;
        ///< write formatted variable argument list to stream
    void_t         readLine(std::tstring_t *str, std::csize_t maxCount) const;
        ///< read string to newline or to the end of file
    void_t         writeLine(std::ctstring_t &str) const;
        ///< write string and end of line
    tchar_t        readChar() const;
        ///< get character
    void_t         writeChar(ctchar_t &ch) const;
        ///< write character
    void_t         ungetChar(ctchar_t &ch) const;
        ///< unget character from stream
    void_t         clear() const;
        ///< clear

    // other
    void_t         locking(cLockingMode mode, clong_t bytes);
        ///< locks or unlocks bytes of a file
    void_t         setPosition(clong_t offset, cPointerPosition pos) const;
        ///< set stream position indicator
    long_t         position() const;
        ///< get current position in stream
    void_t         setVBuff(char *buff, cBufferingMode mode, std::csize_t size) const;
        ///< change stream buffering

    longlong_t     size() const;
        ///< get file size
    void_t         resize(clonglong_t size) const;
        ///< changes the file size

    // error handling
    bool_t         isEmpty() const;
        ///< is empty
    bool_t         isEof() const;
        ///< check end of file indicator
    bool_t         isError() const;
        ///< check error indicator
    void_t         errorClear() const;
        ///< clear error indicators

    // closing
    void_t         flush() const;
        ///< flush
    void_t         close();
        ///< close

    // actions
    void_t         remove();
        ///< deleting
    void_t         tryRemove(std::csize_t attempts, culong_t timeoutMsec);
        ///< try deleting, max 100 attempts
    void_t         wipe(std::csize_t passes);
        ///< wipe
    void_t         unlink();
        ///< deleting
    void_t         rename(std::ctstring_t &filePathNew);
        ///< renaming
    void_t         move(std::ctstring_t &dirPath);
        ///< move
    void_t         copy(std::ctstring_t &filePathTo, cbool_t isFailIfExists) const
                        /* throw(Exception) */;
        ///< copy

xPUBLIC_STATIC:
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

    static
    int_t          _nativeHandle(std::FILE *file);
        ///< gets the file descriptor associated with a stream
    static
    std::FILE*     _stdHandle(int_t fileHandle, cOpenMode mode);
        ///< get stream by handle
    static
    std::tstring_t _openMode(cOpenMode mode);
        ///< get open mode as string, by default use "r"

    friend class FileTemp;  ///< temporary file
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
// TODO: [skynowa] _filePath invariants - rm for constmembers
// TODO: [skynowa] get objects (Path, FileInfo)
// TODO: [skynowa] actions methods - big in using
// TODO: [skynowa] static methods - as utils class

// TODO: [skynowa] - xNO ...
// xNO_DEFAULT_CONSTRUCT(Path)
// xNO_COPY_ASSIGN(Path)
//-------------------------------------------------------------------------------------------------
