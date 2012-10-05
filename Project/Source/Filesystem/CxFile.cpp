/**
 * \file  CxFile.cpp
 * \brief file
 */


#include <xLib/Filesystem/CxFile.h>

#include <xLib/Common/CxString.h>
#include <xLib/Common/CxLocale.h>
#include <xLib/Common/CxDateTime.h>
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
    /*DEBUG*/// n/a

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
    const std::tstring_t &csFilePath,
    const ExOpenMode     &comMode,
    const bool           &cbIsUseBuffering
)
{
    /*DEBUG*/xTEST_EQ(false, bIsValid());
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_EQ(true, CxPath::bIsNameValid(csFilePath));
    /*DEBUG*/// comMode - n/a

    //create force dirs
    CxDir::vCreateForce( CxPath::sGetDir(csFilePath) );

    //create, open file
    std::FILE *pFile = ::xTFOPEN(csFilePath.c_str(), _sGetOpenMode(comMode).c_str());
    /*DEBUG*/xTEST_PTR(pFile);

    _m_pFile     = pFile;
    _m_sFilePath = csFilePath;

    //buffering
    if (false == cbIsUseBuffering) {
        vSetVBuff(NULL, bmNo,   0);
    } else {
        vSetVBuff(NULL, bmFull, BUFSIZ);
    }
}
//---------------------------------------------------------------------------
void
CxFile::vReopen(
    const std::tstring_t &csFilePath,
    const ExOpenMode     &comMode,
    const bool           &cbIsUseBuffering
)
{
    /*DEBUG*/// _m_pFile - n/a
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_EQ(true, CxPath::bIsNameValid(csFilePath));
    /*DEBUG*/// omMode - n/a

    std::FILE *pFile = ::xTFREOPEN(csFilePath.c_str(), _sGetOpenMode(comMode).c_str(), _m_pFile);
    /*DEBUG*/xTEST_PTR(pFile);

    _m_pFile     = pFile;
    _m_sFilePath = csFilePath;

    //buffering
    if (false == cbIsUseBuffering) {
        vSetVBuff(NULL, bmNo,   0);
    } else {
        vSetVBuff(NULL, bmFull, BUFSIZ);
    }
}
//---------------------------------------------------------------------------
void
CxFile::vAttach(
    std::FILE *pflFile
)
{
    /*DEBUG*/// _m_pFile - n/a
    /*DEBUG*/// pflFile  - n/a

    vClose();

    _m_pFile     = pflFile;
    _m_sFilePath = CxConst::xSTR_EMPTY;
}
//---------------------------------------------------------------------------
std::FILE *
CxFile::pDetach() {
    std::FILE *pFile = _m_pFile;

    _m_pFile = NULL;

    return pFile;
}
//---------------------------------------------------------------------------
std::FILE *
CxFile::pGet() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    return _m_pFile;
}
//---------------------------------------------------------------------------
std::tstring_t
CxFile::sGetPath() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_EQ(false, _m_sFilePath.empty());
    /*DEBUG*/xTEST_EQ(true, bIsExists(_m_sFilePath));

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
    void         *pvBuff,
    const size_t &cuiCount
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_PTR(pvBuff);

    size_t uiRes = std::fread(pvBuff, 1, cuiCount, pGet());
    /*DEBUG*/xTEST_GR_EQ(cuiCount, uiRes);

    return uiRes;
}
//---------------------------------------------------------------------------
size_t
CxFile::uiWrite(
    const void   *pcvBuff,
    const size_t &cuiCount
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_PTR(pcvBuff);

    size_t uiRes = std::fwrite(pcvBuff, 1, cuiCount, pGet());
    /*DEBUG*/xTEST_EQ(cuiCount, uiRes);

    return uiRes;
}
//---------------------------------------------------------------------------
void
CxFile::vRead(
    std::ustring_t *psBuff
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_PTR(psBuff);

    longlong_t llFileSize = llGetSize();
    /*DEBUG*/xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    (*psBuff).clear();
    (*psBuff).resize( static_cast<size_t>( llFileSize ) );
    xCHECK_DO(0LL == llFileSize, return);

    size_t uiRes = std::fread(&(*psBuff).at(0), sizeof(std::ustring_t::value_type), (*psBuff).size(), pGet());
    /*DEBUG*/xTEST_EQ((*psBuff).size(), uiRes);
}
//---------------------------------------------------------------------------
void
CxFile::vWrite(
    const std::ustring_t &csBuff
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*///csBuff - n/a

    size_t uiRes = std::fwrite(&csBuff.at(0), sizeof(std::ustring_t::value_type), csBuff.size(), pGet());
    /*DEBUG*/xTEST_EQ(csBuff.size(), uiRes);
}
//---------------------------------------------------------------------------
void
CxFile::vRead(
    std::tstring_t *psBuff
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_PTR(psBuff);

    longlong_t llFileSize = llGetSize();
    /*DEBUG*/xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    (*psBuff).clear();
    (*psBuff).resize( static_cast<size_t>( llFileSize) );
    xCHECK_DO(0LL == llFileSize, return);

    size_t uiRes =std::fread(&(*psBuff).at(0), sizeof(std::tstring_t::value_type), (*psBuff).size(), pGet());
    /*DEBUG*/xTEST_EQ((*psBuff).size(), uiRes);
}
//---------------------------------------------------------------------------
int
CxFile::iWrite(
    const tchar_t *pcszFormat, ...
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_PTR(pcszFormat);

    va_list vlArgs;
    xVA_START(vlArgs, pcszFormat);

    int iRv = std::xTVFPRINTF(pGet(), pcszFormat, vlArgs);
    /*DEBUG*/xTEST_LESS(- 1, iRv);

    xVA_END(vlArgs);

    return iRv;
}
//---------------------------------------------------------------------------
int
CxFile::iWriteV(
    const tchar_t *pcszFormat,
    va_list        vlArgs
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_PTR(pcszFormat);
    /*DEBUG*/xTEST_PTR(vlArgs);

    int iRv = std::xTVFPRINTF(pGet(), pcszFormat, vlArgs);
    /*DEBUG*/xTEST_LESS(- 1, iRv);

    return iRv;
}
//---------------------------------------------------------------------------
void
CxFile::vReadLine(
    std::tstring_t *psStr,
    const size_t   &cuiMaxCount
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_PTR(psStr);
    /*DEBUG*/xTEST_LESS(size_t(0U), cuiMaxCount);

    #if xTEMP_DISABLED
        if ((*psStr).size() != cuiMaxCount) {
            (*psStr).resize(cuiMaxCount);
        }
        std::fill((*psStr).begin(), (*psStr).end(), std::tstring_t::value_type());
    #endif

    (*psStr).clear();
    (*psStr).resize(cuiMaxCount + 1);   //+ 1 for 0

    tchar_t *pszRes = std::xTFGETS(&(*psStr).at(0), (*psStr).size(), pGet());
    /*DEBUG*/xTEST_PTR(pszRes);

    (*psStr).erase( (*psStr).end() - 1 );   //erase last char - 0
}
//---------------------------------------------------------------------------
void
CxFile::vWriteLine(
    const std::tstring_t &csStr
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    std::tstring_t sLine;

    sLine = csStr;
    sLine.append(CxConst::xEOL);

    size_t uiRes = uiWrite(&sLine.at(0), sLine.size());
    /*DEBUG*/xTEST_EQ(uiRes, sLine.size());
}
//---------------------------------------------------------------------------
//TODO: chReadChar
tchar_t
CxFile::chReadChar() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    int iRv = std::xTFGETC(pGet());
    /*DEBUG*/xTEST_LESS_EQ(xTEOF, iRv);

    return static_cast<tchar_t>( iRv );
}
//---------------------------------------------------------------------------
//TODO: bWriteChar
void
CxFile::vWriteChar(
    const tchar_t &ccChar
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    int iRv = xTFPUTC(static_cast<int>( ccChar ), pGet());
    /*DEBUG*/xTEST_DIFF(static_cast<int>( ccChar ), xTEOF);
    /*DEBUG*/xTEST_EQ(static_cast<int>( ccChar ), iRv);
}
//---------------------------------------------------------------------------
//TODO: bUngetChar
void
CxFile::vUngetChar(
    const tchar_t &ccChar
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    int iRv = std::xTUNGETC(ccChar, pGet());
    /*DEBUG*/xTEST_DIFF(iRv, xTEOF);
    /*DEBUG*/xTEST_EQ(ccChar, static_cast<tchar_t>( iRv ));
}
//---------------------------------------------------------------------------
void
CxFile::vClear() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

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
    const ExLockingMode &clmMode,
    const long_t        &cliBytes
)
{
#if   xOS_ENV_WIN
    int iRv = ::xLOCKING(_iGetHandle(pGet()), clmMode, cliBytes);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
#elif xOS_ENV_UNIX
    int iRv = ::lockf   (_iGetHandle(pGet()), clmMode, static_cast<off_t>( cliBytes ));
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
#endif
}
//---------------------------------------------------------------------------
void
CxFile::vSetPosition(
    const long_t            &clOffset,
    const ExPointerPosition &cppPos
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    int iRv = std::fseek(pGet(), clOffset, cppPos);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
}
//---------------------------------------------------------------------------
long_t
CxFile::liGetPosition() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    long_t liRv = std::ftell(pGet());
    /*DEBUG*/xTEST_DIFF(- 1L, liRv);

    return liRv;
}
//---------------------------------------------------------------------------
void
CxFile::vSetVBuff(
    char                  *pszBuff,
    const ExBufferingMode &cbmMode,
    const size_t          &cuiSize
) const
{
    /*DEBUG*/// pszBuff - n/a
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/// cuiSize - n/a

    int iRv = std::setvbuf(pGet(), pszBuff, cbmMode, cuiSize);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
}
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

void
CxFile::vSetMode(
    const ExTranslationMode &ctmMode
) const
{
    int iRv = ::setmode(_iGetHandle(pGet()), ctmMode);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
}

#endif
//---------------------------------------------------------------------------
//NOTE: https://www.securecoding.cert.org/confluence/display/seccode/FIO19-C.+Do+not+use+fseek()+and+ftell()+to+compute+the+size+of+a+file
longlong_t
CxFile::llGetSize() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

#if xDEPRECIATE
    vFlush();

    xTSTAT_STRUCT stStat = {0};

    //TODO: fstat
    int iRv = ::xTSTAT(_m_sFilePath.c_str(), &stStat);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);

    return stStat.st_size;
#else
    long_t liStreamSize    = - 1L;
    long_t liCurrStreamPos = - 1L;

    liCurrStreamPos = liGetPosition();
    vSetPosition(0, ppEnd);

    liStreamSize = liGetPosition();
    vSetPosition(liCurrStreamPos, ppBegin);

    return static_cast<longlong_t>( liStreamSize );
#endif
}
//---------------------------------------------------------------------------
void
CxFile::vResize(
    const longlong_t &cllSize
) const
{
    /*DEBUG*/// n/a

#if   xOS_ENV_WIN
    int iRv = static_cast<int>( ::xCHSIZE(_iGetHandle(pGet()), cllSize) );
    /*DEBUG*/xTEST_EQ(0, iRv);
#elif xOS_ENV_UNIX
    int iRv = ::ftruncate(_iGetHandle(pGet()), static_cast<off_t>( cllSize ));
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
#endif

    /*DEBUG*/xTEST_EQ(cllSize, llGetSize());
}
//---------------------------------------------------------------------------

/****************************************************************************
*    public: error handling
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxFile::bIsValid() const {
    /*DEBUG*/

    return (NULL != _m_pFile);
}
//---------------------------------------------------------------------------
bool
CxFile::bIsOpen() const {
    /*DEBUG*/// n/a

    return bIsValid();
}
//---------------------------------------------------------------------------
bool
CxFile::bIsEmpty() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    longlong_t llFileSize = llGetSize();
    /*DEBUG*/xTEST_DIFF(- 1LL, llFileSize);

    return (0LL == llFileSize);
}
//---------------------------------------------------------------------------
bool
CxFile::bIsEof() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    return xINT_TO_BOOL( std::feof(pGet()) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
bool
CxFile::bIsError() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    return xINT_TO_BOOL( std::ferror(pGet()) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
void
CxFile::vErrorClear() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

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
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    int iRv = std::fflush(pGet());
    /*DEBUG*/xTEST_DIFF(xTEOF, iRv);
}
//---------------------------------------------------------------------------
void
CxFile::vClose() {
    /*DEBUG*/// _m_pFile - n/a

    xCHECK_DO(false == bIsValid(), _m_pFile = NULL; return);

    vErrorClear();

    int iRv = std::fclose(pGet());
    /*DEBUG*/xTEST_DIFF(xTEOF, iRv);

    _m_pFile = NULL;
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
    const std::tstring_t &csFilePath
)
{
    bool bRv = false;

    CxFileAttribute::ExAttribute atAttr = CxFileAttribute::atGet(csFilePath);
    xCHECK_RET(CxFileAttribute::faInvalid == atAttr, false);

#if   xOS_ENV_WIN
    bRv = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faDirectory);
    xCHECK_RET(true == bRv, false);

    bRv = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faDevice);
    xCHECK_RET(true == bRv, false);

    bRv = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faReparsePoint);
    xCHECK_RET(true == bRv, false);

    bRv = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faOffline);
    xCHECK_RET(true == bRv, false);
#elif xOS_ENV_UNIX
    bRv = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faRegularFile);
    xCHECK_RET(false == bRv, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFile::bIsExists(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/// csFilePath - n/a
    xCHECK_RET(false == bIsFile(csFilePath), false);

    int iRv = ::xTACCESS(csFilePath.c_str(), amExistence);
    xCHECK_RET(- 1 == iRv && ENOENT == CxStdError::iGet(), false);

    return true;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxFile::sIsExists(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());

    std::tstring_t sRv;

    std::tstring_t sFileDir  = CxPath::sGetDir(csFilePath);
    std::tstring_t sFileName = CxPath::sGetFileBaseName(csFilePath);
    std::tstring_t sFileExt  = CxPath::sGetExt(csFilePath);

    xCHECK_DO(false == sFileExt.empty(), sFileExt.insert(0, CxConst::xDOT));

    for (ulong_t ulExistsIndex = 1; ; ++ ulExistsIndex) {
        sRv = CxString::sFormat(xT("%s%s%s (%lu)%s"),
                                 sFileDir.c_str(), CxConst::xSLASH.c_str(), sFileName.c_str(), ulExistsIndex, sFileExt.c_str());

        xCHECK_DO(false == bIsExists(sRv), break);
    }

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vAccess(
    const std::tstring_t &csFilePath,
    const ExAccessMode   &camMode
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*///iMode

    int iRv = ::xTACCESS(csFilePath.c_str(), camMode);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vChmod(
    const std::tstring_t   &csFilePath,
    const ExPermissionMode &cpmMode
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*///iMode

#if   xOS_ENV_WIN
    int iRv = ::xTCHMOD(csFilePath.c_str(), static_cast<int>( cpmMode ));
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
#elif xOS_ENV_UNIX
    int iRv = ::xTCHMOD(csFilePath.c_str(), static_cast<mode_t>( cpmMode ));
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
#endif
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vClear(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());

    bool   bRv = false;
    CxFile sfFile;

    sfFile.vCreate(csFilePath, omWrite, true);
    sfFile.vClear();
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vDelete(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    xCHECK_DO(false == bIsExists(csFilePath), return);

    vChmod(csFilePath, pmWrite);

    int iRv = ::xTREMOVE(csFilePath.c_str());
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
    /*DEBUG*/xTEST_EQ(false, bIsExists(csFilePath));
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vTryDelete(
    const std::tstring_t &csFilePath,
    const size_t         &cuiAttempts,
    const ulong_t        &culTimeoutMsec
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_LESS(size_t(0U), cuiAttempts);

    const size_t cuiMaxAttempts  = 100;  //MAGIC_NUMBER: cuiMaxAttempts
    const size_t cuiRealAttempts = (cuiMaxAttempts < cuiAttempts) ? cuiMaxAttempts : cuiAttempts;


    bool bIsDeleted = false;

    for (size_t i = 0; i < cuiRealAttempts; ++ i) {
        try {
            vDelete(csFilePath);
            break;
        }
        catch (const CxException &) {
            xNA;
        }

        CxCurrentThread::vSleep(culTimeoutMsec);
    }
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vWipe(
    const std::tstring_t &csFilePath,
    const size_t         &cuiPasses
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// cuiPasses - n/a

    xCHECK_DO(false == bIsExists(csFilePath), return);

    {
        CxFile sfFile;

        //--------------------------------------------------
        //set normal file attributes
        CxFileAttribute::vSet(csFilePath, CxFileAttribute::faNormal);

        //--------------------------------------------------
        //open
        sfFile.vCreate(csFilePath, omBinWrite, true);

        longlong_t llSize = sfFile.llGetSize();
        if (0LL < llSize) {
            //--------------------------------------------------
            //fill by 0x55, 0xAA, random char
            for (size_t p = 0; p < cuiPasses; ++ p) {
                CxRandom::vSetSeed();

                const uchar_t chRand  = static_cast<uchar_t>(CxRandom::liGetInt(0, 255) + 1);
                const uchar_t chChar1 = 0x55;
                const uchar_t chChar2 = 0xAA;

                //chRand
                {
                    sfFile.vSetPosition(0L, ppBegin);

                    for (longlong_t i = 0LL; i < llSize; ++ i) {
                        size_t uiRes = std::fwrite(&chRand, 1, sizeof(chRand), sfFile.pGet());
                        /*DEBUG*/xTEST_EQ(sizeof(chRand), uiRes);
                    }
                }

                //chChar1
                {
                    sfFile.vSetPosition(0L, ppBegin);

                    for (longlong_t i = 0LL; i < llSize; ++ i) {
                        size_t uiRes = std::fwrite(&chChar1, 1, sizeof(chChar1), sfFile.pGet());
                        /*DEBUG*/xTEST_EQ(sizeof(chChar1), uiRes);
                    }
                }

                //chChar2
                {
                    sfFile.vSetPosition(0L, ppBegin);

                    for (longlong_t i = 0LL; i < llSize; ++ i) {
                        size_t uiRes = std::fwrite(&chChar2, 1, sizeof(chChar2), sfFile.pGet());
                        /*DEBUG*/xTEST_EQ(sizeof(chChar2), uiRes);
                    }
                }
            }

            //--------------------------------------------------
            //truncate
            sfFile.vFlush();
            sfFile.vResize(0L);
        }
    }

    //--------------------------------------------------
    //reset filetime
    {
        const time_t ctmCreate   = 0;
        const time_t ctmAccess   = 0;
        const time_t ctmModified = 0;

        vSetTime(csFilePath, ctmCreate, ctmAccess, ctmModified);
    }

    //--------------------------------------------------
    //random file name
    std::tstring_t sRndFilePath;

    {
        std::tstring_t sRndFileName;

        sRndFileName = CxString::string_cast( CxDateTime().dtGetCurrent().ullToMilliseconds() );
        std::random_shuffle(sRndFileName.begin(), sRndFileName.end());

        sRndFilePath = CxPath::sGetDir(csFilePath) + CxConst::xSLASH + sRndFileName;

        vRename(csFilePath, sRndFilePath);
    }

    //--------------------------------------------------
    //delete
    vDelete(sRndFilePath);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vUnlink(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());

    int iRv = ::xTUNLINK(csFilePath.c_str());
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vRename(
    const std::tstring_t &csOldFilePath,
    const std::tstring_t &csNewFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csOldFilePath.empty());
    /*DEBUG*/xTEST_EQ(false, csNewFilePath.empty());

    int iRv = ::xTRENAME(csOldFilePath.c_str(), csNewFilePath.c_str());
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vMove(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_EQ(false, csDirPath.empty());

    vRename(csFilePath, CxPath::sSlashAppend(csDirPath) + CxPath::sGetFileName(csFilePath));
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vCopy(
    const std::tstring_t &csFilePathFrom,
    const std::tstring_t &csFilePathTo,
    const bool           &cbFailIfExists
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePathFrom.empty());
    /*DEBUG*/xTEST_EQ(false, csFilePathTo.empty());

    bool bIsCopyOk = true;

    //--------------------------------------------------
    // TODO: fail if exists
    /*if (true == cbFailIfExists && true == bIsExists(csFilePathTo)) {
        xTEST_FAIL;
    }*/
    //TODO: check filesize

    {
        //--------------------------------------------------
        //open files
        CxFile sfFrom;
        sfFrom.vCreate(csFilePathFrom, omBinRead, true);

        CxFile sfTo;
        sfTo.vCreate(csFilePathTo, omBinWrite, true);

        //--------------------------------------------------
        //copy files
        const size_t cuiBuffSize         = 1024;
        uchar_t      ucBuff[cuiBuffSize] = {0};

        for ( ; ; ) {
            const size_t uiReaded  = sfFrom.uiRead(ucBuff, cuiBuffSize);
            xCHECK_DO(0 >= uiReaded, break);

            const size_t uiWritten = sfTo.uiWrite(ucBuff, uiReaded);
            xCHECK_DO(uiReaded != uiWritten, bIsCopyOk = false; break);
        }
    }

    //--------------------------------------------------
    //if copy fail - delete out file
    xCHECK_DO(false == bIsCopyOk, vDelete(csFilePathTo); return /* false */);

    //--------------------------------------------------
    //test for size, maybe CRC
    xCHECK_DO(llGetSize(csFilePathFrom) != llGetSize(csFilePathTo), vDelete(csFilePathTo); return /* false */);
}
//--------------------------------------------------------------------------
/* static */
longlong_t
CxFile::llGetSize(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_EQ(true, bIsExists(csFilePath));

    CxFile sfFile;

    sfFile.vCreate(csFilePath, omRead, true);
    longlong_t liRv = sfFile.llGetSize();
    /*DEBUG*/xTEST_LESS_EQ(0LL, liRv);

    return liRv;
}
//---------------------------------------------------------------------------
/* static */
ulonglong_t
CxFile::ullGetLines(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_EQ(true, bIsExists(csFilePath));

    ulonglong_t      ullRv = 0LL;
    std::tifstream_t ifsStream(csFilePath.c_str(), std::ios::in);

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
CxFile::vGetTime(
    const std::tstring_t &csFilePath,
    time_t               *ptmCreate,
    time_t               *ptmAccess,
    time_t               *ptmModified
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// pftCreate   - n/a
    /*DEBUG*/// pftAccess   - n/a
    /*DEBUG*/// pftModified - n/a

#if   xOS_ENV_WIN
    FILETIME ftCreate   = {0};
    FILETIME ftAccess   = {0};
    FILETIME ftModified = {0};

    CxFileHandle m_hHandle;

    m_hHandle = ::CreateFile(csFilePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, CxFileAttribute::faNormal, NULL);
    /*DEBUG*/xTEST_EQ(true, m_hHandle.bIsValid());

    BOOL blRes = ::GetFileTime(m_hHandle.hGet(), &ftCreate, &ftAccess, &ftModified);
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);

    CxUtils::ptrAssignT(ptmCreate,   CxDateTime::tmFileTimeToUnixTime(ftCreate));
    CxUtils::ptrAssignT(ptmAccess,   CxDateTime::tmFileTimeToUnixTime(ftAccess));
    CxUtils::ptrAssignT(ptmModified, CxDateTime::tmFileTimeToUnixTime(ftModified));
#elif xOS_ENV_UNIX
    xTSTAT_STRUCT stInfo = {0};

    int iRv = ::xTSTAT(csFilePath.c_str(), &stInfo);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);

    //ctmCreate - n/a
    CxUtils::ptrAssignT(ptmAccess,   stInfo.st_atime);
    CxUtils::ptrAssignT(ptmModified, stInfo.st_mtime);
#endif
}
//---------------------------------------------------------------------------
/*static */
void
CxFile::vSetTime(
    const std::tstring_t &csFilePath,
    const time_t         &ctmCreate,
    const time_t         &ctmAccess,
    const time_t         &ctmModified
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// ctmCreate   - n/a
    /*DEBUG*/// ctmAccess   - n/a
    /*DEBUG*/// ctmModified - n/a

#if   xOS_ENV_WIN
    bool     bRv     = false;

    FILETIME ftCreate = {0};
    CxDateTime::vUnixTimeToFileTime(ctmCreate, &ftCreate);

    FILETIME ftAccess = {0};
    CxDateTime::vUnixTimeToFileTime(ctmAccess, &ftAccess);

    FILETIME ftModified = {0};
    CxDateTime::vUnixTimeToFileTime(ctmModified, &ftModified);

    CxFileHandle m_hHandle;

    m_hHandle = ::CreateFile(csFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, CxFileAttribute::faNormal, NULL);
    /*DEBUG*/xTEST_EQ(true, m_hHandle.bIsValid());

    BOOL blRes = ::SetFileTime(m_hHandle.hGet(), &ftCreate, &ftAccess, &ftModified);
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    utimbuf tbTimes = {0};

    //ctmCreate - n/a
    tbTimes.actime  = ctmAccess;
    tbTimes.modtime = ctmModified;

    int iRv = ::utime(csFilePath.c_str(), &tbTimes);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
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
    const std::tstring_t &csFilePath,
    std::tstring_t       *psContent
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_PTR(psContent);

    CxFile         sfFile;
    std::tstring_t sRv;

    sfFile.vCreate(csFilePath, omBinRead, true);

    longlong_t llFileSize = sfFile.llGetSize();
    /*DEBUG*/xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    xCHECK_DO(0LL == llFileSize, (*psContent).clear(); return);

    sRv.resize( static_cast<size_t>( llFileSize) );

    size_t uiReadLen = sfFile.uiRead((void *)&sRv.at(0), sRv.size());
    /*DEBUG*/xTEST_EQ(sRv.size(), uiReadLen);

    //out
    std::swap((*psContent), sRv);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vTextWrite(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csContent
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// csContent - n/a

    //TODO: if csContent.empty()

    bool   bRv = false;
    CxFile sfFile;

    sfFile.vCreate(csFilePath, omBinWrite, true);

    xCHECK_DO(true == csContent.empty(), return);

    size_t uiWriteLen = sfFile.uiWrite((void *)&csContent.at(0), csContent.size());
    /*DEBUG*/xTEST_EQ(csContent.size(), uiWriteLen);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vTextRead(
    const std::tstring_t &csFilePath,
    std::vec_tstring_t   *pvsContent
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_EQ(true, bIsExists(csFilePath));
    /*DEBUG*/xTEST_PTR(pvsContent);

    std::vec_tstring_t vsRes;
    std::tstring_t     sFileContent;

    vTextRead(csFilePath, &sFileContent);

    CxString::vSplit(sFileContent, CxConst::xNL, &vsRes);

    //out
    std::swap((*pvsContent), vsRes);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vTextWrite(
    const std::tstring_t     &csFilePath,
    const std::vec_tstring_t &cvsContent
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// cvsContent - n/a

    //TODO: if cvsContent.empty()

    std::tstring_t sFileContent;

    sFileContent = CxString::sJoin(cvsContent, CxConst::xNL);

    vTextWrite(csFilePath, sFileContent);
}
//--------------------------------------------------------------------------
/* static */
void
CxFile::vTextRead(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csSeparator,
    std::map_tstring_t   *pmsContent
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_EQ(true, bIsExists(csFilePath));
    /*DEBUG*/xTEST_PTR(pmsContent);

    //if file empty
    xCHECK_DO(0L == llGetSize(csFilePath), (*pmsContent).clear(); return);

    bool bRv = false;

    std::tifstream_t ifsStream(csFilePath.c_str());
    /*DEBUG*/xTEST_EQ(true,  !! ifsStream);
    /*DEBUG*/xTEST_EQ(false, ifsStream.fail());
    /*DEBUG*/xTEST_EQ(true,  ifsStream.good());
    /*DEBUG*/xTEST_EQ(true,  ifsStream.is_open());
    /*DEBUG*/xTEST_EQ(false, ifsStream.eof());

    std::map_tstring_t msRv;
    std::tstring_t     sLine;
    std::vec_tstring_t vsLine;

    for (size_t i = 0; !ifsStream.eof(); ++ i) {
        std::getline(ifsStream, sLine);

        sLine = CxString::sTrimRightChars(sLine, CxConst::xEOL);

        CxString::vSplit(sLine, csSeparator, &vsLine);

        msRv.insert( std::pair<std::tstring_t, std::tstring_t>(vsLine.at(0), vsLine.at(1)) );
    }

    //out
    (*pmsContent).swap(msRv);

#if xTODO
    bool               bRv = false;
    std::map_tstring_t msRv;
    std::vec_tstring_t vsRes;

    bRv = bTextRead(csFilePath, &vsRes);
    /*DEBUG*/xTEST_EQ(true, bRv);

    std::vec_tstring_t::_const_iterator it;
    for (it = vsRes.begin(); it != vsRes.end(); ++ it) {
        std::vec_tstring_t vsLine;

        bRv = CxString::bSplit(vsRes.at(0), csSeparator, &vsLine);
        /*DEBUG*/xTEST_EQ(true, bRv);

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
    const std::tstring_t     &csFilePath,
    const std::tstring_t     &csSeparator,
    const std::map_tstring_t &cmsContent
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_EQ(false, csSeparator.empty());
    /*DEBUG*/// cmsFile - n/a

    //TODO: if cmsFile.empty()

    bool   bRv = false;
    CxFile stdFile;

    stdFile.vCreate(csFilePath, omWrite, true);

    typedef std::map_tstring_t TContent;

    xFOREACH_CONST(TContent, it, cmsContent) {
        stdFile.vWriteLine((*it).first + csSeparator + (*it).second);
    }

#if xTODO
    bool           bRv = false;
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
    const std::tstring_t &csFilePath,
    std::ustring_t       *pusContent
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_PTR(pusContent);

    CxFile         sfFile;
    std::ustring_t usRv;

    sfFile.vCreate(csFilePath, omBinRead, true);

    longlong_t llFileSize = sfFile.llGetSize();
    /*DEBUG*/xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    xCHECK_DO(0LL == llFileSize, (*pusContent).clear(); return);

    usRv.resize( static_cast<size_t>( llFileSize ) );

    size_t uiReadLen = sfFile.uiRead((void *)&usRv.at(0), usRv.size());
    /*DEBUG*/xTEST_EQ(usRv.size(), uiReadLen);

    //out
    std::swap((*pusContent), usRv);
}
//---------------------------------------------------------------------------
/* static */
void
CxFile::vBinWrite(
    const std::tstring_t &csFilePath,
    const std::ustring_t &cusContent
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// cusContent - n/a

    //TODO: if cusContent.empty()

    CxFile sfFile;

    sfFile.vCreate(csFilePath, omBinWrite, true);

    xCHECK_DO(true == cusContent.empty(), return);

    size_t uiWriteLen = sfFile.uiWrite((void *)&cusContent.at(0), cusContent.size());
    /*DEBUG*/xTEST_EQ(cusContent.size(), uiWriteLen);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
int
CxFile::_iGetHandle(
    std::FILE *pfFile
)
{
    /*DEBUG*/xTEST_PTR(pfFile);

    int iRv = /*::*/fileno(pfFile);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);

    return iRv;
}
//---------------------------------------------------------------------------
/* static */
std::FILE *
CxFile::_pfGetHandle(
    int               iFileHandle,
    const ExOpenMode &omMode
)
{
    /*DEBUG*/

    std::FILE *pfRes = ::xTFDOPEN(iFileHandle, _sGetOpenMode(omMode).c_str());
    /*DEBUG*/xTEST_PTR(pfRes);

    return pfRes;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxFile::_sGetOpenMode(
    const ExOpenMode &comMode
)
{
    /*DEBUG*/// omMode - n/a

    std::tstring_t sRv;

    switch (comMode) {
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

        default:                    { sRv = xT("r");   }    break;
    }

    return sRv;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
