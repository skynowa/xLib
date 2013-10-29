/**
 * \file  CxFile.cpp
 * \brief file
 */


#include <xLib/Filesystem/CxFile.h>

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

/*******************************************************************************
*    public: constructors, destructor
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxFile::CxFile() :
    _file    (NULL),
    _filePath()
{
}
//------------------------------------------------------------------------------
/* virtual */
xINLINE_HO
CxFile::~CxFile()
{
    close();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: open, get
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO void_t
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
        std::FILE *pFile = ::xTFOPEN(a_filePath.c_str(), _openMode(a_mode).c_str());
        xTEST_PTR(pFile);

        _file     = pFile;
        _filePath = a_filePath;
    }

    // buffering
    if (!a_isUseBuffering) {
        setVBuff(NULL, bmNo,   0);
    } else {
        setVBuff(NULL, bmFull, BUFSIZ);
    }
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
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
        std::FILE *pFile = ::xTFREOPEN(a_filePath.c_str(), _openMode(a_mode).c_str(), get());
        xTEST_PTR(pFile);

        _file     = pFile;
        _filePath = a_filePath;
    }

    // buffering
    if (!a_isUseBuffering) {
        setVBuff(NULL, bmNo,   0);
    } else {
        setVBuff(NULL, bmFull, BUFSIZ);
    }
}
//------------------------------------------------------------------------------
xINLINE_HO std::FILE *
CxFile::get() const
{
    xTEST_EQ(true, isValid());

    return _file;
}
//------------------------------------------------------------------------------
xINLINE_HO std::ctstring_t &
CxFile::path() const
{
    xTEST_EQ(false, _filePath.empty());
    xTEST_EQ(true,  isExists(_filePath));

    return _filePath;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxFile::attach(
    std::FILE *a_file
)
{
    xTEST_NA(a_file);

    close();

    _file     = a_file;
    _filePath = CxConst::xSTR_EMPTY();
}
//------------------------------------------------------------------------------
xINLINE_HO std::FILE *
CxFile::detach()
{
    std::FILE *pFile = get();

    _file = NULL;

    return pFile;
}
//------------------------------------------------------------------------------


/*******************************************************************************
* public: read / write
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO size_t
CxFile::read(
    void_t       *a_buff,
    std::csize_t &a_count
) const
{
    xTEST_PTR(a_buff);
    xTEST_NA(a_count);

    size_t uiRes = std::fread(a_buff, 1, a_count, get());
    xTEST_GR_EQ(a_count, uiRes);

    return uiRes;
}
//------------------------------------------------------------------------------
xINLINE_HO size_t
CxFile::write(
    cvoid_t      *a_buff,
    std::csize_t &a_count
) const
{
    xTEST_PTR(a_buff);
    xTEST_NA(a_count);

    size_t uiRes = std::fwrite(a_buff, 1, a_count, get());
    xTEST_EQ(a_count, uiRes);

    return uiRes;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxFile::read(
    std::ustring_t *a_buff
) const
{
    xTEST_PTR(a_buff);

    longlong_t llFileSize = size();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    (*a_buff).clear();
    (*a_buff).resize( static_cast<size_t>( llFileSize ) );
    xCHECK_DO(0LL == llFileSize, return);

    size_t uiRes = std::fread(&(*a_buff).at(0), 1, (*a_buff).size() * sizeof(std::ustring_t::value_type), get());
    xTEST_EQ((*a_buff).size(), uiRes);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxFile::write(
    std::custring_t &a_buff
) const
{
    xTEST_NA(a_buff);

    size_t uiRes = std::fwrite(&a_buff.at(0), 1, a_buff.size() * sizeof(std::ustring_t::value_type), get());
    xTEST_EQ(a_buff.size(), uiRes);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxFile::read(
    std::tstring_t *a_buff
) const
{
    xTEST_PTR(a_buff);

    longlong_t llFileSize = size();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    (*a_buff).clear();
    (*a_buff).resize( static_cast<size_t>( llFileSize) );
    xCHECK_DO(0LL == llFileSize, return);

    size_t uiRes = std::fread(&(*a_buff).at(0), 1, (*a_buff).size() * sizeof(std::tstring_t::value_type), get());
    xTEST_EQ((*a_buff).size(), uiRes);
}
//------------------------------------------------------------------------------
xINLINE_HO int_t
CxFile::write(
    ctchar_t *a_format, ...
) const
{
    xTEST_PTR(a_format);

    va_list vlArgs;
    xVA_START(vlArgs, a_format);

    int_t iRv = std::xTVFPRINTF(get(), a_format, vlArgs);
    xTEST_LESS(- 1, iRv);

    xVA_END(vlArgs);

    return iRv;
}
//------------------------------------------------------------------------------
xINLINE_HO int_t
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
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxFile::readLine(
    std::tstring_t *a_str,
    std::csize_t   &a_maxCount
) const
{
    xTEST_PTR(a_str);
    xTEST_NA(a_maxCount);

    std::tstring_t sStr;
    sStr.resize(a_maxCount + 1); // + 1 for 0

    tchar_t *pszRes = std::xTFGETS(&sStr.at(0), static_cast<int_t>( sStr.size() ), get());
    xTEST_PTR(pszRes);

    sStr.erase(sStr.end() - 1); // erase last char - 0

    // out
    (*a_str).swap(sStr);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxFile::writeLine(
    std::ctstring_t &a_str
) const
{
    xTEST_NA(a_str);

    int_t iRv = xTFPUTS((a_str + CxConst::xEOL()).c_str(), get());
    xTEST_DIFF(- 1, iRv);
}
//------------------------------------------------------------------------------
xINLINE_HO tchar_t
CxFile::readChar() const
{
    twint_t iRv = std::xTFGETC(get());
    xTEST_DIFF(xTEOF, iRv);

    return static_cast<tchar_t>( iRv );
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxFile::writeChar(
    ctchar_t &a_ch
) const
{
    xTEST_NA(a_ch);

    twint_t iRv = xTFPUTC(a_ch, get());
    xTEST_DIFF(xTEOF, iRv);
    xTEST_EQ(a_ch, static_cast<tchar_t>( iRv ));
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxFile::ungetChar(
    ctchar_t &a_ch
) const
{
    xTEST_NA(a_ch);

    twint_t iRv = std::xTUNGETC(a_ch, get());
    xTEST_DIFF(xTEOF, iRv);
    xTEST_EQ(a_ch, static_cast<tchar_t>( iRv ));
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxFile::clear() const
{
    resize(0L);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: other
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxFile::locking(
    const ExLockingMode &a_mode,
    clong_t             &a_bytes
)
{
    xTEST_NA(a_mode);
    xTEST_NA(a_bytes);

#if xOS_ENV_WIN
    clong_t bytes = a_bytes;
#else
    const off_t bytes = static_cast<off_t>( a_bytes );
#endif

    int_t iRv = ::xLOCKING(_nativeHandle(get()), a_mode, bytes);
    xTEST_DIFF(- 1, iRv);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
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
//------------------------------------------------------------------------------
xINLINE_HO long_t
CxFile::position() const {
    long_t liRv = std::ftell(get());
    xTEST_DIFF(- 1L, liRv);

    return liRv;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
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
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xINLINE_HO void_t
CxFile::setMode(
    const ExTranslationMode &a_mode
) const
{
    xTEST_NA(a_mode);

    int_t iRv = ::setmode(_nativeHandle(get()), a_mode);
    xTEST_DIFF(- 1, iRv);
}

#endif
//------------------------------------------------------------------------------
// NOTE: https://www.securecoding.cert.org/confluence/display/seccode/FIO19-C.+Do+not+use+fseek()+and+ftell()+to+compute+the+size+of+a+file
xINLINE_HO longlong_t
CxFile::size() const
{
#if xDEPRECIATE
    vFlush();

    xTSTAT_STRUCT stStat = {0};

    // TODO: fstat
    int_t iRv = ::xTSTAT(_filePath.c_str(), &stStat);
    xTEST_DIFF(- 1, iRv);

    return stStat.st_size;
#else
    long_t liStreamSize    = - 1L;
    long_t liCurrStreamPos = - 1L;

    liCurrStreamPos = position();
    setPosition(0, ppEnd);

    liStreamSize = position();
    setPosition(liCurrStreamPos, ppBegin);

    return static_cast<longlong_t>( liStreamSize );
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
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

    int_t iRv = ::xCHSIZE(_nativeHandle(get()), _size);
    xTEST_EQ(0, iRv);
    xTEST_EQ(a_size, size());
}
//------------------------------------------------------------------------------

/*******************************************************************************
*    public: error handling
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxFile::isValid() const
{
    return (NULL != _file);
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxFile::isOpen() const
{
    return isValid();
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxFile::isEmpty() const
{
    longlong_t llFileSize = size();
    xTEST_DIFF(- 1LL, llFileSize);

    return (0LL == llFileSize);
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxFile::isEof() const
{
    bool_t bRv = xINT_TO_BOOL( std::feof(get()) );
    xTEST_NA(bRv);

    return bRv;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxFile::isError() const
{
    bool_t bRv = xINT_TO_BOOL( std::ferror(get()) );
    xTEST_NA(bRv);

    return bRv;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxFile::errorClear() const
{
    (void_t)std::clearerr( get() );
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: closing
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxFile::flush() const
{
    int_t iRv = std::fflush(get());
    xTEST_DIFF(EOF, iRv);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxFile::close()
{
    xCHECK_DO(!isValid(), return);

    errorClear();

    int_t iRv = std::fclose(get()); _file = NULL;
    xTEST_DIFF(EOF, iRv);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public, static
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
xINLINE_HO bool_t
CxFile::isFile(
    std::ctstring_t &a_filePath
)
{
    xTEST_NA(a_filePath);

    bool_t bRv = false;

    CxFileType ftType(a_filePath);

    xCHECK_RET(CxFileType::faInvalid == ftType.get(), false);

#if xOS_ENV_WIN
    bRv = ftType.isExists(CxFileType::faDirectory);
    xCHECK_RET(bRv, false);

    bRv = ftType.isExists(CxFileType::faDevice);
    xCHECK_RET(bRv, false);

    bRv = ftType.isExists(CxFileType::faReparsePoint);
    xCHECK_RET(bRv, false);

    bRv = ftType.isExists(CxFileType::faOffline);
    xCHECK_RET(bRv, false);
#else
    bRv = ftType.isExists(CxFileType::faRegularFile);
    xCHECK_RET(!bRv, false);
#endif

    return true;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO bool_t
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
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxFile::isExistsEx(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(false, a_filePath.empty());

    std::tstring_t sRv;

    CxPath ptPath(a_filePath);

    std::tstring_t sFileDir  = ptPath.dir();
    std::tstring_t sFileName = ptPath.fileBaseName();
    std::tstring_t sFileExt  = ptPath.ext();

    xCHECK_DO(!sFileExt.empty(), sFileExt.insert(0, CxConst::xDOT()));

    for (ulong_t ulExistsIndex = 1; ; ++ ulExistsIndex) {
        sRv = CxString::format(xT("%s%s%s (%lu)%s"),
                               sFileDir.c_str(),
                               CxConst::xSLASH().c_str(),
                               sFileName.c_str(),
                               ulExistsIndex,
                               sFileExt.c_str());

        xCHECK_DO(!isExists(sRv), break);
    }

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
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
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
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
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxFile::clear(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(false, a_filePath.empty());

    CxFile sfFile;

    sfFile.create(a_filePath, omWrite, true);
    sfFile.clear();
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxFile::remove(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(false, a_filePath.empty());

    xCHECK_DO(!isExists(a_filePath), return);

    chmod(a_filePath, pmWrite);

    int_t iRv = ::xTREMOVE(a_filePath.c_str());
    xTEST_DIFF(- 1, iRv);
    xTEST_EQ(false, isExists(a_filePath));
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxFile::tryRemove(
    std::ctstring_t &a_filePath,
    std::csize_t    &a_attempts,
    culong_t        &a_timeoutMsec
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_LESS(size_t(0U), a_attempts);
    xTEST_NA(a_timeoutMsec);

    std::csize_t cuiMaxAttempts  = 100;  // MAGIC_NUMBER: cuiMaxAttempts
    std::csize_t cuiRealAttempts = (cuiMaxAttempts < a_attempts) ? cuiMaxAttempts : a_attempts;

    for (size_t i = 0; i < cuiRealAttempts; ++ i) {
        try {
            remove(a_filePath);
            break;
        }
        catch (const CxException &) {
            xNA;
        }

        CxThread::currentSleep(a_timeoutMsec);
    }
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxFile::wipe(
    std::ctstring_t &a_filePath,
    std::csize_t    &a_passes
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_NA(a_passes);

    xCHECK_DO(!isExists(a_filePath), return);

    {
        CxFile sfFile;

        //--------------------------------------------------
        // set normal file attributes
        CxFileType(a_filePath).clear();

        //--------------------------------------------------
        // open
        sfFile.create(a_filePath, omBinWrite, true);

        longlong_t llSize = sfFile.size();
        if (0LL < llSize) {
            //--------------------------------------------------
            // fill by 0x55, 0xAA, random char
            for (size_t p = 0; p < a_passes; ++ p) {
                CxRandom::vSetSeed();

                cuchar_t chRand  = static_cast<uchar_t>(CxRandom::liInt(0, 255) + 1);
                cuchar_t chChar1 = 0x55;
                cuchar_t chChar2 = 0xAA;

                // chRand
                {
                    sfFile.setPosition(0L, ppBegin);

                    for (longlong_t i = 0LL; i < llSize; ++ i) {
                        size_t uiRes = std::fwrite(&chRand, 1, sizeof(chRand), sfFile.get());
                        xTEST_EQ(sizeof(chRand), uiRes);
                    }
                }

                // chChar1
                {
                    sfFile.setPosition(0L, ppBegin);

                    for (longlong_t i = 0LL; i < llSize; ++ i) {
                        size_t uiRes = std::fwrite(&chChar1, 1, sizeof(chChar1), sfFile.get());
                        xTEST_EQ(sizeof(chChar1), uiRes);
                    }
                }

                // chChar2
                {
                    sfFile.setPosition(0L, ppBegin);

                    for (longlong_t i = 0LL; i < llSize; ++ i) {
                        size_t uiRes = std::fwrite(&chChar2, 1, sizeof(chChar2), sfFile.get());
                        xTEST_EQ(sizeof(chChar2), uiRes);
                    }
                }
            }

            //--------------------------------------------------
            // truncate
            sfFile.flush();
            sfFile.resize(0L);
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
    std::tstring_t sRndFilePath;

    {
        std::tstring_t sRndFileName;

        sRndFileName = CxString::cast( CxDateTime().current().toMilliseconds() );
        std::random_shuffle(sRndFileName.begin(), sRndFileName.end());

        sRndFilePath = CxPath(a_filePath).dir() + CxConst::xSLASH() + sRndFileName;

        rename(a_filePath, sRndFilePath);
    }

    //--------------------------------------------------
    // delete
    remove(sRndFilePath);
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxFile::unlink(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(false, a_filePath.empty());

    int_t iRv = ::xTUNLINK(a_filePath.c_str());
    xTEST_DIFF(- 1, iRv);
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxFile::rename(
    std::ctstring_t &a_filePathOld,
    std::ctstring_t &a_filePathNew
)
{
    xTEST_EQ(false, a_filePathOld.empty());
    xTEST_EQ(false, a_filePathNew.empty());

    int_t iRv = ::xTRENAME(a_filePathOld.c_str(), a_filePathNew.c_str());
    xTEST_DIFF(- 1, iRv);
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxFile::move(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_dirPath
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_EQ(false, a_dirPath.empty());

    rename(a_filePath, CxPath(a_dirPath).slashAppend() + CxPath(a_filePath).fileName());
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxFile::copy(
    std::ctstring_t &a_filePathFrom,
    std::ctstring_t &a_filePathTo,
    cbool_t         &a_isFailIfExists
)
{
    xTEST_EQ(false, a_filePathFrom.empty());
    xTEST_EQ(false, a_filePathTo.empty());
    xTEST_NA(a_isFailIfExists);

    bool_t bIsCopyOk = true;

    //--------------------------------------------------
    // TODO: fail if exists
#if xTODO
    if (isFailIfExists && bIsExists(filePathTo)) {
        xTEST_FAIL;
    }
#endif

    // TODO: check file size

    {
        //--------------------------------------------------
        // open files
        CxFile sfFrom;
        sfFrom.create(a_filePathFrom, omBinRead, true);

        CxFile sfTo;
        sfTo.create(a_filePathTo, omBinWrite, true);

        //--------------------------------------------------
        // copy files
        std::csize_t cuiBuffSize         = 1024;
        uchar_t      ucBuff[cuiBuffSize] = {0};

        xFOREVER {
            std::csize_t uiReaded  = sfFrom.read(ucBuff, cuiBuffSize);
            xCHECK_DO(0 >= uiReaded, break);

            std::csize_t uiWritten = sfTo.write(ucBuff, uiReaded);
            xCHECK_DO(uiReaded != uiWritten, bIsCopyOk = false; break);
        }
    }

    //--------------------------------------------------
    // if copy fail - delete out file
    xCHECK_DO(!bIsCopyOk, remove(a_filePathTo); return /* false */);

    //--------------------------------------------------
    // test for size, maybe CRC
    xCHECK_DO(size(a_filePathFrom) != size(a_filePathTo), remove(a_filePathTo); return /* false */);
}
//--------------------------------------------------------------------------
/* static */
xINLINE_HO longlong_t
CxFile::size(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_EQ(true,  isExists(a_filePath));

    CxFile sfFile;

    sfFile.create(a_filePath, omRead, true);
    longlong_t liRv = sfFile.size();
    xTEST_LESS_EQ(0LL, liRv);

    return liRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO ulonglong_t
CxFile::lines(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_EQ(true,  isExists(a_filePath));

    std::locale::global(std::locale());

    ulonglong_t      ullRv = 0LL;
    std::tifstream_t ifsStream(a_filePath.c_str(), std::ios::in);

    xCHECK_RET(!ifsStream || ifsStream.fail() || !ifsStream.good() || !ifsStream.is_open() || ifsStream.eof(), 0LL);

    tchar_t chChar;
    for (ullRv = 0LL; ifsStream.get(chChar); ) {
        xCHECK_DO(xT('\n') == chChar, ++ ullRv);
    }

    return ullRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
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
    FILETIME ftCreate   = {0};
    FILETIME ftAccess   = {0};
    FILETIME ftModified = {0};

    CxHandleInvalid m_hHandle;

    m_hHandle = ::CreateFile(a_filePath.c_str(), GENERIC_READ, FILE_SHARE_READ,
                             NULL, OPEN_EXISTING, CxFileType::faNormal, NULL);
    xTEST_EQ(true, m_hHandle.isValid());

    BOOL blRes = ::GetFileTime(m_hHandle.get(), &ftCreate, &ftAccess, &ftModified);
    xTEST_DIFF(FALSE, blRes);

    CxUtils::ptrAssignT(a_create,   CxDateTime::fileTimeToUnixTime(ftCreate));
    CxUtils::ptrAssignT(a_access,   CxDateTime::fileTimeToUnixTime(ftAccess));
    CxUtils::ptrAssignT(a_modified, CxDateTime::fileTimeToUnixTime(ftModified));
#else
    xTSTAT_STRUCT stInfo = {0};

    int_t iRv = ::xTSTAT(a_filePath.c_str(), &stInfo);
    xTEST_DIFF(- 1, iRv);

    // create - n/a
    CxUtils::ptrAssignT(a_access,   stInfo.st_atime);
    CxUtils::ptrAssignT(a_modified, stInfo.st_mtime);
#endif
}
//------------------------------------------------------------------------------
/*static */
xINLINE_HO void_t
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
    FILETIME ftCreate = {0};
    CxDateTime::unixTimeToFileTime(a_create, &ftCreate);

    FILETIME ftAccess = {0};
    CxDateTime::unixTimeToFileTime(a_access, &ftAccess);

    FILETIME ftModified = {0};
    CxDateTime::unixTimeToFileTime(a_modified, &ftModified);

    CxHandleInvalid m_hHandle;

    m_hHandle = ::CreateFile(a_filePath.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE,
                             NULL, OPEN_EXISTING, CxFileType::faNormal, NULL);
    xTEST_EQ(true, m_hHandle.isValid());

    BOOL blRes = ::SetFileTime(m_hHandle.get(), &ftCreate, &ftAccess, &ftModified);
    xTEST_DIFF(FALSE, blRes);
#else
    utimbuf tbTimes = {0};

    // create - n/a
    tbTimes.actime  = a_access;
    tbTimes.modtime = a_modified;

    int_t iRv = ::utime(a_filePath.c_str(), &tbTimes);
    xTEST_DIFF(- 1, iRv);
#endif
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: text
*
*******************************************************************************/

//--------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxFile::textRead(
    std::ctstring_t &a_filePath,
    std::tstring_t  *a_content
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_PTR(a_content);

    CxFile         sfFile;
    std::tstring_t sRv;

    sfFile.create(a_filePath, omBinRead, true);

    longlong_t llFileSize = sfFile.size();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    xCHECK_DO(0LL == llFileSize, (*a_content).clear(); return);

    sRv.resize( static_cast<size_t>( llFileSize) );

    size_t uiReadLen = sfFile.read((void_t *)&sRv.at(0), sRv.size());
    xTEST_EQ(sRv.size(), uiReadLen);

    // out
    a_content->swap(sRv);
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxFile::textWrite(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_content
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_NA(a_content);

    // TODO: if content.empty()

    CxFile sfFile;

    sfFile.create(a_filePath, omBinWrite, true);

    xCHECK_DO(a_content.empty(), return);

    size_t uiWriteLen = sfFile.write((void_t *)&a_content.at(0), a_content.size());
    xTEST_EQ(a_content.size(), uiWriteLen);
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxFile::textRead(
    std::ctstring_t    &a_filePath,
    std::vec_tstring_t *a_content
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_EQ(true,  isExists(a_filePath));
    xTEST_PTR(a_content);

    std::vec_tstring_t vsRes;
    std::tstring_t     sFileContent;

    textRead(a_filePath, &sFileContent);

    CxString::split(sFileContent, CxConst::xNL(), &vsRes);

    // out
    a_content->swap(vsRes);
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxFile::textWrite(
    std::ctstring_t     &a_filePath,
    std::cvec_tstring_t &a_content
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_NA(a_content);

    // TODO: if content.empty()

    std::tstring_t sFileContent;

    sFileContent = CxString::join(a_content, CxConst::xNL());

    textWrite(a_filePath, sFileContent);
}
//--------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
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
    xCHECK_DO(0L == size(a_filePath), (*a_content).clear(); return);

    std::locale::global(std::locale());

    std::tifstream_t ifsStream(a_filePath.c_str());
    xTEST_EQ(true,  !! ifsStream);
    xTEST_EQ(false, ifsStream.fail());
    xTEST_EQ(true,  ifsStream.good());
    xTEST_EQ(true,  ifsStream.is_open());
    xTEST_EQ(false, ifsStream.eof());

    std::map_tstring_t msRv;
    std::tstring_t     sLine;
    std::vec_tstring_t vsLine;

    for (size_t i = 0; !ifsStream.eof(); ++ i) {
        std::getline(ifsStream, sLine);

        sLine = CxString::trimRightChars(sLine, CxConst::xEOL());

        CxString::split(sLine, a_separator, &vsLine);
        xTEST_EQ(size_t(2), vsLine.size());

        msRv.insert( std::pair<std::tstring_t, std::tstring_t>(vsLine.at(0), vsLine.at(1)) );
    }

    // out
    (*a_content).swap(msRv);

#if xTODO
    bool_t               bRv = false;
    std::map_tstring_t msRv;
    std::vec_tstring_t vsRes;

    bRv = textRead(filePath, &vsRes);
    xTEST_EQ(true, bRv);

    std::vec_tstring_t::_const_iterator it;
    for (it = vsRes.begin(); it != vsRes.end(); ++ it) {
        std::vec_tstring_t vsLine;

        CxString::split(vsRes.at(0), separator, &vsLine);
        msRv.insert( std::pair<std::tstring_t, std::tstring_t>(vsLine.at(0), vsLine.at(1)) );
    }

    //out
    content.swap(msRv);
#endif
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxFile::textWrite(
    std::ctstring_t     &a_filePath,
    std::ctstring_t     &a_separator,
    std::cmap_tstring_t &a_content
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_EQ(false, a_separator.empty());
    xTEST_NA(a_content);

    // TODO: if cmsFile.empty()

    CxFile stdFile;

    stdFile.create(a_filePath, omWrite, true);

    typedef std::map_tstring_t TContent;

    xFOREACH_CONST(TContent, it, a_content) {
        stdFile.writeLine((*it).first + a_separator + (*it).second);
    }

#if xTODO
    std::tstring_t sRv;

    xFOREACH_CONST(TContent, it, content) {
        sRv.append((*it).first);
        sRv.append(separator);
        sRv.append((*it).second);
        sRv.append(CxConst::xNL());

        xCHECK_DO(it != content.end(), sRv.append(CxConst::xNL()));
    }

    textWrite(filePath, sRv);
#endif
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: bin
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxFile::binRead(
    std::ctstring_t &a_filePath,
    std::ustring_t  *a_content
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_PTR(a_content);

    CxFile         sfFile;
    std::ustring_t usRv;

    sfFile.create(a_filePath, omBinRead, true);

    longlong_t llFileSize = sfFile.size();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    xCHECK_DO(0LL == llFileSize, (*a_content).clear(); return);

    usRv.resize( static_cast<size_t>( llFileSize ) );

    size_t uiReadLen = sfFile.read((void_t *)&usRv.at(0), usRv.size());
    xTEST_EQ(usRv.size(), uiReadLen);

    // out
    a_content->swap(usRv);
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxFile::binWrite(
    std::ctstring_t &a_filePath,
    std::custring_t &a_content
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_NA(a_content);

    // TODO: if content.empty()

    CxFile sfFile;

    sfFile.create(a_filePath, omBinWrite, true);

    xCHECK_DO(a_content.empty(), return);

    size_t uiWriteLen = sfFile.write((void_t *)&a_content.at(0), a_content.size());
    xTEST_EQ(a_content.size(), uiWriteLen);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
xINLINE_HO int_t
CxFile::_nativeHandle(
    std::FILE *a_file
)
{
    xTEST_PTR(a_file);

    int_t iRv = /*::*/fileno(a_file);
    xTEST_DIFF(- 1, iRv);

    return iRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::FILE *
CxFile::_stdHandle(
    int_t             a_fileHandle,
    const ExOpenMode &a_mode
)
{
    xTEST_NA(a_fileHandle);
    xTEST_NA(a_mode);

    std::FILE *pfRes = ::xTFDOPEN(a_fileHandle, _openMode(a_mode).c_str());
    xTEST_PTR(pfRes);

    return pfRes;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
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
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
