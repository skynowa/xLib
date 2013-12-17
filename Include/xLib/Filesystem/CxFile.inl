/**
 * \file  CxFile.cpp
 * \brief file
 */


#include <xLib/Core/CxString.h>
#include <xLib/Core/CxLocale.h>
#include <xLib/Core/CxDateTime.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/Debug/CxException.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxFileType.h>
#include <xLib/Crypt/CxRandom.h>
#include <xLib/Sync/CxThread.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public: constructors, destructor
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxFile::CxFile() :
    _file    (NULL),
    _filePath()
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxFile::~CxFile()
{
    close();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: open, get
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::create(
    std::ctstring_t  &a_filePath,
    const ExOpenMode &a_mode,
    cbool_t          &a_isUseBuffering
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_NA(a_mode);
    xTEST_NA(a_isUseBuffering);

    // create dir
    CxDir( CxPath(a_filePath).dir() ).pathCreate();

    // create, open file
    {
        std::FILE *file = std::xTFOPEN(a_filePath.c_str(), _openMode(a_mode).c_str());
        xTEST_PTR(file);

        _file     = file;
        _filePath = a_filePath;
    }

    // buffering
    if (!a_isUseBuffering) {
        setVBuff(NULL, bmNo,   0);
    } else {
        setVBuff(NULL, bmFull, BUFSIZ);
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::reopen(
    std::ctstring_t  &a_filePath,
    const ExOpenMode &a_mode,
    cbool_t          &a_isUseBuffering
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_NA(a_mode);
    xTEST_NA(a_isUseBuffering);

    // create dir
    CxDir( CxPath(a_filePath).dir() ).pathCreate();

    // create, reopen file
    {
        std::FILE *file = std::xTFREOPEN(a_filePath.c_str(), _openMode(a_mode).c_str(), get());
        xTEST_PTR(file);

        _file     = file;
        _filePath = a_filePath;
    }

    // buffering
    if (!a_isUseBuffering) {
        setVBuff(NULL, bmNo,   0);
    } else {
        setVBuff(NULL, bmFull, BUFSIZ);
    }
}
//-------------------------------------------------------------------------------------------------
inline std::FILE *
CxFile::get() const
{
    xTEST_EQ(true, isValid());

    return _file;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxFile::path() const
{
    xTEST_EQ(false, _filePath.empty());
    xTEST_EQ(true,  isExists(_filePath));

    return _filePath;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::attach(
    std::FILE *a_file
)
{
    xTEST_NA(a_file);

    close();

    _file     = a_file;
    _filePath = CxConst::strEmpty();
}
//-------------------------------------------------------------------------------------------------
inline std::FILE *
CxFile::detach()
{
    std::FILE *file = get();

    _file = NULL;

    return file;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
* public: read / write
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline size_t
CxFile::read(
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
inline size_t
CxFile::write(
    cvoid_t      *a_buff,
    std::csize_t &a_count
) const
{
    xTEST_PTR(a_buff);
    xTEST_NA(a_count);

    size_t uiRv = std::fwrite(a_buff, 1, a_count, get());
    xTEST_EQ(a_count, uiRv);

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::read(
    std::ustring_t *a_buff
) const
{
    xTEST_PTR(a_buff);

    longlong_t fileSize = size();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), fileSize);

    (*a_buff).clear();
    (*a_buff).resize( static_cast<size_t>( fileSize ) );
    xCHECK_DO(0LL == fileSize, return);

    size_t uiRv = std::fread(&a_buff->at(0), 1, a_buff->size() *
        sizeof(std::ustring_t::value_type), get());
    xTEST_EQ(a_buff->size(), uiRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::write(
    std::custring_t &a_buff
) const
{
    xTEST_NA(a_buff);

    size_t uiRv = std::fwrite(&a_buff.at(0), 1, a_buff.size() *
        sizeof(std::ustring_t::value_type), get());
    xTEST_EQ(a_buff.size(), uiRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::read(
    std::tstring_t *a_buff
) const
{
    xTEST_PTR(a_buff);

    clonglong_t fileSize = size();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), fileSize);

    (*a_buff).clear();
    (*a_buff).resize( static_cast<size_t>( fileSize) );
    xCHECK_DO(0LL == fileSize, return);

    size_t uiRv = std::fread(&a_buff->at(0), 1, a_buff->size() *
        sizeof(std::tstring_t::value_type), get());
    xTEST_EQ(a_buff->size(), uiRv);
}
//-------------------------------------------------------------------------------------------------
inline int_t
CxFile::write(
    ctchar_t *a_format, ...
) const
{
    xTEST_PTR(a_format);

    va_list args;
    xVA_START(args, a_format);

    int_t iRv = std::xTVFPRINTF(get(), a_format, args);
    xTEST_LESS(- 1, iRv);

    xVA_END(args);

    return iRv;
}
//-------------------------------------------------------------------------------------------------
inline int_t
CxFile::writeV(
    ctchar_t *a_format,
    va_list   a_args
) const
{
    xTEST_PTR(a_format);
    xTEST_PTR(a_args);

    int_t iRv = std::xTVFPRINTF(get(), a_format, a_args);
    xTEST_LESS(- 1, iRv);

    return iRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::readLine(
    std::tstring_t *a_str,
    std::csize_t   &a_maxCount
) const
{
    xTEST_PTR(a_str);
    xTEST_NA(a_maxCount);

    std::tstring_t str;
    str.resize(a_maxCount + 1); // + 1 for 0

    tchar_t *pszRv = std::xTFGETS(&str.at(0), static_cast<int_t>( str.size() ), get());
    xTEST_PTR(pszRv);

    str.erase(str.end() - 1); // erase last char - 0

    // out
    a_str->swap(str);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::writeLine(
    std::ctstring_t &a_str
) const
{
    xTEST_NA(a_str);

    int_t iRv = std::xTFPUTS((a_str + CxConst::eol()).c_str(), get());
    xTEST_DIFF(- 1, iRv);
}
//-------------------------------------------------------------------------------------------------
inline tchar_t
CxFile::readChar() const
{
    twint_t iRv = std::xTFGETC(get());
    xTEST_DIFF(xTEOF, iRv);

    return static_cast<tchar_t>( iRv );
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::writeChar(
    ctchar_t &a_ch
) const
{
    xTEST_NA(a_ch);

    twint_t iRv = std::xTFPUTC(a_ch, get());
    xTEST_DIFF(xTEOF, iRv);
    xTEST_EQ(a_ch, static_cast<tchar_t>( iRv ));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::ungetChar(
    ctchar_t &a_ch
) const
{
    xTEST_NA(a_ch);

    twint_t iRv = std::xTUNGETC(a_ch, get());
    xTEST_DIFF(xTEOF, iRv);
    xTEST_EQ(a_ch, static_cast<tchar_t>( iRv ));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::clear() const
{
    resize(0L);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: other
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::locking(
    const ExLockingMode &a_mode,
    clong_t             &a_bytes
)
{
    xTEST_NA(a_mode);
    xTEST_NA(a_bytes);

#if xOS_ENV_WIN
    clong_t     bytes = a_bytes;
#else
    const off_t bytes = static_cast<off_t>( a_bytes );
#endif

    int_t iRv = ::xLOCKING(_nativeHandle(get()), a_mode, bytes);
    xTEST_DIFF(- 1, iRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::setPosition(
    clong_t                 &a_offset,
    const ExPointerPosition &a_pos
) const
{
    xTEST_NA(a_offset);
    xTEST_NA(a_pos);

    int_t iRv = std::fseek(get(), a_offset, a_pos);
    xTEST_DIFF(- 1, iRv);
}
//-------------------------------------------------------------------------------------------------
inline long_t
CxFile::position() const {
    long_t liRv = std::ftell(get());
    xTEST_DIFF(- 1L, liRv);

    return liRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::setVBuff(
    char                  *a_buff,
    const ExBufferingMode &a_mode,
    std::csize_t          &a_size
) const
{
    xTEST_NA(a_buff);
    xTEST_NA(a_mode);
    xTEST_NA(a_size);

    int_t iRv = std::setvbuf(get(), a_buff, a_mode, a_size);
    xTEST_DIFF(- 1, iRv);
}
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

inline void_t
CxFile::setMode(
    const ExTranslationMode &a_mode
) const
{
    xTEST_NA(a_mode);

    int_t iRv = ::setmode(_nativeHandle(get()), a_mode);
    xTEST_DIFF(- 1, iRv);
}

#endif
//-------------------------------------------------------------------------------------------------
inline longlong_t
CxFile::size() const
{
/**
 * TODO: Do not use fseek() and ftell() to compute the size of a regular file
 * https://www.securecoding.cert.org/confluence/display/seccode/FIO19-C.+Do+not+use+fseek()+and+ftell()+to+compute+the+size+of+a+file
 */

#if xTODO
    vFlush();

    xTSTAT_STRUCT stat = {0};

    // TODO: fstat
    int_t iRv = ::xTSTAT(_filePath.c_str(), &stat);
    xTEST_DIFF(- 1, iRv);

    return stat.st_size;
#else
    long_t streamSize    = - 1L;
    long_t currStreamPos = - 1L;

    currStreamPos = position();
    setPosition(0, ppEnd);

    streamSize = position();
    setPosition(currStreamPos, ppBegin);

    return static_cast<longlong_t>( streamSize );
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::resize(
    clonglong_t &a_size
) const
{
    xTEST_NA(a_size);

#if xOS_ENV_WIN
    clonglong_t _size = a_size;
#else
    const off_t _size = static_cast<off_t>( a_size );
#endif

    int_t iRv = ::xCHSIZE(_nativeHandle( get() ), _size);
    xTEST_EQ(0, iRv);
    xTEST_EQ(a_size, size());
}
//-------------------------------------------------------------------------------------------------

/**************************************************************************************************
*    public: error handling
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxFile::isValid() const
{
    return (NULL != _file);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxFile::isOpen() const
{
    return isValid();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxFile::isEmpty() const
{
    longlong_t fileSize = size();
    xTEST_DIFF(- 1LL, fileSize);

    return (0LL == fileSize);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxFile::isEof() const
{
    bool_t bRv = xINT_TO_BOOL( std::feof(get()) );
    xTEST_NA(bRv);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxFile::isError() const
{
    bool_t bRv = xINT_TO_BOOL( std::ferror(get()) );
    xTEST_NA(bRv);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::errorClear() const
{
    (void_t)std::clearerr( get() );
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: closing
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::flush() const
{
    int_t iRv = std::fflush(get());
    xTEST_DIFF(EOF, iRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::close()
{
    xCHECK_DO(!isValid(), return);

    errorClear();

    int_t iRv = std::fclose(get()); _file = NULL;
    xTEST_DIFF(EOF, iRv);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxFile::isFile(
    std::ctstring_t &a_filePath
)
{
    xTEST_NA(a_filePath);

    bool_t bRv = false;

    CxFileType type(a_filePath);

    xCHECK_RET(CxFileType::faInvalid == type.get(), false);

#if xOS_ENV_WIN
    bRv = type.isExists(CxFileType::faDirectory);
    xCHECK_RET(bRv, false);

    bRv = type.isExists(CxFileType::faDevice);
    xCHECK_RET(bRv, false);

    bRv = type.isExists(CxFileType::faReparsePoint);
    xCHECK_RET(bRv, false);

    bRv = type.isExists(CxFileType::faOffline);
    xCHECK_RET(bRv, false);
#else
    bRv = type.isExists(CxFileType::faRegularFile);
    xCHECK_RET(!bRv, false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxFile::isExists(
    std::ctstring_t &a_filePath
)
{
    xTEST_NA(a_filePath);

    xCHECK_RET(!isFile(a_filePath), false);

    int_t iRv = ::xTACCESS(a_filePath.c_str(), amExistence);
    xCHECK_RET(- 1 == iRv && ENOENT == CxStdError::get(), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxFile::isExistsEx(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(false, a_filePath.empty());

    std::tstring_t sRv;

    CxPath path(a_filePath);

    std::tstring_t fileDir  = path.dir();
    std::tstring_t fileName = path.fileBaseName();
    std::tstring_t fileExt  = path.ext();

    xCHECK_DO(!fileExt.empty(), fileExt.insert(0, CxConst::dot()));

    for (ulong_t existsIndex = 1; ; ++ existsIndex) {
        sRv = CxString::format(xT("%s%s%s (%lu)%s"), fileDir.c_str(), CxConst::slash().c_str(),
            fileName.c_str(), existsIndex, fileExt.c_str());
        xCHECK_DO(!isExists(sRv), break);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::access(
    std::ctstring_t    &a_filePath,
    const ExAccessMode &a_mode
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_NA(a_mode);

    int_t iRv = ::xTACCESS(a_filePath.c_str(), a_mode);
    xTEST_DIFF(- 1, iRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::chmod(
    std::ctstring_t        &a_filePath,
    const ExPermissionMode &a_mode
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_NA(a_mode);

#if xOS_ENV_WIN
    cint_t       mode = static_cast<int_t> ( a_mode );
#else
    const mode_t mode = static_cast<mode_t>( a_mode );
#endif

    int_t iRv = ::xTCHMOD(a_filePath.c_str(), mode);
    xTEST_DIFF(- 1, iRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::clear(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(false, a_filePath.empty());

    CxFile file;

    file.create(a_filePath, omWrite, true);
    file.clear();
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::remove(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(false, a_filePath.empty());

    xCHECK_DO(!isExists(a_filePath), return);

    chmod(a_filePath, pmWrite);

    int_t iRv = std::xTREMOVE(a_filePath.c_str());
    xTEST_DIFF(- 1, iRv);
    xTEST_EQ(false, isExists(a_filePath));
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::tryRemove(
    std::ctstring_t &a_filePath,
    std::csize_t    &a_attempts,
    culong_t        &a_timeoutMsec
)
{
    xTEST_EQ(false, a_filePath.empty());
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

        CxThread::currentSleep(a_timeoutMsec);
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::wipe(
    std::ctstring_t &a_filePath,
    std::csize_t    &a_passes
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_NA(a_passes);

    xCHECK_DO(!isExists(a_filePath), return);

    {
        CxFile file;

        //--------------------------------------------------
        // set normal file attributes
        CxFileType(a_filePath).clear();

        //--------------------------------------------------
        // open
        file.create(a_filePath, omBinWrite, true);

        clonglong_t size = file.size();
        if (0LL < size) {
            //--------------------------------------------------
            // fill by 0x55, 0xAA, random char
            for (size_t p = 0; p < a_passes; ++ p) {
                CxNativeRandom random;

                cuchar_t rand  = random.nextChar<uchar_t>();
                cuchar_t char1 = 0x55;
                cuchar_t char2 = 0xAA;

                // rand
                {
                    file.setPosition(0L, ppBegin);

                    for (longlong_t i = 0LL; i < size; ++ i) {
                        size_t uiRv = std::fwrite(&rand, 1, sizeof(rand), file.get());
                        xTEST_EQ(sizeof(rand), uiRv);
                    }
                }

                // char1
                {
                    file.setPosition(0L, ppBegin);

                    for (longlong_t i = 0LL; i < size; ++ i) {
                        size_t uiRv = std::fwrite(&char1, 1, sizeof(char1), file.get());
                        xTEST_EQ(sizeof(char1), uiRv);
                    }
                }

                // char2
                {
                    file.setPosition(0L, ppBegin);

                    for (longlong_t i = 0LL; i < size; ++ i) {
                        size_t uiRv = std::fwrite(&char2, 1, sizeof(char2), file.get());
                        xTEST_EQ(sizeof(char2), uiRv);
                    }
                }
            }

            //--------------------------------------------------
            // truncate
            file.flush();
            file.resize(0L);
        }
    }

    //--------------------------------------------------
    // reset file time
    {
        const time_t create   = 0;
        const time_t access   = 0;
        const time_t modified = 0;

        setTime(a_filePath, create, access, modified);
    }

    //--------------------------------------------------
    // random file name
    std::tstring_t randFilePath;
    {
        std::tstring_t randFileName;

        randFileName = CxString::cast( CxDateTime().current().toMsec() );
        std::random_shuffle(randFileName.begin(), randFileName.end());

        randFilePath = CxPath(a_filePath).dir() + CxConst::slash() + randFileName;

        rename(a_filePath, randFilePath);
    }

    //--------------------------------------------------
    // delete
    remove(randFilePath);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::unlink(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(false, a_filePath.empty());

    int_t iRv = ::xTUNLINK(a_filePath.c_str());
    xTEST_DIFF(- 1, iRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::rename(
    std::ctstring_t &a_filePathOld,
    std::ctstring_t &a_filePathNew
)
{
    xTEST_EQ(false, a_filePathOld.empty());
    xTEST_EQ(false, a_filePathNew.empty());

    int_t iRv = std::xTRENAME(a_filePathOld.c_str(), a_filePathNew.c_str());
    xTEST_DIFF(- 1, iRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::move(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_dirPath
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_EQ(false, a_dirPath.empty());

    rename(a_filePath, CxPath(a_dirPath).slashAppend() + CxPath(a_filePath).fileName());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::copy(
    std::ctstring_t &a_filePathFrom,
    std::ctstring_t &a_filePathTo,
    cbool_t         &a_isFailIfExists
)
{
    xTEST_EQ(false, a_filePathFrom.empty());
    xTEST_EQ(false, a_filePathTo.empty());
    xTEST_NA(a_isFailIfExists);

    bool_t isCopyOk = true;

    //--------------------------------------------------
    // TODO: fail if exists
    if (a_isFailIfExists && isExists(a_filePathTo)) {
        xTEST_FAIL;
    }

    // TODO: check file size

    {
        //--------------------------------------------------
        // open files
        CxFile fileFrom;
        fileFrom.create(a_filePathFrom, omBinRead, true);

        CxFile fileTo;
        fileTo.create(a_filePathTo, omBinWrite, true);

        //--------------------------------------------------
        // copy files
        std::csize_t buffSize       = 1024;
        uchar_t      buff[buffSize] = {0};

        xFOREVER {
            std::csize_t readed  = fileFrom.read(buff, buffSize);
            xCHECK_DO(0 >= readed, break);

            std::csize_t written = fileTo.write(buff, readed);
            xCHECK_DO(readed != written, isCopyOk = false; break);
        }
    }

    //--------------------------------------------------
    // if copy fail - delete out file
    xCHECK_DO(!isCopyOk, remove(a_filePathTo); return /* false */);

    //--------------------------------------------------
    // test for size, maybe CRC
    xCHECK_DO(size(a_filePathFrom) != size(a_filePathTo), remove(a_filePathTo); return /* false */);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline longlong_t
CxFile::size(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_EQ(true,  isExists(a_filePath));

    CxFile file;

    file.create(a_filePath, omRead, true);
    longlong_t liRv = file.size();
    xTEST_LESS_EQ(0LL, liRv);

    return liRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline ulonglong_t
CxFile::lines(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_EQ(true,  isExists(a_filePath));

    std::locale::global(std::locale());

    ulonglong_t      ullRv = 0LL;
    std::tifstream_t ifs(a_filePath.c_str(), std::ios::in);

    xCHECK_RET(!ifs || ifs.fail() || !ifs.good() || !ifs.is_open() || ifs.eof(), 0LL);

    tchar_t chChar;
    for (ullRv = 0LL; ifs.get(chChar); ) {
        xCHECK_DO(xT('\n') == chChar, ++ ullRv);
    }

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::time(
    std::ctstring_t &a_filePath,
    time_t          *a_create,
    time_t          *a_access,
    time_t          *a_modified
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_NA(a_create);
    xTEST_NA(a_access);
    xTEST_NA(a_modified);

#if xOS_ENV_WIN
    FILETIME timeCreate   = {0};
    FILETIME timeAccess   = {0};
    FILETIME timeModified = {0};

    CxHandleInvalid file;

    file = ::CreateFile(a_filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
        CxFileType::faNormal, NULL);
    xTEST_EQ(true, file.isValid());

    BOOL blRv = ::GetFileTime(file.get(), &timeCreate, &timeAccess, &timeModified);
    xTEST_DIFF(FALSE, blRv);

    CxUtils::ptrAssignT(a_create,   CxDateTime::fileTimeToUnixTime(timeCreate));
    CxUtils::ptrAssignT(a_access,   CxDateTime::fileTimeToUnixTime(timeAccess));
    CxUtils::ptrAssignT(a_modified, CxDateTime::fileTimeToUnixTime(timeModified));
#else
    xUNUSED(a_create);

    xTSTAT_STRUCT info; xSTRUCT_ZERO(info);

    int_t iRv = ::xTSTAT(a_filePath.c_str(), &info);
    xTEST_DIFF(- 1, iRv);

    // create - n/a
    CxUtils::ptrAssignT(a_access,   info.st_atime);
    CxUtils::ptrAssignT(a_modified, info.st_mtime);
#endif
}
//-------------------------------------------------------------------------------------------------
/*static */
inline void_t
CxFile::setTime(
    std::ctstring_t &a_filePath,
    const time_t    &a_create,
    const time_t    &a_access,
    const time_t    &a_modified
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_NA(a_create);
    xTEST_NA(a_access);
    xTEST_NA(a_modified);

#if xOS_ENV_WIN
    FILETIME timeCreate = {0};
    CxDateTime::unixTimeToFileTime(a_create, &timeCreate);

    FILETIME timeAccess = {0};
    CxDateTime::unixTimeToFileTime(a_access, &timeAccess);

    FILETIME timeModified = {0};
    CxDateTime::unixTimeToFileTime(a_modified, &timeModified);

    CxHandleInvalid file;

    file = ::CreateFile(a_filePath.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
        CxFileType::faNormal, NULL);
    xTEST_EQ(true, file.isValid());

    BOOL blRv = ::SetFileTime(file.get(), &timeCreate, &timeAccess, &timeModified);
    xTEST_DIFF(FALSE, blRv);
#else
    xUNUSED(a_create);

    utimbuf times = {0, 0};

    // times.create - n/a
    times.actime  = a_access;
    times.modtime = a_modified;

    int_t iRv = ::utime(a_filePath.c_str(), &times);
    xTEST_DIFF(- 1, iRv);
#endif
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: text
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::textRead(
    std::ctstring_t &a_filePath,
    std::tstring_t  *a_content
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_PTR(a_content);

    CxFile         file;
    std::tstring_t sRv;

    file.create(a_filePath, omBinRead, true);

    clonglong_t fileSize = file.size();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), fileSize);

    xCHECK_DO(0LL == fileSize, a_content->clear(); return);

    sRv.resize( static_cast<size_t>( fileSize) );

    size_t readLen = file.read((void_t *)&sRv.at(0), sRv.size());
    xTEST_EQ(sRv.size(), readLen);

    // out
    a_content->swap(sRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::textWrite(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_content
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_NA(a_content);

    // TODO: if content.empty()

    CxFile file;

    file.create(a_filePath, omBinWrite, true);

    xCHECK_DO(a_content.empty(), return);

    size_t writeLen = file.write((void_t *)&a_content.at(0), a_content.size());
    xTEST_EQ(a_content.size(), writeLen);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::textRead(
    std::ctstring_t    &a_filePath,
    std::vec_tstring_t *a_content
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_EQ(true,  isExists(a_filePath));
    xTEST_PTR(a_content);

    std::vec_tstring_t vsRv;
    std::tstring_t     content;

    textRead(a_filePath, &content);

    CxString::split(content, CxConst::nl(), &vsRv);

    // out
    a_content->swap(vsRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::textWrite(
    std::ctstring_t     &a_filePath,
    std::cvec_tstring_t &a_content
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_NA(a_content);

    // TODO: if content.empty()

    std::tstring_t content;

    content = CxString::join(a_content, CxConst::nl());

    textWrite(a_filePath, content);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::textRead(
    std::ctstring_t    &a_filePath,
    std::ctstring_t    &a_separator,
    std::map_tstring_t *a_content
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_EQ(true,  isExists(a_filePath));
    xTEST_PTR(a_content);

    // if file empty
    xCHECK_DO(0L == size(a_filePath), a_content->clear(); return);

    std::locale::global( std::locale() );

    std::tifstream_t ifs(a_filePath.c_str());
    xTEST_EQ(true,  !! ifs);
    xTEST_EQ(false, ifs.fail());
    xTEST_EQ(true,  ifs.good());
    xTEST_EQ(true,  ifs.is_open());
    xTEST_EQ(false, ifs.eof());

    std::map_tstring_t msRv;
    std::tstring_t     line;
    std::vec_tstring_t lines;

    for (size_t i = 0; !ifs.eof(); ++ i) {
        std::getline(ifs, line);
        xCHECK_DO(line.empty(), continue);

        line = CxString::trimRightChars(line, CxConst::eol());

        CxString::split(line, a_separator, &lines);
        xTEST_EQ(size_t(2), lines.size());

        msRv.insert( std::make_pair(lines.at(0), lines.at(1)) );
    }

    // out
    a_content->swap(msRv);

#if xTODO
    bool_t             bRv = false;
    std::map_tstring_t msRv;
    std::vec_tstring_t vsRv;

    bRv = textRead(filePath, &vsRv);
    xTEST_EQ(true, bRv);

    std::vec_tstring_t::_const_iterator it;
    for (it = vsRv.begin(); it != vsRv.end(); ++ it) {
        std::vec_tstring_t lines;

        CxString::split(vsRv.at(0), separator, &lines);
        msRv.insert( std::pair<std::tstring_t, std::tstring_t>(lines.at(0), lines.at(1)) );
    }

    // out
    content.swap(msRv);
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::textWrite(
    std::ctstring_t     &a_filePath,
    std::ctstring_t     &a_separator,
    std::cmap_tstring_t &a_content
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_EQ(false, a_separator.empty());
    xTEST_NA(a_content);

    // TODO: if a_content.empty()

    CxFile file;
    file.create(a_filePath, omWrite, true);

    typedef std::map_tstring_t content_t;

    xFOREACH_CONST(content_t, it, a_content) {
        file.writeLine(it->first + a_separator + it->second);
    }

#if xTODO
    std::tstring_t sRv;

    xFOREACH_CONST(TContent, it, content) {
        sRv.append(it->first);
        sRv.append(separator);
        sRv.append(it->second);
        sRv.append(CxConst::nl());

        xCHECK_DO(it != content.end(), sRv.append(CxConst::nl()));
    }

    textWrite(filePath, sRv);
#endif
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: bin
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::binRead(
    std::ctstring_t &a_filePath,
    std::ustring_t  *a_content
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_PTR(a_content);

    CxFile         file;
    std::ustring_t usRv;

    file.create(a_filePath, omBinRead, true);

    longlong_t fileSize = file.size();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), fileSize);

    xCHECK_DO(0LL == fileSize, a_content->clear(); return);

    usRv.resize( static_cast<size_t>( fileSize ) );

    size_t readLen = file.read((void_t *)&usRv.at(0), usRv.size());
    xTEST_EQ(usRv.size(), readLen);

    // out
    a_content->swap(usRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::binWrite(
    std::ctstring_t &a_filePath,
    std::custring_t &a_content
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_NA(a_content);

    // TODO: if a_content.empty()

    CxFile file;
    file.create(a_filePath, omBinWrite, true);

    xCHECK_DO(a_content.empty(), return);

    size_t uiWriteLen = file.write((void_t *)&a_content.at(0), a_content.size());
    xTEST_EQ(a_content.size(), uiWriteLen);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline int_t
CxFile::_nativeHandle(
    std::FILE *a_file
)
{
    xTEST_PTR(a_file);

    int_t iRv = /*::*/fileno(a_file);
    xTEST_DIFF(- 1, iRv);

    return iRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::FILE *
CxFile::_stdHandle(
    int_t             a_fileHandle,
    const ExOpenMode &a_mode
)
{
    xTEST_NA(a_fileHandle);
    xTEST_NA(a_mode);

    std::FILE *pfRv = ::xTFDOPEN(a_fileHandle, _openMode(a_mode).c_str());
    xTEST_PTR(pfRv);

    return pfRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxFile::_openMode(
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
    default:
        sRv = xT("r");
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
