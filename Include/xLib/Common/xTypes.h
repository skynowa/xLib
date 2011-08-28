/**
 * \file  xTypes.h
 * \brief types
 */


#ifndef xLib_Common_xTypesH
#define xLib_Common_xTypesH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xUNICODE)
    #define xTEXT(x)        L##x
    #define xT(x)           xTEXT(x)

    typedef wchar_t         TCHAR;
    typedef wchar_t *       LPTSTR;
    typedef const wchar_t * LPCTSTR;

    #define tcin            wcin
    #define tcout           wcout
    #define tcerr           wcerr
    #define tclog           wclog

    #define _ttmpnam        _wtmpnam
    #define TEOF            WEOF
#else
    #define xTEXT(x)        x
    #define xT(x)           xTEXT(x)

    typedef char            TCHAR;
    typedef char *          LPTSTR;
    typedef const char *    LPCTSTR;
    typedef char *          LPSTR;   //ansi
    typedef const char *    LPCSTR;  //ansi

    #define tcin            cin
    #define tcout           cout
    #define tcerr           cerr
    #define tclog           clog

    #define _ttmpnam        tmpnam
    #define TEOF            EOF
#endif //xUNICODE

namespace std {
	typedef basic_string<TCHAR,         char_traits<TCHAR>,         allocator<TCHAR> >         tstring;
	typedef basic_string<unsigned char, char_traits<unsigned char>, allocator<unsigned char> > ustring;
	
	typedef basic_istream <TCHAR, char_traits<TCHAR> >                                         tistream;
	typedef basic_ostream <TCHAR, char_traits<TCHAR> >                                         tostream;
	typedef basic_iostream<TCHAR, char_traits<TCHAR> >                                         tiostream;
	
	typedef basic_istringstream<TCHAR, char_traits<TCHAR>, allocator<TCHAR> >                  tistringstream;
	typedef basic_ostringstream<TCHAR, char_traits<TCHAR>, allocator<TCHAR> >                  tostringstream;
	typedef basic_stringstream <TCHAR, char_traits<TCHAR>, allocator<TCHAR> >                  tstringstream;
	
	typedef basic_ifstream<TCHAR, char_traits<TCHAR> >                                         tifstream;
	typedef basic_ofstream<TCHAR, char_traits<TCHAR> >                                         tofstream;
	typedef basic_fstream <TCHAR, char_traits<TCHAR> >                                         tfstream;
} //namespace std

    typedef float                  FLOAT;
    typedef double                 DOUBLE;

#if defined(xOS_WIN)
	#if defined(xCOMPILER_MINGW32)
		//sockets
		typedef addrinfo           ADDRINFOT;
	#endif //xUNICODE
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

    typedef char                   CHAR;
    typedef unsigned char          UCHAR;

    #if defined(xUNICODE)
        #define _tmain      wmain
        #define _ftprintf   fwprintf
        #define _tasctime   _wasctime
        #define _tfopen     _wfopen
        #define _tfdopen    _wfdopen
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
        #define _tstat      _wstat

        //chars
        #define _istalnum   iswalnum
        #define _istalpha   iswalpha
        #define _istcntrl   iswcntrl
        #define _istdigit   iswdigit
        #define _istxdigit  iswxdigit
        #define _istgraph   iswgraph
        #define _istprint   iswprint
        #define _istpunct   iswpunct
        #define _istspace   iswspace
        #define _istlower   iswlower
        #define _istupper   iswupper
        #define _totlower   towlower
        #define _totupper   towupper

        //sockets
        typedef addrinfo    ADDRINFOT;
    #else
        #define _tmain      main
        #define _ftprintf   fprintf
        #define _tasctime   asctime
        #define _tfopen     fopen
        #define _tfdopen    fdopen
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
        #define _tstat      stat

        //chars
        #define _istalnum   isalnum
        #define _istalpha   isalpha
        #define _istcntrl   iscntrl
        #define _istdigit   isdigit
        #define _istxdigit  isxdigit
        #define _istgraph   isgraph
        #define _istprint   isprint
        #define _istpunct   ispunct
        #define _istspace   isspace
        #define _istlower   islower
        #define _istupper   isupper
        #define _totlower   tolower
        #define _totupper   toupper

        //sockets
        typedef addrinfo    ADDRINFOT;
    #endif //xUNICODE


    //For compilers lacking Win64 support
    #if 0 && defined(xOS_WIN)
        #if !defined(GetWindowLongPtr)
            #define GetWindowLongPtr   GetWindowLong
            #define SetWindowLongPtr   SetWindowLong
            #define GWLP_WNDPROC       GWL_WNDPROC
            #define GWLP_HINSTANCE     GWL_HINSTANCE
            #define GWLP_ID            GWL_ID
            #define GWLP_USERDATA      GWL_USERDATA
            #define DWLP_DLGPROC       DWL_DLGPROC
            #define DWLP_MSGRESULT     DWL_MSGRESULT
            #define DWLP_USER          DWL_USER
            #define DWORD_PTR          DWORD
            #define LONG_PTR           LONG
            #define ULONG_PTR          LONG
        #endif
            #ifndef GetClassLongPtr
            #define GetClassLongPtr    GetClassLong
            #define SetClassLongPtr    SetClassLong
            #define GCLP_HBRBACKGROUND GCL_HBRBACKGROUND
            #define GCLP_HCURSOR       GCL_HCURSOR
            #define GCLP_HICON         GCL_HICON
            #define GCLP_HICONSM       GCL_HICONSM
            #define GCLP_HMODULE       GCL_HMODULE
            #define GCLP_MENUNAME      GCL_MENUNAME
            #define GCLP_WNDPROC       GCL_WNDPROC
        #endif
    #endif
    
#endif
//---------------------------------------------------------------------------
#endif  //xLib_Common_xTypesH
