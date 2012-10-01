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

    (void)bClose();
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: open, get
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxFile::bCreate(
    const std::tstring_t &csFilePath,
    const ExOpenMode       comMode,
    const bool            cbIsUseBuffering
)
{
    /*DEBUG*/xTEST_EQ(false, bIsValid());
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_EQ(true, CxPath::bIsNameValid(csFilePath));
    /*DEBUG*/// comMode - n/a

    bool bRv = false;

    //create force dirs
    bRv = CxDir::bCreateForce( CxPath::sGetDir(csFilePath) );
    /*DEBUG*/xTEST_EQ(true, bRv);

    //create, open file
    std::FILE *pFile = ::xTFOPEN(csFilePath.c_str(), _sGetOpenMode(comMode).c_str());
    /*DEBUG*/xTEST_PTR(pFile);

    _m_pFile     = pFile;
    _m_sFilePath = csFilePath;

    //buffering
    if (false == cbIsUseBuffering) {
        bRv = bSetVBuff(NULL, bmNo,   0);
    } else {
        bRv = bSetVBuff(NULL, bmFull, BUFSIZ);
    }
    /*DEBUG*/xTEST_EQ(true, bRv);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFile::bReopen(
    const std::tstring_t &csFilePath,
    const ExOpenMode       comMode,
    const bool            cbIsUseBuffering
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
    bool bRv = false;

    if (false == cbIsUseBuffering) {
        bRv = bSetVBuff(NULL, bmNo,   0);
    } else {
        bRv = bSetVBuff(NULL, bmFull, BUFSIZ);
    }
    /*DEBUG*/xTEST_EQ(true, bRv);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFile::bAttach(
    std::FILE *pflFile
)
{
    /*DEBUG*/// _m_pFile - n/a
    /*DEBUG*/// pflFile  - n/a

    bool bRv = bClose();
    /*DEBUG*/xTEST_EQ(true, bRv);

    _m_pFile     = pflFile;
    _m_sFilePath = CxConst::xSTR_EMPTY;

    return true;
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
    const size_t  cuiCount
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
    const size_t  cuiCount
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_PTR(pcvBuff);

    size_t uiRes = std::fwrite(pcvBuff, 1, cuiCount, pGet());
    /*DEBUG*/xTEST_EQ(cuiCount, uiRes);

    return uiRes;
}
//---------------------------------------------------------------------------
bool
CxFile::bRead(
    std::ustring_t *psBuff
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_PTR(psBuff);

    longlong_t llFileSize = llGetSize();
    /*DEBUG*/xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    (*psBuff).clear();
    (*psBuff).resize( static_cast<size_t>( llFileSize ) );
    xCHECK_RET(0LL == llFileSize, true);

    size_t uiRes = std::fread(&(*psBuff).at(0), sizeof(std::ustring_t::value_type), (*psBuff).size(), pGet());
    /*DEBUG*/xTEST_EQ((*psBuff).size(), uiRes);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFile::bWrite(
    const std::ustring_t &csBuff
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*///csBuff - n/a

    size_t uiRes = std::fwrite(&csBuff.at(0), sizeof(std::ustring_t::value_type), csBuff.size(), pGet());
    /*DEBUG*/xTEST_EQ(csBuff.size(), uiRes);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFile::bRead(
    std::tstring_t *psBuff
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_PTR(psBuff);

    longlong_t llFileSize = llGetSize();
    /*DEBUG*/xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    (*psBuff).clear();
    (*psBuff).resize( static_cast<size_t>( llFileSize) );
    xCHECK_RET(0LL == llFileSize, true);

    size_t uiRes =std::fread(&(*psBuff).at(0), sizeof(std::tstring_t::value_type), (*psBuff).size(), pGet());
    /*DEBUG*/xTEST_EQ((*psBuff).size(), uiRes);

    return true;
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
bool
CxFile::bReadLine(
    std::tstring_t *psStr,
    const size_t    cuiMaxCount
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

    return true;
}
//---------------------------------------------------------------------------
bool
CxFile::bWriteLine(
    const std::tstring_t &csStr
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    std::tstring_t sLine;

    sLine = csStr;
    sLine.append(CxConst::xEOL);

    size_t uiRes = uiWrite(&sLine.at(0), sLine.size());
    /*DEBUG*/xTEST_EQ(uiRes, sLine.size());

    return true;
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
bool
CxFile::bWriteChar(
    const tchar_t ccChar
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    int iRv = xTFPUTC(static_cast<int>( ccChar ), pGet());
    /*DEBUG*/xTEST_DIFF(static_cast<int>( ccChar ), xTEOF);
    /*DEBUG*/xTEST_EQ(static_cast<int>( ccChar ), iRv);

    return true;
}
//---------------------------------------------------------------------------
//TODO: bUngetChar
bool
CxFile::bUngetChar(
    const tchar_t ccChar
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    int iRv = std::xTUNGETC(ccChar, pGet());
    /*DEBUG*/xTEST_DIFF(iRv, xTEOF);
    /*DEBUG*/xTEST_EQ(ccChar, static_cast<tchar_t>( iRv ));

    return true;
}
//---------------------------------------------------------------------------
bool
CxFile::bClear() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    return bResize(0L);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: other
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxFile::bLocking(
    const ExLockingMode clmMode,
    const long_t        cliBytes
)
{
#if   xOS_ENV_WIN
    int iRv = ::xLOCKING(_iGetHandle(pGet()), clmMode, cliBytes);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
#elif xOS_ENV_UNIX
    int iRv = ::lockf   (_iGetHandle(pGet()), clmMode, static_cast<off_t>( cliBytes ));
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxFile::bSetPosition(
    const long_t            clOffset,
    const ExPointerPosition cppPos
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    int iRv = std::fseek(pGet(), clOffset, cppPos);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);

    return true;
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
bool
CxFile::bSetVBuff(
    char                 *pszBuff,
    const ExBufferingMode cbmMode,
    const size_t          cuiSize
) const
{
    /*DEBUG*/// pszBuff - n/a
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/// cuiSize - n/a

    int iRv = std::setvbuf(pGet(), pszBuff, cbmMode, cuiSize);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);

    return true;
}
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

bool
CxFile::bSetMode(
    const ExTranslationMode ctmMode
) const
{
    int iRv = ::setmode(_iGetHandle(pGet()), ctmMode);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);

    return true;
}

#endif
//---------------------------------------------------------------------------
//NOTE: https://www.securecoding.cert.org/confluence/display/seccode/FIO19-C.+Do+not+use+fseek()+and+ftell()+to+compute+the+size+of+a+file
longlong_t
CxFile::llGetSize() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

#if xDEPRECIATE
    bool bRv = bFlush();
    /*DEBUG*/xTEST_EQ(true, bRv);

    xTSTAT_STRUCT stStat = {0};

    //TODO: fstat
    int iRv = ::xTSTAT(_m_sFilePath.c_str(), &stStat);
    /*DEBUG*/xASSERT_RET(- 1 != iRv);

    return stStat.st_size;
#else
    long_t liStreamSize    = - 1L;
    long_t liCurrStreamPos = - 1L;

    liCurrStreamPos = liGetPosition();

    xCHECK_RET(false == bSetPosition(0, ppEnd), etError);

    liStreamSize = liGetPosition();

    xCHECK_RET(false == bSetPosition(liCurrStreamPos, ppBegin), etError);

    return static_cast<longlong_t>( liStreamSize );
#endif
}
//---------------------------------------------------------------------------
bool
CxFile::bResize(
    const longlong_t cllSize
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

    return true;
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
bool
CxFile::bErrorClear() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    (void)std::clearerr( pGet() );

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: closing
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxFile::bFlush() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    int iRv = std::fflush(pGet());
    /*DEBUG*/xTEST_DIFF(xTEOF, iRv);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFile::bClose() {
    /*DEBUG*/// _m_pFile - n/a

    xCHECK_DO(false == bIsValid(), _m_pFile = NULL; return true);

    bool bRv = bErrorClear();
    /*DEBUG*/xTEST_EQ(true, bRv);

    int iRv = std::fclose(pGet());
    /*DEBUG*/xTEST_DIFF(xTEOF, iRv);

    _m_pFile = NULL;

    return true;
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
bool
CxFile::bAccess(
    const std::tstring_t &csFilePath,
    const ExAccessMode    camMode
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*///iMode

    int iRv = ::xTACCESS(csFilePath.c_str(), camMode);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFile::bChmod(
    const std::tstring_t   &csFilePath,
    const ExPermissionMode  cpmMode
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

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFile::bClear(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());

    bool   bRv = false;
    CxFile sfFile;

    bRv = sfFile.bCreate(csFilePath, omWrite, true);
    /*DEBUG*/xTEST_EQ(true, bRv);

    bRv = sfFile.bClear();
    /*DEBUG*/xTEST_EQ(true, bRv);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFile::bDelete(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    xCHECK_RET(false == bIsExists(csFilePath), true);

    bool bRv = bChmod(csFilePath, pmWrite);
    /*DEBUG*/xTEST_EQ(true, bRv);

    int iRv = ::xTREMOVE(csFilePath.c_str());
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
    /*DEBUG*/xTEST_EQ(false, bIsExists(csFilePath));

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFile::bTryDelete(
    const std::tstring_t &csFilePath,
    const size_t          cuiAttempts,
    const ulong_t         culTimeoutMsec
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_LESS(size_t(0U), cuiAttempts);

    const size_t cuiMaxAttempts  = 100;  //MAGIC_NUMBER: cuiMaxAttempts
    const size_t cuiRealAttempts = (cuiMaxAttempts < cuiAttempts) ? cuiMaxAttempts : cuiAttempts;


    bool bIsDeleted = false;

    for (size_t i = 0; i < cuiRealAttempts; ++ i) {
        bool bRv = bDelete(csFilePath);
        xCHECK_DO(true == bRv, bIsDeleted = true; break);

        bRv = CxCurrentThread::bSleep(culTimeoutMsec);
        /*DEBUG*/xTEST_EQ(true, bRv);
    }

    return bIsDeleted;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFile::bWipe(
    const std::tstring_t &csFilePath,
    const size_t          cuiPasses
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// cuiPasses - n/a

    xCHECK_RET(false == bIsExists(csFilePath), true);

    bool bRv = false;

    {
        CxFile sfFile;

        //--------------------------------------------------
        //set normal file attributes
        bRv = CxFileAttribute::bSet(csFilePath, CxFileAttribute::faNormal);
        /*DEBUG*/xTEST_EQ(true, bRv);

        //--------------------------------------------------
        //open
        bRv = sfFile.bCreate(csFilePath, omBinWrite, true);
        /*DEBUG*/xTEST_EQ(true, bRv);

        longlong_t llSize = sfFile.llGetSize();
        if (0LL < llSize) {
            //--------------------------------------------------
            //fill by 0x55, 0xAA, random char
            for (size_t p = 0; p < cuiPasses; ++ p) {
                CxRandom::bSetSeed();

                const uchar_t chRand  = static_cast<uchar_t>(CxRandom::liGetInt(0, 255) + 1);
                const uchar_t chChar1 = 0x55;
                const uchar_t chChar2 = 0xAA;

                //chRand
                {
                    bRv = sfFile.bSetPosition(0L, ppBegin);
                    /*DEBUG*/xTEST_EQ(true, bRv);

                    for (longlong_t i = 0LL; i < llSize; ++ i) {
                        size_t uiRes = std::fwrite(&chRand, 1, sizeof(chRand), sfFile.pGet());
                        /*DEBUG*/xTEST_EQ(sizeof(chRand), uiRes);
                    }
                }

                //chChar1
                {
                    bRv = sfFile.bSetPosition(0L, ppBegin);
                    /*DEBUG*/xTEST_EQ(true, bRv);

                    for (longlong_t i = 0LL; i < llSize; ++ i) {
                        size_t uiRes = std::fwrite(&chChar1, 1, sizeof(chChar1), sfFile.pGet());
                        /*DEBUG*/xTEST_EQ(sizeof(chChar1), uiRes);
                    }
                }

                //chChar2
                {
                    bRv = sfFile.bSetPosition(0L, ppBegin);
                    /*DEBUG*/xTEST_EQ(true, bRv);

                    for (longlong_t i = 0LL; i < llSize; ++ i) {
                        size_t uiRes = std::fwrite(&chChar2, 1, sizeof(chChar2), sfFile.pGet());
                        /*DEBUG*/xTEST_EQ(sizeof(chChar2), uiRes);
                    }
                }
            }

            //--------------------------------------------------
            //truncate
            bRv = sfFile.bFlush();
            /*DEBUG*/xTEST_EQ(true, bRv);

            bRv = sfFile.bResize(0L);
            /*DEBUG*/xTEST_EQ(true, bRv);
        }
    }

    //--------------------------------------------------
    //reset filetime
    {
        const time_t ctmCreate   = 0;
        const time_t ctmAccess   = 0;
        const time_t ctmModified = 0;

        bRv = bSetTime(csFilePath, ctmCreate, ctmAccess, ctmModified);
        /*DEBUG*/xTEST_EQ(true, bRv);
    }

    //--------------------------------------------------
    //random file name
    std::tstring_t sRndFilePath;

    {
        std::tstring_t sRndFileName;

        sRndFileName = CxString::string_cast( CxDateTime().dtGetCurrent().ullToMilliseconds() );
        std::random_shuffle(sRndFileName.begin(), sRndFileName.end());

        sRndFilePath = CxPath::sGetDir(csFilePath) + CxConst::xSLASH + sRndFileName;

        bRv = bRename(csFilePath, sRndFilePath);
        /*DEBUG*/xTEST_EQ(true, bRv);
    }

    //--------------------------------------------------
    //delete
    bRv = bDelete(sRndFilePath);
    /*DEBUG*/xTEST_EQ(true, bRv);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFile::bUnlink(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());

    int iRv = ::xTUNLINK(csFilePath.c_str());
    /*DEBUG*/xTEST_DIFF(- 1, iRv);

    return false;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFile::bRename(
    const std::tstring_t &csOldFilePath,
    const std::tstring_t &csNewFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csOldFilePath.empty());
    /*DEBUG*/xTEST_EQ(false, csNewFilePath.empty());

    int iRv = ::xTRENAME(csOldFilePath.c_str(), csNewFilePath.c_str());
    /*DEBUG*/xTEST_DIFF(- 1, iRv);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFile::bMove(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_EQ(false, csDirPath.empty());

    bool bRv = bRename(csFilePath, CxPath::sSlashAppend(csDirPath) + CxPath::sGetFileName(csFilePath));
    /*DEBUG*/xTEST_EQ(true, bRv);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFile::bCopy(
    const std::tstring_t &csFilePathFrom,
    const std::tstring_t &csFilePathTo,
    const bool            cbFailIfExists
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePathFrom.empty());
    /*DEBUG*/xTEST_EQ(false, csFilePathTo.empty());

    bool bIsCopyOk = true;

    //--------------------------------------------------
    //fail if exists
    xCHECK_RET(true == cbFailIfExists && true == bIsExists(csFilePathTo), false);
    //TODO: check filesize

    {
        //--------------------------------------------------
        //open files
        CxFile sfFrom;

        bool bRv = sfFrom.bCreate(csFilePathFrom, omBinRead, true);
        xCHECK_RET(false == bRv, false);

        CxFile sfTo;

        bRv = sfTo.bCreate(csFilePathTo, omBinWrite, true);
        xCHECK_RET(false == bRv, false);

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
    xCHECK_DO(false == bIsCopyOk, bDelete(csFilePathTo); return false);

    //--------------------------------------------------
    //test for size, maybe CRC
    xCHECK_DO(llGetSize(csFilePathFrom) != llGetSize(csFilePathTo), (void)bDelete(csFilePathTo); return false);

    return true;
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

    bool bRv = sfFile.bCreate(csFilePath, omRead, true);
    /*DEBUG*/xTEST_EQ(true, bRv);

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
bool
CxFile::bGetTime(
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

    return true;
}
//---------------------------------------------------------------------------
/*static */
bool
CxFile::bSetTime(
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
    bRv = CxDateTime::bUnixTimeToFileTime(ctmCreate, &ftCreate);
    /*DEBUG*/xTEST_EQ(true, bRv);

    FILETIME ftAccess = {0};
    bRv = CxDateTime::bUnixTimeToFileTime(ctmAccess, &ftAccess);
    /*DEBUG*/xTEST_EQ(true, bRv);

    FILETIME ftModified = {0};
    bRv = CxDateTime::bUnixTimeToFileTime(ctmModified, &ftModified);
    /*DEBUG*/xTEST_EQ(true, bRv);

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

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: text
*
*****************************************************************************/

//--------------------------------------------------------------------------
/* static */
bool
CxFile::bTextRead(
    const std::tstring_t &csFilePath,
    std::tstring_t       *psContent
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_PTR(psContent);

    CxFile         sfFile;
    std::tstring_t sRv;

    bool bRv = sfFile.bCreate(csFilePath, omBinRead, true);
    /*DEBUG*/xTEST_EQ(true, bRv);

    longlong_t llFileSize = sfFile.llGetSize();
    /*DEBUG*/xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    xCHECK_DO(0LL == llFileSize, (*psContent).clear(); return true);

    sRv.resize( static_cast<size_t>( llFileSize) );

    size_t uiReadLen = sfFile.uiRead((void *)&sRv.at(0), sRv.size());
    /*DEBUG*/xTEST_EQ(sRv.size(), uiReadLen);

    //out
    std::swap((*psContent), sRv);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFile::bTextWrite(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csContent
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// csContent - n/a

    //TODO: if csContent.empty()

    bool   bRv = false;
    CxFile sfFile;

    bRv = sfFile.bCreate(csFilePath, omBinWrite, true);
    /*DEBUG*/xTEST_EQ(true, bRv);

    xCHECK_RET(true == csContent.empty(), true);

    size_t uiWriteLen = sfFile.uiWrite((void *)&csContent.at(0), csContent.size());
    /*DEBUG*/xTEST_EQ(csContent.size(), uiWriteLen);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFile::bTextRead(
    const std::tstring_t &csFilePath,
    std::vec_tstring_t   *pvsContent
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_EQ(true, bIsExists(csFilePath));
    /*DEBUG*/xTEST_PTR(pvsContent);

    bool               bRv = false;
    std::vec_tstring_t vsRes;
    std::tstring_t     sFileContent;

    bRv = bTextRead(csFilePath, &sFileContent);
    /*DEBUG*/xTEST_EQ(true, bRv);

    bRv = CxString::bSplit(sFileContent, CxConst::xNL, &vsRes);
    /*DEBUG*/xTEST_EQ(true, bRv);

    //out
    std::swap((*pvsContent), vsRes);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFile::bTextWrite(
    const std::tstring_t     &csFilePath,
    const std::vec_tstring_t &cvsContent
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// cvsContent - n/a

    //TODO: if cvsContent.empty()

    bool           bRv = false;
    std::tstring_t sFileContent;

    sFileContent = CxString::sJoin(cvsContent, CxConst::xNL);

    bRv = bTextWrite(csFilePath, sFileContent);
    /*DEBUG*/xTEST_EQ(true, bRv);

    return true;
}
//--------------------------------------------------------------------------
/* static */
bool
CxFile::bTextRead(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csSeparator,
    std::map_tstring_t   *pmsContent
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_EQ(true, bIsExists(csFilePath));
    /*DEBUG*/xTEST_PTR(pmsContent);

    //if file empty
    xCHECK_DO(0L == llGetSize(csFilePath), (*pmsContent).clear(); return true);

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

        bRv = CxString::bSplit(sLine, csSeparator, &vsLine);
        /*DEBUG*/xTEST_EQ(true, bRv);

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

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFile::bTextWrite(
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

    bRv = stdFile.bCreate(csFilePath, omWrite, true);
    /*DEBUG*/xTEST_EQ(true, bRv);

    typedef std::map_tstring_t TContent;

    xFOREACH_CONST(TContent, it, cmsContent) {
        bRv = stdFile.bWriteLine((*it).first + csSeparator + (*it).second);
        /*DEBUG*/xTEST_EQ(true, bRv);
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

    bRv = bTextWrite(csFilePath, sRv);
    /*DEBUG*/xTEST_EQ(true, bRv);
#endif

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: bin
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
bool
CxFile::bBinRead(
    const std::tstring_t &csFilePath,
    std::ustring_t       *pusContent
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_PTR(pusContent);

    bool           bRv = false;
    CxFile         sfFile;
    std::ustring_t usRv;

    bRv = sfFile.bCreate(csFilePath, omBinRead, true);
    /*DEBUG*/xTEST_EQ(true, bRv);

    longlong_t llFileSize = sfFile.llGetSize();
    /*DEBUG*/xTEST_DIFF(static_cast<longlong_t>( ppError ), llFileSize);

    xCHECK_DO(0LL == llFileSize, (*pusContent).clear(); return true);

    usRv.resize( static_cast<size_t>( llFileSize ) );

    size_t uiReadLen = sfFile.uiRead((void *)&usRv.at(0), usRv.size());
    /*DEBUG*/xTEST_EQ(usRv.size(), uiReadLen);

    //out
    std::swap((*pusContent), usRv);

    return true;

}
//---------------------------------------------------------------------------
/* static */
bool
CxFile::bBinWrite(
    const std::tstring_t &csFilePath,
    const std::ustring_t &cusContent
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// cusContent - n/a

    //TODO: if cusContent.empty()

    bool   bRv = false;
    CxFile sfFile;

    bRv = sfFile.bCreate(csFilePath, omBinWrite, true);
    /*DEBUG*/xTEST_EQ(true, bRv);

    xCHECK_RET(true == cusContent.empty(), true);

    size_t uiWriteLen = sfFile.uiWrite((void *)&cusContent.at(0), cusContent.size());
    /*DEBUG*/xTEST_EQ(cusContent.size(), uiWriteLen);

    return true;
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
    int              iFileHandle,
    const ExOpenMode omMode
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
    const ExOpenMode comMode
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
