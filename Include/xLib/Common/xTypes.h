/****************************************************************************
* Class name:  xTypes
* Description: types
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     20.05.2011
*
*****************************************************************************/


#ifndef xLib_Common_xTypesH
#define xLib_Common_xTypesH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xUNICODE)
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

//qualifiers
#if defined(xOS_WIN)
    #ifdef xARCHITECTURE_64BIT
        #define xPR_SIZET xT("I")
        #define xPR_I64d  xT("I64d")
        #define xPR_I64u  xT("I64u")
        #define xPR_I64x  xT("I64x")
    #else
        #define xPR_SIZET xT("")
    #endif
#elif defined(xOS_LINUX)
    #ifdef xARCHITECTURE_64BIT
        #define xPR_SIZET xT("z")
        #define xPR_I64d  xT("lld")
        #define xPR_I64u  xT("llu")
        #define xPR_I64x  xT("llx")
    #else
        #define xPR_SIZET xT("z")
    #endif
#endif



#if defined(xOS_WIN)
    // win defines
#elif defined(xOS_LINUX)
    #if !defined(BOOL)
        typedef enum { FALSE = 0, TRUE = 1 } BOOL;
    #endif

    typedef void                   VOID;
    typedef void *                 LPVOID;

    typedef int                    INT;
    typedef short int              SHORT;
    typedef long int               LONG;
    typedef long long int          LONGLONG;

    typedef unsigned int           UINT;
    typedef unsigned short int     USHORT;
    typedef unsigned long int      ULONG;
    typedef unsigned long long int ULONGLONG;

    typedef float                  FLOAT;
    typedef double                 DOUBLE;

    typedef char                   CHAR;
    typedef unsigned char          UCHAR;

    #if defined(xUNICODE)
        #define _tmain      wmain
        #define _ftprintf   fwprintf
        #define _tasctime   _wasctime
        #define _tfopen     _wfopen
        #define _tsetlocale _wsetlocale
        #define _vsntprintf _vsnwprintf
        #define _tfreopen   _wfreopen
        #define _tperror    _wperror
        #define _vstprintf  _vswprintf
        #define _vtprintf   vwprintf
        #define _vftprintf  vfwprintf
        #define _gettc      getwc
        #define _putts      _putws
        #define _puttchar   putwchar
        #define _taccess    _waccess
        #define _getts      _getws
        #define _gettchar   getwchar
        #define _tsystem    _wsystem
        #define _ttmpnam    _wtmpnam
        #define _tmkstemp   mkstemp         //TODO: need unicode version
        #define _trename    _wrename
        #define _tunlink    _wunlink
        #define _tremove    _wremove
        #define _fputts     fputws
        #define _ungettc    ungetwc
        #define _fputtc     fputwc
        #define _fgetts     fgetws
        #define _tcslen     wcslen
        #define _tchmod     _wchmod
        #define _totlower   towlower
        #define _totupper   towupper

        typedef addrinfo    ADDRINFOT;
    #else
        #define _tmain      main
        #define _ftprintf   fprintf
        #define _tasctime   asctime
        #define _tfopen     fopen
        #define _tsetlocale setlocale
        #define _vsntprintf vsnprintf
        #define _tfreopen   freopen
        #define _tperror    perror
        #define _vstprintf  vsprintf
        #define _vtprintf   vprintf
        #define _vftprintf  vfprintf
        #define _gettc      getc
        #define _putts      puts
        #define _puttchar   putchar
        #define _taccess    access
        #define _getts      gets
        #define _gettchar   getchar
        #define _tsystem    system
        #define _ttmpnam    tmpnam
        #define _tmkstemp   mkstemp
        #define _trename    rename
        #define _tunlink    unlink
        #define _tremove    remove
        #define _fputts     fputs
        #define _ungettc    ungetc
        #define _fputtc     fputc
        #define _fgetts     fgets
        #define _tcslen     strlen
        #define _tchmod     chmod
        #define _totlower   tolower
        #define _totupper   toupper

        typedef addrinfo    ADDRINFOT;
    #endif //xUNICODE
#endif
//---------------------------------------------------------------------------
#endif  //xLib_Common_xTypesH
