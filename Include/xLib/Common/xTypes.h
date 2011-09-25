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

    #define xTTMPNAM        _wtmpnam
    #define xTEOF           WEOF
#else
    #define xTEXT(x)        x
    #define xT(x)           xTEXT(x)

    typedef char            TCHAR;
    typedef char *          LPTSTR;
    typedef const char *    LPCTSTR;
    typedef char *          LPSTR;
    typedef const char *    LPCSTR;

    #define tcin            cin
    #define tcout           cout
    #define tcerr           cerr
    #define tclog           clog

    #define xTTMPNAM        tmpnam
    #define xTEOF           EOF
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
#endif
//---------------------------------------------------------------------------
#endif  //xLib_Common_xTypesH
