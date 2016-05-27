/**
 * \file  Functions_ansi.h
 * \brief function macroses
 */


#pragma once

    #define tcin          cin
    #define tcout         cout
    #define tcerr         cerr
    #define tclog         clog
    #define xTEOF         EOF

    #define xTMAIN        main
    #define xTFPRINTF     std::fprintf
    #define xTASCTIME     std::asctime
    #define xTLOCALE       std::locale
    #define xTSETLOCALE   std::setlocale
    #define xTFOPEN       std::fopen
    #define xTFREOPEN     std::freopen
    #define xTFDOPEN      ::fdopen
    #define xTVSNPRINTF   ::vsnprintf
    #define xTPERROR      std::perror
    #define xTVSPRINTF    std::vsprintf
    #define xTVPRINTF     std::vprintf
    #define xTVFPRINTF    std::vfprintf
    #define xTFGETC       std::getc
    #define xTPUTS        std::puts
    #define xTPUTCHAR     std::putchar
    #define xTACCESS      ::access
    #define xTGETS        std::gets
    #define xTGETCHAR     std::getchar
    #define xTTMPNAM      std::tmpnam
    #define xSTRFTIME     std::strftime

    // xTMKSTEMP
#if   xCOMPILER_MINGW
    #define xTMKSTEMP     ::_mktemp
#elif xCOMPILER_MS
    #define xTMKSTEMP     ::_tmktemp_s
#elif xCOMPILER_CODEGEAR
    #define xTMKSTEMP     ::_mktemp
#elif xCOMPILER_GNUC
    #define xTMKSTEMP     ::mkstemp
#else
    #define xTMKSTEMP     std::mktemp
#endif

    #define xTRENAME      std::rename
    #define xTUNLINK      ::unlink
    #define xTREMOVE      std::remove
    #define xTFPUTS       std::fputs
    #define xTUNGETC      std::ungetc
    #define xTFPUTC       std::fputc
    #define xTFGETS       std::fgets
    #define xTSTRLEN      std::strlen
    #define xTCHMOD       ::chmod
    #define xTSYSTEM      std::system

// xTSTAT_STRUCT
#if   xCOMPILER_MINGW
    #define xTSTAT_STRUCT struct stat
#elif xCOMPILER_MS
    #define xTSTAT_STRUCT struct _tstat64
#elif xCOMPILER_CODEGEAR
    #define xTSTAT_STRUCT struct _stat
#elif xCOMPILER_GNUC
    #define xTSTAT_STRUCT struct stat
#else
    #define xTSTAT_STRUCT struct stat
#endif

// xTSTAT
#if   xCOMPILER_MINGW
    #define xTSTAT        ::stat
#elif xCOMPILER_MS
    #define xTSTAT        ::_tstat64
#elif xCOMPILER_CODEGEAR
    #define xTSTAT        ::_tstat
#elif xCOMPILER_GNUC
    #define xTSTAT        ::lstat
#else
    #define xTSTAT        ::stat
#endif

// xSTRERROR
#if   xCOMPILER_MINGW
    #define xSTRERROR     ::_tcserror
#elif xCOMPILER_MS
    #define xSTRERROR     ::_tcserror_s
#elif xCOMPILER_GNUC
    #define xSTRERROR     ::strerror_r
#elif xCOMPILER_CODEGEAR
    #define xSTRERROR     ::_tcserror
#else
    #define xSTRERROR     std::strerror
#endif

    // chars
    #define xTISALNUM     std::isalnum
    #define xTISALPHA     std::isalpha
    #define xTISCNTRL     std::iscntrl
    #define xTISDIGIT     std::isdigit
    #define xTISXDIGIT    std::isxdigit
    #define xTISGRAPH     std::isgraph
    #define xTISPRINT     std::isprint
    #define xTISPUNCT     std::ispunct
    #define xTISSPACE     std::isspace
    #define xTISLOWER     std::islower
    #define xTISUPPER     std::isupper
    #define xTTOLOWER     std::tolower
    #define xTTOUPPER     std::toupper

    // chars (locale)
    #define xTISALNUM_L   xTISALNUM
    #define xTISALPHA_L   xTISALPHA
    #define xTISCNTRL_L   xTISCNTRL
    #define xTISDIGIT_L   xTISDIGIT
    #define xTISXDIGIT_L  xTISXDIGIT
    #define xTISGRAPH_L   xTISGRAPH
    #define xTISPRINT_L   xTISPRINT
    #define xTISPUNCT_L   xTISPUNCT
    #define xTISSPACE_L   xTISSPACE
    #define xTISLOWER_L   xTISLOWER
    #define xTISUPPER_L   xTISUPPER
    #define xTTOLOWER_L   xTTOLOWER
    #define xTTOUPPER_L   xTTOUPPER
