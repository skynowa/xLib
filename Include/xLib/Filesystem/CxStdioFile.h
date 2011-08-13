/****************************************************************************
* Class name:  CxStdioFile
* Description: file
* File name:   CxStdioFile.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     21.05.2009 17:46:38
*
*****************************************************************************/


#ifndef xLib_Filesystem_CxStdioFileH
#define xLib_Filesystem_CxStdioFileH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxStdioFile :
    public CxNonCopyable
{
    public:
        enum EErrorType {
            etError = TEOF
        };

        enum EOpenMode {
            omRead,                //"r"
            omWrite,               //"w"
            omAppend,              //"a"
            omOpenReadWrite,       //"r+"
            omCreateReadWrite,     //"w+"
            omOpenReadAppend,      //"a+"

            omBinRead,             //"rb"
            omBinWrite,            //"wb"
            omBinAppend,           //"ab"
            omBinOpenReadWrite,    //"rb+"
            omBinCreateReadWrite,  //"wb+"
            omBinOpenReadAppend    //"ab+"
        };

    #if defined(xOS_WIN)
        enum ETranslationMode {
            tmText   = O_TEXT,
            tmBinary = O_BINARY
        };
    #elif defined(xOS_LINUX)
        //TODO: ETranslationMode
    #endif

        enum EAccessMode {
            amExistence = 0,
            amWrite     = 2,
            amRead      = 4,
            amReadWrite = 6
        };

        enum EPointerPosition {
            ppBegin = SEEK_SET,
            ppCurr  = SEEK_CUR,
            ppEnd   = SEEK_END,
            ppError = - 1L
        };

        enum EBufferingMode {
            bmFull = _IOFBF,
            bmLine = _IOLBF,
            bmNo   = _IONBF
        };

        enum ELockingMode {
            #if defined(xOS_WIN)
                lmLock    = LK_NBLCK,
                lmTryLock = LK_LOCK,
                lmUnlock  = LK_UNLCK
            #elif defined(xOS_LINUX)
                lmLock    = F_LOCK,
                lmTlock   = F_TLOCK,
                lmTryLock = F_TEST,
                lmUnlock  = F_ULOCK
            #endif
        };

        enum EPermissionMode {
            #if defined(xOS_WIN)
                pmRead             = _S_IREAD,
                pmWrite            = _S_IWRITE,
                pmReadWrite        = (_S_IREAD | _S_IWRITE)
            #elif defined(xOS_LINUX)
                pmSetUserId        = S_ISUID,
                pmSetGroupId       = S_ISGID,
                pmStickyBit        = S_ISVTX,

                pmRead             = S_IRUSR,
                pmWrite            = S_IWUSR,
                pmReadWrite        = (S_IRUSR | S_IWUSR),
                pmExecSearch       = S_IXUSR,

                pmGroupRead        = S_IRGRP,
                pmGroupWrite       = S_IWGRP,
                pmGroupExecSearch  = S_IXGRP,

                pmOthersRead       = S_IROTH,
                pmOthersWrite      = S_IWOTH,
                pmOthersExecSearch = S_IXOTH
            #endif
        };


        //constructors, destructor
                         CxStdioFile  ();
        virtual         ~CxStdioFile  ();

        //open, get
        BOOL             bOpen        (const tString &csFilePath, const EOpenMode omMode, const BOOL cbIsUseBuffering);
        BOOL             bReopen      (const tString &csFilePath, const EOpenMode omMode, const BOOL cbIsUseBuffering);
        BOOL             bOpen        (FILE *pflFile);
        FILE            *pGet         () const;
        tString          sGetPath     () const;

        //read, write
        size_t           uiRead       (LPVOID pvBuff,        const size_t cuiCount) const;
        size_t           uiWrite      (const LPVOID pcvBuff, const size_t cuiCount) const;

        BOOL             bRead        (uString *psBuff) const;
        BOOL             bWrite       (const uString &csBuff) const;

        BOOL             bRead        (tString *psBuff) const;
        INT              iWrite       (LPCTSTR pcszFormat, ...) const;
        INT              iWriteV      (LPCTSTR pcszFormat, va_list arg) const;

        BOOL             bReadLine    (tString *psStr, const size_t cuiMaxCount) const;
        BOOL             bWriteLine   (const tString &csStr) const;

        TCHAR            chReadChar   () const;
        BOOL             bWriteChar   (const TCHAR ccChar) const;
        BOOL             bUngetChar   (const TCHAR ccChar) const;

        BOOL             bClear       () const;

        //times


        //other
        BOOL             bLocking     (const ELockingMode clmMode, const LONG cliBytes);
        BOOL             bSetPosition (const LONG clOffset, const EPointerPosition cppPos) const;
        LONG             liGetPosition() const;
        BOOL             bSetVBuff    (LPSTR pszBuff, const EBufferingMode cbmMode, const size_t cuiSize) const;

    #if defined(xOS_WIN)
        BOOL             bSetMode     (const ETranslationMode tmMode) const;
    #elif defined(xOS_LINUX)
        //TODO: bSetMode
    #endif

        LONG             liGetSize    () const;
        BOOL             bResize      (const LONG cliSize) const;

        //error handling
        BOOL             bIsValid     () const;
        BOOL             bIsOpen      () const;
        BOOL             bIsEmpty     () const;
        BOOL             bIsEof       () const;
        BOOL             bIsError     () const;
        BOOL             bErrorClear  () const;

        //closing
        BOOL             bFlush       () const;
        BOOL             bClose       ();

        //static
        static BOOL      bIsFile      (const tString &csFilePath);
        static BOOL      bIsExists    (const tString &csFilePath);
        static BOOL      bAccess      (const tString &csFilePath, const EAccessMode camMode);
        static BOOL      bChmod       (const tString &csFilePath, const EPermissionMode cpmMode);
        static BOOL      bClear       (const tString &csFilePath);
        static BOOL      bDelete      (const tString &csFilePath);
        static BOOL      bTryDelete   (const tString &csFilePath, const size_t cuiAttempts, const ULONG culTimeoutMsec);
        static BOOL      bWipe        (const tString &csFilePath, const size_t cuiPasses);
        static BOOL      bUnlink      (const tString &csFilePath);
        static BOOL      bRename      (const tString &csOldFilePath,  const tString &csNewFilePath);
        static BOOL      bMove        (const tString &csFilePath,     const tString &csDirPath);
        static BOOL      bCopy        (const tString &csFilePathFrom, const tString &csFilePathTo, const BOOL cbFailIfExists);
        static tString   sCreateTemp  (const tString &csFilePath, const tString &csDirPath);
        static LONG      liGetSize    (const tString &csFilePath);
        static ULONGLONG ullGetLines  (const tString &csFilePath);
        static BOOL      bGetTime     (const tString &csFilePath, time_t *ptmCreate, time_t *ptmAccess, time_t *ptmModified);
        static BOOL      bSetTime     (const tString &csFilePath, const time_t &ctmCreate, const time_t &ctmAccess, const time_t &ctmModified);

        //text
        static BOOL      bTextRead    (const tString &csFilePath, tString *psContent);
        static BOOL      bTextWrite   (const tString &csFilePath, const tString &csContent);

        static BOOL      bTextRead    (const tString &csFilePath, std::vector<tString> *pvsContent);
        static BOOL      bTextWrite   (const tString &csFilePath, const std::vector<tString> &cvsContent);

        static BOOL      bTextRead    (const tString &csFilePath, const tString &csSeparator, std::map<tString, tString> *pmsContent);
        static BOOL      bTextWrite   (const tString &csFilePath, const tString &csSeparator, const std::map<tString, tString> &cmsContent);

        //binary
        static BOOL      bBinRead     (const tString &csFilePath, uString *pusContent);
        static BOOL      bBinWrite    (const tString &csFilePath, const uString &cusContent);

        //other
        static tString   sBackup      (const tString &csFilePath, const tString &csDestDirPath, const BOOL cbMakeDaily /*,INT bBackupLimit*/);

    private:
        mutable BOOL     _m_bRes;
        FILE            *_m_pFile;
        tString          _m_sFilePath;

        INT              _iGetHandle  () const;
        static tString   _sGetOpenMode(const EOpenMode comMode);
};
//---------------------------------------------------------------------------
#endif  //xLib_Filesystem_CxStdioFileH
