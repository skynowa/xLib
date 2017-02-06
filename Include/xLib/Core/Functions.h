/**
 * \file  Functions.h
 * \brief function macroses
 */


#pragma once

#if xUNICODE
    #include "Platform/Functions_unicode.h"
#else
    #include "Platform/Functions_ansi.h"
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
    #if xUNICODE
        #define xGETADDRINFO    xl::core::getaddrinfoW
    #else
        #define xGETADDRINFO    ::getaddrinfo
    #endif
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
    #if xUNICODE
        #define xGETNAMEINFO    xl::core::getnameinfoW
    #else
        #define xGETNAMEINFO    ::getnameinfo
    #endif
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

#if cmOPTION_PROJECT_HEADER_ONLY
    #include "Functions.cpp"
#endif
