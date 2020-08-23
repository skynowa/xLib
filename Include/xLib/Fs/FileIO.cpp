/**
 * \file  FileIO.cpp
 * \brief File input/output
 */


#include "FileIO.h"

#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/FileInfo.h>
#include <xLib/Fs/FileType.h>


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    public: constructors, destructor
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
FileIO::FileIO()
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
FileIO::~FileIO()
{
    close();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: open, get
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
FileIO::create(
    std::ctstring_t &a_filePath,
    cOpenMode        a_mode,
    cbool_t          a_isBuffering /* = true */
)
{
    xTEST(!a_filePath.empty());
    xTEST_NA(a_mode);
    xTEST_NA(a_isBuffering);

    // create dir
    Dir( Path(a_filePath).dir() ).pathCreate();

    // create, open file
    {
        std::FILE *file = xTFOPEN(a_filePath.c_str(), _openMode(a_mode).c_str());
        xTEST_PTR(file);

        _handle   = file;
        _filePath = a_filePath;
    }

    // buffering
    _setVBuffDefault(a_isBuffering);
}
//-------------------------------------------------------------------------------------------------
void_t
FileIO::reopen(
    std::ctstring_t &a_filePath,
    cOpenMode        a_mode,
    cbool_t          a_isBuffering /* = true */
)
{
    xTEST(!a_filePath.empty());
    xTEST_NA(a_mode);
	xTEST_NA(a_isBuffering);

    // create dir
    Dir( Path(a_filePath).dir() ).pathCreate();

    // create, reopen file
    {
        std::FILE *file = xTFREOPEN(a_filePath.c_str(), _openMode(a_mode).c_str(), _handle.get());
        xTEST_PTR(file);

        _handle   = file;
        _filePath = a_filePath;
    }

    // buffering
    _setVBuffDefault(a_isBuffering);
}
//-------------------------------------------------------------------------------------------------
HandleStdFile &
FileIO::get()
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
int_t
FileIO::getNative() const
{
    xTEST(_handle.isValid());

    return _nativeHandle( _handle.get() );
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
FileIO::path() const
{
    xTEST(!_filePath.empty());
    xTEST(FileInfo(_filePath).isExists());

    return _filePath;
}
//-------------------------------------------------------------------------------------------------
void_t
FileIO::attach(
    const HandleStdFile &a_handle,
    std::ctstring_t     &a_filePath
)
{
    xTEST(a_handle.isValid());
    xTEST_NA(a_filePath);

    close();

    _handle   = a_handle;
    _filePath = a_filePath;
}
//-------------------------------------------------------------------------------------------------
HandleStdFile &
FileIO::detach()
{
    HandleStdFile &handle = _handle;

    _handle = nullptr;
    _filePath.clear();

    return handle;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
* public: read / write
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
FileIO::setVBuff(
    cBufferingMode a_mode,
    char          *a_buff,
    std::csize_t   a_size
) const
{
    xTEST_NA(a_mode);
    xTEST_NA(a_buff);
    xTEST_NA(a_size);

    int_t iRv = std::setvbuf(_handle.get(), a_buff, static_cast<int>(a_mode), a_size);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
size_t
FileIO::read(
    void_t       *a_buff,
    std::csize_t  a_count
) const
{
    xTEST_PTR(a_buff);
    xTEST_NA(a_count);

    size_t uiRv = std::fread(a_buff, 1, a_count, _handle.get());
    xTEST_GR_EQ(a_count, uiRv);

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
size_t
FileIO::write(
    cptr_cvoid_t a_buff,
    std::csize_t a_count
) const
{
    xTEST_PTR(a_buff);
    xTEST_NA(a_count);

    size_t uiRv = std::fwrite(a_buff, 1, a_count, _handle.get());
    xTEST_EQ(uiRv, a_count);

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
void_t
FileIO::read(
    std::ustring_t *a_buff
) const
{
    xTEST_PTR(a_buff);

    clonglong_t fileSize = size();
    xTEST_DIFF(fileSize, static_cast<longlong_t>(PointerPosition::Error));

    a_buff->clear();
    a_buff->resize( static_cast<size_t>(fileSize) );
    xCHECK_DO(fileSize == 0LL, return);

    size_t uiRv = std::fread(&a_buff->at(0), 1, a_buff->size() *
        sizeof(std::ustring_t::value_type), _handle.get());
    xTEST_EQ(uiRv, a_buff->size());
}
//-------------------------------------------------------------------------------------------------
void_t
FileIO::write(
    std::custring_t &a_buff
) const
{
    xTEST_NA(a_buff);

    size_t uiRv = std::fwrite(&a_buff.at(0), 1, a_buff.size() *
        sizeof(std::ustring_t::value_type), _handle.get());
    xTEST_EQ(uiRv, a_buff.size());
}
//-------------------------------------------------------------------------------------------------
void_t
FileIO::read(
    std::tstring_t *a_buff
) const
{
    xTEST_PTR(a_buff);

    clonglong_t fileSize = size();
    xTEST_DIFF(static_cast<longlong_t>(PointerPosition::Error), fileSize);

    a_buff->clear();
    a_buff->resize( static_cast<size_t>( fileSize) );
    xCHECK_DO(fileSize == 0LL, return);

    size_t uiRv = std::fread(&a_buff->at(0), 1, a_buff->size() *
        sizeof(std::tstring_t::value_type), _handle.get());
    xTEST_EQ(uiRv, a_buff->size());
}
//-------------------------------------------------------------------------------------------------
int_t
FileIO::write(
    cptr_ctchar_t a_format, ...
) const
{
    xTEST_PTR(a_format);

    va_list args;
    xVA_START(args, a_format);

    int_t iRv = xTVFPRINTF(_handle.get(), a_format, args);
    xTEST_LESS(- 1, iRv);

    xVA_END(args);

    return iRv;
}
//-------------------------------------------------------------------------------------------------
int_t
FileIO::writeV(
    cptr_ctchar_t a_format,
    va_list       a_args
) const
{
    xTEST_PTR(a_format);
    xTEST_NA(a_args);

    int_t iRv = xTVFPRINTF(_handle.get(), a_format, a_args);
    xTEST_LESS(- 1, iRv);

    return iRv;
}
//-------------------------------------------------------------------------------------------------
void_t
FileIO::readLine(
    std::tstring_t *a_str,
    std::csize_t    a_maxCount
) const
{
    xTEST_PTR(a_str);
    xTEST_NA(a_maxCount);

    std::tstring_t str;
    str.resize(a_maxCount + 1); // + 1 for 0

    tchar_t *pszRv = xTFGETS(&str.at(0), static_cast<int_t>( str.size() ), _handle.get());
    xTEST_PTR(pszRv);

    // trim nullptr's from string, remove EOL
    str = String::removeEol( str.c_str() );

    // [out]
    a_str->swap(str);
}
//-------------------------------------------------------------------------------------------------
void_t
FileIO::writeLine(
    std::ctstring_t &a_str
) const
{
    xTEST_NA(a_str);

    int_t iRv = xTFPUTS((a_str + Const::eol()).c_str(), _handle.get());
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
tchar_t
FileIO::readChar() const
{
    twint_t iRv = xTFGETC(_handle.get());
    xTEST_DIFF(iRv, xTEOF);

    return static_cast<tchar_t>(iRv);
}
//-------------------------------------------------------------------------------------------------
void_t
FileIO::writeChar(
    ctchar_t &a_ch
) const
{
    xTEST_NA(a_ch);

    twint_t iRv = xTFPUTC(a_ch, _handle.get());
    xTEST_DIFF(iRv, xTEOF);
    xTEST_EQ(static_cast<tchar_t>(iRv), a_ch);
}
//-------------------------------------------------------------------------------------------------
void_t
FileIO::ungetChar(
    ctchar_t &a_ch
) const
{
    xTEST_NA(a_ch);

    twint_t iRv = xTUNGETC(a_ch, _handle.get());
    xTEST_DIFF(iRv, xTEOF);
    xTEST_EQ(static_cast<tchar_t>(iRv), a_ch);
}
//-------------------------------------------------------------------------------------------------
void_t
FileIO::clear() const
{
    setSize(0L);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: other
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
FileIO::locking(
    cLockingMode a_mode,
    clong_t      a_bytes
)
{
    xTEST_NA(a_mode);
    xTEST_NA(a_bytes);

#if   xENV_WIN
    clong_t    bytes = a_bytes;
#elif xENV_UNIX
    const auto bytes = static_cast<off_t>(a_bytes);
#endif

    int_t iRv = xLOCKING(_nativeHandle(_handle.get()), static_cast<int>(a_mode), bytes);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
void_t
FileIO::setPosition(
    clong_t          a_offset,
    cPointerPosition a_pos
) const
{
    xTEST_NA(a_offset);
    xTEST_NA(a_pos);

    int_t iRv = std::fseek(_handle.get(), a_offset, static_cast<int>(a_pos));
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
long_t
FileIO::position() const
{
    long_t liRv = std::ftell(_handle.get());
    xTEST_DIFF(liRv, - 1L);

    return liRv;
}
//-------------------------------------------------------------------------------------------------
longlong_t
FileIO::size() const
{
    clong_t currStreamPos = position();
    setPosition(0, PointerPosition::End);

    clong_t streamSize = position();
    setPosition(currStreamPos, PointerPosition::Begin);

    return static_cast<longlong_t>( streamSize );
}
//-------------------------------------------------------------------------------------------------
void_t
FileIO::setSize(
    clonglong_t a_bytes
) const
{
    xTEST_NA(a_bytes);

#if   xENV_WIN
    clonglong_t _bytes = a_bytes;
#elif xENV_UNIX
    const auto  _bytes = static_cast<off_t>(a_bytes);
#endif

    int_t iRv = xCHSIZE(_nativeHandle( _handle.get() ), _bytes);
    xTEST_EQ(iRv, 0);
    xTEST_EQ(size(), a_bytes);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: error handling
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
FileIO::isEmpty() const
{
    clonglong_t fileSize = size();
    xTEST_DIFF(fileSize, - 1LL);

    return (fileSize == 0LL);
}
//-------------------------------------------------------------------------------------------------
bool_t
FileIO::isEof() const
{
    return static_cast<bool_t>( std::feof(_handle.get()) );
}
//-------------------------------------------------------------------------------------------------
bool_t
FileIO::isError() const
{
    return static_cast<bool_t>( std::ferror(_handle.get()) );
}
//-------------------------------------------------------------------------------------------------
void_t
FileIO::clearError() const
{
    (void_t)std::clearerr( _handle.get() );
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: closing
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
FileIO::flush() const
{
    twint_t iRv = std::fflush( _handle.get() );
    xTEST_DIFF(iRv, xTEOF);
}
//-------------------------------------------------------------------------------------------------
void_t
FileIO::close()
{
    xCHECK_DO(!_handle.isValid(), return);

    clearError();

    _handle.close();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
int_t
FileIO::_nativeHandle(
    std::FILE *a_file
)
{
    xTEST_PTR(a_file);

    int_t iRv = /*::*/fileno(a_file);
    xTEST_DIFF(iRv, - 1);

    return iRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::FILE *
FileIO::_stdHandle(
    int_t     a_fileHandle,
    cOpenMode a_mode
)
{
    xTEST_NA(a_fileHandle);
    xTEST_NA(a_mode);

    std::FILE *pfRv = xTFDOPEN(a_fileHandle, _openMode(a_mode).c_str());
    xTEST_PTR(pfRv);

    return pfRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
FileIO::_openMode(
    cOpenMode a_mode
)
{
    xTEST_NA(a_mode);

	static const std::map<OpenMode, std::tstring_t> modes
	{
		// Text
		{OpenMode::ReadOnly,         xT("r")},
		{OpenMode::Write,            xT("w")},
		{OpenMode::Append,           xT("a")},

		{OpenMode::ReadWriteOnly,    xT("r+")},
		{OpenMode::ReadWrite,        xT("w+")},
		{OpenMode::ReadAppend,       xT("a+")},

		// Binary
		{OpenMode::BinReadOnly,      xT("rb")},
		{OpenMode::BinWrite,         xT("wb")},
		{OpenMode::BinAppend,        xT("ab")},

		{OpenMode::BinReadWriteOnly, xT("rb+")},
		{OpenMode::BinReadWrite,     xT("wb+")},
		{OpenMode::BinReadAppend,    xT("ab+")}
	};

	auto it = modes.find(a_mode);
	xCHECK_RET(it == modes.cend(), std::tstring_t());

	return it->second;
}
//-------------------------------------------------------------------------------------------------
void_t
FileIO::_setVBuffDefault(
	cbool_t a_isBuffering
) const
{
    const BufferingMode mode     = a_isBuffering ? BufferingMode::Full : BufferingMode::No;
    std::csize_t        buffSize = a_isBuffering ? BUFSIZ              : 0;

    setVBuff(mode, nullptr, buffSize);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
