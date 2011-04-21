/****************************************************************************
* Class name:  CxStdioFile
* Description: file
* File name:   CxStdioFile.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     21.05.2009 17:46:38
*
*****************************************************************************/


#ifndef    xLib_Fso_CxStdioFileH
#define    xLib_Fso_CxStdioFileH
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

        //File attribute
        ////enum EAttributes {
        ////    faInvalid  = - 1,           /*?*/
        ////    faNormal   =  _A_NORMAL,    /* Normal file - No read/write restrictions */
        ////    faReadOnly =  _A_RDONLY,    /* Read only file */
        ////    faHidden   =  _A_HIDDEN,    /* Hidden file */
        ////    faSystem   =  _A_SYSTEM,    /* System file */
        ////    faSubDir   =  _A_SUBDIR,    /* Subdirectory */
        ////    faArchive  =  _A_ARCH ,     /* Archive file */
        ////};

        //Translation mode
        ////enum ETranslationMode {
        ////    tmText   = _O_TEXT,          /* file mode is text (translated) */
        ////    tmBinary = _O_BINARY         /* file mode is binary (untranslated) */
        ////};

        //Access mode
        enum EAccessMode {
            amExistence = 0,    //Existence only
            amWrite     = 2,    //Write permission
            amRead      = 4,    //Read permission
            amReadWrite = 6     //Read and write permission
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


        #if defined(xOS_WIN)
        //Locking action to perform
        enum ELockingMode {
            lmTryLock = LK_LOCK/*_LK_LOCK*/,        //Locks the specified bytes. If the bytes cannot be locked, the program immediately tries again after 1 second. If, after 10 attempts, the bytes cannot be locked, the constant returns an error.
            lmLock    = LK_NBLCK/*_LK_NBLCK*/,      //Locks the specified bytes. If the bytes cannot be locked, the constant returns an error.
            //lmXXX = _LK_NBRLCK,                   //Same as _LK_NBLCK.
            //lmXXX = _LK_RLCK,                     //Same as _LK_LOCK.
            lmUnlock  = LK_UNLCK/*_LK_UNLCK*/       //Unlocks the specified bytes, which must have been previously locked.
        };
        #endif

        //Permission mode
        enum EPermissionMode {
            #if defined(xOS_WIN)
                pmRead             = _S_IREAD,                  //read permitted
                pmWrite            = _S_IWRITE,                 //write permitted
                pmReadWrite        = (_S_IREAD | _S_IWRITE)     //read and write
            #elif defined(xOS_LINUX)
                pmSetUserId        = S_ISUID,                   //set-user-ID
                pmSetGroupId       = S_ISGID,                   //set-group-ID
                pmStickyBit        = S_ISVTX,                   //sticky bit

                pmRead             = S_IRUSR,                   //read by owner
                pmWrite            = S_IWUSR,                   //write by owner
                pmReadWrite        = (S_IRUSR | S_IWUSR),       //read and write by owner
                pmExecSearch       = S_IXUSR,                   //execute/search by owner

                pmReadGroup        = S_IRGRP,                   //read by group
                pmWriteGroup       = S_IWGRP,                   //write by group
                pmExecSearchGroup  = S_IXGRP,                   //execute/search by group

                pmReadOthers       = S_IROTH,                   //read by others
                pmWriteOthers      = S_IWOTH,                   //write by others
                pmExecSearchOthers = S_IXOTH                    //execute/search by others
            #endif
        };


        //constructors, destructor
                           CxStdioFile  ();
        virtual           ~CxStdioFile  ();

        //open, get
        BOOL               bIsValid     () const;
        BOOL               bOpen        (const tString &csFilePath, const EOpenMode omMode);
        BOOL               bReopen      (const tString &csFilePath, const EOpenMode omMode);
        BOOL               bAttach      (FILE *pflFile);
        FILE              *pGet         () const;
        tString            sGetPath     () const;

        //read, write
        std::size_t        uiRead       (LPVOID pvBuf,         std::size_t uiCount) const;
        std::size_t        uiWrite      (const LPVOID pcvBuff, std::size_t uiCount) const;

        BOOL               bReadAll     (LPVOID pvBuff,        std::size_t uiBuffSize, std::size_t uiBlockSize) const;
        BOOL               bWriteAll    (const LPVOID pcvBuf,  std::size_t uiBuffSize, std::size_t uiBlockSize) const;

        BOOL               bReadAll     (uString *psBuff,       std::size_t uiBlockSize) const;
        BOOL               bWriteAll    (const uString &csBuff, std::size_t uiBlockSize) const;

        BOOL               bReadAll     (tString *psBuff,       std::size_t uiBlockSize) const;
        BOOL               bWriteAll    (const tString &csBuff, std::size_t uiBlockSize) const;

        BOOL               bReadLine    (LPTSTR pszStr, std::size_t uiMaxSize) const;
        BOOL               bWriteLine   (const tString &csStr) const;
        BOOL               bWriteString (const tString &csStr) const;

        TCHAR              cReadChar    ();
        BOOL               bWriteChar   (TCHAR cChar);
        BOOL               bUngetChar   (TCHAR cChar);

        //formatting write
        INT                iFprintf     (LPCTSTR pcszFormat, ...) const;
        INT                iFprintfV    (LPCTSTR pcszFormat, va_list arg) const;

        //other
        #if defined(xOS_WIN)
        BOOL               bLocking     (ELockingMode lmMode, LONG liBytes);
        #endif

        BOOL               bSetPosition (LONG lOffset, EPointerPosition fpPos/* = fpBegin*/) const;
        LONG               liGetPosition() const;

        BOOL               bSetVBuff    (LPSTR pszBuff, EBufferingMode bmMode, std::size_t uiSize);
        ////BOOL               bSetMode (ETranslationMode tmMode);

        LONG               liGetSize    () const;

        #if defined(xOS_WIN)
        BOOL               bChsize      (LONG liSize);
        #endif

        //error handling
        BOOL               bIsEof       () const;
        BOOL               bIsError     () const;
        BOOL               bClearErr    () const;

        //closing
        BOOL               bFlush       () const;
        BOOL               bClose       ();

        //static
        static BOOL        bIsFile      (const tString &csFilePath);
        static BOOL        bIsExists    (const tString &csFilePath);
        static BOOL        bAccess      (const tString &csFilePath, EAccessMode amMode);
        static BOOL        bChmod       (const tString &csFilePath, EPermissionMode pmMode);
        static BOOL        bDelete      (const tString &csFilePath);
        static BOOL        bUnlink      (const tString &csFilePath);
        static BOOL        bRename      (const tString &csOldFilePath,  const tString &csNewFilePath);
        static BOOL        bMove        (const tString &csFilePath,     const tString &csDirPath);
        static BOOL        bCopy        (const tString &csFromFilePath, const tString &csToFilePath);
        static tString     sCreateTemp  (const tString &csFilePath, const tString &csDirPath);
        static ULONGLONG   ullLines     (const tString &csFilePath);

        //Macros
        //FILENAME_MAX    Maximum length of file names (constant)
        //TMP_MAX        Number of temporary files (constant)

        /****************************************************************************
        * static (all not tested)
        *
        *****************************************************************************/

        static LONG        liGetSize    (const tString &csFilePath);

        static BOOL        bReadFile    (const tString &csFilePath, std::vector<tString> *pvecsVector);
        static BOOL        bWriteFile   (const tString &csFilePath, const std::vector<tString> *pcvecsVector);

        static BOOL        bReadFileEx  (const tString &csFilePath, std::vector<tString> *pvecsFile);
        static BOOL        bReadFile    (const tString &csFilePath, std::vector<TCHAR>   *pvecchFile);

        static BOOL        bReadFile    (const tString &csFilePath, const tString &csDelimiter, std::map<tString, tString> *pmapsFile);
        static BOOL        bReadFile    (const tString &csFilePath, tString *psStr);

        static BOOL        bReadFile    (const tString &csFilePath, uString *pusStr);
        static BOOL        bWriteFile   (const tString &csFilePath, const uString &cusStr);

    private:
        mutable BOOL       _m_bRes;
        FILE              *_m_pFile;
        tString            _m_sFilePath;

        INT                _iGetHandle  ();
        static tString     _sGetOpenMode(const EOpenMode omMode);
};
//---------------------------------------------------------------------------
#endif    //xLib_Fso_CxStdioFileH
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
