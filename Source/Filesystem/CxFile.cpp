/**
 * \file  CxFile.cpp
 * \brief file
 */


#include <xLib/Filesystem/CxFile.h>

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
/*virtual*/
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
BOOL
CxFile::bCreate(
    const std::string_t &csFilePath,
    const EOpenMode     comMode,
    const BOOL          cbIsUseBuffering
)
{
    /*DEBUG*/xASSERT_RET(FALSE == bIsValid(),                       FALSE);
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != CxPath::bIsNameValid(csFilePath), FALSE);
    /*DEBUG*/// comMode - n/a

    BOOL bRes = FALSE;

    //create force dirs
    bRes = CxDir::bCreateForce( CxPath::sGetDir(csFilePath) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //create, open file
    std::FILE *pFile = std::xTFOPEN(csFilePath.c_str(), _sGetOpenMode(comMode).c_str());
    /*DEBUG*/xASSERT_RET(NULL != pFile, FALSE);

    _m_pFile     = pFile;
    _m_sFilePath = csFilePath;

    //buffering
    if (FALSE == cbIsUseBuffering) {
        bRes = bSetVBuff(NULL, bmNo,   0);
    } else {
        bRes = bSetVBuff(NULL, bmFull, BUFSIZ);
    }
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bReopen(
    const std::string_t &csFilePath,
    const EOpenMode     comMode,
    const BOOL          cbIsUseBuffering
)
{
    /*DEBUG*/// _m_pFile - n/a
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != CxPath::bIsNameValid(csFilePath), FALSE);
    /*DEBUG*/// omMode - n/a

    std::FILE *pFile = std::xTFREOPEN(csFilePath.c_str(), _sGetOpenMode(comMode).c_str(), _m_pFile);
    /*DEBUG*/xASSERT_RET(NULL != pFile, FALSE);

    _m_pFile     = pFile;
    _m_sFilePath = csFilePath;

    //buffering
    BOOL bRes = FALSE;

    if (FALSE == cbIsUseBuffering) {
        bRes = bSetVBuff(NULL, bmNo,   0);
    } else {
        bRes = bSetVBuff(NULL, bmFull, BUFSIZ);
    }
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bAttach(
    std::FILE *pflFile
)
{
    /*DEBUG*/// _m_pFile - n/a
    /*DEBUG*/// pflFile  - n/a

    BOOL bRes = bClose();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    _m_pFile     = pflFile;
    _m_sFilePath = CxConst::xSTR_EMPTY;

    return TRUE;
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
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), NULL);

    return _m_pFile;
}
//---------------------------------------------------------------------------
std::string_t
CxFile::sGetPath() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),              std::string_t());
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(),    std::string_t());
    /*DEBUG*/xASSERT_RET(FALSE != bIsExists(_m_sFilePath), std::string_t());

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
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0);
    /*DEBUG*/xASSERT_RET(NULL  != pvBuff,     0);

    size_t uiRes = std::fread(pvBuff, 1, cuiCount, pGet());
    /*DEBUG*/xASSERT_RET(cuiCount >= uiRes, uiRes);

    return uiRes;
}
//---------------------------------------------------------------------------
size_t
CxFile::uiWrite(
    const void   *pcvBuff,
    const size_t  cuiCount
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0);
    /*DEBUG*/xASSERT_RET(NULL  != pcvBuff,    0);

    size_t uiRes = std::fwrite(pcvBuff, 1, cuiCount, pGet());
    /*DEBUG*/xASSERT_RET(cuiCount == uiRes, uiRes);

    return uiRes;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bRead(
    std::ustring *psBuff
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != psBuff,     FALSE);

    LONG liFileSize = liGetSize();
    /*DEBUG*/xASSERT_RET(ppError != liFileSize, FALSE);

    (*psBuff).clear();
    (*psBuff).resize(liFileSize);
    xCHECK_RET(0L == liFileSize, TRUE);

    size_t uiRes = std::fread(&(*psBuff).at(0), sizeof(std::ustring::value_type), (*psBuff).size(), pGet());
    /*DEBUG*/xASSERT_RET((*psBuff).size() == uiRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bWrite(
    const std::ustring &csBuff
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*///csBuff - n/a

    size_t uiRes = std::fwrite(&csBuff.at(0), sizeof(std::ustring::value_type), csBuff.size(), pGet());
    /*DEBUG*/xASSERT_RET(csBuff.size() == uiRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bRead(
    std::string_t *psBuff
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != psBuff,     FALSE);

    LONG liFileSize = liGetSize();
    /*DEBUG*/xASSERT_RET(ppError != liFileSize, FALSE);

    (*psBuff).clear();
    (*psBuff).resize(liFileSize);
    xCHECK_RET(0L == liFileSize, TRUE);

    size_t uiRes =std::fread(&(*psBuff).at(0), sizeof(std::string_t::value_type), (*psBuff).size(), pGet());
    /*DEBUG*/xASSERT_RET((*psBuff).size() == uiRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
int
CxFile::iWrite(
    const char_t *pcszFormat, ...
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), etError);
    /*DEBUG*/xASSERT_RET(NULL  != pcszFormat, etError);

    va_list vlArgs;
    xVA_START(vlArgs, pcszFormat);

    int iRes = std::xTVFPRINTF(pGet(), pcszFormat, vlArgs);
    /*DEBUG*/xASSERT_RET(- 1 < iRes, etError);

    xVA_END(vlArgs);

    return iRes;
}
//---------------------------------------------------------------------------
int
CxFile::iWriteV(
    const char_t *pcszFormat,
    va_list      vlArgs
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), etError);
    /*DEBUG*/xASSERT_RET(NULL  != pcszFormat, etError);
    /*DEBUG*/xASSERT_RET(NULL  != vlArgs,     etError);

    int iRes = std::xTVFPRINTF(pGet(), pcszFormat, vlArgs);
    /*DEBUG*/xASSERT_RET(- 1 < iRes, etError);

    return iRes;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bReadLine(
    std::string_t *psStr,
    const size_t  cuiMaxCount
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != psStr,      FALSE);
    /*DEBUG*/xASSERT_RET(0     < cuiMaxCount, FALSE);

    #if xTEMP_DISABLED
        if ((*psStr).size() != cuiMaxCount) {
            (*psStr).resize(cuiMaxCount);
        }
        std::fill((*psStr).begin(), (*psStr).end(), std::string_t::value_type());
    #endif

    (*psStr).clear();
    (*psStr).resize(cuiMaxCount + 1);   //+ 1 for 0

    char_t *pszRes = std::xTFGETS(&(*psStr).at(0), (*psStr).size(), pGet());
    /*DEBUG*/xASSERT_RET(NULL != pszRes, FALSE);

    (*psStr).erase( (*psStr).end() - 1 );   //erase last char - 0

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bWriteLine(
    const std::string_t &csStr
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    std::string_t sLine;

    sLine.assign(csStr);
    sLine.append(CxConst::xEOL);

    size_t uiRes = uiWrite(&sLine.at(0), sLine.size());
    /*DEBUG*/xASSERT_RET(uiRes == sLine.size(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: chReadChar
char_t
CxFile::chReadChar() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    int iRes = std::xTFGETC(pGet());
    /*DEBUG*/xASSERT_RET(xTEOF <= iRes, static_cast<char_t>( etError ));

    return static_cast<char_t>( iRes );
}
//---------------------------------------------------------------------------
//TODO: bWriteChar
BOOL
CxFile::bWriteChar(
    const char_t ccChar
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    int iRes = xTFPUTC(static_cast<int>( ccChar ), pGet());
    /*DEBUG*/xASSERT_RET(static_cast<int>( ccChar ) != xTEOF, FALSE);
    /*DEBUG*/xASSERT_RET(static_cast<int>( ccChar ) == iRes,  FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bUngetChar
BOOL
CxFile::bUngetChar(
    const char_t ccChar
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    int iRes = std::xTUNGETC(ccChar, pGet());
    /*DEBUG*/xASSERT_RET(iRes   != xTEOF,                      FALSE);
    /*DEBUG*/xASSERT_RET(ccChar == static_cast<char_t>( iRes ), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bClear() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    return bResize(0L);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: other
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxFile::bLocking(
    const ELockingMode clmMode,
    const LONG         cliBytes
)
{
#if defined(xOS_ENV_WIN)
    #if defined(xCOMPILER_CODEGEAR)
        #define xLOCKING locking
    #else
        #define xLOCKING _locking
    #endif

    int iRes = ::xLOCKING(_iGetHandle(pGet()), clmMode, cliBytes);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    int iRes = ::lockf(_iGetHandle(pGet()), clmMode, static_cast<off_t>( cliBytes ));
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bSetPosition(
    const LONG             clOffset,
    const EPointerPosition cppPos
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    int iRet = std::fseek(pGet(), clOffset, cppPos);
    /*DEBUG*/xASSERT_RET(- 1 != iRet, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
LONG
CxFile::liGetPosition() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    LONG liRes = std::ftell(pGet());
    /*DEBUG*/xASSERT_RET(- 1 != liRes, ppError);

    return liRes;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bSetVBuff(
    char                 *pszBuff,
    const EBufferingMode  cbmMode,
    const size_t          cuiSize
) const
{
    /*DEBUG*/// pszBuff - n/a
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/// cuiSize - n/a

    int iRes = std::setvbuf(pGet(), pszBuff, cbmMode, cuiSize);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

BOOL
CxFile::bSetMode(
    const ETranslationMode ctmMode
) const
{
    int iRes = ::setmode(_iGetHandle(pGet()), ctmMode);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);

    return TRUE;
}

#endif
//---------------------------------------------------------------------------
//NOTE: https://www.securecoding.cert.org/confluence/display/seccode/FIO19-C.+Do+not+use+fseek()+and+ftell()+to+compute+the+size+of+a+file
LONG
CxFile::liGetSize() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), etError);

    LONG liStreamSize    = - 1L;
    LONG liCurrStreamPos = - 1L;

    //Get current position
    liCurrStreamPos = liGetPosition();

    //seek to the end of file
    xCHECK_RET(FALSE == bSetPosition(0, ppEnd), etError);

    liStreamSize = liGetPosition();

    //Get back to the stored position
    xCHECK_RET(FALSE == bSetPosition(liCurrStreamPos, ppBegin), etError);

    return liStreamSize;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bResize(
    const LONG cliSize
) const
{
    /*DEBUG*/// n/a

#if defined(xOS_ENV_WIN)
    int iRes = ::chsize(_iGetHandle(pGet()), cliSize);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    int iRes = ::ftruncate(_iGetHandle(pGet()), static_cast<off_t>( cliSize ));
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    /*DEBUG*/xASSERT_RET(cliSize == liGetSize(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------

/****************************************************************************
*    public: error handling
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxFile::bIsValid() const {
    /*DEBUG*/

    return static_cast<BOOL>( NULL != _m_pFile );
}
//---------------------------------------------------------------------------
BOOL
CxFile::bIsOpen() const {
    /*DEBUG*/// n/a

    return bIsValid();
}
//---------------------------------------------------------------------------
BOOL
CxFile::bIsEmpty() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    LONG liFileSize = liGetSize();
    /*DEBUG*/xASSERT_RET(- 1L != liFileSize, TRUE);

    return static_cast<BOOL>( 0L == liFileSize);
}
//---------------------------------------------------------------------------
BOOL
CxFile::bIsEof() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    return static_cast<BOOL>( std::feof(pGet()) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
BOOL
CxFile::bIsError() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    return static_cast<BOOL>( std::ferror(pGet()) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------

BOOL
CxFile::bErrorClear() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    (void)std::clearerr(pGet());

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: closing
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxFile::bFlush() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    int iRes = std::fflush(pGet());
    /*DEBUG*/xASSERT_RET(xTEOF != iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bClose() {
    /*DEBUG*/// _m_pFile - n/a

    if (FALSE != bIsValid()) {
        BOOL bRes = bErrorClear();
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        int iRes = std::fclose(pGet());
        /*DEBUG*/xASSERT_RET(xTEOF != iRes, FALSE);
    }

    _m_pFile = NULL;

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public, static
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bIsFile(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/// csFilePath - n/a

    BOOL bRes = FALSE;

    CxFileAttribute::EAttribute atAttr = CxFileAttribute::atGet(csFilePath);
    xCHECK_RET(CxFileAttribute::faInvalid == atAttr, FALSE);

#if defined(xOS_ENV_WIN)
    bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faDirectory);
    xCHECK_RET(TRUE == bRes, FALSE);

    bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faDevice);
    xCHECK_RET(TRUE == bRes, FALSE);

    bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faReparsePoint);
    xCHECK_RET(TRUE == bRes, FALSE);

    bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faOffline);
    xCHECK_RET(TRUE == bRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faRegularFile);
    xCHECK_RET(FALSE == bRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bIsExists(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/// csFilePath - n/a
    xCHECK_RET(FALSE == bIsFile(csFilePath), FALSE);

    int iRes       = ::xTACCESS(csFilePath.c_str(), amExistence);
    int iLastError = CxStdError::iGet();
    xCHECK_RET((- 1 == iRes) && (ENOENT == iLastError), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxFile::sIsExists(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());

    std::string_t sRes;

    std::string_t sFileDir  = CxPath::sGetDir(csFilePath);
    std::string_t sFileName = CxPath::sGetName(csFilePath);
    std::string_t sFileExt  = CxPath::sGetExt(csFilePath);

    xCHECK_DO(false == sFileExt.empty(), sFileExt.insert(0, CxConst::xDOT));

    for (ULONG ulExistsIndex = 1; ; ++ ulExistsIndex) {
        sRes = CxString::sFormat(xT("%s%s%s (%li)%s"),
                                 sFileDir.c_str(), CxConst::xSLASH.c_str(), sFileName.c_str(), ulExistsIndex, sFileExt.c_str());

        xCHECK_DO(FALSE == bIsExists(sRes), break);
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bAccess(
    const std::string_t &csFilePath,
    const EAccessMode   camMode
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*///iMode

    int iRes = ::xTACCESS(csFilePath.c_str(), camMode);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bChmod(
    const std::string_t    &csFilePath,
    const EPermissionMode  cpmMode
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*///iMode

#if defined(xOS_ENV_WIN)
    int iRes = ::xTCHMOD(csFilePath.c_str(), static_cast<int>( cpmMode ));
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    int iRes = ::xTCHMOD(csFilePath.c_str(), static_cast<mode_t>( cpmMode ));
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bClear(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    BOOL   bRes = FALSE;
    CxFile sfFile;

    bRes = sfFile.bCreate(csFilePath, omWrite, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = sfFile.bClear();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bDelete(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    xCHECK_RET(FALSE == bIsExists(csFilePath), TRUE);

    BOOL bRes = bChmod(csFilePath, pmWrite);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    int iRes = std::xTREMOVE(csFilePath.c_str());
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);

    /*DEBUG*/xASSERT_RET(FALSE == bIsExists(csFilePath), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bTryDelete(
    const std::string_t &csFilePath,
    const size_t        cuiAttempts,
    const ULONG         culTimeoutMsec
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(0     <  cuiAttempts,        FALSE);

    const size_t cuiMaxAttempts  = 100;  //MAGIC_NUMBER: cuiMaxAttempts
    const size_t cuiRealAttempts = (cuiMaxAttempts < cuiAttempts) ? cuiMaxAttempts : cuiAttempts;


    BOOL bIsDeleted = FALSE;

    for (size_t i = 0; i < cuiRealAttempts; ++ i) {
        BOOL bRes = bDelete(csFilePath);
        xCHECK_DO(TRUE == bRes, bIsDeleted = TRUE; break);

        bRes = CxCurrentThread::bSleep(culTimeoutMsec);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    return bIsDeleted;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bWipe(
    const std::string_t &csFilePath,
    const size_t        cuiPasses
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cuiPasses - n/a

    xCHECK_RET(FALSE == bIsExists(csFilePath), TRUE);

    BOOL bRes = FALSE;

    {
        CxFile sfFile;

        //--------------------------------------------------
        //set normal file attributes
        bRes = CxFileAttribute::bSet(csFilePath, CxFileAttribute::faNormal);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        //--------------------------------------------------
        //open
        bRes = sfFile.bCreate(csFilePath, omBinWrite, TRUE);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        LONG liSize = sfFile.liGetSize();
        if (0L < liSize) {
            //--------------------------------------------------
            //fill by 0x55, 0xAA, random char
            for (size_t p = 0; p < cuiPasses; ++ p) {
                CxRandom::bSetSeed();

                const UCHAR chRand  = static_cast<UCHAR>(CxRandom::liGetInt(0, 255) + 1);
                const UCHAR chChar1 = 0x55;
                const UCHAR chChar2 = 0xAA;

                //chRand
                {
                    bRes = sfFile.bSetPosition(0L, ppBegin);
                    /*DEBUG*/xASSERT(FALSE != bRes);

                    for (LONG i = 0L; i < liSize; ++ i) {
                        size_t uiRes = std::fwrite(&chRand, 1, sizeof(chRand), sfFile.pGet());
                        /*DEBUG*/xASSERT_RET(sizeof(chRand) == uiRes, FALSE);
                    }
                }

                //chChar1
                {
                    bRes = sfFile.bSetPosition(0L, ppBegin);
                    /*DEBUG*/xASSERT(FALSE != bRes);

                    for (LONG i = 0L; i < liSize; ++ i) {
                        size_t uiRes = std::fwrite(&chChar1, 1, sizeof(chChar1), sfFile.pGet());
                        /*DEBUG*/xASSERT_RET(sizeof(chChar1) == uiRes, FALSE);
                    }
                }

                //chChar2
                {
                    bRes = sfFile.bSetPosition(0L, ppBegin);
                    /*DEBUG*/xASSERT(FALSE != bRes);

                    for (LONG i = 0L; i < liSize; ++ i) {
                        size_t uiRes = std::fwrite(&chChar2, 1, sizeof(chChar2), sfFile.pGet());
                        /*DEBUG*/xASSERT_RET(sizeof(chChar2) == uiRes, FALSE);
                    }
                }
            }

            //--------------------------------------------------
            //truncate
            bRes = sfFile.bFlush();
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

            bRes = sfFile.bResize(0L);
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
        }
    }

    //--------------------------------------------------
    //reset filetime
    {
        const time_t ctmCreate   = 0;
        const time_t ctmAccess   = 0;
        const time_t ctmModified = 0;

        bRes = bSetTime(csFilePath, ctmCreate, ctmAccess, ctmModified);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    //--------------------------------------------------
    //random file name
    std::string_t sRndFilePath;

    {
        std::string_t sRndFileName;

        sRndFileName = CxString::lexical_cast( CxDateTime().dtGetCurrent().ullToMilliseconds() );
        std::random_shuffle(sRndFileName.begin(), sRndFileName.end());

        sRndFilePath = CxPath::sGetDir(csFilePath) + CxConst::xSLASH + sRndFileName;

        bRes = bRename(csFilePath, sRndFilePath);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    //--------------------------------------------------
    //delete
    bRes = bDelete(sRndFilePath);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bUnlink(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    int iRes = ::xTUNLINK(csFilePath.c_str());
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);

    return FALSE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bRename(
    const std::string_t &csOldFilePath,
    const std::string_t &csNewFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csOldFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csNewFilePath.empty(), FALSE);

    int iRes = std::xTRENAME(csOldFilePath.c_str(), csNewFilePath.c_str());
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bMove(
    const std::string_t &csFilePath,
    const std::string_t &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(),  FALSE);

    BOOL bRes = bRename(csFilePath, CxPath::sSlashAppend(csDirPath) + CxPath::sGetFullName(csFilePath));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bCopy(
    const std::string_t &csFilePathFrom,
    const std::string_t &csFilePathTo,
    const BOOL          cbFailIfExists
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePathFrom.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csFilePathTo.empty(),   FALSE);

    BOOL bIsCopyOk = TRUE;

    //--------------------------------------------------
    //fail if exists
    xCHECK_RET(TRUE == cbFailIfExists && TRUE == bIsExists(csFilePathTo), FALSE);
    //TODO: check filesize

    {
        //--------------------------------------------------
        //open files
        CxFile sfFrom;

        BOOL bRes = sfFrom.bCreate(csFilePathFrom, omBinRead, TRUE);
        xCHECK_RET(FALSE == bRes, FALSE);

        CxFile sfTo;

        bRes = sfTo.bCreate(csFilePathTo, omBinWrite, TRUE);
        xCHECK_RET(FALSE == bRes, FALSE);

        //--------------------------------------------------
        //copy files
        const size_t cuiBuffSize         = 1024;
        UCHAR        ucBuff[cuiBuffSize] = {0};

        for ( ; ; ) {
            const size_t uiReaded  = sfFrom.uiRead(ucBuff, cuiBuffSize);
            xCHECK_DO(0 >= uiReaded, break);

            const size_t uiWritten = sfTo.uiWrite(ucBuff, uiReaded);
            xCHECK_DO(uiReaded != uiWritten, bIsCopyOk = FALSE; break);
        }
    }

    //--------------------------------------------------
    //if copy fail - delete out file
    xCHECK_DO(FALSE == bIsCopyOk, bDelete(csFilePathTo); return FALSE);

    //--------------------------------------------------
    //test for size, maybe CRC
    xCHECK_DO(liGetSize(csFilePathFrom) != liGetSize(csFilePathTo), (void)bDelete(csFilePathTo); return FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
/*static*/
LONG
CxFile::liGetSize(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    - 1L);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), - 1L);

    CxFile sfFile;

    BOOL bRes = sfFile.bCreate(csFilePath, omRead, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, - 1L);

    LONG liRes = sfFile.liGetSize();
    /*DEBUG*/xASSERT_RET(0L <= liRes, - 1L);

    return liRes;
}
//---------------------------------------------------------------------------
/*static*/
ULONGLONG
CxFile::ullGetLines(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    0LL);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), 0LL);

    ULONGLONG       ullRes = 0LL;
    std::ifstream_t ifsStream(csFilePath.c_str(), std::ios::in);

    xCHECK_RET(!ifsStream || ifsStream.fail() || !ifsStream.good() || !ifsStream.is_open() || ifsStream.eof(), 0LL);

    char_t chChar;
    for (ullRes = 0LL; ifsStream.get(chChar); ) {
        xCHECK_DO(xT('\n') == chChar, ++ ullRes);
    }

    return ullRes;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bGetTime(
    const std::string_t &csFilePath,
    time_t             *ptmCreate,
    time_t             *ptmAccess,
    time_t             *ptmModified
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// pftCreate   - n/a
    /*DEBUG*/// pftAccess   - n/a
    /*DEBUG*/// pftModified - n/a

#if defined(xOS_ENV_WIN)
    FILETIME ftCreate   = {{0}};
    FILETIME ftAccess   = {{0}};
    FILETIME ftModified = {{0}};

    CxFileHandle m_hHandle;

    m_hHandle = ::CreateFile(csFilePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, CxFileAttribute::faNormal, NULL);
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), FALSE);

    BOOL bRes = ::GetFileTime(m_hHandle, &ftCreate, &ftAccess, &ftModified);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    xCHECK_DO(NULL != ptmCreate,   *ptmCreate   = CxDateTime::tmFileTimeToUnixTime(ftCreate));
    xCHECK_DO(NULL != ptmAccess,   *ptmAccess   = CxDateTime::tmFileTimeToUnixTime(ftAccess));
    xCHECK_DO(NULL != ptmModified, *ptmModified = CxDateTime::tmFileTimeToUnixTime(ftModified));
#elif defined(xOS_ENV_UNIX)
    xTSTAT_STRUCT stInfo = {0};

    int iRes = ::xTSTAT(csFilePath.c_str(), &stInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);

    //ctmCreate - n/a
    xCHECK_DO(NULL != ptmAccess,   *ptmAccess   = stInfo.st_atime);
    xCHECK_DO(NULL != ptmModified, *ptmModified = stInfo.st_mtime);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static */
BOOL
CxFile::bSetTime(
    const std::string_t &csFilePath,
    const time_t       &ctmCreate,
    const time_t       &ctmAccess,
    const time_t       &ctmModified
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// ctmCreate   - n/a
    /*DEBUG*/// ctmAccess   - n/a
    /*DEBUG*/// ctmModified - n/a

#if defined(xOS_ENV_WIN)
    BOOL     bRes     = FALSE;

    FILETIME ftCreate = {0};
    bRes = CxDateTime::bUnixTimeToFileTime(ctmCreate, &ftCreate);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    FILETIME ftAccess = {0};
    bRes = CxDateTime::bUnixTimeToFileTime(ctmAccess, &ftAccess);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    FILETIME ftModified = {0};
    bRes = CxDateTime::bUnixTimeToFileTime(ctmModified, &ftModified);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    CxFileHandle m_hHandle;

    m_hHandle = ::CreateFile(csFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, CxFileAttribute::faNormal, NULL);
    /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), FALSE);

    bRes = ::SetFileTime(m_hHandle, &ftCreate, &ftAccess, &ftModified);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    utimbuf tbTimes = {0};

    //ctmCreate - n/a
    tbTimes.actime  = ctmAccess;
    tbTimes.modtime = ctmModified;

    int iRes = ::utime(csFilePath.c_str(), &tbTimes);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: text
*
*****************************************************************************/

//--------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bTextRead(
    const std::string_t &csFilePath,
    std::string_t       *psContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != psContent,          FALSE);

    CxFile       sfFile;
    std::string_t sRes;

    BOOL bRes = sfFile.bCreate(csFilePath, omBinRead, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    LONG liFileSize = sfFile.liGetSize();
    /*DEBUG*/xASSERT_RET(ppError != liFileSize, FALSE);

    xCHECK_DO(0L == liFileSize, (*psContent).clear(); return TRUE);

    sRes.resize(liFileSize);

    size_t uiReadLen = sfFile.uiRead((void *)&sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(sRes.size() == uiReadLen, FALSE);

    //out
    std::swap((*psContent), sRes);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bTextWrite(
    const std::string_t &csFilePath,
    const std::string_t &csContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// csContent - n/a

    //TODO: if csContent.empty()

    BOOL   bRes = FALSE;
    CxFile sfFile;
//BUG: line 1206
    bRes = sfFile.bCreate(csFilePath, omBinWrite, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    xCHECK_RET(true == csContent.empty(), TRUE);

    size_t uiWriteLen = sfFile.uiWrite((void *)&csContent.at(0), csContent.size());
    /*DEBUG*/xASSERT_RET(csContent.size() == uiWriteLen, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bTextRead(
    const std::string_t        &csFilePath,
    std::vector<std::string_t> *pvsContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pvsContent,            FALSE);

    BOOL                      bRes = FALSE;
    std::vector<std::string_t> vsRes;
    std::string_t              sFileContent;

    bRes = bTextRead(csFilePath, &sFileContent);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = CxString::bSplit(sFileContent, CxConst::xNL, &vsRes);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //out
    std::swap((*pvsContent), vsRes);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bTextWrite(
    const std::string_t              &csFilePath,
    const std::vector<std::string_t> &cvsContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cvsContent - n/a

    //TODO: if cvsContent.empty()

    BOOL         bRes = FALSE;
    std::string_t sFileContent;

    sFileContent = CxString::sJoin(cvsContent, CxConst::xNL);

    bRes = bTextWrite(csFilePath, sFileContent);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bTextRead(
    const std::string_t                   &csFilePath,
    const std::string_t                   &csSeparator,
    std::map<std::string_t, std::string_t> *pmsContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pmsContent,            FALSE);

    //if file empty
    xCHECK_DO(0L == liGetSize(csFilePath), (*pmsContent).clear(); return TRUE);

    BOOL bRes = FALSE;

    std::ifstream_t ifsStream(csFilePath.c_str());
    /*DEBUG*/xASSERT_RET(ifsStream,           FALSE);
    /*DEBUG*/xASSERT_RET(!ifsStream.fail(),   FALSE);
    /*DEBUG*/xASSERT_RET(ifsStream.good(),    FALSE);
    /*DEBUG*/xASSERT_RET(ifsStream.is_open(), FALSE);
    /*DEBUG*/xASSERT_RET(!ifsStream.eof(),    FALSE);

    std::map<std::string_t, std::string_t> msRes;
    std::string_t                         sLine;
    std::vector<std::string_t>            vsLine;

    for (size_t i = 0; !ifsStream.eof(); ++ i) {
        std::getline(ifsStream, sLine);

        sLine = CxString::sTrimRightChars(sLine, CxConst::xEOL);

        bRes = CxString::bSplit(sLine, csSeparator, &vsLine);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        msRes.insert( std::pair<std::string_t, std::string_t>(vsLine.at(0), vsLine.at(1)) );
    }

    //out
    (*pmsContent).swap(msRes);


#if xTODO
    BOOL                                 bRes = FALSE;
    std::map<std::string_t, std::string_t> msRes;
    std::vector<std::string_t>            vsRes;

    bRes = bTextRead(csFilePath, &vsRes);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    std::vector<std::string_t>::const_iterator it;
    for (it = vsRes.begin(); it != vsRes.end(); ++ it) {
        std::vector<std::string_t> vsLine;

        bRes = CxString::bSplit(vsRes.at(0), csSeparator, &vsLine);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        msRes.insert( std::pair<std::string_t, std::string_t>(vsLine.at(0), vsLine.at(1)) );
    }

    //out
    std::swap((*pmsContent), msRes);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bTextWrite(
    const std::string_t                         &csFilePath,
    const std::string_t                         &csSeparator,
    const std::map<std::string_t, std::string_t> &cmsContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),  FALSE);
    /*DEBUG*/xASSERT_RET(false == csSeparator.empty(), FALSE);
    /*DEBUG*/// cmsFile - n/a

    //TODO: if cmsFile.empty()

    BOOL   bRes = FALSE;
    CxFile stdFile;

    bRes = stdFile.bCreate(csFilePath, omWrite, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    std::map<std::string_t, std::string_t>::const_iterator it;
    for (it = cmsContent.begin(); it != cmsContent.end(); ++ it) {
        bRes = stdFile.bWriteLine((*it).first + csSeparator + (*it).second);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

#if xTODO
    BOOL         bRes = FALSE;
    std::string_t sRes;

    std::map<std::string_t, std::string_t>::const_iterator it;
    for (it = cmsContent.begin(); it != cmsContent.end(); ++ it) {
        sRes.append((*it).first);
        sRes.append(csSeparator);
        sRes.append((*it).second);
        sRes.append(CxConst::xNL);

        xCHECK_DO(it != cmsContent.end(), sRes.append(CxConst::xNL));
    }

    bRes = bTextWrite(csFilePath, sRes);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: bin
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bBinRead(
    const std::string_t &csFilePath,
    std::ustring       *pusContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pusContent,         FALSE);

    BOOL         bRes = FALSE;
    CxFile       sfFile;
    std::ustring usRes;

    bRes = sfFile.bCreate(csFilePath, omBinRead, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    LONG liFileSize = sfFile.liGetSize();
    /*DEBUG*/xASSERT_RET(ppError != liFileSize, FALSE);

    xCHECK_DO(0 == liFileSize, (*pusContent).clear(); return TRUE);

    usRes.resize(liFileSize);

    size_t uiReadLen = sfFile.uiRead((void *)&usRes.at(0), usRes.size());
    /*DEBUG*/xASSERT_RET(usRes.size() == uiReadLen, FALSE);

    //out
    std::swap((*pusContent), usRes);

    return TRUE;

}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bBinWrite(
    const std::string_t &csFilePath,
    const std::ustring &cusContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cusContent - n/a

    //TODO: if cusContent.empty()

    BOOL   bRes = FALSE;
    CxFile sfFile;

    bRes = sfFile.bCreate(csFilePath, omBinWrite, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    xCHECK_RET(true == cusContent.empty(), TRUE);

    size_t uiWriteLen = sfFile.uiWrite((void *)&cusContent.at(0), cusContent.size());
    /*DEBUG*/xASSERT_RET(cusContent.size() == uiWriteLen, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
int
CxFile::_iGetHandle(
    std::FILE *pfFile
)
{
    /*DEBUG*/xASSERT_RET(NULL != pfFile, - 1);

    int iRes = ::fileno(pfFile);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, - 1);

    return iRes;
}
//---------------------------------------------------------------------------
/*static*/
std::FILE *
CxFile::_pfGetHandle(
    int             iFileHandle,
    const EOpenMode omMode
)
{
    /*DEBUG*/

    std::FILE *pfRes = ::xTFDOPEN(iFileHandle, _sGetOpenMode(omMode).c_str());
    /*DEBUG*/xASSERT_RET(NULL != pfRes, NULL);

    return pfRes;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxFile::_sGetOpenMode(
    const EOpenMode comMode
)
{
    /*DEBUG*/// omMode - n/a

    std::string_t sRes;

    switch (comMode) {
        case omRead:                { sRes.assign( xT("r")   ); }   break;
        case omWrite:               { sRes.assign( xT("w")   ); }   break;
        case omAppend:              { sRes.assign( xT("a")   ); }   break;
        case omOpenReadWrite:       { sRes.assign( xT("r+")  ); }   break;
        case omCreateReadWrite:     { sRes.assign( xT("w+")  ); }   break;
        case omOpenReadAppend:      { sRes.assign( xT("a+")  ); }   break;

        case omBinRead:             { sRes.assign( xT("rb")  ); }   break;
        case omBinWrite:            { sRes.assign( xT("wb")  ); }   break;
        case omBinAppend:           { sRes.assign( xT("ab")  ); }   break;
        case omBinOpenReadWrite:    { sRes.assign( xT("rb+") ); }   break;
        case omBinCreateReadWrite:  { sRes.assign( xT("wb+") ); }   break;
        case omBinOpenReadAppend:   { sRes.assign( xT("ab+") ); }   break;

        default:                    { sRes.assign( xT("r")   ); }    break;
    }

    return sRes;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
