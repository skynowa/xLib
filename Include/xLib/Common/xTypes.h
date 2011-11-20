/**
 * \file  xTypes.h
 * \brief types
 */


#ifndef xLib_Common_xTypesH
#define xLib_Common_xTypesH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

    #if xUNICODE
        #define xTEXT(x)               L##x
        #define xT(x)                  xTEXT(x)

        typedef wchar_t                tchar;
    #else
        #define xTEXT(x)               x
        #define xT(x)                  xTEXT(x)

        typedef char                   tchar;
    #endif //xUNICODE

    #if xOS_ENV_WIN
        #if xCOMPILER_MINGW32
            typedef addrinfo           ADDRINFOT;
        #endif
    #elif xOS_ENV_UNIX
        typedef unsigned char          UCHAR;

        typedef signed short int       SHORT;
        typedef signed long int        LONG;
        typedef signed long long int   LONGLONG;

        typedef unsigned int           UINT;
        typedef unsigned short int     USHORT;
        typedef unsigned long int      ULONG;
        typedef unsigned long long int ULONGLONG;

        typedef addrinfo               ADDRINFOT;
    #endif

xNAMESPACE_END(NxLib)


xNAMESPACE_BEGIN(std)

    typedef basic_string<tchar, char_traits<tchar>, allocator<tchar> >        tstring;
    typedef basic_string<UCHAR, char_traits<UCHAR>, allocator<UCHAR> >           ustring;

    typedef basic_istream <tchar, char_traits<tchar> >                         tistream;
    typedef basic_ostream <tchar, char_traits<tchar> >                         tostream;
    typedef basic_iostream<tchar, char_traits<tchar> >                         tiostream;

    typedef basic_istringstream<tchar, char_traits<tchar>, allocator<tchar> > tistringstream;
    typedef basic_ostringstream<tchar, char_traits<tchar>, allocator<tchar> > tostringstream;
    typedef basic_stringstream <tchar, char_traits<tchar>, allocator<tchar> > tstringstream;

    typedef basic_ifstream<tchar, char_traits<tchar> >                         tifstream;
    typedef basic_ofstream<tchar, char_traits<tchar> >                         tofstream;
    typedef basic_fstream <tchar, char_traits<tchar> >                         tfstream;

xNAMESPACE_END(std)
//---------------------------------------------------------------------------
#endif  //xLib_Common_xTypesH
