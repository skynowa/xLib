/**
 * \file  CxFile.cpp
 * \brief file
 */


#include <xLib/Filesystem/CxFile.h>

#include <xLib/Common/CxString.h>
#include <xLib/Common/CxLocale.h>
#include <xLib/Common/CxDateTime.h>
#include <xLib/Debug/CxException.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxFileType.h>
#include <xLib/Crypt/CxRandom.h>
#include <xLib/Sync/CxCurrentThread.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public: constructors, destructor
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxFile::CxFile() :
    _m_pFile    (NULL),
    _m_sFilePath()
{
}
//------------------------------------------------------------------------------
/* virtual */
CxFile::~CxFile() {
    close();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: open, get
*
*******************************************************************************/

//------------------------------------------------------------------------------
void_t
CxFile::create(
    std::ctstring_t  &a_csFilePath,
    const ExOpenMode &a_comMode,
    cbool_t          &a_cbIsUseBuffering
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_comMode);
    xTEST_NA(a_cbIsUseBuffering);

    // create dir
    CxDir( CxPath(a_csFilePath).dir() ).pathCreate();

    // create, open file
    {
        std::FILE *pFile = ::xTFOPEN(a_csFilePath.c_str(), _openMode(a_comMode).c_str());
        xTEST_PTR(pFile);

        _m_pFile     = pFile;
        _m_sFilePath = a_csFilePath;
    }

    // buffering
    if (!a_cbIsUseBuffering) {
        setVBuff(NULL, bmNo,   0);
    } else {
        setVBuff(NULL, bmFull, BUFSIZ);
    }
}
//------------------------------------------------------------------------------
void_t
CxFile::reopen(
    std::ctstring_t  &a_csFilePath,
    const ExOpenMode &a_comMode,
    cbool_t          &a_cbIsUseBuffering
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_comMode);
    xTEST_NA(a_cbIsUseBuffering);

    // create dir
    CxDir( CxPath(a_csFilePath).dir() ).pathCreate();

    // create, reopen file
    {
        std::FILE *pFile = ::xTFREOPEN(a_csFilePath.c_str(), _openMode(a_comMode).c_str(), get());
        xTEST_PTR(pFile);

        _m_pFile     = pFile;
        _m_sFilePath = a_csFilePath;
    }

    // buffering
    if (!a_cbIsUseBuffering) {
        setVBuff(NULL, bmNo,   0);
    } else {
        setVBuff(NULL, bmFull, BUFSIZ);
    }
}
//------------------------------------------------------------------------------
std::FILE *
CxFile::get() const {
    xTEST_EQ(true, isValid());

    return _m_pFile;
}
//------------------------------------------------------------------------------
std::ctstring_t &
CxFile::path() const {
    xTEST_EQ(false, _m_sFilePath.empty());
    xTEST_EQ(true,  isExists(_m_sFilePath));

    return _m_sFilePath;
}
//------------------------------------------------------------------------------
void_t
CxFile::attach(
    std::FILE *a_pflFile
)
{
    xTEST_NA(a_pflFile);

    close();

    _m_pFile     = a_pflFile;
    _m_sFilePath = CxConst::xSTR_EMPTY;
}
//------------------------------------------------------------------------------
std::FILE *
CxFile::detach() {
    std::FILE *pFile = get();

    _m_pFile = NULL;

    return pFile;
}
//------------------------------------------------------------------------------


/*******************************************************************************
* public: read / write
*
*******************************************************************************/

//------------------------------------------------------------------------------
size_t
CxFile::read(
    void_t       *a_pvBuff,
    std::csize_t &a_cuiCount
) const
{
    xTEST_PTR(a_pvBuff);
    xTEST_NA(a_cuiCount);

    size_t uiRes = std::fread(a_pvBuff, 1, a_cuiCount, get());
    xTEST_GR_EQ(a_cuiCount, uiRes);

    return uiRes;
}
//------------------------------------------------------------------------------
size_t
CxFile::write(
    cvoid_t      *a_pcvBuff,
    std::csize_t &a_cuiCount
) const
{
    xTEST_PTR(a_pcvBuff);
    xTEST_NA(a_cuiCount);

    size_t uiRes = std::fwrite(a_pcvBuff, 1, a_cuiCount, get());
    xTEST_EQ(a_cuiCount, uiRes);

    return uiRes;
}
//------------------------------------------------------------------------------
void_t
CxFile::read(
    std::ustring_t *a_psBuff
) const
{
    xTEST_PTR(a_psBuff);

    longlong_t llFileSize = size();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    (*a_psBuff).clear();
    (*a_psBuff).resize( static_cast<size_t>( llFileSize ) );
    xCHECK_DO(0LL == llFileSize, return);

    size_t uiRes = std::fread(&(*a_psBuff).at(0), 1, (*a_psBuff).size() * sizeof(std::ustring_t::value_type), get());
    xTEST_EQ((*a_psBuff).size(), uiRes);
}
//------------------------------------------------------------------------------
void_t
CxFile::write(
    std::custring_t &a_csBuff
) const
{
    xTEST_NA(a_csBuff);

    size_t uiRes = std::fwrite(&a_csBuff.at(0), 1, a_csBuff.size() * sizeof(std::ustring_t::value_type), get());
    xTEST_EQ(a_csBuff.size(), uiRes);
}
//------------------------------------------------------------------------------
void_t
CxFile::read(
    std::tstring_t *a_psBuff
) const
{
    xTEST_PTR(a_psBuff);

    longlong_t llFileSize = size();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    (*a_psBuff).clear();
    (*a_psBuff).resize( static_cast<size_t>( llFileSize) );
    xCHECK_DO(0LL == llFileSize, return);

    size_t uiRes = std::fread(&(*a_psBuff).at(0), 1, (*a_psBuff).size() * sizeof(std::tstring_t::value_type), get());
    xTEST_EQ((*a_psBuff).size(), uiRes);
}
//------------------------------------------------------------------------------
int_t
CxFile::write(
    ctchar_t *a_pcszFormat, ...
) const
{
    xTEST_PTR(a_pcszFormat);

    va_list vlArgs;
    xVA_START(vlArgs, a_pcszFormat);

    int_t iRv = std::xTVFPRINTF(get(), a_pcszFormat, vlArgs);
    xTEST_LESS(- 1, iRv);

    xVA_END(vlArgs);

    return iRv;
}
//------------------------------------------------------------------------------
int_t
CxFile::writeV(
    ctchar_t *a_pcszFormat,
    va_list   a_vlArgs
) const
{
    xTEST_PTR(a_pcszFormat);
    xTEST_PTR(a_vlArgs);

    int_t iRv = std::xTVFPRINTF(get(), a_pcszFormat, a_vlArgs);
    xTEST_LESS(- 1, iRv);

    return iRv;
}
//------------------------------------------------------------------------------
void_t
CxFile::readLine(
    std::tstring_t *a_psStr,
    std::csize_t   &a_cuiMaxCount
) const
{
    xTEST_PTR(a_psStr);
    xTEST_NA(a_cuiMaxCount);

    std::tstring_t sStr;
    sStr.resize(a_cuiMaxCount + 1); // + 1 for 0

    tchar_t *pszRes = std::xTFGETS(&sStr.at(0), static_cast<int_t>( sStr.size() ), get());
    xTEST_PTR(pszRes);

    sStr.erase(sStr.end() - 1); // erase last char - 0

    // out
    (*a_psStr).swap(sStr);
}
//------------------------------------------------------------------------------
void_t
CxFile::writeLine(
    std::ctstring_t &a_csStr
) const
{
    xTEST_NA(a_csStr);

    int_t iRv = xTFPUTS((a_csStr + CxConst::xEOL).c_str(), get());
    xTEST_DIFF(- 1, iRv);
}
//------------------------------------------------------------------------------
tchar_t
CxFile::readChar() const {
    twint_t iRv = std::xTFGETC(get());
    xTEST_DIFF(xTEOF, iRv);

    return static_cast<tchar_t>( iRv );
}
//------------------------------------------------------------------------------
void_t
CxFile::writeChar(
    ctchar_t &a_ccChar
) const
{
    xTEST_NA(a_ccChar);

    twint_t iRv = xTFPUTC(a_ccChar, get());
    xTEST_DIFF(xTEOF, iRv);
    xTEST_EQ(a_ccChar, static_cast<tchar_t>( iRv ));
}
//------------------------------------------------------------------------------
void_t
CxFile::ungetChar(
    ctchar_t &a_ccChar
) const
{
    xTEST_NA(a_ccChar);

    twint_t iRv = std::xTUNGETC(a_ccChar, get());
    xTEST_DIFF(xTEOF, iRv);
    xTEST_EQ(a_ccChar, static_cast<tchar_t>( iRv ));
}
//------------------------------------------------------------------------------
void_t
CxFile::clear() const {
    resize(0L);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: other
*
*******************************************************************************/

//------------------------------------------------------------------------------
void_t
CxFile::locking(
    const ExLockingMode &a_clmMode,
    clong_t             &a_cliBytes
)
{
    xTEST_NA(a_clmMode);
    xTEST_NA(a_cliBytes);

#if   xOS_ENV_WIN
    clong_t cliBytes = a_cliBytes;
#elif xOS_ENV_UNIX
    const off_t  cliBytes = static_cast<off_t>( a_cliBytes );
#endif

    int_t iRv = ::xLOCKING(_nativeHandle(get()), a_clmMode, cliBytes);
    xTEST_DIFF(- 1, iRv);
}
//------------------------------------------------------------------------------
void_t
CxFile::setPosition(
    clong_t                 &a_clOffset,
    const ExPointerPosition &a_cppPos
) const
{
    xTEST_NA(a_clOffset);
    xTEST_NA(a_cppPos);

    int_t iRv = std::fseek(get(), a_clOffset, a_cppPos);
    xTEST_DIFF(- 1, iRv);
}
//------------------------------------------------------------------------------
long_t
CxFile::position() const {
    long_t liRv = std::ftell(get());
    xTEST_DIFF(- 1L, liRv);

    return liRv;
}
//------------------------------------------------------------------------------
void_t
CxFile::setVBuff(
    char                  *a_pszBuff,
    const ExBufferingMode &a_cbmMode,
    std::csize_t          &a_cuiSize
) const
{
    xTEST_NA(a_pszBuff);
    xTEST_NA(a_cbmMode);
    xTEST_NA(a_cuiSize);

    int_t iRv = std::setvbuf(get(), a_pszBuff, a_cbmMode, a_cuiSize);
    xTEST_DIFF(- 1, iRv);
}
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

void_t
CxFile::setMode(
    const ExTranslationMode &a_ctmMode
) const
{
    xTEST_NA(a_ctmMode);

    int_t iRv = ::setmode(_nativeHandle(get()), a_ctmMode);
    xTEST_DIFF(- 1, iRv);
}

#endif
//------------------------------------------------------------------------------
// NOTE: https://www.securecoding.cert.org/confluence/display/seccode/FIO19-C.+Do+not+use+fseek()+and+ftell()+to+compute+the+size+of+a+file
longlong_t
CxFile::size() const {
#if xDEPRECIATE
    vFlush();

    xTSTAT_STRUCT stStat = {0};

    // TODO: fstat
    int_t iRv = ::xTSTAT(_m_sFilePath.c_str(), &stStat);
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
void_t
CxFile::resize(
    clonglong_t &a_cllSize
) const
{
    xTEST_NA(a_cllSize);

#if   xOS_ENV_WIN
    clonglong_t cllSize = a_cllSize;
#elif xOS_ENV_UNIX
    const off_t      cllSize = static_cast<off_t>( a_cllSize );
#endif

    int_t iRv = ::xCHSIZE(_nativeHandle(get()), cllSize);
    xTEST_EQ(0, iRv);
    xTEST_EQ(a_cllSize, size());
}
//------------------------------------------------------------------------------

/*******************************************************************************
*    public: error handling
*
*******************************************************************************/

//------------------------------------------------------------------------------
bool_t
CxFile::isValid() const {
    return (NULL != _m_pFile);
}
//------------------------------------------------------------------------------
bool_t
CxFile::isOpen() const {
    return isValid();
}
//------------------------------------------------------------------------------
bool_t
CxFile::isEmpty() const {
    longlong_t llFileSize = size();
    xTEST_DIFF(- 1LL, llFileSize);

    return (0LL == llFileSize);
}
//------------------------------------------------------------------------------
bool_t
CxFile::isEof() const {
    bool_t bRv = xINT_TO_BOOL( std::feof(get()) );
    xTEST_NA(bRv);

    return bRv;
}
//------------------------------------------------------------------------------
bool_t
CxFile::isError() const {
    bool_t bRv = xINT_TO_BOOL( std::ferror(get()) );
    xTEST_NA(bRv);

    return bRv;
}
//------------------------------------------------------------------------------
void_t
CxFile::errorClear() const {
    (void_t)std::clearerr( get() );
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: closing
*
*******************************************************************************/

//------------------------------------------------------------------------------
void_t
CxFile::flush() const {
    int_t iRv = std::fflush(get());
    xTEST_DIFF(EOF, iRv);
}
//------------------------------------------------------------------------------
void_t
CxFile::close() {
    xCHECK_DO(!isValid(), return);

    errorClear();

    int_t iRv = std::fclose(get()); _m_pFile = NULL;
    xTEST_DIFF(EOF, iRv);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public, static
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
bool_t
CxFile::isFile(
    std::ctstring_t &a_csFilePath
)
{
    xTEST_NA(a_csFilePath);

    bool_t bRv = false;

    CxFileType faAttr(a_csFilePath);

    CxFileType::ExAttribute atAttribute = faAttr.get();
    xCHECK_RET(CxFileType::faInvalid == atAttribute, false);

#if   xOS_ENV_WIN
    bRv = faAttr.isExists(CxFileType::faDirectory);
    xCHECK_RET(bRv, false);

    bRv = faAttr.isExists(CxFileType::faDevice);
    xCHECK_RET(bRv, false);

    bRv = faAttr.isExists(CxFileType::faReparsePoint);
    xCHECK_RET(bRv, false);

    bRv = faAttr.isExists(CxFileType::faOffline);
    xCHECK_RET(bRv, false);
#elif xOS_ENV_UNIX
    bRv = faAttr.isExists(CxFileType::faRegularFile);
    xCHECK_RET(!bRv, false);
#endif

    return true;
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxFile::isExists(
    std::ctstring_t &a_csFilePath
)
{
    xTEST_NA(a_csFilePath);

    xCHECK_RET(!isFile(a_csFilePath), false);

    int_t iRv = ::xTACCESS(a_csFilePath.c_str(), amExistence);
    xCHECK_RET(- 1 == iRv && ENOENT == CxStdError::get(), false);

    return true;
}
//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxFile::isExistsEx(
    std::ctstring_t &a_csFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());

    std::tstring_t sRv;

    CxPath ptPath(a_csFilePath);

    std::tstring_t sFileDir  = ptPath.dir();
    std::tstring_t sFileName = ptPath.fileBaseName();
    std::tstring_t sFileExt  = ptPath.ext();

    xCHECK_DO(!sFileExt.empty(), sFileExt.insert(0, CxConst::xDOT));

    for (ulong_t ulExistsIndex = 1; ; ++ ulExistsIndex) {
        sRv = CxString::format(xT("%s%s%s (%lu)%s"),
                               sFileDir.c_str(),
                               CxConst::xSLASH.c_str(),
                               sFileName.c_str(),
                               ulExistsIndex,
                               sFileExt.c_str());

        xCHECK_DO(!isExists(sRv), break);
    }

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFile::access(
    std::ctstring_t    &a_csFilePath,
    const ExAccessMode &a_camMode
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_camMode);

    int_t iRv = ::xTACCESS(a_csFilePath.c_str(), a_camMode);
    xTEST_DIFF(- 1, iRv);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFile::chmod(
    std::ctstring_t        &a_csFilePath,
    const ExPermissionMode &a_cpmMode
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_cpmMode);

#if   xOS_ENV_WIN
    cint_t    cpmMode = static_cast<int_t>   ( a_cpmMode );
#elif xOS_ENV_UNIX
    const mode_t cpmMode = static_cast<mode_t>( a_cpmMode );
#endif

    int_t iRv = ::xTCHMOD(a_csFilePath.c_str(), cpmMode);
    xTEST_DIFF(- 1, iRv);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFile::clear(
    std::ctstring_t &a_csFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());

    CxFile sfFile;

    sfFile.create(a_csFilePath, omWrite, true);
    sfFile.clear();
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFile::remove(
    std::ctstring_t &a_csFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());

    xCHECK_DO(!isExists(a_csFilePath), return);

    chmod(a_csFilePath, pmWrite);

    int_t iRv = ::xTREMOVE(a_csFilePath.c_str());
    xTEST_DIFF(- 1, iRv);
    xTEST_EQ(false, isExists(a_csFilePath));
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFile::tryRemove(
    std::ctstring_t &a_csFilePath,
    std::csize_t    &a_cuiAttempts,
    culong_t        &a_culTimeoutMsec
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_LESS(size_t(0U), a_cuiAttempts);
    xTEST_NA(a_culTimeoutMsec);

    std::csize_t cuiMaxAttempts  = 100;  // MAGIC_NUMBER: cuiMaxAttempts
    std::csize_t cuiRealAttempts = (cuiMaxAttempts < a_cuiAttempts) ? cuiMaxAttempts : a_cuiAttempts;

    for (size_t i = 0; i < cuiRealAttempts; ++ i) {
        try {
            remove(a_csFilePath);
            break;
        }
        catch (const CxException &) {
            xNA;
        }

        CxCurrentThread::sleep(a_culTimeoutMsec);
    }
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFile::wipe(
    std::ctstring_t &a_csFilePath,
    std::csize_t    &a_cuiPasses
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_cuiPasses);

    xCHECK_DO(!isExists(a_csFilePath), return);

    {
        CxFile sfFile;

        //--------------------------------------------------
        // set normal file attributes
        CxFileType(a_csFilePath).clear();

        //--------------------------------------------------
        // open
        sfFile.create(a_csFilePath, omBinWrite, true);

        longlong_t llSize = sfFile.size();
        if (0LL < llSize) {
            //--------------------------------------------------
            // fill by 0x55, 0xAA, random char
            for (size_t p = 0; p < a_cuiPasses; ++ p) {
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
        const time_t ctmCreate   = 0;
        const time_t ctmAccess   = 0;
        const time_t ctmModified = 0;

        setTime(a_csFilePath, ctmCreate, ctmAccess, ctmModified);
    }

    //--------------------------------------------------
    // random file name
    std::tstring_t sRndFilePath;

    {
        std::tstring_t sRndFileName;

        sRndFileName = CxString::cast( CxDateTime().current().toMilliseconds() );
        std::random_shuffle(sRndFileName.begin(), sRndFileName.end());

        sRndFilePath = CxPath(a_csFilePath).dir() + CxConst::xSLASH + sRndFileName;

        rename(a_csFilePath, sRndFilePath);
    }

    //--------------------------------------------------
    // delete
    remove(sRndFilePath);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFile::unlink(
    std::ctstring_t &a_csFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());

    int_t iRv = ::xTUNLINK(a_csFilePath.c_str());
    xTEST_DIFF(- 1, iRv);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFile::rename(
    std::ctstring_t &a_csOldFilePath,
    std::ctstring_t &a_csNewFilePath
)
{
    xTEST_EQ(false, a_csOldFilePath.empty());
    xTEST_EQ(false, a_csNewFilePath.empty());

    int_t iRv = ::xTRENAME(a_csOldFilePath.c_str(), a_csNewFilePath.c_str());
    xTEST_DIFF(- 1, iRv);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFile::move(
    std::ctstring_t &a_csFilePath,
    std::ctstring_t &a_csDirPath
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_EQ(false, a_csDirPath.empty());

    rename(a_csFilePath, CxPath(a_csDirPath).slashAppend() + CxPath(a_csFilePath).fileName());
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFile::copy(
    std::ctstring_t &a_csFilePathFrom,
    std::ctstring_t &a_csFilePathTo,
    cbool_t         &a_cbFailIfExists
)
{
    xTEST_EQ(false, a_csFilePathFrom.empty());
    xTEST_EQ(false, a_csFilePathTo.empty());
    xTEST_NA(a_cbFailIfExists);

    bool_t bIsCopyOk = true;

    //--------------------------------------------------
    // TODO: fail if exists
#if xTODO
    if (cbFailIfExists && bIsExists(csFilePathTo)) {
        xTEST_FAIL;
    }
#endif

    // TODO: check file size

    {
        //--------------------------------------------------
        // open files
        CxFile sfFrom;
        sfFrom.create(a_csFilePathFrom, omBinRead, true);

        CxFile sfTo;
        sfTo.create(a_csFilePathTo, omBinWrite, true);

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
    xCHECK_DO(!bIsCopyOk, remove(a_csFilePathTo); return /* false */);

    //--------------------------------------------------
    // test for size, maybe CRC
    xCHECK_DO(size(a_csFilePathFrom) != size(a_csFilePathTo), remove(a_csFilePathTo); return /* false */);
}
//--------------------------------------------------------------------------
/* static */
longlong_t
CxFile::size(
    std::ctstring_t &a_csFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_EQ(true,  isExists(a_csFilePath));

    CxFile sfFile;

    sfFile.create(a_csFilePath, omRead, true);
    longlong_t liRv = sfFile.size();
    xTEST_LESS_EQ(0LL, liRv);

    return liRv;
}
//------------------------------------------------------------------------------
/* static */
ulonglong_t
CxFile::lines(
    std::ctstring_t &a_csFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_EQ(true,  isExists(a_csFilePath));

    std::locale::global(std::locale());

    ulonglong_t      ullRv = 0LL;
    std::tifstream_t ifsStream(a_csFilePath.c_str(), std::ios::in);

    xCHECK_RET(!ifsStream || ifsStream.fail() || !ifsStream.good() || !ifsStream.is_open() || ifsStream.eof(), 0LL);

    tchar_t chChar;
    for (ullRv = 0LL; ifsStream.get(chChar); ) {
        xCHECK_DO(xT('\n') == chChar, ++ ullRv);
    }

    return ullRv;
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFile::time(
    std::ctstring_t &a_csFilePath,
    time_t          *a_ptmCreate,
    time_t          *a_ptmAccess,
    time_t          *a_ptmModified
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_ptmCreate);
    xTEST_NA(a_ptmAccess);
    xTEST_NA(a_ptmModified);

#if   xOS_ENV_WIN
    FILETIME ftCreate   = {0};
    FILETIME ftAccess   = {0};
    FILETIME ftModified = {0};

    CxHandleInvalid m_hHandle;

    m_hHandle = ::CreateFile(a_csFilePath.c_str(), GENERIC_READ, FILE_SHARE_READ,
                             NULL, OPEN_EXISTING, CxFileType::faNormal, NULL);
    xTEST_EQ(true, m_hHandle.isValid());

    BOOL blRes = ::GetFileTime(m_hHandle.get(), &ftCreate, &ftAccess, &ftModified);
    xTEST_DIFF(FALSE, blRes);

    CxUtils::ptrAssignT(a_ptmCreate,   CxDateTime::fileTimeToUnixTime(ftCreate));
    CxUtils::ptrAssignT(a_ptmAccess,   CxDateTime::fileTimeToUnixTime(ftAccess));
    CxUtils::ptrAssignT(a_ptmModified, CxDateTime::fileTimeToUnixTime(ftModified));
#elif xOS_ENV_UNIX
    xTSTAT_STRUCT stInfo = {0};

    int_t iRv = ::xTSTAT(a_csFilePath.c_str(), &stInfo);
    xTEST_DIFF(- 1, iRv);

    // ctmCreate - n/a
    CxUtils::ptrAssignT(a_ptmAccess,   stInfo.st_atime);
    CxUtils::ptrAssignT(a_ptmModified, stInfo.st_mtime);
#endif
}
//------------------------------------------------------------------------------
/*static */
void_t
CxFile::setTime(
    std::ctstring_t &a_csFilePath,
    const time_t    &a_ctmCreate,
    const time_t    &a_ctmAccess,
    const time_t    &a_ctmModified
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_ctmCreate);
    xTEST_NA(a_ctmAccess);
    xTEST_NA(a_ctmModified);

#if   xOS_ENV_WIN
    FILETIME ftCreate = {0};
    CxDateTime::unixTimeToFileTime(a_ctmCreate, &ftCreate);

    FILETIME ftAccess = {0};
    CxDateTime::unixTimeToFileTime(a_ctmAccess, &ftAccess);

    FILETIME ftModified = {0};
    CxDateTime::unixTimeToFileTime(a_ctmModified, &ftModified);

    CxHandleInvalid m_hHandle;

    m_hHandle = ::CreateFile(a_csFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE,
                             NULL, OPEN_EXISTING, CxFileType::faNormal, NULL);
    xTEST_EQ(true, m_hHandle.isValid());

    BOOL blRes = ::SetFileTime(m_hHandle.get(), &ftCreate, &ftAccess, &ftModified);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    utimbuf tbTimes = {0};

    // ctmCreate - n/a
    tbTimes.actime  = a_ctmAccess;
    tbTimes.modtime = a_ctmModified;

    int_t iRv = ::utime(a_csFilePath.c_str(), &tbTimes);
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
void_t
CxFile::textRead(
    std::ctstring_t &a_csFilePath,
    std::tstring_t  *a_psContent
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_PTR(a_psContent);

    CxFile         sfFile;
    std::tstring_t sRv;

    sfFile.create(a_csFilePath, omBinRead, true);

    longlong_t llFileSize = sfFile.size();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    xCHECK_DO(0LL == llFileSize, (*a_psContent).clear(); return);

    sRv.resize( static_cast<size_t>( llFileSize) );

    size_t uiReadLen = sfFile.read((void_t *)&sRv.at(0), sRv.size());
    xTEST_EQ(sRv.size(), uiReadLen);

    // out
    std::swap((*a_psContent), sRv);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFile::textWrite(
    std::ctstring_t &a_csFilePath,
    std::ctstring_t &a_csContent
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_csContent);

    // TODO: if csContent.empty()

    CxFile sfFile;

    sfFile.create(a_csFilePath, omBinWrite, true);

    xCHECK_DO(a_csContent.empty(), return);

    size_t uiWriteLen = sfFile.write((void_t *)&a_csContent.at(0), a_csContent.size());
    xTEST_EQ(a_csContent.size(), uiWriteLen);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFile::textRead(
    std::ctstring_t    &a_csFilePath,
    std::vec_tstring_t *a_pvsContent
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_EQ(true,  isExists(a_csFilePath));
    xTEST_PTR(a_pvsContent);

    std::vec_tstring_t vsRes;
    std::tstring_t     sFileContent;

    textRead(a_csFilePath, &sFileContent);

    CxString::split(sFileContent, CxConst::xNL, &vsRes);

    // out
    std::swap((*a_pvsContent), vsRes);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFile::textWrite(
    std::ctstring_t     &a_csFilePath,
    std::cvec_tstring_t &a_cvsContent
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_cvsContent);

    // TODO: if cvsContent.empty()

    std::tstring_t sFileContent;

    sFileContent = CxString::join(a_cvsContent, CxConst::xNL);

    textWrite(a_csFilePath, sFileContent);
}
//--------------------------------------------------------------------------
/* static */
void_t
CxFile::textRead(
    std::ctstring_t    &a_csFilePath,
    std::ctstring_t    &a_csSeparator,
    std::map_tstring_t *a_pmsContent
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_EQ(true,  isExists(a_csFilePath));
    xTEST_PTR(a_pmsContent);

    // if file empty
    xCHECK_DO(0L == size(a_csFilePath), (*a_pmsContent).clear(); return);

    std::locale::global(std::locale());

    std::tifstream_t ifsStream(a_csFilePath.c_str());
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

        sLine = CxString::trimRightChars(sLine, CxConst::xEOL);

        CxString::split(sLine, a_csSeparator, &vsLine);
        xTEST_EQ(size_t(2), vsLine.size());

        msRv.insert( std::pair<std::tstring_t, std::tstring_t>(vsLine.at(0), vsLine.at(1)) );
    }

    // out
    (*a_pmsContent).swap(msRv);

#if xTODO
    bool_t               bRv = false;
    std::map_tstring_t msRv;
    std::vec_tstring_t vsRes;

    bRv = textRead(csFilePath, &vsRes);
    xTEST_EQ(true, bRv);

    std::vec_tstring_t::_const_iterator it;
    for (it = vsRes.begin(); it != vsRes.end(); ++ it) {
        std::vec_tstring_t vsLine;

        CxString::split(vsRes.at(0), csSeparator, &vsLine);
        msRv.insert( std::pair<std::tstring_t, std::tstring_t>(vsLine.at(0), vsLine.at(1)) );
    }

    //out
    std::swap((*pmsContent), msRv);
#endif
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFile::textWrite(
    std::ctstring_t     &a_csFilePath,
    std::ctstring_t     &a_csSeparator,
    std::cmap_tstring_t &a_cmsContent
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_EQ(false, a_csSeparator.empty());
    xTEST_NA(a_cmsContent);

    // TODO: if cmsFile.empty()

    CxFile stdFile;

    stdFile.create(a_csFilePath, omWrite, true);

    typedef std::map_tstring_t TContent;

    xFOREACH_CONST(TContent, it, a_cmsContent) {
        stdFile.writeLine((*it).first + a_csSeparator + (*it).second);
    }

#if xTODO
    std::tstring_t sRv;

    xFOREACH_CONST(TContent, it, cmsContent) {
        sRv.append((*it).first);
        sRv.append(csSeparator);
        sRv.append((*it).second);
        sRv.append(CxConst::xNL);

        xCHECK_DO(it != cmsContent.end(), sRv.append(CxConst::xNL));
    }

    textWrite(csFilePath, sRv);
#endif
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: bin
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
void_t
CxFile::binRead(
    std::ctstring_t &a_csFilePath,
    std::ustring_t  *a_pusContent
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_PTR(a_pusContent);

    CxFile         sfFile;
    std::ustring_t usRv;

    sfFile.create(a_csFilePath, omBinRead, true);

    longlong_t llFileSize = sfFile.size();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    xCHECK_DO(0LL == llFileSize, (*a_pusContent).clear(); return);

    usRv.resize( static_cast<size_t>( llFileSize ) );

    size_t uiReadLen = sfFile.read((void_t *)&usRv.at(0), usRv.size());
    xTEST_EQ(usRv.size(), uiReadLen);

    // out
    std::swap((*a_pusContent), usRv);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFile::binWrite(
    std::ctstring_t &a_csFilePath,
    std::custring_t &a_cusContent
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_cusContent);

    // TODO: if cusContent.empty()

    CxFile sfFile;

    sfFile.create(a_csFilePath, omBinWrite, true);

    xCHECK_DO(a_cusContent.empty(), return);

    size_t uiWriteLen = sfFile.write((void_t *)&a_cusContent.at(0), a_cusContent.size());
    xTEST_EQ(a_cusContent.size(), uiWriteLen);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
int_t
CxFile::_nativeHandle(
    std::FILE *a_pfFile
)
{
    xTEST_PTR(a_pfFile);

    int_t iRv = /*::*/fileno(a_pfFile);
    xTEST_DIFF(- 1, iRv);

    return iRv;
}
//------------------------------------------------------------------------------
/* static */
std::FILE *
CxFile::_stdHandle(
    int_t             a_iFileHandle,
    const ExOpenMode &a_omMode
)
{
    xTEST_NA(a_iFileHandle);
    xTEST_NA(a_omMode);

    std::FILE *pfRes = ::xTFDOPEN(a_iFileHandle, _openMode(a_omMode).c_str());
    xTEST_PTR(pfRes);

    return pfRes;
}
//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxFile::_openMode(
    const ExOpenMode &a_comMode
)
{
    xTEST_NA(a_comMode);

    std::tstring_t sRv;

    switch (a_comMode) {
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
