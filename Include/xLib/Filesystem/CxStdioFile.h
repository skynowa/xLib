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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <ostream>
#include <fstream>

#if defined(xOS_WIN)
    #include <sys/locking.h>
    #include <io.h>
    #include <errno.h>
#endif
//---------------------------------------------------------------------------
class CxStdioFile : public CxNonCopyable {
    public:
        enum EErrorType {
            etError = EOF
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
        BOOL             bIsValid     () const;
        BOOL             bOpen        (const tString &csFilePath, const EOpenMode omMode);
        BOOL             bReopen      (const tString &csFilePath, const EOpenMode omMode);
        BOOL             bAttach      (FILE *pflFile);
        FILE            *pGet         () const;
        tString          sGetPath     () const;

        //read, write
        size_t           uiRead       (LPVOID pvBuff,        const size_t cuiCount) const;
        size_t           uiWrite      (const LPVOID pcvBuff, const size_t cuiCount) const;
        BOOL             bRead        (uString *psBuff) const;
        BOOL             bWrite       (const uString &csBuff) const;
        INT              iWrite       (LPCTSTR pcszFormat, ...) const;
        INT              iWriteV      (LPCTSTR pcszFormat, va_list arg) const;

        BOOL             bReadLine    (tString *psStr, const size_t cuiMaxCount) const;
        BOOL             bWriteLine   (const tString &csStr) const;
        BOOL             bWriteString (const tString &csStr) const;

        TCHAR            cReadChar    () const;
        BOOL             bWriteChar   (TCHAR cChar) const;
        BOOL             bUngetChar   (TCHAR cChar) const;

        BOOL             bClear       () const;

        //other
        BOOL             bLocking     (const ELockingMode clmMode, LONG liBytes);
        BOOL             bSetPosition (LONG lOffset, const EPointerPosition cppPos) const;
        LONG             liGetPosition() const;

        BOOL             bSetVBuff    (LPSTR pszBuff, const EBufferingMode cbmMode, size_t uiSize) const;

    #if defined(xOS_WIN)
        BOOL             bSetMode     (const ETranslationMode tmMode) const;
    #elif defined(xOS_LINUX)
        //TODO: bSetMode
    #endif

        LONG             liGetSize    () const;
        BOOL             bResize      (const LONG cliSize) const;

        //error handling
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
        static BOOL      bDelete      (const tString &csFilePath);
        static BOOL      bWipe        (const tString &csFilePath, const size_t cuiPasses);
        static BOOL      bUnlink      (const tString &csFilePath);
        static BOOL      bRename      (const tString &csOldFilePath,  const tString &csNewFilePath);
        static BOOL      bMove        (const tString &csFilePath,     const tString &csDirPath);
        static BOOL      bCopy        (const tString &csFilePathFrom, const tString &csFilePathTo, BOOL bFailIfExists);
        static tString   sCreateTemp  (const tString &csFilePath, const tString &csDirPath);
        static LONG      liGetSize    (const tString &csFilePath);
        static ULONGLONG ullGetLines  (const tString &csFilePath);

        //text
        static BOOL      bTextRead    (const tString &csFilePath, tString *psStr);
        static BOOL      bTextWrite   (const tString &csFilePath, const tString &csStr);

        static BOOL      bTextRead    (const tString &csFilePath, std::vector<tString> *pvecsContent);
        static BOOL      bTextWrite   (const tString &csFilePath, const std::vector<tString> &cvecsContent);

        static BOOL      bTextRead    (const tString &csFilePath, const tString &csDelimiter, std::map<tString, tString> *pmapsFile);

        //binary
        static BOOL      bBinRead     (const tString &csFilePath, uString *pusStr);
        static BOOL      bBinWrite    (const tString &csFilePath, const uString &cusStr);

    private:
        mutable BOOL     _m_bRes;
        FILE            *_m_pFile;
        tString          _m_sFilePath;

        INT              _iGetHandle  () const;
        static tString   _sGetOpenMode(const EOpenMode omMode);
};
//---------------------------------------------------------------------------
#endif  //xLib_Filesystem_CxStdioFileH
