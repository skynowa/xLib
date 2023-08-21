/**
 * \file  FileIO.h
 * \brief File input/output
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

class FileIO
    /// File input/output
{
public:
    enum class OpenMode
        /// Open mode
    {
        // Text
        ReadOnly,         ///< "r" (no file - error)
        Write,            ///< "w" (no file - create)
        Append,           ///< "a" (no file - create)

        ReadWriteOnly,    ///< "r+" (no file - error)
        ReadWrite,        ///< "w+" (no file - create)
        ReadAppend,       ///< "a+" (no file - create)

		// Binary
        BinReadOnly,      ///< "rb" (no file - error)
        BinWrite,         ///< "wb" (no file - create)
        BinAppend,        ///< "ab" (no file - create)

        BinReadWriteOnly, ///< "rb+" (no file - error)
        BinReadWrite,     ///< "wb+" (no file - create)
        BinReadAppend     ///< "ab+" (no file - create)
    };
    xUSING_CONST(OpenMode);

    enum class PointerPosition
        /// Pointer position
    {
        Error = - 1L,
        Begin = SEEK_SET,
        Curr  = SEEK_CUR,
        End   = SEEK_END
    };
    xUSING_CONST(PointerPosition);

    enum class BufferingMode
        /// Buffering mode
    {
        No   = _IONBF,
        Line = _IOLBF,
        Full = _IOFBF
    };
    xUSING_CONST(BufferingMode);

    enum class LockingMode
        /// Locking mode
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

///\name ctors, dtor
///\{
    explicit FileIO(std::ctstring_t &filePath);
    virtual ~FileIO();

    xNO_DEFAULT_CONSTRUCT(FileIO)
    xNO_COPY_ASSIGN(FileIO)
///\}

///\name open, get
///\{
	void_t         open(cOpenMode mode, cbool_t isBuffering = true);
		///< open
	HandleStdFile &get();
		///< get handle
	int_t          getNative() const;
		///< get native file descriptor associated with a stream
	std::tstring_t path() const;
		///< get file path
///\}

///\name read, write
///\{
	void_t         setVBuff(cBufferingMode mode, char *buff, std::csize_t size) const;
		///< change stream buffering
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
	int_t          scanf(cptr_ctchar_t format, ...) const;
		///< read formatted variables (as vfscanf)
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
	void_t         writeChar(ctchar_t ch) const;
		///< write character
	void_t         ungetChar(ctchar_t ch) const;
		///< unget character from stream
	void_t         clear() const;
		///< clear content
///\}

///\name other
///\{
	void_t         locking(cLockingMode mode, clong_t bytes);
		///< locks or unlocks bytes of a file
	void_t         setPosition(clong_t offset, cPointerPosition pos) const;
		///< set stream position indicator
	long_t         position() const;
		///< get current position in stream

    longlong_t     size() const;
        ///< get file size
    bool_t         isEmpty() const;
        ///< is empty
    void_t         setSize(clonglong_t bytes) const;
        ///< changes the file size
///\}

///\name error handling
///\{
	bool_t         isEof() const;
		///< check end of file indicator
	bool_t         isError() const;
		///< check error indicator
	void_t         clearError() const;
		///< clear error indicators
///\}

///\name closing
///\{
	void_t         flush() const;
		///< flush
	void_t         close();
		///< close
///\}

private:
    HandleStdFile   _handle;   ///< file handle
    std::ctstring_t _filePath; ///< file path

	void_t _setVBuffDefault(cbool_t isBuffering) const;
		///< change stream buffering with deafault buffer size

xPRIVATE_STATIC:
    static int_t          _nativeHandle(std::FILE *file);
        ///< gets the file descriptor associated with a stream
    static std::FILE*     _stdHandle(cint_t fileHandle, cOpenMode mode);
        ///< get stream by handle
    static std::tstring_t _openMode(cOpenMode mode);
        ///< get open mode as string, by default use "r"
};

} // namespace
//-------------------------------------------------------------------------------------------------
// TODO: [skynowa] get objects (Path, FileInfo)
//-------------------------------------------------------------------------------------------------
