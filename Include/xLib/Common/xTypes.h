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
#else
    #define xTEXT(x)        x
    #define xT(x)           xTEXT(x)

    typedef char            TCHAR;
    typedef char *          LPTSTR;
    typedef const char *    LPCTSTR;
    typedef char *          LPSTR;
    typedef const char *    LPCSTR;
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

#if defined(xOS_ENV_WIN)
	#if defined(xCOMPILER_MINGW32)
		typedef addrinfo           ADDRINFOT;
	#endif
#elif defined(xOS_ENV_UNIX)
    #if !defined(BOOL)
        typedef enum { FALSE = 0, TRUE = 1 } BOOL;
    #endif

    typedef void                   VOID;
    typedef void *                 LPVOID;

    typedef signed int             INT;
    typedef signed short int       SHORT;
    typedef signed long int        LONG;
    typedef signed long long int   LONGLONG;

    typedef unsigned int           UINT;
    typedef unsigned short int     USHORT;
    typedef unsigned long int      ULONG;
    typedef unsigned long long int ULONGLONG;

    typedef char                   CHAR;
    typedef unsigned char          UCHAR;

    typedef addrinfo               ADDRINFOT;
#endif
//---------------------------------------------------------------------------
#endif  //xLib_Common_xTypesH
