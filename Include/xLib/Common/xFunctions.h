/**
 * \file  xFunctions.h
 * \brief function's macroses
 */


#ifndef xLib_Common_xFunctionsH
#define xLib_Common_xFunctionsH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if xUNICODE
        #define tcin            wcin
        #define tcout           wcout
        #define tcerr           wcerr
        #define tclog           wclog
        #define xTEOF           WEOF

        #define xTMAIN          wmain
        #define xTFPRINTF       fwprintf
        #define xTASCTIME       _wasctime
        #define xTSETLOCALE     _wsetlocale
        #define xTFOPEN         _wfopen
        #define xTFREOPEN       _wfreopen
        #define xTFDOPEN        _wfdopen
        #define xTVSNPRINTF     _vsnwprintf
        #define xTPERROR        _wperror
        #define xTVSPRINTF      _vswprintf
        #define xTVPRINTF       vwprintf
        #define xTVFPRINTF      vfwprintf
        #define xTFGETC         getwc
        #define xTPUTS          _putws
        #define xTPUTCHAR       putwchar
        #define xTACCESS        _waccess
        #define xTGETS          _getws
        #define xTGETCHAR       getwchar
        #define xTTMPNAM        _wtmpnam

        //mkstemp
    #if   xCOMPILER_MINGW32
        #define xTMKSTEMP       _wmktemp
    #elif xCOMPILER_INTEL
        #define xTMKSTEMP       _tmktemp_s
    #elif xCOMPILER_MS
        #define xTMKSTEMP       _tmktemp_s
    #elif xCOMPILER_CODEGEAR
        #define xTMKSTEMP       _wmktemp
    #elif xCOMPILER_GNUC
        #define xTMKSTEMP       mkstemp
    #else
        #define xTMKSTEMP       mkstemp
    #endif

        #define xTRENAME        _wrename
        #define xTUNLINK        _wunlink
        #define xTREMOVE        _wremove
        #define xTFPUTS         fputws
        #define xTUNGETC        ungetwc
        #define xTFPUTC         fputwc
        #define xTFGETS         fgetws
        #define xTSTRLEN        wcslen
        #define xTCHMOD         _wchmod
        #define xTSYSTEM        _wsystem

    //struct stat
    #if xCOMPILER_CODEGEAR
        #define xTSTAT_STRUCT   struct _stat
    #elif xCOMPILER_MS
        #define xTSTAT_STRUCT   struct _tstat64
    #else
        #define xTSTAT_STRUCT   struct stat
    #endif

    //stat
    #if xCOMPILER_CODEGEAR
        #define xTSTAT          _tstat
    #elif xCOMPILER_MS
        #define xTSTAT          _tstat64
    #else
        #define xTSTAT          _wstat
    #endif

        //chars
        #define xTISALNUM       iswalnum
        #define xTISALPHA       iswalpha
        #define xTISCNTRL       iswcntrl
        #define xTISDIGIT       iswdigit
        #define xTISXDIGIT      iswxdigit
        #define xTISGRAPH       iswgraph
        #define xTISPRINT       iswprint
        #define xTISPUNCT       iswpunct
        #define xTISSPACE       iswspace
        #define xTISLOWER       iswlower
        #define xTISUPPER       iswupper
        #define xTTOLOWER       towlower
        #define xTTOUPPER       towupper
#else
        #define tcin            cin
        #define tcout           cout
        #define tcerr           cerr
        #define tclog           clog
        #define xTEOF           EOF

        #define xTMAIN          main
        #define xTFPRINTF       fprintf
        #define xTASCTIME       asctime
        #define xTSETLOCALE     setlocale
        #define xTFOPEN         fopen
        #define xTFREOPEN       freopen
        #define xTFDOPEN        fdopen
        #define xTVSNPRINTF     vsnprintf
        #define xTPERROR        perror
        #define xTVSPRINTF      vsprintf
        #define xTVPRINTF       vprintf
        #define xTVFPRINTF      vfprintf
        #define xTFGETC         getc
        #define xTPUTS          puts
        #define xTPUTCHAR       putchar
        #define xTACCESS        access
        #define xTGETS          gets
        #define xTGETCHAR       getchar
        #define xTTMPNAM        tmpnam

        //mkstemp
    #if   xCOMPILER_MINGW32
        #define xTMKSTEMP       _mktemp
    #elif xCOMPILER_INTEL
        #define xTMKSTEMP       _tmktemp_s
    #elif xCOMPILER_MS
        #define xTMKSTEMP       _tmktemp_s
    #elif xCOMPILER_CODEGEAR
        #define xTMKSTEMP       _mktemp
    #elif xCOMPILER_GNUC
        #define xTMKSTEMP       mkstemp
    #else
        #define xTMKSTEMP       mktemp
    #endif

        #define xTRENAME        rename
        #define xTUNLINK        unlink
        #define xTREMOVE        remove
        #define xTFPUTS         fputs
        #define xTUNGETC        ungetc
        #define xTFPUTC         fputc
        #define xTFGETS         fgets
        #define xTSTRLEN        strlen
        #define xTCHMOD         chmod
        #define xTSYSTEM        system

    //struct stat
    #if xCOMPILER_CODEGEAR
        #define xTSTAT_STRUCT   struct _stat
    #elif xCOMPILER_MS
        #define xTSTAT_STRUCT   struct _tstat64
    #else
        #define xTSTAT_STRUCT   struct stat
    #endif

    //stat
    #if xCOMPILER_CODEGEAR
        #define xTSTAT          _tstat
    #elif xCOMPILER_MS
        #define xTSTAT          _tstat64
    #else
        #define xTSTAT          stat
    #endif

        //chars
        #define xTISALNUM       isalnum
        #define xTISALPHA       isalpha
        #define xTISCNTRL       iscntrl
        #define xTISDIGIT       isdigit
        #define xTISXDIGIT      isxdigit
        #define xTISGRAPH       isgraph
        #define xTISPRINT       isprint
        #define xTISPUNCT       ispunct
        #define xTISSPACE       isspace
        #define xTISLOWER       islower
        #define xTISUPPER       isupper
        #define xTTOLOWER       tolower
        #define xTTOUPPER       toupper
#endif //xUNICODE
//---------------------------------------------------------------------------
#endif  //xLib_Common_xFunctionsH
