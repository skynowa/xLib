/**
 * \file  Functions.h
 * \brief function macroses
 */


#pragma once

#if xUNICODE
        #define tcin            wcin
        #define tcout           wcout
        #define tcerr           wcerr
        #define tclog           wclog
        #define xTEOF           WEOF

        #define xTMAIN          wmain
        #define xTFPRINTF       std::fwprintf
        #define xTASCTIME       std::_wasctime
        #define xTSETLOCALE     std::_wsetlocale
        #define xTFOPEN         std::_wfopen
        #define xTFREOPEN       std::_wfreopen
        #define xTFDOPEN        ::_wfdopen
        #define xTVSNPRINTF     ::_vsnwprintf
        #define xTPERROR        std::_wperror
        #define xTVSPRINTF      std::_vswprintf
        #define xTVPRINTF       std::vwprintf
        #define xTVFPRINTF      std::vfwprintf
        #define xTFGETC         std::getwc
        #define xTPUTS          std::_putws
        #define xTPUTCHAR       std::putwchar
        #define xTACCESS        ::_waccess
        #define xTGETS          std::_getws
        #define xTGETCHAR       std::getwchar
        #define xTTMPNAM        std::_wtmpnam
        #define xSTRFTIME       std::wcsftime

        // xTMKSTEMP
    #if   xCOMPILER_MINGW
        #define xTMKSTEMP       ::_wmktemp
    #elif xCOMPILER_MS
        #define xTMKSTEMP       ::_tmktemp_s
    #elif xCOMPILER_CODEGEAR
        #define xTMKSTEMP       ::_wmktemp
    #elif xCOMPILER_GNUC
        #define xTMKSTEMP       ::mkstemp
    #else
        #define xTMKSTEMP       std::mkstemp
    #endif

        #define xTRENAME        std::_wrename
        #define xTUNLINK        ::_wunlink
        #define xTREMOVE        std::_wremove
        #define xTFPUTS         std::fputws
        #define xTUNGETC        std::ungetwc
        #define xTFPUTC         std::fputwc
        #define xTFGETS         std::fgetws
        #define xTSTRLEN        std::wcslen
        #define xTCHMOD         ::_wchmod
        #define xTSYSTEM        std::_wsystem

    // xTSTAT_STRUCT
    #if   xCOMPILER_MINGW
        #define xTSTAT_STRUCT   struct stat
    #elif xCOMPILER_MS
        #define xTSTAT_STRUCT   struct _tstat64
    #elif xCOMPILER_CODEGEAR
        #define xTSTAT_STRUCT   struct _stat
    #elif xCOMPILER_GNUC
        #define xTSTAT_STRUCT   struct stat
    #else
        #define xTSTAT_STRUCT   struct stat
    #endif

    // xTSTAT
    #if   xCOMPILER_MINGW
        #define xTSTAT          ::_wstat
    #elif xCOMPILER_MS
        #define xTSTAT          ::_tstat64
    #elif xCOMPILER_CODEGEAR
        #define xTSTAT          ::_tstat
    #elif xCOMPILER_GNUC
        #define xTSTAT          ::_wlstat
    #else
        #define xTSTAT          ::_wstat
    #endif

    // xSTRERROR
    #if   xCOMPILER_MINGW
        #define xSTRERROR       ::_tcserror
    #elif xCOMPILER_MS
        #define xSTRERROR       ::_tcserror_s
    #elif xCOMPILER_GNUC
        #define xSTRERROR       ::strerror_r
    #elif xCOMPILER_CODEGEAR
        #define xSTRERROR       ::_tcserror
    #else
        #define xSTRERROR       ::_wstrerror
    #endif

        // chars
        #define xTISALNUM       std::iswalnum
        #define xTISALPHA       std::iswalpha
        #define xTISCNTRL       std::iswcntrl
        #define xTISDIGIT       std::iswdigit
        #define xTISXDIGIT      std::iswxdigit
        #define xTISGRAPH       std::iswgraph
        #define xTISPRINT       std::iswprint
        #define xTISPUNCT       std::iswpunct
        #define xTISSPACE       std::iswspace
        #define xTISLOWER       std::iswlower
        #define xTISUPPER       std::iswupper
        #define xTTOLOWER       std::towlower
        #define xTTOUPPER       std::towupper
#else
        #define tcin            cin
        #define tcout           cout
        #define tcerr           cerr
        #define tclog           clog
        #define xTEOF           EOF

        #define xTMAIN          main
        #define xTFPRINTF       std::fprintf
        #define xTASCTIME       std::asctime
        #define xTSETLOCALE     std::setlocale
        #define xTFOPEN         std::fopen
        #define xTFREOPEN       std::freopen
        #define xTFDOPEN        ::fdopen
        #define xTVSNPRINTF     ::vsnprintf
        #define xTPERROR        std::perror
        #define xTVSPRINTF      std::vsprintf
        #define xTVPRINTF       std::vprintf
        #define xTVFPRINTF      std::vfprintf
        #define xTFGETC         std::getc
        #define xTPUTS          std::puts
        #define xTPUTCHAR       std::putchar
        #define xTACCESS        ::access
        #define xTGETS          std::gets
        #define xTGETCHAR       std::getchar
        #define xTTMPNAM        std::tmpnam
        #define xSTRFTIME       std::strftime

        // xTMKSTEMP
    #if   xCOMPILER_MINGW
        #define xTMKSTEMP       ::_mktemp
    #elif xCOMPILER_MS
        #define xTMKSTEMP       ::_tmktemp_s
    #elif xCOMPILER_CODEGEAR
        #define xTMKSTEMP       ::_mktemp
    #elif xCOMPILER_GNUC
        #define xTMKSTEMP       ::mkstemp
    #else
        #define xTMKSTEMP       std::mktemp
    #endif

        #define xTRENAME        std::rename
        #define xTUNLINK        ::unlink
        #define xTREMOVE        std::remove
        #define xTFPUTS         std::fputs
        #define xTUNGETC        std::ungetc
        #define xTFPUTC         std::fputc
        #define xTFGETS         std::fgets
        #define xTSTRLEN        std::strlen
        #define xTCHMOD         ::chmod
        #define xTSYSTEM        std::system

    // xTSTAT_STRUCT
    #if   xCOMPILER_MINGW
        #define xTSTAT_STRUCT   struct stat
    #elif xCOMPILER_MS
        #define xTSTAT_STRUCT   struct _tstat64
    #elif xCOMPILER_CODEGEAR
        #define xTSTAT_STRUCT   struct _stat
    #elif xCOMPILER_GNUC
        #define xTSTAT_STRUCT   struct stat
    #else
        #define xTSTAT_STRUCT   struct stat
    #endif

    // xTSTAT
    #if   xCOMPILER_MINGW
        #define xTSTAT          ::stat
    #elif xCOMPILER_MS
        #define xTSTAT          ::_tstat64
    #elif xCOMPILER_CODEGEAR
        #define xTSTAT          ::_tstat
    #elif xCOMPILER_GNUC
        #define xTSTAT          ::lstat
    #else
        #define xTSTAT          ::stat
    #endif

    // xSTRERROR
    #if   xCOMPILER_MINGW
        #define xSTRERROR       ::_tcserror
    #elif xCOMPILER_MS
        #define xSTRERROR       ::_tcserror_s
    #elif xCOMPILER_GNUC
        #define xSTRERROR       ::strerror_r
    #elif xCOMPILER_CODEGEAR
        #define xSTRERROR       ::_tcserror
    #else
        #define xSTRERROR       std::strerror
    #endif

        // chars
        #define xTISALNUM       std::isalnum
        #define xTISALPHA       std::isalpha
        #define xTISCNTRL       std::iscntrl
        #define xTISDIGIT       std::isdigit
        #define xTISXDIGIT      std::isxdigit
        #define xTISGRAPH       std::isgraph
        #define xTISPRINT       std::isprint
        #define xTISPUNCT       std::ispunct
        #define xTISSPACE       std::isspace
        #define xTISLOWER       std::islower
        #define xTISUPPER       std::isupper
        #define xTTOLOWER       std::tolower
        #define xTTOUPPER       std::toupper
#endif // xUNICODE


// xLOCKING
#if   xCOMPILER_MINGW
    #define xLOCKING            ::_locking
#elif xCOMPILER_MS
    #define xLOCKING            ::_locking
#elif xCOMPILER_CODEGEAR
    #define xLOCKING            ::locking
#elif xCOMPILER_GNUC
    #define xLOCKING            ::lockf
#else
    #define xLOCKING            ::locking
#endif

// xCHSIZE
#if   xCOMPILER_MINGW
    #define xCHSIZE             ::chsize
#elif xCOMPILER_MS
    #define xCHSIZE             ::_chsize_s
#elif xCOMPILER_CODEGEAR
    #define xCHSIZE             ::chsize
#elif xCOMPILER_GNUC
    #define xCHSIZE             ::ftruncate
#else
    #define xCHSIZE             ::chsize
#endif

// xIOCTLSOCKET
#if   xENV_WIN
    #define xIOCTLSOCKET        ::ioctlsocket
#elif xENV_UNIX
    #define xIOCTLSOCKET        ::ioctl
#endif

// xGETADDRINFO
#if   xCOMPILER_MINGW
    #define xGETADDRINFO        ::getaddrinfo
#elif xCOMPILER_MS
    #define xGETADDRINFO        ::GetAddrInfo
#elif xCOMPILER_CODEGEAR
    #define xGETADDRINFO        ::GetAddrInfo
#elif xCOMPILER_GNUC
    #define xGETADDRINFO        ::getaddrinfo
#else
    #define xGETADDRINFO        ::getaddrinfo
#endif

// xGETNAMEINFO
#if   xCOMPILER_MINGW
    #define xGETNAMEINFO        ::getnameinfo
#elif xCOMPILER_MS
    #define xGETNAMEINFO        ::GetNameInfo
#elif xCOMPILER_CODEGEAR
    #define xGETNAMEINFO        ::GetNameInfo
#elif xCOMPILER_GNUC
    #define xGETNAMEINFO        ::getnameinfo
#else
    #define xGETNAMEINFO        ::getnameinfo
#endif

// xSTATVFS (struct and function)
#if   xENV_WIN
    xNA
#elif xENV_UNIX
    xNA

    #if   xENV_LINUX
        #if   xOS_ANDROID
            #define xSTATVFS    ::statfs
        #elif xOS_LINUX
            #define xSTATVFS    ::statfs64
        #endif
    #elif xENV_BSD
        #define xSTATVFS        ::statvfs
    #elif xENV_APPLE
        #define xSTATVFS        ::statfs64
    #endif
#endif
    ///< filesystem statfs (struct and function)

#if xOPTION_HEADER_ONLY
    #include "Functions.cpp"
#endif
