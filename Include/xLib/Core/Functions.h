/**
 * \file  Functions.h
 * \brief function macroses
 */


#pragma once

#if xUNICODE
    #include "Platform/Functions_unicode.h"
#else
    #include "Platform/Functions_ansi.h"
#endif
//-------------------------------------------------------------------------------------------------
///\def xDUP2
///\{
#if   xENV_WIN
	#define xDUP2 ::_dup2
#elif xENV_UNIX
	#define xDUP2 ::dup2
#endif
///\}

///\def xLOCKING
///\{
#if   xCOMPILER_MINGW
	#define xLOCKING ::_locking
#elif xCOMPILER_MS
	#define xLOCKING ::_locking
#elif xCOMPILER_GNUC
	#define xLOCKING ::lockf
#else
	#define xLOCKING ::locking
#endif
///\}

///\def xCHSIZE
///\{
#if   xCOMPILER_MINGW
	#define xCHSIZE ::chsize
#elif xCOMPILER_MS
	#define xCHSIZE ::_chsize_s
#elif xCOMPILER_GNUC
	#define xCHSIZE ::ftruncate
#else
	#define xCHSIZE ::chsize
#endif
///\}

///\def xIOCTLSOCKET
///\{
#if   xENV_WIN
	#define xIOCTLSOCKET ::ioctlsocket
#elif xENV_UNIX
	#define xIOCTLSOCKET ::ioctl
#endif
///\}

///\def xADDR_INFO_GET
///\{
#if   xCOMPILER_MINGW
	#define xADDR_INFO_GET     ::getaddrinfo
#elif xCOMPILER_MS
	#define xADDR_INFO_GET     ::GetAddrInfo
#elif xCOMPILER_GNUC
	#if xUNICODE
		#define xADDR_INFO_GET xl::core::getaddrinfoW
	#else
		#define xADDR_INFO_GET ::getaddrinfo
	#endif
#else
	#define xADDR_INFO_GET     ::getaddrinfo
#endif
///\}

///\def xADDR_INFO_FREE
///\{
#if   xENV_WIN
	#if xCOMPILER_MS
		#define xADDR_INFO_FREE ::FreeAddrInfo
	#else
		#define xADDR_INFO_FREE ::freeaddrinfo
	#endif
#elif xENV_UNIX
	#define xADDR_INFO_FREE ::freeaddrinfo
#endif
///\}

///\def xNAME_INFO_GET
///\{
#if   xCOMPILER_MINGW
	#define xNAME_INFO_GET     ::getnameinfo
#elif xCOMPILER_MS
	#define xNAME_INFO_GET     ::GetNameInfo
#elif xCOMPILER_GNUC
	#if xUNICODE
		#define xNAME_INFO_GET xl::core::getnameinfoW
	#else
		#define xNAME_INFO_GET ::getnameinfo
	#endif
#else
	#define xNAME_INFO_GET     ::getnameinfo
#endif
///\}

///\def   xSTATVFS
///\brief Filesystem statfs - struct and function
///\{
#if   xENV_WIN
	xNA
#elif xENV_UNIX
	xNA

	#if   xENV_LINUX
		#if   xOS_ANDROID
			#define xSTATVFS ::statfs
		#elif xOS_LINUX
			#define xSTATVFS ::statfs64
		#endif
	#elif xENV_BSD
		#define xSTATVFS     ::statvfs
	#elif xENV_APPLE
		#define xSTATVFS     statfs	/// TODO: ::statfs64
	#endif
#endif
///\}

///\def xISATTY
///\{
#if   xENV_WIN
	#define xISATTY ::_isatty
#elif xENV_UNIX
	#define xISATTY ::isatty
#endif
///\}

///\def xFILENO
///\{
#if   xENV_WIN
	#define xFILENO ::_fileno
#elif xENV_UNIX
	#define xFILENO ::fileno
#endif
///\}

#if xENV_APPLE
///\name Sem API
///\{
int sem_init(sem_t *psem, int flags, unsigned count);
int sem_destroy(sem_t *psem);
int sem_post(sem_t *psem);
int sem_trywait(sem_t *psem);
int sem_wait(sem_t *psem);
int sem_timedwait(sem_t *psem, const struct timespec *abstim);
///\}
#endif
//-------------------------------------------------------------------------------------------------
// Custom
#include <string>

namespace xl
{

std::string demangleName(const char *nameRaw);
	///< Demangling names

}
//-------------------------------------------------------------------------------------------------
