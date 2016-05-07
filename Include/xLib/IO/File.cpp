/**
 * \file  File.inl
 * \brief file
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "File.h"
#endif

#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Locale.h>
#include <xLib/Core/DateTime.h>
#include <xLib/Core/Utils.h>
#include <xLib/Debug/Exception.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/Dir.h>
#include <xLib/IO/FileType.h>
#include <xLib/Crypt/Random.h>
#include <xLib/Sync/Thread.h>

#if   xENV_WIN
    #include "Platform/Win/File_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/File_unix.inl"

    #if   xENV_LINUX

    #elif xENV_BSD

    #elif xENV_APPLE

    #endif
#endif


xNAMESPACE_BEGIN2(xlib, io)

/**************************************************************************************************
*    public: constructors, destructor
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
File::File(
    cbool_t &a_isUseBuffering
) :
    _handle        (xPTR_NULL),
    _filePath      (),
    _isUseBuffering(a_isUseBuffering)
{
    xTEST_NA(a_isUseBuffering);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
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
xINLINE void_t
File::create(
    std::ctstring_t  &a_filePath,
    const ExOpenMode &a_mode
)
{
    xTEST_EQ(a_filePath.empty(), false);
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
    if (_isUseBuffering) {
        setVBuff(xPTR_NULL, bmFull, BUFSIZ);
    } else {
        setVBuff(xPTR_NULL, bmNo,   0);
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
File::reopen(
    std::ctstring_t  &a_filePath,
    const ExOpenMode &a_mode
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_NA(a_mode);

    // create dir
    Dir( Path(a_filePath).dir() ).pathCreate();

    // create, reopen file
    {
        std::FILE *file = xTFREOPEN(a_filePath.c_str(), _openMode(a_mode).c_str(), get());
        xTEST_PTR(file);

        _handle   = file;
        _filePath = a_filePath;
    }

    // buffering
    if (_isUseBuffering) {
        setVBuff(xPTR_NULL, bmFull, BUFSIZ);
    } else {
        setVBuff(xPTR_NULL, bmNo,   0);
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE std::FILE*
File::get() const
{
    xTEST_EQ(isValid(), true);

    return _handle;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
File::path() const
{
    xTEST_EQ(_filePath.empty(),   false);
    xTEST_EQ(isExists(_filePath), true);

    return _filePath;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
File::attach(
    std::FILE       *a_file,
    std::ctstring_t &a_filePath
)
{
    xTEST_PTR(a_file);
    xTEST_NA(a_filePath);

    close();

    _handle   = a_file;
    _filePath = a_filePath;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::FILE*
File::detach()
{
    std::FILE *file = get();

    _handle = xPTR_NULL;
    _filePath.clear();

    return file;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
* public: read / write
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE size_t
File::read(
    void_t       *a_buff,
    std::csize_t &a_count
) const
{
    xTEST_PTR(a_buff);
    xTEST_NA(a_count);

    size_t uiRv = std::fread(a_buff, 1, a_count, get());
    xTEST_GR_EQ(a_count, uiRv);

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE size_t
File::write(
    cvoid_t      *a_buff,
    std::csize_t &a_count
) const
{
    xTEST_PTR(a_buff);
    xTEST_NA(a_count);

    size_t uiRv = std::fwrite(a_buff, 1, a_count, get());
    xTEST_EQ(uiRv, a_count);

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
File::read(
    std::ustring_t *a_buff
) const
{
    xTEST_PTR(a_buff);

    longlong_t fileSize = size();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), fileSize);

    a_buff->clear();
    a_buff->resize( static_cast<size_t>( fileSize ) );
    xCHECK_DO(fileSize == 0LL, return);

    size_t uiRv = std::fread(&a_buff->at(0), 1, a_buff->size() *
        sizeof(std::ustring_t::value_type), get());
    xTEST_EQ(uiRv, a_buff->size());
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
File::write(
    std::custring_t &a_buff
) const
{
    xTEST_NA(a_buff);

    size_t uiRv = std::fwrite(&a_buff.at(0), 1, a_buff.size() *
        sizeof(std::ustring_t::value_type), get());
    xTEST_EQ(uiRv, a_buff.size());
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
File::read(
    std::tstring_t *a_buff
) const
{
    xTEST_PTR(a_buff);

    clonglong_t fileSize = size();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), fileSize);

    a_buff->clear();
    a_buff->resize( static_cast<size_t>( fileSize) );
    xCHECK_DO(fileSize == 0LL, return);

    size_t uiRv = std::fread(&a_buff->at(0), 1, a_buff->size() *
        sizeof(std::tstring_t::value_type), get());
    xTEST_EQ(uiRv, a_buff->size());
}
//-------------------------------------------------------------------------------------------------
xINLINE int_t
File::write(
    ctchar_t *a_format, ...
) const
{
    xTEST_PTR(a_format);

    va_list args;
    xVA_START(args, a_format);

    int_t iRv = xTVFPRINTF(get(), a_format, args);
    xTEST_LESS(- 1, iRv);

    xVA_END(args);

    return iRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE int_t
File::writeV(
    ctchar_t *a_format,
    va_list   a_args
) const
{
    xTEST_PTR(a_format);
    xTEST_NA(a_args);

    int_t iRv = xTVFPRINTF(get(), a_format, a_args);
    xTEST_LESS(- 1, iRv);

    return iRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
File::readLine(
    std::tstring_t *a_str,
    std::csize_t   &a_maxCount
) const
{
    xTEST_PTR(a_str);
    xTEST_NA(a_maxCount);

    std::tstring_t str;
    str.resize(a_maxCount + 1); // + 1 for 0

    tchar_t *pszRv = xTFGETS(&str.at(0), static_cast<int_t>( str.size() ), get());
    xTEST_PTR(pszRv);

    // trim xPTR_NULL's from string, remove EOL
    str = String::removeEol( str.c_str() );
    // out
    a_str->swap(str);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
File::writeLine(
    std::ctstring_t &a_str
) const
{
    xTEST_NA(a_str);

    int_t iRv = xTFPUTS((a_str + Const::eol()).c_str(), get());
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
xINLINE tchar_t
File::readChar() const
{
    twint_t iRv = xTFGETC(get());
    xTEST_DIFF(iRv, xTEOF);

    return static_cast<tchar_t>( iRv );
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
File::writeChar(
    ctchar_t &a_ch
) const
{
    xTEST_NA(a_ch);

    twint_t iRv = xTFPUTC(a_ch, get());
    xTEST_DIFF(iRv, xTEOF);
    xTEST_EQ(static_cast<tchar_t>( iRv ), a_ch);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
File::ungetChar(
    ctchar_t &a_ch
) const
{
    xTEST_NA(a_ch);

    twint_t iRv = xTUNGETC(a_ch, get());
    xTEST_DIFF(iRv, xTEOF);
    xTEST_EQ(static_cast<tchar_t>( iRv ), a_ch);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
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
xINLINE void_t
File::locking(
    const ExLockingMode &a_mode,
    clong_t             &a_bytes
)
{
    xTEST_NA(a_mode);
    xTEST_NA(a_bytes);

#if   xENV_WIN
    clong_t     bytes = a_bytes;
#elif xENV_UNIX
    const off_t bytes = static_cast<off_t>( a_bytes );
#endif

    int_t iRv = xLOCKING(_nativeHandle(get()), a_mode, bytes);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
File::setPosition(
    clong_t                 &a_offset,
    const ExPointerPosition &a_pos
) const
{
    xTEST_NA(a_offset);
    xTEST_NA(a_pos);

    int_t iRv = std::fseek(get(), a_offset, a_pos);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
xINLINE long_t
File::position() const {
    long_t liRv = std::ftell(get());
    xTEST_DIFF(liRv, - 1L);

    return liRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
File::setVBuff(
    char                  *a_buff,
    const ExBufferingMode &a_mode,
    std::csize_t          &a_size
) const
{
    xTEST_NA(a_buff);
    xTEST_NA(a_mode);
    xTEST_NA(a_size);

    int_t iRv = std::setvbuf(get(), a_buff, a_mode, a_size);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
xINLINE longlong_t
File::size() const
{
    long_t currStreamPos = position();
    setPosition(0, ppEnd);

    long_t streamSize = position();
    setPosition(currStreamPos, ppBegin);

    return static_cast<longlong_t>( streamSize );
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
File::resize(
    clonglong_t &a_size
) const
{
    xTEST_NA(a_size);

#if   xENV_WIN
    clonglong_t _size = a_size;
#elif xENV_UNIX
    const off_t _size = static_cast<off_t>( a_size );
#endif

    int_t iRv = xCHSIZE(_nativeHandle( get() ), _size);
    xTEST_EQ(iRv, 0);
    xTEST_EQ(a_size, size());
}
//-------------------------------------------------------------------------------------------------

/**************************************************************************************************
*    public: error handling
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE bool_t
File::isValid() const
{
    return (_handle != xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
File::isOpen() const
{
    return isValid();
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
File::isEmpty() const
{
    longlong_t fileSize = size();
    xTEST_DIFF(fileSize, - 1LL);

    return (fileSize == 0LL);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
File::isEof() const
{
    bool_t bRv = static_cast<bool_t>( std::feof(get()) );
    xTEST_NA(bRv);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
File::isError() const
{
    bool_t bRv = static_cast<bool_t>( std::ferror(get()) );
    xTEST_NA(bRv);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
File::errorClear() const
{
    (void_t)std::clearerr( get() );
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: closing
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
File::flush() const
{
    twint_t iRv = std::fflush( get() );
    xTEST_DIFF(iRv, xTEOF);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
File::close()
{
    xCHECK_DO(!isValid(), return);

    errorClear();

    twint_t iRv = std::fclose( get() ); _handle = xPTR_NULL;
    xTEST_DIFF(iRv, xTEOF);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE bool_t
File::isFile(
    std::ctstring_t &a_filePath
)
{
    xTEST_NA(a_filePath);

    FileType type(a_filePath);
    xCHECK_RET(type.get() == FileType::faInvalid, false);

    return _isFile_impl(type);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE bool_t
File::isExists(
    std::ctstring_t &a_filePath
)
{
    xTEST_NA(a_filePath);

    xCHECK_RET(!isFile(a_filePath), false);

    int_t iRv = xTACCESS(a_filePath.c_str(), amExistence);
    xCHECK_RET(iRv == - 1 && StdError::get() == ENOENT, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
File::isExistsEx(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(a_filePath.empty(), false);

    std::tstring_t sRv;

    Path path(a_filePath);

    std::tstring_t fileDir  = path.dir();
    std::tstring_t fileName = path.fileBaseName();
    std::tstring_t fileExt  = path.ext();

    xCHECK_DO(!fileExt.empty(), fileExt.insert(0, Const::dot()));

    for (ulong_t existsIndex = 1; ; ++ existsIndex) {
        sRv = Format::str(xT("{}{}{} ({}){}"), fileDir, Const::slash(), fileName, existsIndex,
            fileExt);
        xCHECK_DO(!isExists(sRv), break);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::access(
    std::ctstring_t    &a_filePath,
    const ExAccessMode &a_mode
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_NA(a_mode);

    int_t iRv = xTACCESS(a_filePath.c_str(), a_mode);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::chmod(
    std::ctstring_t        &a_filePath,
    const ExPermissionMode &a_mode
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_NA(a_mode);

#if   xENV_WIN
    cint_t       mode = static_cast<int_t> ( a_mode );
#elif xENV_UNIX
    const mode_t mode = static_cast<mode_t>( a_mode );
#endif

    int_t iRv = xTCHMOD(a_filePath.c_str(), mode);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::clear(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(a_filePath.empty(), false);

    File file;
    file.create(a_filePath, omWrite);
    file.clear();
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::remove(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(a_filePath.empty(), false);

    xCHECK_DO(!isExists(a_filePath), return);

    chmod(a_filePath, pmWrite);

    int_t iRv = xTREMOVE(a_filePath.c_str());
    xTEST_DIFF(iRv, - 1);
    xTEST_EQ(isExists(a_filePath), false);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::tryRemove(
    std::ctstring_t &a_filePath,
    std::csize_t    &a_attempts,
    culong_t        &a_timeoutMsec
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_LESS(size_t(0U), a_attempts);
    xTEST_NA(a_timeoutMsec);

    std::csize_t attemptsMax  = 100;  // MAGIC_NUMBER: attemptsMax
    std::csize_t attemptsReal = (attemptsMax < a_attempts) ? attemptsMax : a_attempts;

    for (size_t i = 0; i < attemptsReal; ++ i) {
        xTRY {
            remove(a_filePath);
            xCHECK_DO(!isExists(a_filePath), break);
        }
        xCATCH_ALL

        Thread::currentSleep(a_timeoutMsec);
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::wipe(
    std::ctstring_t &a_filePath,
    std::csize_t    &a_passes
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_NA(a_passes);

    xCHECK_DO(!isExists(a_filePath), return);

    {
        // set normal file attributes
        FileType(a_filePath).clear();

        // open
        File file;
        file.create(a_filePath, omBinWrite);

        clonglong_t size = file.size();
        if (size > 0LL) {
            // fill by 0x55, 0xAA, random char
            for (size_t p = 0; p < a_passes; ++ p) {
                cuchar_t rand  = NativeRandom().nextChar<uchar_t>();
                cuchar_t char1 = 0x55;
                cuchar_t char2 = 0xAA;

                // rand
                {
                    file.setPosition(0L, ppBegin);

                    for (longlong_t i = 0LL; i < size; ++ i) {
                        size_t uiRv = std::fwrite(&rand, 1, sizeof(rand), file.get());
                        xTEST_EQ(uiRv, sizeof(rand));
                    }
                }

                // char1
                {
                    file.setPosition(0L, ppBegin);

                    for (longlong_t i = 0LL; i < size; ++ i) {
                        size_t uiRv = std::fwrite(&char1, 1, sizeof(char1), file.get());
                        xTEST_EQ(uiRv, sizeof(char1));
                    }
                }

                // char2
                {
                    file.setPosition(0L, ppBegin);

                    for (longlong_t i = 0LL; i < size; ++ i) {
                        size_t uiRv = std::fwrite(&char2, 1, sizeof(char2), file.get());
                        xTEST_EQ(uiRv, sizeof(char2));
                    }
                }
            } // if (size > 0LL)

            // truncate
            file.flush();
            file.resize(0L);
        }
    }

    // reset file time
    {
        const time_t create   = 0;
        const time_t access   = 0;
        const time_t modified = 0;

        setTime(a_filePath, create, access, modified);
    }

    // random file name
    std::tstring_t randFilePath;
    {
        std::tstring_t randFileName;

        randFileName = String::cast( DateTime().current().toMsec() );
        std::random_shuffle(randFileName.begin(), randFileName.end());

        randFilePath = Path(a_filePath).dir() + Const::slash() + randFileName;

        rename(a_filePath, randFilePath);
    }

    // delete
    remove(randFilePath);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::unlink(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(a_filePath.empty(), false);

    int_t iRv = xTUNLINK(a_filePath.c_str());
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::rename(
    std::ctstring_t &a_filePathOld,
    std::ctstring_t &a_filePathNew
)
{
    xTEST_EQ(a_filePathOld.empty(), false);
    xTEST_EQ(a_filePathNew.empty(), false);

    int_t iRv = xTRENAME(a_filePathOld.c_str(), a_filePathNew.c_str());
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::move(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_dirPath
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_EQ(a_dirPath.empty(), false);

    rename(a_filePath, Path(a_dirPath).slashAppend() + Path(a_filePath).fileName());
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::copy(
    std::ctstring_t &a_filePathFrom,
    std::ctstring_t &a_filePathTo,
    cbool_t         &a_isFailIfExists
) /* throw(Exception) */
{
    xTEST_EQ(a_filePathFrom.empty(), false);
    xTEST_EQ(a_filePathTo.empty(), false);
    xTEST_NA(a_isFailIfExists);

    bool_t isCopyOk = true;

    // errors
    std::ctstring_t errorDestFileExists = xT("File - Destination file is exists");
    std::ctstring_t errorCopyFail       = xT("File - Copy fail");
    std::ctstring_t errorFilesDiffrent  = xT("File - Files are diffrent");

    xCHECK_DO(a_isFailIfExists && isExists(a_filePathTo), xTHROW_REPORT(errorDestFileExists));

    // copy
    {
        // open files
        File fileFrom;
        fileFrom.create(a_filePathFrom, omBinRead);

        File fileTo;
        fileTo.create(a_filePathTo, omBinWrite);

        if ( !fileFrom.isEmpty() ) {
            // copy files
            std::csize_t buffSize       = 1024;
            uchar_t      buff[buffSize] = {0};

            for ( ; ; ) {
                std::csize_t readed  = fileFrom.read(buff, buffSize);
                xCHECK_DO(0 >= readed, break);

                std::csize_t written = fileTo.write(buff, readed);
                xCHECK_DO(readed != written, isCopyOk = false; break);
            }
        }
    }

    // checks
    {
        xCHECK_DO(!isCopyOk, remove(a_filePathTo); xTHROW_REPORT(errorCopyFail));
        xCHECK_DO(size(a_filePathFrom) != size(a_filePathTo), remove(a_filePathTo);
            xTHROW_REPORT(errorFilesDiffrent));
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE longlong_t
File::size(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(a_filePath.empty(),   false);
    xTEST_EQ(isExists(a_filePath), true);

    File file;
    file.create(a_filePath, omRead);
    longlong_t liRv = file.size();
    xTEST_GR_EQ(liRv, 0LL);

    return liRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE ulonglong_t
File::lines(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(a_filePath.empty(),   false);
    xTEST_EQ(isExists(a_filePath), true);

    std::locale::global(std::locale());

    ulonglong_t      ullRv = 0LL;
    std::tifstream_t ifs(a_filePath.c_str(), std::ios::in);

    xCHECK_RET(!ifs || ifs.fail() || !ifs.good() || !ifs.is_open() || ifs.eof(), 0LL);

    tchar_t chChar;
    for (ullRv = 0LL; ifs.get(chChar); ) {
        xCHECK_DO(chChar == xT('\n'), ++ ullRv);
    }

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::time(
    std::ctstring_t &a_filePath,
    time_t          *a_create,
    time_t          *a_access,
    time_t          *a_modified
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_NA(a_create);
    xTEST_NA(a_access);
    xTEST_NA(a_modified);

    _time_impl(a_filePath, a_create, a_access, a_modified);
}
//-------------------------------------------------------------------------------------------------
/*static */
xINLINE void_t
File::setTime(
    std::ctstring_t &a_filePath,
    const time_t    &a_create,
    const time_t    &a_access,
    const time_t    &a_modified
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_NA(a_create);
    xTEST_NA(a_access);
    xTEST_NA(a_modified);

    _setTime_impl(a_filePath, a_create, a_access, a_modified);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: text
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::textRead(
    std::ctstring_t &a_filePath,
    std::tstring_t  *a_content
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_PTR(a_content);

    File           file;
    std::tstring_t sRv;

    file.create(a_filePath, omBinRead);

    clonglong_t fileSize = file.size();
    xTEST_DIFF(fileSize, static_cast<longlong_t>( ppError ));

    xCHECK_DO(fileSize == 0LL, a_content->clear(); return);

    sRv.resize( static_cast<size_t>( fileSize) );

    size_t readLen = file.read((void_t *)&sRv.at(0), sRv.size());
    xTEST_EQ(readLen, sRv.size());

    // out
    a_content->swap(sRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::textWrite(
    std::ctstring_t  &a_filePath,
    std::ctstring_t  &a_content,
    const ExOpenMode &a_mode
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_NA(a_content);
    xTEST_DIFF(a_mode, omUnknown);

    File file;
    file.create(a_filePath, a_mode);

    xCHECK_DO(a_content.empty(), return);

    size_t writeLen = file.write((void_t *)&a_content.at(0), a_content.size());
    xTEST_EQ(writeLen, a_content.size());
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::textRead(
    std::ctstring_t    &a_filePath,
    std::vec_tstring_t *a_content
)
{
    xTEST_EQ(a_filePath.empty(),   false);
    xTEST_EQ(isExists(a_filePath), true);
    xTEST_PTR(a_content);

    std::vec_tstring_t vsRv;
    std::tstring_t     content;

    textRead(a_filePath, &content);

    String::split(content, Const::nl(), &vsRv);

    // out
    a_content->swap(vsRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::textWrite(
    std::ctstring_t     &a_filePath,
    std::cvec_tstring_t &a_content,
    const ExOpenMode    &a_mode
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_NA(a_content);
    xTEST_DIFF(a_mode, omUnknown);

    std::tstring_t content;

    content = String::join(a_content, Const::nl());

    textWrite(a_filePath, content, a_mode);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::textRead(
    std::ctstring_t    &a_filePath,
    std::ctstring_t    &a_separator,
    std::map_tstring_t *a_content
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_EQ(isExists(a_filePath), true);
    xTEST_PTR(a_content);

    // if file empty
    xCHECK_DO(size(a_filePath) == 0L, a_content->clear(); return);

    std::locale::global( std::locale() );

    std::tifstream_t ifs(a_filePath.c_str());
    xTEST_EQ(!! ifs,        true);
    xTEST_EQ(ifs.fail(),    false);
    xTEST_EQ(ifs.good(),    true);
    xTEST_EQ(ifs.is_open(), true);
    xTEST_EQ(ifs.eof(),     false);

    std::map_tstring_t msRv;
    std::tstring_t     line;
    std::vec_tstring_t lines;

    for (size_t i = 0; !ifs.eof(); ++ i) {
        std::pair<std::map_tstring_t::iterator, bool_t> prRv;

        std::getline(ifs, line);
        line = String::trimRightChars(line, Const::eol());

        if ( line.empty() ) {
            prRv = msRv.insert( std::make_pair(Const::strEmpty(), Const::strEmpty()) );
        } else {
            String::split(line, a_separator, &lines);
            xTEST_EQ(lines.size(), size_t(2));

            prRv = msRv.insert( std::make_pair(lines.at(0), lines.at(1)) );
        }

        // TODO: File::textRead() - xTEST_EQ(prRv.second, true);
        xUNUSED(prRv);
    }

    // out
    a_content->swap(msRv);

#if xTODO
    bool_t             bRv = false;
    std::map_tstring_t msRv;
    std::vec_tstring_t vsRv;

    bRv = textRead(filePath, &vsRv);
    xTEST_EQ(bRv, true);

    std::vec_tstring_t::_const_iterator it;
    for (it = vsRv.begin(); it != vsRv.end(); ++ it) {
        std::vec_tstring_t lines;

        String::split(vsRv.at(0), separator, &lines);
        msRv.insert( std::pair<std::tstring_t, std::tstring_t>(lines.at(0), lines.at(1)) );
    }

    // out
    content.swap(msRv);
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::textWrite(
    std::ctstring_t     &a_filePath,
    std::ctstring_t     &a_separator,
    std::cmap_tstring_t &a_content,
    const ExOpenMode    &a_mode
)
{
    xTEST_EQ(a_filePath.empty(),  false);
    xTEST_EQ(a_separator.empty(), false);
    xTEST_NA(a_content);
    xTEST_DIFF(a_mode, omUnknown);

    File file;
    file.create(a_filePath, a_mode);

    xCHECK_DO(a_content.empty(), return);

    typedef std::map_tstring_t content_t;

    xFOR_EACH_CONST(content_t, it, a_content) {
        file.writeLine(it->first + a_separator + it->second);
    }

#if xTODO
    std::tstring_t sRv;

    xFOR_EACH_CONST(TContent, it, content) {
        sRv.append(it->first);
        sRv.append(separator);
        sRv.append(it->second);
        sRv.append(Const::nl());

        xCHECK_DO(it != content.end(), sRv.append(Const::nl()));
    }

    textWrite(filePath, sRv, a_mode);
#endif
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: bin
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::binRead(
    std::ctstring_t &a_filePath,
    std::ustring_t  *a_content
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_PTR(a_content);

    File         file;
    std::ustring_t usRv;

    file.create(a_filePath, omBinRead);

    longlong_t fileSize = file.size();
    xTEST_DIFF(fileSize, static_cast<longlong_t>( ppError ));

    xCHECK_DO(fileSize == 0LL, a_content->clear(); return);

    usRv.resize( static_cast<size_t>( fileSize ) );

    size_t readLen = file.read((void_t *)&usRv.at(0), usRv.size());
    xTEST_EQ(readLen, usRv.size());

    // out
    a_content->swap(usRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
File::binWrite(
    std::ctstring_t &a_filePath,
    std::custring_t &a_content
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_NA(a_content);

    File file;
    file.create(a_filePath, omBinWrite);

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
xINLINE int_t
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
xINLINE std::FILE *
File::_stdHandle(
    int_t             a_fileHandle,
    const ExOpenMode &a_mode
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
xINLINE std::tstring_t
File::_openMode(
    const ExOpenMode &a_mode
)
{
    xTEST_NA(a_mode);

    std::tstring_t sRv;

    switch (a_mode) {
    // text modes
    case omRead:
        sRv = xT("r");
        break;
    case omWrite:
        sRv = xT("w");
        break;
    case omAppend:
        sRv = xT("a");
        break;
    case omOpenReadWrite:
        sRv = xT("r+");
        break;
    case omCreateReadWrite:
        sRv = xT("w+");
        break;
    case omOpenReadAppend:
        sRv = xT("a+");
        break;

    // binary modes
    case omBinRead:
        sRv = xT("rb");
        break;
    case omBinWrite:
        sRv = xT("wb");
        break;
    case omBinAppend:
        sRv = xT("ab");
        break;
    case omBinOpenReadWrite:
        sRv = xT("rb+");
        break;
    case omBinCreateReadWrite:
        sRv = xT("wb+");
        break;
    case omBinOpenReadAppend:
        sRv = xT("ab+");
        break;

    case omUnknown:
    default:
        sRv = xT("r");
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
