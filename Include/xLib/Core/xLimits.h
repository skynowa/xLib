/**
 * \file  xLimits.h.h
 * \brief
 */


#pragma once

#ifndef xLib_xLimitsH
#define xLib_xLimitsH
//-------------------------------------------------------------------------------------------------
// xHOST_NAME_MAX
#if   xOS_ENV_WIN
    #if defined(MAX_COMPUTERNAME_LENGTH)
        #define xHOST_NAME_MAX \
            ( MAX_COMPUTERNAME_LENGTH )
    #else
        #define xHOST_NAME_MAX \
            ( 15 ) // custom define
    #endif
#elif xOS_ENV_UNIX
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
// xPATH_MAX
#define xPATH_MAX \
    ( CxPath::maxSize() )
    ///< max path length

//-------------------------------------------------------------------------------------------------
// xNAME_MAX
#define xNAME_MAX \
    ( CxPath::nameMaxSize() )
    ///< max file name length

//-------------------------------------------------------------------------------------------------
// xLINE_MAX
#if   xOS_ENV_WIN
    #define xLINE_MAX \
    ( 2048 ) // custom define
#elif xOS_ENV_UNIX
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
#if   xOS_ENV_WIN
    #if   xCOMPILER_MS
        #define xENV_MAX \
            ( _MAX_ENV )
    #else
        #define xENV_MAX \
            ( 32767 ) // custom define
    #endif
#elif xOS_ENV_UNIX
    #define xENV_MAX \
        ( 32767 ) // custom define
#endif
    ///< maximum permissible string length of an environmental variable

//-------------------------------------------------------------------------------------------------
// xSTACK_TRACE_FRAMES_MAX
#if   xOS_ENV_WIN
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
#elif xOS_ENV_UNIX
    #define xSTACK_TRACE_FRAMES_MAX \
        ( 256 )     // custom define, this should be enough
#endif
    ///< maximum frames for stack trace

//-------------------------------------------------------------------------------------------------
// xSEMAPHORE_VALUE_MAX
#if   xOS_ENV_WIN
    #define xSEMAPHORE_VALUE_MAX \
        ( LONG_MAX ) // LONG, custom define (tested on Win7 x64)
#elif xOS_ENV_UNIX
    #define xSEMAPHORE_VALUE_MAX \
        ( SEM_VALUE_MAX ) // int_t
#endif
    ///< semaphore maximum value

//-------------------------------------------------------------------------------------------------
// xPAGE_SIZE
#if   xOS_ENV_WIN
    xNA
#elif xOS_ENV_UNIX
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
#if   xOS_ENV_WIN
    #define xTIMEOUT_INFINITE \
        ( INFINITE )
#elif xOS_ENV_UNIX
    #define xTIMEOUT_INFINITE \
        ( ~(0UL) )
#endif
    ///< infinite timeout

//-------------------------------------------------------------------------------------------------
#endif // xLib_xLimitsH
