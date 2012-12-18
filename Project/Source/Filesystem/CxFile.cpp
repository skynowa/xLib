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
#include <xLib/Filesystem/CxFileAttribute.h>
#include <xLib/Crypt/CxRandom.h>
#include <xLib/Sync/CxCurrentThread.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public: constructors, destructor
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxFile::CxFile() :
    _m_pFile    (NULL),
    _m_sFilePath()
{
}
//---------------------------------------------------------------------------
/* virtual */
CxFile::~CxFile() {
    vClose();
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: open, get
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxFile::vCreate(
    const std::tstring_t &a_csFilePath,
    const ExOpenMode     &a_comMode,
    const bool           &a_cbIsUseBuffering
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_comMode);
    xTEST_NA(a_cbIsUseBuffering);

    // create dir
    CxDir( CxPath(a_csFilePath).sDir() ).vPathCreate();

    // create, open file
    std::FILE *pFile = ::xTFOPEN(a_csFilePath.c_str(), _sOpenMode(a_comMode).c_str());
    xTEST_PTR(pFile);

    _m_pFile     = pFile;
    _m_sFilePath = a_csFilePath;

    // buffering
    if (false == a_cbIsUseBuffering) {
        vSetVBuff(NULL, bmNo,   0);
    } else {
        vSetVBuff(NULL, bmFull, BUFSIZ);
    }
}
//---------------------------------------------------------------------------
void
CxFile::vReopen(
    const std::tstring_t &a_csFilePath,
    const ExOpenMode     &a_comMode,
    const bool           &a_cbIsUseBuffering
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_comMode);
    xTEST_NA(a_cbIsUseBuffering);

    std::FILE *pFile = ::xTFREOPEN(a_csFilePath.c_str(), _sOpenMode(a_comMode).c_str(), pGet());
    xTEST_PTR(pFile);

    _m_pFile     = pFile;
    _m_sFilePath = a_csFilePath;

    // buffering
    if (false == a_cbIsUseBuffering) {
        vSetVBuff(NULL, bmNo,   0);
    } else {
        vSetVBuff(NULL, bmFull, BUFSIZ);
    }
}
//---------------------------------------------------------------------------
void
CxFile::vAttach(
    std::FILE *a_pflFile
)
{
    xTEST_NA(a_pflFile);

    vClose();

    _m_pFile     = a_pflFile;
    _m_sFilePath = CxConst::xSTR_EMPTY;
}
//---------------------------------------------------------------------------
std::FILE *
CxFile::pDetach() {
    std::FILE *pFile = pGet();

    _m_pFile = NULL;

    return pFile;
}
//---------------------------------------------------------------------------
std::FILE *
CxFile::pGet() const {
    xTEST_EQ(true, bIsValid());

    return _m_pFile;
}
//---------------------------------------------------------------------------
std::tstring_t
CxFile::sPath() const {
    xTEST_EQ(false, _m_sFilePath.empty());
    xTEST_EQ(true,  bIsExists(_m_sFilePath));

    return _m_sFilePath;
}
//---------------------------------------------------------------------------


/****************************************************************************
* public: read / write
*
*****************************************************************************/

//---------------------------------------------------------------------------
size_t
CxFile::uiRead(
    void         *a_pvBuff,
    const size_t &a_cuiCount
) const
{
    xTEST_PTR(a_pvBuff);
    xTEST_NA(a_cuiCount);

    size_t uiRes = std::fread(a_pvBuff, 1, a_cuiCount, pGet());
    xTEST_GR_EQ(a_cuiCount, uiRes);

    return uiRes;
}
//---------------------------------------------------------------------------
size_t
CxFile::uiWrite(
    const void   *a_pcvBuff,
    const size_t &a_cuiCount
) const
{
    xTEST_PTR(a_pcvBuff);
    xTEST_NA(a_cuiCount);

    size_t uiRes = std::fwrite(a_pcvBuff, 1, a_cuiCount, pGet());
    xTEST_EQ(a_cuiCount, uiRes);

    return uiRes;
}
//---------------------------------------------------------------------------
void
CxFile::vRead(
    std::ustring_t *a_psBuff
) const
{
    xTEST_PTR(a_psBuff);

    longlong_t llFileSize = llSize();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    (*a_psBuff).clear();
    (*a_psBuff).resize( static_cast<size_t>( llFileSize ) );
    xCHECK_DO(0LL == llFileSize, return);

    size_t uiRes = std::fread(&(*a_psBuff).at(0), 1, (*a_psBuff).size() * sizeof(std::ustring_t::value_type), pGet());
    xTEST_EQ((*a_psBuff).size(), uiRes);
}
//---------------------------------------------------------------------------
void
CxFile::vWrite(
    const std::ustring_t &a_csBuff
) const
{
    xTEST_NA(a_csBuff);

    size_t uiRes = std::fwrite(&a_csBuff.at(0), 1, a_csBuff.size() * sizeof(std::ustring_t::value_type), pGet());
    xTEST_EQ(a_csBuff.size(), uiRes);
}
//---------------------------------------------------------------------------
void
CxFile::vRead(
    std::tstring_t *a_psBuff
) const
{
    xTEST_PTR(a_psBuff);

    longlong_t llFileSize = llSize();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    (*a_psBuff).clear();
    (*a_psBuff).resize( static_cast<size_t>( llFileSize) );
    xCHECK_DO(0LL == llFileSize, return);

    size_t uiRes = std::fread(&(*a_psBuff).at(0), 1, (*a_psBuff).size() * sizeof(std::tstring_t::value_type), pGet());
    xTEST_EQ((*a_psBuff).size(), uiRes);
}
//---------------------------------------------------------------------------
int
CxFile::iWrite(
    const tchar_t *a_pcszFormat, ...
) const
{
    xTEST_PTR(a_pcszFormat);

    va_list vlArgs;
    xVA_START(vlArgs, a_pcszFormat);

    int iRv = std::xTVFPRINTF(pGet(), a_pcszFormat, vlArgs);
    xTEST_LESS(- 1, iRv);

    xVA_END(vlArgs);

    return iRv;
}
//---------------------------------------------------------------------------
int
CxFile::iWriteV(
    const tchar_t *a_pcszFormat,
    va_list        a_vlArgs
) const
{
    xTEST_PTR(a_pcszFormat);
    xTEST_PTR(a_vlArgs);

    int iRv = std::xTVFPRINTF(pGet(), a_pcszFormat, a_vlArgs);
    xTEST_LESS(- 1, iRv);

    return iRv;
}
//---------------------------------------------------------------------------
void
CxFile::vReadLine(
    std::tstring_t *a_psStr,
    const size_t   &a_cuiMaxCount
) const
{
    xTEST_PTR(a_psStr);
    xTEST_NA(a_cuiMaxCount);

    std::tstring_t sStr;
    sStr.resize(a_cuiMaxCount + 1); // + 1 for 0

    tchar_t *pszRes = std::xTFGETS(&sStr.at(0), static_cast<int>( sStr.size() ), pGet());
    xTEST_PTR(pszRes);

    sStr.erase(sStr.end() - 1); // erase last char - 0

    // out
    (*a_psStr).swap(sStr);
}
//---------------------------------------------------------------------------
void
CxFile::vWriteLine(
    const std::tstring_t &a_csStr
) const
{
    xTEST_NA(a_csStr);

    int iRv = xTFPUTS((a_csStr + CxConst::xEOL).c_str(), pGet());
    xTEST_DIFF(- 1, iRv);
}
//---------------------------------------------------------------------------
tchar_t
CxFile::chReadChar() const {
    twint_t iRv = std::xTFGETC(pGet());
    xTEST_DIFF(xTEOF, iRv);

    return static_cast<tchar_t>( iRv );
}
//---------------------------------------------------------------------------
void
CxFile::vWriteChar(
    const tchar_t &a_ccChar
) const
{
    xTEST_NA(a_ccChar);

    twint_t iRv = xTFPUTC(a_ccChar, pGet());
    xTEST_DIFF(xTEOF, iRv);
    xTEST_EQ(a_ccChar, static_cast<tchar_t>( iRv ));
}
//---------------------------------------------------------------------------
void
CxFile::vUngetChar(
    const tchar_t &a_ccChar
) const
{
    xTEST_NA(a_ccChar);

    twint_t iRv = std::xTUNGETC(a_ccChar, pGet());
    xTEST_DIFF(xTEOF, iRv);
    xTEST_EQ(a_ccChar, static_cast<tchar_t>( iRv ));
}
//---------------------------------------------------------------------------
void
CxFile::vClear() const {
    vResize(0L);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: other
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxFile::vLocking(
    const ExLockingMode &a_clmMode,
    const long_t        &a_cliBytes
)
{
    xTEST_NA(a_clmMode);
    xTEST_NA(a_cliBytes);

#if   xOS_ENV_WIN
    const long_t cliBytes = a_cliBytes;
#elif xOS_ENV_UNIX
    const off_t  cliBytes = static_cast<off_t>( a_cliBytes );
#endif

    int iRv = ::xLOCKING(_iHandle(pGet()), a_clmMode, cliBytes);

    xTEST_DIFF(- 1, iRv);
}
//---------------------------------------------------------------------------
void
CxFile::vSetPosition(
    const long_t            &a_clOffset,
    const ExPointerPosition &a_cppPos
) const
{
    xTEST_NA(a_clOffset);
    xTEST_NA(a_cppPos);

    int iRv = std::fseek(pGet(), a_clOffset, a_cppPos);
    xTEST_DIFF(- 1, iRv);
}
//---------------------------------------------------------------------------
long_t
CxFile::liPosition() const {
    long_t liRv = std::ftell(pGet());
    xTEST_DIFF(- 1L, liRv);

    return liRv;
}
//---------------------------------------------------------------------------
void
CxFile::vSetVBuff(
    char                  *a_pszBuff,
    const ExBufferingMode &a_cbmMode,
    const size_t          &a_cuiSize
) const
{
    xTEST_NA(a_pszBuff);
    xTEST_NA(a_cbmMode);
    xTEST_NA(a_cuiSize);

    int iRv = std::setvbuf(pGet(), a_pszBuff, a_cbmMode, a_cuiSize);
    xTEST_DIFF(- 1, iRv);
}
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

void
CxFile::vSetMode(
    const ExTranslationMode &a_ctmMode
) const
{
    xTEST_NA(a_ctmMode);

    int iRv = ::setmode(_iHandle(pGet()), a_ctmMode);
    xTEST_DIFF(- 1, iRv);
}

#endif
//---------------------------------------------------------------------------
// NOTE: https://www.securecoding.cert.org/confluence/display/seccode/FIO19-C.+Do+not+use+fseek()+and+ftell()+to+compute+the+size+of+a+file
longlong_t
CxFile::llSize() const {
#if xDEPRECIATE
    vFlush();

    xTSTAT_STRUCT stStat = {0};

    // TODO: fstat
    int iRv = ::xTSTAT(_m_sFilePath.c_str(), &stStat);
    xTEST_DIFF(- 1, iRv);

    return stStat.st_size;
#else
    long_t liStreamSize    = - 1L;
    long_t liCurrStreamPos = - 1L;

    liCurrStreamPos = liPosition();
    vSetPosition(0, ppEnd);

    liStreamSize = liPosition();
    vSetPosition(liCurrStreamPos, ppBegin);

    return static_cast<longlong_t>( liStreamSize );
#endif
}
//---------------------------------------------------------------------------
void
CxFile::vResize(
    const longlong_t &a_cllSize
) const
{
    xTEST_NA(a_cllSize);

#if   xOS_ENV_WIN
    int iRv = static_cast<int>( ::xCHSIZE(_iHandle(pGet()), a_cllSize) );
    xTEST_EQ(0, iRv);
#elif xOS_ENV_UNIX
    int iRv = ::ftruncate(_iHandle(pGet()), static_cast<off_t>( a_cllSize ));
    xTEST_DIFF(- 1, iRv);
#endif

    xTEST_EQ(a_cllSize, llSize());
}
//---------------------------------------------------------------------------

/****************************************************************************
*    public: error handling
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxFile::bIsValid() const {
    return (NULL != _m_pFile);
}
//---------------------------------------------------------------------------
bool
CxFile::bIsOpen() const {
    return bIsValid();
}
//---------------------------------------------------------------------------
bool
CxFile::bIsEmpty() const {
    longlong_t llFileSize = llSize();
    xTEST_DIFF(- 1LL, llFileSize);

    return (0LL == llFileSize);
}
//---------------------------------------------------------------------------
bool
CxFile::bIsEof() const {
    bool bRv = xINT_TO_BOOL( std::feof(pGet()) );
    xTEST_NA(bRv);

    return bRv;
}
//---------------------------------------------------------------------------
bool
CxFile::bIsError() const {
    bool bRv = xINT_TO_BOOL( std::ferror(pGet()) );
    xTEST_NA(bRv);

    return bRv;
}
//---------------------------------------------------------------------------
void
CxFile::vErrorClear() const {
    (void)std::clearerr( pGet() );
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: closing
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxFile::vFlush() const {
    int iRv = std::fflush(pGet());
    xTEST_DIFF(static_cast<int>( xTEOF ), iRv);
}
//---------------------------------------------------------------------------
void
CxFile::vClose() {
    xCHECK_DO(false == bIsValid(), _m_pFile = NULL; return);

    vErrorClear();

    int iRv = std::fclose(pGet()); _m_pFile = NULL;
    xTEST_DIFF(static_cast<int>( xTEOF ), iRv);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public, static
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
bool
CxFile::bIsFile(
    const std::tstring_t &a_csFilePath
)
{
    xTEST_NA(a_csFilePath);

    bool bRv = false;

    CxFileAttribute faAttr(a_csFilePath);

    CxFileAttribute::ExAttribute atAttribute = faAttr.atGet();
    xCHECK_RET(CxFileAttribute::faInvalid == atAttribute, false);

#if   xOS_ENV_WIN
    bRv = faAttr.bIsExists(CxFileAttribute::faDirectory);
    xCHECK_RET(true == bRv, false);

    bRv = faAttr.bIsExists(CxFileAttribute::faDevice);
    xCHECK_RET(true == bRv, false);

    bRv = faAttr.bIsExists(CxFileAttribute::faReparsePoint);
    xCHECK_RET(true == bRv, false);

    bRv = faAttr.bIsExists(CxFileAttribute::faOffline);
    xCHECK_RET(true == bRv, false);
#elif xOS_ENV_UNIX
    bRv = faAttr.bIsExists(CxFileAttribute::faRegularFile);
    xCHECK_RET(false == bRv, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFile::bIsExists(
    const std::tstring_t &a_csFilePath
)
{
    xTEST_NA(a_csFilePath);

    xCHECK_RET(false == bIsFile(a_csFilePath), false);

    int iRv = ::xTACCESS(a_csFilePath.c_str(), amExistence);
    xCHECK_RET(- 1 == iRv && ENOENT == CxStdError::iGet(), false);

    return true;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxFile::sIsExists(
    const std::tstring_t &a_csFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());

    std::tstring_t sRv;

    CxPath ptPath(a_csFilePath);

    std::tstring_t sFileDir  = ptPath.sDir();
    std::tstring_t sFileName = ptPath.sFileBaseName();
    std::tstring_t sFileExt  = ptPath.sExt();

    xCHECK_DO(false == sFileExt.empty(), sFileExt.insert(0, CxConst::xDOT));

    for (ulong_t ulExistsIndex = 1; ; ++ ulExistsIndex) {
        sRv = CxString::sFormat(xT("%s%s%s (%lu)%s"),
                                sFileDir.c_str(),
                                CxConst::xSLASH.c_str(),
                                sFileName.c_str(),
                                ulExistsIndex,
                                sFileExt.c_str());

        xCHECK_DO(false == bIsExists(sRv), break);
    }

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vAccess(
    const std::tstring_t &a_csFilePath,
    const ExAccessMode   &a_camMode
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_camMode);

    int iRv = ::xTACCESS(a_csFilePath.c_str(), a_camMode);
    xTEST_DIFF(- 1, iRv);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vChmod(
    const std::tstring_t   &a_csFilePath,
    const ExPermissionMode &a_cpmMode
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_cpmMode);

#if   xOS_ENV_WIN
    const int    cpmMode = static_cast<int>   ( a_cpmMode );
#elif xOS_ENV_UNIX
    const mode_t cpmMode = static_cast<mode_t>( a_cpmMode );
#endif

    int iRv = ::xTCHMOD(a_csFilePath.c_str(), cpmMode);
    xTEST_DIFF(- 1, iRv);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vClear(
    const std::tstring_t &a_csFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());

    CxFile sfFile;

    sfFile.vCreate(a_csFilePath, omWrite, true);
    sfFile.vClear();
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vDelete(
    const std::tstring_t &a_csFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());

    xCHECK_DO(false == bIsExists(a_csFilePath), return);

    vChmod(a_csFilePath, pmWrite);

    int iRv = ::xTREMOVE(a_csFilePath.c_str());
    xTEST_DIFF(- 1, iRv);
    xTEST_EQ(false, bIsExists(a_csFilePath));
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vTryDelete(
    const std::tstring_t &a_csFilePath,
    const size_t         &a_cuiAttempts,
    const ulong_t        &a_culTimeoutMsec
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_LESS(size_t(0U), a_cuiAttempts);
    xTEST_NA(a_culTimeoutMsec);

    const size_t cuiMaxAttempts  = 100;  // MAGIC_NUMBER: cuiMaxAttempts
    const size_t cuiRealAttempts = (cuiMaxAttempts < a_cuiAttempts) ? cuiMaxAttempts : a_cuiAttempts;

    for (size_t i = 0; i < cuiRealAttempts; ++ i) {
        try {
            vDelete(a_csFilePath);
            break;
        }
        catch (const CxException &) {
            xNA;
        }

        CxCurrentThread::vSleep(a_culTimeoutMsec);
    }
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vWipe(
    const std::tstring_t &a_csFilePath,
    const size_t         &a_cuiPasses
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_cuiPasses);

    xCHECK_DO(false == bIsExists(a_csFilePath), return);

    {
        CxFile sfFile;

        //--------------------------------------------------
        // set normal file attributes
        CxFileAttribute(a_csFilePath).vSet(CxFileAttribute::faNormal);

        //--------------------------------------------------
        // open
        sfFile.vCreate(a_csFilePath, omBinWrite, true);

        longlong_t llSize = sfFile.llSize();
        if (0LL < llSize) {
            //--------------------------------------------------
            // fill by 0x55, 0xAA, random char
            for (size_t p = 0; p < a_cuiPasses; ++ p) {
                CxRandom::vSetSeed();

                const uchar_t chRand  = static_cast<uchar_t>(CxRandom::liInt(0, 255) + 1);
                const uchar_t chChar1 = 0x55;
                const uchar_t chChar2 = 0xAA;

                // chRand
                {
                    sfFile.vSetPosition(0L, ppBegin);

                    for (longlong_t i = 0LL; i < llSize; ++ i) {
                        size_t uiRes = std::fwrite(&chRand, 1, sizeof(chRand), sfFile.pGet());
                        xTEST_EQ(sizeof(chRand), uiRes);
                    }
                }

                // chChar1
                {
                    sfFile.vSetPosition(0L, ppBegin);

                    for (longlong_t i = 0LL; i < llSize; ++ i) {
                        size_t uiRes = std::fwrite(&chChar1, 1, sizeof(chChar1), sfFile.pGet());
                        xTEST_EQ(sizeof(chChar1), uiRes);
                    }
                }

                // chChar2
                {
                    sfFile.vSetPosition(0L, ppBegin);

                    for (longlong_t i = 0LL; i < llSize; ++ i) {
                        size_t uiRes = std::fwrite(&chChar2, 1, sizeof(chChar2), sfFile.pGet());
                        xTEST_EQ(sizeof(chChar2), uiRes);
                    }
                }
            }

            //--------------------------------------------------
            // truncate
            sfFile.vFlush();
            sfFile.vResize(0L);
        }
    }

    //--------------------------------------------------
    // reset file time
    {
        const time_t ctmCreate   = 0;
        const time_t ctmAccess   = 0;
        const time_t ctmModified = 0;

        vSetTime(a_csFilePath, ctmCreate, ctmAccess, ctmModified);
    }

    //--------------------------------------------------
    // random file name
    std::tstring_t sRndFilePath;

    {
        std::tstring_t sRndFileName;

        sRndFileName = CxString::cast( CxDateTime().dtCurrent().ullToMilliseconds() );
        std::random_shuffle(sRndFileName.begin(), sRndFileName.end());

        sRndFilePath = CxPath(a_csFilePath).sDir() + CxConst::xSLASH + sRndFileName;

        vRename(a_csFilePath, sRndFilePath);
    }

    //--------------------------------------------------
    // delete
    vDelete(sRndFilePath);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vUnlink(
    const std::tstring_t &a_csFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());

    int iRv = ::xTUNLINK(a_csFilePath.c_str());
    xTEST_DIFF(- 1, iRv);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vRename(
    const std::tstring_t &a_csOldFilePath,
    const std::tstring_t &a_csNewFilePath
)
{
    xTEST_EQ(false, a_csOldFilePath.empty());
    xTEST_EQ(false, a_csNewFilePath.empty());

    int iRv = ::xTRENAME(a_csOldFilePath.c_str(), a_csNewFilePath.c_str());
    xTEST_DIFF(- 1, iRv);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vMove(
    const std::tstring_t &a_csFilePath,
    const std::tstring_t &a_csDirPath
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_EQ(false, a_csDirPath.empty());

    vRename(a_csFilePath, CxPath(a_csDirPath).sSlashAppend() + CxPath(a_csFilePath).sFileName());
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vCopy(
    const std::tstring_t &a_csFilePathFrom,
    const std::tstring_t &a_csFilePathTo,
    const bool           &a_cbFailIfExists
)
{
    xTEST_EQ(false, a_csFilePathFrom.empty());
    xTEST_EQ(false, a_csFilePathTo.empty());
    xTEST_NA(a_cbFailIfExists);

    bool bIsCopyOk = true;

    //--------------------------------------------------
    // TODO: fail if exists
#if xTODO
    if (true == cbFailIfExists && true == bIsExists(csFilePathTo)) {
        xTEST_FAIL;
    }
#endif

    // TODO: check file size

    {
        //--------------------------------------------------
        // open files
        CxFile sfFrom;
        sfFrom.vCreate(a_csFilePathFrom, omBinRead, true);

        CxFile sfTo;
        sfTo.vCreate(a_csFilePathTo, omBinWrite, true);

        //--------------------------------------------------
        // copy files
        const size_t cuiBuffSize         = 1024;
        uchar_t      ucBuff[cuiBuffSize] = {0};

        xFOREVER {
            const size_t uiReaded  = sfFrom.uiRead(ucBuff, cuiBuffSize);
            xCHECK_DO(0 >= uiReaded, break);

            const size_t uiWritten = sfTo.uiWrite(ucBuff, uiReaded);
            xCHECK_DO(uiReaded != uiWritten, bIsCopyOk = false; break);
        }
    }

    //--------------------------------------------------
    // if copy fail - delete out file
    xCHECK_DO(false == bIsCopyOk, vDelete(a_csFilePathTo); return /* false */);

    //--------------------------------------------------
    // test for size, maybe CRC
    xCHECK_DO(llSize(a_csFilePathFrom) != llSize(a_csFilePathTo), vDelete(a_csFilePathTo); return /* false */);
}
//--------------------------------------------------------------------------
/* static */
longlong_t
CxFile::llSize(
    const std::tstring_t &a_csFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_EQ(true,  bIsExists(a_csFilePath));

    CxFile sfFile;

    sfFile.vCreate(a_csFilePath, omRead, true);
    longlong_t liRv = sfFile.llSize();
    xTEST_LESS_EQ(0LL, liRv);

    return liRv;
}
//---------------------------------------------------------------------------
/* static */
ulonglong_t
CxFile::ullLines(
    const std::tstring_t &a_csFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_EQ(true,  bIsExists(a_csFilePath));

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
//---------------------------------------------------------------------------
/* static */
void
CxFile::vTime(
    const std::tstring_t &a_csFilePath,
    time_t               *a_ptmCreate,
    time_t               *a_ptmAccess,
    time_t               *a_ptmModified
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
                             NULL, OPEN_EXISTING, CxFileAttribute::faNormal, NULL);
    xTEST_EQ(true, m_hHandle.bIsValid());

    BOOL blRes = ::GetFileTime(m_hHandle.hGet(), &ftCreate, &ftAccess, &ftModified);
    xTEST_DIFF(FALSE, blRes);

    CxUtils::ptrAssignT(a_ptmCreate,   CxDateTime::tmFileTimeToUnixTime(ftCreate));
    CxUtils::ptrAssignT(a_ptmAccess,   CxDateTime::tmFileTimeToUnixTime(ftAccess));
    CxUtils::ptrAssignT(a_ptmModified, CxDateTime::tmFileTimeToUnixTime(ftModified));
#elif xOS_ENV_UNIX
    xTSTAT_STRUCT stInfo = {0};

    int iRv = ::xTSTAT(a_csFilePath.c_str(), &stInfo);
    xTEST_DIFF(- 1, iRv);

    // ctmCreate - n/a
    CxUtils::ptrAssignT(a_ptmAccess,   stInfo.st_atime);
    CxUtils::ptrAssignT(a_ptmModified, stInfo.st_mtime);
#endif
}
//---------------------------------------------------------------------------
/*static */
void
CxFile::vSetTime(
    const std::tstring_t &a_csFilePath,
    const time_t         &a_ctmCreate,
    const time_t         &a_ctmAccess,
    const time_t         &a_ctmModified
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_ctmCreate);
    xTEST_NA(a_ctmAccess);
    xTEST_NA(a_ctmModified);

#if   xOS_ENV_WIN
    FILETIME ftCreate = {0};
    CxDateTime::vUnixTimeToFileTime(a_ctmCreate, &ftCreate);

    FILETIME ftAccess = {0};
    CxDateTime::vUnixTimeToFileTime(a_ctmAccess, &ftAccess);

    FILETIME ftModified = {0};
    CxDateTime::vUnixTimeToFileTime(a_ctmModified, &ftModified);

    CxHandleInvalid m_hHandle;

    m_hHandle = ::CreateFile(a_csFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE,
                             NULL, OPEN_EXISTING, CxFileAttribute::faNormal, NULL);
    xTEST_EQ(true, m_hHandle.bIsValid());

    BOOL blRes = ::SetFileTime(m_hHandle.hGet(), &ftCreate, &ftAccess, &ftModified);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    utimbuf tbTimes = {0};

    // ctmCreate - n/a
    tbTimes.actime  = a_ctmAccess;
    tbTimes.modtime = a_ctmModified;

    int iRv = ::utime(a_csFilePath.c_str(), &tbTimes);
    xTEST_DIFF(- 1, iRv);
#endif
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: text
*
*****************************************************************************/

//--------------------------------------------------------------------------
/* static */
void
CxFile::vTextRead(
    const std::tstring_t &a_csFilePath,
    std::tstring_t       *a_psContent
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_PTR(a_psContent);

    CxFile         sfFile;
    std::tstring_t sRv;

    sfFile.vCreate(a_csFilePath, omBinRead, true);

    longlong_t llFileSize = sfFile.llSize();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    xCHECK_DO(0LL == llFileSize, (*a_psContent).clear(); return);

    sRv.resize( static_cast<size_t>( llFileSize) );

    size_t uiReadLen = sfFile.uiRead((void *)&sRv.at(0), sRv.size());
    xTEST_EQ(sRv.size(), uiReadLen);

    // out
    std::swap((*a_psContent), sRv);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vTextWrite(
    const std::tstring_t &a_csFilePath,
    const std::tstring_t &a_csContent
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_csContent);

    // TODO: if csContent.empty()

    CxFile sfFile;

    sfFile.vCreate(a_csFilePath, omBinWrite, true);

    xCHECK_DO(true == a_csContent.empty(), return);

    size_t uiWriteLen = sfFile.uiWrite((void *)&a_csContent.at(0), a_csContent.size());
    xTEST_EQ(a_csContent.size(), uiWriteLen);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vTextRead(
    const std::tstring_t &a_csFilePath,
    std::vec_tstring_t   *a_pvsContent
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_EQ(true,  bIsExists(a_csFilePath));
    xTEST_PTR(a_pvsContent);

    std::vec_tstring_t vsRes;
    std::tstring_t     sFileContent;

    vTextRead(a_csFilePath, &sFileContent);

    CxString::vSplit(sFileContent, CxConst::xNL, &vsRes);

    // out
    std::swap((*a_pvsContent), vsRes);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vTextWrite(
    const std::tstring_t     &a_csFilePath,
    const std::vec_tstring_t &a_cvsContent
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_cvsContent);

    // TODO: if cvsContent.empty()

    std::tstring_t sFileContent;

    sFileContent = CxString::sJoin(a_cvsContent, CxConst::xNL);

    vTextWrite(a_csFilePath, sFileContent);
}
//--------------------------------------------------------------------------
/* static */
void
CxFile::vTextRead(
    const std::tstring_t &a_csFilePath,
    const std::tstring_t &a_csSeparator,
    std::map_tstring_t   *a_pmsContent
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_EQ(true,  bIsExists(a_csFilePath));
    xTEST_PTR(a_pmsContent);

    // if file empty
    xCHECK_DO(0L == llSize(a_csFilePath), (*a_pmsContent).clear(); return);

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

        sLine = CxString::sTrimRightChars(sLine, CxConst::xEOL);

        CxString::vSplit(sLine, a_csSeparator, &vsLine);
        xTEST_EQ(size_t(2), vsLine.size());

        msRv.insert( std::pair<std::tstring_t, std::tstring_t>(vsLine.at(0), vsLine.at(1)) );
    }

    // out
    (*a_pmsContent).swap(msRv);

#if xTODO
    bool               bRv = false;
    std::map_tstring_t msRv;
    std::vec_tstring_t vsRes;

    bRv = bTextRead(csFilePath, &vsRes);
    xTEST_EQ(true, bRv);

    std::vec_tstring_t::_const_iterator it;
    for (it = vsRes.begin(); it != vsRes.end(); ++ it) {
        std::vec_tstring_t vsLine;

        CxString::vSplit(vsRes.at(0), csSeparator, &vsLine);
        msRv.insert( std::pair<std::tstring_t, std::tstring_t>(vsLine.at(0), vsLine.at(1)) );
    }

    //out
    std::swap((*pmsContent), msRv);
#endif
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vTextWrite(
    const std::tstring_t     &a_csFilePath,
    const std::tstring_t     &a_csSeparator,
    const std::map_tstring_t &a_cmsContent
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_EQ(false, a_csSeparator.empty());
    xTEST_NA(a_cmsContent);

    // TODO: if cmsFile.empty()

    CxFile stdFile;

    stdFile.vCreate(a_csFilePath, omWrite, true);

    typedef std::map_tstring_t TContent;

    xFOREACH_CONST(TContent, it, a_cmsContent) {
        stdFile.vWriteLine((*it).first + a_csSeparator + (*it).second);
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

    vTextWrite(csFilePath, sRv);
#endif
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: bin
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
void
CxFile::vBinRead(
    const std::tstring_t &a_csFilePath,
    std::ustring_t       *a_pusContent
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_PTR(a_pusContent);

    CxFile         sfFile;
    std::ustring_t usRv;

    sfFile.vCreate(a_csFilePath, omBinRead, true);

    longlong_t llFileSize = sfFile.llSize();
    xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    xCHECK_DO(0LL == llFileSize, (*a_pusContent).clear(); return);

    usRv.resize( static_cast<size_t>( llFileSize ) );

    size_t uiReadLen = sfFile.uiRead((void *)&usRv.at(0), usRv.size());
    xTEST_EQ(usRv.size(), uiReadLen);

    // out
    std::swap((*a_pusContent), usRv);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vBinWrite(
    const std::tstring_t &a_csFilePath,
    const std::ustring_t &a_cusContent
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_cusContent);

    // TODO: if cusContent.empty()

    CxFile sfFile;

    sfFile.vCreate(a_csFilePath, omBinWrite, true);

    xCHECK_DO(true == a_cusContent.empty(), return);

    size_t uiWriteLen = sfFile.uiWrite((void *)&a_cusContent.at(0), a_cusContent.size());
    xTEST_EQ(a_cusContent.size(), uiWriteLen);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
int
CxFile::_iHandle(
    std::FILE *a_pfFile
)
{
    xTEST_PTR(a_pfFile);

    int iRv = /*::*/fileno(a_pfFile);
    xTEST_DIFF(- 1, iRv);

    return iRv;
}
//---------------------------------------------------------------------------
/* static */
std::FILE *
CxFile::_pfHandle(
    int               a_iFileHandle,
    const ExOpenMode &a_omMode
)
{
    xTEST_NA(a_iFileHandle);
    xTEST_NA(a_omMode);

    std::FILE *pfRes = ::xTFDOPEN(a_iFileHandle, _sOpenMode(a_omMode).c_str());
    xTEST_PTR(pfRes);

    return pfRes;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxFile::_sOpenMode(
    const ExOpenMode &a_comMode
)
{
    xTEST_NA(a_comMode);

    std::tstring_t sRv;

    switch (a_comMode) {
        case omRead:                { sRv = xT("r");   }   break;
        case omWrite:               { sRv = xT("w");   }   break;
        case omAppend:              { sRv = xT("a");   }   break;
        case omOpenReadWrite:       { sRv = xT("r+");  }   break;
        case omCreateReadWrite:     { sRv = xT("w+");  }   break;
        case omOpenReadAppend:      { sRv = xT("a+");  }   break;

        case omBinRead:             { sRv = xT("rb");  }   break;
        case omBinWrite:            { sRv = xT("wb");  }   break;
        case omBinAppend:           { sRv = xT("ab");  }   break;
        case omBinOpenReadWrite:    { sRv = xT("rb+"); }   break;
        case omBinCreateReadWrite:  { sRv = xT("wb+"); }   break;
        case omBinOpenReadAppend:   { sRv = xT("ab+"); }   break;

        default:                    { sRv = xT("r");   }   break;
    }

    return sRv;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
