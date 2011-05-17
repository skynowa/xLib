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
#ifndef __cplusplus
    #error xLib: require C++ compilation (use a .cpp suffix)
#endif

#include <xLib/Common/xConfig.h>


/****************************************************************************
*    Predefined macros
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: OS family (http://predef.sourceforge.net/preos.html)
#if (_WIN32 || _WIN64 || __WIN32__ || __TOS_WIN__ || __WINDOWS__)
    #define xOS_WIN
    //#pragma message("  --- xLib: xOS_WIN ---")
#elif (linux || __linux)
    #define xOS_LINUX
    //#pragma message("  --- xLib: xOS_LINUX ---")
#elif (__FreeBSD__)
    #define xOS_FREEBSD
    //#pragma message("  --- xLib: xOS_FREEBSD ---")
    #error xLib: xOS_FREEBSD
#else
    #define xOS_UNSUPPORTED
    //#pragma message("  --- xLib: xOS_UNSUPPORTED ---")
    #error xLib: unsupported OS
#endif
//---------------------------------------------------------------------------
//DONE: OS architecture (http://predef.sourceforge.net/preos.html)
#if (i386 || __i386__ || __i486__ || __i586__ || __i686__ || __i386 || _M_IX86 || __X86__ || _X86_ || __THW_INTEL__ || __I86__ || __I86__ || __INTEL__)
    #define xARCHITECTURE_32BIT
    //#pragma message("  --- xLib: xARCHITECTURE_32BIT ---")
#elif (__amd64__ || __amd64 || __x86_64__ || __x86_64 || _M_X64 || __ia64__  || _IA64 || __IA64__ || __ia64 || _M_IA64 )
    #define xARCHITECTURE_64BIT
    //#pragma message("  --- xLib: xARCHITECTURE_64BIT ---")
#else
    #define xARCHITECTURE_UNSUPPORTED
    //#pragma message("  --- xLib: xARCHITECTURE_UNSUPPORTED ---")
    #error xLib: unsupported architectures
#endif
//---------------------------------------------------------------------------
//DONE: Compilers
#if   (__MINGW32__)
    #define xCOMPILER_MINGW32
    //#pragma message("  --- xLib: xCOMPILER_MINGW32 ---")
#elif (_MSC_VER || _MSC_FULL_VER || _MSC_BUILD)
    #define xCOMPILER_MS
    //#pragma message("  --- xLib: xCOMPILER_MS ---")
#elif (__BORLANDC__ || __CODEGEARC__)
    #define xCOMPILER_CODEGEAR
    //#pragma message("  --- xLib: xCOMPILER_CODEGEAR ---")
#elif (__GNUC__)
    #define xCOMPILER_GNUC
    //#pragma message("  --- xLib: xCOMPILER_GNUC ---")
#else
    #define xCOMPILER_UNSUPPORTED
    //#pragma message("  --- xLib: xCOMPILER_UNSUPPORTED ---")
    #error xLib: unsupported compiler
#endif
//---------------------------------------------------------------------------
//DONE: unicode, ansi
#if (UNICODE || _UNICODE)
    #define xUNICODE
    //#pragma message("  --- xLib: xUNICODE ---")
#else
    #define xANSI
    //#pragma message("  --- xLib: xANSI ---")
#endif //UNICODE || _UNICODE
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

#if (xIS_STL_ASSERTING)
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
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
//---------------------------------------------------------------------------
#if (xUNICODE)
    #define xTEXT(x)                         L##x
    #define xT(x)                            xTEXT(x)

    typedef wchar_t                          TCHAR;
    typedef wchar_t *                        LPTSTR;
    typedef const wchar_t *                  LPCTSTR;

    #define tcin                             std::wcin
    #define tcout                            std::wcout
    #define tcerr                            std::wcerr
    #define tclog                            std::wclog
    #define tendl                            std::endl

    #define _ttmpnam                         _wtmpnam
#else
    #define xTEXT(x)                         x
    #define xT(x)                            xTEXT(x)

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

    #define _ttmpnam                         tmpnam
#endif //xUNICODE

typedef double DOUBLE;

typedef std::basic_string<TCHAR,         std::char_traits<TCHAR>,         std::allocator<TCHAR> >         tString;
typedef std::basic_string<unsigned char, std::char_traits<unsigned char>, std::allocator<unsigned char> > uString;

typedef std::basic_istream <TCHAR, std::char_traits<TCHAR> >                                              tistream;
typedef std::basic_ostream <TCHAR, std::char_traits<TCHAR> >                                              tostream;
typedef std::basic_iostream<TCHAR, std::char_traits<TCHAR> >                                              tiostream;

typedef std::basic_istringstream<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >                  tistringstream;
typedef std::basic_ostringstream<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >                  tostringstream;
typedef std::basic_stringstream <TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >                  tstringstream;

typedef std::basic_ifstream<TCHAR, std::char_traits<TCHAR> >                                              tifstream;
typedef std::basic_ofstream<TCHAR, std::char_traits<TCHAR> >                                              tofstream;
typedef std::basic_fstream <TCHAR, std::char_traits<TCHAR> >                                              tfstream;
//---------------------------------------------------------------------------
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
