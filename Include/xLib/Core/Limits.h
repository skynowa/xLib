/**
 * \file  Limits.h
 * \brief numeric limits
 */


#pragma once

#if   xENV_UNIX
    #include <sys/socket.h>
#elif xENV_WIN
    #include <winsock2.h>
#endif
//-------------------------------------------------------------------------------------------------
///\def   xHOST_NAME_MAX
///\brief max host name length
///\{
#if   xENV_WIN
	#if defined(MAX_COMPUTERNAME_LENGTH)
		#define xHOST_NAME_MAX ( MAX_COMPUTERNAME_LENGTH )
	#else
		#define xHOST_NAME_MAX ( 15 )
			///< custom define
	#endif
#elif xENV_UNIX
	#if   defined(HOST_NAME_MAX)
		#define xHOST_NAME_MAX ( HOST_NAME_MAX )
	#elif defined(MAXHOSTNAMELEN)
		#define xHOST_NAME_MAX ( MAXHOSTNAMELEN )
	#else
		#define xHOST_NAME_MAX ( 256 )
			///< custom define
	#endif
#endif
///\}
//-------------------------------------------------------------------------------------------------
///\def   xUSER_NAME_MAX
///\brief max user name length
///\{
#if   xENV_WIN
	#define xUSER_NAME_MAX ( UNLEN )
#elif xENV_UNIX
	#if defined(L_cuserid)
		#define xUSER_NAME_MAX ( L_cuserid )
	#else
		#define xUSER_NAME_MAX ( 9 )
			///< custom define
	#endif
#endif
///\}
//-------------------------------------------------------------------------------------------------
///\def   xLINE_MAX
///\brief maximum length of a utility's input line, either from standard input or from a file
///\{
#if   xENV_WIN
	#define xLINE_MAX ( 2048 )
		///< custom define
#elif xENV_UNIX
	#if   defined(LINE_MAX)
		#define xLINE_MAX ( LINE_MAX )
	#elif defined(_SC_LINE_MAX)
		#define xLINE_MAX ( _SC_LINE_MAX )
	#else
		#define xLINE_MAX ( 2048 )
			///< custom define
	#endif
#endif
///\}
//-------------------------------------------------------------------------------------------------
///\def   xPAGE_SIZE
///\brief file system page size
///\{
#if   xENV_WIN
	xNA
#elif xENV_UNIX
	#if   defined(_SC_PAGESIZE)
		#define xPAGE_SIZE ( _SC_PAGESIZE )
	#elif defined(_SC_PAGE_SIZE)
		#define xPAGE_SIZE ( _SC_PAGE_SIZE )
	#else
		#define xPAGE_SIZE ( 30 )
			///< custom define
	#endif
#endif
///\}
//-------------------------------------------------------------------------------------------------
///\def   xTIMEOUT_INFINITE
///\brief infinite timeout
///\{
#if   xENV_WIN
	#define xTIMEOUT_INFINITE ( INFINITE )
#elif xENV_UNIX
	#define xTIMEOUT_INFINITE ( ~(0UL) )
#endif
///\}
//-------------------------------------------------------------------------------------------------
///\def   xSOCKET_LISTEN_CONNECTIONS_MAX
///\brief Maximum queue length specifiable by listen
///\{
#if defined(SOMAXCONN)
	#define xSOCKET_LISTEN_CONNECTIONS_MAX ( SOMAXCONN )
#else
	#define xSOCKET_LISTEN_CONNECTIONS_MAX ( 4096 )
		///< custom define
#endif
///\}
//-------------------------------------------------------------------------------------------------
///\name Socket limits
///\{
#define xSOCKET_PORT_MIN ( 1 )
	///< socket minimum port number
#define xSOCKET_PORT_MAX ( 65535 )
	///< socket maximum port number
///\}
//-------------------------------------------------------------------------------------------------
///\name Custom defines
///\{
#define xCUSTOM_SEMAPHORE_VALUE_MAX_WIN          (LONG_MAX)
    ///< semaphore maximum value (tested on Win7 x64)
#define xCUSTOM_SYSCONF_SC_GETPW_R_SIZE_MAX_UNIX (16384L)
    ///< as \code ::sysconf(_SC_GETPW_R_SIZE_MAX) \endcode

// TODO: [skynowa] xTHREAD_NAME_LENGTH_MAX - fix unicode version
#if   xENV_WIN
	#define xTHREAD_NAME_LENGTH_MAX ( static_cast<std::size_t>(32) )
#elif xENV_UNIX
	#define xTHREAD_NAME_LENGTH_MAX ( static_cast<std::size_t>(16) )
#endif
	///< thread name max length
///\}
//-------------------------------------------------------------------------------------------------
