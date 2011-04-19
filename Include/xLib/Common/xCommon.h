/****************************************************************************
* Class name:  CxCommon
* Description: common header for xLib
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     23.12.2010 23:24:26
*
*****************************************************************************/


#ifndef xLib_Common_xCommonH
#define xLib_Common_xCommonH
//---------------------------------------------------------------------------
#include <xLib/Common/xConfig.h>


#ifndef __cplusplus
    #error xLib: require C++ compilation (use a .cpp suffix)
#endif


/****************************************************************************
*	Predefined xLib macros
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: OS family (http://predef.sourceforge.net/preos.html)
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
	#define xOS_WIN
    ////#pragma message("  --- xLib: xOS_WIN ---")
#elif defined(linux) || defined(__linux)
	#define xOS_LINUX
    ////#pragma message("  --- xLib: xOS_LINUX ---")
#elif defined(__FreeBSD__)
    #define xOS_FREEBSD
    #pragma message("  --- xLib: xOS_FREEBSD ---")
    ////#error xLib: xOS_FREEBSD
#else
    #define xOS_UNSUPPORTED
    #pragma message("  --- xLib: xOS_UNSUPPORTED ---")
    #error xLib: unsupported OS
#endif
//---------------------------------------------------------------------------
//DONE: OS architecture (http://predef.sourceforge.net/preos.html)
#if defined(i386)    || defined(__i386__) || defined(__i486__) || defined(__i586__)      || defined(__i686__) || defined(__i386)  || \
    defined(_M_IX86) || defined(__X86__)  || defined(_X86_)    || defined(__THW_INTEL__) || defined(__I86__)  || defined(__I86__) || defined(__INTEL__)

    #define xARCHITECTURE_32BIT
    ////#pragma message("  --- xLib: xARCHITECTURE_32BIT ---")
#elif defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || \
      defined(__ia64__)  || defined(_IA64)   || defined(__IA64__)   || defined(__ia64)   || defined(_M_IA64)

    #define xARCHITECTURE_64BIT
    ////#pragma message("  --- xLib: xARCHITECTURE_64BIT ---")
#else
    #define xARCHITECTURE_UNSUPPORTED

    #pragma message("  --- xLib: xARCHITECTURE_UNSUPPORTED ---")
    #error xLib: unsupported architectures
#endif
//---------------------------------------------------------------------------
//C library
#include <stdio.h>
#include <stdlib.h>
#include <cctype>
#include <cstring>
#include <ctime>
#include <errno.h>
#include <stdarg.h>
#include <time.h>
#include <stddef.h>
#include <math.h>
#if defined(xIS_STL_ASSERTING)
    #include <assert.h>
#endif

//stl
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <utility>
#include <iomanip>
#include <cerrno>
#include <limits>
#include <stdexcept>

//POSIX
#include <fcntl.h>              //File opening, locking and other operations.
#include <sys/stat.h>           //File information (stat et al.).
#include <sys/types.h>          //Various data types used elsewhere.
//---------------------------------------------------------------------------
#if defined(UNICODE) || defined(_UNICODE)
    #define xTEXT(x)                         L##x
    #define xT(x)					         xTEXT(x)

    typedef wchar_t                          TCHAR;
    typedef wchar_t *                        LPTSTR;
    typedef const wchar_t *                  LPCTSTR;

	#define tcin					         std::wcin
	#define tcout					         std::wcout
    #define tcerr                            std::wcerr
    #define tclog                            std::wclog
	#define tendl                            std::endl

#define _ttmpnam    _wtmpnam

    ////#pragma message("  --- xLib: xUNICODE ---")
#else
    #define xTEXT(x)                         x
    #define xT(x)					         xTEXT(x)

    typedef char                             TCHAR;
    typedef char *                           LPTSTR;
    typedef const char *                     LPCTSTR;
    typedef char *                           LPSTR;   //ansi
    typedef const char *                     LPCSTR;  //ansi

	#define tcin                             std::cin
	#define tcout                            std::cout
    #define tcerr                            std::cerr
    #define tclog                            std::clog
	#define tendl                            std::endl

#define _ttmpnam    tmpnam

    ////#pragma message("  --- xLib: xANSI ---")
#endif  /*_UNICODE*/

typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >                         tString;
typedef std::basic_string<unsigned char, std::char_traits<unsigned char>, std::allocator<unsigned char> > uString;

typedef std::basic_istream<TCHAR, std::char_traits<TCHAR> >                                               tistream;
typedef std::basic_ostream<TCHAR, std::char_traits<TCHAR> >                                               tostream;
typedef std::basic_iostream<TCHAR, std::char_traits<TCHAR> >                                              tiostream;

typedef std::basic_istringstream<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >                  tistringstream;
typedef std::basic_ostringstream<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >                  tostringstream;
typedef std::basic_stringstream<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >                   tstringstream;

typedef std::basic_ifstream<TCHAR, std::char_traits<TCHAR> >                                              tifstream;
typedef std::basic_ofstream<TCHAR, std::char_traits<TCHAR> >                                              tofstream;
typedef std::basic_fstream<TCHAR, std::char_traits<TCHAR> >                                               tfstream;
//---------------------------------------------------------------------------
//Automatically include the xLib namespace, define xNO_USING_NAMESPACE to skip this step
namespace NxLib {}
#ifndef xNO_USING_NAMESPACE
    using namespace NxLib;
#endif
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
    #include <xLib/Common/Win/xCommon_Win.h>
#elif defined(xOS_LINUX)
    #include <xLib/Common/Linux/xCommon_Linux.h>
#endif
//---------------------------------------------------------------------------
#include <xLib/Common/xLinking.h>
#include <xLib/Common/CxMacros.h>
#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxNonCopyable.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Common/CxString.h>
//---------------------------------------------------------------------------
#endif  //xLib_Common_xCommonH
