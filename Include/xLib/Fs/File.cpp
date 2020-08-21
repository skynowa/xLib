/**
 * \file  File.inl
 * \brief file
 */


#include "File.h"

#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Locale.h>
#include <xLib/Core/DateTime.h>
#include <xLib/Core/Utils.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/FileInfo.h>
#include <xLib/Fs/FileType.h>
#include <xLib/Crypt/Random.h>
#include <xLib/Sync/Thread.h>


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    public: constructors, destructor
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
File::File()
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
File::~File()
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
File::create(
    std::ctstring_t &a_filePath,
    cOpenMode        a_mode,
    cbool_t          a_isBuffering /* = true */
)
{
    xTEST(!a_filePath.empty());
    xTEST_NA(a_mode);

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
    if (a_isBuffering) {
        setVBuff(nullptr, BufferingMode::Full, BUFSIZ);
    } else {
        setVBuff(nullptr, BufferingMode::No,   0);
    }
}
//-------------------------------------------------------------------------------------------------
void_t
File::reopen(
    std::ctstring_t &a_filePath,
    cOpenMode        a_mode,
    cbool_t          a_isBuffering /* = true */
)
{
    xTEST(!a_filePath.empty());
    xTEST_NA(a_mode);

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
    if (a_isBuffering) {
        setVBuff(nullptr, BufferingMode::Full, BUFSIZ);
    } else {
        setVBuff(nullptr, BufferingMode::No,   0);
    }
}
//-------------------------------------------------------------------------------------------------
HandleStdFile &
File::get()
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
int_t
File::getNative() const
{
    xTEST(_handle.isValid());

    return _nativeHandle( _handle.get() );
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
File::path() const
{
    xTEST(!_filePath.empty());
    xTEST(FileInfo(_filePath).isExists());

    return _filePath;
}
//-------------------------------------------------------------------------------------------------
void_t
File::attach(
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
File::detach()
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
size_t
File::read(
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
File::write(
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
File::read(
    std::ustring_t *a_buff
) const
{
    xTEST_PTR(a_buff);

    clonglong_t fileSize = size();
    xTEST_DIFF(static_cast<longlong_t>( PointerPosition::Error ), fileSize);

    a_buff->clear();
    a_buff->resize( static_cast<size_t>(fileSize) );
    xCHECK_DO(fileSize == 0LL, return);

    size_t uiRv = std::fread(&a_buff->at(0), 1, a_buff->size() *
        sizeof(std::ustring_t::value_type), _handle.get());
    xTEST_EQ(uiRv, a_buff->size());
}
//-------------------------------------------------------------------------------------------------
void_t
File::write(
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
File::read(
    std::tstring_t *a_buff
) const
{
    xTEST_PTR(a_buff);

    clonglong_t fileSize = size();
    xTEST_DIFF(static_cast<longlong_t>( PointerPosition::Error ), fileSize);

    a_buff->clear();
    a_buff->resize( static_cast<size_t>( fileSize) );
    xCHECK_DO(fileSize == 0LL, return);

    size_t uiRv = std::fread(&a_buff->at(0), 1, a_buff->size() *
        sizeof(std::tstring_t::value_type), _handle.get());
    xTEST_EQ(uiRv, a_buff->size());
}
//-------------------------------------------------------------------------------------------------
int_t
File::write(
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
File::writeV(
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
File::readLine(
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
File::writeLine(
    std::ctstring_t &a_str
) const
{
    xTEST_NA(a_str);

    int_t iRv = xTFPUTS((a_str + Const::eol()).c_str(), _handle.get());
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
tchar_t
File::readChar() const
{
    twint_t iRv = xTFGETC(_handle.get());
    xTEST_DIFF(iRv, xTEOF);

    return static_cast<tchar_t>(iRv);
}
//-------------------------------------------------------------------------------------------------
void_t
File::writeChar(
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
File::ungetChar(
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
File::clear() const
{
    resize(0L);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: other
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
File::locking(
    cLockingMode a_mode,
    clong_t     &a_bytes
)
{
    xTEST_NA(a_mode);
    xTEST_NA(a_bytes);

#if   xENV_WIN
    clong_t     bytes = a_bytes;
#elif xENV_UNIX
    const off_t bytes = static_cast<off_t>(a_bytes);
#endif

    int_t iRv = xLOCKING(_nativeHandle(_handle.get()), static_cast<int>(a_mode), bytes);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
void_t
File::setPosition(
    clong_t          &a_offset,
    cPointerPosition &a_pos
) const
{
    xTEST_NA(a_offset);
    xTEST_NA(a_pos);

    int_t iRv = std::fseek(_handle.get(), a_offset, static_cast<int>(a_pos));
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
long_t
File::position() const {
    long_t liRv = std::ftell(_handle.get());
    xTEST_DIFF(liRv, - 1L);

    return liRv;
}
//-------------------------------------------------------------------------------------------------
void_t
File::setVBuff(
    char          *a_buff,
    cBufferingMode a_mode,
    std::csize_t   a_size
) const
{
    xTEST_NA(a_buff);
    xTEST_NA(a_mode);
    xTEST_NA(a_size);

    int_t iRv = std::setvbuf(_handle.get(), a_buff, static_cast<int>(a_mode), a_size);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
longlong_t
File::size() const
{
    clong_t currStreamPos = position();
    setPosition(0, PointerPosition::End);

    clong_t streamSize = position();
    setPosition(currStreamPos, PointerPosition::Begin);

    return static_cast<longlong_t>( streamSize );
}
//-------------------------------------------------------------------------------------------------
void_t
File::resize(
    clonglong_t &a_size
) const
{
    xTEST_NA(a_size);

#if   xENV_WIN
    clonglong_t _size = a_size;
#elif xENV_UNIX
    const off_t _size = static_cast<off_t>(a_size);
#endif

    int_t iRv = xCHSIZE(_nativeHandle( _handle.get() ), _size);
    xTEST_EQ(iRv, 0);
    xTEST_EQ(a_size, size());
}
//-------------------------------------------------------------------------------------------------

/**************************************************************************************************
*    public: error handling
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
File::isEmpty() const
{
    clonglong_t fileSize = size();
    xTEST_DIFF(fileSize, - 1LL);

    return (fileSize == 0LL);
}
//-------------------------------------------------------------------------------------------------
bool_t
File::isEof() const
{
    return static_cast<bool_t>( std::feof(_handle.get()) );
}
//-------------------------------------------------------------------------------------------------
bool_t
File::isError() const
{
    return static_cast<bool_t>( std::ferror(_handle.get()) );
}
//-------------------------------------------------------------------------------------------------
void_t
File::errorClear() const
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
File::flush() const
{
    twint_t iRv = std::fflush( _handle.get() );
    xTEST_DIFF(iRv, xTEOF);
}
//-------------------------------------------------------------------------------------------------
void_t
File::close()
{
    xCHECK_DO(!_handle.isValid(), return);

    errorClear();

    _handle.close();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, actions
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
File::remove()
{
    xTEST(!_filePath.empty());

    close();

    FileInfo info(_filePath);
    xCHECK_DO(!info.isExists(), return);

    // TODO: [skynowa] maybe not work ?
    info.chmod(FileInfo::PermissionMode::Write);

    int_t iRv = xTREMOVE(_filePath.c_str());
    xTEST_DIFF(iRv, - 1);
    xTEST(!info.isExists());
}
//-------------------------------------------------------------------------------------------------
void_t
File::tryRemove(
    std::csize_t a_attempts,
    culong_t     a_timeoutMsec
)
{
    xTEST(!_filePath.empty());
    xTEST_GR(a_attempts, size_t(0U));
    xTEST_NA(a_timeoutMsec);

    std::csize_t attemptsMax  {100};  // MAGIC_NUMBER: attemptsMax
    std::csize_t attemptsReal {attemptsMax < a_attempts ? attemptsMax : a_attempts};

    for (size_t i = 0; i < attemptsReal; ++ i) {
        xTRY {
            remove();
            xCHECK_DO(!FileInfo(_filePath).isExists(), break);
        }
        xCATCH_ALL

        Thread::currentSleep(a_timeoutMsec);
    }
}
//-------------------------------------------------------------------------------------------------
void_t
File::wipe(
    std::csize_t a_passes
)
{
    xTEST(!_filePath.empty());
    xTEST_NA(a_passes);

    FileInfo info(_filePath);
    xCHECK_DO(!info.isExists(), return);

	// attributes - reset
	{
		FileType(_filePath).clear();
	}

	// content - reset
	clonglong_t fileSize = size();
	if (fileSize > 0LL) {
		// fill by 0x55, 0xAA, random char
		for (size_t p {}; p < a_passes; ++ p) {
			cuchar_t rand  { NativeRandom().nextChar<uchar_t>() };
			cuchar_t char1 {0x55};
			cuchar_t char2 {0xAA};

			// rand
			{
				setPosition(0L, PointerPosition::Begin);

				for (longlong_t i {}; i < fileSize; ++ i) {
					std::csize_t uiRv = std::fwrite(&rand, 1, sizeof(rand), get().get());
					xTEST_EQ(uiRv, sizeof(rand));
				}
			}

			// char1
			{
				setPosition(0L, PointerPosition::Begin);

				for (longlong_t i {}; i < fileSize; ++ i) {
					std::csize_t uiRv = std::fwrite(&char1, 1, sizeof(char1), get().get());
					xTEST_EQ(uiRv, sizeof(char1));
				}
			}

			// char2
			{
				setPosition(0L, PointerPosition::Begin);

				for (longlong_t i {}; i < fileSize; ++ i) {
					std::csize_t uiRv = std::fwrite(&char2, 1, sizeof(char2), get().get());
					xTEST_EQ(uiRv, sizeof(char2));
				}
			}
		} // if (size > 0LL)

		// truncate
		flush();
		clear();
	} // if (fileSize)

    // file time - reset
    {
        const time_t create   {};
        const time_t access   {};
        const time_t modified {};

        info.setTime(create, access, modified);
    }

    // file name - randomize
    std::tstring_t randFilePath;
    {
        std::tstring_t randFileName = String::cast( DateTime().current().toMsec() );
        std::random_shuffle(randFileName.begin(), randFileName.end());

        randFilePath = Path(_filePath).dir() + Const::slash() + randFileName;

        rename(randFilePath);
    }

	remove();
}
//-------------------------------------------------------------------------------------------------
void_t
File::unlink()
{
    xTEST(!_filePath.empty());

    close();

    int_t iRv = xTUNLINK(_filePath.c_str());
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
void_t
File::rename(
    std::ctstring_t &a_filePathNew
)
{
    xTEST(!_filePath.empty());
    xTEST(!a_filePathNew.empty());

    // TODO: [skynowa] close();

    int_t iRv = xTRENAME(_filePath.c_str(), a_filePathNew.c_str());
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
void_t
File::move(
    std::ctstring_t &a_dirPath
)
{
    xTEST(!_filePath.empty());
    xTEST(!a_dirPath.empty());

    // TODO: [skynowa] close();

    rename(Path(a_dirPath).slashAppend() + Path(_filePath).fileName());
}
//-------------------------------------------------------------------------------------------------
void_t
File::copy(
    std::ctstring_t &a_filePathTo,
    cbool_t          a_isFailIfExists
) const /* throw(Exception) */
{
    xTEST(!_filePath.empty());
    xTEST(!a_filePathTo.empty());
    xTEST_NA(a_isFailIfExists);

    bool_t isCopyOk {true};

    // errors
    std::ctstring_t errorDestFileExists = xT("File - Destination file is exists");
    std::ctstring_t errorCopyFail       = xT("File - Copy fail");
    std::ctstring_t errorFilesDiffrent  = xT("File - Files are diffrent");

    xCHECK_DO(a_isFailIfExists && FileInfo(a_filePathTo).isExists(),
        xTHROW_REPORT(errorDestFileExists));

    // copy
	File fileFrom;
	File fileTo;
    {
        // open files
        fileFrom.create(_filePath, OpenMode::BinRead);
        fileTo.create(a_filePathTo, OpenMode::BinWrite);

        if ( !FileInfo(fileFrom).isEmpty() ) {
            // copy files
            constexpr std::size_t buffSize       {1024};
            uchar_t               buff[buffSize] {};

            for ( ; ; ) {
                std::csize_t readed  = fileFrom.read(buff, buffSize);
                xCHECK_DO(0 >= readed, break);

                std::csize_t written = fileTo.write(buff, readed);
                xCHECK_DO(readed != written, isCopyOk = false; break);
            }
        }

        fileTo.flush();
    }

	// checks
	{
		if (!isCopyOk) {
			File file;
			file.create(a_filePathTo, File::OpenMode::Write);
			file.remove();

			xTHROW_REPORT(errorCopyFail);
		}

		if (FileInfo(fileFrom).size() != FileInfo(fileTo).size()) {
			File file;
			file.create(a_filePathTo, File::OpenMode::Write);
			file.remove();

			xTHROW_REPORT(errorFilesDiffrent);
		}
	}
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: text
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
void_t
File::textRead(
    std::ctstring_t &a_filePath,
    std::tstring_t  *a_content
)
{
    xTEST(!a_filePath.empty());
    xTEST_PTR(a_content);

    std::tstring_t sRv;

    File file;
    file.create(a_filePath, OpenMode::BinRead);

    clonglong_t fileSize = file.size();
    xTEST_DIFF(fileSize, static_cast<longlong_t>(PointerPosition::Error));

    xCHECK_DO(fileSize == 0LL, a_content->clear(); return);

    sRv.resize( static_cast<size_t>(fileSize) );

    std::csize_t readLen = file.read((void_t *)&sRv.at(0), sRv.size());
    xTEST_EQ(readLen, sRv.size());

    // out
    a_content->swap(sRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
File::textWrite(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_content,
    cOpenMode        a_mode
)
{
    xTEST(!a_filePath.empty());
    xTEST_NA(a_content);
    xTEST(a_mode != OpenMode::Unknown);

    File file;
    file.create(a_filePath, a_mode);

    xCHECK_DO(a_content.empty(), return);

    std::csize_t writeLen = file.write((void_t *)&a_content.at(0), a_content.size());
    xTEST_EQ(writeLen, a_content.size());
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
File::textRead(
    std::ctstring_t    &a_filePath,
    std::vec_tstring_t *a_content
)
{
    xTEST(!a_filePath.empty());
    xTEST(FileInfo(a_filePath).isExists());
    xTEST_PTR(a_content);

    std::tstring_t content;
    textRead(a_filePath, &content);

    std::vec_tstring_t vsRv;
    String::split(content, Const::nl(), &vsRv);

    // out
    a_content->swap(vsRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
File::textWrite(
    std::ctstring_t     &a_filePath,
    std::cvec_tstring_t &a_content,
    cOpenMode            a_mode
)
{
    xTEST(!a_filePath.empty());
    xTEST_NA(a_content);
    xTEST(a_mode != OpenMode::Unknown);

    std::tstring_t content;

    content = String::join(a_content, Const::nl());

    textWrite(a_filePath, content, a_mode);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
File::textRead(
    std::ctstring_t    &a_filePath,
    std::ctstring_t    &a_separator,
    std::map_tstring_t *a_content
)
{
    xTEST(!a_filePath.empty());
    xTEST(FileInfo(a_filePath).isExists());
    xTEST_PTR(a_content);

    // if file empty
    xCHECK_DO(FileInfo(a_filePath).size() == 0L, a_content->clear(); return);

    std::locale::global( std::locale() );

    std::tifstream_t ifs(xT2A(a_filePath));
    xTEST(!! ifs);
    xTEST(!ifs.fail());
    xTEST(ifs.good());
    xTEST(ifs.is_open());
    xTEST(!ifs.eof());

    std::map_tstring_t msRv;
    std::tstring_t     line;
    std::vec_tstring_t lines;

    for (size_t i = 0; !ifs.eof(); ++ i) {
        std::getline(ifs, line);
        line = String::trimRightChars(line, Const::eol());

        if ( line.empty() ) {
            auto prRv = msRv.insert( {Const::strEmpty(), Const::strEmpty()} );
            xTEST_NA(prRv);
        } else {
            String::split(line, a_separator, &lines);
            xTEST_EQ(lines.size(), size_t(2));

            auto prRv = msRv.insert( {lines.at(0), lines.at(1)} );
            xTEST_NA(prRv);
        }
    }

    // out
    a_content->swap(msRv);

#if xTODO
    bool_t             bRv = false;
    std::map_tstring_t msRv;
    std::vec_tstring_t vsRv;

    bRv = textRead(filePath, &vsRv);
    xTEST_EQ(bRv, true);

    for (const auto it = vsRv.begin(); it != vsRv.end(); ++ it) {
        std::vec_tstring_t lines;
        String::split(vsRv.at(0), separator, &lines);

        msRv.insert( {lines.at(0), lines.at(1)} );
    }

    // out
    content.swap(msRv);
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
File::textWrite(
    std::ctstring_t     &a_filePath,
    std::ctstring_t     &a_separator,
    std::cmap_tstring_t &a_content,
    cOpenMode            a_mode
)
{
    xTEST(!a_filePath.empty());
    xTEST(!a_separator.empty());
    xTEST_NA(a_content);
    xTEST(a_mode != OpenMode::Unknown);

    File file;
    file.create(a_filePath, a_mode);

    xCHECK_DO(a_content.empty(), return);

    for (const auto &[key, value] : a_content) {
        file.writeLine(key + a_separator + value);
    }
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: bin
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
void_t
File::binRead(
    std::ctstring_t &a_filePath,
    std::ustring_t  *a_content
)
{
    xTEST(!a_filePath.empty());
    xTEST_PTR(a_content);

    std::ustring_t usRv;

    File file;
    file.create(a_filePath, OpenMode::BinRead);

    clonglong_t fileSize = file.size();
    xTEST_DIFF(fileSize, static_cast<longlong_t>( PointerPosition::Error ));
    xCHECK_DO(fileSize == 0LL, a_content->clear(); return);

    usRv.resize( static_cast<size_t>(fileSize) );

    std::csize_t readLen = file.read((void_t *)&usRv.at(0), usRv.size());
    xTEST_EQ(readLen, usRv.size());

    // out
    a_content->swap(usRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
File::binWrite(
    std::ctstring_t &a_filePath,
    std::custring_t &a_content
)
{
    xTEST(!a_filePath.empty());
    xTEST_NA(a_content);

    File file;
    file.create(a_filePath, OpenMode::BinWrite);

    xCHECK_DO(a_content.empty(), return);

    size_t writeLen = file.write((void_t *)&a_content.at(0), a_content.size());
    xTEST_EQ(writeLen, a_content.size());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
int_t
File::_nativeHandle(
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
File::_stdHandle(
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
File::_openMode(
    cOpenMode a_mode
)
{
    xTEST_NA(a_mode);

#if 0
	std::tstring_t sRv;

	switch (a_mode) {
	// text modes
	case OpenMode::Read:
		sRv = xT("r");
		break;
	case OpenMode::Write:
		sRv = xT("w");
		break;
	case OpenMode::Append:
		sRv = xT("a");
		break;
	case OpenMode::OpenReadWrite:
		sRv = xT("r+");
		break;
	case OpenMode::CreateReadWrite:
		sRv = xT("w+");
		break;
	case OpenMode::OpenReadAppend:
		sRv = xT("a+");
		break;

	// binary modes
	case OpenMode::BinRead:
		sRv = xT("rb");
		break;
	case OpenMode::BinWrite:
		sRv = xT("wb");
		break;
	case OpenMode::BinAppend:
		sRv = xT("ab");
		break;
	case OpenMode::BinOpenReadWrite:
		sRv = xT("rb+");
		break;
	case OpenMode::BinCreateReadWrite:
		sRv = xT("wb+");
		break;
	case OpenMode::BinOpenReadAppend:
		sRv = xT("ab+");
		break;

	case OpenMode::Unknown:
	default:
		sRv = xT("r");
		break;
	}

	return sRv;
#else
	static const std::map<OpenMode, std::tstring_t> modes
	{
		// text modes
		{OpenMode::Read,               xT("r")},
		{OpenMode::Write,              xT("w")},
		{OpenMode::Append,             xT("a")},
		{OpenMode::OpenReadWrite,      xT("r+")},
		{OpenMode::CreateReadWrite,    xT("w+")},
		{OpenMode::OpenReadAppend,     xT("a+")},

		// binary modes
		{OpenMode::BinRead,            xT("rb")},
		{OpenMode::BinWrite,           xT("wb")},
		{OpenMode::BinAppend,          xT("ab")},
		{OpenMode::BinOpenReadWrite,   xT("rb+")},
		{OpenMode::BinCreateReadWrite, xT("wb+")},
		{OpenMode::BinOpenReadAppend,  xT("ab+")},

		{OpenMode::Unknown,            xT("r")}
	};

	auto it = modes.find(a_mode);
	xCHECK_RET(it == modes.cend(), std::tstring_t());

	return it->second;
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
