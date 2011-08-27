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
#include <xLib/Filesystem/CxVolume.h>
#include <xLib/Crypt/CxCrc32.h>
#include <xLib/Crypt/CxRandom.h>
#include <xLib/Sync/CxThread.h>
#include <xLib/Gui/Dialogs/CxMsgBoxT.h>


/****************************************************************************
*    public: constructors, destructor
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxFile::CxFile() :
    _m_bRes     (FALSE),
    _m_pFile    (NULL),
    _m_sFilePath()
{
}
//---------------------------------------------------------------------------
CxFile::~CxFile() {
    /*DEBUG*/// n/a

    _m_bRes = bClose();
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: open, get
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxFile::bOpen(
    const std::tstring &csFilePath,
    const EOpenMode     comMode,
    const BOOL          cbIsUseBuffering
)
{
    /*DEBUG*/xASSERT_RET(FALSE == bIsValid(),                       FALSE);
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != CxPath::bIsNameValid(csFilePath), FALSE);
    /*DEBUG*/// comMode - n/a

    FILE *pFile = _tfopen(csFilePath.c_str(), _sGetOpenMode(comMode).c_str());
    /*DEBUG*/xASSERT_RET(NULL != pFile, FALSE);

    _m_pFile     = pFile;
    _m_sFilePath = csFilePath;

    //buffering
    if (FALSE == cbIsUseBuffering) {
        _m_bRes = bSetVBuff(NULL, bmNo, 0);
    } else {
        _m_bRes = bSetVBuff(NULL, bmFull, BUFSIZ);
    }
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bReopen(
    const std::tstring &csFilePath,
    const EOpenMode     comMode,
    const BOOL          cbIsUseBuffering
)
{
    /*DEBUG*/// _m_pFile - n/a
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != CxPath::bIsNameValid(csFilePath), FALSE);
    /*DEBUG*/// omMode - n/a

    FILE *pFile = _tfreopen(csFilePath.c_str(), _sGetOpenMode(comMode).c_str(), _m_pFile);
    /*DEBUG*/xASSERT_RET(NULL != pFile, FALSE);

    _m_pFile     = pFile;
    _m_sFilePath = csFilePath;

    //buffering
    if (FALSE == cbIsUseBuffering) {
        _m_bRes = bSetVBuff(NULL, bmNo, 0);
    } else {
        _m_bRes = bSetVBuff(NULL, bmFull, BUFSIZ);
    }
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bOpen(
    FILE *pflFile
)
{
    /*DEBUG*/// _m_pFile - n/a
    /*DEBUG*/// pflFile  - n/a

    _m_bRes = bClose();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_pFile     = pflFile;
    _m_sFilePath = CxConst::xSTR_EMPTY;

    return TRUE;
}
//---------------------------------------------------------------------------
FILE *
CxFile::pGet() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), NULL);

    return _m_pFile;
}
//---------------------------------------------------------------------------
std::tstring
CxFile::sGetPath() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),              std::tstring());
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(),    std::tstring());
    /*DEBUG*/xASSERT_RET(FALSE != bIsExists(_m_sFilePath), std::tstring());

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
    LPVOID       pvBuff,
    const size_t cuiCount
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0);
    /*DEBUG*/xASSERT_RET(NULL  != pvBuff,     0);

    size_t uiRes = 0;

    uiRes = fread(pvBuff, 1, cuiCount, pGet());
    /*DEBUG*/xASSERT_RET(cuiCount >= uiRes, uiRes);

    return uiRes;
}
//---------------------------------------------------------------------------
size_t
CxFile::uiWrite(
    const LPVOID pcvBuff,
    const size_t cuiCount
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0);
    /*DEBUG*/xASSERT_RET(NULL  != pcvBuff,    0);

    size_t uiRes = 0;

    uiRes = fwrite(pcvBuff, 1, cuiCount, pGet());
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

    size_t uiRes      = 0;
    LONG   liFileSize = 0;

    liFileSize = liGetSize();
    /*DEBUG*/xASSERT_RET(ppError != liFileSize, FALSE);

    (*psBuff).clear();
    (*psBuff).resize(liFileSize);
    xCHECK_RET(0 == liFileSize, TRUE);

    uiRes = fread(&(*psBuff).at(0), sizeof(std::ustring::value_type), (*psBuff).size(), pGet());
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

    size_t uiRes = 0;

    uiRes = fwrite(&csBuff.at(0), sizeof(std::ustring::value_type), csBuff.size(), pGet());
    /*DEBUG*/xASSERT_RET(csBuff.size() == uiRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bRead(
    std::tstring *psBuff
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != psBuff,     FALSE);

    size_t uiRes      = 0;
    LONG   liFileSize = 0;

    liFileSize = liGetSize();
    /*DEBUG*/xASSERT_RET(ppError != liFileSize, FALSE);

    (*psBuff).clear();
    (*psBuff).resize(liFileSize);
    xCHECK_RET(0 == liFileSize, TRUE);

    uiRes = fread(&(*psBuff).at(0), sizeof(std::tstring::value_type), (*psBuff).size(), pGet());
    /*DEBUG*/xASSERT_RET((*psBuff).size() == uiRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
INT
CxFile::iWrite(
    LPCTSTR pcszFormat, ...
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), etError);
    /*DEBUG*/xASSERT_RET(NULL  != pcszFormat, etError);

    INT iRes = etError;

    va_list vlArgs;
    xVA_START(vlArgs, pcszFormat);

    iRes = _vftprintf(pGet(), pcszFormat, vlArgs);
    /*DEBUG*/xASSERT_RET(etError < iRes, etError);

    xVA_END(vlArgs);

    return iRes;
}
//---------------------------------------------------------------------------
INT
CxFile::iWriteV(
    LPCTSTR pcszFormat,
    va_list vlArgs
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), etError);
    /*DEBUG*/xASSERT_RET(NULL  != pcszFormat, etError);
    /*DEBUG*/xASSERT_RET(NULL  != vlArgs,     etError);

    INT iRes = etError;

    iRes = _vftprintf(pGet(), pcszFormat, vlArgs);
    /*DEBUG*/xASSERT_RET(etError < iRes, etError);

    return iRes;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bReadLine(
    std::tstring *psStr,
    const size_t  cuiMaxCount
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != psStr,      FALSE);
    /*DEBUG*/xASSERT_RET(0     < cuiMaxCount, FALSE);

    LPTSTR pszRes = NULL;

    #if xTEMP_DISABLED
        if ((*psStr).size() != cuiMaxCount) {
            (*psStr).resize(cuiMaxCount);
        }
        std::fill((*psStr).begin(), (*psStr).end(), std::tstring::value_type());
    #endif

    (*psStr).clear();
    (*psStr).resize(cuiMaxCount + 1);   //+ 1 for 0

    pszRes = _fgetts(&(*psStr).at(0), (*psStr).size(), pGet());
    /*DEBUG*/xASSERT_RET(NULL != pszRes, FALSE);

    (*psStr).erase( (*psStr).end() - 1 );   //erase last char - 0

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bWriteLine(
    const std::tstring &csStr
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    std::tstring sLine;

    sLine.assign(csStr);
    sLine.append(CxConst::xEOL);

    size_t uiRes = uiWrite(&sLine.at(0), sLine.size());
    /*DEBUG*/xASSERT_RET(uiRes == sLine.size(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: chReadChar
TCHAR
CxFile::chReadChar() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    INT iRes = etError;

    iRes = _gettc(pGet());
    /*DEBUG*/xASSERT_RET(EOF <= iRes, static_cast<TCHAR>(etError));

    return static_cast<TCHAR>(iRes);
}
//---------------------------------------------------------------------------
//TODO: bWriteChar
BOOL
CxFile::bWriteChar(
    const TCHAR ccChar
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    INT iRes = etError;

    iRes = _fputtc(static_cast<INT>(ccChar), pGet());
    /*DEBUG*/xASSERT_RET(static_cast<INT>(ccChar) != etError, FALSE);
    /*DEBUG*/xASSERT_RET(static_cast<INT>(ccChar) == iRes,    FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bUngetChar
BOOL
CxFile::bUngetChar(
    const TCHAR ccChar
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    INT iRes = etError;

    iRes = _ungettc(ccChar, pGet());
    /*DEBUG*/xASSERT_RET(iRes   != etError,                  FALSE);
    /*DEBUG*/xASSERT_RET(ccChar == static_cast<TCHAR>(iRes), FALSE);

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
    INT iRes = etError;

#if defined(xOS_WIN)
	#if defined(xCOMPILER_CODEGEAR)
		#define xLocking locking
	#else
		#define xLocking _locking
	#endif

	iRes = xLocking(_iGetHandle(pGet()), clmMode, cliBytes);
	/*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
#elif defined(xOS_LINUX)
    iRes = lockf(_iGetHandle(pGet()), clmMode, static_cast<off_t>( cliBytes ));
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
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

    INT iRet = ppError;

    iRet = fseek(pGet(), clOffset, cppPos);
    /*DEBUG*/xASSERT_RET(0 == iRet, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
LONG
CxFile::liGetPosition() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    LONG liRes = ppError;

    liRes = ftell(pGet());
    /*DEBUG*/xASSERT_RET(ppError != liRes, ppError);

    return liRes;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bSetVBuff(
    LPSTR                pszBuff,
    const EBufferingMode cbmMode,
    const size_t         cuiSize
) const
{
    /*DEBUG*/// pszBuff - n/a
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/// cuiSize - n/a

    INT iRes = etError;

    iRes = setvbuf(pGet(), pszBuff, cbmMode, cuiSize);
    /*DEBUG*/xASSERT_RET(0 == iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
BOOL
CxFile::bSetMode(
    const ETranslationMode ctmMode
) const
{
    INT iRes = etError;

    #if defined(xCOMPILER_MINGW32) || defined(xCOMPILER_MS)
        iRes = setmode(_iGetHandle(pGet()), ctmMode);
        /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
    #elif defined(xCOMPILER_CODEGEAR)
        iRes = setmode(_iGetHandle(pGet()), ctmMode);
        /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
    #endif

    return TRUE;
}
#endif
//---------------------------------------------------------------------------
//NOTE: https://www.securecoding.cert.org/confluence/display/seccode/FIO19-C.+Do+not+use+fseek()+and+ftell()+to+compute+the+size+of+a+file
LONG
CxFile::liGetSize() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), ppError);

    LONG liStreamSize    = ppError;
    LONG liCurrStreamPos = ppError;

    //Get current position
    liCurrStreamPos = liGetPosition();

    //seek to the end of file
    xCHECK_RET(FALSE == bSetPosition(0, ppEnd), ppError);

    liStreamSize = liGetPosition();

    //Get back to the stored position
    xCHECK_RET(FALSE == bSetPosition(liCurrStreamPos, ppBegin), ppError);

    return liStreamSize;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bResize(
    const LONG cliSize
) const
{
    /*DEBUG*/// n/a

    INT iRes = etError;

#if defined(xOS_WIN)
    #if defined(xCOMPILER_MINGW32) || defined(xCOMPILER_MS)
        iRes = chsize(_iGetHandle(pGet()), cliSize);
        /*DEBUG*/xASSERT_RET(iRes != etError, FALSE);
    #elif defined(xCOMPILER_CODEGEAR)
        iRes = chsize(_iGetHandle(pGet()), cliSize);
        /*DEBUG*/xASSERT_RET(iRes != etError, FALSE);
    #endif
#elif defined(xOS_LINUX)
    iRes = ftruncate(_iGetHandle(pGet()), static_cast<off_t>( cliSize ));
    /*DEBUG*/xASSERT_RET(iRes != etError, FALSE);
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
    /*DEBUG*/xASSERT_RET(etError != liFileSize, TRUE);

    return static_cast<BOOL>( 0L == liFileSize);
}
//---------------------------------------------------------------------------
BOOL
CxFile::bIsEof() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    _m_bRes = static_cast<BOOL>( feof(pGet()) );
    /*DEBUG*/// n/a

    return _m_bRes;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bIsError() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    _m_bRes = static_cast<BOOL>( ferror(pGet()) );
    /*DEBUG*/// n/a

    return _m_bRes;
}
//---------------------------------------------------------------------------

BOOL
CxFile::bErrorClear() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    clearerr(pGet());
    /*DEBUG*/// n/a

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

    INT iRes = etError;

    iRes = fflush(pGet());
    /*DEBUG*/xASSERT_RET(0 == iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFile::bClose() {
    /*DEBUG*/// _m_pFile - n/a

    if (FALSE != bIsValid()) {
        _m_bRes = bErrorClear();
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        INT iRes = fclose(pGet());
        /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
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
    const std::tstring &csFilePath
)
{
    /*DEBUG*/// csFilePath - n/a

    BOOL bRes = FALSE;

    CxFileAttribute::EAttribute atAttr = CxFileAttribute::atGet(csFilePath);
    xCHECK_RET(CxFileAttribute::faInvalid == atAttr, FALSE);

#if defined(xOS_WIN)
    bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faDirectory);
    xCHECK_RET(TRUE == bRes, FALSE);

    bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faDevice);
    xCHECK_RET(TRUE == bRes, FALSE);

    bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faReparsePoint);
    xCHECK_RET(TRUE == bRes, FALSE);

    bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faOffline);
    xCHECK_RET(TRUE == bRes, FALSE);
#elif defined(xOS_LINUX)
    bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faRegularFile);
    xCHECK_RET(FALSE == bRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bIsExists(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/// csFilePath - n/a
    xCHECK_RET(FALSE == bIsFile(csFilePath), FALSE);

    INT iRes       = etError;
    INT iLastError = 0;

    iRes       = _taccess(csFilePath.c_str(), amExistence);
    iLastError = errno;
    xCHECK_RET((etError == iRes) && (ENOENT == iLastError), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxFile::sIsExists(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());

    std::tstring sRes;
    sRes.assign(csFilePath);

    //--static INT s_iFileExistsIndex = 0;
    std::tstring    sFileDir           = CxPath::sGetDir(sRes);
    std::tstring    sFileName          = CxPath::sGetName(sRes);
    std::tstring    sFileExt           = CxPath::sGetExt(sRes);

    for (INT s_iFileExistsIndex = 1; TRUE == bIsExists(sRes); ++ s_iFileExistsIndex) {
        sRes = sFileDir                                   + CxConst::xSLASH     +
               sFileName                                  + xT(" (")                +
               CxString::lexical_cast(s_iFileExistsIndex) + xT(")") + CxConst::xDOT +
               sFileExt;
    }

    //--s_iFileExistsIndex = 0;

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bAccess(
    const std::tstring &csFilePath,
    const EAccessMode   camMode
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*///iMode

    INT iRes = etError;

    iRes = _taccess(csFilePath.c_str(), camMode);
    /*DEBUG*/xASSERT_RET(iRes != etError, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bChmod(
    const std::tstring    &csFilePath,
    const EPermissionMode  cpmMode
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*///iMode

    INT iRes = etError;

#if defined(xOS_WIN)
    iRes = _tchmod(csFilePath.c_str(), static_cast<INT>( cpmMode ));
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
#elif defined(xOS_LINUX)
    iRes = _tchmod(csFilePath.c_str(), static_cast<mode_t>( cpmMode ));
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bClear(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    BOOL   bRes = FALSE;
    CxFile sfFile;

    bRes = sfFile.bOpen(csFilePath, omWrite, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = sfFile.bClear();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bDelete(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    xCHECK_RET(FALSE == bIsExists(csFilePath), TRUE);

    BOOL bRes = FALSE;
    INT  iRes = etError;

    bRes = bChmod(csFilePath, pmWrite);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    iRes = _tremove(csFilePath.c_str());
    /*DEBUG*/xASSERT_RET(0 == iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bTryDelete(
    const std::tstring &csFilePath,
    const size_t        cuiAttempts,
    const ULONG         culTimeoutMsec
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(0     <  cuiAttempts,        FALSE);

    const size_t cuiMaxAttempts  = 100;  //MAGIC_NUMBER: cuiMaxAttempts
    const size_t cuiRealAttempts = (cuiMaxAttempts < cuiAttempts) ? cuiMaxAttempts : cuiAttempts;

    BOOL bRes       = FALSE;
    BOOL bIsDeleted = FALSE;

    for (size_t i = 0; i < cuiRealAttempts; ++ i) {
        bRes = bDelete(csFilePath);
        xCHECK_DO(TRUE == bRes, bIsDeleted = TRUE; break);

        bRes = CxThread::bSleep(culTimeoutMsec);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    return bIsDeleted;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bWipe(
    const std::tstring &csFilePath,
    const size_t        cuiPasses
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cuiPasses - n/a

    xCHECK_RET(FALSE == bIsExists(csFilePath), TRUE);

    BOOL bRes = FALSE;

    {
        CxFile sfFile;
        LONG   liSize = 0;

        //--------------------------------------------------
        //set normal file attributes
        bRes = CxFileAttribute::bSet(csFilePath, CxFileAttribute::faNormal);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        //--------------------------------------------------
        //open
        bRes = sfFile.bOpen(csFilePath, omBinWrite, TRUE);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        liSize = sfFile.liGetSize();
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
                    bRes = sfFile.bSetPosition(0, ppBegin);
                    /*DEBUG*/xASSERT(FALSE != bRes);

                    for (LONG i = 0; i < liSize; ++ i) {
                        size_t uiRes = fwrite(&chRand, 1, sizeof(chRand), sfFile.pGet());
                        /*DEBUG*/xASSERT_RET(sizeof(chRand) == uiRes, FALSE);
                    }
                }

                //chChar1
                {
                    bRes = sfFile.bSetPosition(0, ppBegin);
                    /*DEBUG*/xASSERT(FALSE != bRes);

                    for (LONG i = 0; i < liSize; ++ i) {
                        size_t uiRes = fwrite(&chChar1, 1, sizeof(chChar1), sfFile.pGet());
                        /*DEBUG*/xASSERT_RET(sizeof(chChar1) == uiRes, FALSE);
                    }
                }

                //chChar2
                {
                    bRes = sfFile.bSetPosition(0, ppBegin);
                    /*DEBUG*/xASSERT(FALSE != bRes);

                    for (LONG i = 0; i < liSize; ++ i) {
                        size_t uiRes = fwrite(&chChar2, 1, sizeof(chChar2), sfFile.pGet());
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
    const time_t ctmCreate   = 0;
    const time_t ctmAccess   = 0;
    const time_t ctmModified = 0;

    bRes = bSetTime(csFilePath, ctmCreate, ctmAccess, ctmModified);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //--------------------------------------------------
    //random file name
    std::tstring sRndFileName;
    std::tstring sRndFilePath;

    sRndFileName = CxString::lexical_cast( CxDateTime().dtGetCurrent().ullToMilliseconds() );
    std::random_shuffle(sRndFileName.begin(), sRndFileName.end());

    sRndFilePath = CxPath::sGetDir(csFilePath) + CxConst::xSLASH + sRndFileName;

    bRes = bRename(csFilePath, sRndFilePath);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

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
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    INT iRes = etError;

    iRes = _tunlink(csFilePath.c_str());
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);

    return FALSE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bRename(
    const std::tstring &csOldFilePath,
    const std::tstring &csNewFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csOldFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csNewFilePath.empty(), FALSE);

    INT iRes = etError;

    iRes = _trename(csOldFilePath.c_str(), csNewFilePath.c_str());
    /*DEBUG*/xASSERT_RET(0 == iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bMove(
    const std::tstring &csFilePath,
    const std::tstring &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(),  FALSE);

    BOOL bRes = FALSE;

    bRes = bRename(csFilePath, CxPath::sSlashAppend(csDirPath) + CxPath::sGetFullName(csFilePath));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bCopy(
    const std::tstring &csFilePathFrom,
    const std::tstring &csFilePathTo,
    const BOOL          cbFailIfExists
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePathFrom.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csFilePathTo.empty(),   FALSE);

    BOOL bRes      = FALSE;
    BOOL bIsCopyOk = TRUE;

    //--------------------------------------------------
    //fail if exists
    xCHECK_RET(TRUE == cbFailIfExists && TRUE == bIsExists(csFilePathTo), FALSE);
    //TODO: check filesize

    {
        //--------------------------------------------------
        //open files
        CxFile sfFrom;

        bRes = sfFrom.bOpen(csFilePathFrom, omBinRead, TRUE);
        xCHECK_RET(FALSE == bRes, FALSE);

        CxFile sfTo;

        bRes = sfTo.bOpen(csFilePathTo, omBinWrite, TRUE);
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
    xCHECK_DO(bIsCopyOk == FALSE, bDelete(csFilePathTo); return FALSE);

    //--------------------------------------------------
    //test for size, maybe CRC
    xCHECK_DO(liGetSize(csFilePathFrom) != liGetSize(csFilePathTo), bDelete(csFilePathTo); return FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
/*static*/
LONG
CxFile::liGetSize(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    - 1L);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), - 1L);

    LONG   liRes = 0L;
    BOOL   bRes  = FALSE;
    CxFile sfFile;

    bRes = sfFile.bOpen(csFilePath, omRead, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, - 1L);

    liRes = sfFile.liGetSize();
    /*DEBUG*/xASSERT_RET(0 <= liRes, - 1L);

    return liRes;
}
//---------------------------------------------------------------------------
/*static*/
ULONGLONG
CxFile::ullGetLines(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    0LL);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), 0LL);

    ULONGLONG ullRes = 0LL;
    TCHAR     cChar;
    std::tifstream ifsStream(csFilePath.c_str(), std::ios::in);

    xCHECK_RET(!ifsStream || ifsStream.fail() || !ifsStream.good() || !ifsStream.is_open() || ifsStream.eof(), 0LL);

    for (ullRes = 0LL; ifsStream.get(cChar); ) {
        xCHECK_DO(xT('\n') == cChar, ++ ullRes);
    }

    return ullRes;
}
//---------------------------------------------------------------------------
//TODO: bGetTime (get time)
/*static*/
BOOL
CxFile::bGetTime(
    const std::tstring &csFilePath,
    time_t             *ptmCreate,
    time_t             *ptmAccess,
    time_t             *ptmModified
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// pftCreate   - n/a
    /*DEBUG*/// pftAccess   - n/a
    /*DEBUG*/// pftModified - n/a

    struct stat stInfo = {0};

    INT iRes = /*_t*/stat(csFilePath.c_str(), &stInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);

#if xTODO
    xCHECK_DO(NULL != ptmCreate,   *ptmCreate   = stInfo.st_ctim);  //status change
#endif
    xCHECK_DO(NULL != ptmAccess,   *ptmAccess   = stInfo.st_atime); //access
    xCHECK_DO(NULL != ptmModified, *ptmModified = stInfo.st_mtime); //modification

#if xTODO
    FILETIME *pftCreate, 
    FILETIME *pftAccess, 
    FILETIME *pftModified

    _m_bRes = ::GetFileTime(m_hHandle, pftCreate, pftAccess, pftModified);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bSetTime (set time)
/*static */
BOOL
CxFile::bSetTime(
    const std::tstring &csFilePath,
    const time_t       &ctmCreate,
    const time_t       &ctmAccess,
    const time_t       &ctmModified
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// ctmCreate   - n/a
    /*DEBUG*/// ctmAccess   - n/a
    /*DEBUG*/// ctmModified - n/a

#if defined(xOS_WIN)
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

    #if xDEPRECIATE
        CxFile flFile;

        bRes = flFile.bOpen(csFilePath, grWrite, smWrite, cfOpenExisting, CxFileAttribute::faNormal);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        bRes = flFile.bSetTime(ftCreate, ftAccess, ftModified);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    #else
        CxFileHandle m_hHandle;

        m_hHandle = ::CreateFile(csFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, CxFileAttribute::faNormal, NULL);
        /*DEBUG*/xASSERT_RET(FALSE != m_hHandle.bIsValid(), FALSE);

        bRes = ::SetFileTime(m_hHandle, &ftCreate, &ftAccess, &ftModified);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    #endif
#elif defined(xOS_LINUX)
    utimbuf tbTimes;

    tbTimes.actime  = ctmAccess;
    tbTimes.modtime = ctmModified;

    INT iRes = utime(csFilePath.c_str(), &tbTimes);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*   public: temporary
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
std::tstring
CxFile::sTempCreate(
    const std::tstring  &csFilePath,
    const std::tstring  &csDirPath,
    FILE               **pfFileHandle
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(),  std::tstring());
    /*DEBUG*/xASSERT_RET(NULL  == *pfFileHandle,      std::tstring());

    const std::tstring csFileNameTemplate = xT("XXXXXX");


    std::tstring sRes;

    BOOL bRes = CxDir::bCreateForce(csDirPath);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, std::tstring());

    sRes = CxPath::sSlashAppend(csDirPath) + CxPath::sGetFullName(csFilePath) + csFileNameTemplate;

#if defined(xOS_WIN)
    sRes.resize( sRes.size() + 1);

    errno_t iError = _tmktemp_s(&sRes.at(0), sRes.size() + 1);
    /*DEBUG*/xASSERT_RET(0 == iError, std::tstring());

    FILE *pfFile = _tfopen(sRes.c_str(), _sGetOpenMode(omBinCreateReadWrite).c_str());
    /*DEBUG*/xASSERT_RET(NULL != pfFile, std::tstring());
#elif defined(xOS_LINUX)
    INT iFile = _tmkstemp(&sRes.at(0));
    /*DEBUG*/xASSERT_RET(- 1 != iFile, std::tstring());

    FILE *pfFile = _tfdopen(iFile, _sGetOpenMode(omBinCreateReadWrite).c_str());
    /*DEBUG*/xASSERT_RET(NULL != pfFile, std::tstring());
#endif

    //out
    *pfFileHandle = pfFile;

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bTempClose(
    FILE **pfFileHandle
)
{
    /*DEBUG*/// n/a

    if (NULL != *pfFileHandle) {
        INT iRes = fclose(*pfFileHandle);
        /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
    }

    pfFileHandle = NULL;

    return TRUE;
}
//--------------------------------------------------------------------------


/****************************************************************************
*	public: text
*
*****************************************************************************/

//--------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bTextRead(
    const std::tstring &csFilePath,
    std::tstring       *psContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != psContent,          FALSE);

    BOOL         bRes = FALSE;
    CxFile       sfFile;
    std::tstring sRes;

    bRes = sfFile.bOpen(csFilePath, omBinRead, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    LONG liFileSize = sfFile.liGetSize();
    /*DEBUG*/xASSERT_RET(ppError != liFileSize, FALSE);

    xCHECK_DO(0L == liFileSize, (*psContent).clear(); return TRUE);

    sRes.resize(liFileSize);

    size_t uiReadLen = sfFile.uiRead((LPVOID)&sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(sRes.size() == uiReadLen, FALSE);

    //out
    std::swap((*psContent), sRes);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bTextWrite(
    const std::tstring &csFilePath,
    const std::tstring &csContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// csContent - n/a

    //TODO: if csContent.empty()

    BOOL   bRes = FALSE;
    CxFile sfFile;

    bRes = sfFile.bOpen(csFilePath, omBinWrite, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    xCHECK_RET(true == csContent.empty(), TRUE);

    size_t uiWriteLen = sfFile.uiWrite((LPVOID)&csContent.at(0), csContent.size());
    /*DEBUG*/xASSERT_RET(csContent.size() == uiWriteLen, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bTextRead(
    const std::tstring        &csFilePath,
    std::vector<std::tstring> *pvsContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pvsContent,            FALSE);

    BOOL                 bRes = FALSE;
    std::vector<std::tstring> vsRes;
    std::tstring              sFileContent;

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
    const std::tstring              &csFilePath,
    const std::vector<std::tstring> &cvsContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cvsContent - n/a

    //TODO: if cvsContent.empty()

    BOOL    bRes = FALSE;
    std::tstring sFileContent;

    sFileContent = CxString::sJoin(cvsContent, CxConst::xNL);

    bRes = bTextWrite(csFilePath, sFileContent);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bTextRead(
    const std::tstring                   &csFilePath,
    const std::tstring                   &csSeparator,
    std::map<std::tstring, std::tstring> *pmsContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFilePath), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pmsContent,            FALSE);

    //if file empty
    xCHECK_DO(0L == liGetSize(csFilePath), (*pmsContent).clear(); return TRUE);

    BOOL bRes = FALSE;

    std::tifstream ifsStream(csFilePath.c_str());
    /*DEBUG*/xASSERT_RET(ifsStream,           FALSE);
    /*DEBUG*/xASSERT_RET(!ifsStream.fail(),   FALSE);
    /*DEBUG*/xASSERT_RET(ifsStream.good(),    FALSE);
    /*DEBUG*/xASSERT_RET(ifsStream.is_open(), FALSE);
    /*DEBUG*/xASSERT_RET(!ifsStream.eof(),    FALSE);

    std::map<std::tstring, std::tstring> msRes;
    std::tstring                         sLine;
    std::vector<std::tstring>            vsLine;

    for (size_t i = 0; !ifsStream.eof();  ++ i) {
        std::getline(ifsStream, sLine);

        sLine = CxString::sTrimRightChars(sLine, CxConst::xEOL);

        bRes = CxString::bSplit(sLine, csSeparator, &vsLine);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        msRes.insert( std::pair<std::tstring, std::tstring>(vsLine.at(0), vsLine.at(1)) );
    }

    //out
    (*pmsContent).swap(msRes);


#if xTODO
    BOOL                                 bRes = FALSE;
    std::map<std::tstring, std::tstring> msRes;
    std::vector<std::tstring>            vsRes;

    bRes = bTextRead(csFilePath, &vsRes);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    std::vector<std::tstring>::const_iterator it;
    for (it = vsRes.begin(); it != vsRes.end(); ++ it) {
        std::vector<std::tstring> vsLine;

        bRes = CxString::bSplit(vsRes.at(0), csSeparator, &vsLine);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        msRes.insert( std::pair<std::tstring, std::tstring>(vsLine.at(0), vsLine.at(1)) );
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
    const std::tstring                         &csFilePath,
    const std::tstring                         &csSeparator,
    const std::map<std::tstring, std::tstring> &cmsContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),  FALSE);
    /*DEBUG*/xASSERT_RET(false == csSeparator.empty(), FALSE);
    /*DEBUG*/// cmsFile - n/a

    //TODO: if cmsFile.empty()

    BOOL   bRes = FALSE;
    CxFile stdFile;

    bRes = stdFile.bOpen(csFilePath, omWrite, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    std::map<std::tstring, std::tstring>::const_iterator it;
    for (it = cmsContent.begin(); it != cmsContent.end(); ++ it) {
        bRes = stdFile.bWriteLine((*it).first + csSeparator + (*it).second);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

#if xTODO
    BOOL         bRes = FALSE;
    std::tstring sRes;

    std::map<std::tstring, std::tstring>::const_iterator it;
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
*	public: bin
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bBinRead(
    const std::tstring &csFilePath,
    std::ustring       *pusContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pusContent,         FALSE);

    BOOL         bRes = FALSE;
    CxFile       sfFile;
    std::ustring usRes;

    bRes = sfFile.bOpen(csFilePath, omBinRead, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    LONG liFileSize = sfFile.liGetSize();
    /*DEBUG*/xASSERT_RET(ppError != liFileSize, FALSE);

    xCHECK_DO(0 == liFileSize, (*pusContent).clear(); return TRUE);

    usRes.resize(liFileSize);

    size_t uiReadLen = sfFile.uiRead((LPVOID)&usRes.at(0), usRes.size());
    /*DEBUG*/xASSERT_RET(usRes.size() == uiReadLen, FALSE);

    //out
    std::swap((*pusContent), usRes);

    return TRUE;

}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFile::bBinWrite(
    const std::tstring &csFilePath,
    const std::ustring &cusContent
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cusContent - n/a

    //TODO: if cusContent.empty()

    BOOL   bRes = FALSE;
    CxFile sfFile;

    bRes = sfFile.bOpen(csFilePath, omBinWrite, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    xCHECK_RET(true == cusContent.empty(), TRUE);

    size_t uiWriteLen = sfFile.uiWrite((LPVOID)&cusContent.at(0), cusContent.size());
    /*DEBUG*/xASSERT_RET(cusContent.size() == uiWriteLen, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public: other
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
std::tstring
CxFile::sBackup(
    const std::tstring &csFilePath,
    const std::tstring &csDestDirPath,
    const BOOL          cbMakeDaily
    /*INT bBackupLimit*/
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    std::tstring());
    /*DEBUG*/xASSERT_RET(false == csDestDirPath.empty(), std::tstring());

    BOOL bRes = FALSE;

    bRes = bIsExists(csFilePath);
    xCHECK_RET(FALSE == bRes, std::tstring());

    bRes = CxDir::bIsExists(csDestDirPath);
    xCHECK_DO(FALSE == bRes, CxDir::bCreateForce(csDestDirPath));

    //-------------------------------------
    //format file full name
    CxDateTime dtDT;

    std::tstring sBackupFilePath =
        CxPath::sSlashAppend(csDestDirPath) +
        CxPath::sGetFullName(csFilePath)    +
        xT(".bak [") + CxString::sReplaceAll((TRUE == cbMakeDaily) ? (dtDT.dtGetCurrent().sFormat(CxDateTime::ftDate)) : (dtDT.dtGetCurrent().sFormat(CxDateTime::ftDateTime)), xT(":"), xT("-")) + xT("]");

    bRes = bIsExists(sBackupFilePath);
    xCHECK_RET(TRUE == bRes, sBackupFilePath);

    //-------------------------------------
    //check for enough space
    ULONGLONG ullTotalFreeBytes = 0ULL;
    bRes = CxVolume::bGetFreeSpace(csDestDirPath, NULL, NULL, &ullTotalFreeBytes);
    xCHECK_RET(FALSE == bRes, std::tstring());

    if (static_cast<ULONGLONG>( liGetSize(csFilePath) ) > ullTotalFreeBytes) {
    	////TODO: CxMsgBoxT::iShow(xT("Not enough free space"), xT("File backup"));

    	return std::tstring();
    }

    //-------------------------------------
    //copy
    bRes = bCopy(csFilePath, sBackupFilePath, TRUE);
    xCHECK_RET(FALSE == bRes, std::tstring());

    //-------------------------------------
    //check for a valid backup
    /*DEBUG*/xASSERT_RET(TRUE                                == bIsExists(sBackupFilePath),               std::tstring());
    /*DEBUG*/xASSERT_RET(liGetSize(csFilePath)               == liGetSize(sBackupFilePath),               std::tstring());
    /*DEBUG*/xASSERT_RET(CxCrc32::ulCalcFileFast(csFilePath) == CxCrc32::ulCalcFileFast(sBackupFilePath), std::tstring());

    return sBackupFilePath;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
INT
CxFile::_iGetHandle(
    FILE *pfFile
)
{
    /*DEBUG*/xASSERT_RET(NULL != pfFile, etError);

    INT iRes = etError;

    iRes = fileno(pfFile);
    /*DEBUG*/xASSERT_RET(etError != iRes, etError);

    return iRes;
}
//---------------------------------------------------------------------------
/*static*/
FILE *
CxFile::_pfGetHandle(
    INT             iFileHandle,
    const EOpenMode omMode
)
{
    /*DEBUG*/
    /*DEBUG*/

    FILE *pfRes = NULL;

    pfRes = _tfdopen(iFileHandle, _sGetOpenMode(omMode).c_str());
    /*DEBUG*/xASSERT_RET(NULL != pfRes, NULL);

    return pfRes;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxFile::_sGetOpenMode(
    const EOpenMode comMode
)
{
    /*DEBUG*/// omMode - n/a

    std::tstring sRes;

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

        default:                    { sRes.assign( xT("r")   ); }	break;
    }

    return sRes;
}
//---------------------------------------------------------------------------
