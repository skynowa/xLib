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
    #define xTEXT(x)               L##x
    #define xT(x)                  xTEXT(x)

    typedef wchar_t                TCHAR;
#else
    #define xTEXT(x)               x
    #define xT(x)                  xTEXT(x)

    typedef char                   TCHAR;
#endif //xUNICODE

    typedef float                  FLOAT;
    typedef double                 DOUBLE;

    #ifndef FALSE
        #define FALSE              0
    #endif

    #ifndef TRUE
        #define TRUE               1
    #endif

#if defined(xOS_ENV_WIN)
    #if defined(xCOMPILER_MINGW32)
        typedef addrinfo           ADDRINFOT;
    #endif
#elif defined(xOS_ENV_UNIX)
    typedef int                    BOOL;

    typedef void                   VOID;

    typedef char                   CHAR;
    typedef unsigned char          UCHAR;

    typedef signed int             INT;
    typedef signed short int       SHORT;
    typedef signed long int        LONG;
    typedef signed long long int   LONGLONG;

    typedef unsigned int           UINT;
    typedef unsigned short int     USHORT;
    typedef unsigned long int      ULONG;
    typedef unsigned long long int ULONGLONG;

    typedef addrinfo               ADDRINFOT;
#endif

namespace std {
    typedef basic_string<TCHAR, char_traits<TCHAR>, allocator<TCHAR> >        tstring;
    typedef basic_string<UCHAR, char_traits<UCHAR>, allocator<UCHAR> >        ustring;

    typedef basic_istream <TCHAR, char_traits<TCHAR> >                        tistream;
    typedef basic_ostream <TCHAR, char_traits<TCHAR> >                        tostream;
    typedef basic_iostream<TCHAR, char_traits<TCHAR> >                        tiostream;

    typedef basic_istringstream<TCHAR, char_traits<TCHAR>, allocator<TCHAR> > tistringstream;
    typedef basic_ostringstream<TCHAR, char_traits<TCHAR>, allocator<TCHAR> > tostringstream;
    typedef basic_stringstream <TCHAR, char_traits<TCHAR>, allocator<TCHAR> > tstringstream;

    typedef basic_ifstream<TCHAR, char_traits<TCHAR> >                        tifstream;
    typedef basic_ofstream<TCHAR, char_traits<TCHAR> >                        tofstream;
    typedef basic_fstream <TCHAR, char_traits<TCHAR> >                        tfstream;
} //namespace std
//---------------------------------------------------------------------------
#endif  //xLib_Common_xTypesH
