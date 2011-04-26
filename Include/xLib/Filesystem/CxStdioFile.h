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
        //error type
        enum EErrorType {
            etError = EOF
        };

        //Open mode
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

        //Translation mode
    #if defined(xOS_WIN)
        enum ETranslationMode {
            tmText   = O_TEXT,
            tmBinary = O_BINARY
        };
    #elif defined(xOS_LINUX)
        //TODO: xOS_LINUX

    #endif

        //Access mode
        enum EAccessMode {
            amExistence = 0,
            amWrite     = 2,
            amRead      = 4,
            amReadWrite = 6
        };

        //file position data for the given stream
        enum EPointerPosition {
            ppBegin = SEEK_SET,
            ppCurr  = SEEK_CUR,
            ppEnd   = SEEK_END,
            ppError = - 1L
        };

        //mode for file buffering
        enum EBufferingMode {
            bmFull = _IOFBF,
            bmLine = _IOLBF,
            bmNo   = _IONBF
        };

        //Locking action to perform
        enum ELockingMode {
            #if defined(xOS_WIN)
                lmTryLock = LK_LOCK,    //Locks the specified bytes. If the bytes cannot be locked, the program immediately tries again after 1 second.
                lmLock    = LK_NBLCK,   //Locks the specified bytes. If the bytes cannot be locked, the constant returns an error.
                lmUnlock  = LK_UNLCK    //Unlocks the specified bytes, which must have been previously locked.
            #elif defined(xOS_LINUX)
                lmLock    = F_LOCK,     //Set an exclusive lock on the specified section of the file
                lmTlock   = F_TLOCK,    //Same as F_LOCK but the call never blocks and returns an error instead if the file is already locked
                lmUlock   = F_ULOCK,    //Unlock the indicated section of the file.  This may cause a locked section to be split into two locked sections
                lmTest    = F_TEST      //Test the lock: return 0 if the specified section is unlocked or locked by this process; return -1, set errno to EAGAIN
            #endif
        };

        //Permission mode
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
        size_t           uiRead       (LPVOID pvBuf,         const size_t cuiCount) const;
        size_t           uiWrite      (const LPVOID pcvBuff, const size_t cuiCount) const;

        BOOL             bReadAll     (LPVOID pvBuff,        const size_t cuiBuffSize, const size_t uiBlockSize) const;
        BOOL             bWriteAll    (const LPVOID pcvBuf,  const size_t cuiBuffSize, const size_t uiBlockSize) const;

        BOOL             bReadAll     (uString *psBuff,       const size_t cuiBlockSize) const;
        BOOL             bWriteAll    (const uString &csBuff, size_t uiBlockSize) const;

        BOOL             bReadAll     (tString *psBuff,       const size_t cuiBlockSize) const;
        BOOL             bWriteAll    (const tString &csBuff, size_t uiBlockSize) const;

        BOOL             bReadLine    (LPTSTR pszStr, const size_t cuiMaxCount) const;
        BOOL             bWriteLine   (const tString &csStr) const;
        BOOL             bWriteString (const tString &csStr) const;

        TCHAR            cReadChar    ();
        BOOL             bWriteChar   (TCHAR cChar);
        BOOL             bUngetChar   (TCHAR cChar);

        //formatting write
        INT              iWrite       (LPCTSTR pcszFormat, ...) const;
        INT              iWriteV      (LPCTSTR pcszFormat, va_list arg) const;

        //other
        BOOL             bLocking     (const ELockingMode clmMode, LONG liBytes);
        BOOL             bSetPosition (LONG lOffset, const EPointerPosition cfpPos) const;
        LONG             liGetPosition() const;

        BOOL             bSetVBuff    (LPSTR pszBuff, const EBufferingMode cbmMode, size_t uiSize);

    #if defined(xOS_WIN)
        BOOL             bSetMode     (const ETranslationMode tmMode);
    #elif defined(xOS_LINUX)
        //TODO: xOS_LINUX
    #endif

        LONG             liGetSize    () const;
        BOOL             bChsize      (LONG liSize);

        //error handling
        BOOL             bIsEof       () const;
        BOOL             bIsError     () const;
        BOOL             bClearErr    () const;

        //closing
        BOOL             bFlush       () const;
        BOOL             bClose       ();

        //static
        static BOOL      bIsFile      (const tString &csFilePath);
        static BOOL      bIsExists    (const tString &csFilePath);
        static BOOL      bAccess      (const tString &csFilePath, const EAccessMode camMode);
        static BOOL      bChmod       (const tString &csFilePath, const EPermissionMode cpmMode);
        static BOOL      bDelete      (const tString &csFilePath);
        static BOOL      bUnlink      (const tString &csFilePath);
        static BOOL      bRename      (const tString &csOldFilePath,  const tString &csNewFilePath);
        static BOOL      bMove        (const tString &csFilePath,     const tString &csDirPath);
        static BOOL      bCopy        (const tString &csFromFilePath, const tString &csToFilePath);
        static tString   sCreateTemp  (const tString &csFilePath, const tString &csDirPath);
        static ULONGLONG ullLines     (const tString &csFilePath);

        //static (all not tested)
        static LONG      liGetSize    (const tString &csFilePath);

        static BOOL      bReadFile    (const tString &csFilePath, std::vector<tString> *pvecsVector);
        static BOOL      bWriteFile   (const tString &csFilePath, const std::vector<tString> *pcvecsVector);

        static BOOL      bReadFileEx  (const tString &csFilePath, std::vector<tString> *pvecsFile);
        static BOOL      bReadFile    (const tString &csFilePath, std::vector<TCHAR>   *pvecchFile);

        static BOOL      bReadFile    (const tString &csFilePath, const tString &csDelimiter, std::map<tString, tString> *pmapsFile);
        static BOOL      bReadFile    (const tString &csFilePath, tString *psStr);

        static BOOL      bReadFile    (const tString &csFilePath, uString *pusStr);
        static BOOL      bWriteFile   (const tString &csFilePath, const uString &cusStr);

    private:
        mutable BOOL     _m_bRes;
        FILE            *_m_pFile;
        tString          _m_sFilePath;

        INT              _iGetHandle  ();
        static tString   _sGetOpenMode(const EOpenMode omMode);
};
//---------------------------------------------------------------------------
#endif    //xLib_Filesystem_CxStdioFileH
/*
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256

int main(int argc, char *argv[]) {
    FILE *in, *out;
    char buf[BUFSIZE];
    size_t bt = 0;
    if((in = fopen(argv[1], "r")) == NULL) {
        perror("fopen in");
        exit(1);
    }
    if((out = fopen(argv[2], "w")) == NULL) {
        perror("fopen out");
        exit(1);
    }
    while(!feof(in)) {
        bt = fread(buf, sizeof(char), BUFSIZE, in);
        if(ferror(in)) {
            printf("fread error");
            exit(1);
        }
        fwrite(buf, sizeof(char), bt, out);
        if(ferror(out)) {
            printf("fwrite error");
            exit(1);
        }
    }
    return 0;
}
*/

/*
"r"        Open a file for reading. The file must exist.
"w"        Create an empty file for writing. If a file with the same name already exists its content is erased and the file is treated as a new empty file.
"a"        Append to a file. Writing operations append data at the end of the file. The file is created if it does not exist.
"r+"    Open a file for update both reading and writing. The file must exist.
"w+"    Create an empty file for both reading and writing. If a file with the same name already exists its content is erased and the file is treated as a new empty file.
"a+"    Open a file for reading and appending. All writing operations are performed at the end of the file, protecting the previous content to be overwritten. You can re
*/




/*
//setlocale(LC_NUMERIC, "");
//setlocale(LC_ALL, ".ACP" );
//setlocale(LC_ALL,"Russian");
*/


//TODO: std::ifsStream - �� ������ ������� �����



//_get_osfhandle()



/*
Dump memory buffer to hex text

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void dmpbuf(FILE *stream, const unsigned char* buffer, unsigned int length)
{
    const int N = 16;           // define maximum number of bytes of each line
    int i, nRead, addr = 0;
    char s[N * 3 + 1];          // string buffer
    char tmpbuf[32];            // temp buffer

    fprintf(stream, "\n");
    fprintf(stream, " ADDRESS | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F |      ASSCII     \n");
    fprintf(stream, "-----------------------------------------------------------------------------\n");

    while (length > 0) {
        // calculate number of bytes to output this line
        nRead = (length > N) ? N : length;
        length -= nRead;

        // output address
        fprintf(stream, "%08X | ", addr);

        // output hex contents
        s[0] = '\0';
        for (i = 0; i < nRead; i++) {
            sprintf(tmpbuf, "%02X ", buffer[addr+i]);
            strcat(s, tmpbuf);
        }
        fprintf(stream, "%s", s);

        // output alignment
        for (i = 0; i < N - nRead; i++) {
            fprintf(stream, "%3s", " ");
        }
        fprintf(stream, "| ");

        // output ascii characters
        for (i = 0; i < nRead; i++) {
            s[i] = isprint(buffer[addr+i]) ? buffer[addr+i] : '.';
        }
        s[i] = '\0';
        fprintf(stream, "%s", s);
        fprintf(stream, "\n");

        addr += nRead;
    }
}

int main()
{
    unsigned char buffer[253];

    for (int i = 0; i < sizeof(buffer); i++) {
        buffer[i] = i;
    }

    dmpbuf(stdout, buffer, sizeof(buffer));
    return 0;
}
*/
