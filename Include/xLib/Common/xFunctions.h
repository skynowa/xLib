/**
 * \file  xFunctions.h
 * \brief types
 */


#ifndef xLib_Common_xFunctionsH
#define xLib_Common_xFunctionsH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xUNICODE)
    #define xTMAIN      wmain
    #define xFTPRINTF   fwprintf
    #define xTASCTIME   _wasctime
    #define xTFOPEN     _wfopen
    #define xTFDOPEN    _wfdopen
    #define xTSETLOCALE _wsetlocale
    #define xVSNTPRINTF _vsnwprintf
    #define xTFREOPEN   _wfreopen
    #define xTPERROR    _wperror
    #define xVSTPRINTF  _vswprintf
    #define xVTPRINTF   vwprintf
    #define xVFTPRINTF  vfwprintf
    #define xFGETTC      getwc
    #define xPUTTS      _putws
	#define xPUTTCHAR   putwchar
    #define xTACCESS    _waccess
    #define xGETTS      _getws
    #define xGETTCHAR   getwchar
    #define xTSYSTEM    _wsystem
	#define xTTMPNAM    _wtmpnam

	#define xTMKSTEMP   mkstemp


    #define xTRENAME    _wrename
	#define xTUNLINK    _wunlink
    #define xTREMOVE    _wremove
    #define xFPUTTS     fputws
	#define xUNGETTC    ungetwc
    #define xFPUTTC     fputwc
    #define xFGETTS     fgetws
    #define xTCSLEN     wcslen
    #define xTCHMOD     _wchmod

    //stat
    #if defined(xCOMPILER_CODEGEAR)
	    #define xTSTAT      _tstat
    #elif defined(xCOMPILER_MS)
        #define xTSTAT      _tstat64
    #else
        #define xTSTAT      _wstat
    #endif

    
    //chars
    #define xISTALNUM   iswalnum
    #define xISTALPHA   iswalpha
    #define xISTCNTRL   iswcntrl
    #define xISTDIGIT   iswdigit
    #define xISTXDIGIT  iswxdigit
    #define xISTGRAPH   iswgraph
    #define xISTPRINT   iswprint
    #define xISTPUNCT   iswpunct
    #define xISTSPACE   iswspace
    #define xISTLOWER   iswlower
    #define xISTUPPER   iswupper
    #define xTOTLOWER   towlower
    #define xTOTUPPER   towupper

    //sockets
    ////typedef addrinfo    ADDRINFOT;
#else
    #define xTMAIN      main
    #define xFTPRINTF   fprintf
    #define xTASCTIME   asctime
    #define xTFOPEN     fopen
    #define xTFDOPEN    fdopen
    #define xTSETLOCALE setlocale
    #define xVSNTPRINTF vsnprintf
    #define xTFREOPEN   freopen
    #define xTPERROR    perror
    #define xVSTPRINTF  vsprintf
    #define xVTPRINTF   vprintf
    #define xVFTPRINTF  vfprintf
    #define xFGETTC      getc
    #define xPUTTS      puts
    #define xPUTTCHAR   putchar
    #define xTACCESS    access
    #define xGETTS      gets
    #define xGETTCHAR   getchar
    #define xTSYSTEM    system
    #define xTTMPNAM    tmpnam
    #define xTMKSTEMP   mkstemp
    #define xTRENAME    rename
    #define xTUNLINK    unlink
    #define xTREMOVE    remove
    #define xFPUTTS     fputs
    #define xUNGETTC    ungetc
    #define xFPUTTC     fputc
    #define xFGETTS     fgets
    #define xTCSLEN     strlen
    #define xTCHMOD     chmod

    //stat
    #if defined(xCOMPILER_CODEGEAR)
	    #define xTSTAT      _tstat
    #elif defined(xCOMPILER_MS)
        #define xTSTAT      _tstat64
    #else
        #define xTSTAT      _wstat
    #endif


    //chars
    #define xISTALNUM   isalnum
    #define xISTALPHA   isalpha
    #define xISTCNTRL   iscntrl
    #define xISTDIGIT   isdigit
    #define xISTXDIGIT  isxdigit
    #define xISTGRAPH   isgraph
    #define xISTPRINT   isprint
    #define xISTPUNCT   ispunct
    #define xISTSPACE   isspace
    #define xISTLOWER   islower
    #define xISTUPPER   isupper
    #define xTOTLOWER   tolower
    #define xTOTUPPER   toupper

    //sockets
    ////typedef addrinfo    ADDRINFOT;
#endif //xUNICODE
//---------------------------------------------------------------------------
#endif  //xLib_Common_xFunctionsH
