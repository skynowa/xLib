/**
 * \file  xFunctions.h
 * \brief function's macroses
 */


#pragma once

#ifndef xLib_xFunctionsH
#define xLib_xFunctionsH
//-------------------------------------------------------------------------------------------------
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
        #define xTVSNPRINTF     ::_vsnwprintf
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
        #define xTSTAT          _wstat
    #elif xCOMPILER_MS
        #define xTSTAT          _tstat64
    #elif xCOMPILER_CODEGEAR
        #define xTSTAT          _tstat
    #elif xCOMPILER_GNUC
        #define xTSTAT          _wlstat
    #else
        #define xTSTAT          _wstat
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
        #define xTFPRINTF       fprintf
        #define xTASCTIME       asctime
        #define xTSETLOCALE     setlocale
        #define xTFOPEN         fopen
        #define xTFREOPEN       freopen
        #define xTFDOPEN        fdopen
        #define xTVSNPRINTF     ::vsnprintf
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
        #define xTSTAT          stat
    #elif xCOMPILER_MS
        #define xTSTAT          _tstat64
    #elif xCOMPILER_CODEGEAR
        #define xTSTAT          _tstat
    #elif xCOMPILER_GNUC
        #define xTSTAT          lstat
    #else
        #define xTSTAT          stat
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
    #define xLOCKING            _locking
#elif xCOMPILER_MS
    #define xLOCKING            _locking
#elif xCOMPILER_CODEGEAR
    #define xLOCKING            locking
#elif xCOMPILER_GNUC
    #define xLOCKING            lockf
#else
    #define xLOCKING            locking
#endif

// xCHSIZE
#if   xCOMPILER_MINGW
    #define xCHSIZE             chsize
#elif xCOMPILER_MS
    #define xCHSIZE             _chsize_s
#elif xCOMPILER_CODEGEAR
    #define xCHSIZE             chsize
#elif xCOMPILER_GNUC
    #define xCHSIZE             ftruncate
#else
    #define xCHSIZE             chsize
#endif

// xGETADDRINFO
#if   xCOMPILER_MINGW
    #define xGETADDRINFO        getaddrinfo
#elif xCOMPILER_MS
    #define xGETADDRINFO        GetAddrInfo
#elif xCOMPILER_CODEGEAR
    #define xGETADDRINFO        GetAddrInfo
#elif xCOMPILER_GNUC
    #define xGETADDRINFO        getaddrinfo
#else
    #define xGETADDRINFO        getaddrinfo
#endif

// xGETNAMEINFO
#if   xCOMPILER_MINGW
    #define xGETNAMEINFO        getnameinfo
#elif xCOMPILER_MS
    #define xGETNAMEINFO        GetNameInfo
#elif xCOMPILER_CODEGEAR
    #define xGETNAMEINFO        GetNameInfo
#elif xCOMPILER_GNUC
    #define xGETNAMEINFO        getnameinfo
#else
    #define xGETNAMEINFO        getnameinfo
#endif

// xSTATVFS (struct and function)
#if xOS_ENV_WIN
    xNA
#else
    #if xOS_FREEBSD
        #define xSTATVFS            statvfs
        #define xSTATVFS_F_FRSIZE   f_frsize
    #else
        #define xSTATVFS            statfs64
        #define xSTATVFS_F_FRSIZE   f_bsize
    #endif
#endif
    ///< filesystem statfs (struct and function)


/*******************************************************************************
*    implementation missing functions
*
*******************************************************************************/

xNAMESPACE_BEGIN(NxLib)

// xGETTIMEOFDAY
#if xOS_ENV_WIN
    struct timezone
        /// for gettimeofday
    {
        int_t tz_minuteswest; ///< minutes W of Greenwich
        int_t tz_dsttime;     ///< type of dst correction
    };

    inline int_t getTimeOfDay(timeval *tv, timezone *tz) xWARN_UNUSED_RV;
        ///< porting from Linux gettimeofday

    #define xGETTIMEOFDAY           getTimeOfDay
#else
    #define xGETTIMEOFDAY           gettimeofday
#endif
    ///< implementation gettimeofday

// xSTD_CLOCK
#if   xOS_ENV_WIN
    #define xSTD_CLOCK              std::clock
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        #define xSTD_CLOCK          std::clock
    #elif xOS_FREEBSD
        inline std::clock_t clock() xWARN_UNUSED_RV;
            ///< get std::clock_t (http://bugs.vcmi.eu/view.php?id=719)

        #define xSTD_CLOCK          clock
    #endif
#elif xOS_ENV_MAC
    #define xSTD_CLOCK              std::clock
#endif
    ///< implementation std::clock

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "xFunctions.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_xFunctionsH
