/**
 * \file  Limits.h
 * \brief numeric limits
 */


#pragma once

#include <sys/socket.h>

//-------------------------------------------------------------------------------------------------
// xHOST_NAME_MAX
#if   xENV_WIN
    #if defined(MAX_COMPUTERNAME_LENGTH)
        #define xHOST_NAME_MAX \
            ( MAX_COMPUTERNAME_LENGTH )
    #else
        #define xHOST_NAME_MAX \
            ( 15 ) // custom define
    #endif
#elif xENV_UNIX
    #if   defined(HOST_NAME_MAX)
        #define xHOST_NAME_MAX \
            ( HOST_NAME_MAX )
    #elif defined(MAXHOSTNAMELEN)
        #define xHOST_NAME_MAX \
            ( MAXHOSTNAMELEN )
    #else
        #define xHOST_NAME_MAX \
            ( 256 ) // custom define
    #endif
#endif
    ///< max host name length
//-------------------------------------------------------------------------------------------------
// xUSER_NAME_MAX
#if   xENV_WIN
    #define xUSER_NAME_MAX \
        ( UNLEN )
#elif xENV_UNIX
    #define xUSER_NAME_MAX \
        ( L_cuserid )
#endif
    ///< max user name length
//-------------------------------------------------------------------------------------------------
// xPATH_MAX
#define xPATH_MAX \
    ( Path::maxSize() )
    ///< max path length
//-------------------------------------------------------------------------------------------------
// xNAME_MAX
#define xNAME_MAX \
    ( Path::nameMaxSize() )
    ///< max file name length
//-------------------------------------------------------------------------------------------------
// xLINE_MAX
#if   xENV_WIN
    #define xLINE_MAX \
    ( 2048 ) // custom define
#elif xENV_UNIX
    #if   defined(LINE_MAX)
        #define xLINE_MAX \
            ( LINE_MAX )
    #elif defined(_SC_LINE_MAX)
        #define xLINE_MAX \
            ( _SC_LINE_MAX )
    #else
        #error xLib: xLINE_MAX not defined
    #endif
#endif
    ///< maximum length of a utility's input line, either from standard input or from a file
//-------------------------------------------------------------------------------------------------
// xENV_MAX
#if   xENV_WIN
    #if   xCOMPILER_MS
        #define xENV_MAX \
            ( _MAX_ENV )
    #else
        #define xENV_MAX \
            ( 32767 ) // custom define
    #endif
#elif xENV_UNIX
    #define xENV_MAX \
        ( 32767 ) // custom define
#endif
    ///< maximum permissible string length of an environmental variable
//-------------------------------------------------------------------------------------------------
// xSTACK_TRACE_FRAMES_MAX
#if   xENV_WIN
    #if (xOS_WIN_VER <= xOS_WIN_S03)
       /**
        * MSDN: Windows Server 2003 and Windows XP:
        *       The sum of the FramesToSkip and FramesToCapture
        *       parameters must be less than 63
        */
        #define xSTACK_TRACE_FRAMES_MAX \
            ( 62UL )
    #else
        #define xSTACK_TRACE_FRAMES_MAX \
            ( USHRT_MAX )
    #endif
#elif xENV_UNIX
    #define xSTACK_TRACE_FRAMES_MAX \
        ( 256 )     // custom define, this should be enough
#endif
    ///< maximum frames for stack trace
//-------------------------------------------------------------------------------------------------
// xPAGE_SIZE
#if   xENV_WIN
    xNA
#elif xENV_UNIX
    #if   defined(_SC_PAGESIZE)
        #define xPAGE_SIZE \
            ( _SC_PAGESIZE )
    #elif defined(_SC_PAGE_SIZE)
        #define xPAGE_SIZE \
            ( _SC_PAGE_SIZE )
    #else
        #error xLib: xPAGE_SIZE not defined
    #endif
#endif
    ///< file system page size
//-------------------------------------------------------------------------------------------------
// xTIMEOUT_INFINITE
#if   xENV_WIN
    #define xTIMEOUT_INFINITE \
        ( INFINITE )
#elif xENV_UNIX
    #define xTIMEOUT_INFINITE \
        ( ~(0UL) )
#endif
    ///< infinite timeout
//-------------------------------------------------------------------------------------------------
// xSOCKET_LISTEN_CONNECTIONS_MAX
#if defined(SOMAXCONN)
    #define xSOCKET_LISTEN_CONNECTIONS_MAX \
            ( SOMAXCONN )
#else
    #error xLib: xSOCKET_LISTEN_CONNECTIONS_MAX not defined
#endif
    ///< Maximum queue length specifiable by listen
//-------------------------------------------------------------------------------------------------
// xSOCKET_PORT_MIN, xSOCKET_PORT_MAX
#define xSOCKET_PORT_MIN \
        ( 1 )
    ///< socket minimum port number
#define xSOCKET_PORT_MAX \
        ( 65535 )
    ///< socket maximum port number
//-------------------------------------------------------------------------------------------------
///@name Custom defines
///@{
#define xCUSTOM_SEMAPHORE_VALUE_MAX_WIN \
    (LONG_MAX)
    ///< semaphore maximum value (tested on Win7 x64)
#define xCUSTOM_SYSCONF_SC_GETPW_R_SIZE_MAX_UNIX \
    (16384L)
    ///< ::sysconf(_SC_GETPW_R_SIZE_MAX)

// xTHREAD_NAME_LENGTH_MAX
// TODO: [skynowa] xTHREAD_NAME_LENGTH_MAX - fix unicode version
#if   xENV_WIN
    #define xTHREAD_NAME_LENGTH_MAX \
        ( static_cast<std::size_t>(32) )
#elif xENV_UNIX
    #define xTHREAD_NAME_LENGTH_MAX \
        ( static_cast<std::size_t>(16) )
#endif
    ///< thread name max length
///@}
//-------------------------------------------------------------------------------------------------
