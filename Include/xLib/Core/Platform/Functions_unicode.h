/**
 * \file  Functions_unicode.h
 * \brief function macroses
 */


#pragma once

    #define tcin          wcin
    #define tcout         wcout
    #define tcerr         wcerr
    #define tclog         wclog
    #define xTEOF         WEOF

    #define xTFPRINTF     std::fwprintf
    #define xTASCTIME     std::_wasctime
    #define xTLOCALE      ::locale_t

#if   xENV_WIN
    #define xTMAIN        wmain
    #define xTVSNPRINTF   ::_vsnwprintf
    #define xTSETLOCALE   ::_wsetlocale
    #define xTFOPEN       std::_wfopen
    #define xTFDOPEN      ::_wfdopen
    #define xTFREOPEN     std::_wfreopen
    #define xTACCESS      ::_waccess
    #define xTSYSTEM      std::_wsystem
#elif xENV_UNIX
    #define xTMAIN        main
    #define xTVSNPRINTF   ::vswprintf
    #define xTFOPEN       xl::core::fopenW
    #define xTFDOPEN      xl::core::fdopenW
    #define xTFREOPEN     xl::core::freopenW
    #define xTSETLOCALE   xl::core::setlocaleW
    #define xTACCESS      xl::core::accessW
    #define xTSYSTEM      xl::core::systemW
#endif

    #define xTPERROR      std::_wperror
    #define xTVSPRINTF    std::_vswprintf
    #define xTVPRINTF     std::vwprintf
    #define xTVFPRINTF    std::vfwprintf
    #define xTFGETC       std::getwc
    #define xTPUTS        std::_putws
    #define xTPUTCHAR     std::putwchar

    #define xTGETS        std::_getws
    #define xTGETCHAR     std::getwchar
    #define xTTMPNAM      std::_wtmpnam
    #define xSTRFTIME     std::wcsftime

    // xTMKSTEMP
#if   xCOMPILER_MINGW
    #define xTMKSTEMP     ::_wmktemp
#elif xCOMPILER_MS
    #define xTMKSTEMP     ::_tmktemp_s
#elif xCOMPILER_CODEGEAR
    #define xTMKSTEMP     ::_wmktemp
#elif xCOMPILER_GNUC
    #define xTMKSTEMP     xl::core::mkstempW
#else
    #define xTMKSTEMP     std::mkstemp
#endif

#if   xENV_WIN
    #define xTREMOVE      std::_wremove
    #define xTRENAME      std::_wrename
    #define xTUNLINK      ::_wunlink
#elif xENV_UNIX
    #define xTUNLINK      xl::core::unlinkW
    #define xTRENAME      xl::core::renameW
    #define xTREMOVE      xl::core::removeW
#endif

    #define xTFPUTS       std::fputws
    #define xTUNGETC      std::ungetwc
    #define xTFPUTC       std::fputwc
    #define xTFGETS       std::fgetws
    #define xTSTRLEN      std::wcslen

#if   xCOMPILER_MINGW
    #define xTCHMOD       ::_wchmod
#elif xCOMPILER_MS
    #define xTCHMOD       ::_wchmod
#elif xCOMPILER_CODEGEAR
    #define xTCHMOD       ::_wchmod
#elif xCOMPILER_CLANG
    #define xTCHMOD       xl::core::chmodW
#elif xCOMPILER_GNUC
    #define xTCHMOD       xl::core::chmodW
#else
    #define xTCHMOD       ::_wchmod
#endif

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
    #define xTSTAT        ::_wstat
#elif xCOMPILER_MS
    #define xTSTAT        ::_tstat64
#elif xCOMPILER_CODEGEAR
    #define xTSTAT        ::_tstat
#elif xCOMPILER_GNUC
    #define xTSTAT        xl::core::statW
#else
    #define xTSTAT        ::_wstat
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
    #define xSTRERROR     ::_wstrerror
#endif

    // chars
    #define xTISALNUM     ::iswalnum
    #define xTISALPHA     ::iswalpha
    #define xTISCNTRL     ::iswcntrl
    #define xTISDIGIT     ::iswdigit
    #define xTISXDIGIT    ::iswxdigit
    #define xTISGRAPH     ::iswgraph
    #define xTISPRINT     ::iswprint
    #define xTISPUNCT     ::iswpunct
    #define xTISSPACE     ::iswspace
    #define xTISLOWER     ::iswlower
    #define xTISUPPER     ::iswupper
    #define xTTOLOWER     ::towlower
    #define xTTOUPPER     ::towupper

    // chars (locale)
    #define xTISALNUM_L   ::iswalnum_l
    #define xTISALPHA_L   ::iswalpha_l
    #define xTISCNTRL_L   ::iswcntrl_l
    #define xTISDIGIT_L   ::iswdigit_l
    #define xTISXDIGIT_L  ::iswxdigit_l
    #define xTISGRAPH_L   ::iswgraph_l
    #define xTISPRINT_L   ::iswprint_l
    #define xTISPUNCT_L   ::iswpunct_l
    #define xTISSPACE_L   ::iswspace_l
    #define xTISLOWER_L   ::iswlower_l
    #define xTISUPPER_L   ::iswupper_l
    #define xTTOLOWER_L   ::towlower_l
    #define xTTOUPPER_L   ::towupper_l
