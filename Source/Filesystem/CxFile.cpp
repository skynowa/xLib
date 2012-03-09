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
bool
CxFile::bCreate(
    const std::tstring_t &csFilePath,
    const EOpenMode       comMode,
    const bool            cbIsUseBuffering
)
{
    /*DEBUG*/xASSERT_RET(false == bIsValid(),                       false);
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),               false);
    /*DEBUG*/xASSERT_RET(false != CxPath::bIsNameValid(csFilePath), false);
    /*DEBUG*/// comMode - n/a

    bool bRes = false;

    //create force dirs
    bRes = CxDir::bCreateForce( CxPath::sGetDir(csFilePath) );
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    //create, open file
    std::FILE *pFile = ::xTFOPEN(csFilePath.c_str(), _sGetOpenMode(comMode).c_str());
    /*DEBUG*/xASSERT_RET(NULL != pFile, false);

    _m_pFile     = pFile;
    _m_sFilePath = csFilePath;

    //buffering
    if (false == cbIsUseBuffering) {
        bRes = bSetVBuff(NULL, bmNo,   0);
    } else {
        bRes = bSetVBuff(NULL, bmFull, BUFSIZ);
    }
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFile::bReopen(
    const std::tstring_t &csFilePath,
    const EOpenMode       comMode,
    const bool            cbIsUseBuffering
)
{
    /*DEBUG*/// _m_pFile - n/a
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),               false);
    /*DEBUG*/xASSERT_RET(false != CxPath::bIsNameValid(csFilePath), false);
    /*DEBUG*/// omMode - n/a

    std::FILE *pFile = ::xTFREOPEN(csFilePath.c_str(), _sGetOpenMode(comMode).c_str(), _m_pFile);
    /*DEBUG*/xASSERT_RET(NULL != pFile, false);

    _m_pFile     = pFile;
    _m_sFilePath = csFilePath;

    //buffering
    bool bRes = false;

    if (false == cbIsUseBuffering) {
        bRes = bSetVBuff(NULL, bmNo,   0);
    } else {
        bRes = bSetVBuff(NULL, bmFull, BUFSIZ);
    }
    /*DEBUG*/xASSERT_RET(true == bRes, false);

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

    bool bRes = bClose();
    /*DEBUG*/xASSERT_RET(true == bRes, false);

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
    /*DEBUG*/xASSERT_RET(false != bIsValid(), NULL);

    return _m_pFile;
}
//---------------------------------------------------------------------------
std::tstring_t
CxFile::sGetPath() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(),              std::tstring_t());
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(),    std::tstring_t());
    /*DEBUG*/xASSERT_RET(false != bIsExists(_m_sFilePath), std::tstring_t());

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
    /*DEBUG*/xASSERT_RET(false != bIsValid(), 0);
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
    /*DEBUG*/xASSERT_RET(false != bIsValid(), 0);
    /*DEBUG*/xASSERT_RET(NULL  != pcvBuff,    0);

    size_t uiRes = std::fwrite(pcvBuff, 1, cuiCount, pGet());
    /*DEBUG*/xASSERT_RET(cuiCount == uiRes, uiRes);

    return uiRes;
}
//---------------------------------------------------------------------------
bool
CxFile::bRead(
    std::ustring_t *psBuff
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);
    /*DEBUG*/xASSERT_RET(NULL  != psBuff,     false);

    longlong_t llFileSize = llGetSize();
    /*DEBUG*/xASSERT_RET(ppError != llFileSize, false);

    (*psBuff).clear();
    (*psBuff).resize( static_cast<size_t>( llFileSize ) );
    xCHECK_RET(0LL == llFileSize, true);

    size_t uiRes = std::fread(&(*psBuff).at(0), sizeof(std::ustring_t::value_type), (*psBuff).size(), pGet());
    /*DEBUG*/xASSERT_RET((*psBuff).size() == uiRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFile::bWrite(
    const std::ustring_t &csBuff
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);
    /*DEBUG*///csBuff - n/a

    size_t uiRes = std::fwrite(&csBuff.at(0), sizeof(std::ustring_t::value_type), csBuff.size(), pGet());
    /*DEBUG*/xASSERT_RET(csBuff.size() == uiRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFile::bRead(
    std::tstring_t *psBuff
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);
    /*DEBUG*/xASSERT_RET(NULL  != psBuff,     false);

    longlong_t llFileSize = llGetSize();
    /*DEBUG*/xASSERT_RET(ppError != llFileSize, false);

    (*psBuff).clear();
    (*psBuff).resize( static_cast<size_t>( llFileSize) );
    xCHECK_RET(0LL == llFileSize, true);

    size_t uiRes =std::fread(&(*psBuff).at(0), sizeof(std::tstring_t::value_type), (*psBuff).size(), pGet());
    /*DEBUG*/xASSERT_RET((*psBuff).size() == uiRes, false);

    return true;
}
//---------------------------------------------------------------------------
int
CxFile::iWrite(
    const tchar_t *pcszFormat, ...
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), etError);
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
    const tchar_t *pcszFormat,
    va_list        vlArgs
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), etError);
    /*DEBUG*/xASSERT_RET(NULL  != pcszFormat, etError);
    /*DEBUG*/xASSERT_RET(NULL  != vlArgs,     etError);

    int iRes = std::xTVFPRINTF(pGet(), pcszFormat, vlArgs);
    /*DEBUG*/xASSERT_RET(- 1 < iRes, etError);

    return iRes;
}
//---------------------------------------------------------------------------
bool
CxFile::bReadLine(
    std::tstring_t *psStr,
    const size_t    cuiMaxCount
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(),  false);
    /*DEBUG*/xASSERT_RET(NULL  != psStr,       false);
    /*DEBUG*/xASSERT_RET(0     <  cuiMaxCount, false);

    #if xTEMP_DISABLED
        if ((*psStr).size() != cuiMaxCount) {
            (*psStr).resize(cuiMaxCount);
        }
        std::fill((*psStr).begin(), (*psStr).end(), std::tstring_t::value_type());
    #endif

    (*psStr).clear();
    (*psStr).resize(cuiMaxCount + 1);   //+ 1 for 0

    tchar_t *pszRes = std::xTFGETS(&(*psStr).at(0), (*psStr).size(), pGet());
    /*DEBUG*/xASSERT_RET(NULL != pszRes, false);

    (*psStr).erase( (*psStr).end() - 1 );   //erase last char - 0

    return true;
}
//---------------------------------------------------------------------------
bool
CxFile::bWriteLine(
    const std::tstring_t &csStr
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

    std::tstring_t sLine;

    sLine = csStr;
    sLine.append(CxConst::xEOL);

    size_t uiRes = uiWrite(&sLine.at(0), sLine.size());
    /*DEBUG*/xASSERT_RET(uiRes == sLine.size(), false);

    return true;
}
//---------------------------------------------------------------------------
//TODO: chReadChar
tchar_t
CxFile::chReadChar() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

    int iRes = std::xTFGETC(pGet());
    /*DEBUG*/xASSERT_RET(xTEOF <= iRes, static_cast<tchar_t>( etError ));

    return static_cast<tchar_t>( iRes );
}
//---------------------------------------------------------------------------
//TODO: bWriteChar
bool
CxFile::bWriteChar(
    const tchar_t ccChar
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

    int iRes = xTFPUTC(static_cast<int>( ccChar ), pGet());
    /*DEBUG*/xASSERT_RET(static_cast<int>( ccChar ) != xTEOF, false);
    /*DEBUG*/xASSERT_RET(static_cast<int>( ccChar ) == iRes,  false);

    return true;
}
//---------------------------------------------------------------------------
//TODO: bUngetChar
bool
CxFile::bUngetChar(
    const tchar_t ccChar
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

    int iRes = std::xTUNGETC(ccChar, pGet());
    /*DEBUG*/xASSERT_RET(iRes   != xTEOF,                      false);
    /*DEBUG*/xASSERT_RET(ccChar == static_cast<tchar_t>( iRes ), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFile::bClear() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

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
    const ELockingMode clmMode,
    const long_t       cliBytes
)
{
#if xOS_ENV_WIN
    int iRes = ::xLOCKING(_iGetHandle(pGet()), clmMode, cliBytes);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#elif xOS_ENV_UNIX
    int iRes = ::lockf   (_iGetHandle(pGet()), clmMode, static_cast<off_t>( cliBytes ));
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxFile::bSetPosition(
    const long_t           clOffset,
    const EPointerPosition cppPos
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

    int iRet = std::fseek(pGet(), clOffset, cppPos);
    /*DEBUG*/xASSERT_RET(- 1 != iRet, false);

    return true;
}
//---------------------------------------------------------------------------
long_t
CxFile::liGetPosition() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

    long_t liRes = std::ftell(pGet());
    /*DEBUG*/xASSERT_RET(- 1 != liRes, ppError);

    return liRes;
}
//---------------------------------------------------------------------------
bool
CxFile::bSetVBuff(
    char                 *pszBuff,
    const EBufferingMode  cbmMode,
    const size_t          cuiSize
) const
{
    /*DEBUG*/// pszBuff - n/a
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);
    /*DEBUG*/// cuiSize - n/a

    int iRes = std::setvbuf(pGet(), pszBuff, cbmMode, cuiSize);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);

    return true;
}
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

bool
CxFile::bSetMode(
    const ETranslationMode ctmMode
) const
{
    int iRes = ::setmode(_iGetHandle(pGet()), ctmMode);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);

    return true;
}

#endif
//---------------------------------------------------------------------------
//NOTE: https://www.securecoding.cert.org/confluence/display/seccode/FIO19-C.+Do+not+use+fseek()+and+ftell()+to+compute+the+size+of+a+file
longlong_t
CxFile::llGetSize() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), 0LL);

#if xDEPRECIATE
    bool bRes = bFlush();
    /*DEBUG*/xASSERT_RET(true == bRes, 0LL);

    xTSTAT_STRUCT stStat = {0};

    //TODO: fstat
    int iRes = ::xTSTAT(_m_sFilePath.c_str(), &stStat);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, 0LL);

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

#if xOS_ENV_WIN
    int iRes = static_cast<int>( ::xCHSIZE(_iGetHandle(pGet()), cllSize) );
    /*DEBUG*/xASSERT_RET(0 == iRes, false);
#elif xOS_ENV_UNIX
    int iRes = ::ftruncate(_iGetHandle(pGet()), static_cast<off_t>( cllSize ));
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    /*DEBUG*/xASSERT_RET(cllSize == llGetSize(), false);

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
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

    longlong_t llFileSize = llGetSize();
    /*DEBUG*/xASSERT_RET(- 1L != llFileSize, true);

    return (0LL == llFileSize);
}
//---------------------------------------------------------------------------
bool
CxFile::bIsEof() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

    return xINT_TO_BOOL( std::feof(pGet()) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
bool
CxFile::bIsError() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

    return xINT_TO_BOOL( std::ferror(pGet()) );
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
bool
CxFile::bErrorClear() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

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
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

    int iRes = std::fflush(pGet());
    /*DEBUG*/xASSERT_RET(xTEOF != iRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFile::bClose() {
    /*DEBUG*/// _m_pFile - n/a

    xCHECK_DO(false == bIsValid(), _m_pFile = NULL; return true);

    bool bRes = bErrorClear();
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    int iRes = std::fclose(pGet());
    /*DEBUG*/xASSERT_RET(xTEOF != iRes, false);

    _m_pFile = NULL;

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public, static
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bIsFile(
    const std::tstring_t &csFilePath
)
{
    bool bRes = false;

    CxFileAttribute::EAttribute atAttr = CxFileAttribute::atGet(csFilePath);
    xCHECK_RET(CxFileAttribute::faInvalid == atAttr, false);

#if xOS_ENV_WIN
    bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faDirectory);
    xCHECK_RET(true == bRes, false);

    bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faDevice);
    xCHECK_RET(true == bRes, false);

    bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faReparsePoint);
    xCHECK_RET(true == bRes, false);

    bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faOffline);
    xCHECK_RET(true == bRes, false);
#elif xOS_ENV_UNIX
    bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faRegularFile);
    xCHECK_RET(false == bRes, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bIsExists(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/// csFilePath - n/a
    xCHECK_RET(false == bIsFile(csFilePath), false);

    int iRes = ::xTACCESS(csFilePath.c_str(), amExistence);
    xCHECK_RET(- 1 == iRes && ENOENT == CxStdError::iGet(), false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxFile::sIsExists(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());

    std::tstring_t sRes;

    std::tstring_t sFileDir  = CxPath::sGetDir(csFilePath);
    std::tstring_t sFileName = CxPath::sGetName(csFilePath);
    std::tstring_t sFileExt  = CxPath::sGetExt(csFilePath);

    xCHECK_DO(false == sFileExt.empty(), sFileExt.insert(0, CxConst::xDOT));

    for (ulong_t ulExistsIndex = 1; ; ++ ulExistsIndex) {
        sRes = CxString::sFormat(xT("%s%s%s (%lu)%s"),
                                 sFileDir.c_str(), CxConst::xSLASH.c_str(), sFileName.c_str(), ulExistsIndex, sFileExt.c_str());

        xCHECK_DO(false == bIsExists(sRes), break);
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bAccess(
    const std::tstring_t &csFilePath,
    const EAccessMode     camMode
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*///iMode

    int iRes = ::xTACCESS(csFilePath.c_str(), camMode);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bChmod(
    const std::tstring_t  &csFilePath,
    const EPermissionMode  cpmMode
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*///iMode

#if xOS_ENV_WIN
    int iRes = ::xTCHMOD(csFilePath.c_str(), static_cast<int>( cpmMode ));
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#elif xOS_ENV_UNIX
    int iRes = ::xTCHMOD(csFilePath.c_str(), static_cast<mode_t>( cpmMode ));
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bClear(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);

    bool   bRes = false;
    CxFile sfFile;

    bRes = sfFile.bCreate(csFilePath, omWrite, true);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    bRes = sfFile.bClear();
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bDelete(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);

    xCHECK_RET(false == bIsExists(csFilePath), true);

    bool bRes = bChmod(csFilePath, pmWrite);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    int iRes = ::xTREMOVE(csFilePath.c_str());
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);

    /*DEBUG*/xASSERT_RET(false == bIsExists(csFilePath), false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bTryDelete(
    const std::tstring_t &csFilePath,
    const size_t          cuiAttempts,
    const ulong_t         culTimeoutMsec
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(0     <  cuiAttempts,        false);

    const size_t cuiMaxAttempts  = 100;  //MAGIC_NUMBER: cuiMaxAttempts
    const size_t cuiRealAttempts = (cuiMaxAttempts < cuiAttempts) ? cuiMaxAttempts : cuiAttempts;


    bool bIsDeleted = false;

    for (size_t i = 0; i < cuiRealAttempts; ++ i) {
        bool bRes = bDelete(csFilePath);
        xCHECK_DO(true == bRes, bIsDeleted = true; break);

        bRes = CxCurrentThread::bSleep(culTimeoutMsec);
        /*DEBUG*/xASSERT_RET(true == bRes, false);
    }

    return bIsDeleted;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bWipe(
    const std::tstring_t &csFilePath,
    const size_t          cuiPasses
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/// cuiPasses - n/a

    xCHECK_RET(false == bIsExists(csFilePath), true);

    bool bRes = false;

    {
        CxFile sfFile;

        //--------------------------------------------------
        //set normal file attributes
        bRes = CxFileAttribute::bSet(csFilePath, CxFileAttribute::faNormal);
        /*DEBUG*/xASSERT_RET(true == bRes, false);

        //--------------------------------------------------
        //open
        bRes = sfFile.bCreate(csFilePath, omBinWrite, true);
        /*DEBUG*/xASSERT_RET(true == bRes, false);

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
                    bRes = sfFile.bSetPosition(0L, ppBegin);
                    /*DEBUG*/xASSERT(true == bRes);

                    for (longlong_t i = 0LL; i < llSize; ++ i) {
                        size_t uiRes = std::fwrite(&chRand, 1, sizeof(chRand), sfFile.pGet());
                        /*DEBUG*/xASSERT_RET(sizeof(chRand) == uiRes, false);
                    }
                }

                //chChar1
                {
                    bRes = sfFile.bSetPosition(0L, ppBegin);
                    /*DEBUG*/xASSERT(true == bRes);

                    for (longlong_t i = 0LL; i < llSize; ++ i) {
                        size_t uiRes = std::fwrite(&chChar1, 1, sizeof(chChar1), sfFile.pGet());
                        /*DEBUG*/xASSERT_RET(sizeof(chChar1) == uiRes, false);
                    }
                }

                //chChar2
                {
                    bRes = sfFile.bSetPosition(0L, ppBegin);
                    /*DEBUG*/xASSERT(true == bRes);

                    for (longlong_t i = 0LL; i < llSize; ++ i) {
                        size_t uiRes = std::fwrite(&chChar2, 1, sizeof(chChar2), sfFile.pGet());
                        /*DEBUG*/xASSERT_RET(sizeof(chChar2) == uiRes, false);
                    }
                }
            }

            //--------------------------------------------------
            //truncate
            bRes = sfFile.bFlush();
            /*DEBUG*/xASSERT_RET(true == bRes, false);

            bRes = sfFile.bResize(0L);
            /*DEBUG*/xASSERT_RET(true == bRes, false);
        }
    }

    //--------------------------------------------------
    //reset filetime
    {
        const time_t ctmCreate   = 0;
        const time_t ctmAccess   = 0;
        const time_t ctmModified = 0;

        bRes = bSetTime(csFilePath, ctmCreate, ctmAccess, ctmModified);
        /*DEBUG*/xASSERT_RET(true == bRes, false);
    }

    //--------------------------------------------------
    //random file name
    std::tstring_t sRndFilePath;

    {
        std::tstring_t sRndFileName;

        sRndFileName = CxString::lexical_cast( CxDateTime().dtGetCurrent().ullToMilliseconds() );
        std::random_shuffle(sRndFileName.begin(), sRndFileName.end());

        sRndFilePath = CxPath::sGetDir(csFilePath) + CxConst::xSLASH + sRndFileName;

        bRes = bRename(csFilePath, sRndFilePath);
        /*DEBUG*/xASSERT_RET(true == bRes, false);
    }

    //--------------------------------------------------
    //delete
    bRes = bDelete(sRndFilePath);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bUnlink(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);

    int iRes = ::xTUNLINK(csFilePath.c_str());
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);

    return false;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bRename(
    const std::tstring_t &csOldFilePath,
    const std::tstring_t &csNewFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csOldFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csNewFilePath.empty(), false);

    int iRes = ::xTRENAME(csOldFilePath.c_str(), csNewFilePath.c_str());
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bMove(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(),  false);

    bool bRes = bRename(csFilePath, CxPath::sSlashAppend(csDirPath) + CxPath::sGetFullName(csFilePath));
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bCopy(
    const std::tstring_t &csFilePathFrom,
    const std::tstring_t &csFilePathTo,
    const bool            cbFailIfExists
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePathFrom.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csFilePathTo.empty(),   false);

    bool bIsCopyOk = true;

    //--------------------------------------------------
    //fail if exists
    xCHECK_RET(true == cbFailIfExists && true == bIsExists(csFilePathTo), false);
    //TODO: check filesize

    {
        //--------------------------------------------------
        //open files
        CxFile sfFrom;

        bool bRes = sfFrom.bCreate(csFilePathFrom, omBinRead, true);
        xCHECK_RET(false == bRes, false);

        CxFile sfTo;

        bRes = sfTo.bCreate(csFilePathTo, omBinWrite, true);
        xCHECK_RET(false == bRes, false);

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
/*static*/
longlong_t
CxFile::llGetSize(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    - 1LL);
    /*DEBUG*/xASSERT_RET(true  == bIsExists(csFilePath), - 1LL);

    CxFile sfFile;

    bool bRes = sfFile.bCreate(csFilePath, omRead, true);
    /*DEBUG*/xASSERT_RET(true == bRes, - 1LL);

    longlong_t liRes = sfFile.llGetSize();
    /*DEBUG*/xASSERT_RET(0LL <= liRes, - 1LL);

    return liRes;
}
//---------------------------------------------------------------------------
/*static*/
ulonglong_t
CxFile::ullGetLines(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    0LL);
    /*DEBUG*/xASSERT_RET(true  == bIsExists(csFilePath), 0LL);

    ulonglong_t      ullRes = 0LL;
    std::tifstream_t ifsStream(csFilePath.c_str(), std::ios::in);

    xCHECK_RET(!ifsStream || ifsStream.fail() || !ifsStream.good() || !ifsStream.is_open() || ifsStream.eof(), 0LL);

    tchar_t chChar;
    for (ullRes = 0LL; ifsStream.get(chChar); ) {
        xCHECK_DO(xT('\n') == chChar, ++ ullRes);
    }

    return ullRes;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bGetTime(
    const std::tstring_t &csFilePath,
    time_t               *ptmCreate,
    time_t               *ptmAccess,
    time_t               *ptmModified
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/// pftCreate   - n/a
    /*DEBUG*/// pftAccess   - n/a
    /*DEBUG*/// pftModified - n/a

#if xOS_ENV_WIN
    FILETIME ftCreate   = {0};
    FILETIME ftAccess   = {0};
    FILETIME ftModified = {0};

    CxFileHandle m_hHandle;

    m_hHandle = ::CreateFile(csFilePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, CxFileAttribute::faNormal, NULL);
    /*DEBUG*/xASSERT_RET(false != m_hHandle.bIsValid(), false);

    BOOL blRes = ::GetFileTime(m_hHandle.hGet(), &ftCreate, &ftAccess, &ftModified);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    xCHECK_DO(NULL != ptmCreate,   *ptmCreate   = CxDateTime::tmFileTimeToUnixTime(ftCreate));
    xCHECK_DO(NULL != ptmAccess,   *ptmAccess   = CxDateTime::tmFileTimeToUnixTime(ftAccess));
    xCHECK_DO(NULL != ptmModified, *ptmModified = CxDateTime::tmFileTimeToUnixTime(ftModified));
#elif xOS_ENV_UNIX
    xTSTAT_STRUCT stInfo = {0};

    int iRes = ::xTSTAT(csFilePath.c_str(), &stInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);

    //ctmCreate - n/a
    xCHECK_DO(NULL != ptmAccess,   *ptmAccess   = stInfo.st_atime);
    xCHECK_DO(NULL != ptmModified, *ptmModified = stInfo.st_mtime);
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
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/// ctmCreate   - n/a
    /*DEBUG*/// ctmAccess   - n/a
    /*DEBUG*/// ctmModified - n/a

#if xOS_ENV_WIN
    bool     bRes     = false;

    FILETIME ftCreate = {0};
    bRes = CxDateTime::bUnixTimeToFileTime(ctmCreate, &ftCreate);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    FILETIME ftAccess = {0};
    bRes = CxDateTime::bUnixTimeToFileTime(ctmAccess, &ftAccess);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    FILETIME ftModified = {0};
    bRes = CxDateTime::bUnixTimeToFileTime(ctmModified, &ftModified);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    CxFileHandle m_hHandle;

    m_hHandle = ::CreateFile(csFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, CxFileAttribute::faNormal, NULL);
    /*DEBUG*/xASSERT_RET(false != m_hHandle.bIsValid(), false);

    BOOL blRes = ::SetFileTime(m_hHandle.hGet(), &ftCreate, &ftAccess, &ftModified);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    utimbuf tbTimes = {0};

    //ctmCreate - n/a
    tbTimes.actime  = ctmAccess;
    tbTimes.modtime = ctmModified;

    int iRes = ::utime(csFilePath.c_str(), &tbTimes);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: text
*
*****************************************************************************/

//--------------------------------------------------------------------------
/*static*/
bool
CxFile::bTextRead(
    const std::tstring_t &csFilePath,
    std::tstring_t       *psContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != psContent,          false);

    CxFile         sfFile;
    std::tstring_t sRes;

    bool bRes = sfFile.bCreate(csFilePath, omBinRead, true);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    longlong_t llFileSize = sfFile.llGetSize();
    /*DEBUG*/xASSERT_RET(ppError != llFileSize, false);

    xCHECK_DO(0LL == llFileSize, (*psContent).clear(); return true);

    sRes.resize( static_cast<size_t>( llFileSize) );

    size_t uiReadLen = sfFile.uiRead((void *)&sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(sRes.size() == uiReadLen, false);

    //out
    std::swap((*psContent), sRes);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bTextWrite(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/// csContent - n/a

    //TODO: if csContent.empty()

    bool   bRes = false;
    CxFile sfFile;

    bRes = sfFile.bCreate(csFilePath, omBinWrite, true);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    xCHECK_RET(true == csContent.empty(), true);

    size_t uiWriteLen = sfFile.uiWrite((void *)&csContent.at(0), csContent.size());
    /*DEBUG*/xASSERT_RET(csContent.size() == uiWriteLen, false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bTextRead(
    const std::tstring_t        &csFilePath,
    std::vector<std::tstring_t> *pvsContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    false);
    /*DEBUG*/xASSERT_RET(true  == bIsExists(csFilePath), false);
    /*DEBUG*/xASSERT_RET(NULL  != pvsContent,            false);

    bool                        bRes = false;
    std::vector<std::tstring_t> vsRes;
    std::tstring_t              sFileContent;

    bRes = bTextRead(csFilePath, &sFileContent);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    bRes = CxString::bSplit(sFileContent, CxConst::xNL, &vsRes);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    //out
    std::swap((*pvsContent), vsRes);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bTextWrite(
    const std::tstring_t              &csFilePath,
    const std::vector<std::tstring_t> &cvsContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/// cvsContent - n/a

    //TODO: if cvsContent.empty()

    bool           bRes = false;
    std::tstring_t sFileContent;

    sFileContent = CxString::sJoin(cvsContent, CxConst::xNL);

    bRes = bTextWrite(csFilePath, sFileContent);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    return true;
}
//--------------------------------------------------------------------------
/*static*/
bool
CxFile::bTextRead(
    const std::tstring_t                     &csFilePath,
    const std::tstring_t                     &csSeparator,
    std::map<std::tstring_t, std::tstring_t> *pmsContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    false);
    /*DEBUG*/xASSERT_RET(true  == bIsExists(csFilePath), false);
    /*DEBUG*/xASSERT_RET(NULL  != pmsContent,            false);

    //if file empty
    xCHECK_DO(0L == llGetSize(csFilePath), (*pmsContent).clear(); return true);

    bool bRes = false;

    std::tifstream_t ifsStream(csFilePath.c_str());
    /*DEBUG*/xASSERT_RET(ifsStream,           false);
    /*DEBUG*/xASSERT_RET(!ifsStream.fail(),   false);
    /*DEBUG*/xASSERT_RET(ifsStream.good(),    false);
    /*DEBUG*/xASSERT_RET(ifsStream.is_open(), false);
    /*DEBUG*/xASSERT_RET(!ifsStream.eof(),    false);

    std::map<std::tstring_t, std::tstring_t> msRes;
    std::tstring_t                           sLine;
    std::vector<std::tstring_t>              vsLine;

    for (size_t i = 0; !ifsStream.eof(); ++ i) {
        std::getline(ifsStream, sLine);

        sLine = CxString::sTrimRightChars(sLine, CxConst::xEOL);

        bRes = CxString::bSplit(sLine, csSeparator, &vsLine);
        /*DEBUG*/xASSERT_RET(true == bRes, false);

        msRes.insert( std::pair<std::tstring_t, std::tstring_t>(vsLine.at(0), vsLine.at(1)) );
    }

    //out
    (*pmsContent).swap(msRes);


#if xTODO
    bool                                     bRes = false;
    std::map<std::tstring_t, std::tstring_t> msRes;
    std::vector<std::tstring_t>              vsRes;

    bRes = bTextRead(csFilePath, &vsRes);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    std::vector<std::tstring_t>::_const_iterator it;
    for (it = vsRes.begin(); it != vsRes.end(); ++ it) {
        std::vector<std::tstring_t> vsLine;

        bRes = CxString::bSplit(vsRes.at(0), csSeparator, &vsLine);
        /*DEBUG*/xASSERT_RET(true == bRes, false);

        msRes.insert( std::pair<std::tstring_t, std::tstring_t>(vsLine.at(0), vsLine.at(1)) );
    }

    //out
    std::swap((*pmsContent), msRes);
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bTextWrite(
    const std::tstring_t                           &csFilePath,
    const std::tstring_t                           &csSeparator,
    const std::map<std::tstring_t, std::tstring_t> &cmsContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),  false);
    /*DEBUG*/xASSERT_RET(false == csSeparator.empty(), false);
    /*DEBUG*/// cmsFile - n/a

    //TODO: if cmsFile.empty()

    bool   bRes = false;
    CxFile stdFile;

    bRes = stdFile.bCreate(csFilePath, omWrite, true);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    typedef std::map<std::tstring_t, std::tstring_t> TContent;

    xFOREACH_CONST(TContent, it, cmsContent) {
        bRes = stdFile.bWriteLine((*it).first + csSeparator + (*it).second);
        /*DEBUG*/xASSERT_RET(true == bRes, false);
    }

#if xTODO
    bool           bRes = false;
    std::tstring_t sRes;

    std::map<std::tstring_t, std::tstring_t>::_const_iterator it;
    for (it = cmsContent.begin(); it != cmsContent.end(); ++ it) {
        sRes.append((*it).first);
        sRes.append(csSeparator);
        sRes.append((*it).second);
        sRes.append(CxConst::xNL);

        xCHECK_DO(it != cmsContent.end(), sRes.append(CxConst::xNL));
    }

    bRes = bTextWrite(csFilePath, sRes);
    /*DEBUG*/xASSERT_RET(true == bRes, false);
#endif

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: bin
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bBinRead(
    const std::tstring_t &csFilePath,
    std::ustring_t       *pusContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != pusContent,         false);

    bool           bRes = false;
    CxFile         sfFile;
    std::ustring_t usRes;

    bRes = sfFile.bCreate(csFilePath, omBinRead, true);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    longlong_t llFileSize = sfFile.llGetSize();
    /*DEBUG*/xASSERT_RET(ppError != llFileSize, false);

    xCHECK_DO(0LL == llFileSize, (*pusContent).clear(); return true);

    usRes.resize( static_cast<size_t>( llFileSize ) );

    size_t uiReadLen = sfFile.uiRead((void *)&usRes.at(0), usRes.size());
    /*DEBUG*/xASSERT_RET(usRes.size() == uiReadLen, false);

    //out
    std::swap((*pusContent), usRes);

    return true;

}
//---------------------------------------------------------------------------
/*static*/
bool
CxFile::bBinWrite(
    const std::tstring_t &csFilePath,
    const std::ustring_t &cusContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/// cusContent - n/a

    //TODO: if cusContent.empty()

    bool   bRes = false;
    CxFile sfFile;

    bRes = sfFile.bCreate(csFilePath, omBinWrite, true);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    xCHECK_RET(true == cusContent.empty(), true);

    size_t uiWriteLen = sfFile.uiWrite((void *)&cusContent.at(0), cusContent.size());
    /*DEBUG*/xASSERT_RET(cusContent.size() == uiWriteLen, false);

    return true;
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

    int iRes = /*::*/fileno(pfFile);
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
std::tstring_t
CxFile::_sGetOpenMode(
    const EOpenMode comMode
)
{
    /*DEBUG*/// omMode - n/a

    std::tstring_t sRes;

    switch (comMode) {
        case omRead:                { sRes = xT("r");   }   break;
        case omWrite:               { sRes = xT("w");   }   break;
        case omAppend:              { sRes = xT("a");   }   break;
        case omOpenReadWrite:       { sRes = xT("r+");  }   break;
        case omCreateReadWrite:     { sRes = xT("w+");  }   break;
        case omOpenReadAppend:      { sRes = xT("a+");  }   break;

        case omBinRead:             { sRes = xT("rb");  }   break;
        case omBinWrite:            { sRes = xT("wb");  }   break;
        case omBinAppend:           { sRes = xT("ab");  }   break;
        case omBinOpenReadWrite:    { sRes = xT("rb+"); }   break;
        case omBinCreateReadWrite:  { sRes = xT("wb+"); }   break;
        case omBinOpenReadAppend:   { sRes = xT("ab+"); }   break;

        default:                    { sRes = xT("r");   }    break;
    }

    return sRes;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
